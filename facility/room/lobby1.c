#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Lobby of Facility 31" );
    set( "ansi_short", YEL "The Lobby of Facility 31" );
    
    set( "day_long", "The tile floor is cracked and ruptured. "
      "There are blood stains all over it. The area hums with "
      "energy. The benches have been destroyed, and the "
      "magazines ripped to shreds. The reception desk has "
      "been reduced to shreds. To the north you can see the " 
      "laboratory. To the west there is some office space. "
      "To the east you can see the museum. From the south a "
      "cool breeze blows in." );
    
    set( "day_light", PART_LIT  );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "north" : FROOM "res_lab1",
      "west"  : FROOM "office1",
      "east"  : FROOM "museum1",
      "south" : FROOM "outside",
    ]) );
    
    set( "reset_data" , 
    ([ 
      "mon"  : FMONS "posres",
      "mon1" : FMONS "posres",
      "mon2" : FMONS "posres",
      "mon3" : FMONS "creature"
    ]) );
   
    set( "descs",
    ([ 
      ({ "magazine", "magazines", "shreds" }) :
        "They are scattered all around the room like confetti. "
        "There is blood clinging to every shred. Looks like that "
        "sheen on magazine paper keeps too much liquid from absorbing. "
        "Who knew?",
        
      ({ "bench", "benches" })                :
        "What used to be comfortable looking benches are just "
        "pieces and splinters. It looks like they were thrown up "
        "into the air and came crashing down to the ground.",
 
      ({ "floor", "floors", "tile"  })        :
        "Chunks of tile covered in blood are scattered all around. "
        "It looks like something exploded up from below the floor. "
        "Something huge."
    ]) );
}

