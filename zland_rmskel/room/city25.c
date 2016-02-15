#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Park Drive" );
    set( "ansi_short", HIK "Park Drive" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northwest" : ROOM "police",
      "south"     : ROOM "city27",
      "east"      : ROOM "city26",
      "west"      : ROOM "city24"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
