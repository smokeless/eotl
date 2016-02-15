#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Oakwood Circle" );
    set( "ansi_short", HIK "Oakwood Circle" );
    
    set( "day_long", "Skeleton area. South is police." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northeast" : ROOM "city15",
      "northwest" : ROOM "city14",
      "south"     : ROOM "police",
      "west"      : ROOM "city17"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
