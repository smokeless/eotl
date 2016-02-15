/**
***  Force Confusion causes a non-combatant monster to
***  defend a Jedi.
***  5-25-05 
**/

inherit AttackCommand;
inherit AnsiTellCode;
#include <ansi.h>
#include "Jedi.h"
#define FORCEPOWER   25
#define FORCESTRENGTH  200

void extra_create()
{
    set( "name", "force confusion" );
    set( "help",
      "Spell : Force Confusion\n"
      "Cost  : " +FORCEPOWER+ " Force Power\n"
      "Usage : force confuse [target optional]\n"
      "Type  : Combat\n"
      "Minimum : " +FORCESTRENGTH+ " Force Strength\n"
      "\n"
      "     Force Confusion leaves an opponent disoriented, often "
      "resulting in unpredictable behavior.  A confused combatant "
      "may mistakenly strike out at other objects in the area, "
      "unexpectedly flee, or completely forget your presence.\n"
       );
    set( "function", "do_confuse" );
    set( "action", "force" );
    set( "verb", "confuse" );
    set( "usage", "force confuse [target optional]" );
    set( "private", 1 );
    set( "no_rest", 1 );
    set( "no_combat", 0 );
    set( "guild", "jedi" );
    set( "class", "combat" );
//    set( "min", ([ "stats" : ([ "wil" : 40 ]) ]) );
//    set( "cost", ([ "mana" : 30 ]) );
    set( "time", ([ "skills"    : ({ "force confusion", 2, 1 }) ]) );
    set( "success", ([ "skills" : ({ "force confusion", 1, 1 }) ])  );
    set( "offchance", 10 );
} 

status okattempt( object victim )
{
    if( !::okattempt( victim ) ) return 0;

    if( THISP->query_force_power() < FORCEPOWER )
        return( write( "You lack sufficient power in the Force.\n" ), 0 );

    if( THISP->query_max_force_power() < FORCESTRENGTH )
        return( write( "You lack sufficient strength in the Force.\n" ), 0 );

    if( ENV( THISP )->query( NoMagicP ) )
        return( write( "The Force cannot be manipulated here.\n" ), 0 );

    if( THISP->test_prop( CastingP ) )
        return( write( "You are directing the Force elsewhere.\n" ), 0 );

    if( victim->query_halluc_shad() )
        return( write( "That target is already confused.\n" ), 0 );

    return 1;
}

void do_confuse( object victim )
{
    string vname, myname, hand;
    object shad;
    int align = THISP->query_alignment();
    vname = victim->query_name();
    myname = THISP->query_name();
    hand = THISP->query_hand_name();

    THISP->add_force_power( -FORCEPOWER );

    ansi_tell( THISP, sprintf( "You wave your %s toward %s, attempting "
        "to muddle %s mind.", hand, vname, possessive( victim ) ), YELLOW );
    ansi_tell( victim, sprintf( "%s waves %s %s toward you.",
        CAP( myname ), possessive( THISP ), hand ), YELLOW );
    ansi_tell_room( ENV( THISP ), sprintf( "%s waves %s %s toward %s.",
        CAP( myname ), possessive( THISP ), hand, vname ),
        YELLOW, ({THISP, victim }) );

    if( success_roll() <= 0 )
    {
        ansi_tell( THISP, "Your attempt to manipulate the Force fails.",
            LOW_YELLOW );
        return;
    }

    if( victim->query_race() == "Squid" ||    // like jaba teh hutt!
        victim->query_race() == "Android" ||
        victim->query( UndeadP ) ||
        victim->query_resistance( "psionic" ) > 60 ||
        victim->query_stat( "int" ) > victim->query_stat_total() / 6 )
    {
        ansi_tell( THISP, sprintf( "%s's mind is impervious to your call.",
            CAP( vname ) ), LOW_YELLOW );
        ansi_tell( victim, "You feel a mental probe slide harmlessly "
            "away from your mind.", LOW_YELLOW );
        return;
    }

    shad = clone_object( GOBJ "halluc_shad" );
    shad->sh_init( victim, calc( "time", THISP ) );
    return;
}
