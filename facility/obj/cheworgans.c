#include <facility.h>

inherit HealingCode;

void extra_create()
{ 
    set( "id", ({ "organs", "organ", "fermented", "fermented organs" })
      );
    
    set( "short","some chewy fermented organs" );
    
    set( "long", "These are the entrails of some lesser creature. "
      "They smell terrible, and are held together with bits of "
      "gum. There has to be something better to chew on." );
    
    set( "heal_uses", 1 );
   
    set( "weight", 300 );
    
    set( "value", 1 );
    
    set( "heal_action", "chew" );
    
    set( "action_msg", ({ "You plug your nose and chew on the " 
      "horrible mess of liquified organs and gum. The juices are disgusting.", 
      " masticates some fermented organs." }) );
    
    set( "heal_array", ({ 10, 10, 10, 1 }) );
}
