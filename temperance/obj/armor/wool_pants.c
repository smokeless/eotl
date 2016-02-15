#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a pair of rough wool pants" );
    set_ansi_short( YEL "a pair of rough wool pants" );
    
    set_ids( ({ "pants", "wool pants", "rough wool pants" }) );
      
    set_long( "These pants are made of coarse wool. They are covered "
      "in stains and caked with mud. The cuffs are torn and fraying. "
      "They have no brand name on them and look to be hand made.");
    
    set( "value" , 50 );
    set( "weight" , 60 );
    set( "ac" , 4 );
    
    set_material( "cloth" );
    
    set_areas( ({ "left thigh", "right thigh", "left calf", "right calf" }) );
}
