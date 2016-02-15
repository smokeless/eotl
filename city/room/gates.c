#include<city.h>
inherit RoomPlusCode;
void extra_create() 
{
    set("short","Gates of Chooli");
    set("day_long",
      "You are at the gates of Chooli. Armed guards "
      "stand alert and looking for trouble. Beyond "
      "the gates you can hear the bustle of a populated "
      "city. Refugees stand in line waiting for the guards "
      "to validate their entry into the city. "
      "To the east you can see a worn path. To "
      "the north you can see the main street of Chooli.");
    set("day_light", WELL_LIT);
    
    set( "reset_data", ([
      "guarda"  : MON "guard",
      "guardb"  : MON "guard",
      "refuge"  : MON "refuge",
      "refugea" : MON "refuge",
      "refugeb" : MON "refuge"
    ]));
    
    set( "descs", ([
      ({"gate", "gates"}) : "These gates are made of thick steel. "
                            "Obviously they are made to keep something out. "
                            "Or maybe, something in."                            
    
    ]));
    
    set("exits", ([ 
    "north" : ROOM "city18"
    ]));
    replace_program();
}
