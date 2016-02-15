#include <facility.h>;

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "pipe", "waste pipe", "sewer" }) );
    
    set_short( "a large rusted sewer drainage pipe" );
    set_ansi_short( YEL "a large rusted sewer drainage pipe" );
    
    set_long( "The pipe is covered in over an inch of brown "
      "filth and corrosion. There are bits of hair and rotting "
      "skin stuck to it. You can hear the sounds of a city echoing "
      "inside of it, but have no idea how far it goes. It looks like "
      "when the Eternal sewer system was being built someone ran across "
      "this pit and then abadoned the entire pipe run. You think you "
      "could crawl through it." );
      
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "crawl", "crawl" );
}

crawl( string arg )
{
    if( !stringp( arg ) || arg != "through pipe" && arg != 
      "through sewer" )
      return notify_fail( query_verb()  + " through what?\n" );
      
    tell_player( THISP, "You take a deep breath and crawl through "
      "the pipe. It seems to go on forever. But finally "
      "you emerge!" );

    tell_room( THISO, sprintf( "%s takes a deep breath and crawls "
      "into the pipe.\n", THISP->query_name() ), ({ THISP }) );

    THISP->move_player( "&&", "/zone/null/underworld/sewer/sewer10", 1 );

    return 1;
}    
