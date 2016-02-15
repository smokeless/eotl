#include <popcontrol.h>

inherit NewThingCode;

string action;
string *whatisit;

void extra_create()
{
    set_ids( ({ "poison", "vial of poison", "vial" }) );
    set_short( "a vial of poison" );
    set_long( "This is a vial of poison. It has a picture of a "
      "crossed out dead bug on the label. It is clearly for "
      "killing insects. The fluid inside is odorless, probably "
      "tasteles. The label reads: \"Not for human consumption.\"" );
      
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
    
    if( !present( str, THISP ) )
      return notify_fail( "You don't have that.\n" );
    
    poisoned = present( str, THISP );
    
    if( !poisoned->query( "heal_action" ) )
      return notify_fail( "That is not a food or drink item.\n" );
      
    action = poisoned->query( "heal_action" );
    
    tell_player( THISP, sprintf( "You poison %s.", poisoned->query( "short" ) ) );
    tell_room( ENV( THISP ), sprintf( "%s pours a vial of liquid over %s.\n",
      THISP->query_name(), poisoned->query( "short" ) ), ({ THISP }) );
    
    whatisit = poisoned->query( "id" );
    
    THISO->set_ids( whatisit );
    set_short( poisoned->query( "short" ) );
    set_long( poisoned->query( "long" ) );
    add_action( "sucker", action );
    destruct( poisoned );
    return 1;
}

int sucker( string str )
{
    if( !str )
      return 0;
    if( member( query_ids(), str ) == -1 )
      return 1;
      
    tell_player( THISP, sprintf( "You feel a horrible burning "
      "sensation in your throat. Something may have been off about "
      "%s.", THISO->query( "short") ) );
    tell_room( ENV( THISP ), sprintf( "%s grabs %s stomach after consuming "
      "%s.\n", THISP->query_name(), possessive( THISP ),
      THISO->query( "short" ) ), ({ THISP }) );
    
    destruct( THISO );
    return 1;
}
