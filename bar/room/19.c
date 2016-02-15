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
  "up": "/usr/taplash/bar/room/18"
]) );
    add( "exits", ([ "east" : "20" ]) );
    replace_program(); //makes the driver happy.
}