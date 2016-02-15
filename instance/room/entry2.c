#include <instance.h>
inherit RoomCode;

void extra_create()
{
    set( "short", "Darkblade Mines Entry" );
    set( "day_long", "At least the cave is lit. " 
      "The rock is jagged and crumbling from being "
      "mined for many years. The air is hot and humid. "
      "Which is strange considering that you're underground. "
      "To the south you can hear footsteps. The tunnel "
      "continues south. To the east you can see where you entered." );
    
    set( "day_light", TORCH_LIT );
    set( "exits",
    ([
      "south" : ROOM "entchamber",
      "east" : ROOM "entry"
    ]) );
    replace_program( RoomCode );
}
