#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Saint James Street" );
    set( "ansi_short", HIK "Saint James Street" );
    
    set( "day_long", "Skeleton area. Crossroads." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northeast" : ROOM "city03",
      "southeast" : ROOM "city14",
      "northwest" : ROOM "city02",
      "southwest" : ROOM "city13",
      "west"      : ROOM "city07",
      "east"      : ROOM "city09"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
