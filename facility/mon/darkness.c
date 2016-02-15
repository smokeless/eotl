#include <facility.h>

inherit MonsterCode;
inherit MonsterMove;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create() 
{
    set_name( "the darkness" );
    
    add_alias( "dark" );
    add_alias( "darkness" );
    add_alias( "creeping" );
    add_alias( "creeping darkness" );
    
    set_short( "a creeping darkness" );
    
    set_long( "An inky black darkness pulsates its way through the "
      "room. There is a chill following behind it. It is darker than " 
      "night itself." );
    
    set_gender( "unknown" );
    
    set_alignment( DEMONIC_AL );
    
    set_stat( "str", 125 );
    set_stat( "con", 200 );
    set_stat( "wil", 200 );
    
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 20 );
    
    set_max_damage( 60 );
    
    set_heal_rate( 5 );
    set_heal_amount( 30 );
    
    set_proficiency( "hands", 70 );
    
    set_move_rate( 15 );
    set_move_chance( 20 );
    set_avoid_props( ({ NoWanderRoomP }) );
    
    set_aggressive( 7 );
    
    add_combat_message( "grasp", "grasps" );
    add_combat_message( "cling to", "clings to");
    
    set_heal_rate( 15 );
    set_heal_amount( 50 );
    
    set_light( -1000 );
}

DeathSequence( object killer, string cause, int nocorpse )
{
    ansi_tell_room( ENV( THISO ), "The darkness is banished.\n",
      HIK, ({ }) );
    return( ::DeathSequence( killer, cause, 1 ) );
}
