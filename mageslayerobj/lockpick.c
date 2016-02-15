//  mechanical/electronic lockpick (right hand)

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"
#define COST    15

void extra_create()
{
    set( "id", ({ "pick", "lockpick", "electronic lockpick",
         "picks", "hand", "device", "lockpick device",
         "electronic lockpick device", "electronic device" }) );
    set( "short", "an electronic lockpick device" );
    set( "long",
        "This device replaces your right hand.  It is the latest "
        "technology in picking mechanical or electronic locks.  "
        "You may <use lockpick on [lock/door]> to attempt to unlock "
        "it.  Some locks may require many attempts, and some will be "
        "completely resistant.  "
        "You must have a functioning wrist implant "
        "before this prosthetic limb can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 900 );
    set( "weight", 50 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "copper" );
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
        tell_object( wearer, "Your wrist implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the lockpick device into your wrist "
        "implant.\n" );
    return 0;
}

int try_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the lockpick device from your "
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
    add_action( "do_pick", "use" );
}

int do_pick( string arg )
{
    object lock;
    string lname, foo;

    if( !arg )
        return( notify_fail( "Use what?\n" ), 0 );

    if( sscanf( arg, "%s on %s", foo, lname ) != 2 )
        return( write( "Use <what> on <what>?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The lockpick device must be worn in a "
            "wrist implant.\n" ), 0 );

    if( THISP->in_combat() )
        return( notify_fail( "The lockpick device cannot be operated "
            "during combat.\n" ), 0 );

    lock = present( lname, ENV(THISP) );
    if( !lock ) lock = present( lname, THISP );

    if( !lock )
        return( notify_fail( "You don't see anything like that.\n" ), 0 );

    if( !lock->query( LockedP ) && !lock->query( "locked" ) )
        return( notify_fail( "The lockpick device will not work on "
            "that.\n" ), 0 );

    if( THISP->query_fatigue() < COST )
        return( notify_fail( "You are too fatigued to use "
            "that.\n" ), 0 );

    tell_object( THISP, sprintf( "You apply the lockpick device "
        "to %s.\n", lock->short() ) );
    tell_room( ENV( THISP ), sprintf( "%s fiddles with %s.\n",
        THISP->query_name() || "Somebody", lock->short() ), ({ THISP }) );

    THISP->add_fatigue( -COST );

    //  Is our lock DoorCode?
    if( lock->query( DoorP ) )
    {
        if( !lock->query( "lock_level" ) )
        {
            tell_object( THISP, "The lockpick device is incompatible with "
                "that.\n" );
            return 1;
        }
        if( random( 101 ) > 11 * lock->query( "lock_level" ) )
            lock->magic_unlock_door();
        else tell_object( THISP, "The lockpick device fails on that "
            "attempt.  Try again.\n" );
        return 1;
    }

    //  Not DoorCode, perhaps /lib/support/lock.c ?
    switch( lock->pick_lock( 30 ) )
    {
        case 1:  tell_room( ENV(THISP), sprintf( "The lock on %s "
                     "releases.\n", lock->short() ) );
                 break;
        default: tell_object( THISP, "The lockpick device fails on that "
                     "attempt.  Try again.\n" );
                 break;
    }
          
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
