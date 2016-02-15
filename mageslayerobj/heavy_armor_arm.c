//  heavy armor plating (left arm)

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"

void extra_create()
{
    set( "id", ({ "plating", "arm", "armor", "armor plating", "heavy armor",
                  "heavy plating", "heavy armor plating" }) );
    set( "short", "heavy armor plating" );
    set( "long",
        "This device replaces your entire left arm.  Power cords "
        "stretch from the shoulder implant to armor pads which "
        "cover various parts of the body, greatly adding to your armor "
        "class rating.  You must "
        "have a functioning shoulder implant before this prosthesis "
        "can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1600 );
    set( "weight", 1000 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "titanium" );
    set( "ac", 8 );
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
    tell_object( wearer, "You socket the heavy armor plating into "
        "your shoulder implant.\n" );
    return 0;
}

void post_remove( object wearer )
{
    object shunt;

    if( wearer ) shunt = present_clone( SHUNT, wearer );

    if( shunt )
        shunt->stop_using( THISO );
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
