#include <town.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Temperance City Gates" );
    set( "ansi_short", YEL "Temperance City Gates" NORM );
      
    set( "day_long", "Towering above your head over fifty feet tall are the gates to "
      "Temperance City. They have been fitted into a solid wood fence that extends "
      "to the north and the south blocking all paths around the city. The top of the "
      "gates are carved into extremely sharp looking points. What used to be a population "
      "sign attached to the front is now just a bullet hole ridden mess." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "east"      : TROOM "@check",
      "northwest" : TROOM "en4"
    ]) );
    
    set( "reset_data",  
    ([
      "guard" : TMON "guard",
      "guard" : TMON "guard"
    ]) );
}
