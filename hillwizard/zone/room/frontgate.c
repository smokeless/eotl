// This is the room where people will join the guild.
// Only let them join if Clyde is alive

#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Just outside the front gate of The "
      "Wartzhog Institute of Spellflingery" );
    set( "ansi_short" , HIK "Just outside the front gate of "
      "The Wartzhog Institute of Spellflingery" NORM );
    set( "day_long" ,
      "You are standing directly outside the front gate of the wonderous "
      "Wartzhog Institute of Spellflingery.  People round here are pretty "
      "friendly, but they don't take kindly to tresspassing.  This gate is "
      "to keep the undespirable and the unknown elements on the outside, "
      "and create a safe space for learning about spellflingery on the "
      "inside.  The gate is nothing special, just a black wrought iron "
      "barrier.  You could probably climb over it with relative ease, "
      "but the Hill Wizards probably wouldn't much appreciate that."
    );
    set( "day_light" , 100 );
    set( "night_light", 30 );
    set( OutsideP, 1 );
    set( "exits" , 
      ([
        "north" : "@enter_compound", 
        "south" : ZROOM "outside",
      ])
    );
    set( "reset_data" ,
      ([
       "guild" : GOBJ "no_train",
        "entryguard" : ZMON "clyde",
        "notresspassing" : ZOBJ "gatesign",
      ])
    );
    set( "descs" ,
      ([
        "gate" : "The wrought iron gate is nothing particularly special, but it "
          "does look sturdy.  If it was unprotected, you might be able to climb "
          "it.",
        "wartzhog" : "*building",
        "building" : "Before you lies The Wartzhog Institute of Spellflingery.  "
          "You cannot imagine why it was designed to resemble a trailer...",
      ])
    );
}

void extra_init()
{
   add_action( "climb_it", "climb" );
}

mixed enter_compound()
{
    object o = present_clone( ZMON "clyde" );

    if( THISP->query_specialization() == "hillwizard" )
    { 
      if( !o )
      {
        tell_player( THISP, "You bang your head against the gate.\nDamn it, "
          "where the hell is Clyde?  HE HAS ONE JOB TO DO!!!" );
        tell_room( ENV( THISP ), sprintf( "%s bangs %s head against "
          "the gate.\n", THISP->query_name(), possessive( THISP ) ) );
        THISP->take_damage( 1 + random( 10 ), 0, "blunt", THISO );
        return 1;
      }

      tell_player( THISP, "Clyde opens the gate for you." );
      tell_room( ENV( o ), sprintf( "Clyde opens the gate for %s.\n",
        THISP->query_name() ), ({ THISP }) );
      return ZROOM "courtyard"; 
    }

    if( !o )
    {
      tell_player( THISP, "You bang your head on the gate.\n"
        "Apparently it doesn't open magically.\nHow disappointing." );
      tell_room( ENV( THISP ), sprintf( "%s bangs %s head against the gate.\n",
        THISP->query_name(), possessive( THISP ) ), ({ THISP }) );
      THISP->take_damage( 1 + random( 10 ), 0, "blunt", THISO );
      return 1;
    }

    tell_player( THISP, "Clyde blocks your path." );
    tell_room( ENV( THISP ), sprintf( "Clyde blocks %s's path.\n",
      THISP->query_name() ), ({ THISP }) );
    command( "say Ya dun't berlong here, pal.  Best get ta steppin'.", o );
    return 1;
}

mixed climb_it( string arg )
{
    if( arg != "gate" )
      return 0;

    object o = present_clone( ZMON "clyde" );

    if( o && THISP->query_specialization() != "hillwizard" )
    {
      tell_player( THISP, "Clyde grabs you and pulls you down off "
        "the gate." );
      tell_room( ENV( THISP ), sprintf( "Clyde grabs %s and pulls %s "
        "down off the gate.\n", THISP->query_name(), objective( THISP ) ),
        ({ THISP }) );
      command( "say Buddy, I's had just 'bout 'nougha yer type "
        "round here.", o );
      command( "crack", o );
      o->attack_object( THISP );
      return 1;
    }

    if( random( THISP->query_skill( "climb" ) ) <= random( 20 ) )
    {
      tell_player( THISP, "You try to climb the gate, but slip and fall!" );
      tell_room( ENV( THISP ), sprintf( "%s tries to climb the gate, "
        "but slips and falls!\n", THISP->query_name() ), ({ THISP }) );
      THISP->take_damage( 1 + random( 10 ), 0, "blunt", THISO );
      return 1;
    }

    tell_player( THISP, "You climb up over the gate and into the Hill "
      "Wizard compound." );
    THISP->move_player( "climbs over the gate to the north", 
      ZROOM "courtyard", 1 );
    return 1;
}
