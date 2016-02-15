#include <town.h>

inherit GunCode;

void extra_create()
{
    set_ids( ({ "gun", "pistol", "old pistol", "revolver",  }) );
    set_short( "an old revolver" );
    set_long( "This is an old revolver. The grips are made of ivory and the "
      "barrel extends out six inches from the chambers. Its maximum capacity "
      "is 6 rounds. It seems that it would be able to empty all those rounds "
      "very quickly, but might reload a bit slow. The trigger guard has been "
      "completely removed and the hammer is well worn." );
    
    set_base_damage( 20 );
    set_base_speed( 2 );
    set_damage_step( 500 );
    set_speed_step( 5 );
    set_prof_mod( 2 );
    set_proficiency( "pistol" );
    
    set_fatigue_cost( 2 );
    set_handed( 1 );
    set_combat_messages( ({ "blast", "blasts", "fire", "fires",
      "shoot", "shoots" }) );
    
    set_mag_fed( 0 );
    set_capacity( 6 );
    set_ammo_type( "45 ACP" );
    set_jam_delay( 2 );
    set_op_delay( 3 );
    set_recoil( 1 );
    set_reliability( 50 );
    set_weight( 12 );
    set_value( 100 );
}
