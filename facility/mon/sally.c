#include <facility.h>

inherit MonsterCode;

void extra_create()
{
    set_name( "Sally Riedman" );
    
    add_alias( ({ "sally riedman", "receptionist", "reception",
      "sally", "riedman" }) );
      
    set_short( "Sally Riedman" );
    
    set_long( "Sally sits behind the counter clacking away on the "
      "keyboard. She is much taller than most Drow you have seen. "
      "Her lilac eyes are focused on the screen and the work at hand. "
      "She doesn't seem to be paying attention to what is going on around "
      "her." );

    set_alignment( GOOD_AL );
    
    set_race( "drow_elf" );
    set_gender( "female" );
    
    set_stat( "str", 100 );
    set_stat( "int", 200 );
    set_stat( "con", 250 );
    set_stat( "dex", 300 );
    
    set_proficiency( "hands", 100 );
    
    set_heal_rate( 40 );
    set_heal_amount( 30 );
    
    move_object( clone_object( FARMOR "pants" ), THISO );
    move_object( clone_object( FARMOR "shirt" ), THISO );
    command( "equip" );
}
      
