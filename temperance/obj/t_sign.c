#include <town.h>

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "sign", "weathered sign" }) );
    
    set_short( "a weathered sign" );
    set_ansi_short( GRN "a weathered sign" );
    
    set_long( "Set on top of a small wooden post is a beaten "
      "old sign pointing southeast. You should read it." );
      
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "read", "read" );
}

int read( string arg )
{   
    if( !stringp( arg ) ||  arg != "sign" )
      return notify_fail( query_verb()  + "what?\n" );
    
    if( THISP->query_skill( "Silvari" ) < 10 )
      return notify_fail( "You don't know Silvari well enough.\n" );
    
    tell_object( THISP, "The sign reads \"Temperance City: What happens here stays here.\"\n" );
    return 1;
}
