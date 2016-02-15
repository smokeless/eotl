#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Saint James Street" );
    set( "ansi_short", HIK "Saint James Street" );
    
    set( "day_long", "Skeleton area." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"  : ROOM "city04",
      "south"  : ROOM "city15",
      "west"   : ROOM "city08",
      "east"   : ROOM "city10"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
