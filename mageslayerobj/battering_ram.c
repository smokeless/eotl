//  battering ram -- replaces left arm/tentacle/hoof, etc

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"

void extra_create()
{
    set( "id", ({ "arm", "ram", "battering ram" }) );
    set( "short", "a battering ram" );
    set( "long",
        "This device replaces your entire left arm.  "
        "A hydrolic piston drives a flat plate with tremendous "
        "force, pounding an opponent with a crushing blow.  You may "
        "activate the battering ram during combat, but you must "
        "have a functioning shoulder implant before this prosthetic limb "
        "can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 6600 );
    set( "weight", 2000 );
    set_material( "steel" );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
}

query_areas() { return 0; }

int try_wear( object wearer )
{
    object shunt;

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
    tell_object( wearer, "You socket the battering ram into your shoulder "
        "implant.\n" );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
}

destruct_signal( object dester, object destee )
{
    if( query_worn() )
        post_remove( ENV( THISO ) );
    return ::destruct_signal( dester, destee );
}

varargs string post_short( object me )
{
    if( query_worn() )
        return( " (socketed into shoulder implant)" );
}

extra_init()
{
    add_action( "battering_ram", "activate" );
}

int battering_ram( string arg )
{
    object attacker, victim;
    string aname, vname;
    int dam, ftgcost;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The battering ram must be worn in a "
            "shoulder implant.\n" ), 0 );

    if( !THISP->in_combat() )
        return( notify_fail( "The battering ram is designed to be "
            "used only in combat.\n" ), 0 );

    attacker = THISP;
    victim = attacker->choose_target();
    if( !victim ) 
        return( notify_fail( "The battering ram is designed to be "
            "used only during combat.\n" ), 0 );

    ftgcost = attacker->query_max_fatigue() / 10;
    if( attacker->query_fatigue() < ftgcost )
        return( notify_fail( "You are too exhausted to operate "
            "the battering ram.\n" ), 0 );

    if( time() - query( "last_use" ) < 10 )
        return( notify_fail( "The battering ram's hydraulics need "
            "more time to cool.\n" ), 0 );

    dam = attacker->query_stat( "str" );
    aname = attacker->query_name();
    vname = victim->query_name();
    if( !victim->is_player() )
        dam = 2 * dam + random( dam );

    attacker->add_fatigue( -ftgcost );
    ansi_tell( attacker, sprintf( "Your battering ram thunders "
        "forward, striking %s with a crushing blow!",
        vname ), BOLD_YELLOW );
    ansi_tell( victim, sprintf( "%s smashes you with a blow from "
        "%s shoulder-mounted battering ram!",
        aname, possessive( attacker ) ),
        BOLD_YELLOW );
    ansi_tell_room( ENV( attacker ), sprintf( "%s smashes %s with a "
        "blow from %s shoulder-mounted battering ram!", aname,
        vname,  possessive( attacker ) ), BOLD_YELLOW,
        ({ attacker, victim }) );
    set( "last_use", time() );
    victim->take_damage( dam, 0, "blunt", attacker, 0 );
    return 1;
}

pigs_can_wear() { return 1; }
lobstarbears_can_wear() { return 1; }


//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
