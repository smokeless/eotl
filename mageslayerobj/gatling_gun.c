//  gatling gun arm

inherit WeaponCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;
#include <ansi.h>
#include <combat.h>
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"
#define SHAD    "/zone/guild/mageslayer/obj/hand_shad"

void extra_create()
{
    set( "id", ({ "gun", "gatling gun", "gun arm", "gatling",
                  "mechanical arm", "arm" }) );
    set( "short", "a gatling gun mechanical arm" );
    set( "long",
        "This device replaces your entire left arm.  "
        "It consists of several rotating barrels through which "
        "small round discs (approximately the same size and shape "
        "as a normal coin) may be fired.  You must have a "
        "functioning shoulder implant in order to wield this "
        "prosthetic limb." );
    set_combat_messages( ({ "shoot", "shoots", "blast", "blasts",
                            "fire at", "fires at" }) );
    set( "value", 3000 );
    set( "weight", 1500 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set( NoDisarmP, 1 );
    set_material( "steel" );
    set_proficiency( "rifle" );
    add_special_attack( "shoot_coins", THISO, 100 );
}

int try_wield( object wearer )
{
    object shunt, shad;

    shunt = present_clone( SHUNT, wearer );

    if( !shunt )
    {
        tell_object( wearer, "You don't have the proper implant to "
            "attach that.\n" );
        return 1;
    }

    if( shunt->query_used() )
    {
        tell_object( wearer, "Your shoulder implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the gatling gun mechanical "
        "arm into your shoulder implant.\n" );
    tell_room( ENV( wearer ), sprintf( "%s inserts a gatling gun "
        "mechanical arm into %s shoulder socket.", wearer->query_name(),
        possessive( wearer ) ), ({ wearer }) );
    shad = clone_object( SHAD );
    shad->sh_init( THISP, THISO );
    return 0;
}

void post_unwield( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        tell_object( wearer, "You remove the gatling gun mechanical "
            "arm from your shoulder implant.\n" );
        tell_room( ENV( wearer ), sprintf( "%s removes the mechanical "
            "arm from %s shoulder socket.", wearer->query_name(),
            possessive( wearer ) ), ({ wearer }) );
    }
    return;
}

string post_short( object me )
{
   if( query_wielded() )
       return( " (wielded in shoulder implant)" );
   return "";
}

int shoot_coins( object victim, object attacker )
{
    string aname;
    int roll, dam;
    aname = attacker->query_name();
    roll = attacker->roll_to_hit( victim, THISO );
    dam = attacker->query_proficiency( "rifle" );
    dam = 1 + dam + random( dam );

    if( !attacker->query_money() )
    {
        ansi_tell( attacker, "Your gatling gun makes a clicking sound, "
            "but nothing happens.", LOW_WHITE );
        tell_room( ENV( attacker ), sprintf( "%s's gatling gun makes "
            "a clicking sound, but nothing happens.",
            aname ), ({ attacker }) );
        return 0;
    }

    if( roll == CRITICAL_HIT )
    {
        attacker->add_money( -5 );
        ansi_tell( attacker, "Your gatling gun explodes with a rapid "
            "burst of coinage!", BOLD_YELLOW );
        ansi_tell_room( ENV( attacker ), sprintf( "%s's gatling gun explodes "
            "in a burst of golden fury!", aname ), BOLD_YELLOW,
            ({ attacker }) );
        victim->add_money(5);
        victim->take_damage( 5 * dam, 0, "piercing", attacker, THISO );
        return 1;
    }

    if( roll == HIT )
    {
        attacker->add_money( -1 );
        //  Normal hit, let combat supply the damage message
        victim->add_money( 1 );
        victim->take_damage( dam,
           attacker->get_hit_location( victim ),
           "piercing", attacker, THISO );
        return 1;
    }

    //  miss, but still subtract "ammo" and let combat supply message
    attacker->add_money( -1 );
    victim->take_damage( 0, 0, "piercing", attacker, THISO );
    return 1;
}

int query_speed( object me )  {  return 100; }

int query_handed() { return 0; }


//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
