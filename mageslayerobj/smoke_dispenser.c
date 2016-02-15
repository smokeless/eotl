//  smoke dispenser tail

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/tail_implant"
#define TIME_DELAY  60
int last_use;

void extra_create()
{
    set( "id", ({ "dispenser", "fog dispenser", "fog bomb", "tail" }) );
    set( "short", "a fog dispenser" );
    set( "long",
        "This device protrudes from where your tail might be.  "
        "Activating this device "
        "will release an aerosol spray which will quickly form "
        "a dense, black fog.  This may intermittently conceal any nearby "
        "occupants from the IR and visual spectra, making it difficult "
        "to continue hostile actions.  "
        "You must have a functioning tail implant "
        "before this prosthetic limb can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1100 );
    set( "weight", 50 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "tin" );
    set( "ac", 0 );
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
        tell_object( wearer, "Your tail implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the fog dispenser into your tail "
        "implant.\n" );
    return 0;
}

int try_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the fog dispenser from your "
            "tail implant.\n" );

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
        return( " (socketed into tail implant)" );
}

extra_init()
{
    add_action( "do_use", "activate" );
}

int do_use( string arg )
{
    object smoke;

    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The fog dispenser must be worn in a "
            "tail implant.\n" ), 0 );

    if( time() - last_use < TIME_DELAY )
        return( write( "The fog dispenser needs a few more moments "
            "to recharge.\n" ), 1 );

    last_use = time();

    smoke = clone_object( "/zone/guild/mageslayer/obj/smoke_cloud" );
    smoke->start();
    tell_room( ENV(THISP), "A thick black cloud of fog fills the area.\n" );
    move_object( smoke, ENV(THISP) );    

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
