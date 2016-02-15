#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Outside Saint Constantine" );
    set( "ansi_short", HIK "Outside Saint Constantine" );
    
    set( "day_long", "Hospital." );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"     : ROOM "city10",
      "west"      : ROOM "city15", 
      "east"      : ROOM "city16",
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
