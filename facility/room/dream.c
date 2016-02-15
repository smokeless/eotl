#include <facility.h>

inherit RoomPlusCode;

//This room is where a player napping in the intern lounge goes.

void extra_create()
{
    set( "short", "in the ether" ); 
    set( "ansi_short", sprintf( "%sin the ether", HIK ) );   
    
    set( "day_long", "There is nothing here. Literally nothing. It is just "
      "a barren expanse of black." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
}

//Called when a player is moved into this room.
int start( object arg )
{
    string name = arg->query_real_name();
    
    if( !find_player( name ) )
      return 0;
    
    tell_player( arg, "You feel like you are being watched." );
    call_out( "watcher", 5, THISP );
    return 1;
}
void watcher( object arg )
{
    tell_player( arg, "You feel something caressing your body." );
    call_out( "tender_lovin", 10, THISP );
}
void tender_lovin( object arg )
{
    tell_player( arg, "There is a horrible roar in the distance." );
    call_out( "get_out", 3, THISP );
}
void get_out( object arg )
{
    tell_player( arg, "You try to snap awake, but it isn't working. "
      "The roar is getting closer, and louder." );
    call_out( "snack", 5, THISP );
}
void snack( object arg )
{
    tell_player( arg, "You finally wake up. You check your body, "
      "you are strangely sticky." );
    THISP->move_player( "&&", FROOM "intern", 1 );
}
