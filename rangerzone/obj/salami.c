#include <ranger.h>
inherit HealCode;

void extra_create()
{
    string desc;
    switch( random( 4 ) )
    {
      case 0 : desc = "venison";        break;
      case 1 : desc = "wild boar";      break;
      case 2 : desc = "alligator meat"; break;
      case 3 : desc = "ostrich meat";   break;
    }
    set( "id", "salami" );
    add( "id", "a salami" );
    add( "id", "hunk" );
    add( "hunk of salami" );
    set( "short", "a hunk of salami" );
    
    set( "long", sprintf( "This salami is well marbled and very hard. "
      "It has been smoked for hours and the outer shell is "
      "thick and crusty. It appears to be made out of %s. "
      "You cannot wait to devour it!", desc ) );
    
    set( "weight", 3 );
    set( "value", 50 );
    
    set( "heal_uses", 2);
    set( "heal_action", "eat" );
    set( "action_message", ({ "You take a huge bite of salami.",
      " eats some salami." }) );
    set( "solid", 1 );
    set( "heal_array", ({ 30, 0, 15 }) );
} 
    
