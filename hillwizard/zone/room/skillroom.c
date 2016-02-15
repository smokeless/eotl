// This room will serve as the Skill Training Hall for Hill Wizards

#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Wartzhog Institute of Spellflingery Lecture Hall" );
    set( "ansi_short" , HIB "The Wartzhog Institute of Spellflingery "
      "Lecture Hall" NORM );
    set( "day_long" ,
      "A classroom is a classroom is a classroom, right?  Well, this is a "
      "quite nice room full of small chairs with desks attached to them, "
      "with a more substantial desk up front for the instructor to use.  "
      "The room is sparse, with nothing adorning the walls, and simple "
      "fluorescent lighting overhead.  At the front is a small blackboard "
      "where the Head Flinger can impart knowledge unto other Hill "
      "Wizards."
    );
    set( "day_light" , SUNLIGHT );
    set( "night_light", SUNLIGHT );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "north" : ZROOM "hallway4" ,
      ])
    );
    set( "reset_data" ,
      ([
      "guildobj" : GOBJ "strainer",
        "skilltrainer" : ZMON "clara",
      ])
    );
    set( "descs" ,
      ([
        "desk" : "*desks",
        "desks" : "These small desks are pretty much standard issue for "
          "schools around the world.  Its a simple chair, with a small "
          "wooden desk wrapping around on the right hand side.  Because "
          "fuck lefties, apparently.",
        "light" : "*lights",
        "lights" : "The overhead lights are fluorescent tubes in fairly "
          "cheap fixtures.  They get the job done, however.",
        "blackboard" : "This blackboard looks quite old and beat up, like "
          "someone found it in the landfill and just decided it would "
          "still work.  Of course, there is no chalk.  There is never any "
          "chalk.",
      ])
    );
}
