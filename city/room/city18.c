#include<city.h> 
inherit RoomPlusCode;

void extra_create() 
{
    set("short", "Chooli, Main Street");
    set("day_long",
      "This is the main drag of Chooli. This particular area "
      "is essentially one gigantic pit of mud. There are cart "
      "tracks and foot prints running all through it. The inner "
      "gate guards survey you from within large steel enclosed "
      "bunkers. Some guards stand outside of the bunkers near "
      "tanks. To the north the main drag continues, to the " 
      "south you can see the gates you passed through, to the "
      "east and west is Alvaro street.");
    
    set("day_light",WELL_LIT);
    
    set( "exits", ([
      "north" : ROOM "city7",
      "west"  : ROOM "city16",
      "east"  : ROOM "city17",
      "south" : ROOM "gates"
    ]));
    
    set( "reset_data", ([
      "guarda" : MON "guard",
      "guardb" : MON "guard",
      "tanka"  : OBJ "tank",
      "tankb"  : OBJ "tank",
      "peace"  : OBJ "aggro_obj"
    ]));
    
    set( "descs", ([
      ({ "mud", "tracks", "footprints" }) : "Looks like a lot of "
                                            "people have been "
                                            "through here recently.",
      ({ "bunker", "bunkers", "steel" })  : "There are slits cut into "
                                            "these solid steel bunkers. "
                                            "You can hear movement from "
                                            "inside. The barrels of "
                                            "guns poke out from the slits. "
                                            "You probably don't want "
                                            "any trouble."
    ]));
    replace_program();
}
