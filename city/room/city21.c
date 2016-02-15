#include<city.h> 
inherit RoomPlusCode;

extra_create() 
{
    set("short","Technomancers Meeting Hall");
    set("day_long",
      "This meeting hall is extremely well lit by pulsating "
      "tesla coils. The floors are hard wood, and extremely "
      "well maintained. You can smell incense in the air. "
      "There is a large fire place in the center of the "
      "room radiating warmth out to plush couches that "
      "circle it. The area has a very comfortable feel, "
      "despite the general lack of safety in the lighting." 
      "To the west is the discussion room. To the south "
      "is the bustle of Main street. To the east is some sort "
      "of private area. An ornate staircase leads up and down "
      "as far as the eye can see.");
      
    set("day_light",WELL_LIT);
    
    set("reset_data", ([
      "guy"    : MON "resident",
      "guy2"   : MON "resident",
      "sci"    : MON "scientist",
      "mage"   : MON "mage",
      "leader" : MON "leader",
      "guard"  : MON "guard",
      "guard1" : MON "guard", 
      "coil"   : OBJ "coil",
      "magic"  : OBJ "magic_machine",
      "magic2" : OBJ "magic_machine"
    ]));
    
    set( "descs", ([
      ({ "fire", "fireplace", "fire place" }) : "The fire keeps the "
                                                "room at a perfect "
                                                "temperature, but uses no fuel.",
      ({ "wood", "floors" })  : "It appears to be from Newhaven. It comes from "
                                "the tree commonly used to support treehouses.",
      ({ "couch", "couches"}) : "Hand tooled soft leather? Yes please.",
      "lighting"              : "Probably not the best idea to light rooms with "
                                "uncontrolled electrical current.",
      ({ "stairs", "staircase" }) : "You can't tell where it goes."                                
    ]));
    
    set( "exits", ([
      "up"   : "@nope",
      "down" : "@nope",
      "west" : ROOM "city20",
      "east" : "@nope",
      "south": ROOM "city24"
    ]));
}
 
int nope()
{
    string y;
    switch( random( 4 ) )
    {
        case 0 : y = "roaring magical fire";      break;
        case 1 : y = "arcing blue electricity";   break;
        case 2 : y = "horribly chilling dry ice"; break;
        case 3 : y = "oozing molten steel";       break;
    }
    
    tell_player( THISP, sprintf( "As you approach the exit a barrier of %s "
      "explodes into existence. You aren't getting through it.", y ) );
    if( present_clone( MON "guard", THISO ) )
    { 
      object x = present_clone( MON "guard", THISO );
      command( sprintf( "say I'm watching you %s.", 
        CAP( THISP->query_real_name() ) ), x );
      return 1;
    }
    return 1;
 }
