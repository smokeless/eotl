inherit ObjectCode;
#define owner find_player( owname )
int pitched, allow_all;
string *allow_list, owname="";
void extra_create()
{
        set("id","tent");
        set("short","a nice little red tent");
        set_light( 1 );
        set("weight",1);
        set("gettable",1);
        set("droppable",1);
        allow_list=({"sarah","becca","alake","jester"});
}

void long( string str )
{
        if( ENV( THISP ) == THISO && pitched )
        {
                write(
 "A Lovely Spacious Tent\n" +
 "   The inside of this tent sure seems bigger than it should be,  but the\n" +
 "little light that manages to filter though the canvas walls gives the\n" +
 "enclosure a sleepy cosy feeling. Infact...  where's that sleeping bag?\n" +
 "\n---- The only way out,  is out. *yawn*\n" );
 }
        else
        {
             if( pitched ) write( "This is " +
               ( THISP == owner?"your":capitalize( owname ) + "'s" ) +
               " neat little red tent.\n" );
             else
               write( "The neatly folded red tent is looks just dandy...\n" );
               }
}

string short()
{
        if(owner)return("a little red tent."+
                ( pitched ? "(pitched)" : "(packed away)" ) );
        else return "an unwanted tent";
}

void init()
{
        add_action( "enter", "enter" );
        add_action( "out", "out" );
        if( !owner && THISP == ENV( THISO ) ) owname = PRNAME;
        if( THISP != owner ) return;
        add_action( "pitch", "pitch" );
        add_action( "unpitch", "unpitch" );
        add_action( "allow", "admit" );
        add_action( "boot", "boot" );
        add_action( "allowed", "allowed" );
        add_action( "help", "help" );
}

static int boot( string str )
{
        object pl;
        int i;
        str = lower_case( str );
        i = searcha( allow_list, str );
        if(remote_command()){return 1;}
        if( i >= 0 )
        {
                write( capitalize( str ) + " no longer admitted.\n" );
                allow_list = deletea( allow_list, i );
        }
        pl = find_player( str );
        if( !pl || ENV( pl ) != THISO )
        {
                if( i == -1 ) write( capitalize( str ) + " isn't here.\n" );
                return 1;
        }
        move_object( pl, ENV( THISO ) );
        write( "You kick " + capitalize( str ) + " out of your tent.\n" );
        say( PNAME + " kicks " + capitalize( str ) + " out of " +
                possessive( THISP ) + " tent.\n" );
        tell_object( pl, PNAME + " kicks you out of " +
                possessive( THISP ) + " tent.\n" );
        tell_room( ENV( pl ), capitalize( str ) + " is kicked out of " +
                PNAME + "'s tent.\n", ({ pl }) );
        return 1;
}

static int help( string str )
{
        if( str == "tent" )
        {
write("Commands:\npitch tent\nenter tent\nadmit <name>\nadmit all\nadmit none\nallowed\nunpitch tent\n");
return 1;
        }
        return 0;
}

static int allow( string str )
{
    if(remote_command()){return 1;}
        if( !str ) return 0;
        if( str == "all" )
        {
                write( "Everyone allowed.\n" );
                allow_all = 1;
                return 1;
        }
        if( str == "none" )
        {
                write( "No one allowed.\n" );
                allow_all = 0;
                allow_list = ( {} );
                return 1;
        }
        allow_list += ({ lower_case( str ) });
        write( capitalize( str ) + " allowed.\n" );
        return 1;
}

static int allowed( string str )
{
        int i;

        if( allow_all )
        {
                write( "Everyone allowed.\n" );
                return 1;
        }
        if( !sizeof( allow_list ) )
        {
                write( "No one allowed but you.\n" );
                return 1;
        }
        write( "People allowed in your tent : \n" );
        for( i=0; i<sizeof(allow_list); i++ )
        {
                write( " - " + capitalize( allow_list[i] ) + "\n" );
        }
        return 1;
}

static int pitch( string str )
{
        if( str != "tent" ) return 0;
        if( ENV( THISO ) != THISP )
        {
                write( "You need to be carrying it.\n" );
                return 1;
        }
        write( "You pitch your tent.\n" );
        say( PNAME + " pitches " + possessive( THISP ) + " tent.\n" );
        move_object( THISO, ENV( THISP ) );
        pitched = 1;
        set("gettable",0);
        set("droppable",0);
        return 1;
}

static int unpitch( string str )
{
        if( str != "tent" ) return 0;
        if( ENV( THISO ) != ENV( THISP ) )
        {
                write( "You need to be outside it.\n" );
                return 1;
        }
        if( first_inventory( THISO ) )
        {
                write( "The tent's not empty.\n" );
                return 1;
        }
        write( "You unpitch your tent.\n" );
        say( PNAME + " unpitches " + possessive( THISP ) + " tent.\n" );
        move_object( THISO, THISP );
        pitched = 0;
        set("gettable",1);
        set("droppable",1);
        return 1;
}

static int enter( string str )
{
        if( str != "tent" || ENV( THISP ) != ENV( THISO ) ) return 0;
        if( THISP != owner &&
            searcha( allow_list, PRNAME ) == ( -1 ) &&
            !allow_all )
        {
              write( "You can't get into the tent.\n" );
              tell_room( THISO, PNAME + " tried to get in,  but couldn't.\n" );
              return 1;
        }
        if( THISP->in_combat() )
        {
                write( "You can't enter during combat.\n" );
                return 1;
        }
        write( "You enter the tent.\n" );
        say( PNAME + " enters the tent.\n" );
        move_object( THISP, THISO );
        say( PNAME + " enters the tent.\n" );
        command( "glance", THISP );
        return 1;
}

static int out( string str )
{
        if( ENV( THISP ) != THISO ) return 0;
        write( "You leave the tent.\n" );
        say( PNAME + " leaves the tent.\n" );
        move_object( THISP, ENV( THISO ) );
        say( PNAME + " climbs out of the tent.\n" );
        command( "glance", THISP );
        return 1;
}
query_enter_ok()
{
        if( THISP != owner &&
            searcha( allow_list, PRNAME ) == ( -1 ) &&
            !allow_all )
        {
              write( "You can't get into the tent.\n" );
              tell_room( THISO, PNAME + " tried to get in,  but couldn't.\n" );
              return 1;
        }
}
destruct_signal()
{
        if( THISP != owner &&
            searcha( allow_list, PRNAME ) == ( -1 ) &&
            !allow_all )
        {
              write( "You can't get into the tent.\n" );
              tell_room( THISO, PNAME + " tried to get in,  but couldn't.\n" );
              return 1;
        }
}
query_prevent_shadow(){return 1;}
