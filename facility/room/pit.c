/*
The player should only see this room
if they jump into the pit. Jumping 
into the pit will cause them to die.
There is no other way into this pit.
*/

#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The bottom of a pit." ); 
    set( "ansi_short", HIK "The bottom of a pit." );   
    
    set( "day_long", "The air is thick, hot, humid, sickly with the "
      "smell of decay. The floor is a thick gelatinous blob of melted "
      "biological material in varying states of decay and liquidation. "
      "The hum is even louder down here, despite being away from the "
      "machines. Moving is difficult in this sludge, and the stink is "
      "over powering."
    );
    set( "day_light", 30 );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
   
    set( "reset_data",  
    ([
        "pipe"   : FOBJ "sewpipe"
    ]) );
    
    replace_program( RoomCode );
}
