#include <zland.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Saint James and Bookman" );
    set( "ansi_short", HIK "Saint James and Bookman" );
    
    set( "day_long", "city01" );
    
    set( "day_light", 30 );
    
    set( OutsideP, 1 );
    set( NoTeleportP, 1 );

    set( "descs", 
    ([ 
    ]) );
    
    add( "exits", 
    ([
      "south" : ROOM "city07",
      "east"  : ROOM "city02"      
    ]) );
    
    set( "reset_data",  
    ([
	]) );
}
