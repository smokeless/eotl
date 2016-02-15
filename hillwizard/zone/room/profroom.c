// This room will serve as the Proficiency Training Hall for Hill Wizards

#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Wartzhog Institute of Spellflingery Weapons Room" );
    set( "ansi_short" , HIB "The Wartzhog Institute of Spellflingery "
      "Weapons Room" NORM );
    set( "day_long" ,
      "This room has pictures of weapons all over the walls.  It seems "
      "they couldn't afford the real things.  The floor is padded, "
      "albeit lightly, and there is sufficient lighting hanging over"
      "head.  This is a no frills room, but from the smell of dried "
      "sweat, it is plain that hard, true work gets done in here."
    );
    set( "day_light" , 40 );
    set( "night_light", 25 );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "south" : ZROOM "hallway4" ,
      ])
    );
    set( "reset_data" ,
      ([
    "profthing" : GOBJ "ptrainer",
        "proftrainer" : ZMON "chester",
      ])
    );
    set( "descs" ,
      ([
        "walls" : "*picture",
        "wall" : "*picture",
        "pictures" : "*picture",
        "picture" : "The walls are a simple pale blue, but you can barely "
          "see any of the walls for all these weapon posters plastered up "
          "everywhere.  From common stuff like swords and spears to totally "
          "outlandish things you couldn't even begin to describe... "
          "Hillbillies love their weapons.  Muricuh!",
        "floor" : "*ground",
        "mat" : "*ground",
        "ground" : "The mat on the floor is a light blue, and is just "
          "squishy enough to soften a fall.",
        "light" : "*lights",
        "lights" : "Just a few dangling lightbulbs.  Nothing cool.",
      ])
    );
}
