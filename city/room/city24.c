#include<city.h>
inherit RoomPlusCode;

void extra_create() 
{
    set("short","Chooli, Main Street");
    set("day_long",
      "Main street narrows here. On the west side of the street "
      "there is a small dry creek bed. The dirt of the street isn't "
      "as well packed, dust kicks up as you move around. To the north "
      "you see a large industrial mansion. To the east there is some sort of "
      "hunting shop. To the west Proud street begins." );
      
    set("day_light",WELL_LIT);
    
    set( "descs", ([
      ({"creek", "creek bed" }) : "Looks like there hasn't been rain in ages."
                                  "Of course you are also underground. Maybe "
                                  "it's just not seeping through properly.",
      "mansion"                 : "It looks like something from "
                                  "a science fiction novel. "
                                  "It's an old style, done completely "
                                  "in black steel, with harsh modern "
                                  "angles."
    
    ]));
    
    set("exits",([
      "north" : ROOM "city21",
      "west"  : ROOM "city23",
      "east"  : ROOM "city25",
      "south" : ROOM "city27"
    ]));
   
    replace_program();
}
