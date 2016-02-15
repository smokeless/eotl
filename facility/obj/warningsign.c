#include <facility.h>;

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "sign", "warning", "warning sign" }) );
    
    set_short( "a warning sign taped to the west wall" );
    set_ansi_short( HIR "a warning sign taped to the west wall" );
    
    set_long( "It is big and red. It is made out of plastic "
      "and there is a picture of a teddy bear dismembering a "
      "person on it. You should probably read the sign." );
    
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "read", "read" );
}

int read( string arg )
{
    if( !stringp( arg ) || arg != "sign" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    tell_player( THISP, "In large letters the sign says \""
      "ABSOLUTELY NO UNAUTHORIZED PERSONAL. RESTRICTED AREA.\" "
      "The fine print says, \"Facility 31 is not responsible for "
      "any actions that may or may not be taken against your person "
      "should you attempt to view, or enter this restricted area.\"" );
    
    return 1;
}
