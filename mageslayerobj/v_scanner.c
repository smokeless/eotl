//  scanner : eye implant

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/eye_implant"

void extra_create()
{
    set( "id", ({ "eye", "eyeball", "blue eyeball",
                  "scanner", "vitality scanner", "blue eye" }) );
    set( "short", "a blue eyeball" );
    set( "long",
        "Using biometric measurements, this device can scan an opponent "
        "and produce an evaluation of the relative "
        "health of your current target.  The scanner may be activated "
        "any time during combat, but you must have a functioning "
        "eye implant before this prosthetic device can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 7000 );
    set( "weight", 5 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set_material( "glass" );
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
        tell_object( wearer, "Your eye implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the vitality scanner into your eye "
        "implant.\n" );

    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the vitality scanner from your "
            "eye implant.\n" );

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
        return( " (socketed into eye implant)" );
}

extra_init()
{
    add_action( "scan", "activate" );
}

status scan( string arg )
{
    object attacker, victim;
    int hp;
    string aname, vname;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The vitality scanner must first be worn in an "
            "eye implant.\n" ), 0 );

    if( !THISP->in_combat() )
        return( notify_fail( "The vitality scanner is designed to operate "
            "only in combat.\n" ), 0 );

    attacker = THISP;
    victim = attacker->choose_target();
    if( !victim )
        return( notify_fail( "The vitality scanner is designed to operate "
            "only during combat.\n" ), 0 );

    aname = attacker->query_name();
    vname = victim->query_name();

    ansi_tell( attacker, sprintf( "A blue light shines from your "
        "prosthetic eyeball, scanning %s from top to bottom.",
        vname ), BOLD_BLUE );
    ansi_tell( victim, sprintf( "A blue light shines from %s's eye, "
        "illuminating you from head to toe.", aname ), BOLD_BLUE );
    ansi_tell_room( ENV( attacker ), sprintf( "A blue light shines "
       "from %s's eyeball, illuminating %s.",
       aname, vname ), BOLD_BLUE, ({ attacker, victim }) );
    hp = victim->query_hp();
    hp = hp + random( hp / 10 ) - random( hp / 10 );
    ansi_tell( attacker, sprintf( "Scan results:  %s has approximately "
       "%d hitpoints, with a 10 percent margin of error.", 
       CAP( victim->query_real_name() ), hp ), LOW_BLUE );
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
