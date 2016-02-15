
inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"

void extra_create()
{
    set( "id", ({ "arm", "cylinder", "assist cylinder", "hydraulic assist",
         "hydraulic cylinder", "hydraulic assist", "cylinder arm",
         "hydraulic arm", "hydraulic assist arm", "assist arm" }) );
    set( "short", "a hydraulic assist cylinder" );
    set( "long",
        "This device replaces your entire left arm.  "
        "Heavy duty hydraulic lines attach to various body parts, "
        "providing autonomic responses during instances when you "
        "might otherwise be stunned or paralyzed.  "
        "You must have an operable shoulder implant in order to wear "
        "this prosthesis." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1000 );
    set( "weight", 150 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "steel" );
}

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
    object shunt;
    shunt = present_clone( SHUNT, wearer );
    shunt->start_using( THISO );
    tell_object( wearer, "You socket the hydraulic assist into your shoulder "
        "implant.\n" );
    wearer->add_temp_prop( NoHoldP );
    wearer->add_temp_prop( NoStunP );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        tell_object( wearer, "You remove the hydraulic assist from your "
            "shoulder implant.\n" );
        wearer->remove_temp_prop( NoStunP );
        wearer->remove_temp_prop( NoHoldP );
    }

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
