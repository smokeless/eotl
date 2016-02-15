#include<city.h> 
inherit RoomPlusCode;
void extra_create() 
{
    set( "short", "Chooli, Main street");
    set("day_long",
      "Main street becomes wider here. It looks like you've reached "
      "a market of sorts. Refugees have set up a few carts and are "
      "competing with each other for sales. Despite the commerce "
      "all around you, there is an air of sadness to the market. "
      "Perhaps they are just looking for an influx of coin. "
      "To the east is a general store, an alley runs off to the "
      "west, to the north and south Main street continues." );
    
    set("day_light", WELL_LIT);
    set("exits",([
      "north" : ROOM "city24",
      "west"  : ROOM "city26",
      "east"  : ROOM "city28",
      "south" : ROOM "city7"
    ]));
    
    set("reset_data", ([
      "resident"  : MON "resident",
      "residenta" : MON "resident",
      "residentb" : MON "resident",
      "cart"      : OBJ "cart",
      "carta"     : OBJ "cart",
      "cartb"     : OBJ "cart",
      "peace"     : OBJ "aggro_obj"
    ]));
    
    replace_program();
}
 
