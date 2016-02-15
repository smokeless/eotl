#include <town.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "An opening in the rock" );
    set( "ansi_short", YEL "An opening in the rock" NORM );
      
    set( "day_long", "You are standing outside an opening in a sheer "
      "rock wall. The top of the cave must be at least three hundred feet "
      "in the air. Bits of light filter down through the cave ceiling allowing "
      "you to see. To the northwest there is a tunnel entrance. To the southeast "
      "there is some sort of gate." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "northwest" : TROOM "en3",
      "southeast" : TROOM "gate1"
    ]) );
    
    set( "reset_data",  
    ([
      "t_sign" : TOBJ "t_sign",
    ]) );
    replace_program( RoomCode );
}
