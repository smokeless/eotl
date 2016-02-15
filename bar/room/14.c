//Created with Taplash's room zapper!@#!
#include<bar.h>
inherit RoomPlusCode;
void extra_create()
{
    set("short", "Room");
    set("day_long", "skeletonroom!");
    set( "descs", ([]));

    set( "reset_data", ([]));
 
    add( "exits", ([
       "west" : "/usr/taplash/bar/room/12" ]) );
    replace_program(); //makes the driver happy.
}