#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Bookman Street" );
    set( "ansi_short", HIK "Bookman Street" );
    
    set( "day_long", "city04" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "south" : ROOM "city09",
      "east"  : ROOM "city05",
      "west"  : ROOM "city03"      
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
