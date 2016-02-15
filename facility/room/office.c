#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Facility 31 Office Space" );
    set( "ansi_short", YEL "Facility 31 Office Space" );
    set( "day_long", "Beige everywhere. Beige computers, beige tables, "
      "beige mousepads, beige mice. There is a yellow tint even in "
      "the lights. A couple terminals are set up for data entry. "
      "The room is carpeted and the carpet is covered in coffee. "
      "It seems like the office aspect of this company has "
      "been forgotten for quite a long while. You can hear "
      "music coming from the north. The lobby is to the east." );
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", 
    ([
      "east"  :  FROOM  "lobby",
      "north" :  FROOM "intern",
      "west"  :        "@guard"        
    ]) );
    set( "descs",
    ([ 
      ({ "mouse", "mice"}) :
        "Clunky and old. Not an ergonomic design to be found "
        "anywhere.",
        
      ({ "mousepads", "mousepad" }) :
        "They used to be white. They are faded and stained. "
        "In the past they must have got a lot of use, so "
        "why is no one using them now?",
        
      ({ "computer", "terminal", "computers", "terminals" }) :
        "Faded beige Dell computers. They are hooked up to "
        "CRT monitors. The fans hum loudly.", 
    
      ({ "table", "tables"  }) : 
        "Some of these tables have deep grooves in them, "
        "spaced in the same manner as human fingers.",
 
      ({ "carpet", "stain", "stains" }) :
        "The stains all over the carpet are varying in colors "
        "and in size. Some of them still seem wet."
    ]) );    

    set( "reset_data" , 
    ([ 
      "fluff" : FMONS "fluffius",
      "sign"  : FOBJ  "warningsign"
    ]) );
}

mixed guard()
{
//This is a guard function to keep players
//from easily wandering down into the cellar.
//This monster will attack players but not
//other monsters from the area.
    object fluf = query( "fluff" );

    if( fluf && ENV( fluf ) == THISO &&
      object_name( THISP )[ 0..sizeof( FMONS ) -1 ] != FMONS )
    { 
      command( "say You aren't allowed in there!", fluf );
      fluf->attack_object( THISP );
      return 1; 
    }
    else
    return FROOM "ustair";
}	
