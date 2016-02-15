#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Outside of Facility 31" ); 
    set( "ansi_short" , HIK "Outside of Facility 31" );   
    
    set( "day_long" , "The interior of this cavern is dimly lit by "
      "some sort of flourescent moss. You can hear water trickling "
      "down through the cracks in the rocks above you. Steps lead "
      "north into some sort of building carved out of the rock. "
      "To the south there is large barricade constructed of boulders "
      "and mortar. To the east you can make out a portion of the " 
      "Eternal sewer system.");
    
    set( "day_light", 30 );
    set( NoWanderRoomP, 1 );
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", 
    ([
      "north" : "@phased"        
    ]) );
      
    set( "descs",
    ([ 
      ({ "barricade", "mortar", "boulder", "boulders" }) : 
        "The barricade looks hastily constructed, "
        "but very sturdy. The boulders must weigh "
        "thousands of pounds.",

      ({ "building", "facility", "door", "doors" }) :
        "The outside of the facility is not much "
        "to look at. Smooth rock gives away to "
        "the entryway, which appears to have "
        "no means of being shut.", 
 
      ({ "cavern", "interior", "moss", "walls", "wall", "rock", "rocks" }) :
        "The rocks that compose this cavern seem to "
        "be constantly wet. The moss that grows on "
        "them slightly illuminates the area allowing "
        "you to see.",
      
      ({ "step", "steps" }) :
        "The steps get progressively smaller as they "
        "approach the door. The stone is smooth from "
        "from years of water running across it."
    ]) );
}
    
mixed phased()
{
//This function checks to see if someone has completed
//the first phase of this area, and moves them to the
//appropriate phase on entry.
    if( THISP->query_prop_value( "facility_phase" ) == 1 )
      return FROOM "lobby1.c";
    else
      return FROOM "lobby.c";
}
