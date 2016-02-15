#include <facility.h>

inherit NewThingCode;

int battery;
int camnumber;
object camobj;

void extra_create()
{
    camnumber = 1;
    battery = 100;
    set_ids( ({ "tablet", "security tablet" }) );
    
    set_short( "a security tablet" );
    set_long( "This tablet has a 7-inch LCD touchscreen and Wi-Fi capability. " 
      "Where there would normally be a camera there is an ejection port. "
      "On the right side of the tablet near the ejection port there is a large red button."
      "This tablet is running DrowOS. The screen saver is enabled and reads \"Property of Facility "
      "31\". The case is made of an extremely light weight plastic. You might try "
      "pressing the button. Or touching the screen." );
      
    set_weight( 5 );
    set_value( 0 );
    set( NoStoreP, 1 );
    
    set_limit( 3 );
}

void extra_init()
{
    add_action( "roomcheck", "touch" );
    add_action( "camera", "press" );
    add_action( "camera", "push" );
}

int roomcheck( string arg )
{
    if( arg != "screen" )
      return notify_fail( query_verb()  + " what?\n" );
    
    battery = battery - 10;
    
    if( battery <= 0 )
    {
      tell_player( THISP, "The batteries are dead!" );
      return 1;
    }
    
    tell_room( ENV( THISP ), sprintf( "%s whips out some sort of new fangled "
      "tech gadget and plays around with it.\n", THISP->query_name() ), ({ THISP }) );
  
    tell_player( THISP, "The screen glows white for a moment then presents you with "
      "some data." );
    
    if( ENV( THISP )->query( NoCombatP ) )
      tell_player( THISP, "You are in a no combat room." );
    else
      tell_player( THISP, "You are in a combat room." );
    
    if( ENV( THISP )->query( NoPKP ) )
      tell_player( THISP, "You are in a no PK room." );
    else
      tell_player( THISP, "You are in a PK room." );
    
    if( ENV( THISP )->query( NoTeleportP ) )
      tell_player( THISP, "You cannot teleport in this room." );
    else
      tell_player( THISP, "You can teleport in this room." );
    
    if( ENV( THISP )->query( OutsideP ) )
      tell_player( THISP, "You are outside." );
  
    if( ENV( THISP )->query( InsideP ) )
      tell_player( THISP, "You are inside." );
    
    return 1;
 }
 
 int camera( string arg )
 {
    string queryobj, desc;
    object *inventory;
    int i;
    
    if( arg != "button" )
      return notify_fail( query_verb()  + " what?\n" );
    
    battery = battery - 10;
    if( battery <= 0 )
    {
      tell_player( THISP, "The batteries are dead!" );
      return 1;
    }
    
    if( camnumber == 1 )
    {
      tell_room( ENV( THISP ), sprintf( "%s whips out some sort of new fangled "
        "tech gadget and plays around with it.\n", THISP->query_name() ), ({ THISP }) );
    
      tell_player( THISP, "You push the button and a tiny little camera shoots out of "
        "the back of the device and onto the ground." );
      camobj = clone_object( FOBJ "camera" );
      move_object( camobj, ENV( THISP ) );
      camnumber = 0;
      return 1;
    }      
    
    if( camnumber == 0 && camobj->query( "alive" ) )
    {
      queryobj = to_string( camobj );
      tell_room( ENV( THISP ), sprintf( "%s whips out some sort of new fangled "
        "tech gadget and plays around with it.\n", THISP->query_name() ), ({ THISP }) );
      tell_player( THISP, sprintf( "You mash the button and the tablet screen lights up. "
        "You see: " ) );
      if( ENV( queryobj )->query( "short" ) == 0 )
        desc = ENV( queryobj )->query_name()+"\n";
      else
        desc = ENV( queryobj )->query( "short" )+"\n";
      
      inventory = all_inventory( ENV( camobj ) );
      for( i = 0; i < sizeof( inventory ); i++ )
      if( inventory[ i ]->short() )
       desc += inventory[ i ]->short() + "\n";
       THISP->more_string( desc );
      return 1;
    }
    else
      tell_player( THISP, "The screen remains blank. Your camera must have run out "
        "of batteries." );
      return 1;    
}  
