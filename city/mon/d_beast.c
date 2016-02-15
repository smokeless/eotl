#include <city.h>
inherit MonsterCode;
//inherit MonsterNoFlee;
inherit MonsterMove;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_name( "a displacer beast" );
    add_alias( "displacer" );
    add_alias( "beast" );
    set_short( "a displacer beast" );
    set_long( "This is a large cat-like creature " 
      "with six legs and a pair of long tentacles "
      "sprouting from its shoulders. It is covered "
      "in a pelt of blue-black fur. It is about 9 feet "
      "long and weighs roughly 500 pounds." );
    set_gender( "unknown" );
    //set_race();
    
    set_guild( "spellcaster" );
    set_specialization( "illusionist" );
    
    set_skill( "simulacrum", 50 );
    set_skill( "dodge", 50 );
    set_alignment( -4000 );
    set_stat( "chr", 100 );
    set_stat( "int", 200 );
    set_skill( "Silvari", 50 );
    set_skill( "spell casting", 50 );
    set_stat( "str", random( 5000 ) + 200 );
    set_stat( "con", random( 5000 ) + 200 );
    
    set_proficiency( "hands", 75 );
    set_move_rate( 60 );
    set_move_chance( 50 );
    set_aggressive( 3 );
    add_combat_message( "rip", "rips" );
    add_combat_message( "claw", "claws" );
    add_combat_message( "tear", "tears" );
    set_type( "piercing" );
    //set_hit_bonus( 2 );
    set_heal_rate( 30 );
    set_heal_amount( random( THISO->query_max_hp() ) - random( THISO->query_max_hp() ) );
    set_natural_ac( 10 );
    set( "loot", 1 );
    add_money( random( 1000 ) );
    add_special_attack( "init", THISO, 15 );
}

int init( object vic, object att )
{
    if( !vic || !att )
      return 0;
    if( !random( 100 )%2 )
    {
      command( "cast simulacrum", THISO );
      THISO->add_hp( random( THISO->query_max_hp() ) );
      THISO->reset_combat();
      return 1;
    }
    return 0;
}
   
int DeathSequence( object killer, string cause, int nocorpse )
{
    ansi_tell_room( ENV( THISO ), "The displacer beast collapses to "
      "the ground dead.\n", RED, ({ }) );
    int level = THISO->query( "loot" );
    object env = ENV( THISO );
    SERV->loot( level, env );
    return( ::DeathSequence( killer, cause ) );
}
