#include <facility.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

string says;

void extra_create()
{
    string desc;
    
    switch( random( 3 ) )
    {
      case 0 : says = "say Adfackjfak, the pain...";    break;
      case 1 : says = "say Hradmifuga... Why?";         break;
      case 2 : says = "say Tyraoifinn! They must die!"; break;
    }
    
    switch( random( 3 ) )
    {
      case 0 : desc = "Organs and prehensile limbs are held together with "
        "bits of big league chew. Half gimping and half oozing the "
        "creature shudders with horrible agony. What you assume "
        "to be its mouth hangs open. It wails pitifully. "; break;
      case 1 : desc = "Big league chew gives away to pulsating organs. "
        "The creature slurps loudly. Its sticky gum tendrils feel across "
        "the floor. You suddenly realize it is looking for something to "
        "eat. You just hope it won't be you."; break;
      case 2 : desc = "This thing smells like it was born of vomit "
        "and sulphor. It shakes and shudders towards you. The gum wrapped around its "
        "bones muffle the snapping sound of its disjointed movement.";
        break;
    }  
    
    set_name( "a creature" );
    
    add_alias( "heap" );
    add_alias( "gum" );
    add_alias( "organs" );
    add_alias( "creature" );
    add_alias( "sticky gimping creature" );
    add_alias( "sticky" );
    add_alias( "gimping" );
    
    set_short( "a sticky gimping creature" );
    set_ansi_short( RED "a sticky gimping creature" );
    
    set_long( sprintf( "%s", desc ) );   
    
    set_gender( "other" );
    set_race( FRACE "gumrace" );
    
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str" , 100 );
    set_stat( "con" , 50 );
    set_stat( "wil" , 500 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 75 );
    set_skill( "dodge", 65 );
    
    set_type( "asphyxiation" );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_aggressive( 1 );
    
    set_natural_ac( 3 );
    
//  This monster is cloneable by simply
//  using the chemistry set in the lab.
//  To remove incentive for players to 
//  sit and clone it over and over again,
//  I have removed 99% of it's xp value.
    set_percent_bonus_exp( -99 );
    
    add_special_attack( "split", THISO, 2 );
    add_special_attack( "suffocate", THISO, 5 );
    
//  Using call_out instead of MonsterTalk
//  because I only want him to talk once, when
//  cloned.
    call_out( "hello", 1 );
}

split( object vic, object att )
{
    int howmany = 5;
    
    if( howmany < 1 )
      return 1;
    
    object new = clone_object( FMONS "gum" );
    
    ansi_tell_room( ENV( THISO ), "Suddenly the thing begins to split, "
      "there is a sickly sound as it divides itself.", RED );
    
    move_object( new, ENV( THISO ) );
    
    new->attack_object( vic );
    
    howmany--;
    
    return 1;
}

suffocate( object vic, object att )
{
    int dam = random( 35 );
    string player = vic->query_name(); 
    
    ansi_tell_room( ENV( THISO ), sprintf( "The creature wraps around %s! "
      "Gummy tendrils crawling all over %s skin and up through %s nose.",
      vic, possessive( vic ), possessive( vic ) ),
      RED, ({ vic }) );
    
    ansi_tell( vic, "The creature is trying to suffocate you!",
        RED );
    
    vic->add_combat_delay( 3 );
    vic->take_damage( dam, 0, "asphyxiation", att );
    
    return 1;
}

void hello()
{
    command( sprintf( "%s", says ) );
}
