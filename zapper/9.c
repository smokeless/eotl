//Created with Taplash's room zapper!@#!
#include<city.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "Room");
    set("day_long", "skeletonroom!");
    set( "descs", ([]));

    set( "reset_data", ([]));
 
    add( "exits", ([
       "southwest" : "/usr/taplash/zapper/7" ]) );
    replace_program(); //makes the driver happy.
}