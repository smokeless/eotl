#include <popcontrol.h>

inherit WeaponCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_ids( ({ "boom stick", "shotgun", "rusty shotgun", "boomstick" }) );
    
    set_short( "a rusty boom stick" );
    
    set_long( "The metal on both barrels of this shotgun are pocked "
      "and pitted. The rust covers the gun like moss on a tree. The "
      "walnut stock hasn't been oiled in ages and is dry and cracking. "
      "The trigger guard has been broken off at some point, and you take "
      "note that there is no safety." );
    
    set( BlessedP, 1 );
    
    set_material( "steel" );
    set_material_name( "pock marked steel" );
    
    set_proficiency( "rifle" );
    set_damage_type( "piercing" );
    
    set_handed( 2 );
    
    set_weight( 300 );
    set_value( 300 );
    
    set_base_damage( 20 );
    set_base_speed( 25 );
    set_damage_step( 500 );
    set_speed_step( 10 );
    set_prof_mod( 3 );
    set_fatigue_cost( 15 );
    
    set_combat_messages( ({ "blast", "blasts", "fire", "fires",
      "shoot", "shoots" }) );
      
    add_special_attack( "blast", THISO, 10);
}

int blast( object victim, object attacker)
{
    string vic = victim->query_name();
    string agg = attacker->query_name();
    
    int dam = attacker->query_stat( "wil" ) + 
      ( attacker->query_stat( "dex" ) / 5 ) + random( 30 );    
               
    ansi_tell( attacker, sprintf( "You've had enough of this! You "
      "unload both barrels into %s", vic ), RED );
    
    ansi_tell( victim, sprintf( "%s empties both barrels into you!", 
      agg ), RED );
    
    ansi_tell_room( ENV( attacker ), sprintf( "%s blasts %s "
       "with both barrels!", agg , vic ), RED,   
       ({ victim, attacker })  );
    
    victim->take_damage( dam, 0, "blunt", attacker, THISO);
    object shad = clone_object( PSHAD "blastedshad.c");
    shad->sh_init( victim );
    
    return 1;
}
