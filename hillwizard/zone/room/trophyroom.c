#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Hill Wizard Treasure Hall" );
    set( "ansi_short" , HIB "The Hill Wizard Treasure Hall" NORM );
    set( "day_long" ,
      "Well, Hill Wizards might call it a treasure hall... but in "
      "reality, this is just a grungey old room full of crap.  There "
      "is so much crap in here that you can't even tell what is what.  "
      "The only remotely accessable thing in here is a large car-hood "
      "barbeque.  And even that assumes you're willing to trudge "
      "through all the garbage on the floor between here and there."
      "There are windows in this room, but they are so grime covered "
      "that they barely let any light in.  Luckily, a dangling light "
      "bulb is lit up on the ceiling.  You feel a little dirty just "
      "being in here."
    );
    set( "day_light" , PART_LIT );
    set( "night_light", PART_LIT );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "down" : ZROOM "foyer" ,
      ])
    );
    set( "reset_data" ,
      ([
//      "case" : ZOBJ "trophycase",
        "battlepig" : ZMON "wartz",
      ])
    );
    set( "descs" ,
      ([
        "floor" : "You can't see the floor through all this garbage.",
        "garbage" : "You... don't even know where to begin.  It's just "
          "a sea of nothing worth saving.",
        "light" : "*lightbulb",
        "lightbulb" : "It's just a boring old lightbulb, covered in dust.",
        "window" : "*windows",
        "windows" : "Is it really a window if its so dirty that you can't "
          "see through it?",
      ])
    );
}
