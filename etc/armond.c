inherit MonsterAsk;
inherit MonsterTalk;

void extra_create()
{
    object ob;

    if( !clonep() )
        return;

    seteuid( getuid() );
    set_name( "Armond" );
    add_alias( "armond" );
    add_alias( "man" );
    add_alias( "wanderer" );
    set_short( "Armond the Wanderer" );
    set_gender( "male" );
    set_long( "Armond is a grizzled old man.  His skin looks more like "
      "tanned leather and his clothing seems to be part of his body.  "
      "Despite his obvious age, he looks frightfully strong, and his "
      "eyes burn with the fierceness of a man who has survived many a "
      "peril on determination alone.  He has wandered the desert for a "
      "lifetime, and still seems quite alert.  He looks as though he "
      "could be of some service if you inquired about recieving his "
      "help." );
    set_race( "human" );
    set_alignment( 500 );
    set_stat( "str", 100 );
    set_stat( "int", 70 );
    set_stat( "wil", 200 );
    set_stat( "con", 120 );
    set_stat( "dex", 150 );
    set_stat( "chr", 35 );
    set_proficiency( "hands", 30 );
    set_proficiency( "staff", 35 );
    set_offensive_level( 20 );
    set_defensive_level( 20 );
    set_chat_rate( 40 );
    set_chat_chance( 20 );
    add_phrase( "Armond peers at you, seeming to judge your worth.\n" );
    add_phrase( "Armond growls in a rasping voice: What is it you want?\n" );
    add_phrase( strformat( "Armond snarls at you: If you want to ask me "
      "for help, fine.  Otherwise get out of my sight.\n" ) );
    add_phrase( "Armond says: I know the desert like the back of my hand.\n" );
    ask_me_about( "help", "@train_info" );
    add_combat_phrase( "Armond grunts: I'll crush you like a grape.\n" );

    ob = clone_object( ARMOR "hooded_cloak" );
    move_object( ob, THISO );
    wear_armor( ob );
}

void post_engage_combat( object attacker, object victim )
{
    if( victim == THISO )
        command( "say you miserable wretch!  Die like the dog you are!" );

}
void extra_init()
{                      
    add_action( "train_em", "train");
    add_action( "show_cost", "cost");
} 

int train_info()
{
    command( "say Ah yes, another lost soul in seek of my guidance.  "
      "You are not the first to ask me for help my child, and I doubt you "
      "will be the last.  Since I have spent so much time in the desert "
      "I truly know how to survive there.  For a small fee I can train "
      "you in the ways of finding your direction in the desert.  Such "
      "knowledge can prevent you from getting lost and thereby save your "
      "life." );
    return 1;
}

int show_cost( string arg )
{
    int xpcost, ccost, prof;

    prof = 1;

    if( !arg )
      return( command( "say You would like to know the cost of which "
        "proficiency?" ), 1 );

    if( arg != "direction" && arg != "all" )
      return( command( "say I only train people in the direction "
        "proficiency." ), 1 );

    prof  += THISP->query_misc_proficiency( "direction" );
    xpcost = prof * prof;
    ccost  = prof * 6;

    command( "say It will cost " + xpcost + " xp and " + ccost + 
      " coins to raise your direction proficiency to " + prof + "." );
    return 1;
}

int train_em( string arg )
{
    int xpcost, ccost, prof;


    if( !arg )
      return( command( "say You would like to train in which "
        "proficiency?" ), 1 );

    if( arg != "direction" )
      return( command( "say I only train people in the direction "
        "proficiency." ), 1 );

    prof  += THISP->query_misc_proficiency( "direction" ) + 1;
    xpcost = prof * prof;
    ccost  = prof * 6;

    if( THISP->query_money() < ccost )
      return( command( "say You waste of my time! You have not "
        "my fee!!" ), 1 );

   if( THISP->query_exp() < xpcost )
     return( command( "say You lack the experience to learn." ), 1 );

    THISP->add_exp( -xpcost );
    THISP->add_money( -ccost );
    THISP->set_real_misc_proficiency_value( "direction", prof );
    write_file( ARMOND_LOG, ctime() + " -- " + CPRNAME + " raised " +
      possessive( THISP ) + " direction prof to " + prof + " for " +
      xpcost + " xp and " + ccost + " coins.\n" );
    command( "say Remember this lesson, it may save your life." );
    return 1;
}
