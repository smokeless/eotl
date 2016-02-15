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
      "north"  : ROOM "city05",
      "south"  : ROOM "hospital",
      "west"   : ROOM "city09",
      "east"   : ROOM "city11"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
