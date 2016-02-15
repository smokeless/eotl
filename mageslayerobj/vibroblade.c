//  knife-like hand

inherit WeaponCode;
inherit AnsiTellCode;
#include <ansi.h>

#define SHUNT   "/zone/guild/mageslayer/obj/wrist_implant"
#define SHAD    "/zone/guild/mageslayer/obj/hand_shad"

void extra_create()
{
    set( "id", ({ "knife", "vibroblade", "attachment", "hand",
                  "vibroblade attachment", "blade" }) );
    set( "short", "a vibroblade attachment" );
    set( "long",
        "This device replaces your right hand.  "
        "It consists of two razor-sharp blades vibrating side-by-"
        "side in opposition, capable of cutting through nearly "
        "any substance.  You must have a "
        "functioning wrist implant in order to wield this "
        "prosthetic limb." );
    set_combat_messages( ({ "slice", "slices", "dice", "dices", 
                            "shear", "shears", "cut", "cuts" }) );
    set( "value", 1800 );
    set( "weight", 250 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 ); 
    set( NoEnchantP, 1 );
    set( NoBlockP, 1 );
    set( NoDisarmP, 1 );
    set_material( "steel" );
    set_material_name( "surgical steel" );
    set_proficiency( "knife" );
    set_damage_type( "edged" );
    set_prof_mod( 8 );
    set_base_speed( 40 );
    set_speed_step( 4 );
    set_base_damage( 10 );
    set_damage_step( 9 );
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
        tell_object( wearer, "Your wrist implant is currently in use.\n" );
        return 1;
    }

    shunt->start_using( THISO );
    tell_object( wearer, "You socket the vibroblade "
        "into your wrist implant.\n" );
    tell_room( ENV( wearer ), sprintf( "%s inserts a vibroblade "
        "into %s wrist socket.", wearer->query_name(),
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
        tell_object( wearer, "You remove the vibroblade "
            "from your wrist implant.\n" );
        tell_room( ENV( wearer ), sprintf( "%s removes the vibroblade "
            "from %s shoulder socket.", wearer->query_name(),
            possessive( wearer ) ), ({ wearer }) );
    }
    return;
}

string post_short( object me )
{
   if( query_wielded() )
       return( " (wielded in wrist implant)" );
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
