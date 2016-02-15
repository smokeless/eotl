// Sense Focus is a basic
// alignment detection skill.
// Modified for shaman by:
// Socialism 9/12
// Originally by:
// Wilecoyote 11-5-95
// Originally coded by Barnak

#include <ansi.h>

inherit BaseCommand;
inherit AnsiTellCode;
 
void extra_create()
{
    set( "name", "sense focus" );
    set( "help",  
         "Spell : Sense Focus\n"
         "Cost  : 30 Mana\n"
         "Type  : Detection\n"
         "Usage : sense focus\n"
         "Requirements : 40 Wil\n"
         "\n"
         "All shaman are attuned to the spirits that bind and "
         "surround life force. These spirits can be helpful "
         "in discerning what type of life form you are dealing "
         "with. Evil beings tend attract evil spirits, good "
         "beings will attract good spirits. By seeing these "
         "spirits a shaman can sense the focus of the being "
         "they surround." );
    set( "private", 1 );
    set( "action", "sense" );
    set( "verb", "focus" );  
    set( "usage", "sense focus" );
    set( "guild", "shaman" );
    set( "class", "Detection" );
    set( "function", "find_evil" );
    set( "no_combat", 1 );
    set( "cost", ([ "mana" : 15 ]) );
    set( "min", ([ "stats"      : ([ "wil": 40 ])   ]) );
    set( "success", ([ "skills" : ({ "sense focus", 1, 1 }),
                       "stats"  : ({ "wil", 1, 8 }) ]) );
    set( "offchance", 3 );
}
 
int okattempt()
{
    if( !::okattempt() )
      return 0;
      
   return 1;
}

void find_evil()
{   
    int i, foundevil, align, foundgood;
    object *people;      
    string pepname;
 
    people = all_inventory( ENV( THISP ) ); 
    foundevil = 0; 

    subtract_cost();
    combat_delay();            
 
    if( success_roll() < 0 )
      return( ansi_tell( THISP, "The spirits remain invisible to you.", RED ) );
 
    for( i = 0; i < sizeof( people ); i++ )
     {            
      if( living( people[ i ] ) && people[ i ] != THISP &&
        stringp( pepname = people[ i ]->query_name() ) )
       {   
        align = people[ i ]->query_alignment();           
        if( align <= 0 )     
            foundevil = 1;
        if( THISP->query_skill( "detect alignment" ) >= 10 )
         {
          switch( align )
           {
            case 3750..4000:
              ansi_tell( THISP, sprintf( "%s is surrounded by good spirits.",
                     pepname ), HIW );
              break;
            case 3000..3749: 
              ansi_tell( THISP, sprintf( "%s is guided by altruism.", 
                     pepname ), WHT );
              break;
            case 1..2999:
              ansi_tell( THISP, sprintf( "%s has few spirits, though they are "
                "mainly good.",
                     pepname ), GRN );
              break;
            case 0:
              ansi_tell( THISP, sprintf( "%s is completely neutral. There are "
                     "no spirits near.", pepname ), YEL );
              break;
            case -2300..-1:
              ansi_tell( THISP, sprintf( "%s has a few dark spirits clinging on.",
                pepname ), HIR );
              break; 
            case -3000..-2301:
              ansi_tell( THISP, sprintf( "%s is guided by dark spirits.",
                pepname ), HIR );
              break;
            case -4000..-3001:
              ansi_tell( THISP, sprintf( "%s is surrounded by the darkest "
                "of spirits.", pepname ), HIK );
              break;
            default:
              ansi_tell( THISP, sprintf( "%s's soul rests in "
                "Hell.", pepname ), HIK );
              break;
           }
         }
        else 
        {
          switch( align )
          {
            case 1..4000:
              ansi_tell( THISP, sprintf( "%s is linked to the spirits of good.",
                     pepname ), HIG );
              break;
            case 0:
              ansi_tell( THISP, sprintf( "%s has no spirits.", pepname ), HIY );
              break;
            case -4000..-1:
              ansi_tell( THISP, sprintf( "%s is linked to the spirits of evil.", pepname ),
                     HIR );
              break;
          }
        }
       }   
     }
    if( !foundevil )
      ansi_tell( THISP, "You detect no evil.", CYN );
}
