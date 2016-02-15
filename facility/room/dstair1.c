#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Facility 31 Stairwell" );
    set( "ansi_short", YEL "Facility 31 Stairwell" NORM );
    
    set( "day_long", "The stairwell is made out of huge cinder blocks. "
      "The lighting is dim and the whole area is very humid. There "
      "is a horrible smell filling the air. A worn rusty banister "
      "disappears up into the light of the facility. There used to be "
      "a door on the wall, but it has been exploded outwards from the "
      "inside! There is a cold breeze coming from where the door used "
      "to be." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
    
    add( "exits", 
    ([
      "up"   : FROOM "ustair1.c",
      "east" : FROOM "basement1.c"      
    ]) );
    
    set( "descs",
    ([ 
      ({ "cinder", "blocks", "cinderblocks", "cinder blocks" }) :
        "Stained, cracked, and worn. It is amazing this "
        "place is still standing.", 
      ({ "stairs", "stair", "banister"  }) : 
        "The banister is worn smooth from having hands run across it for "
        "however long it has been here. It disappears up into the "
        "bright lights of the office. The stairs look like they go "
        "up forever. You are amazed you made it down."
    ]) );    

    set( "reset_data" , 
    ([ 
        
    ]) );
}
