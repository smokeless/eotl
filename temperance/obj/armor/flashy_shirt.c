#include <town.h>

inherit ArmorCode;

void extra_create()
{
    set_short( "a stylish cowboy shirt" );
    set_ansi_short( HIK "a stylish cowboy shirt" );
    
    set_ids( ({ "shirt", "cowboy shirt", "stylish cowboy shirt" }) );
      
    set_long( "This shirt is made out of very soft cotton. It is black with "
      "pearl buttons running up the front. The chest has two pockets with arrows "
      "embossed over them. The shoulders are bright purple with the image of "
      "rolling dice stitched onto them." );
    
    set( "value" , 200 );
    set( "weight" , 60 );
    set( "ac" , 6 );
    
    set_material( "cloth" );
    
    set_areas( ({ "chest", "stomach", "right arm", "left arm" }) );
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
   if( arg == "dex" ) return 10;
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
