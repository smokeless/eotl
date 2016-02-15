#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Bookman Street" );
    set( "ansi_short", HIK "Bookman Street" );
    
    set( "day_long", "city02" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "southeast" : ROOM "city08",
      "east"      : ROOM "city03",
      "west"      : ROOM "city01"      
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
