#include <ansi.h>

inherit BaseCommand;
inherit AnsiTellCode;

#define SHAD "/usr/taplash/shaman/obj/lightningshad"
 
void extra_create()
{
    set( "name", "lightning shield");
    set( "help", 
         "Spell : Lightning Shield\n"
         "Cost  : 60 Mana\n"
         "Type  : Enchantment\n" 
         "Usage : cast lightning shield\n"
         "Requirements : 50 Int, 20 Dex, 30 Wil, "
         "10 natural attunement. Must be outside.\n"
         "\n"
         "Nature protects her own. A well attuned shaman "
         "is capable of summoning a bolt of lightning to "
         "wrap them in a shield of electricity. The shield "
         "will have limited protection of course. But it's "
         "better than nothing.\n" );         
    set( "action", "cast" );
    set( "verb", "lightning shield" );
    set( "usage", "cast lightning shield" );
    set( "guild", "shaman" );
    set( "class", "Enchantment" );
    set( "function", "special" );
    set( "cost", ([ "mana" : 60 ]) );
    set( "success", ([ 
        "skills" : ({ "lightning shield", 1, 1, "natural attunement", 1, 1 }),
        "stats"  : ({ "int", 1, 7, "wil", 1, 1 }) ]) );
    set( "offchance",  3 );
    set( "delay",  0 );
    set( "no_combat",  1 );
    set( "private",  1 );
}

            
int okattempt()
{
    if( !::okattempt( THISP ) ) 
      return 0;
    
    //Not using min because, I like to see ansi!
    
    if( THISP->query_skill( "natural attunement" ) < 10 ||
        THISP->query_stat( "int" ) < 50                 ||
        THISP->query_stat( "dex" ) < 20                 ||
        THISP->query_stat( "wil" ) < 30 )
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
    
    if( THISP->lightning_shielded() )
      return( ansi_tell( THISP, "You are already shielded!", HIY ), 0 );
      
    return( 1 );
}
 
void special()
{
    object shad;
    int dam = random( THISP->query_hp() - 5 ); //Don't want it to kill them
    
    ansi_tell( THISP, sprintf( "You wave your %ss around, the sky "
      "above you darkens. Lightning flashes in the clouds and "
      "thunder rumbles!!!", THISP->query_hand_name() ), HIK );
    
    ansi_tell_room( ENV( THISP ), sprintf( "%s waves %s %s around. "
      "The sky above you darkens. Lightning flashes in the clouds "
      "and thunder rumbles!!!", CAP( THISP->query_name() ),
      possessive( THISP ), THISP->query_hand_name() ), HIK, ({ THISP }) );
     
    subtract_cost();
    
     
    if( success_roll() <= 0 )
    {
      ansi_tell( THISP, "You are struck by a powerful bolt of "
        "lightning! You are not well enough attuned to nature "
        "to absorb its power!!! As quickly as the storm came, "
        "it vanishes.", HIY );
      ansi_tell_room( ENV( THISP ), sprintf( "%s is struck by a "
        "bolt of lightning! As quickly as the storm arrived, "
        "it vanishes.", CAP( THISP->query_name() ) ), HIY,
        ({ THISP }) );        
      THISP->take_damage( dam, 0, "electric", 0, 0 );
      return;
    }
    
    ansi_tell( THISP, "You are struck by a powerful bolt of "
      "lightning! You absorb its power and the storm vanishes.",
      HIY );
    ansi_tell_room( ENV( THISP ), sprintf( "%s is struck by a "
        "bolt of lightning! As quickly as the storm arrived, "
        "it vanishes.", CAP( THISP->query_name() ) ), HIY,
        ({ THISP }) );

    shad = clone_object( SHAD );
    shad->sh_init( THISP );
    return;
}
