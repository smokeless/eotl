#include <facility.h>

inherit NewThingCode;

/*
This object is moved into /zone/null/underworld/sewer/sewer39
by outside.c. It is the entry into the facility.
*/

//#define LOC "/zone/null/underworld/sewer/sewer39"

void extra_create()
{
    set_id( "crack" );
    
    set_short( "a large spreading crack" );
    set_ansi_short( HIK "a large spreading crack" );
    
    set_long( "The entirety of the west wall is starting to "
      "crack open. As you look at it, you notice that there "
      "is light shining through. The crack seems large enough "
      "that you could squeeze through it." );
         
    set_gettable( 0 );
    move_object( THISO, LOC );
}

void extra_init()
{
    add_action( "squeeze", "squeeze" );
}

int squeeze( string arg )
{
    if( !stringp( arg ) || arg != "through crack"  )
      return notify_fail( query_verb()  + "through what?" );

    tell_player( THISP, "You suck in your gut and squeeze "
      "through the crack." );
    
    tell_room( ENV( THISO ), sprintf( "%s squeezes through the "
      "crack in the wall.\n", THISP->query_name() ), ({ THISP }) );
    
    THISP->move_player( "&&", FROOM "outside", 1 );
    
    return 1;
}
