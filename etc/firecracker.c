/* firecracker.c by Lightning 8/13/92
** shoot a large message into the air
** modified by Locus to use Hannah's mortals/wizards on gossip echo 10/30/93
** modified by Reverend to ansify it. somethin like 03/somethin/99
*/

object LAST;
inherit ObjectCode;

#define CHANNEL	"/secure/player/commands/channel"

#define LINE1 "            [1;AAm.                [1;BBm.         [1;CCm.         [1;DDm.             [1;EEm.[0;0m\n"
#define LINE2 "                [1;AAm.             [1;BBm.        [1;CCm.        [1;DDm.           [1;EEm.[0;0m\n"
#define LINE3 "                    [1;AAm.          [1;BBm.       [1;CCm.       [1;DDm.         [1;EEm.[0;0m\n"
#define LINE4 "                        [1;AAm.       [1;BBm.      [1;CCm.      [1;DDm.       [1;EEm.[0;0m\n"
#define LINE5 "                        [1;HHm.       [1;IIm.      [1;JJm.      [1;KKm.       [1;LLm.[0;0m\n"
#define LINE6 "                    [1;HHm.          [1;IIm.       [1;JJm.       [1;KKm.         [1;LLm.[0;0m\n"
#define LINE7 "                [1;HHm.             [1;IIm.        [1;JJm.        [1;KKm.           [1;LLm.[0;0m\n"
#define LINE8 "            [1;HHm.                [1;IIm.         [1;JJm.         [1;KKm.             [1;LLm.[0;0m\n"
#define SIDE "[1;FFm.  [1;FFm.  [1;FFm.  [1;FFm.[0;0m"
#define SIDE2 "[1;GGm.  [1;GGm.  [1;GGm.  [1;GGm.[0;0m"
#define SPACE "                                                  "
#define MAXLEN 56

status do_mortal_wizgos_echoall( string msg );
void
extra_create() {
    set("id",({"firecracker","cracker"}));
    set("short","a firecracker");
    set("long","An industrial-strength super-duper firecracker.\n"+
      "Its explosion can probably be seen all over the world.\n"+
      "Type \"shoot firecracker <message>\" to display a message in the air.\n"+
      "The message should be less than "+MAXLEN+" characters long.\n");
    LAST=THISO;
}

void
extra_init() {
    if (environment() != THISP)
	return;
    add_action("shoot", "shoot");
}

status
shoot(string arg) {
    string whole, temp;
    int ME;
    string *words;
    string phrase;
    string OUT;
    string *mess;
    object *all;
    int i;
    string aa,bb,cc,dd,ee,ff,gg,hh,ii,jj,kk,ll;
    string l1,l2;
    string s1,s2;

    if (!arg)
    {
	notify_fail("What do you want to shoot?\n");
	return (0);
    }
    if (sscanf(arg, "%s %s", temp, arg) != 2 || !id(temp))
    {
	write("What message do you want to shoot into the sky?\n");
	return (1);
    }

    mess = ({});
    words = explode(arg," ");
    phrase = "";
    for(i=0;i<sizeof(words);i++) {
	if(strlen(phrase) + strlen(words[i]) < MAXLEN)
	    phrase += words[i]+" ";
	else {
	    mess += ({phrase});
	    phrase = words[i]+" ";
	    while(strlen(phrase) > MAXLEN) {
		phrase=phrase[0..MAXLEN-1];
		mess += ({phrase});
		phrase = words[i][MAXLEN..strlen(words[i])]+" ";
	    }
	}
    }
    mess += ({phrase});
    for(i=0;i<sizeof(mess);i++) {
	phrase=mess[i];
	phrase = phrase[0..(strlen(phrase)-2)];
	temp = extract(SPACE, 0, (MAXLEN-strlen(phrase))/2);
	phrase = temp + phrase + temp;
	while(strlen(phrase) < 60) phrase +=" ";
	mess[i]=phrase;
    }


    aa=to_string(31 + random(6));
    bb=to_string(31 + random(6));
    cc=to_string(31 + random(6));
    dd=to_string(31 + random(6));
    ee=to_string(31 + random(6));
    ff=to_string(31 + random(6));
    gg=to_string(31 + random(6));
    hh=to_string(31 + random(6));
    ii=to_string(31 + random(6));
    jj=to_string(31 + random(6));
    kk=to_string(31 + random(6));
    ll=to_string(31 + random(6));
    l1 = LINE1 + LINE2 + LINE3 + LINE4;
    l2 = LINE5 + LINE6 + LINE7 + LINE8;
    s1 = SIDE;
    s2 = SIDE2;
    l1 = implode(explode(l1,"AA"),aa);
    l1=implode(explode(l1,"BB"),bb);
    l1=implode(explode(l1,"CC"),cc);
    l1=implode(explode(l1,"DD"),dd);
    l1=implode(explode(l1,"EE"),ee);
    s1=implode(explode(s1,"FF"),ff);
    s2=implode(explode(s2,"GG"),gg);
    l2=implode(explode(l2,"HH"),hh);
    l2=implode(explode(l2,"II"),ii);
    l2=implode(explode(l2,"JJ"),jj);
    l2=implode(explode(l2,"KK"),kk);
    l2=implode(explode(l2,"LL"),ll);
    OUT = "";
    for(i=0;i<sizeof(mess);i++) {
	phrase = mess[i];
	phrase = "["+random(2)+";"+(31 + random(6))+"m"+phrase+"[0;0m";
	if(i == (sizeof(mess)/2)) OUT += s1 + phrase + s2 + "\n";
	else OUT += "            "+phrase+"\n";
    }
    whole = PNAME+" launches a firecracker into the air . . .\n"+
    l1 +
    OUT +
    l2;
	do_mortal_wizgos_echoall(whole);
destruct(THISO);
    return 1;
}

status do_mortal_wizgos_echoall( string msg )
{
    object	*list,ob;
    string	 channels;
    int      i;

    notify_fail( "What do you want to echoall?\n" );
    if( !msg )
	return 0;
    list = users();
    for( i = 0; i < sizeof( list ); i++ )
    {
	ob = list[ i ];
	if (ob && GetLevel(ob) == "mortal" ||
	  (pointerp(channels = ob->query(ChannelP)) &&
	    searcha(channels, "gossip") != -1))
	{
	    tell_object( ob, msg);
	}
    }
    return 1;
}
query_last() {
    return LAST;
}
set_last(object last) {
    LAST = last;
    return;
}
