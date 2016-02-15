#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Oakwood Circle" );
    set( "ansi_short", HIK "Oakwood Circle" );
    
    set( "day_long", "Skeleton area." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northwest" : ROOM "city08",
      "southeast" : ROOM "city18",
      "east"      : ROOM "city15"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
