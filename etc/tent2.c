inherit MonsterCode;

#include <facility.h>

void extra_create()
{
    
    set_name( "tendrils" );
    add_alias( "tendril" );
    add_alias( "tendrils" );
    set_short( "some writhing black tendrils" );
    set_ansi_short ( sprintf( "%ssome writhing black tendrils%s", HIK, NORM ) );
    set_long( "These horrible black tendrils writhe and grip about wildly."
    );
    set_alignment( DEMONIC_AL );
    set_stat( "str" , 200 );
    set_stat( "con" , 300 );
    set_stat( "wil" , 300 );
    set_stat( "dex" , 130 );
    set_skill( "dodge", 65 );
    set( NoStealP );
    set( NoStunP );
    set_natural_ac( 3 );
    set_heal_rate( 30 );
    set_heal_amount( 6 );
    set_max_damage( 10 );
	set_aggressive( 1 );
	add_combat_message( "grope", "gropes" );
	add_combat_message( "slither on", "slither on" );
}    


