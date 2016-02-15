#include <temple.h>
#define GEN "/usr/taplash/temple/obj/pop"
inherit MonsterCode;

void extra_create()
{
    set_gender( GEN->sex() );
    if( THISO->query_gender() == "female" )
      set_name( sprintf( "%s", GEN->get_female() ) );
    else
      set_name( sprintf( "%s", GEN->get_male() ) );
    
    set_race( GEN->race() );
    
    add_alias( lower_case( THISO->query_name() ) );
    add_alias( lower_case( THISO->query_race() ) );
    set_short( sprintf( "%s, the %s", THISO->query_name(), 
      THISO->query_race() ) );
    
    set_long( sprintf( "%s", GEN->desc() ) );
    set_alignment( GEN->alignment() );
    set_toughness( GEN->toughness() );
}
