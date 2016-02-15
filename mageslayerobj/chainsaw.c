
//  Chainsaw arm

inherit WeaponCode;
#define SHUNT   "/zone/guild/mageslayer/obj/shoulder_implant"
#define SHAD    "/zone/guild/mageslayer/obj/hand_shad"

void extra_create()
{
    set( "id", ({ "arm", "chainsaw arm", "chainsaw", "mechanical arm",
                  "chainsaw-tipped arm", "saw" }) );
    set( "short", "a chainsaw-tipped mechanical arm" );
    set( "long",
        "This device replaces your entire left arm.  "
        "It consists of a long slender pole completely encircled "
        "by a ribbed chain, powered by a bioengineered motor.  "
        "One word comes to mind:  Groovy.  You must have a "
        "functioning shoulder implant in order to wield this "
        "prosthetic limb." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "value", 3100 );
    set( "weight", 1250 );
    set( NoDisarmP, 1 );
    set( NoTemperP, 1 );
    set( NoBlessP, 1 );
    set( NoEnhanceP, 1 );
    set( NoEnchantP, 1 );
    set_base_speed( 20 );
    set_base_damage( 25 );
    set_speed_step( 15 );
    set_damage_step( 5 );
    set_prof_mod( 8 );
    set_damage_type( "edged" );
    set_material( "steel" );
    set_proficiency( "heavy axe" );
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
    tell_object( wearer, "You socket the chainsaw-tipped mechanical "
        "arm into your shoulder implant.\n" );
    tell_room( ENV( wearer ), sprintf( "%s inserts a chainsaw-tipped "
       "mechanical arm into %s shoulder socket.\n", wearer->query_name(),
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
        tell_object( wearer, "You remove the chainsaw-tipped mechanical "
            "arm from your shoulder implant.\n" );
        tell_room( ENV( wearer ), sprintf( "%s removes the mechanical "
            "arm from %s shoulder socket.\n", wearer->query_name(),
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

int query_handed()  { return 0; }

//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
