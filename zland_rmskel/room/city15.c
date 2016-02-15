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
      "north"     : ROOM "city09",
      "west"      : ROOM "city14", 
      "southwest" : ROOM "city18",
      "east"      : ROOM "hospital",
      "southeast" : ROOM "city19"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
