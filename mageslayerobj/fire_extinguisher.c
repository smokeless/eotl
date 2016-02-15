//  smoke dispenser (right hand)

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"
#define TIME_DELAY  120
int last_use;

void extra_create()
{
    set( "id", ({ "extinguisher", "fire extinguisher", "hand", "attachment",
         "fire extinguisher attachment", "extinguisher attachment", 
         "fire attachment" }) );
    set( "short", "a fire extinguisher attachment" );
    set( "long",
        "This device replaces your right hand.  Activating this device "
        "will release a smothering blanket of foam which will quickly "
        "protect the occupants of the room from nearby fires.  The foam "
        "will gradually dissipate, "
        "and the extinguisher will need plenty of time to recharge between "
        "uses.  "
        "You must have a functioning wrist implant "
        "before this prosthetic limb can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1100 );
    set( "weight", 50 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "steel" );
    set_ac( 0 );
    last_use = 0;
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
    tell_object( wearer, "You socket the fire extinguisher into your wrist "
        "implant.\n" );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the fire extinguisher from your "
            "wrist implant.\n" );

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
    add_action( "do_use", "activate" );
}

int do_use( string arg )
{
    object foam;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The fire extinguisher must be worn in a "
            "wrist implant.\n" ), 0 );

    if( time() - last_use < TIME_DELAY )
        return( write( "The fire extinguisher needs a few more moments "
            "to recharge.\n" ), 1 );

    last_use = time();

    foam = clone_object( "/zone/guild/mageslayer/obj/foam" );
    tell_room( ENV(THISP), "A thick spray of foam blankets you, the floor, "
        "and everything nearby.\n" );
    move_object( foam, ENV(THISP) );    

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
