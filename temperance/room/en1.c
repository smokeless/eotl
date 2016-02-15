#include <town.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Beyond the barricade" );
    set( "ansi_short", YEL "Beyond the barricade" NORM );
      
    set( "day_long", "You are standing in a flat clear area. The cave ceiling "
      "is extremely high above you, but slopes down quickly to the mouth of "
      "a small southern tunnel. The a barricade you climbed over is to the north." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "south" : TROOM "en2"
    ]) );
    
    set( "descs", 
    ([
      "ceiling"   : "The entire ceiling swoops downwards and narrows "
                    "at the point of the tunnel entrance.",
      "tunnel"    : "The mouth of the tunnel is completely dark. "
                    "it is roughly five foot tall and three feet "
                    "wide.",
      "barricade" : "This barricade is very well constructed. Someone "
                    "has painted \"Beware what evil lurks beyond!\" on "
                    "the front of it."
    ]) );
    replace_program( RoomCode );
}
