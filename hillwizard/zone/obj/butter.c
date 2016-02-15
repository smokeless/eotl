#include <ansi.h>

inherit HealCode;

void extra_create()
{
   set( "id", ({ "butter", "stick of butter", "butter stick", 
     "a stick of butter" }) );
   set( "short", "a stick of butter" );
   set( "ansi_short", HIY "a stick of butter" NORM );
   set( "long", 
     "This stick of butter is unwrapped and ready to go.  It "
     "looks... butterily... delicious?  Questionmark?"
   );
   set( "solid", 1 );
   set( "weight", 5 );
   set( "value", 10 );
   set( "heal_array", ({ 25, 0, 0, 1 }) );
   set( "heal_uses", 1 );
   set( "heal_action", "eat" );
   set( "action_msg",({ "You gobble down the entire stick.\n",
     " gobbles down an entire stick of butter.  Eww...\n" }) );
}
