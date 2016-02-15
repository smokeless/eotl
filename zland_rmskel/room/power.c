#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Power Plant and Water Works Parking Lot" );
    set( "ansi_short", HIK "Power Plant and Water Works Parking Lot" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "southwest" : ROOM "city27"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
