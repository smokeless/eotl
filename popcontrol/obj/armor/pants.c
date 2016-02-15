#include <popcontrol.h>

inherit ArmorCode;

void extra_create()
{
    set_ids( ({ "pants", "pant" }) );
    
    set_short( "a pair of pants" );
    
    set_long( "A generic pair of cotton pants. The fabric feels thin and "
      "poorly stitched. Not the first choice for adventuring, but adequate "
      "for day to day tasks." );
    
    set_base_ac( 1 );
    set_weight( 100 );
    
    set_areas( ({ "left thigh", "right thigh", "left calf", 
      "right calf" }) );
    
    set_material( "cloth" );
    
    set_value( 30 );
}    
