#include <forest.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "An underground forest" );
    set( "ansi_short", GRN "An underground forest" );
 
    set( "day_light", PART_LIT );
    
    
    set( OutsideP      , 1 );
    set( NoTeleportP   , 1 );
    
    add( "exits", 
    ([
      "north" : FROOM "path2",
      "south" : FROOM "f11",
      "east"  : FROOM "f4",
      "west"  : FROOM "f2"      
    ]) );
}

void extra_init()
{
    string long;
    switch( random( 100 ) + 1 )
    {
      case 0..30 :  long = "Light shines in from the half dome above you "
        "allowing you to move easily through the thick mushroom growth. "
        "Huge mushrooms with red stems tower over you forming a thick "
        "canopy. The stone ground below you is thick with moss, forming "
        "a comfortable cushion for every step."; break;
      case 31..40 : long = "You have reached a clearing in the mushroom "
        "forest. Massive rocks covered in moss jut out of the ground. "
        "The air is humid and still around you. The forest surrounds you "
        "on all sides. Tiny bits of water trickle out of the ground."; break;
      case 41..60 : long = "The elevation here is lower than most of the "
        "forest. The mushroom stalks bend restlessly in a crisp breeze. "
        "The humidity in the air is gone. You can hear creatures "
        "skittering and moving about further into the woods."; break;
      case 61..100 : long = "The moss underfoot is extremely bright here. In "
        "combination with the light filtering through the cave ceiling "
        "it is more than enough to see by. The air is humid and heavy. Gigantic "
        "mushrooms sway to a breeze that you cannot feel. The sound of critters "
        "scurrying along rocks and through brush comes from somewhere within the "
        "forest."; break;
    }
    
    set( "day_long", long );
}
    
