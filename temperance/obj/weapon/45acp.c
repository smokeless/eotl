#include <town.h>

inherit AmmoCode;

void extra_create()
{
    set_ids( ({ "round", "ammo", "45 acp", "45" }) );
    set_short( "45 ACP round" );
    set_long( "This is a carefully machined 45 ACP round. It is stamped "
      "with the name Vinchester." );
    
    set_weight( 1 );
    set_value( 1 );
    
    set_min_damage( 30 );
    set_ammo_type( "45 ACP" );
}
