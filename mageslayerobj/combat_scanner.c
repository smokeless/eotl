//  combat scanner : eye implant

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/eye_implant"
object user;

void extra_create()
{
    set( "id", ({ "eye", "eyeball", "red eyeball",
                  "scanner", "combat scanner", "red eye" }) );
    set( "short", "a red eyeball" );
    set( "long",
        "This device can be socketed as a false eye.  "
        "The combat scanner is the latest in design in real-time "
        "computer-assisted targeting.  During combat situations, "
        "the electronic eye highlights the weak spots of an "
        "opponent's defense, and predicts the likely points of an "
        "opponent's next attack.  This information is fed directly "
        "into the wearer's central nervous system via an implant, "
        "allowing him, her, or it to successfully strike the "
        "opponent more often, while simultaneously dodging enemy "
        "attacks.  These effects are enhanced by a higher native "
        "intelligence.  The scanner functions automatically, but "
        "you must have a functioning eye implant "
        "before this prosthetic device can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 9500 );
    set( "weight", 5 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "glass" );
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
    tell_object( wearer, "You socket the combat scanner into your eye "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    user = wearer;
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        tell_object( wearer, "You unhook the combat scanner from your "
            "eye implant.\n" );
        wearer->remove_bonus_object( THISO );
    }
    user = 0;
}

varargs string post_short( object me )
{
    if( query_worn() )
        return( " (socketed into eye implant)" );
}

query_offensive_bonus()
{
    if( query_worn() && ENV( THISO ) == user )
        return( user->query_stat( "int" ) );
}

query_defensive_bonus()
{
    if( query_worn() && ENV( THISO ) == user )
        return( user->query_stat( "int" ) / 2 );
}

query_skill_bonus( string arg )
{
    if( arg == "shield" || arg == "dodge" )
        if( user->query_base_skill( arg ) )
            return( user->query_base_stat( "int" ) / 20 );
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
