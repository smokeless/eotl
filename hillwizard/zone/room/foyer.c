#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Wartzhog Institute of Spellflingery's Main Foyer" );
    set( "ansi_short" , HIB "The Wartzhog Institute of Spellflingery's "
      "Main Foyer" NORM );
    set( "day_long" ,
      "Foyer is such a nice word.  This is really just a big room "
      "with a staircase, some hallways going off to the east and "
      "west, and a big south facing door to the outside.  While it "
      "is large, it really isn't very spectacular in any way.  The "
      "floors are dirty linoleum, and the walls are just plain old "
      "sheetrock with a thin, spotty coat of cheap paint.  In some "
      "places the paint doesn't even seem to match correctly.  While "
      "not extravagant, it does offer a warm, welcoming feeling."
    );
    set( "day_light" , 40 );
    set( "night_light", 25 );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "west"  : ZROOM "hallway2" ,
        "east"  : ZROOM "hallway3",
        "up"    : ZROOM "trophyroom",
        "south" : ZROOM "courtyard", //needs a door
      ])
    );
    set( "reset_data" ,
      ([
      ])
    );
    set( "descs" ,
      ([
        "starcase" : "*stairs",
        "stairway" : "*stairs",
        "stairs" : "This staircase runs along the back wall of the "
          "foyer.  It appears to lead to a small room above.",

        "walls" : "*wall",
        "wall" : "These walls are nothing special.  Sorry.",

        "floor" : ".... blah.",
      ])
    );
}
