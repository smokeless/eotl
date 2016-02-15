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
      "north"     : ROOM "city19",
      "west"      : ROOM "police",
      "east"      : ROOM "city22",
      "southwest" : ROOM "city24"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
