#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Hofner Street" );
    set( "ansi_short", HIK "Hofner Street" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northwest" : ROOM "city15",
      "east"      : ROOM "city20",
      "south"     : ROOM "city21"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
