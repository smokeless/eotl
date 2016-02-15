#include <facility.h>

inherit RoomPlusCode;

//This room is the result of a player leaping into
//the well in the basement of facility 31. They will
//fall to their deaths.
void extra_create()
{
    set( "short", "falling" ); 
    set( "ansi_short", HIK "%falling" NORM  );   
    
    set( "day_long", "The wind whips your face as you plummet "
      "towards the bottom of the pit." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
}

int start( object arg )
{
    string player = arg->query_real_name();
    if( !find_player( player ) )
      return 0;
    tell_player( arg, "The air starts to get hotter." );
    call_out( "phase2", 5, THISP );
}
void phase2( object arg )
{
    tell_player( arg, "It feels like you have been falling forever." );
    call_out( "phase3", 10, THISP );
}
void phase3( object arg )
{
    tell_player( arg, "You think you can make out something at the "
      "bottom of the pit." );
    call_out( "phase4", 3, THISP );
}
void phase4( object arg )
{
    tell_player( arg, "There is definitely something shifting "
      "down in the darkness. You can make out a huge dark shape."
    );
    call_out( "phase5", 5, THISP );
}
void phase5( object arg )
{
    tell_player( arg, "You hit the ground with a resounding thud. "
      "Your limbs twist and contort." );
    THISP->move_player( "&&", FROOM "pit", 1 );
    arg->DeathSequence( arg, "fell too far" );
}
