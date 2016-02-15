#include <popcontrol.h>

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "poison", "vial of poison", "vial" }) );
    set_short( "a vial of poison" );
    set_ansi_short( RED "a vial of poison" );
    set_long( "A very old vial of bubbling red liquid. It is "
      "conviently stored within a test tube. A cork at the "
      "top allows for easy opening and pouring. The expiration "
      "date is completely illegible, so who knows if it "
      "even works anymore. It is labled "
      "\"Doctor Snakey's Extremely Dangerous Formula.\" It could " 
      "probably be used to poison food." );
      
    set_weight( 1 );
    set_value( 5 );
    set( NoStoreP, 1 );
}

void extra_init()
{
    add_action( "poison", "poison" );
}

poison( string str )
{
    object poisoned;
    string short, long, *ids;
    string id;
    
    if( !present( str, THISP ) )
      return notify_fail( "You don't have that.\n" );
    
    poisoned = present( str, THISP );
    
    if( !poisoned->query_food_array() && !poisoned->query_intox_array() &&
      !poisoned->query_heal_array() )
      return notify_fail( "That is not a food or drink item.\n" );
    
    tell_player( THISP, sprintf( "You poison %s.", poisoned->query_short() ) );
    tell_room( ENV( THISP ), sprintf( "%s pours a vial of liquid over %s.\n",
      THISP->query_name(), poisoned->query_short() ), ({ THISP }) );
    
    short = poisoned->query_short();
    long  = poisoned->query_long();
    poisoned->query_ids();
    id = poisoned->query_id();
    set_ids( ids );
    set_short( short );
    set_long( long );
    return 1;
}
