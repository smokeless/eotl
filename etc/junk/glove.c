#include <facility.h>

inherit WeaponCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create(){
   set_ids( ({ "gloves", "glove", "dark gloves", "black gloves", 
               "psychic gloves"
   }) );
   set_short("a pair of dark Gloves");
   set_ansi_short( sprintf("%sa pair of dark gloves", BOLD_BLACK) );
   set_long("These gloves make squelching noises as "
            "you handle them. Their surface has some "
            "sort of thick liquid substance coating "
            "it. They seem to have a dull glow to them." 
   );

   set_proficiency( "hands" );
   set_damage_type( "psychic" );
   set_material( "cloth" );
   set_material_name( "Cloth soaked in, something..." );
   set_handed( 2 );
   set(NoStoreP, 1 );
   set(BlessedP, 1 );
   set(NoDisarmP, 1 );
   set(SharpenedP,1 );
set_limit( 1 );
   set_weight( 100 );
   set_fatigue_cost( 10 );
   set_value( 300 );
   set_base_damage( 100 ); //Does base 20 damage
   set_damage_step( 15 ); //For every 15 str add one damage
   set_prof_mod( 35 );     //More damages for more prof.
   set_base_speed( 100 );  // 3 attacks a round and possibly one more
   set_combat_messages( ({"burn", "burns", "grasp", "grasps",
                          "touch", "touches", "sting", "stings"
	                 })
   );
   add_special_attack( "souldrain", THISO, 4);
}

int souldrain( object victim, object attacker)
{
   string vic = victim->query_name();
   string agg = attacker->query_name();
   int attackprof = attacker->query_proficiency( "hands" );
   int attackint = attacker->query_stat( "int" );
//int attackwil = attacker->query_stat( "wil" )+random(100);
   int damage = (to_int( ( attacker->query_stat( "int" ) ) ) +
                 to_int( ( attacker->query_stat( "wil") / 5) + 3) );         
   if(attackprof < 30 || attackint < 50) return 0;
		       
    ansi_tell( attacker, sprintf( "Your gloves reach into the"
                                 " very soul of %s...", vic), BLU);
    ansi_tell( victim, sprintf( "Something horrible shakes your"
                               " very being."), RED);
    ansi_tell_room( ENV( attacker ), sprintf( "%s steams with"
                                              " dark power.", agg), BLU,
		    ({ victim, attacker })
    );
    victim->take_damage( damage, 0, "psychic", attacker, THISO);
		       return 1;
		       }
