#include <facility.h>

inherit RoomPlusCode;
inherit AnsiTellCode;

void extra_create()
{
    set( "short", "The Facility 31 Basement" );
    set( "ansi_short" HIK "The Facility 31 Basement" );
    
    set( "day_long", "Cold grey concrete walls covered with blood "
      "stained moss give way to a very well contained space. Despite "
      "the size of the facility above, this room is not very large. "
      "The air is hot, humid, and it smells of rot. In the center of "
      "the room surrounded by destroyed machinery there is a well. "
      "To the west there is a stairwell." );
	
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "descs", 
    ([  
      ({ "wall", "walls", "moss", "blood" })  :
        "The moss on the wall glows slightly, despite being blackened "
        "with dried blood. There are large swaths of moss missing, as "
        "if something slashed them away.",
        
      ({ "machinery", "destroyed machinery" }) :
        "Something smashed this machinery to pieces. All it is now "
        "is a pile of components. Maybe whatever is in the well "
        "is a luddite."
    ]) );
    
    set( "exits", 
    ([
      "west"  : FROOM "dstair1",
    ]) );
    
    set( "reset_data",  
    ([
	  "well"   : FOBJ "well1"
	]) );
    
    call_out( "make_noise", 10 );
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
