#include <ranger.h>
inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A Great Room" ); 
    set( "ansi_short", GRN "A Great Room" );   
    
    set( "day_long", "This room is massive. "
      "Despite the size it is incredibly warm. A fire "
      "pops and crackles in the hearth. Comfortable "
      "looking chairs and cots are scattered around "
      "the fireplace. In the center of the room a "
      "huge tree grows up three tall stories. Thick "
      "branches grow from the tree acting "
      "as a stair set to the other floors of the building. "
      "The floor is constructed of rough-"
      "hewn unfinished pine. Each footstep echos "
      "loudly in the large space. The walls are "
      "covered in some sort of living ivy. The scent "
      "of stew cooking wafts in from the south. The "
      "stairs lead up to a landing." );
           
    set( ForestP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "south" : ROOM "kitchen",
      "up"    : ROOM "landing1"      
    ]) );
    
    set( "descs",
    ([ 
      ({ "fire", "hearth", "fireplace", "fire place" }) : 
         "The wood on the fire glows bright red, occassionally "
         "hissing and belching steam. It is amazing it doesn't "
         "burn through the wooden hearth. The hearth is large "
         "enough to contain ten foot long logs.",
      
      ({ "log", "logs" }) :
         "The logs in the fire place are eight feet long "
         "and at least a foot around. They are stacked "
         "in a log cabin shape. They burn extremely "
         "hot.",
 
      ({ "chair", "chairs", "cot", "cots" }) :
         "The chairs and cots look extremely well used. "
         "They are draped in various soft furred animal "
         "hides.",
    
      ({ "tree", "trunk" }) :
         "A timeless oak. The largest that you have "
         "ever seen. It is amazing that is has survived so "
         "long. According to legend this tree was once "
         "a powerful dryad who sacrificed herself in "
         "the protection of forests everywhere.",
    
      ({ "branches", "branch", "stair", "stairs" }) : 
         "The branches appear very sturdy. The time "
         "it must have taken to train the tree to grow "
         "this way is unfathomable.",
      
      ({ "floor", "pine", "floors" }) :
         "The floor was obviously hand tooled. "
         "Each piece of wood carved with chisels, "
         "axes, and hatches. Each piece is unique.",
         
      ({ "ivy", "wall", "walls" }) :
         "The ivy seems to have made this wall "
         "its home. It is lush and the leaves "
         "are bright green. As you examine it "
         "you think you can actually see it growing!"
    ]) );
    
    /*
    set( "reset_data" , 
    ([ 
      
    ]) );
    */
    call_out( "fire_noise", random( 100 ) );
}

int fire_noise()
{
    string noise;
    switch( random( 3 ) )
    {
      case 0 : noise = "You hear the hissing of steam escaping a log on the fire."; break;
      case 1 : noise = "A log on the fire pops."                                  ; break;
      case 2 : noise = "There is a loud crunch as one of the logs collapses. "    ; break;
    }
    tell_room( THISO, sprintf( "%s\n", noise ), ({ }) );
    call_out( "fire_noise", random( 300 ) );
    return 1;
}    
