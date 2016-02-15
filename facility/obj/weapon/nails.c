#include <facility.h>;

inherit WeaponCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_ids( ({ "nails", "nail" }) );
    
    set_short( "a set of five nails" );
    set_ansi_short( RED "a set of five nails" );
    
    set_long( "These nails are completely rusted "
      "and stained in blood. It seems the only way "
      "you could use them as a weapon would be to shove "
      "them through your fingers. Seems like it might "
      "be painful." );
    
    set_proficiency( "hands" );
    
    set_damage_type( "piercing" );
    
    set_material( "steel" );
    
    set_handed( 2 );
    
    set( NoDisarmP, 1 );
    set( NoStoreP, 1 );
    
    set_weight( 25 );
    
    set_fatigue_cost( 10 );
    
    set_base_damage( 30 );
    set_base_speed( 60 );
    set_damage_step( 5 );
    set_speed_step( 10 );
    set_prof_mod( 1 );
    
    set_combat_messages( ({ "stab", "stabs", "thunk", "thunks",
      "gore", "gores", "nail", "nails" }) );
    
    add_special_attack( "ithurts", THISO, 10 );
}

void post_wield( object wearer )
{
    int dam = wearer->query_stat( "str" ) + random( 10 );

    ansi_tell( wearer, "You shove the nails into your skin.", RED );
    
//Deathsequence so that the wearer doesn't incap themselves then have to
//sit around forever while they slowly bleed out.
    if( wearer->query_stat( "str" ) + wearer->query_stat( "con" ) >=
    wearer->query_hp() )
      wearer->DeathSequence( wearer, "pushed a little too hard" );
    
    else 
      wearer->take_damage( dam, 0, "piercing", wearer, THISO );
}

int ithurts( object victim, object attacker )
{
    string vil = victim->query_name();
    string hero = attacker->query_name();
    
    int herodam = attacker->query_proficiency( "hands" ) 
      + random ( 10 );
    int vicdam = attacker->query_stat( "str" ) + random( 50 );
     
    ansi_tell( attacker, sprintf( "You get a nail stuck in %s.", vil), HIR );
    ansi_tell( victim, sprintf( "%s sticks a nail into you.", hero), RED );
    
    ansi_tell_room( ENV( attacker ), sprintf( "%s yowls in pain, one of %s "
      "nails has become stuck in %s.", hero, possessive( attacker ), 
      vil ), RED, ({ victim, attacker }) );
      
    victim->take_damage( vicdam, 0, "piercing", attacker, THISO );
    attacker->take_damage( herodam, 0, "piercing", attacker, THISO );
    
    return 1;
}
