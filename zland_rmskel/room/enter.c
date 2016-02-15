#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A Barricade" );
    set( "ansi_short", HIK "A Barricade" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"     : ROOM "city27",
      "northwest" : ROOM "park",
      "west"      : ROOM "mall"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
