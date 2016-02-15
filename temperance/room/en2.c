#include <town.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Inside a small tunnel" );
    set( "ansi_short", YEL "Inside a small tunnel" NORM );
      
    set( "day_long", "The tunnel continues downwards at an extremely "
      "steep angle. It is incredibly difficult to maintain your footing "
      "on the cold slippery rock. Small sharp pieces of stone stick "
      "out from the walls catching on your skin and tearing at it. "
      "You can see light to the north. The cave continues to the southeast." );
    
    set( "day_light", DARK );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "north" : TROOM "en1",
      "southeast" : TROOM "en3"
    ]) );
    
    replace_program( RoomCode );
}
