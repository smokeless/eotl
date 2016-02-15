/*
    Regenerative trance is a skill for the shaman guild.
    The shaman enters a trance which disallows all actions.
    It does however boost regeneration of hp, mana, and wil.
      Socialism 2012
*/

#include <ansi.h>

inherit BaseCommand;
inherit AnsiTellCode;

#define TRANCESHAD "/usr/socialism/shaman/obj/trance_shad"

void extra_create()
{
    set( "name", "trance" );
    set( "help",
         "Name : trance\n"
         "Cost  : It only costs time.\n"
         "Type  : Healing\n"
         "Usage : begin trance\n"
         "Requirements : 20 wil \n"
         "\n" 

         "This is the most basic of shamanistic skills. "
         "The shaman enters a trance which binds them to "
         "the spirit realm. While in this trance their "
         "body will regenerate much faster than the normal "
         "rate. Unfortunately while in the trance the shaman "
         "is incapable of performing any action.\n"         
         );
    set( "private", 1 );
    set( "action", "begin" );
    set( "verb", "trance" );
    set( "usage", "begin trance" );
    set( "function", "trance" );
    set( "guild", "shaman" );
    set( "class", "healing" );
//    set( "cost", ([ "mana" : 1 ]) );
    set( "min", ([ "stats"      : ([ "wil" : 20 ])   ]) );
    set( "success", ([ "skills" : ({ "trance", 1, 1 }),
                       "stats"  : ({ "wil", 1, 10 }) ]) );
    set( "offchance", 7 );
    set( "no_rest", -1 );
    set( "no_combat", 1 );
    set( "delay", 1 );
}
 
status okattempt()
{
   int tranceskill = THISP->query_skill( "trance" );

   if( !::okattempt() ) 
     return 0;

   if( tranceskill < 1 )
       return( write( "You don't know that skill.\n"), 0 );
 
   if( THISP->test_prop( CastingP ) )
   {
      ansi_tell( THISP, "You are already doing something else.\n", RED );
      return 0;
   }
 
   return 1;
}
 
void trance()
{
    object shad;
    object tranceobj;
    string objname;
    int duration = THISP->query_skill( "trance" );
 
    if( success_roll() <= 0 )
    {
      ansi_tell( THISP, "You prepare to enter a deep trance. "
        "You stare straight ahead and attempt to empty your mind. "
        "You lose track of what you were doing while counting imaginary "
        "sheep.\n", CYAN );
      ansi_tell_room( ENV( THISP ), sprintf( "%s stares off into space, "
      "%s eyes start to glaze over. Suddenly %s snaps back to reality.\n", 
      THISP->query_name(), possessive( THISP ), subjective( THISP ) ),
      CYAN, ({ THISP }) );
      return;
    }
 
    ansi_tell( THISP, "You prepare to enter a deep trance. "
        "You stare straight ahead and attempt to empty your mind. "
        "Reality slips away from you.\n", CYAN );
      ansi_tell_room( ENV( THISP ), sprintf( "%s stares off into space, "
      "%s eyes start to glaze over.\n", 
      THISP->query_name(), possessive( THISP ) ),
      CYAN, ({ THISP }) );
    
    shad = clone_object( TRANCESHAD );
    shad->sh_init( THISP, duration );
}
