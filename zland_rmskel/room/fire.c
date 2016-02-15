#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Fire Department Parking Lot" );
    set( "ansi_short", HIK "Fire Department Parking Lot" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north" : ROOM "city17",
      "east"  : ROOM "police"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
