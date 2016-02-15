//  makes a hole in the ground to hide in (left arm)

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"
#define BURROW  "/zone/guild/mageslayer/obj/burrow_obj"

void extra_create()
{
    set( "id", ({ "auger", "drill", "motorized auger",
         "motorized earth auger", "earth auger", "arm" }) );
    set( "short", "a motorized earth auger" );
    set( "long",
        "This device replaces your entire left arm.  Helical flighting "
        "rotated around a central shaft quickly digs and moves "
        "large quantities of soil away from a pocket within the "
        "earth.  You can activate the auger only while outside or underground, "
        "and it is much too slow to use while in combat.  You must have "
        "an appropriate shoulder implant "
        "before this prosthetic limb can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1800 );
    set( "weight", 2000 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "steel" );
    set( "ac", 0 );
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
    tell_object( wearer, "You socket the earth auger into your shoulder "
        "implant.\n" );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the earth auger from your "
            "shoulder implant.\n" );

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
    add_action( "do_dig", "activate" );
}

int do_dig( string arg )
{
    object burrow;

    if( !arg || !id(arg) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The earth auger must first be worn in a "
            "shoulder implant.\n" ), 0 );

    if( THISP->in_combat() )
        return( notify_fail( "The earth auger cannot be operated "
            "during combat.\n" ), 0 );

    if( !ENV(THISP)->query( OutsideP ) && 
        !ENV(THISP)->query( UndergroundP ) )
        return( notify_fail( "The earth auger can only be operated "
            "outside.\n" ), 0 );

    tell_object( THISP, "With a loud rumble you "
        "begin to drill down into the earth.\n" );
    tell_room( ENV( THISP ), sprintf( "%s begins to drill down "
        "into the earth with a loud rumble.\n", PNAME ), ({ THISP }) );

    burrow = clone_object( BURROW );
    move_object( burrow, ENV( THISP ) );
    if( !move_object( THISP, burrow ) )
    {
        tell_object( THISP, "You hit bedrock, and cannot dig further.\n" );
        destruct( burrow );
        return 1;
    }
    tell_room( ENV(burrow), sprintf( "%s disappears into the earth!\n",
        PNAME ) );
    tell_object( THISP, "You burrow down into a pocket within the earth!\n" );
    THISP->glance();
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
