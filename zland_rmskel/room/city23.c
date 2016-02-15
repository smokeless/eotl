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
      "south"     : ROOM "mall",
      "east"      : ROOM "city24",
      "southeast" : ROOM "park"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
