#include <facility.h>

inherit ArmorCode;

void extra_create()
{
    set_ids( ({ "suit", "business suit", "fancy", "fancy suit" }) );
    
    set_short( "a well tailored suit" );
    set_ansi_short( HIW "a well tailored suit" );
    
    set_long( "The lapels are well creased, and the pants fit "
      "cleanly and properly. Nothing hangs loose, it seems "
      "to adjust to your form. It is comforting and warm. "
      "The tag says \"Males Wearhouse\"." );
    
    set_material( "cloth" );
    
    set_weight( 250 );
    
    set_base_ac( 4 );
    
    set_areas( ({ "left shoulder", "right shoulder", 
      "chest", "stomach", "right arm", "left arm",
      "left thigh", "right thigh", "left calf",
      "right calf" }) );
}
