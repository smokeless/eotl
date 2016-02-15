/* Originally coded by Morph back when swordsmen were first going to come up */
/* Fixed a few bugs and added a few functions -- Dark 8/97                   */
/* Fixed a few bugs -- Peaches Aug '01 */
/* Made it so NoBlockP weapons or people can't be parried -- Valentino 4/03 */
/* and so NoDisarmP weapons can't be disarmed, NoBreakP weapons can't be */
/* broken */

#include "../defs.h"

#define MAXODDS 95
#define VALID_PROFS ({ "light sword", "light axe", "light club", \
                       "knife", "heavy axe", "hands", \
                       "light polearm", "heavy polearm" })
#define ALLOWED_RIPOSTE_TYPES ({ "thrusting", \
                                 "piercing" \
                              })

#define HANDS( o ) o->query_hand_name()+( o->query_weapon()->query_handed() <= 1 ? "" : "s" )

object swordsman, primary, secondary, in_use, *riposte_weapons;
int percent, parry_skill, s_str, s_prof, sec_damage, riposte_skill;
string s_name, poss_s, wep_name;
int sec_attacked;
string *wp_ids;

sh_init( object s, object w1, object w2, int per )
{
    shadow( s, 1 );
    swordsman = s;
    primary = w1;
    in_use = primary;
    secondary = w2;
    percent = per;
    s_name = capitalize( swordsman->query_name() );
    reset();
}   

query_florentine()
{
    return 1;
}

kill_florentine()
{
    unshadow();
    destruct( THISO );
}

quit(int i)
{
    if( objectp( secondary ) )
        secondary->remove_florentine();

    return swordsman->quit( i );
}

object query_secondary()
{
    return secondary;
}

hands_free()
{
    return( swordsman->hands_free() - ( objectp( secondary ) ?
                                      secondary->query_handed() : 0 ) );
}

check_damage_type( string t, object w )
{
    return( w->query_damage_type() == t );
}

allowed_riposte_weapon( object w )
{
    return(sizeof(filter(ALLOWED_RIPOSTE_TYPES,#'check_damage_type,w)));
}

reset()
{
    if( !clonep( THISO ) || !primary || !secondary || !swordsman )
        return;
    primary->get_vars( swordsman );
    secondary->get_vars( swordsman );

    s_str = swordsman->query_stat( "str" );
    s_prof = swordsman->query_proficiency( 
      secondary->query_proficiency() );
    sec_damage = secondary->query_max_damage();

    parry_skill = swordsman->query_skill( "florentine" ) * 2;
    riposte_skill = swordsman->query_skill( "riposte" );

    if( !sizeof(
           riposte_weapons = filter(
             ({primary,secondary}),#'allowed_riposte_weapon) ) )
        riposte_skill = 0;

    wp_ids = secondary->query_ids()+secondary->query("id");
    wp_ids -= ({ 0 });
    if(sizeof(wp_ids))
        wep_name = wp_ids[0];
    else
        wep_name = secondary->short();

    poss_s = possessive( swordsman );
}

change_percent( int per )
{
    percent = per;
}

query_percent()
{
    return percent;
}

varargs int
take_damage( int damage, int loke, string type, object attacker, object weapon, int always )
{
    string prof, a_name, a_wep, *locs, sec_type, *rooms;
    int hit_chance, i, dam_reduce, dam, a_str, a_prof, 
        loc, odds, tdreturn;
    object riposte_wep;

    if( !objectp( attacker ) || (attacker == swordsman))
        return( swordsman->take_damage( damage, loke, type, attacker,
            weapon, always ) );

    if( swordsman->query_weapon() != in_use ) {
        if( objectp( secondary ) )
            secondary->remove_florentine();
        tdreturn=
          swordsman->take_damage( damage, loke, type, attacker, weapon, always );
        if( swordsman ) kill_florentine();
        else destruct( THISO );
        return( tdreturn );
    }
    if( !objectp( secondary ) || ENV( secondary ) != swordsman ) {
        tdreturn=
          swordsman->take_damage( damage, loke, type, attacker, weapon, always );
        if( swordsman ) kill_florentine();
        else destruct( THISO );
        return( tdreturn );
    }

    if( ENV( attacker ) && ENV( attacker )->query( "exits" ) )
        rooms = m_indices( ENV( attacker )->query( "exits" ) );

    if( !objectp( weapon ) )
        return( swordsman->take_damage( damage, loke, type, attacker,
            weapon, always ) );

    if( objectp( weapon ) && !weapon->query( WeaponP ) )
        prof = "hands";
    else 
        prof = ( objectp( weapon ) ? weapon->query_proficiency() : "No Weapon" );

    a_name = attacker->query_name();
    a_str = attacker->query_stat( "str" );
    a_prof = attacker->query_proficiency( prof );

    if ( weapon && weapon->query_ids() )
        a_wep = weapon->query_ids()[0];
    else a_wep = weapon->short();

    if( member( VALID_PROFS, secondary->query_proficiency() ) == -1 )
        return( swordsman->take_damage( damage, loke, type, attacker,
            weapon, always ) );

    odds = percent+(parry_skill/2);
    odds = MIN( odds, MAXODDS );

    if( member( VALID_PROFS, prof ) == -1   ||
      always                                ||
      swordsman->query_fatigue() < 1        ||
      swordsman->query_hp() < 1             ||
      swordsman->query_combat_delay()       ||
      ( swordsman->query_hit_delay() > 1 )  ||
      random( 100 ) + 1 > odds              ||
      ( weapon->query(NoBlockP) )           ||
      ( attacker->query(NoBlockP) ) )
        return( swordsman->take_damage( damage, loke, type, attacker,
            weapon, always ) );

    swordsman->add_fatigue( -swordsman->compute_fatigue( secondary ) );

    if( ( ( random( percent ) + random( parry_skill ) ) < 50 ) )
    { /* Not a full parry, reduced damage. */ 
        atell( swordsman, 
          sprintf( "You try to block %s's attack, but "
            "only manage to slow it a little.", a_name ), HIY );
        tell_room( ENV( swordsman ), 
          sprintf( "%s swings %s %s, slowing %s's "
            "attack.\n", s_name, poss_s, wep_name, a_name ), 
          ({ attacker, swordsman }) );
        atell( attacker, sprintf( "%s swings %s %s, slowing your "
            "attack.", s_name, poss_s, wep_name ), HIY );

        return( swordsman->take_damage( random( damage )+1, loke, type, attacker,
            weapon ) );
    }

    atell( swordsman, sprintf( "You swing your %s, stopping %s's feeble "
        "attack.", wep_name, a_name ), HIR );
    tell_room( ENV( swordsman ), sprintf( 
        "%s swings %s %s, blocking %s's "
        "feeble attack.\n", s_name, poss_s, wep_name, a_name ), 
      ({ attacker, swordsman }) );
    atell( attacker, sprintf( "%s swings %s %s, blocking your feeble "
        "attack.", s_name, poss_s, wep_name ), HIR );

    if( ( riposte_skill > ( random( 40 ) + random( 20 ) ) ) ) {
        if( objectp( weapon ) && swordsman->query_fatigue() ) {
            riposte_wep = (member(riposte_weapons,secondary)!=-1?secondary:primary);

            swordsman->add_fatigue( -swordsman->compute_fatigue( riposte_wep ) );

            atell( swordsman, "You see an opening and riposte!", HIC );
            atell( attacker, s_name+" lunges at you with "+poss_s+" "+
              (riposte_wep==secondary?"secondary":"main")+" weapon!", HIR );
            tell_room( ENV( swordsman ), s_name+" lunges at "+a_name+
              ".\n", ({ swordsman,attacker }) );

            attacker->take_damage( random( riposte_skill )+random(riposte_skill)+
              random( riposte_wep->query_max_damage() ), swordsman->get_hit_location( attacker ),
              riposte_wep->query_damage_type(), swordsman, riposte_wep );
//          swordsman->add_hit_delay(1);
        }
    }

    if( living( attacker ) && objectp( secondary ) && prof == "hands" && !random( 3 ) )
    {
        locs = attacker->query_hit_locations();
        dam = random( secondary->query_max_damage() );
        sec_type = secondary->query_damage_type();

        switch( random( 4 ) )
        {
        case 0 : loc = member( locs, "left arm" );
            break;
        case 1 : loc = member( locs, "left hand" );
            break;
        case 2 : loc = member( locs, "right arm" );
            break;
        case 3 : loc = member( locs, "right hand" );
            break;
        }

        if( loc == -1 )
            switch( random( 4 ) )
        {
        case 0 : loc = member( locs, "tentacle *1" );
            break;
        case 1 : loc = member( locs, "tentacle *2" );
            break;
        case 2 : loc = member( locs, "tentacle *3" );
            break;
        case 3 : loc = member( locs, "tentacle *4" );
            break;
        }

        if( loc == -1 )
            loc = 0;

        tell_object( attacker, sprintf( "You get cut by %s's %s!\n", 
            s_name, wep_name ) );
        tell_object( swordsman, sprintf( "%s gets cut on your %s!\n", 
            a_name, wep_name ) );
        tell_room( ENV( attacker ), sprintf( "%s gets cut on %s's %s!\n", 
            a_name, s_name, wep_name ), 
          ({ swordsman, attacker }) );

        attacker->take_damage( dam, loc, sec_type, swordsman, secondary );
    }

//  if( weapon && prof != "hands" && !(weapon->query(NoBreakP)) )
//  { /* Damage weapon */
//      weapon->check_break();
//      weapon->check_break();
//      weapon->check_break();
//  } /* Damage weapon */

    if( objectp( swordsman ) && !swordsman->query_ghost() )
        return swordsman->take_damage( 0, loke, type, attacker, weapon );

    return 1;
} /* Take damage */

retrieve_weapon( object monster )
{
    object weapon;

    if( !monster || monster->query_weapon() )
        return;

    if( weapon = present( "weapon", monster ) )
    {
        monster->wield_weapon( weapon );
        return;
    }

    if( weapon = present( "weapon", ENV(monster) ) );
    {
        command( "get weapon", monster );
        call_out( "retrieve_weapon", random( 5 ), monster );
    }
}

unwield_primary()
{
    swordsman->set_weapon(0);
    call_out( "do_switch_weapons", 1 );
}

do_switch_weapons()
{
    if( objectp( secondary ) && ENV( secondary ) == swordsman )
    {
        atell( swordsman, "After finding your main weapon unwielded, you "
          "switch your secondary weapon to your main hand!", HIB );

        secondary->remove_florentine();

        set_weapon( secondary );

        THISO->kill_florentine();
    }
}

varargs attack( int noattack ) {
    string old_short, sec_short;

    if( noattack == 1 ) {
        sec_attacked = 0;
        return 1;
    }

    if( !objectp( swordsman->query_weapon() ) && objectp( secondary ) )
    {
        do_switch_weapons();
        return;
    }

    if( swordsman && !objectp( swordsman->query_weapon() ) )
    {
        tell_object( swordsman, strformat( "You start beating your enemies "
            "with your fists, since you seem to have stopped wielding a "
            "weapon." ) );
        swordsman->attack();
        THISO->kill_florentine();
        return;
    }

    swordsman->set_weapon( primary );

    if( !swordsman->attack() || !swordsman ||
        swordsman->query_delay() ||
        !swordsman->choose_target( swordsman->query_mercy() ) )
        return;

    if( secondary )
        if( ( sec_attacked >= secondary->query_speed() / 10 ) ||
            ( percent > 70  ) ||
            ( percent > 30 && sec_attacked ) ||
            ( sec_attacked > 1 ) ||
            ( sec_attacked && secondary->query( "proficiency" ) == "pistol" ) )
            return;

    sec_attacked++;

    atell( swordsman, "You attack with your " + wep_name + ".",
      HIB );
    tell_room( ENV( swordsman ), sprintf( "%s attacks with %s %s.\n",
        s_name, poss_s, wep_name ), ({ swordsman }) );
    swordsman->set_weapon( secondary );
    in_use = secondary;
    swordsman->attack();
    if( !swordsman )
        return;
    swordsman->set_weapon( primary );
    in_use = primary;
}

clear_sec_attacked() { sec_attacked = 0; }

query_attacks()
{
    int atks;

    atks = swordsman->query_attacks();

    if( percent < 30 )
        return atks+1+random(2);

    if( percent > 30 && percent < 70 )
        return( ( atks / 2 ) + ( ( atks % 2 ) ? 1+random(2) : 0 ) );

    return 1+random(2);
}

// Update our primary weapon
void set_weapon(object ob)
{
    if( !ob )
        unwield_primary();
    else
    {
        primary = ob;
        in_use = primary;
        tell_object(swordsman,"You wield "+primary->short()+".\n");
        swordsman->set_weapon(ob);
    }
}

int query_no_wield(object ob)
{
    if( ob == secondary )
    {
        tell_object(swordsman,"That is already your secondary weapon!\n");
        return 1;
    }
}
