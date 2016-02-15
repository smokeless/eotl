#include <facility.h>

inherit MonsterCode;

void extra_create()
{
    
    set_name( "tendrils" );
    
    add_alias( "tendril" );
    add_alias( "tendrils" );
    
    set_short( "some writhing black tendrils" );
    set_ansi_short ( HIK "some writhing black tendrils" );
    
    set_long( "These horrible black tendrils writhe and grip about wildly. "
      "They are covered in a disgusting black ink. They smell of rot and decay. "
      "Briefly you consider that they might be attached to something much bigger." );
    
    set_alignment( DEMONIC_AL );
    
    set_stat( "str" , 50 );
    set_stat( "con" , 300 );
    set_stat( "wil" , 300 );
    set_stat( "dex" , 130 );
    
    set_skill( "dodge", 65 );
    
    set( NoStunP, 1 );
    
    set_natural_ac( 3 );
    
    set_heal_rate( 30 );
    set_heal_amount( 6 );
    
    set_max_damage( 10 );
	
    set_aggressive( 1 );
    
// This thing is cloned from an item.
// I don't want players just cloning
// it endlessly for xp.
    set_percent_bonus_exp( -99 );
	
    add_combat_message( "grope", "gropes" );
    add_combat_message( "slither on", "slither on" );
}    


