//  material scanner : eye implant

inherit ArmorCode;
#define SHUNT   "/zone/guild/mageslayer/obj/eye_implant"
object user;

void extra_create()
{
    set( "id", ({ "eye", "eyeball", "yellow eyeball",
                  "scanner", "material scanner", "yellow eye" }) );
    set( "short", "a yellow eyeball" );
    set( "long",
        "This device can be socketed as a false eye.  "
        "The material scanner highlights the flaws and strengths "
        "of different substances, allowing the wearer to fashion "
        "item upgrades with a higher quality of success.  "
        "You must have a functioning eye implant "
        "before this prosthetic device can be worn." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 1200 );
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
    tell_object( wearer, "You socket the material scanner into your eye "
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
        tell_object( wearer, "You unhook the material scanner from your "
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

query_skill_bonus( string arg )
{
    if( query_worn() && arg == "upgrade" )
        return( 5 );
}

query_stat_bonus( string arg )
{
    if( arg == "int" ) return user->query_base_stat( "int" ) / 10;
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
