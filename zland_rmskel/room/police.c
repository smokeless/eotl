#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Police Department Parking Lot" );
    set( "ansi_short", HIK "Police Department Parking Lot" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "north"     : ROOM "city18",
      "east"      : ROOM "city21",
      "southeast" : ROOM "city25",
      "west"      : ROOM "fire"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
