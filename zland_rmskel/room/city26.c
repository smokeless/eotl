#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Surrey Bridge" );
    set( "ansi_short", HIK "Surrey Bridge" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "west" : ROOM "city25"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
