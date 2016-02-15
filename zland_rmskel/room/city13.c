#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Oakwood Way" );
    set( "ansi_short", HIK "Oakwood Way" );
    
    set( "day_long", "Skeleton area." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northeast" : ROOM "city08",
      "southwest" : ROOM "city17"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
