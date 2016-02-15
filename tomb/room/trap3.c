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
      "above. You are standing in front of a set of large oak doors." );
      
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", ([
      "south" : ROOM "trap2" ]) );

    set( "descs", 
    ([ 
      ({ "web", "webs", "cobwebs", "ceiling" }) : "You can just barely make out the "
                                       "ceiling of this tunnel. The rocks "
                                       "above look like they were horribly "
                                       "fitted together.",
        
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
      "start to pull. It takes all of your strength but you get it to budge. "
      "Unfortunately it displaces a large portion of the ceiling! Rocks come "
      "crashing down onto you!", RED );
    ansi_tell_room( ENV( THISP ), sprintf( "%s grabs hold of the doors and "
      "with a grunt gets them to move a bit. This unfortunately displaces "
      "a large portion of the ceiling which comes crashing down on you!", 
      THISP->query_name() ), RED,
      ({ THISP }) );
    
    object *inv = filter_array( all_inventory( ENV( THISP ) ), #'living );
    int i = sizeof( inv );
    while( i-- )
    {
      inv[ i ]->take_damage( dam, 0, "blunt", THISO );
    }
    if( !me->query_ghost() && !me->query( "its_a_trap" ) )
    {
        tell_player( me, "You have earned the achievement "
          "It's a trap! You feel more experienced." );
        me->add_exp( 1000000 );
        me->set( "its_a_trap", 1 );
    }
    return 1;    
}    
