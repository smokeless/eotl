
//  Medpack, tail mounted

inherit ArmorCode;
inherit AnsiTellCode;
#include <ansi.h>
#define SHUNT   "/zone/guild/mageslayer/obj/tail_implant"
#define SHAD    "/zone/guild/mageslayer/obj/med_shad"
#define USETIME 180

void extra_create()
{
    set( "id", ({ "medpack", "tail", "tail-mounted medpack",
                  "solar-powered tail-mounted medpack",
                  "mounted medpack", "solar-powered medpack" }) );
    set( "short", "a solar-powered tail-mounted medpack" );
    set( "long",
        "This device is worn like a backpack, but attaches "
        "to your tail implant.  "
        "Rugged solar panels can be seen through the flexible, "
        "transparent casing, which provide power for the bio-enhancing "
        "medpack.  Electrolytic fluids travel back and forth through "
        "a thick cable through the tail implant, boosting your "
        "constitution and filtering out poisonous toxins.  "
        "You can also <activate> the medpack periodically for a rapid "
        "injection of healing proteins and stimulants.  "
        "You must have an operable tail implant in order to wear "
        "this prosthesis." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 900 );
    set( "weight", 100 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_material( "plastic" );
}

query_areas() { return 0; }

extra_init()
{
    add_action( "try_heal", "activate" );
}

int try_heal( string arg )
{
    if( !arg || !id( arg ) )
        return( notify_fail( "Activate what?\n" ), 0 );

    if( THISP->query_incap() )
         return( write( "You cannot do that while incapacitated.\n" ), 1 );

    if( !query_worn() )
        return( write( "The medpack must first be worn in a "
            "tail implant.\n" ), 1 );

    if( find_call_out( "heal_more" ) > -1 )
        return( write( "The medpack is already running.\n" ), 1 );

    if( time() - query( "last_use" ) < USETIME )
        return( write( "The medicinals in the medpack need "
            "more time to regenerate.\n" ), 1 );

    ansi_tell( THISP, "You activate the medpack.", GREEN );
    ansi_tell_room( ENV( THISP ), sprintf( "%s activates something "
       "on %s back.", THISP->query_name() || "Somebody",
       possessive( THISP ) ), GREEN, ({ THISP }) );


    THISP->add_hp( THISP->query_base_stat( "con" ) );
    THISP->add_fatigue( THISP->query_base_stat( "con" ) );
    if( THISP->query_hpw() )
        THISP->print_hp();
    call_out( "heal_more", 15, THISP, 0 );

    set( "last_use", time() );
    return 1;
}

void heal_more( object player, int repeated )
{
    if( !player || player->query_ghost() || !query_worn() )
        return;

    ansi_tell( player, "You continue to feel invigorated.",
        GREEN );
    player->add_hp( player->query_base_stat( "con" ) );
    player->add_fatigue( player->query_base_stat( "con" ) );
    if( player->query_hpw() )
        player->print_hp();

    if( repeated < 2 )
        call_out( "heal_more", 15, player, repeated + 1 );
    else
        ansi_tell( player, "The medpack whirrs to a halt.", GREEN );

    return;
}

int try_wear( object wearer )
{
    object shunt, shad;

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

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the medpack into your tail "
        "implant.\n" );
    wearer->add_bonus_object( THISO );
    shad = clone_object( SHAD );
    shad->sh_init( wearer, THISO );
    return 0;
}

void post_remove( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        wearer->remove_bonus_object( THISO );
        wearer->kill_med_shad();
    }
}

query_stat_bonus( string arg )
{
   if( query_worn() && arg == "con" )
       return ENV( THISO )->query_base_stat( "con" ) / 10;
}

query_resist_bonus( string arg )
{
   if( query_worn() )
       if( arg == "poison" || arg == "toxic" )
           return 50;
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
