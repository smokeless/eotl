#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short",  "Facility 31 Research Laboratory" );
    set( "ansi_short", HIK "Facility 31 Research Laboratory" );
    
    set( "day_long", "The tables in this room have been been twisted into "
      "tight spirals by something of immense strength. What was once "
      "lab equipment is now just debris scattered across the floor. "
      "The floor itself is sticky and makes squelching sounds as you walk on it. "
      "In the center of the room there is a pile of entrails arranged to "
      "spell out: \"Warning: It is free.\" To the south you can see the lobby." );
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "descs", 
    ([
      ({ "table", "tables", "counter", "counters" }) : 
        "They stand on end pointing up towards the ceiling. They are arranged like "
        "some sort of megalithic monument. ",
      ({ "liver", "entrails" }) :
        "Whoever wrote this was in bad need of a pen. You note they also must have "
        "been a masochist, they didn't use an apostrophe. The entrails show no signs "
        "of decay.",
      ({ "equipment", "debris" }) :
        "Pieces of scientific equipment. A bit of an incubator here, a bit of "
        "a computer there, and glass everywhere. The warranty probably doesn't "
        "cover this situation.",
      "floor" : "There are puddles of a brown viscous substance on the ground. "
        "Maybe someone spilled a Coke?"      
    ]) );
    
    set( "reset_data",  
    ([
      "chicken" : FMONS "chicken" 
    ]) );
    
    set( "exits",
    ([
      "south" : FROOM "lobby1"
    ]) );   
}
