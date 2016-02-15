#include <popcontrol.h>

inherit ArmorCode;

void extra_create()
{
    set_ids( ({ "shirt", "t-shirt" }) );
    
    set_short( "a Ted Nugent t-shirt" );
    
    set_long( "This t-shirt depicts Ted Nugent standing "
      "on the corpses of at least 100 elves. He is holding "
      "his guitar and playing what you can only imagine "
      "to be the most amazing guitar solo of all time." );
    
    set_base_ac( 1 );
    
    set_weight( 50 );
    
    set_areas( ({ "chest", "stomach" }) );
    
    set_material( "cloth" );
    
    set_value( 25 );
}
