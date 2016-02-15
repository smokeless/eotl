#include <facility.h>

inherit RoomPlusCode;
inherit AnsiTellCode;
inherit DoorCode;

void extra_create()
{
    set( "short", "The Facility 31 Basement" );
    set( "ansi_short" HIK "The Facility 31 Basement" NORM );
    
    set( "day_long", "Cold grey concrete walls covered with moss "
      "and pieces of biological tissue give way to a very well "
      "contained space. Despite the size of the facility above, this "
      "room is not very large. The air is hot and humid, and smells "
      "of rot. In the center of the room surrounded by machinery there "
      "is a deep pit, it seems to be bottomless. Various displays and "
      "gauges are mounted on the walls. There is an endless humming sound "
      "in the air." );
	
    add_door( "west", FROOM "dstair", FOBJ "stairdoor" );
    
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
    
    set( "descs", 
    ([ 
      "pit" : "You cannot see the bottom, only feel "
        "hot air rising out of it.",
        
      ({ "wall", "walls", "tissue", "pieces" }) :
        "The walls are sticky with charred flesh, "
        "blood, flecks of uncharred skin, "
        "and hair.",
        
      ({ "gauges", "gauge", "display", "displays" }) :
        "You have no idea what any of this information is, "
        "it's just blinking lights, and nothing is labeled. "
        "If you searched hard enough you might be able to "
        "find something you could understand.",
    ]) );
    
    set( "reset_data",  
    ([
      "skelaf" : FMONS "skelaf",
	  "well"   : FOBJ "well"
	]) );
    
    call_out( "make_noise", 10 );
}
int search( string arg )
{
    string name = THISP->query_name();
	
    tell_object( THISP, "You peer through all the dials and "
	  "gauges. Hidden behind one of them is a button labeled: "
	  "INCINERATE!\n" );
	
    tell_room( ENV( THISP ), sprintf( "%s roots around "
	  "the room, determined to find something.\n", name ),
      ({ THISP }) );
	
    return 1;
}

int make_noise()
{
    int noisetime = random( 140 ) + 5;
    
    string noise;
    
    switch( random( 8 ) )
    {
      case 0 : noise = "Jump into the pit, join us...\n";             break;
      case 1 : noise = "Treasure and freedom await, leap in...\n";    break;
      case 2 : noise = "Come with us, with us you will be free...\n"; break;
      case 3 : noise = "We fear nothing. We are one...\n";            break;
      case 4 : noise = "Smell, taste, wishes, we have none "
        "of these...\n";                                              break;
      case 5 : noise = "A leap will set you free...\n";               break;
      case 6 : noise = "A gust of hot air rises from the pit.\n";     break;
      case 7 : noise = "We will never decay, we will never die "
        "again...\n" ;                                                break;
    }
    
    ansi_tell_room( THISO, sprintf( "%s", noise ), HIK );
    
    call_out( "make_noise", noisetime );
    
    return 1;
}
void enter_signal( object inc, object vag )
{
    object skelaf;
    if( interactive( inc ) && objectp( skelaf = present( "Skelaf", THISO ) ) ) 
    {
	skelaf->start_greet( inc );
    return 0;
    }
}
