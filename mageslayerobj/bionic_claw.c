//  Bionic right hand

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"

void extra_create()
{
    set( "id", ({ "claw", "bionic claw" }) );
    set( "short", "a bionic claw" );
    set( "long",
        "This device replaces your right hand.  Enhanced "
        "hydraulics offer greater strength potential, but it is "
        "less dextrous than natural flesh.  Unlike most implant "
        "devices, it does operate as a working hand, and can be "
        "used to hold shields, weapons, or other items.  You must "
        "have a functioning wrist shunt before this prosthetic limb "
        "can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1200 );
    set( "weight", 5 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "plastic" );
}

query_areas() { return ({}); }

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

    return ::try_wear( wearer );
}

void post_wear( object wearer )
{
    object shunt, *stuff;

    shunt = present_clone( SHUNT, wearer );
    shunt->start_using( THISO );
    tell_object( wearer, "You socket the bionic claw into your wrist "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    stuff = wearer->query_armor();
    if( member( stuff, "right hand" ) < 0 )
        wearer->set_armor( wearer->query_armor() + ({ "right hand", 0, 0 }) );
    wearer->add_hit_location( ({ "right hand", 0, 35, 0, 1, 1 }) );
}

int try_remove( object wearer )
{
    object *stuff;
    stuff = wearer->query_armor_worn() || ({});

    if( wearer->hands_free() <= 0 )
    {
        tell_object( wearer, "You must free up a hand in order to "
            "do that.\n" );
        return 1;
    }

    if( sizeof( stuff ) )
        foreach( object temp : stuff )
            if( sizeof( temp->query_areas() ) &&
                member( temp->query_areas(), "right hand" ) > -1 )
            {
                tell_object( wearer, "You must first remove all 'right hand' "
                    "armor covering your bionic claw.\n" );
                return 1;
            }

    return ::try_remove( wearer );
}

void post_remove( object wearer )
{
    mixed *stuff;
    object shunt;
    int x;
    shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        wearer->remove_bonus_object( THISO );
        stuff = wearer->query_armor();
        for( x=0; x<sizeof(stuff); x+=3 )
             if( stuff[x] == "right hand" )
                 stuff = stuff[0..x-1] + stuff[x+3..];
        wearer->set_armor( stuff );
        wearer->remove_hit_location( "right hand" );
    }
}

query_stat_bonus( string arg )
{
    if( query_worn() && arg == "str" )
        return 10 + ENV(THISO)->query_base_stat( arg ) / 20;
    if( query_worn() && arg == "dex" )
        return( - ENV( THISO )->query_base_stat( arg ) / 20 );
}

varargs string post_short( object me )
{
    if( query_worn() )
        return( " (socketed into wrist implant)" );
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
