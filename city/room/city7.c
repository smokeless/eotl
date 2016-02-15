#include<city.h> 
inherit RoomPlusCode;
 
void extra_create() 
{
    set("short","Chooli, Main Street");
    set("day_long",
     "The going is easier here. The street is still dirt, but "
     "at least there aren't any guards. The city seems to move "
     "at its own pace. Things feel slower here, more relaxed then "
     "in a major city like Eternal. Though people seem very on "
     "edge. It shows in the little things, like the buildings "
     "not having fresh paint. To the west there is a small " 
     "shack bearing the sign \"Johnny's Magic and Technology\". "
     "To the south and north is Main street continues. To "
     "the east Dock street begins."
     );
    
    set("day_light",WELL_LIT);
    
    set( "descs", ([
      ({"dirt", "street" }) : "It's a nice red color.",
      ({"buildings", "building", "paint"}) : "Everything seems "
                                             "to have neglected upkeep. "
                                             "Except the guards. They "
                                             "seemed well equipped.",
      ({"sign","shop"}) : "Strange combination, magic and tech? "
                          "Not something that is usually mixed."
    
    ]));
    
    set("exits",([
      "north" : ROOM "city27",
      "west"  : ROOM "city6",
      "east"  : ROOM "city8",
      "south" : ROOM "city18"
    ]));
    
    set("reset_data", ([
      "resident"  : MON "resident",
      "residenta" : MON "resident",
      "residentb" : MON "resident"
    ]));
    replace_program();
}
