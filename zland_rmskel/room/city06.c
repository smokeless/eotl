#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Bookman Street" );
    set( "ansi_short", HIK "Bookman Street" );
    
    set( "day_long", "city06" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "west"  : ROOM "city05",
      "south" : ROOM "city11"      
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
