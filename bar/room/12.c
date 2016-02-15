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
  "south": "/usr/taplash/bar/room/9",
  "east": "/usr/taplash/bar/room/14",
  "west": "/usr/taplash/bar/room/13"
]) );
    add( "exits", ([ "north" : "15" ]) );
    replace_program(); //makes the driver happy.
}