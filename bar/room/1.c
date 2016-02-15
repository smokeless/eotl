    //Created with Taplash's room zapper!@#!
#include<bar.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "A narrow winding path");
    set("day_long", "The path continues to head down into "
      "the earth. The air is becoming more crisp. "
      "The sounds of your footsteps echo through the "
      "gargantuan cavern. Huge lava rocks push up through "
      "the ground. You can see the path continuing to the "
      "east and narrowing to the northeast.");
    set( "descs", ([
      ({ "cavern", "gargantuan cavern"}) : "You are so deep underground "
                                           "that you have no idea of your "
                                           "location relative to Eternal.",
      ({"rocks", "lava rocks", "rock" }) : "The way these are forced through "
                                           "the ground indicates a lot of "
                                           "tectonic movement."
    ]));

    set( "reset_data", ([]));
 
    set( "exits", ([ /* #1 */
     "east": "0",
]) );
    add( "exits", ([ "northeast" : "2" ]) );
    replace_program(); //makes the driver happy.
}
