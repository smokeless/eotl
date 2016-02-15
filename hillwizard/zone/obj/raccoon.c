inherit WeaponCode;

extra_create()
{
   add( "ids", ({ "a dead raccoon", "dead raccoon",
     "raccoon", }) );
   set( "short", "a dead raccoon" );
   set( "long",
     "A dead raccoon isn't really considered a weapon by most "
     "people, but with hillbillies you never know exactly what "
     "they think is acceptable.  There is no way you should be "
     "wielding a raccoon in combat unless you've got the mullet "
     "to go along with it.  Also it's startin' to smell pretty "
     "bad."
   );

   set_proficiency( "light flail" );
   set_damage_type( "blunt" );
   set_material( "organic" );
   set_material_name( "raccoon corpse" );
   set_handed( 1 );
   set_fatigue_cost( 1 );
   set_value( 1 );
   set_weight( 75 );

   set_base_damage( 15 );
   set_damage_step( 7 );
   set_prof_damage_mod( 10 );

   set_base_speed( 40 );
   set_speed_step( 5 );
   set_prof_speed_mod( 15 );

   add_combat_message( ({ "thump",      "thumps"       }) );
   add_combat_message( ({ "thwap",      "thwaps"       }) );
   add_combat_message( ({ "wallop",     "wallops"      }) );
   add_combat_message( ({ "coonsmash",  "coonsmashes"  }) );
}
