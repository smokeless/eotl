#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a Stetson hat" );
    set_ansi_short( YEL "a Stetson hat" );
    
    set_ids( ({ "hat", "stetson", "stetson hat" }) );
      
    set_long( "This hat is made of felt. It feels very high quality. "
      "Its black dye has faded in spots due to much exposure to the elements "
      "however beyond that flaw it is still in extremely good shape." );
    
    set( "value" , 50 );
    set( "weight" , 60 );
    set( "ac" , 4 );
    
    set_material( "cloth" );
    
    set_areas( ({ "head" }) );
}
