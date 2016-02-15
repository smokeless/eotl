#include <ansi.h>

inherit BaseCommand;
inherit AnsiTellCode;

#define RAIN "/usr/taplash/shaman/obj/rain_obj"
 
void extra_create()
{
    set( "name", "healing rain");
    set( "help", 
         "Spell : Healing Rain\n"
         "Cost  : 100 Mana\n"
         "Type  : Elemental Water\n" 
         "Usage : cast healing rain\n"
         "Requirements : 50 Int, 40 Str, 50 Wil, "
         "15 natural attunement. Must be outside.\n"
         "\n"
         "There is nothing more cleansing than fresh "
         "rain. Even more sore if it has been augmented "
         "by a powerful shaman. This is one of the most "
         "famous of shamanistic powers. It allows the "
         "shaman to heal large groups of creatures all "
         "at once. Friend or foe, mother nature does not "
         "care." );         
    set( "action", "cast" );
    set( "verb", "healing rain" );
    set( "usage", "cast healing rain" );
    set( "guild", "shaman" );
    set( "class", "Elemental Water" );
    set( "function", "special" );
    set( "cost", ([ "mana" : 100 ]) );
    set( "success", ([ 
        "skills" : ({ "healing rain", 1, 4, "natural attunement", 1, 3 }),
        "stats"  : ({ "int", 1, 3, "wil", 1, 3, "str", 1, 3 }) ]) );
    set( "offchance",  4 );
    set( "delay",  0 );
    set( "no_combat",  1 );
    set( "private",  1 );
}

            
int okattempt()
{
    if( !::okattempt( THISP ) ) 
      return 0;
    
    //Not using min because, I like to see ansi!
    
    if( THISP->query_skill( "natural attunement" ) < 15 ||
        THISP->query_stat( "int" ) < 50                 ||
        THISP->query_stat( "str" ) < 40                 ||
        THISP->query_stat( "wil" ) < 50 )
      return(  ansi_tell( THISP, "You are not skilled enough to "
          "do that!", HIY ), 0 );

    if( THISP->query_delay() ) 
      return( ansi_tell( THISP, "You cannot cast a spell right "
        "now!", HIY ), 0 );

    if( THISP->test_prop( CastingP ) ) 
      return( ansi_tell( THISP, "You are already casting a "
        "spell!", HIY ), 0 );

    if( THISP->test_prop( MuteP ) )
      return( ansi_tell( THISP, "You cannot cast spells if you cannot "
        "talk!", HIY ), 0 );

    if( ENV( THISP )->query( UnderwaterP ) )
      return( ansi_tell( THISP, "You cannot speak underwater enough to cast "
        "a spell.", HIY ), 0 );

    if( ENV( THISP )->query( NoMagicP ) )
      return( ansi_tell( THISP, "Magic has been banished from this "
        "area.\nYou cannot conjure enough power to overcome the ban.",
        HIY ), 0 );
    
    if( !ENV( THISP )->query( OutsideP ) )
      return( ansi_tell( THISP, "You are not outside!", HIY ), 0 );
    
    if( present_clone( RAIN, ENV( THISP ) ) )
      return( ansi_tell( THISP, "It is already raining!", HIY ), 0 );
      
    return( 1 );
}
 
void special()
{   
    THISP->add_prop( CastingP );
    THISP->set_prop_value( CastingP, THISO );
    
    ansi_tell( THISP, sprintf( "You wave your %ss around, the sky "
      "above slowly begins to change in coloration.", 
      THISP->query_hand_name() ), CYAN );
    
    ansi_tell_room( ENV( THISP ), sprintf( "%s waves %s %s around. "
      "The sky above you begins to change in coloration.", 
      CAP( THISP->query_name() ), possessive( THISP ), 
      THISP->query_hand_name() ), CYAN, ({ THISP }) );
     
    subtract_cost();
    call_out( "phase_2", 2, THISP, ENV( THISP ) );
}

void phase_2( object caster, object castenv )
{
    int dur = random( caster->query_skill( "natural attunement" ) ) +
      random( caster->query_skill( "healing rain" ) ) + 30;
    int attune = caster->query_skill( "natural attunement" );
    int str = caster->query_stat( "str" );
    int hrain = caster->query_skill( "healing rain" );
      
    object rainobj;
    caster->remove_prop( CastingP );
    
    if( caster->test_prop( MuteP ) )
    {
      ansi_tell( caster, "You can not speak to finish your "
        "spell!", HIY );
      return;
    }

    if( ENV( caster )->query( UnderwaterP ) )
    {
      ansi_tell( caster, "You cannot speak underwater.", HIY );
      return;
    }
   
    if( ENV( caster )->query( NoMagicP ) )
    {
      ansi_tell( caster, "There is an anti-magic field preventing "
        "you from casting your spell!", HIY );
      return;
    }
    
    if( caster->query_ghost() )
      return;    

    if( !interactive( caster ) && query_once_interactive( caster ) ) 
      return;
    
    if( caster->query_hp() <= 0 ) 
      return;

    if( !objectp( caster ) )
      return;
    
    if( ENV( THISP ) != castenv )
    {
      ansi_tell( caster, "Your movement has "
        "interupted your casting!", HIY );
      return;
    }
    
    if( success_roll() <= 0 )
    {
      ansi_tell( caster, "You concentrate on "
      "nature. Willing and shaping it. You whistle sharply, "
      "nothing happens. The sky returns to its normal color.",
      CYAN );
      ansi_tell_room( ENV( THISP ), sprintf( "%s whistles "
        "sharply. Nothing seems to happen. The sky returns "
        "to its normal color.", caster->query_name() ),
        CYAN, ({ caster }) );
      return;
    }
    
    ansi_tell_room( ENV( caster ), sprintf( "%s whistles sharply. "
      "The sky turns green. Soothing rain begins to fall.",
      caster->query_name() ), CYAN, ({ caster }) );
    
    ansi_tell( caster, "You concentrate on "
      "nature. Willing and shaping it. You whistle sharply, "
      "the sky turns green and soothing rain begins to fall.",
      CYAN );
    
    rainobj = clone_object( RAIN );
    move_object( rainobj, ENV( caster ) );
    rainobj->set_me_up( dur, attune, hrain, str );
    return;
}
