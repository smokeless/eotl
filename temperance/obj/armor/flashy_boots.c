#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a pair of flashy cowboy boots" );
    set_ansi_short( CYAN "a pair of flashy cowboy boots" );
    
    set_ids( ({ "boots", "cowboy boots", "flashy cowboy boots", 
      "pair of flashy cowboy boots" }) );
      
    set_long( "These boots look extremely comfortable. They are crafted "
      "of the softest alligator skin and look brand new. They are embossed "
      "with a sugar skull in flames on the front. The heel of the boots have "
      "embossed flames coming up from them. The toes come to a nice rounded point." );
    
    set( "value" , 200 );
    set( "weight" , 60 );
    set( "ac" , 6 );
    
    set_material( "leather" );
    
    add( "areas" , ({ "left foot", "right foot" }) );
}

void post_wear( object wearer )
{
    wearer->add_bonus_object( THISO );
}

void post_remove( object wearer )
{
    wearer->remove_bonus_object( THISO );
}

int query_stat_bonus( string arg )
{
   if( arg == "chr" ) return 10;
}

int query_resist_bonus()
{
   return 1;
}

int query_skill_bonus( string arg )
{
   if( arg == "flee"            ) return 3;
   if( arg == "evade"           ) return 3;
   if( arg == "dodge"           ) return 3;
   if( arg == "follow"          ) return 3;
}
