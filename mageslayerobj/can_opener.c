//  can opener (right hand)

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"

void extra_create()
{
    set( "id", ({ "opener", "can opener", "electric can opener",
         "an electric can opener" }) );
    set( "short", "an electric can opener" );
    set( "long",
        "This device replaces your right hand.  Heavy-duty cutting "
        "wheels capable of slicing the thickest titanium are built "
        "into this compact unit.  It is designed to remove extraneous "
        "material from items of armor, in order to better accomodate "
        "shoulder and wrist "
        "implants.  You may <cut wrist from [armor]> to remove areas "
        "lost due to a wrist implant, or <cut shoulder from [armor]> "
        "to remove any areas lost due to a shoulder implant.  "
        "You must have a functioning wrist implant "
        "before this prosthetic limb can be worn.\n" );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 600 );
    set( "weight", 50 );
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
        tell_object( wearer, "Your wrist implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the can opener into your wrist "
        "implant.\n" );
    return 0;
}

int try_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
        tell_object( wearer, "You remove the can opener from your "
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
    add_action( "do_cut", "cut" );
}

int do_cut( string arg )
{
    object armor;
    string aname, type, *shunt, *areas;

    if( !arg )
        return( notify_fail( "Cut what?\n" ), 0 );

    if( sscanf( arg, "%s from %s", type, aname ) != 2 )
        return( write( "Cut <what> from <what>?\n" ), 0 );

    if( !query_worn() )
        return( notify_fail( "The can opener must be worn in a "
            "wrist implant.\n" ), 0 );

    if( THISP->in_combat() )
        return( notify_fail( "The can opener cannot be operated "
            "during combat.\n" ), 0 );

    armor = present( aname, THISP );

    if( !armor )
        return( notify_fail( "You are not holding anything by "
            "that name.\n" ), 0 );

    if( !armor->query( ArmorP ) )
        return( notify_fail( "The can opener will only operate "
            "on items of armor.\n" ), 0 );

    if( type == "wrist" )
        shunt = "/zone/guild/mageslayer/obj/wrist_implant"->query( "shunt" );
    else if( type == "shoulder" )
        shunt = "/zone/guild/mageslayer/obj/shoulder_implant"->query( "shunt" );
    else
        return( notify_fail( "The can opener will only remove "
            "<wrist> or <shoulder> locations.\n" ), 0 );

    areas = armor->query_areas();

    if( !sizeof( areas ) )
        return( notify_fail( "That armor covers no areas.\n" ), 0 );
    if( !sizeof( shunt & areas ) )
        return( notify_fail( "That armor covers no areas affected "
            "by " +type+ " implants.\n" ), 0 );
    if( !sizeof( areas - shunt ) )
        return( notify_fail( "That would completely destroy the "
            "armor!\n" ), 0 );
    
    tell_object( THISP, format( sprintf( "With a loud BZZRGTgxx! you "
        "cut sections away from %s.\n", armor->query_short() ) ) );
    tell_room( ENV( THISP ), format( sprintf( "%s cuts pieces away from %s "
        "with a loud BZZRGTgxx!\n", THISP->query_name() || "Somebody",
        armor->query_short() ) ), ({ THISP }) );

    armor->set( "areas", armor->query_areas() - shunt );
    if( strstr( armor->query_short(), "lopsided" ) == -1 )
        armor->set( "short", armor->query_short() + " (lopsided)" );
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
