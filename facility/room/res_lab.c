#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short",  "Facility 31 Research Laboratory" );
    set( "ansi_short", HIK "Facility 31 Research Laboratory" );
    set( "day_long", "Sterile stainless steel tables and counters "
      "are set out all over this room. There are jars full of "
      "preserved biological parts stacked on the top shelves "
      "collecting dust. A couple workstations sit in the corner of "
      "the room. Near the computers "
      "there are stacks of notebooks. The whole area is very crisp and "
      "cold. To the south you can see the lobby." );
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "descs", 
    ([
      ({ "table", "tables", "counter", "counters" }) : 
        "The steel is dull, but well polished and very clean. They seem to be "
        "prepped and ready for the next experiment.", 
      ({ "jar", "jars", "parts" }) :
        "The jars are dusty, but you can make out some of the "
        "contents. An Ogre fetus floats in a larger jar its "
        "eyes lazily listing off to the left. In the other jars "
        "various fingers, tentacles, and organs list calmly in "
        "the embalming fluid.", 
      ({ "workstation", "workstations", "computers", "computer" }) :
        "All the computer screens are powered off. The computers "
        "themselves are humming away. You can hear drives spin up and "
        "fans blowing.",
      ({ "notebooks", "notebook", "stacks", "stack" }) :
        "Old and dusty, you flip through them briefly. They are written in "
        "pictogram of some sort. It seems impossible to make heads or tails of "
        "what they are trying to convey. One particular symbol is more common "
        "than the others, a large tentacle like thing.",
      ({ "shelf", "shelves" }) :
        "There are a variety of odds and ends piled on these shelves. "
        "Junk food wrappers and other useless miscellaneous clutter."
    ]) );
    
    set( "reset_data",  
    ([
      "rifradbadgem" : FMONS "rifrad", 
      "set" :          FOBJ "chemistry"
    ]) );
    set( "exits",
    ([
      "south" : FROOM "lobby"
    ]) );    
}
