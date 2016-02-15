//  Trivia Tool
//  Many thanks and huggles to Aleron, who debugged far
//  beyond the call of duty.
// -- Tabitha March 1999

// stuff added to put stuff directly onto channel by Him, June, 1999
// (based on stuff done by... uhh... someone, I forget, Beckster knows,
// I think)

// Various tweaks, including question & answer logging, by Anthrax
//    Q1 2000

// Automated question/answer prep from files added by Peaches

// Logging player scores & xp added 3/3/2005 by Anthrax

// Massive overhaul to v3.0 and documented functions on 3/10/2005 - Anthrax

// Changed question prep to pull Q/A sets at random from file, if possible - Anthrax
//    4/7/2005

// Added autoincrement for prepared questions and answers (tread/tans)
//    4/13/2006 Anthrax

// Made buzzer customizable (one character)
//    10/1/2006 Anthrax

// Made logfile name customizable (within asked subdir)
//    5/10/2010  Anthrax

// Doubled XP awards to 750/player, 5k max per question
//    5/10/2010  Anthrax

#include <Newhaven.h>
#include <ansi.h>

#define TRIV BASE "trivia/"

inherit ObjectCode;

// Definitions for PrivChat objects
#define CLIENT "/zone/null/toys/bin/pclient"
#define SERVER "/zone/null/toys/privchat/server"

// Definition for David's announcement command object
#define ANNOBJ "/usr/david/cmds/priv/brapannounce"

// Definitions for using prepared question/answer files
#define QLOG TRIV "ktrivia.log"
#define CURRENT TRIV "asked/ktrivia."
#define CAT6 "WC:"

// Help file locations
#define HELP  TRIV "ttool.hlp"
#define BHELP TRIV "ttool_brief.hlp"

// Where questions and answers are logged to when logging is enabled (default location)
#define LOG TRIV "asked/trivia.log"

// Objects that track trivia player scores
#define TRACKERS ({ \
    DAEMON "triviad",\
})

#define BEEP "\a"

// ([ (string)player_real_name : (int)score ])
mapping players;

// grid array of 6 arrays; each array holds names of player who got Q correct
mixed *grid;

// the PrivChat client object (blueprint)
object client;

// the announcer command object
object announcer;

int time, qno, ans_ok;
string bzc, channel, logfile, *kickedoff, *prepdqs;
status log_qs, ansi_ok;

status do_score( string arg );
status credadd( string who, int num );
status credrmv( string who, int num );
status do_reset( string str );
status do_brap(string question);
status set_logging( string str );
status errmsg( string msg );
status ok_msg( string msg );
status   warn( string msg );

// Sends string 'info' to the current channel
void brap(string info) {
    if(!client)
        client = present_clone(CLIENT, THISP);
    if(!client) {
        errmsg("Couldn't find client object!\nWould have sent: " +
          info );
        return;
    }
    client->server(channel + " " + info);
}

// Announces question on channel, inits question timer
status do_brap(string question) {
    if( !stringp(question) ) return 0;

    if( find_call_out("brap_done") != -1 )
        return errmsg("There is already a question being timed.");

    if( query_verb() == "task" && sizeof(prepdqs) )
        return errmsg("There are prepared questions; use 'tread' to ask them.");

    question = upper_case(question);
    if( log_qs ) write_file(logfile, question+endl);


    question = "\n---------------------------------------------------------------------\n"+
               question+
               "\n---------------------------------------------------------------------";

    ans_ok = 0;
    brap(question);

    call_out( "brap_done", time, THISP );

    return 1;
}

// Announces timer expiration on channel
void brap_done() {
    brap(
		sprintf("\n        %s%s%s%s  %s%s%s%s   %s%s%s  %s%s%s%s  ||\n"
		        "        %s   %s %s   %s %s   %s %s   %s ||\n"
		        "        %s%s%s%s  %s%s%s%s  %s%s%s%s%s %s%s%s%s  ||\n"
		        "        %s   %s %s  %s  %s   %s %s\n"
		        "        %s%s%s%s  %s   %s %s   %s %s     ()\n",
		        bzc,bzc,bzc,bzc, bzc,bzc,bzc,bzc, bzc,bzc,bzc, bzc,bzc,bzc,bzc,
		        bzc,bzc, bzc,bzc, bzc,bzc, bzc,bzc,
		        bzc,bzc,bzc,bzc, bzc,bzc,bzc,bzc, bzc,bzc,bzc,bzc,bzc, bzc,bzc,bzc,bzc,
		        bzc,bzc, bzc,bzc, bzc,bzc, bzc,
		        bzc,bzc,bzc,bzc, bzc,bzc, bzc,bzc, bzc, bzc,bzc
		)
	);
    ans_ok = 1;
}

void extra_create() {
	int i;

    seteuid( getuid() );
    /* basic objectcode stuffs */
    set("id", ({ "trivtool", "brapper", "ttool", "tool"}) );
    set( "short", "a brapper 4.4.3" );
    set( "long",
      "This is a nifty trivia tool.  It is crafted of a smooth, "
      "shiny metal that fits neatly in your palm.  Type <thelp> "
      "for commands."
    );

    /* global variable initializations: */
    time=40;
    channel="BRAP!";
    bzc = "#";
    kickedoff = ({ });
    players = ([ ]);
    grid = allocate( 6 );
    for( i=6; i--; ) grid[i] = ({ });
    log_qs = 1;
    qno = 1;
    prepdqs = ({ });
    logfile = LOG;
}

void extra_init() {
    if( !IsWizard( THISP ) ) return;

    add_action( "do_help",           "thelp" );
    add_action( "do_player",         "tplayer");
    add_action( "do_status",         "tstatus");
    add_action( "do_beep",           "tbeep");
    add_action( "do_kick",           "tkick" );
    add_action( "do_reset",          "treset" );
    add_action( "do_who",            "twho" );
    add_action( "do_credit",         "tcred" );
    add_action( "do_score",          "tscore" );
    add_action( "do_award",          "taward" );
    add_action( "do_brap",           "task" );
    add_action( "do_announce",       "tann" );
    add_action( "check_log",         "tlogcheck");
    add_action( "check_qfile",       "tqfilechk");
    add_action( "set_logging",       "tlog" );
    add_action( "change_time",       "ttime" );
    add_action( "change_channel",    "tchannel" );
    add_action( "prepare_questions", "tprep" );
    add_action( "read_question",     "tread" );
    add_action( "answer_question",   "tans" );
    add_action( "change_buzzer",     "tbuzz");
}

// Used to display error messages; always returns 1
status errmsg(string msg) {
	if( !stringp(msg) ) return 1;
	if( !ansi_ok )
		printf("+Trivia: %s\n", msg);
    else
        printf("%s+Trivia:%s %s\n", BLK BRED, NORM, msg);
    return 1;
}

// Used to display success messages; always returns 1
status ok_msg(string msg) {
	if( !stringp(msg) ) return 1;
	if( !ansi_ok )
		printf("+Trivia: %s\n", msg);
	else
	    printf("%s+Trivia:%s %s\n", BLK BGRN, NORM, msg);
	return 1;
}

// Used to display warning messages; always returns 1
status warn(string msg) {
	if( !stringp(msg) ) return 1;
	if( !ansi_ok )
		printf("+Trivia: %s\n", msg);
	else
	    printf("%s+Trivia:%s %s\n", BLK BYEL, NORM, msg);
	return 1;
}

// Loads a set of 6 questions from file 'str' (or default QLOG)
status prepare_questions( string str ) {
    string *fil, *new, fname;
    int i, logtime, size;

    logtime=time();
    fname = ( stringp(str) ? str : QLOG );
    ansi_ok = THISP->query_ansi();

    if( !exists(fname) )
        return errmsg( sprintf("File (%s) not found.", fname) );

    ok_msg( sprintf("Questions loaded from %s", fname) );

    fil = grab_file(fname);

    size = sizeof(fil);

    if( !size )
        return errmsg( sprintf("File (%s) contains no questions.",fil) );

    if( size % 12 ) // If the file does not excusively contain sets of 6 Q/A pairs
        prepdqs = fil[0..11]; // Pick the first set of 6 Q/A pairs
    else {  //Pick a random set of 6 Q/A pairs
		i = 12 * (random(size/12));
		prepdqs = fil[i..i+11];
	}

    if( !i )
        new = fil[12..size];
    else
        new = fil[0..i-1] + fil[i+12..size];

    set_logging("off");

    if( catch( rm(fname) ) )
		return warn( sprintf("Unable to change file %s."
		    "Questions will not be saved separately.", fname) );

    write_file(fname, implode(new, "\n")+"\n");
    write_file(CURRENT+logtime, implode(prepdqs, "\n")+"\n");
    ok_msg( sprintf("Question set saved to %s%d.",CURRENT,logtime));
    ans_ok = 0;
    return ok_msg( sprintf("Ready to read question #%d.\n", qno) );
}

// Selects prepared question 'str' (num) and asks on channel
status read_question(string str) {
	string val;
    int q, num;

    ansi_ok = THISP->query_ansi();

    if(!str) {
		num = qno;
	} else if(!sscanf(str, "%d%s", num, val ) || val != "")
		return errmsg("Syntax: tread [n]");

    if( !sizeof(prepdqs) )
		return errmsg("No questions have been prepared.");

    if( num < 1 || num > 6 ) {
	    if( qno == 7 )
            return errmsg("Question set completed, proceed with endgame.");
        return errmsg("Question # must be between 1 and 6 inclusive.");
	}

    if( find_call_out("brap_done") != -1 )
		return errmsg("A question is already being timed, please wait.");

    if( ans_ok )
        return errmsg("Please answer the previous question first.");

    ans_ok = 0;
    q = (num-1)*2;
    do_brap( sprintf("Q%d - %s", num, prepdqs[q] ) );
    printf( "Answer: %s\n", prepdqs[q+1] );
    return 1;
}

// Formats the question and sends it to the channel

// Displays the current help file
status do_help( string str ) {
	string file;

	switch( str ) {
		case "brief":
		case "-b"   :
		    file = BHELP;
		    break;
		default     :
		    file = HELP;
		    break;
	}

    ansi_ok = THISP->query_ansi();

	if( !exists(file) )
		return errmsg( sprintf("Help file (%s) not found.", file) );

    return( THISP->more_file( file ), 1 );
}

// Resets the recorded score for given player
void reset_score( string who ) {
	players[who] = 0;
}

// Resets all variables, with possible exception of player list
status do_reset(string str) {
    int i;

    grid = allocate( 6 );

    for( i = 6; i--; )
        grid[ i ] = ({ });

    for( i = sizeof(kickedoff); i--; )
        brap("/invite " + kickedoff[i]);

    kickedoff = ({ });
    prepdqs = ({ });
    log_qs = 1;
    qno = 1;
    ans_ok = 0;
    ansi_ok = THISP->query_ansi();

    if( !stringp(str) )
        if( query_verb() == "taward" ) str = "keep";
        else str = "end";

    switch(str) {
        case "no reset":
        case "noreset":
        case "keep":
        case "keep players":
        case "continue":
            walk_mapping( players, "reset_score" );
            return warn("Game information reset; preserving player list for next round.");

        case "clear":
        case "done":
        case "clear players":
        case "finish":
        case "end":
        default:
            players = ([ ]);
            return ok_msg("All game information reset.");
    }
}

// Adds a single player to the list of people playing
status add_player( string str ) {
	object who;
	string capname;
	mapping chans;

	if( !stringp(str) || str == "" ) return 0;

	str = lower_case(str);
	capname = CAP(str);

    if( !who = FINDP( str ) )
        return errmsg( sprintf( "%s is not online at present.", capname ) );

    if( member( players, str ) )
        return warn( sprintf( "%s is already playing trivia.", capname ) );

    players[str] = 0;

    if( !objectp(present_clone(CLIENT, who)) )
		move_object( clone_object(CLIENT), who );

    chans = SERVER->get_chans();

    if( member( chans[channel], str ) == -1 )
        brap("/invite " + str );

    return ok_msg( sprintf("Added %s.", capname) );
}

// Removes a single player from the list of people playing
status rmv_player( string str ) {
	string capname;
	int i;

	if( !stringp(str) || str == "" ) return 0;

	str = lower_case(str);
    capname = CAP(str);

    if( !member( players, str ) ) {
		errmsg( sprintf("%s is not playing.", capname) );
		return 0;
	}

    players -= ([ str ]);

    for( i = 6; i--; )
        grid[i] -= ({ str });

    return ok_msg( sprintf("Removed %s.", capname) );
}

// Adds/removes players in list 'str' from the player list
status do_player( string str ) {
    string *who, name;

    ansi_ok = THISP->query_ansi();

    if( !str )
        return errmsg("Syntax <tplayer [name1 -name2 .. name n]>");

    who = explode( str, " " );

    foreach( name : who ) {
		if( name == "" ) continue;
		if( name[0..0] == "-" )
		    rmv_player( name[1..] );
		else
		    add_player( name );
    }

    return 1;
}

// Kicks players in list 'str' off channel until game is over
status do_kick( string str ) {
	string *who, name;

    ansi_ok = THISP->query_ansi();

	if( !str )
	    return errmsg("Syntax <tkick [name1 name2 ... name n]>.");

	who = explode( str, " " );

	foreach( name : who )
		if( name != "" && rmv_player( name ) ) {
		    brap( sprintf("/kick %s", name) );
		    kickedoff += ({ name });
		}

    return 1;
}

// Displays the list of who's playing, either silently or on channel
status do_who(string arg) {
    string output, *names, extra;
    int i;
    status quiet;

    ansi_ok = THISP->query_ansi();

    if( !(i = sizeof( players ) ) )
        return errmsg( "There is currently nobody playing trivia.");

    output = sprintf("Player%s (%d):", ( i == 1 ? "" : "s" ), i );

    names = sort_array( m_indices(players), #'< );

    for( ;i--; )
        output += " " + CAP( names[ i ] );

    output += ".";

    if( stringp(arg) ) {
		if( arg[0..1] == "-q" ) {
			quiet = 1;
			if( strlen(arg) > 2 )
			    extra = arg[2..];
			else
			    extra = 0;
		} else
		    extra = arg;
	}

    if(stringp(extra))
        output += "  " + upper_case(extra);

    if(quiet)
        printf( "+Trivia: %s\n", output );
    else
        brap(output);

    return 1;
}

// Shows a person's 'live' status - offline, linkdead, or idle,
//    with a warning if over 2 minutes idle
string show_player_status( string who ) {
	object plyr;
	int idletime;
	string color;

	if( !stringp(who) ) return 0;

	plyr = FINDP(who);

    if( !objectp(plyr) )
        return sprintf("%-18s: [%sOFFLINE%s]", CAP(who),
            (ansi_ok? HIR:""), (ansi_ok? NORM:"") );

    if( !interactive(plyr) )
        return sprintf("%-18s: [%sLINKDEAD%s]", CAP(who),
            (ansi_ok? HIR:""), (ansi_ok? NORM:"") );

    idletime = query_idle(plyr);
    if( idletime > 600 ) color = HIR;
    else if( idletime > 120 ) color = HIY;
    else color = "";

    return sprintf("%-18s: %s%s%s", CAP(who),
        (ansi_ok ? color : ""),
        strfage("%m%M%s%S", idletime),
        (ansi_ok ? NORM : "") );
}

// Command parser for showing player status
status do_status( string str ) {
	string name;
	mixed plyrs;

    ansi_ok = THISP->query_ansi();

    if( !sizeof(players) )
        return errmsg("There is currently nobody playing trivia.");

	if( !stringp(str) ) { // Most common usage, probably
	    write("+Trivia: Current status of all players:\n");
	    plyrs = sort_array( m_indices(players), #'> );
	    foreach( name : plyrs )
			printf("  %s\n", show_player_status(name) );
	    return 1;
	}

    if( !member(players, str) )
		return errmsg( str + " is not on the player list.");

	printf("+Trivia: %s\n", show_player_status(str) );
	return 1;
}

// Sends a double beep to an individual player (optionally only if idle)
status beep_player( string name, int idle_only ) {
    object who;

    who = FINDP(name);
    if( !objectp(who) || !interactive(who) ) return 0;

    if( idle_only && query_idle(who) <= 120 ) return 0;

    tell_object(who, BEEP BEEP );

    return 1;
}

// Command parser for beeping players (option all/just idlers)
status do_beep( string str ) {
	string *beeped, *names;
	int num, tot;

    ansi_ok = THISP->query_ansi();

    if( !sizeof(players) )
		return errmsg("There is currently nobody playing trivia.");

    /* Uses filter_array() because filter() just won't take an extra arg for
       some odd reason */
    names = m_indices(players);
    tot = sizeof(names);

	if( str == "idlers" || str == "idle" || str == "-i" ) {
		beeped = filter_array( names, "beep_player", THISO, 1 );
		num = sizeof(beeped);
		return ok_msg( sprintf("%d player%s (idle more than 2 minutes) "
		    "out of %d total beeped.",
		    num, (num == 1 ? "":"s"), tot ) );
	}

	beeped = filter_array( names, "beep_player", THISO, 0 );
	num = sizeof(beeped);
	return ok_msg( sprintf("%d player%s out of %d total beeped.",
	        num, (num == 1 ? "":"s"), tot ) );
}

// Gives/removes credit for a correct answer for a question
//    to/from players on specified list
status do_credit( string str ) {
    int num;
    string *who, name, rest;

    ansi_ok = THISP->query_ansi();

    if( !str || ( sscanf( str, "%d %s", num, rest ) != 2 ) )
        return errmsg("Syntax <tcred [#] [name 1 name 2 .. name n ]>.");

    if( num < 0 || num > 6 )
        return errmsg( "Question # must be between 1 and 6 inclusive." );

    who = explode( rest, " " );

    foreach( name : who ) {
        if( name[0 .. 0] != "-" )
            credadd( lower_case( name ), num );
        else
            credrmv( lower_case( name[1..]  ), num );
    }
    return 1;
}

// Adds 'who' to the list of those who answered question 'num' right
status credadd( string who, int num ) {
    string WHO;
    int i;

    WHO = capitalize( who );

    if( sizeof( grid[ num - 1 ] ) > 0 )
        if( member( grid[ num - 1 ], who ) > - 1 )
            return warn( sprintf("%s already has credit for question %d.",
                WHO, num ) );

    if( !member( players, who ) )
        return errmsg( WHO + " is not playing.");

    grid[ num - 1 ] += ({ who });
    grid[ num - 1 ] = sort_array( grid[ num - 1 ], #'< );
    return ok_msg( sprintf("%s credited question %d.", WHO, num ) );
}

// Removes 'who' from the list of those who answered question 'num' right
status credrmv( string who, int num ) {
    string WHO;
    int i;

    WHO = capitalize( who );

    if( member( grid[ num - 1 ], who ) < 0 )
        return errmsg( sprintf( "%s has not been credited question %d.",
            WHO, num ) );

    grid[ num - 1 ] -= ({ who });
    return ok_msg(sprintf("%s no longer gets credit for question %d.", WHO, num ));
}

// Returns a string describing who got question 'num'+1 right
string get_qlist( int num ) {
	string out, *right;
	int i;

	out = sprintf("Q%d:", (num+1) );

	right = grid[num];

	if( !( i = sizeof(right) ) )
		out += " (nobody) ";
    else {
		for( ;i--; )
			out += " " + CAP(right[i]);
	    out += ".";
	}
    return out;
}

// Displays list(s) of who got specified/all question(s) correct
status do_score( string str ) {
	string out, answer;
	int qnum, begin, end, i;
	status silent;

    ansi_ok = THISP->query_ansi();

    if( !stringp(str) )
		return errmsg("Syntax <tscore [-q] [\"all\"| num [extra]]>.");

	if( str == "-q" ) {
	    silent = 1;
	    str = "all";
	} else if( str[0..1] == "-q" ) {
		silent = 1;
		if( strlen(str) > 3 )
		    str = str[3..];
		else
		    return errmsg("Syntax <tscore [-q] [\"all\"| num [extra]]>.");
	}

	begin = 1;
	end = 6;

	if( str != "all" )
	    switch( sscanf( str, "%d %s", qnum, answer ) ) {
			case 2:
			case 1:
			    if( qnum >= begin && qnum <= end ) {
					begin = end = qnum;  // redefine loop range to 1 question
					break;
				}
			default:
			    return errmsg("Syntax <tscore [-q] [\"all\"| [1-6] [extra]]>.");
	    }

	out = "";

	for( i = begin-1; i < end; i++ )
	    out += get_qlist( i ) + endl;

	if( stringp(answer) ) {
		answer = upper_case(answer);
		out += sprintf("A: %s", answer);
		if( log_qs )
		    write_file(logfile, answer + endl );
	}

    if( silent )
        printf("+Trivia: %s", ( begin == end ? out :
            "Score record for all questions:\n" + out ) );
    else
        brap( ( begin == end ? "":endl ) + out );

    return 1;
}

// Endgame - calculates score, award xp, displays to channel, logs scores, resets
status do_award( string str )
{
    int i, j, exp, award, base;
    float mult, playnum, correct;
    object player;
    string printable;
    mixed tmp;

    printable	= "";
    playnum = to_float(sizeof(players));
    mult = MIN(2500.0, (375.0 * playnum));

    for( i = 6; i--; ) {
        if( (j = sizeof(grid[ i ])) < 1 )
            continue;

        correct = to_float(j);
        award = to_int(mult / correct);

        for( ;j--; )
            if( member( players, grid[ i ][ j ] ) )
                players[ grid[ i ][ j ] ] += award;
    }

    tmp = transpose_array( ({ m_values( players ), m_indices( players ) }) );
    tmp = sort_array(tmp, lambda( ({'e1, 'e2}), ({ #'>,
          ({#'[, 'e1, 0}),
          ({#'[, 'e2, 0})
        })
      )
    );

    for( i = sizeof( tmp ); i--; ) {
        player = FINDP( tmp[ i ][ 1 ] );

        base = players[ tmp[ i ][ 1 ] ];

        if( !base ) {

            catch(filter_objects( TRACKERS, "update_trivia_player",
				to_string( tmp[i][1] ), 0, 0 ));

            continue;
        }

        if( player ) {
          if( !IsWizard(player) ) {
            exp=to_int(to_float(base)* 1.5 *MAX(1.0, to_float(player->query_eval())) );
            player->add_exp(exp);
		  } else {
            exp = 0;
		  }
	    }

        catch(filter_objects( TRACKERS, "update_trivia_player",
            to_string( tmp[i][1] ), base, exp ) );

        if( player )
            printable += sprintf("\n%18s scored %5d and was awarded %8d xp.",
                CAP( to_string(tmp[ i ][ 1 ]) ), base, exp );
        else
            printable += sprintf("\n%18s scored %5d and was awarded no xp [offline].",
                CAP( to_string(tmp[i][1]) ), base );
	}

    if( printable != "" ) brap(printable);
    do_reset(str);
    catch( filter_objects( TRACKERS, "Save" ) );
    return 1;
}

// Shows score for specified prepared question, with answer, on channel
int answer_question(string str) {
    string val;
    int i, a, num;

    ansi_ok = THISP->query_ansi();

    if( !ans_ok )
        return errmsg("The answer cannot be announced at this time.");

    if(!str) num = qno;
    else num = to_int(str);

    if( !intp(num) ) return errmsg("Syntax tans [#]");

    if( num < 1 || num > 6 )
        return errmsg("Question # must be between 1 and 6 inclusive.");

    if( !sizeof( prepdqs ) )
		return errmsg("No questions have been prepared.");

    if( find_call_out("brap_done") != -1 )
        return errmsg("The timer has not yet finished, please wait.");

    a = ((num-1)*2)+1;
    val = prepdqs[a];
    do_score( sprintf("%d %s", num, val) );
    qno++;
    ans_ok = 0;
    if( qno <= 6 ) return ok_msg(sprintf("Ready to read question #%d.", qno));
    return warn("Question set completed, ready for endgame.");
}

// Changes the length of the question timer to specified # of seconds.
//    Displays the resulting timer value, even if unchanged.
status change_time(string str) {
	int i;

    ansi_ok = THISP->query_ansi();

	if( stringp(str) ) {
      if( !intp(i=to_int(str)) || i < 1 )
        return errmsg("Positive integers only.");
      time = i;
    }

    return ok_msg( sprintf("Question timer set to %d seconds.", time) );
}

// Sets the question channel to 'c'
//  Displays the assigned channel, even if unchanged.
status change_channel(string c) {
	mapping chans;

	ansi_ok = THISP->query_ansi();

        if( !stringp(c) )
            return ok_msg(sprintf("Question channel set to '%s'.", channel));

	chans = SERVER->get_chans();

	if( !member(chans, c) )
	    return errmsg(sprintf("There is no %s channel.", c));

        channel = c;
    return ok_msg( sprintf("Question channel set to '%s'.", channel) );
}

// Checks file for either parity (alternating Q/A) or even number of
//    sets of Q/A pairs
status perform_check(string *arr, int size, string type ) {
    int i;

    if( type != "qasets" )
        for(i=0; (i<size && (arr[i])[<1..]=="?"); i+=2) {}
    else
        for(i=10; (i<size && arr[i][0..2]==CAT6); i+=12) {}

    if(i>=size) {
		if( type == "qasets" )
		    return ok_msg( sprintf("%d complete question sets found.",
		        size/12) );
		else
		    return ok_msg( sprintf("%d question/answer pairs found.",
		        size/2) );
	} else return errmsg( sprintf("Odd line found: %d.", i+1) );
}

// Initiates parity check of log at 'path'
status check_log(string path) {
    string *file, fname;
    int size;

    ansi_ok = THISP->query_ansi();

    if( stringp(path) && exists(path) ) fname = path;
    else fname = LOG;

    if( !exists(fname) )
       return errmsg("Unable to locate file "+fname);

    file = grab_file(fname);

    if(!size=sizeof(file))
        return errmsg( sprintf("The file (%s) is empty.", fname) );

    printf("+Trivia: Checking parity of file (%s)...\n", fname);
    call_out("perform_check", 1, file, size, "parity");

    return 1;
}

// Initiates check on Q/A log to make sure it's got an even number of
//   sets of 6 question/answer pairs
status check_qfile( string path ) {
	string *file, fname;
	int size;

    ansi_ok = THISP->query_ansi();

	if( stringp(path) && exists(path) ) fname = path;
	else fname = QLOG;

    if( !exists(fname) )
        return errmsg("Unable to locate file "+fname);

	file = grab_file(fname);

    if(!size=sizeof(file))
        return errmsg( sprintf("The file (%s) is empty.", fname) );

	printf("+Trivia: Scanning file (%s) for whole Q/A sets using delimiter [%s].\n",
	    fname, CAT6);
	call_out("perform_check", 1, file, size, "qasets");

	return 1;
}

// Toggles or sets question/answer logging on or off, or sets target log file
status set_logging( string str ) {
	string msg;

    if( !stringp(str) ) { log_qs = !log_qs; }
    else switch( str ) {
		case "-on"  : log_qs = 1;       break;
		case "-off" : log_qs = 0;       break;
		default     : log_qs = 1; logfile = TRIV + "asked/" + str; break;
	}

    ansi_ok = THISP->query_ansi();

    if( log_qs ) {
		if( ansi_ok ) msg = HIG "enabled" NORM;
		else msg = "enabled";
	} else {
		if( ansi_ok ) msg = HIR "disabled" NORM;
		else msg = "disabled";
	}

	ok_msg( sprintf("Question and answer logging is now %s.", msg) );
	if( log_qs )
	    ok_msg( sprintf("They will be logged to %s", logfile ) );

	return 1;
}

// Uses David's BRAP announcer module to notify all users about the game
status do_announce( string str ) {
    if( !objectp(announcer) )
        if( catch( announcer = load_object(ANNOBJ) ) || !objectp(announcer) )
            return errmsg("Unable to load announce command handler.");

    return announcer->do_cmd( "tann", str );
}

// Lets the user set a custom character for the BRAP buzzer
status change_buzzer( string str ) {
	if( !stringp(str) || invalid_string(str) || strlen(str) != 1 ) {
		bzc = "#";
		return errmsg("Invalid entry; buzzer character set to default (#).");
	}
	bzc = str;
	return ok_msg(sprintf("Buzzer character is now %s.", bzc));
}

string post_long() {
    return( sprintf("Timer set to %d seconds; channel: '%s'; logging: %s\nLogfile: %s\n",
        time, channel, ( log_qs ? "enabled" : "disabled"), logfile ) );
}

// For troubleshooting purposes, displays values for major variables
void
Dump() {
	printf("Players: %O\n", players);
	printf("Grid: %O\n", grid );
	printf("Prepped Qs: %O\n", prepdqs);
	printf("Kicked off players: %O\n", kickedoff);
	printf("Question Number: %d\n", qno);
}
