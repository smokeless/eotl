
//  Bionic tail

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/tail_implant"

void extra_create()
{
    set( "id", ({ "tail", "bionic tail" }) );
    set( "short", "a bionic tail" );
    set( "long",
        "This device protrudes from where your tail might be.  "
        "Metallic grippers at the end allow it to function as "
        "an extra hand, and its length of flexible cable allows "
        "it to reach clear around your body.  The tail will function "
        "automatically whenever you attempt to wear a shield or wield "
        "a weapon, and can be covered with armor.  "
        "You must have an operable tail implant in order to wear "
        "this prosthesis." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1000 );
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
        tell_object( wearer, "Your tail implant is currently in use.\n" );
        return 1;
    }

    return ::try_wear( wearer );
}

void post_wear( object wearer )
{
    object shunt, *stuff;

    shunt = present_clone( SHUNT, wearer );
    shunt->start_using( THISO );
    tell_object( wearer, "You socket the bionic tail into your tail "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    stuff = wearer->query_armor();
    if( member( stuff, "tail" ) < 0 )
        wearer->set_armor( wearer->query_armor() + ({ "tail", 0, 0 }) );
    wearer->add_hit_location( ({ "tail", 0, 35, 0, 1, 1 }) );
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
                member( temp->query_areas(), "tail" ) > -1 )
            {
                tell_object( wearer, "You must first remove all 'tail' "
                    "armor covering your bionic tail.\n" );
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
             if( stuff[x] == "tail" )
                 stuff = stuff[0..x-1] + stuff[x+3..];
        wearer->set_armor( stuff );
        wearer->remove_hit_location( "tail" );
    }
}

varargs string post_short( object me )
{
    if( query_worn() )
        return( " (socketed into tail implant)" );
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
