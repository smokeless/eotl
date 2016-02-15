#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Edington Park" );
    set( "ansi_short", HIK "Edington Park" );
    
    set( "day_long", "Skeleton" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "northeast" : ROOM "city24",
      "northwest" : ROOM "city23",
      "southeast" : ROOM "enter",
      "southwest" : ROOM "mall"
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
