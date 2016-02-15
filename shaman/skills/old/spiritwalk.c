/*
    Spirit walk for shaman.
    Lets them get out of their bodies for
    a bit. Maybe make it so that they leave a
    corpse that they get yanked to?
    By:
       Socialism 2012
*/

#include <ansi.h>
inherit BaseCommand;
inherit AnsiTellCode;

void extra_create()
{
    set( "name", "spirit walk" );
    set( "help",
         "Name  : Spirit walk\n"
         "Cost  : Half max health, all max mana, all fatigue.\n"
         "Type  : Other\n"
         "Usage : spirit walk\n"
         "Requirements : 70 str, 60 int, 70 wil.\n"
         "\n" 

         "Shaman have long been known for their ability to "
         "channel the spirits. They are lesser known for their "
         "ability to become one with the spirits. A strong and "
         "powerful shaman can will itself to become one with the "
         "spirit world, though leaving the realm of physical "
         "existence is quite taxing.\n"         
         );
    set( "private", 1 );
    set( "no_combat", 1 );
    set( "no_rest", 1 );
    set( "action", "spirit" );
    set( "verb", "walk" );
    set( "usage", "spirit walk" );
    set( "function", "walkme" );
    set( "guild", "shaman" );
    set( "class", "other" );
    set( "cost", ([ "mana" : 0 ]) );
    set( "min", ([ "stats"      : ([ "str" : 70, "int" : 60, "wil" : 70 ]) ]) );
    set( "success", ([ "skills" : ({ "spirit walk", 1, 1 }),
                       "stats"  : ({ "int", 1, 10, "wil", 1, 10 }) ]) );
    set( "offchance", 15 );
    set( "no_rest", 0 );
    set( "no_combat", 1 );
    set( "delay", 1 );
}

/*
mapping cost_check()
{
    int mana = THISP->query_max_mana();
    int ftg = THISP->query_max_fatigue();
    int health = THISP->query_max_hp() / 2;
    mapping cost = ([ "fatigue" : ftg, "hp" : health, "mana" : mana ])
    return cost;
}
*/

status okattempt()
{

    if( !::okattempt() ) 
      return 0;
   
    if( THISP->query_mana() < THISP->query_max_mana() )
    {
      ansi_tell( THISP, "You do not have enough mana\n", RED );
      return 0;
    }
    
    if( THISP->query_fatigue() < THISP->query_max_fatigue() )
    {
      ansi_tell( THISP, "You are too fatigued.\n", RED );
      return 0;
    }
    
    if( THISP->query_max_hp() < ( THISP->query_max_hp() / 2 ) )
    {
      ansi_tell( THISP, "You are not healthy enough.\n", RED );
      return 0;
    }      
   
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
 
void walkme()
{    
    object shad;
    
    if( success_roll() <= 0 )
    {
      ansi_tell( THISP, "You focus inwards. Your eyes blur out of focus. " 
        "You can feel your spirit struggling to be free from your body. "
        "Unfortunately nothing happens.\n", RED );
      ansi_tell_room( ENV( THISP ), sprintf( "%s begins to to twitch. %s "
        "body convulses and %s eyes turn milky white. After a moment the "
        "seizure passes.\n", THISP->query_name(), CAP( possessive( THISP ) ),
        possessive( THISP ) ), RED, ({ THISP }) );
      THISP->add_hp( - THISP->query_max_hp() / 2 );
      THISP->add_fatigue( - THISP->query_max_fatigue() );
      THISP->add_mana( - THISP->query_max_mana() );
      return;
    }
 
    ansi_tell( THISP, "You focus inwards. Your eyes blur out of focus. " 
        "You can feel your spirit struggling to be free from your body. "
        "Then you feel nothing.\n", RED );
    ansi_tell_room( ENV( THISP ), sprintf( "%s begins to to twitch. %s "
        "body convulses and %s eyes turn milky white.\n", 
        THISP->query_name(), CAP( possessive( THISP ) ),
        possessive( THISP ) ), RED, ({ THISP }) );
    
    // Pry should write an include file but,
    // still testing shit.
    shad = clone_object( "/usr/socialism/shaman/obj/spirit_shad" );
    THISP->make_me_ghost();
    shad->sh_init( THISP, THISP->query_skill( "spirit walk" ) );
}
