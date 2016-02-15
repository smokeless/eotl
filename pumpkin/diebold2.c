#include <ansi.h>

inherit NewThingCode;


#define REGFILE "/usr/socialism/pumpkin/registered"

void extra_create()
{
    set_ids( ({ "machine", "listing machine", "listing" }) );
    set_short( "a pumpkin listing machine" );
    set_long( "This is an outdated Diebold voting machine. "
      "Someone has painted it orange and re-purposed it "
      "for use with the halloween pumpkin carving contest. "
      "You could probably touch the screen for a list of "
      "registered pumpkins. If you posted your pumpkin a couple "
      "of days ago and it isn't showing up on the list, mail "
      "Socialism." );
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "touch" , "touch" );
}


int touch( string arg )
{
    if( !stringp( arg ) || arg != "screen" )
      return notify_fail( "Touch what?\n" );
    tell_player( THISP, "You touch the screen.\n" );
    tell_room( ENV( THISP ), sprintf( "%s views the "
      "list of registered pumpkins.\n", THISP->query_name() ),
      ({ THISP }) );
    string *registered = grab_file( REGFILE );
    
    if( sizeof( registered ) == 0 )
    {
      tell_player( THISP, "No one has registered.\n" );
      return 1;
    }
    ansi_tell( THISP, "*********************\n", YEL );
    tell_player( THISP, sprintf( "%s\n", 
      ( implode( registered, "\n" ) ) ) );
    ansi_tell( THISP, "*********************\n", YEL );
    return 1;
}
