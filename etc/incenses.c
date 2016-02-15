//This is a basic stick of incense.
//it's just a toy really.

//To do, add a function with a special lighter so you can light it
//add a burning incense shadow to the player if they are carrying it
//if the object is dropped in a room, add action smell incense to the
//room. add action telling the room that the incense smells.
//fix broken stick scent, get caps.

inherit NewThingCode;
#include<facility.h>;

//let's give them a smell
void extra_create(){
    string stickscent;    
    switch( random( 4 ) )
    {
      case 0 : stickscent = "Cinnamon "; break;
      case 1 : stickscent = "Frankincense "; break;
      case 2 : stickscent = "Clove "; break;
      case 3 : stickscent = "Myrhh "; break;
    }




    set_ids( ({ "incense", "stick" , "stick of incense" +stickscent }) );


//let's go ahead and give these sticks a few color options.
    string stickcolor;
    switch( random(3) ){
      case 0 : stickcolor = RED; break;
      case 1 : stickcolor = GRN; break;
      case 2 : stickcolor = PRP; break;
    }


    set("short",stickcolor + "a Stick of " +stickscent+ "Incense" 
               + NORM);
    set("long","This is a short stick of " +stickscent+ "incense. "
               "Just having it nearby and unlit the smell is "
               "overpowering. You wish you had a proper way to "
               "light it."
    );

}
void extra_init()
{
    add_action( "smell", "smell" );
}

int smell( string strarg )
{ 
  
  object death = find_player( strarg );
  if( !stringp( strarg ) )
    {
      return notify_fail( query_verb()  + " what?\n" );
    }
  switch( random( 6 ) )
  {
    case 0 : death->DeathSequence( death, "fell down the stairs" ); break;
    case 1 : death->DeathSequence( death, "bumped into a door" ); break;
    case 2 : death->DeathSequence( death, "can't take the shame" ); break;
    case 3 : death->DeathSequence( death, "couldn't reach a beer" ); break;
    case 4 : death->DeathSequence( death, "isn't in Kansas anymore" ); break;
    case 5 : death->DeathSequence( death, "got stuck in some asphalt" ); break;
  }
  return 1;
}

    


