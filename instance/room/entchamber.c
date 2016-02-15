#include <instance.h>
inherit RoomCode;

void extra_create()
{
    set( "short", "a chamber in the Darkblade mines" );
    set( "day_long", "This chambered was hollowed out and "
      "looks like it may have served as a staging area for "
      "mine workers at one point. It's lit by torches. Each "
      "of your footsteps echoes loudly." );
    
    set( "day_light", TORCH_LIT );
    set( "exits",
    ([
      "north" : ROOM "entry2",
      "east" : ROOM "chamber2",
      "southeast" : ROOM "chamber4",
      "south"     : ROOM "chamber3"
    ]) );
    replace_program( RoomCode );
}
