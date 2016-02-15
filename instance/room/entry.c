#include <instance.h>
inherit RoomCode;

void extra_create()
{
    set( "short", "Darkblade Mines Entrance" );
    set( "day_long", "You stand at the entrance to the "
      "Darkblade mines. According to legend they were "
      "abandoned years in the past. However you definitely "
      "hear the sound of pick axes and movement. Not to "
      "mention there are torches on the walls. Something "
      "is happening down here. It's time to find out what" );
    
    set( "day_light", TORCH_LIT );
    set( "exits",
    ([
      "west" : ROOM "entry2"
    ]) );
    replace_program( RoomCode );
}
