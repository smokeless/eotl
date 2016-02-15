//  scanner : eye implant
//  This object might f-up anyone with NightVisionP from
//  another source (like drow race), but since Drow can't
//  join mageslayers I'm not too worried about it

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/eye_implant"

void extra_create()
{
    set( "id", ({ "eye", "eyeball", "white eyeball",
                  "scanner", "infrared scanner", "white eye" }) );
    set( "short", "a white eyeball" );
    set( "long",
        "This device can be socketed as a false eye.  "
        "It uses the latest in infra-red technology to deliver "
        "a crystal-clear image in low-light conditions.  "
        "You must have a functioning eye implant "
        "before this prosthetic device can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 500 );
    set( "weight", 5 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set_material( "glass" );
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
        tell_object( wearer, "Your eye implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the infra-red scanner into your eye "
        "implant.\n" );
    wearer->set( NightVisionP, "infra-red vision" );

    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        tell_object( wearer, "You remove the infra-red scanner from your "
            "eye implant.\n" );
        wearer->remove_prop( NightVisionP );
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
        return( " (socketed into eye implant)" );
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
