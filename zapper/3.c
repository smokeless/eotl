    //Created with Taplash's room zapper!@#!
#include<city.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "Room");
    set("day_long", "skeletonroom!");
    set( "descs", ([]));

    set( "reset_data", ([]));
 
    set( "exits", ([ /* #1 */
  "west": "/usr/taplash/zapper/0"
]) );
    add( "exits", ([ "east" : "4" ]) );
    replace_program(); //makes the driver happy.
}