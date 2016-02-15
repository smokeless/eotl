#include <facility.h>

inherit ArmorCode;

void extra_create()
{
    set_ids( ({ "shoes", "dress shoes", "polished", "shoe" }) );
    
    set_short( "some polished dress shoes" );
    set_ansi_short( CYN "some polished dress shoes" );
    
    set_long( "Well polished and tidy. The soles have next to "
      "no wear on them at all. They reflect the light in "
      "the room." );
    
    set_base_ac( 2 );
    set_weight( 250 );
    
    set_areas( ([ "left foot" : 2,
      "right foot" : 2 ]) );
    
    set_material( "leather" );
}

