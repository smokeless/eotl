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
  "west": "/usr/taplash/bar/room/19"
]) );
    add( "exits", ([ "north" : "21" ]) );
    replace_program(); //makes the driver happy.
}