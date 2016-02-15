#include<ansi.h>
inherit MiscCommand;
inherit AnsiTellCode;
virtual inherit "/obj/guild/necromancer/modules/casting";
 
#define SIL "/obj/guild/linguist/skills/Silvari.c";
int delay;
 
void extra_create()
{
    set( "name", "mass hallucination" );
    set( "help", 
         "Spell : Mass Hallucination\n"
         "Cost  : 50 Base mana plus upkeep\n"
         "Type  : Illusion\n" 
         "Usage : cast hallucination\n"
         "Requirements : 70 Int, 20 Triforium, 15 Silvari\n"
         "\n"
         "The mind is a powerful thing. It can heal the body "
         "through sheer wilpower, it can also harm the body. "
         "A skilled illusionist knows this and uses it to "
         "their advantage in combat.\n"
         "This skill creates a terrifying shared hallucination. "
         "Creatures affected by this have been known to tear "
         "at their own skin in horror. The less wilful the creature "
         "the longer the effect lasts."
         
    );
    set( "action", "cast" );
    set( "verb", "hallucination" );
    set( "usage", "cast" );
    set( "guild", "illusionist" );
    set( "class", "enchantment" );
    set( "function", "special" );
    set( "min",  ([ "stats"     : ([ "int": 70 ]),
                    "skills"    : ([ "triforium": 0, "Silvari": 15 ]),
    ]) );
    set( "success", ([ 
        "skills" : ({ "mass hallucination", 1, 1, "spell casting", 1, 1 }),
        "stats"  : ({ "int", 1, 10 }) ]) );
    set( "offchance",  7 );
    set( "delay",  2 );
    set( "no_combat",  0 );
    set( "private",  1 );
    set( "cost", ([ "mana" : 50 ]) );
}

status okattempt( string arg )
{
    
    if( !::okattempt() )
        return( 0 );

    if( !casting_ok( THISP ) ) return 0;


    if( THISP->test_prop( CastingP ) ) {
        ansi_tell( THISP, "You are already casting a spell!\n", HIY );
        return 0;
    }
    
    if( ENV( THISP )->query( NoCombatP ) )
    {
        ansi_tell( THISP, "You can't cast offensive spells here.\n", HIY );
        return 0;
    }
    return 1;
}

void special()
{
    delay = 100;
    delay = delay - ( THISP->query_skill( "mass hallucination") * 2);
    delay = delay - ( THISP->query_skill( "spell casting"));
    delay = delay / 10;
    if( delay < 2 )
        delay = 2;
    
    subtract_cost();
    
    THISP->add_prop( CastingP );
    THISP->set_prop_value( CastingP, THISO );
    
    tell_player( THISP, "You begin to recite the incantation in Silvari." );
    command( "Silvari In the eyes of the beholder!", THISP );
    command( "Silvari A beautiful world turn over.", THISP );
    call_out( "mess1", delay, THISP, ENV( THISP ));
}

void mess1( object caster, object loc )
{
    if( !objectp( caster ) )
        return;
    if( !still_casting( caster ))
    {
        caster->remove_prop( CastingP );
        return;
    }
    command( "Silvari Soon you will see behind the veil.", caster);
    command( "Silvari A place where only terror dares dwell.", caster);
    call_out( "doit", delay, caster, loc);
}

void doit( object caster, object loc )
{
    if( !objectp( caster ))
        return;
    if( !still_casting( caster ))
    {
        caster->remove_prop( CastingP);
        return;
    }
    if( caster->query_ghost() )
        return;
    if( caster->query_hp() < 0 )
        return;
    
    if( ENV( caster )->test_prop( NoPKP ) ||
        ENV( caster )->test_prop( NoCombatP ) ) 
    {
          ansi_tell( caster, "Magics greater than your stop your "
          "spell!", HIY );
          return;
    }
    
    command( "Silvari Open your eyes wide!", caster );
    command( "Silvari I have brought you to your own living hell!", caster );
    
    if( ENV( caster ) != loc)
    {
        ansi_tell( caster, "Moving around jumbles your spell.", HIY );
        return;
    } 
    if( success_roll() < 0 ) 
    {
        ansi_tell( caster, "Your magic fails you!", HIY );
        tell_room( ENV( caster ), sprintf( "%s's spell fails.\n",
          caster->query_name() ), 
        ({ caster }) );
        return;
    }
    
}
