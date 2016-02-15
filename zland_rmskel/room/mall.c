#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Mall Parking Lot" );
    set( "ansi_short", HIK "Mall Parking Lot" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"     : ROOM "city23",
      "east"      : ROOM "enter",
      "northeast" : ROOM "park"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
