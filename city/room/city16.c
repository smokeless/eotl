#include<city.h> 
inherit RoomPlusCode;
void extra_create() 
{
    set("short","Alvaro Street, Chooli");
    set("day_long", "This street is extremely muddy. "
      "There are deep ruts in the road where tanks have "
      "been driven up and down the street. All around "
      "you are old tenant housing buildings. They have "
      "been covered in steel plating, windows, doors "
      "everything. This area seems very secure. To the " 
      "east you can see Main street. To the west Alvaro continues.");
      
    set("day_light",WELL_LIT);
    set( "exits", ([
      "west" : "city29",
      "east" : "city18"
    ]));
    
    set("reset_data", ([
      "guard": MON "guard",
      "gubrd": MON "guard"
    ]));
    
    set( "descs", ([
      ({ "street", "mud" }) : "It's well worn that's for sure. "
                              "It's amazing how muddy it is despite "
                              "the lack of any water sources.",
      ({ "buildings", "housing" }) : "Maybe this is where the refugees live? "
                                     "Or maybe the space is used by the city "
                                     "government for something?"
    ]));
    
    replace_program();
}
