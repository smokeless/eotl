#include <ansi.h>

inherit ArmorCode;

void extra_create()
{
   set( "id", ({ "wig", "white wig", "a big ol' white wig",
     "a big ol white wig", "big ol white wig", "big white wig",
     "ol white wig", "a big old white wig", "big old white wig" }) );
   set( "short" , "a big ol' white wig" );
   set_ansi_short( WHITE "a big ol' white wig" NORM );
   set( "long",
     "This volume of the hair in this wig is absurd.  There is no "
     "way anyone could mistake this for real hair.  It is all poofy "
     "and a little curly and 100% awful.  There is no reason to wear "
     "such a thing."
   );

   set( "weight", 5 );
   set( "value", 1 );

   set_material( "cloth" );
   set_material_name( "greasy hair" );

   set( "ac" , 1 );
   add( "areas" , ({ "head" }) );
}

int pigs_can_wear()
{
   return 1;
}
