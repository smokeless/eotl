/*
  An artifact of old timey matches.
  They're a kick in the teeth! It's either
  always play with matches, or never play with
  matches. I can't remember which though...
  by: Socialism 2012.
*/

#include <ansi.h>
inherit NewThingCode;

int matches;

void extra_create()
{
    string matchnum;
    
    switch( random( 3 ) )
    {
      case 0 : matches = 1; matchnum = "one";   break;
      case 1 : matches = 2; matchnum = "two";   break;
      case 2 : matches = 3; matchnum = "three"; break;
    }
    
    set_ids( ({ "matches", "match book", "book of matches", 
      "mao's matches" }) );
    
    set_short( "a book of matches" );
    set_ansi_short( RED "a book of matches" );
     
    set_long( sprintf( "This is a book of matches. It is "
      "bright red with a hammer and sickle embossed in "
      "black on the front. The striker is well worn. Upon "
      "opening the pack you discover there are only %s matches. "
      "These matches may not be your standard matches! "
      "striking them may be a surpising event!!!!", matchnum ) );
    
    set_material( "paper" );
}

void extra_init()
{
    add_action( "light",  "strike" );
    add_action( "light",  "light" );
}

int light( string arg )
{
    if( !stringp( arg ) || arg != "matches" )
      return notify_fail( CAP( query_verb() ) + "what?\n" );
    
    if( matches < 1 )
      return notify_fail( "You don't have any matches.\n" );
    
    matches = matches - 1;
    
    return 1;
}    
    
