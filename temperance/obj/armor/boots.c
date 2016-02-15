#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a pair of cowboy boots" );
    set_ansi_short( YEL "a pair of cowboy boots" );
    
    set_ids( ({ "boots", "cowboy boots" }) );
      
    set_long( "These boots are cracked and dry. It appears they haven't "
      "been oiled in a very long time. The soles are worn down to the nails "
      "and chunks of the brown leather are chunking off. Since they are so "
      "well broken in, they would probably be comfortable." );
    
    set( "value" , 50 );
    set( "weight" , 60 );
    set( "ac" , 4 );
    
    set_material( "leather" );
    
    set_areas( ({ "left foot", "right foot" }) );
}
