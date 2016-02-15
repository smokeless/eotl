//  Tail whip

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/tail_implant"

void extra_create()
{
    set( "id", ({ "tail", "whipcord tail", "whipcord" }) );
    set( "short", "a whipcord tail" );
    set( "long",
        "This device protrudes from where your tail might be.  "
        "The heavy, cable-like cord ends in a blunt ball of metal, "
        "suitable for flailing about.  You can activate the tail "
        "during combat to catch at an opponents feet.  "
        "You must have an operable tail implant in order to wear "
        "this prosthesis." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1000 );
    set( "weight", 150 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set_material( "steel" );
}

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
        tell_object( wearer, "Your tail implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the whipcord tail into your tail "
        "implant.\n" );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the whipcord tail from your "
            "tail implant.\n" );

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
        return( " (socketed into tail implant)" );
}

extra_init()
{
    add_action( "whip", "activate" );
}

status whip( string arg )
{
    object attacker, victim;
    string aname, vname;
    int ftgcost;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The whipcord must first be worn in a "
            "tail implant.\n" ), 0 );

    if( !THISP->in_combat() )
        return( notify_fail( "The whipcord tail is designed to be "
            "used only in combat.\n" ), 0 );

    attacker = THISP;
    victim = attacker->choose_target();
    if( !victim )
        return( notify_fail( "The whipcord tail is designed to be "
            "used only during combat.\n" ), 0 );

    ftgcost = attacker->query_max_fatigue() / 15;
    if( attacker->query_fatigue() < ftgcost )
        return( notify_fail( "You are too exhausted to swing "
            "the whipcord tail.\n" ), 0 );

    if( time() - query( "last_use" ) < 15 ) 
        return( notify_fail( "The whipcord tail's gyroscopes need "
            "more time to realign.\n" ), 0 ); 

    aname = attacker->query_name();
    vname = victim->query_name();

    ansi_tell( attacker, sprintf( "You deftly whip your body in a "
        "tight circle, striking %s with your gyroscopic tail, knocking "
        "%s from %s feet!", vname, objective( victim ), 
        possessive( victim ) ), BOLD_CYAN );
    ansi_tell( victim, sprintf( "%s whips %s body in a tight circle, "
        "striking you with %s tail and knocking you off of your feet!",
        aname, possessive( attacker ), possessive( attacker ) ),
        BOLD_CYAN );
    ansi_tell_room( ENV( attacker ), sprintf( "%s whips %s body in a "
        "tight circle, striking out with a tail and knocking %s from "
        "%s feet!", aname, possessive( attacker ), vname, 
        possessive( victim ) ), BOLD_CYAN, ({ attacker, victim }) );
    if( victim->query( NoStunP ) )
    {
        tell_room( ENV( attacker ), sprintf( "%s springs right back "
           "up!\n", vname ), ({ victim }) );
        tell_object( victim, "You spring right back up!\n" );
    }
    else
    victim->add_combat_delay( MIN( 2+attacker->query_stat("dex")/50, 6));

    set( "last_use", time() );
    attacker->add_fatigue( - ftgcost );
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
