//  Shield arm -- replaces left arm/tentacle/hoof, etc

inherit ShieldCode;
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"

void extra_create()
{
    set( "id", ({ "arm", "shield", "enormous shield" }) );
    set( "short", "an enormous shield" );
    set( "long",
        "This device replaces your entire left arm.  "
        "It consists of a huge metal plate capable of shielding your "
        "entire body.  There are a few short spikes protruding from the "
        "shield's face, and it is so massive it would be impossible to "
        "use were it not attached directly to your body.  You must "
        "have a functioning shoulder implant before this prosthetic limb "
        "can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set_material( "steel" );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set( ShieldP, 1 );    
    set( "value", 850 );
    set( "weight", 1500 );
    set_block_chance( 5 );
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
        tell_object( wearer, "Your shoulder implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the enormous shield into your shoulder "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        wearer->remove_bonus_object( THISO );
}

/*  Removed  11-05  Dorf
query_stat_bonus( string arg )
{
    if( query_worn() && arg == "dex" ) 
        return( - ENV( THISO )->query_base_stat( arg ) / 10 );
}
*/

/*  Removed  3-06  Dorf  to be compatible with new ShieldCode
query_resist_bonus( string arg )
{
    if( query_worn() )
       if( arg == "blunt" || arg == "edged" || arg == "piercing" )
           return 10;
}

query_defensive_bonus()
{
    if( query_worn() )
       return( ENV(THISO)->query_stat( "dex" ) / 4 );
}
*/

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

pigs_can_wear() { return 1; }
lobstarbears_can_wear() { return 1; }

int query_handed()  { return 0; }  // requires implant
check_areas() { return 1; }        // avoids hands_free() check

int query_block_chance( object att, object vic, object weap )
{
    return( ::query_block_chance( att, vic, weap ) + 
        vic->query_skill( "shield" ) / 2 );
}

post_block( object attacker, object victim, object weapon )
{
    tell_object( attacker, sprintf( "Your %s is sliced by "
        "%s's shield spike!\n", attacker->query_hand_name(),
        victim->query_name() || "your opponent" ) );
    tell_room( ENV( victim ), sprintf( "%s's %s is sliced "
        "by the spiked shield!\n", attacker->query_name() ||
        "The attacker", attacker->query_hand_name() ),
        ({ attacker }) );
    attacker->take_damage( 20 + random(victim->query_stat("str")/3),
        0, "piercing", victim, 0, 0 );
}

//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
