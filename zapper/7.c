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
  "north": "/usr/taplash/zapper/8",
  "northwest": "/usr/taplash/zapper/0",
  "northeast": "/usr/taplash/zapper/9"
]) );
    add( "exits", ([ "southeast" : "10" ]) );
    replace_program(); //makes the driver happy.
}