#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Saint James Street" );
    set( "ansi_short", HIK "Dead End" );
    
    set( "day_long", "Skeleton area." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"  : ROOM "city07"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
