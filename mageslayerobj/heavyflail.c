//  flail arm implant

inherit WeaponCode;
inherit AnsiTellCode;
#include <ansi.h>

#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"
#define SHAD    "/zone/guild/mageslayer/obj/hand_shad"

void extra_create()
{
    add( "id", ({ "arm", "flail", "ball and chain", "flail arm",
                  "ball", "chain", "massive ball",
                  "massive ball and chain" }) );
    set( "short", "a massive ball and chain" );
    set( "long",
        "This device replaces your left arm.  "
        "A heavy metal ball hangs from a length of huge chain "
        "links, and can be swung with tremendous force.  You must have a "
        "functioning shoulder implant in order to wield this "
        "prosthetic limb." );
    set_combat_messages( ({ "bash", "bashes", "smash", "smashes", 
                            "flail", "flails", "smack", "smacks" }) );
    set( "value", 3900 );
    set( "weight", 1250 );
    set( NoDisarmP, 1 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set_material( "adamantium" );
    set_proficiency( "heavy flail" );
    set_damage_type( "blunt" );
    set_prof_mod( 1 );
    set_base_speed( 10 );
    set_speed_step( 20 );
    set_base_damage( 15 );
    set_damage_step( 2 );
}

int try_wield( object wearer )
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
        tell_object( wearer, "Your shoulder implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the massive ball and chain "
        "into your shoulder implant.\n" );
    tell_room( ENV( wearer ), sprintf( "%s inserts a massive ball and chain "
        "into %s shoulder socket.\n", wearer->query_name(),
        possessive( wearer ) ), ({ wearer }) );
    shad = clone_object( SHAD );
    shad->sh_init( THISP, THISO );
    return 0;
}

void post_unwield( object wearer )
{
    object shunt = present_clone( SHUNT, wearer );
    if( shunt )
        shunt->stop_using( THISO );
    if( wearer )
    {
        tell_object( wearer, "You remove the massive ball and chain "
            "from your shoulder implant.\n" );
        tell_room( ENV( wearer ), sprintf( "%s removes the massive ball "
            "and chain from %s shoulder socket.\n", wearer->query_name(),
            possessive( wearer ) ), ({ wearer }) );
    }
    return;
}

string post_short( object me )
{
   if( query_wielded() )
       return( " (wielded in shoulder implant)" );
   return "";
} 

int query_handed() { return 0; }   // attachment


//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
