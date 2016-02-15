//This is a basic stick of incense.
//it's just a toy really.
//To do, add a function with a special lighter so you can light it
//add a burning incense shadow to the player if they are carrying it
//if the object is dropped in a room, add action smell incense to the
//room. add action telling the room that the incense smells.

inherit NewThingCode;
#include <facility.h>

void extra_create(){

    string stickcolor, stickscent;    

//let's give them a smell
    switch( random(4) ){
      case 0 : stickscent = "Cinnamon"; break;
      case 1 : stickscent = "Frankincense"; break;
      case 2 : stickscent = "Clove"; break;
      case 3 : stickscent = "Myrhh"; break;
    }

    set_ids( ({"incense", "stick" , "stick of incense"}) );
    add_id(stickscent);
//let's go ahead and give these sticks a few color options.
    switch( random(3) ){
      case 0 : stickcolor = RED; break;
      case 1 : stickcolor = GRN; break;
      case 2 : stickcolor = PRP; break;
    }

//non ansi players
    set_short( sprintf( "a Stick of %s Incense", stickscent));
//ansi players    
    set_ansi_short( sprintf( "%sa Stick of %s Incense", stickcolor,     stickscent ) );

    set_long( sprintf("This is a short stick of %s incense. "
              "Just having it nearby and unlit the smell is "
              "overpowering. You wish you had a proper way to "
              "light it.", stickscent)
    );



}


