#include <tomb.h>

inherit RoomPlusCode;
inherit AnsiTellCode;

void extra_create()
{
    set( "ansi_short", HIK "In a tunnel." );
    set( "short", "In a tunnel." );
    set( "day_long", "This tunnel is composed of plain roughly worked "
      "stone. It is dark and full of cobwebs. The high ceiling overhead "
      "is obscured by these hanging strands. Daylight filters in from "
      "above. At the end of the tunnel you can see a large set of "
      "oak doors." );
      
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", ([
      "north" : ROOM "trap2",
      "up"    : ROOM "hill1" ]) );

    set( "descs", 
    ([ 
      ({ "web", "webs", "cobwebs", "ceiling" }) : "You can just barely make out the "
                                       "ceiling of this tunnel. The rocks "
                                       "above look like they were horribly "
                                       "fitted together.",
        
      ({ "doors", "door" }) : "You can see large oak doors at the end "
                              "of the hall.",
      ({ "stone", "tunnel" }) : "The entire build quality is horrible "
                                "by todays standards."
    ]) );
}
