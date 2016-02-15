#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A dim hallway in the east wing of Wartzhog" );
    set( "ansi_short" , HIB "A dim hallway in the east wing of "
      "Wartzhog" NORM );
    set( "day_long" ,
       "This tall, slightly ominous hallway runs east-west throughout "
       "The Wartzhog Institute of Spellflingery.  The walls look to be "
       "made of dirt.  They are filty.  Apparently nobody bothers to "
       "clean up around here.  The hallway terminates here to the east, "
       "and runs back west toward the rest of the academy.  There are "
       "large archways on the north and south walls, which lead off "
       "large rooms."
    );
    set( "day_light" , 20 );
    set( "night_light", 18 );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "north" : ZROOM "profroom" ,
        "south" : ZROOM "skillroom",
        "west"  : ZROOM "hallway3",
      ])
    );
    set( "reset_data" ,
      ([
      ])
    );
    set( "descs" ,
      ([
        "archway"  : "*archways",
        "arch"     : "*archways",
        "arches"   : "*archways",
        "archways" : "These large arches seem to be made of dirt.  They "
          "probably are not dirt, but they sure look that way.",
      ])
    );
}
