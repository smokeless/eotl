/*  Simple code for a basic knife.
    Shibame 2014.01.16  */
    
inherit WeaponCode;
inherit SpecialAttackCode;

#include <ansi.h>

void extra_create()
{
    set_ids( ({ "pen", "aluminium pen", "an aluminium pen", "parker",
        "parker jotter", "jotter", "parker pen", "a parker pen",
        "jotter pen", "a jotter pen", "a parker jotter", "knife" }) );
    set_short( "an aluminium pen" );
    set_long( "You hold in your hand a metallic pen made of aluminium. "
        "The pen is about five inches long, and surfaced entirely with "
        "a brushed steel texture. There is a clicker button at the top, "
        "and a pocket clip attached near it. The pen feels quite hefty "
        "and very sturdy in your hand, inspiring confidence in both its "
        "handling and your writing abilities. " );
    set( "id_short", "an all-aluminium Parker Jotter pen" );
    set( "id_long", "You hold in your hand a metallic pen made of "
        "aluminium. The pen is about five inches long, and surfaced "
        "entirely with a brushed steel texture. There is a clicker "
        "button at the top, and a pocket clip attached near it. The pen "
        "feels quite hefty and very sturdy in your hand, inspiring "
        "confidence in both its handling and your writing abilities.\n\n"
        "A pen in hand is a self-defense tool of last resort. Being small "
        "and concealable, a sturdy pen serves great utility without "
        "raising suspicion. This particular model is an all-aluminium "
        "Parker Jotter. Weighing little more than two ounces, the Jotter "
        "also features all-metal tungsten-tipped refills. When used in "
        "self-defense, the pen is held in a closed fist like an icepick, "
        "with the thumb covering the clicker top and the sharp tip "
        "extending below the little finger. Use of this weapon requires "
        "a sharp mind, excellent skill and quick reflexes. The necessarily "
        "aggressive fighting style precludes the use of shields, yet "
        "requires the keen ability to block attacks using the free hand. " );
    set_descs( ([
        ({ "clicker", "button" }) : "At the top of the pen is a highly-"
            "polished clicker button. The button feels smooth and "
            "responsive, the clicking action positive and satisfying. " ,
        ({ "clip", "clipper", "pen clip" }) : "Like the button on top, "
            "the clip is highly-polished. Fastened to your pocket, you " 
            "can be sure your aluminium pen isn't going anywhere. " ]) );

    set_value( 500 );
    set_weight( 6 );
    set_droppable( 1 );
    set_gettable( 1 );
    set_material( "metal" );
    set_material_name( "aluminium and tungsten" );
    
    set_base_damage( 35 );
    set_base_speed ( 20 );
    set_damage_step( 15 );
    set_speed_step( 7 );
    set_prof_mod( 9 );
    set_fatigue_cost( 5 );
    set_proficiency( "knife" );
    set_damage_type( "piercing" );
    set_handed( 1 );
    set_combat_messages( ({
        "stab", "stabs",        "jab", "jabs",
        "pierce", "pierces",    "shank", "shanks",
        "gash", "gashes",       "puncture", "punctures",
        "stick", "sticks",      "wound", "wounds",
        "jag", "jags",          "impale", "impales",
        "plunge", "plunges" }) );
        
    add_special_attack( "do_delay", THISO, 5 );
}

int try_wield( object wielder )
{
    if ( wielder->query_stat( "int" ) < 250 )
    {    
        tell_player( wielder, "Your mind is not sharp enough to use "
            "this weapon effectively. " );
        return 1;
    }
    
    if ( wielder->query_stat( "dex" ) < 250 )
    {
        tell_player( wielder, "You are not swift enough to use "
            "this weapon effectively. " );
        return 1;
    }
    
    if ( wielder->query_proficiency( "knife" ) < 40 )
    {
        tell_player( wielder, "You are not proficient enough to use "
            "this weapon effectively. " );
        return 1;
    }
    
    if ( wielder->query_skill( "shield" ) < 35 )
    {
        tell_player( wielder, "You are not skilled enough in blocking "
            "to use this weapon effectively. " );
        return 1;
    }
    
    if ( sizeof( THISP->query_shields() ) != 0 )
    {
        tell_player( wielder, "You can not use this weapon while wearing "
            "a shield. " );
        return 1;
    }
    
    tell_player( wielder, "You wield the pen confidently in your hand. " );
    return 0;
}

/*  void post_wield( object who )
{
}
*/

/*  status try_unwield()
{
    return 0;
}
*/

void post_unwield( object wielder )
{
    tell_player( wielder, "You put away your pen." );
}

int do_delay( object victim, object attacker )
{
    string vic = victim->query_name();
    string att = attacker->query_name();
    int damage = THISO->query_max_damage() * 8 / 10 ;
    string patt = possessive( attacker );
    string pvic = possessive( victim );
    
    tell_player( attacker, "Dodging carefully, you step into "+vic+"'s circle "
        "of defense and STAB at a pressure point on "+pvic+" body!" );
    tell_object( victim, "Dodging carefully, " +att+ " steps inside "
        "your circle of defense and STABS at a pressure point in your body!" );
    tell_room( ENV( attacker ), "Dodging carefully, "+att+" steps inside "
        +vic+"'s circle of defense and STABS at a pressure point on "
        +pvic+ " body!\n", ({ attacker, victim }) );
    victim->take_damage( damage, 0, "piercing", attacker, THISO );
    victim->add_combat_delay( 2 );
}

int can_wear( object me, object ob )
{
    if( ob->query( ShieldP ) )
    {  
      tell_player( me, "Not with this pen." );
      return( 0 );
    }
    
    return 1;
}    
