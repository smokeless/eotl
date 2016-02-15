/* Fireball - An group attack of flame and fury.
* Coded by Nyarlathotep@EotL 10-6-96
* Some code borrowed from Lightning by Tabitha@EotL
*/

inherit BaseCommand;

#include "../defs.h"
#define REVERSE_EXITS ([ "east":"west","west":"east","north":"south","south":"north","northwest":"southeast","northeast":"southwest","southwest":"northeast","southeast":"northwest","up":"down","down":"up" ])

void boom( object room );

void extra_create()
{
    set( "name", "mass fireball" );
    set( "help",
         "Name  : Fireball\n"
         "Cost  : 50 Mana\n"
         "Type  : Combat\n"
         "Usage : cast fireball\n"
         "Requirements : 40 in Intelligence\n"
         "               15 in Magic Missile\n"
         "               15 in Spell Casting\n"
                 "               15 in Drazk\n"
         "\n"
         "One of the most spectacular displays of power known, "
         "a Warlock's fireball spreads throughout the room burning "
         "all not allied with the caster.  Long ago, we Warlocks "
         "had more precise control over our flame attacks, but "
         "after the sundering we discovered the power within large-"
         "scale attacks such as the fireball we now control.  "
          "\n\nThis spell's casting time varies depending upon the "
          "caster's skill in 'mass fireball' and is not consistent "
          "even for someone at the same skill level."
    );
    set( "action", "cast" );
    set( "verb", "fireball" );
    set( "usage", "cast fireball" );
    set( "guild", "warlock" );
    set( "class", "combat" );
    set( "function", "prepare" );
    set( "no_combat", 0 );
    set( "no_rest", 1 );
    set( "private", 1 );
    set( "min",
    ([
      "skills" : ([ "spell casting" : 15, "magic missile" : 15,
                    "Drazk" : 15 ])
      ,"stats" : ([ "int" : 40 ])
    ]));

    set( "cost",
    ([
      "mana" : 50
    ]));

    set( "delay", 1 );

    set( "success",
    ([
    "skills": ({ "spell casting", 2, 1, "mass fireball", 2, 1 })
   ,"stats": ({ "int", 1, 8 })
    ]));

    set( "offchance", 6 );
}

status okattempt()
{
    if( !::okattempt() )
        return 0;

    if( ( ENV( THISP )->query( NoCombatP ) ) ) {
        atell( THISP, "Etiquette prohibits casting offensive "
        "spells here!", HIY );
        return 0;
    }

    if( !casting_ok( THISP ) ) return 0;

    return 1;
}

void prepare()
{
    int damage;
    int delaytime = 1;

    subtract_cost();

    tell_object( THISP, "You recite ancient words of Drazk, calling "
    "upon the weapon of old Fireball.\n" );
    DRAZK->do_command( "Flames, fire, Power of Destruction!"+

    "  Destroy my enemies upon my instruction!" );

    THISP->set_distract_check( THISP );

    THISP->add_prop( CastingP );
    THISP->set_prop_value( CastingP, THISO );

    delaytime = random( THISP->query_skill( "mass fireball" ) ) > 30 ? 0 : 1;
    delaytime += random( THISP->query_skill( "mass fireball" ) ) > 10 ? 0 : 1;

    if( delaytime )
        call_out( "mess_1", delaytime, THISP, ENV( THISP ) );
    else
        call_other( THISO, "mess_1", THISP, ENV( THISP ) );
}

mess_1( object caster, object ecast )
{
    int delaytime;

    if( !objectp( caster ) )
        return;

    if( !still_casting( caster ) ){
        caster->remove_prop( CastingP );
        return;
    }
    set_this_player( caster );
    DRAZK->do_command( "Burning flames of towering fire!  "+
    "Bend to my WILL and fulfill my DESIRE!" );

    delaytime = random( caster->query_skill( "mass fireball" ) ) > 30 ? 0 : 1;
    delaytime += random( caster->query_skill( "mass fireball" ) ) > 10 ? 0 : 1;

    if( delaytime )
        call_out( "mess_2", delaytime, caster, ecast );
    else
        call_other( THISO, "mess_2", caster, ecast );
}

mess_2( object caster, object ecast )
{
    int delaytime;

    if( !objectp( caster ) )
        return;

    if( !still_casting( caster ) ){
        caster->remove_prop( CastingP );
        return;
    }
    set_this_player( caster );
    DRAZK->do_command( "Burn my ENEMY! BURN THE WORLD!  "
    "To BATTLE! TO WAR! You are sent! You are HURLED!" );

    delaytime = random( THISP->query_skill( "mass fireball" ) ) > 30 ? 0 : 1;
    delaytime += random( THISP->query_skill( "mass fireball" ) ) > 10 ? 0 : 1;

    if( delaytime )
        call_out( "do_hurt", delaytime, caster, ecast );
    else
        call_other( THISO, "do_hurt", caster, ecast );
}

void
do_hurt( object caster, object old_room )
{
    string cname;
    int damage, cint, cskill1, cskill2, x;
    object *all, *Group, *who, *defended;
    string cabal;
    object *stuff;
    string msg;

    if( !objectp( caster ) )
        return;

    cname = caster->query_name();
    caster->remove_prop( CastingP );

    if( !still_casting( caster ) ){
        return;
    }

    if( caster->query_ghost() ) return;
    if( caster->query_hp() < 0 ) return;

    if( ENV( caster )->test_prop( NoPKP ) ||
            ENV( caster )->test_prop( NoCombatP ) ) {
        atell( caster, "Magics greater than your stop your "
        "spell!", HIY );
        return;
    }
                     
    if( caster->is_distracted( caster, -30 ) ) {
//  This skill sucks for low evals and to be useful for higher evals
// needs to be harder to be distracted from.
        atell( caster, "You cannot concentrate enough to cast "
        "a spell!", HIY );
        tell_room( ENV( caster ), cname + "'s spell fails "
        "as " + subjective( caster ) + " loses concentration.\n",
        ({ caster }));
        return;
    }

    if( old_room != ENV( caster ) )
        return;

    if( success_roll() < 0 ) {
        atell( caster, "Your magic fails you!", HIY );
        tell_room( ENV( caster ), cname + "'s spell fails.\n",
        ({ caster }));
        return;
    }

    cint = caster->query_stat( "int" );
    cskill1 = caster->query_skill( "mass fireball" );
    cskill2 = caster->query_skill( "spell casting" );

    damage = random( cint ) * ( random( 3 ) + 2 );
    damage += cskill1 * 5;
    damage += cskill2 * 2;
    damage += random( cskill2 ) * 3;
    damage += random( cskill2 ) * 3;
    damage += ( random( cint ) *
            ( ( cskill2 < 30 ) ? ( 0 ) :
            ( random( cskill2 - 15 ) / 9 ) ) );

    damage += caster->modify_for_power_of_war( damage );

    atell( caster, "You complete the spell with a final hiss.", HIR );
    switch( damage ) {
      case 0..75 :
        msg = "The flames surge across the room, singeing hair.";
        break;
      case 76..150 :
        msg = "The flames surge through the room burning everyone.";
        break;
      case 151..300 :
        msg = "The flames erupt into the room, exploding outwards, engulfing all within!";
        break;
      case 301..500 :
        msg = "The flames erupt into the room, burning flesh and charring bones.";
        break;
      case 501..700 :
        msg = "The explosion blasts through the room, burning all that is within.";
        break;
      case 701..900 :
        msg = "The explosion rocks the land and flays the flesh from the living.";
        break;
      case 901..1100 :
        msg = "The explosion incinerates the flesh and melts the ground into slag.";
        break;
      default :
        msg = "The explosion rocks the mud to its very foundation! The flesh of the living "
        "is vaporized and the superheated air bursts from the room.";
        break;
    }
    if(caster->query_wizard())
    {
        tell_object(caster, sprintf(
            "\n\tTo a player you did %d\n\tTo a monster you did %d.\n",
            damage, damage*2));
    }
    atell( caster, strformat( msg ), HIR );
    tell_room( ENV( caster ), strformat( msg ), ({ caster }) );
    if( damage > 500 )
        boom( ENV( caster ) );

    Group = caster->query_group_members();
    defended = caster->query_defend();
    if( !pointerp( Group ) )
        Group = ({ });
    if( pointerp( defended ) )
        Group += defended;

    stuff = all_inventory( ENV( caster ) );
    for( x = sizeof( stuff ); x--; ) {
        if( living( stuff[ < x + 1 ] ) ) continue;
         if( !objectp( stuff[ < x + 1 ] ) ) continue;
        if( !stuff[ < x + 1 ]->query( FlammableP ) ) continue;

        tell_room( ENV( stuff[<x+1] ), capitalize(stuff[<x+1]->query("id")[0])+
        " is incinerated in the fireball!\n" );
        stuff[ < x + 1 ]->ignite();
        if( objectp( stuff[ < x + 1 ] ) )
            destruct( stuff[ < x + 1 ] );
    }

    for( x = sizeof( all = filter_array( all_inventory( ENV( caster )),
             #'living )); x--; ) {
        if( all[ < x + 1 ] == caster ) continue;
        if( member( Group, all[ < x + 1 ] ) != -1 ) continue;
        if( !caster->valid_target( all[ < x + 1 ] ) || !all[<x+1]->attackable(THISP)) continue;
        if( IsWizard( all[ < x + 1 ] ) ) continue;
        if( ENV( all[ < x + 1 ] )->test_prop( NoPKP ) &&
                 all[ < x + 1 ]->is_player() ) continue;

        atell( all[ < x + 1 ], "You scream in pain as your "
        "flesh is burnt from your body!", HIR );
        command( "scream", all[ < x + 1 ] );

        if(!is_player(all[ < x + 1 ] ) )
        {
            all[ < x + 1 ]->take_damage(damage * 2, 0, "magic_fire", caster );
        }
        else
        {
            all[ < x + 1 ]->take_damage(damage, 0, "magic_fire", caster );
        }
        if( !objectp( all[<x+1] ) || all[<x+1]->query_ghost() )
            continue;

        if( all[ < x + 1 ] )
            caster->attack_object( all[ < x + 1 ] );

        if( ( random( 3 ) < 2 ) && all[ < x + 1 ] )
            move_object( clone_object( NAPALM )->set_it_up( damage, 
            caster ),  all[ < x + 1 ] );

        if( all[ < x + 1 ] && !all[ < x + 1 ]->query_ghost() )
            if( damage > ( all[ < x + 1 ]->query_max_hp() / 3 ) ) {
                if( all[ < x + 1 ]->choose_target() != caster )
                    tell_object( caster, all[ < x + 1 ]->query_name() +
                    " sees you as the greatest immediate threat and "
                    "attacks!\n" );
                all[ < x + 1 ]->set_target( caster );
            }
    }

    if( damage > 1000 ) { 
        cabal = explode( file_name( ENV( THISP ) ), "/" )[3];
        who = users();
        atell( caster, "A mushroom cloud grows over you.\n" HIR );
        for( x = 0; x < sizeof( who ); x++ ) {
            if( !objectp( ENV( who[x] ) ) ) continue;
            if( ( strstr( file_name( ENV( who[x] ) ), cabal ) > 0 ) &&
                ( who[x] != caster ) &&
                !IsWizard( who[ x ]) )   {
                atell( who[ x ], "A mushroom cloud grows over "+
                "the laughing form of "+
                capitalize( caster->query_real_name() ) +
                "!", HIR );
              }
         }
    }

    ENV( caster )->set( "fire_damage",
            ENV( caster )->query( "fire_damage" ) + damage );
}

boom( object room )
{
    int x;
    string *dirs;
    mapping m;

    m = room->query("exits")+room->query("invis_exits");

    if( sizeof( dirs = m_indices( m ) ) ) {
        for( x = 0; x < sizeof( dirs ); x++ ) {
            if( strstr( m[dirs[x]], "@" ) >= 0 ) continue;
            tell_room( m[dirs[x]], strformat( "You hear a loud explosion and feel a rush of heat from "+
            (REVERSE_EXITS[dirs[x]]?"the "+REVERSE_EXITS[dirs[x]]:"nearby")+
            "." ) );
        }
    }
}
