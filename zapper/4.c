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
  "west": "/usr/taplash/zapper/3"
]) );
    add( "exits", ([ "southeast" : "5" ]) );
    replace_program(); //makes the driver happy.
}