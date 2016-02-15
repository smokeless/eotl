#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Wavecrest Street" );
    set( "ansi_short", HIK "Wavecrest Street" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"     : ROOM "city20",
      "west"      : ROOM "city21",
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
