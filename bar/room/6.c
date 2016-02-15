    //Created with Taplash's room zapper!@#!
#include<bar.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "Room");
    set("day_long", "skeletonroom!");
    set( "descs", ([]));

    set( "reset_data", ([]));
 
    set( "exits", ([ /* #1 */
  "southwest": "/usr/taplash/bar/room/5",
  "east": "/usr/taplash/bar/room/8",
  "west": "/usr/taplash/bar/room/7"
]) );
    add( "exits", ([ "north" : "9" ]) );
    replace_program(); //makes the driver happy.
}