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
  "south": "/usr/taplash/bar/room/4"
]) );
    add( "exits", ([ "northeast" : "6" ]) );
    replace_program(); //makes the driver happy.
}