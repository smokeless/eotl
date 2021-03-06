//fix the traphall room
#include <tomb.h>

inherit RoomPlusCode;
inherit AnsiTellCode;


void extra_create()
{
    set( "ansi_short", HIK "In a tunnel."  );
    set( "short", "In a tunnel." );
    set( "day_long", "This tunnel is composed of plain roughly worked "
      "stone. It is dark and full of cobwebs. The celing is roughly 10 "
      "feet high. Daylight filters in from the entrance. "
      "To the north at the end of the hall you can see a set of "
      "heavy oak doors." );
      
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", ([
      "south" : ROOM "traphall4", 
      "north" : ROOM "traphall6" ]) );

    set( "descs", 
    ([ 
      ({ "web", "webs", "cobwebs", "ceiling" }) : "You can just barely make out the "
                                       "ceiling of this tunnel. The rocks "
                                       "above are smooth and well maintained.",
        
      ({ "doors", "door" }) : "From here they look to be extremely "
                              "solid.",
      ({ "stone", "tunnel" }) : "The entire build quality is horrible "
                                "by todays standards."
    ]) );
}

void enter_signal( object inc, object vag )
{
    object trap =to_object( OBJ "halltrap" );
    object room =to_object( ROOM "traphall3" );
    if( !present_clone( trap, room ) )
    {
      clone_object( trap );
      move_object( trap, room );
      object guy = inc;
      ansi_tell( guy, "You hear a loud rumbling sound from "
        "behind you!", RED );
      trap->start( guy );
    return;
    }
    return;
}
