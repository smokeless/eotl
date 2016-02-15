
//  Bionic left arm, dextrous

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"

void extra_create()
{
    set( "id", ({ "manipulator", "robotic manipulator" }) );
    set( "short", "a robotic manipulator" );
    set( "long",
        "This device replaces your entire left arm.  It offers "
        "extremely dextrous and precise movement, but its hydraulics "
        "are rather weak and unsightly.  Unlike most implant "
        "devices, it includes a finely-tuned set of manipulators "
        "that emulates a natural hand, and can be "
        "used to hold shields, weapons, or other items.  You must "
        "have a functioning shoulder implant before this prosthesis "
        "can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1900 );
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
        tell_object( wearer, "Your shoulder implant is currently in use.\n" );
        return 1;
    }

    return ::try_wear( wearer );
}

void post_wear( object wearer )
{
    object shunt, *stuff;

    shunt = present_clone( SHUNT, wearer );
    shunt->start_using( THISO );
    tell_object( wearer, "You socket the manipulator arm into your shoulder "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    stuff = wearer->query_armor();
    if( member( stuff, "left hand" ) < 0 )
        wearer->set_armor( wearer->query_armor() + ({ "left hand", 0, 0 }) );
    if( member( stuff, "left arm" ) < 0 )
        wearer->set_armor( wearer->query_armor() + ({ "left arm", 0, 0 }) );
    wearer->add_hit_location( ({ "left arm", 0, 40, 0, 1, 0 }) );
    wearer->add_hit_location( ({ "left hand", 0, 35, 0, 1, 1 }) );
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
                member( temp->query_areas(), "left hand" ) > -1 )
            {
                tell_object( wearer, "You must first remove all 'left hand' "
                    "armor covering your manipulator arm.\n" );
                return 1;
            }
            else if( sizeof( temp->query_areas() ) &&
                member( temp->query_areas(), "left arm" ) > -1 )
            {
                tell_object( wearer, "You must first remove all 'left arm' "
                    "armor covering your manipulator arm.\n" );
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
             if( stuff[x] == "left hand" )
                 stuff = stuff[0..x-1] + stuff[x+3..];
        for( x=0; x<sizeof(stuff); x+=3 )
             if( stuff[x] == "left arm" )
                 stuff = stuff[0..x-1] + stuff[x+3..];
        wearer->set_armor( stuff );
        wearer->remove_hit_location( "left hand" );
        wearer->remove_hit_location( "left arm" );
    }
}

query_stat_bonus( string arg )
{
    if( query_worn() && arg == "dex" )     //  15% bonus
        return ENV( THISO )->query_base_stat( arg ) * 3 / 20;
    if( query_worn() && arg == "str" )     //  15% penalty
        return( - ENV( THISO )->query_base_stat( arg ) * 3 / 20 );
    if( query_worn() && arg == "chr" )     //  15% penalty
        return( - ENV( THISO )->query_base_stat( arg ) * 3 / 20 );
}

varargs string post_short( object me )
{
    if( query_worn() )
        return( " (socketed into shoulder implant)" );
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
