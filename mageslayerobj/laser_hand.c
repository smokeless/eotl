//  laser (right hand)

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"

void extra_create()
{
    set( "id", ({ "laser", "small laser" }) );
    set( "short", "a small laser" );
    set( "long",
        "This device replaces your right hand.  Compact and "
        "lightweight, this device recharges itself automatically "
        "from energy siphoned from your body.  During combat, the "
        "pistol-like appendage may be activated to discharge a "
        "burst of energy capable of damaging your current opponent.  "
        "The burst may also have unintended side effects for your "
        "target.  "
        "You must have a functioning wrist implant "
        "before this prosthetic limb can be worn.\n\n"
        "Proficiency class:  pistol" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1500 );
    set( "weight", 50 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set_material( "plastic" );
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
        tell_object( wearer, "Your wrist implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the small laser into your wrist "
        "implant.\n" );
    return 0;
}

int try_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the small laser from your "
            "wrist implant.\n" );

    return 0;
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
        return( " (socketed into wrist implant)" );
}

extra_init()
{
    add_action( "laser", "activate" );
}

int laser( string arg )
{
    object victim, attacker;
    string aname, vname;
    int ftgcost, dam;

    ftgcost = 10;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The small laser must be worn in a "
            "wrist implant.\n" ), 0 );

    if( !THISP->in_combat() )
        return( notify_fail( "The small laser is designed to be "
            "used only in combat.\n" ), 0 );

    attacker = THISP;
    victim = attacker->choose_target();
    if( !victim )
        return( notify_fail( "The small laser is designed to be "
            "used only during combat.\n" ), 0 );

    if( attacker->query_fatigue() < ftgcost )
        return( notify_fail( "You are too exhausted to operate "
            "the small laser.\n" ), 0 );

    if( time() - query( "last_use" ) < 10 ) 
        return( notify_fail( "The components of the small laser need "
            "more time to cool.\n" ), 0 );

    attacker->add_fatigue( -ftgcost );
    aname = attacker->query_name();
    vname = victim->query_name();
    dam = 5 + random( 15 ) + 4 * attacker->query_proficiency( "pistol" );

    ansi_tell( attacker, sprintf( "A brilliant green energy burst "
        "erupts from your handheld laser, streaking directly toward "
        "%s!", vname ), BOLD_GREEN );
    ansi_tell( victim, sprintf( "A brilliant green energy burst "
        "erupts from %s's maimed arm, streaking directly toward you!",
        aname ), BOLD_GREEN );
    ansi_tell_room( ENV( attacker ), sprintf( "A brilliant green energy "
       "burst erupts from %s's maimed arm, streaking directly toward %s!",
       aname, vname ), BOLD_GREEN, ({ attacker, victim }) );
    victim->add_mana( dam );
    victim->take_damage( dam, 0, "energy", attacker, 0 );
    set( "last_use", time() );
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
