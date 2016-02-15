#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A dim hallway in the west wing of Wartzhog" );
    set( "ansi_short" , HIB "A dim hallway in the west wing of "
      "Wartzhog" NORM );
    set( "day_long" ,
       "This tall, slightly ominous hallway runs east-west throughout "
       "The Wartzhog Institute of Spellflingery.  The walls look to be "
       "made of dirt.  They are filty.  Apparently nobody bothers to "
       "clean up around here.  The hallway continues to run off to "
       "the west, and to the east you can see the hallway opens up "
       "into a large room."
    );
    set( "day_light" , 20 );
    set( "night_light", 18 );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "west"  : ZROOM "hallway1",
        "east"  : ZROOM "foyer",
      ])
    );
    set( "reset_data" ,
      ([
      ])
    );
    set( "descs" ,
      ([
      ])
    );
}
