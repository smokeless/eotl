/*
Added a damage component
*changed help
*removed chance to harm caster
  -other guilds aren't harming themselves on failed rolls.
*fixed duration check against non-exist damage type
*on a failed flash the illusionist has a chance to enter combat
Taplash 2015
*/
  
inherit AttackCommand;
virtual inherit "/obj/guild/necromancer/modules/casting";

#include "/obj/guild/illusionist/defs.h"

void extra_create()
{
    set( "name", "flash" );
    set( "help",
         "Name  : Flash in the Brain Pan\n"
         "Cost  : 20 Mana\n"
         "Type  : Combat\n"
         "Usage : cast flash [ target ]\n"
         "Requirements : 40 Int, 10 False Light, 15 Spell "
         "Casting, 10 Silvari\n"
         "\n"
        "A Flash in the Brain Pan is the second most basic illusion. "
        "Slightly more potent than the illusion of light, is the illusion "
        "of too much light.  This spell can potentially blind a foe, "
        "causing them to be unable to attack. Powerful illusionists "
        "have been known to create light bright enough to actually "
        "harm their opponents."
    );
    set( "action", "cast" );
    set( "verb", "flash" );
    set( "usage", "cast flash [ target ]" );
    set( "guild", "illusionist" );
    set( "class", "combat" );
    set( "function", "prepare" );
    set( "no_combat", 1 );
    set( "private", 1 );
    set( "min",
    ([
      "stats" : ([ "int" : 40 ])
     ,"skills" : ([ "false light" : 10, "spell casting" : 15,
                    "Silvari" : 10 ])
    ]));

    set( "cost",
    ([
      "mana" : 20
    ]));

    set( "delay", 0 );

    set( "success",
    ([
    "stats" : ({ "int", 1, 5 })
    ,"skills": ({ "flash", 1, 1, "spell casting", 1, 1 })
    ]));

    set( "offchance", 20 );
}

status okattempt( object victim )
{
    if( !::okattempt( victim ) )
        return 0;

    if( ENV( THISP )->query(NoPKP) || ENV( THISP )->query(NoCombatP) )
        return( atell( THISP, "Etiquette prohibits casting offensive "
        "spells here.", HIY ), 0 );

    if( !victim->attackable( THISP ) )
        return( atell( THISP, "You cannot target that!\n", HIY ), 0 );

    if( THISP->query_delay() ) 
        return( atell( THISP, "You cannot cast that spell right now!",
        HIY ), 0 );

    if( !casting_ok( THISP ) ) return 0;

    return 1;
}

void prepare( object victim )
{
    string aname, vname, howbig;
    object attacker = THISP;
    int duration, guy, mob, damage;
    object ov = victim;

    aname = capitalize( (string)THISP->query_name() );
    subtract_cost();

    SILVARI->do_command( 
    "Visions of my plight from the highest height! "
    "Dreams of flight, shades of white, smite with bright light!"
     );
    attacker->add_prop( CastingP );
    attacker->set_prop_value( CastingP, THISO );

    aname = capitalize( (string)attacker->query_name() );
    vname = capitalize( (string)victim->query_name() );

    if( success_roll() < 0 ) {
      atell( attacker, "Your magic fails to take effect.\n", HIR );
      tell_room( ENV( attacker ), aname+" finishes "+
      possessive( attacker )+" spell, but nothing happens.\n",
     ({ attacker }));
     //giving monster a chance to notice something
     //was tried against it. Hopefully it's a 
     //small chance. If you're a player, pay attention.
     guy = attacker->query_stat( "int" ) + attacker->query_stat( "chr" ) +
           attacker->query_skill( "flash" );
     mob = ov->query_stat( "int" );
     if( guy + random( 100 ) < mob + random( 100 ) 
         && !(ov->is_player()) )
     {
       atell( attacker, sprintf( "You weren't subtle enough, "
         "%s figured out %s was the target of your spell!\n",
         ov->query_name(), subjective( ov ) ), HIR );
       attacker->attack_object( ov );
       attacker->remove_prop( CastingP );
       return;
     }
       return;
     }
     
    
    if( victim->test_prop( NoStunP ) ) {
        attacker->remove_prop( CastingP );
        atell( attacker, victim->query_name()+" ignores your magic!", HIR );
        tell_room( ENV( attacker ), aname+" finishes "+possessive( attacker )+
        " spell, but nothing happens.\n", ({ attacker }) );
        atell( victim, aname+" finishes "+possessive( attacker )+" spell but "+
        "you are immune to it.\n", BLU );
        return;
    }

    duration = attacker->query_skill( "flash" );
    duration += ( attacker->query_stat( "int" ) + attacker->query_stat( "chr" ) ) / 10;
    duration -= ( victim->query_resistance( "psychic" ) * duration ) / 100;
    duration = random( duration ) / 3;

    if( duration <= 0 ) {
        atell( attacker, "They are completely unaffected.", HIR );
        attacker->remove_prop( CastingP );
        attacker->attack_object( ov );
        return;
    }
    duration++;
    //set the damage point at 15
    if( objectp( victim ) && attacker->query_skill( "flash" ) < 15 ) {
        if( !victim->query_delay() )
            victim->add_combat_delay( duration );
        atell( victim, "You see a flash of light and your brain seizes up.", HIC );
        if( victim != attacker )
            atell( attacker, vname+" suddenly gets a glazed look in "+possessive( victim )+" eyes.\n", HIC );
        tell_room( ENV( attacker ), vname+" suddenly gets a glazed look in "+possessive( victim )+
        " eyes.\n", ({ victim, attacker }) );
        return;
    }
    int intel = attacker->query_stat( "int" );
    //using burning grasp initial damage calc.
    damage = attacker->query_skill( "flash" ) * 3;
    damage += attacker->query_skill( "spell casting" ) * 3;
    damage += random( attacker->query_stat( "int" ) ) / 5;
    damage += ( attacker->query_skill( "flash" )
                * min( random( intel ) + 
                random( intel ), intel ) ) / 10;
    damage++;
    
    switch( damage )
    {
      case 0..50   : howbig = "bright"; break;
      case 51..200 : howbig = "huge"; break;
      case 201..400: howbig = "gigantic"; break;
      case 401..600: howbig = "stunningly bright";
      default      : howbig = "mind searing"; break;      
    }
    if( objectp( victim ) )
    {
      atell( victim, sprintf( "You see a %s flash of light. "
        "Your brain ceases up!", howbig ), HIC );
      atell( attacker, sprintf( "You fire off a %s flash of light. "
        "%s suddenly gets a glazed look in %s eyes.", vname, possessive(ov) ), HIC);
      ov->take_damage( damage, 0, "psychic", attacker );
    }
      

    attacker->attack_object( ov );
    attacker->remove_prop( CastingP );
}
