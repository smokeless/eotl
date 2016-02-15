/*
     Ancestral tale is based on
     comfort from the bard guild.
     Written by:
             Dorf 5-19-03
     Repurposed for shaman by:
     Socialism 9/12
*/

#include <ansi.h>
inherit BaseCommand;
inherit AnsiTellCode;

void extra_create()
{
    set( "name", "ancestral tale" );
    set( "help",
         "Name : ancestral tale\n"
         "Cost  : 1 Mana per skill level\n"
         "Type  : Healing\n"
         "Usage : weave ancestral tale\n"
         "Requirements : 40 int, 50 chr\n"
         "\n" 

         "The tales of the ancestors can boost the morale of "
         "almost anyone. "
         "While not as powerful as its clerical relatives the "
         "tales of ancestors can restore some vigor. The shaman "
         "opens his mind to the spirits and tells a particularly "
         "rallying story. All party members who heed the words "
         "will feel refreshed.\n"         
         );
    set( "private", 1 );
    set( "action", "weave" );
    set( "verb", "ancestral tale" );
    set( "usage", "weave ancestral tale" );
    set( "function", "tell_tale" );
    set( "guild", "shaman" );
    set( "class", "healing" );
    set( "cost", ([ "mana" : 1 ]) );
    set( "min", ([ "stats"      : ([ "int" : 50, "chr" : 50 ])   ]) );
    set( "success", ([ "skills" : ({ "ancestral tale", 1, 1 }),
                       "stats"  : ({ "int", 1, 10 }) ]) );
    set( "offchance", 7 );
    set( "no_rest", 0 );
    set( "no_combat", 1 );
    set( "delay", 1 );
}
 
status okattempt()
{
   int x = THISP->query_skill( "ancestral tale" );

   if( !::okattempt() ) 
     return 0;

   if( x < 1 )
       return( write( "You do not know any tales.\n"), 0 );

   if( THISP->query_mana() < x )
       return( write( "You're too mentally exhausted.\n"), 0 );
 
   if( THISP->query( MuteP ) )
   {
       ansi_tell( THISP, "You cannot speak.\n", RED );
       return 0;
   }
 
   if( THISP->test_prop( CastingP ) )
   {
      ansi_tell( THISP, "You are already casting something.", RED );
      return 0;
   }
 
   return 1;
}
 
void tell_tale()
{
    int heal;
    object temp, *members;
 
    THISP->add_mana( -THISP->query_skill( "ancestral tale" ) );
 
    if( success_roll() <= 0 )
    {
      ansi_tell( THISP, "You open your mind to the spirts of your "
        "ancestors. You hear many voices but cannot make out an "
        "inspiring tale.", RED );
      ansi_tell_room( ENV( THISP ), sprintf( "%s looks to the ancestral spirits for "
        "guidance. %s mouth drops open but %s says nothing.", PNAME, 
        CAP( possessive( THISP ) ), subjective( THISP ) ), 
        YEL, ({ THISP }) );
      return;
    }
 
    ansi_tell_room( ENV(THISP), sprintf( "%s looks to the ancestral spirits "
      "for guidance. %s mouth falls open. %s recites a tale of heroics "
      "and valor.", PNAME, CAP( possessive( THISP ) ),
      CAP( subjective( THISP ) ) ), YEL, ({ THISP }) );
    ansi_tell( THISP, sprintf( "You open your mind to the spirits "
      "of your ancestors. A story of valor and bravery flashes "
      "in front of your eyes. You recite what you see." ), RED );

    members = THISP->query_group_members();
    if( !sizeof( members )) members = ({ THISP });
    else members = filter( members, #'present, ENV( THISP ) );
    members -= filter_objects( members, "query", DeafP );
 
    foreach( temp : members )
    {
        heal = temp->query_max_hp() *
               ( THISP->query_skill( "ancestral tale" ) +
               THISP->query( "chr" ) ) / 5;
        heal =  ( heal / 2 ) + random( heal / 2 );
 
        ansi_tell( temp, "The tale empowers your body and steels your morale.", YEL );
        ansi_tell_room( ENV( temp ), sprintf( "%s looks empowered by "
            "the tale.", temp->query_name() || "Somebody" ),
            YEL, ({ temp }) );
        temp->add_hp( heal );
        temp->add_fatigue( heal );
    } 
    return;
}
