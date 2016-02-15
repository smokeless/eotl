#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Facility 31 Stairwell" );
    set( "ansi_short", YEL "Facility 31 Stairwell" );
    
    set( "day_long", "The stairwell is made out of huge cinder blocks. "
      "The lighting is dim and the whole area is very humid. There "
      "is a horrible smell filling the air. A worn rusty banister "
      "disappears down into the depths of the facility." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
    set( NoWanderRoomP, 1 );
    
    add( "exits", 
    ([
      "down" : FROOM "dstair.c",
      "east" : FROOM "office.c"      
    ]) );
    
    set( "descs",
    ([ 
      ({ "cinder", "blocks", "cinderblocks", "cinder blocks" }) :
          "Stained, cracked, and worn. It is amazing this "
          "place is still standing.", 
      
      ({ "stairs", "stair", "banister"  }) : 
           "The banister is worn smooth from having hands run across it for "
           "however long it has been here. It disappears down into the "
           "darkness below.",
    ]) );    
}
