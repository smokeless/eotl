#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a rough wool shirt" );
    set_ansi_short( YEL "a rough wool shirt" );
    
    set_ids( ({ "shirt", "wool shirt", "rough wool shirt" }) );
      
    set_long( "This shirt is made out of coarse and itchy wool. It is long sleeved "
      "and button up. It is covered in stains and ground in dirt. The sleeves "
      "are frayed at the edges. It has clearly been used for work for quite "
      "sometime." );
    
    set( "value" , 50 );
    set( "weight" , 60 );
    set( "ac" , 4 );
    
    set_material( "cloth" );
    
    set_areas( ({ "chest", "stomach", "right arm", "left arm" }) );
}
