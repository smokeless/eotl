    //Created with Taplash's room zapper!@#!
#include<bar.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "A narrow path");
    set("day_long", "This path winds down through "
      "rocky outcroppings in a leisurely manner. "
      "You can hear the sound of water running "
      "somewhere off in the distance. The air is "
      "damp and muggy against your face. " 
      "To the east is Facility 31, to the west "
      "the path continues.");
    
    set( "descs", ([
      ({ "rock", "rocks", "outcropping"}) : "Huge obsidian stones "
                                            "prevent you from leaving "
                                            "the path.",
    ]));

    set( "reset_data", ([]));
 
    set( "exits", ([ /* #1 */
  "east": ROOM "entry"
]) );
    add( "exits", ([ "west" : "1" ]) );
    replace_program(); //makes the driver happy.
}
