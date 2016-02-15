//  summons android dropship

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/eye_implant"
#define DS_BAY  "/zone/guild/mageslayer/room/dropdock"

void extra_create()
{
    set( "id", ({ "eye", "transmitter", "radio transmitter", "radio",
                  "radio eyeball", "eyeball", "metallic", "metallic eyeball",
                  "metallic eye" }) );
    set( "short", "a metallic eyeball" );
    set( "long",
        "This device can be socketed as a false eye.  When activated, "
        "it transmits your GPS coordinates to the guild's newly commissioned "
        "dropship.  You must have "
        "a functioning eye implant "
        "before this prosthetic device can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1800 );
    set( "weight", 100 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "copper" );
    set_ac( 0 );
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
        tell_object( wearer, "Your eye implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the metallic eyeball into your eye "
        "implant.\n" );
    return 0;
}

int try_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the metallic eyeball from your "
            "eye implant.\n" );

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
        return( " (socketed into eye implant)" );
}

extra_init()
{
    add_action( "do_call", "activate" );
}

int do_call( string arg )
{
    object dropdock;

    if( !arg || !id(arg) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The metallic eyeball must first be worn in a "
            "eye implant.\n" ), 0 );

    if( ENV( THISP )->query( NoTeleportP ) ||
        ENV( THISP )->query( NoTeleportOutP ) ||
        THISP->query_guild() != "mageslayer" )
        return( notify_fail( "You try to transmit your location, but "
           "all you get is static.\n" ), 1 );

    //  code cut right from android module, with minor tweaks
    DS_BAY->some_wanker_function();
    dropdock=find_object(DS_BAY);
    write("You transmit: Request dustoff my coordinates.\n");
    say("An antenna extends from "+PNAME+"'s head briefly, and "+
      "then retracts.\n");
    if (dropdock->request_drop(environment(THISP)) < 1) {
        write("Dropship transmits: Negative\n");
        return 1;
    }
    write("Dropship transmits: Roger that\n");
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
