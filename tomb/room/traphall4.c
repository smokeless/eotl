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
      "south" : ROOM "traphall3", 
      "north" : ROOM "traphall5" ]) );

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

void clear_exits()
{
    set( "day_long", "This tunnel is composed of plain roughly worked "
      "stone. It is dark and full of cobwebs. The celing is roughly 10 "
      "feet high. Daylight filters in from the entrance. "
      "To the south there is a flat wall blocking your progress. " 
      "To the north you can see a set of heavy oak doors." );
    set( "exits", ([
      "north" : ROOM "traphall5" ]) );
    return;
}

void fix()
{
    set( "exits", ([
      "south" : ROOM "traphall3", 
      "north" : ROOM "traphall5" ]) );
    set( "day_long", "This tunnel is composed of plain roughly worked "
      "stone. It is dark and full of cobwebs. The celing is roughly 10 "
      "feet high. Daylight filters in from the entrance. "
      "To the north at the end of the hall you can see a set of "
      "heavy oak doors." );
    return;
}
