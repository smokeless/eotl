#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    int time = random( 400 ) + 1;
    
    set( "short", "The Facility 31 Intern Room" );
    set( "ansi_short", YEL "The Facility 31 Intern Room" NORM );
    
    set( "day_long", "It's a mess in here. There are body parts all "
      "over the place. Blood coats what is left of a shredded cots. "
      "The posters are still intact. Though they have been covered with "
      "some sort of ink. A single Bose speaker lays on the ground, its " 
      "grill cloth has been ripped off. The actual speaker is missing. " 
      "To the south you can see some office space." );      
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "south" : FROOM "office1"
    ]) );
    
    set( "descs", 
    ([
      ({ "poster", "posters" })           : 
        "There is black ink all over these posters. Maybe it's an improvement? "
        "Who likes motivation anyways?",
      ({ "speaker", "speakers" })         : 
        "The speaker case is full of tiny gooey black ovals. They "
        "could be eggs. You certaintly aren't sticking your hand "
        "inside to find out.",
      ({ "cot", "cots" })                 : 
        "There is an awful lot of blood on these cots. "
        "The smell probably makes it very difficult to get "
        "comfortable on them.",
      ({ "body", "body parts", "parts" }) :
        "Mainly hands and feet. Not a single torso or head to be "
        "seen. Either something walked off with them, or they "
        "walked off on their own. With no feet...",
      "ink"                               :
      "That is definitely ink. It looks like something an octopus would "
      "spray.", 
    ]) );
    
    set( "reset_data",  
    ([
      "intern" : FMONS "darkness"		 
    ]) );  

    call_out( "shake", time );
}

int shake()
{
    int go = random( 300 );
    tell_room( THISO, "A loud roar unlike anything you have ever heard "
      "echoes through the room. The walls shake.\n", ({ }) );
    call_out( "shake", go );
}
