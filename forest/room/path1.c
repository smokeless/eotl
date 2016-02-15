#include <forest.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A narrow cave path" );
    set( "ansi_short", YEL "A narrow cave path" );
    
    set( "day_long", "You are surrounded on all sides by "
      "solid rock. It seems to be getting narrower as you progress "
      "down into the earth. A glimmer of light shines to the south. "
      "To the north the barricade towers above you." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
    
    add( "exits", 
    ([
      "south" : FROOM "path2"      
    ]) );
    
    set( "descs",
    ([ 
      "barricade" : "The barricade looks hastily constructed, "
                    "but very sturdy. The boulders must weigh "
                    "thousands of pounds. You might be able to climb it."
    ]) );    
}

void extra_init()
{
    add_action( "climb", "climb" );
}

int climb( string arg )
{    
    int skill = THISP->query_skill( "climb" );
    int dex = THISP->query_stat( "dex" );
    int number = dex + skill;
    
    if( !stringp( arg ) || arg != "barricade" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
      
    if( number < 70 )
    {
      tell_player( THISP, "You wouldn't even know where to start.\n" );
      return 1;
    }
    
    tell_room( THISO, sprintf( "%s climbs over the barricade. Wow!\n", 
      THISP->query_name() ), ({ THISP }) );
    
    tell_player( THISP, "You climb over the barricade.\n" );
    
    THISP->move_player( "&&", "/zone/present/fac31/room/facility/outside", 1 );
    return 1;
}
