inherit ArmorCode;

#include <facility.h>

void extra_create()
{
    int colors = random( 4 );
    string shirtsay;
    string color;
    string ansishirt;

    switch( random( 4 ) )
    {
      case 0 : shirtsay = "Facility 31, a better future.";                 break;
      case 1 : shirtsay = "Facility 31, we are psychic research.";         break;
      case 2 : shirtsay = "Facility 31, where necromancers don't dare.";   break;
      case 3 : shirtsay = "Facility 31, innovation in science and magic."; break;
    }
    switch( colors )
    {
      case 0 : color = "blue"; ansishirt = BLU;   break;
      case 1 : color = "yellow"; ansishirt = YEL; break;
      case 2 : color = "black"; ansishirt = HIK;  break;
      case 3 : color = "green"; ansishirt = GRN;  break;
    }
  
    set_ids( ({ "shirt", "facility shirt", "facility 31 shirt" }) );
    
    set_short( sprintf( "a %s Facility 31 shirt", color ) );
    set_ansi_short( sprintf( "%sa %s Facility 31 shirt", ansishirt, color ) );
    
    set_long( sprintf( "This is a standard issue Facility 31 shirt. " 
      "This one says: %s", shirtsay ) );
    
    set_base_ac( 1 );
    
    set_weight( 50 );
    
    set_areas( ({ "chest", "stomach" }) );
    
    set_material( "cloth" );
    
    set_value( 25 );
}
   
