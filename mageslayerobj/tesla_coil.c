
//  tesla (left arm)

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"
#define FTGCOST 30
int active;
void do_laser( object attacker, object victim );

void extra_create()
{
    set( "id", ({ "coil", "tesla coil", "arm", "tesla arm",
                  "a tesla coil", "tesla" }) );
    set( "short", "a tesla coil" );
    set( "long",
        "This device replaces your left arm.  This heavy duty "
        "implement generates an incredible amount of power by "
        "siphoning it from your body.  During combat, the "
        "rifle-like appendage may be activated to continuously "
        "discharge a series of electrical bolts "
        "capable of damaging your current opponent.  "
        "The burst may also have unintended side effects for your "
        "target.  Bursts will continue until deactivated."
        "  You must have a functioning shoulder implant "
        "before this prosthetic limb can be worn.\n\n"
        "Proficiency class:  rifle" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1500 );
    set( "weight", 50 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "copper" );
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

     return 0;
}
void post_wear( object wearer )
{
    object shunt;
    shunt = present_clone( SHUNT, wearer );
    shunt->start_using( THISO );
    tell_object( wearer, "You socket the tesla coil into your shoulder "
        "implant.\n" );
    return;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    THISO->no_laser_auto();
    if( wearer )
        tell_object( wearer, "You remove the tesla coil from your "
            "shoulder implant.\n" );

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
        return( " (socketed into shoulder implant)" );
}

extra_init()
{
    add_action( "try_laser", "activate" );
    add_action( "no_laser", "deactivate" );
}

int no_laser( string arg )
{
    if( !arg || !id( arg ) )
        return( notify_fail( "Deactivate what?\n" ), 0 );

    if( !active )
        return( write( "The tesla coil has already been "
            "deactivated.\n" ), 1 );

    active = 0;
    while( find_call_out( "laser" ) != -1 )
        remove_call_out( "laser" );

    ansi_tell( THISP, "You deactivate the tesla coil.", GREEN );
    ansi_tell_room( ENV( THISP ), sprintf( "%s deactivates something "
       "on %s arm.", THISP->query_name() || "Somebody",
       possessive( THISP ) ), GREEN, ({ THISP }) );
    return 1;
}

void no_laser_auto()
{
    object env;

    if( !active ) return;
    active = 0;
    while( find_call_out( "laser" ) != -1 )
        remove_call_out( "laser" );

    if( env = ENV(THISO) )
        if( living( env ) )
            ansi_tell( env, "The tesla coil automatically "
                "deactivates.", GREEN );
        else ansi_tell_room( env, "The tesla coil automatically "
                "deactivates.", GREEN, ({ THISO }) );
    return;
}

int try_laser( string arg )
{
    object victim, attacker;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The tesla coil must be worn in a "
            "shoulder implant.\n" ), 0 );

    if( active )
        return( write( "The tesla coil has already been "
            "activated.\n" ), 1 );

    if( !THISP->in_combat() )
        return( notify_fail( "The tesla coil is designed to be "
            "used only during combat.\n" ), 0 );

    attacker = THISP;
    victim = attacker->choose_target();
    if( !victim )
        return( notify_fail( "The tesla coil is designed to be "
            "used only during combat.\n" ), 0 );

    if( attacker->query_fatigue() < FTGCOST )
        return( notify_fail( "You are too exhausted to operate "
            "the tesla coil.\n" ), 0 );

    if( time() - query( "last_use" ) < 10 )
        return( notify_fail( "The components of the tesla coil need "
            "more time to cool.\n" ), 0 );

    ansi_tell( attacker, "You activate the tesla coil.", YELLOW );
    ansi_tell_room( ENV( attacker ), sprintf( "%s activates something "
       "on %s arm.", THISP->query_name() || "Somebody",
       possessive( THISP ) ), YELLOW, ({ THISP }) );
    active = 1;
    do_laser( attacker, victim );
    return 1;
}

void do_laser( object attacker, object victim )
{
    string aname, vname;
    int dam;

    if( !query_worn() || !THISP->in_combat() || !active ||
        attacker->query_fatigue() < FTGCOST ||
        time() - query( "last_use" ) < 10 )
    {
        no_laser_auto();
        return;
    }

    if( !victim ) victim = attacker->choose_target();
    if( !victim || !attacker->valid_target( victim ) ||
        !victim->attackable( attacker ) )
    {
         no_laser_auto();
         return;
    }

    aname = attacker->query_name() || "Somebody";
    vname = victim->query_name() || "Someone";
    dam = 5 + 4 * attacker->query_proficiency( "rifle" ) +
          random( 6 * attacker->query_proficiency( "rifle" ) );

    attacker->add_fatigue( -FTGCOST );
    ansi_tell( attacker, sprintf( "A crackling electrical burst "
        "erupts from your shoulder-mounted tesla coil, streaking directly "
        "toward %s!", vname ), BOLD_YELLOW );
    ansi_tell( victim, sprintf( "A crackling electrical burst "
        "erupts from %s's maimed arm, streaking directly toward you!",
        aname ), BOLD_YELLOW );
    ansi_tell_room( ENV( attacker ), sprintf( "A crackling electrical "
       "burst erupts from %s's maimed arm, streaking directly toward %s!",
       aname, vname ), BOLD_YELLOW, ({ attacker, victim }) );
    victim->add_mana( dam );
    victim->take_damage( dam, 0, "electric", attacker, 0 );
    set( "last_use", time() );
    call_out( "do_laser", 10, attacker, victim );
    return;
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
