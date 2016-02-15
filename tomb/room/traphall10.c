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
      "You are standing in front of a set of large oak doors." );
      
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", ([
      "south" : ROOM "traphall9" ]) );

    set( "descs", 
    ([ 
      ({ "web", "webs", "cobwebs", "ceiling" }) : "You can just barely make out the "
                                       "ceiling of this tunnel. The rocks "
                                       "above are smooth and well maintained.",
        
      ({ "doors", "door" }) : "These doors are absolutely enormous! Hewn "
                              "out of sturdy well finished oak. They reach "
                              "all the way up to the ceiling!",
      ({ "stone", "tunnel" }) : "The entire build quality is horrible "
                                "by todays standards."
    ]) );
}

void extra_init()
{
    add_action( "open", "open" );
}

int open( string arg )
{
    object me = THISP;
    int dam = random( 300 ) + 50;
    if( !stringp( arg ) && arg != "door" && arg != "doors" )
    {
      tell_player( THISP, "What do you want to open?" );
      return 1;
    }
    ansi_tell( THISP, "You grab hold of the extremely heavy doors, and "
      "start to pull. They won't budge!", RED );
    ansi_tell_room( ENV( THISP ), sprintf( "%s grabs hold of the doors and "
      "tugs to no avail. They won't budge.", 
      THISP->query_name() ), RED,
      ({ THISP }) );
    
    return 1;    
}    
