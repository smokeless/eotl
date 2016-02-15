inherit BaseCommand;
inherit AnsiTellCode;
#include <ansi.h>
#include <hillwizard.h>

void extra_create()
{
    set( "name", "summon shield");
    set( "help", 
      "Spell : Summon Shield\n"
      "Cost  : All the mana!\n"
      "Type  : Conjuration\n" 
      "Usage : summon shield\n"
      "\n"
      "\n"
      "    Hillwizards may not know much about magic " 
      "but they can summon shields. This ancient skill "
      "was developed at a monster truck rally riot by "
      "Cletus MacDermit. Things just got too far out of "
      "hand and good ol' cletus started trying to dodge "
      "the crowds. Next thing you know, he had a magic "
      "shield. Pretty bad ass.\n"
      "This shield is basically mandatory for hillwizards "
      "you can't do much of anything without your shield." );
    set( "action", "summon" );
    set( "verb", "shield" );
    set( "usage", "summon shield" );
    set( "guild", "hillwizard" );
    set( "class", "Conjuration" );
    set( "function", "shield_me" );
    set( "success", ([ "skills" : ({ "summon shield", 1, 1 }) ]) );
    set( "offchance",  6 );
    set( "delay",  4 );
    set( "no_combat",  0 );
    set( "private",  1 );
}
 
void shield_me()
{
    
    int shield_skill = THISP->query_skill( "summon shield" );
    
    if( THISP->query_mana() < THISP->query_max_mana() )
      return( ansi_tell( THISP, "You don't have the mana "
        "to do that.", RED ) );
    
    if( present_clone( GOBJ "shield", THISP ) )
      return( ansi_tell( THISP, "Uh, you already have one.",
        RED ) );
    
    THISP->add_mana( -THISP->query_max_mana() );
 
    if( success_roll() < 0 )
      return( ansi_tell( THISP, "Oops you didn't do it right.", 
        RED ) );
    
    ansi_tell( THISP, "You do some funky shit and a shield "
      "pops into your inventory!", BLUE );
    tell_room( ENV( THISP ), sprintf( "%s does some "
      "funky shit and bam, %s has a shield.",
      THISP->query_name(), subjective( THISP ) ), 
     ({THISP}) );
    
    load_object( GOBJ "shield" ); //make sure it works;
    object shield = clone_object( GOBJ "shield" );
    shield->make_better( shield_skill );
    move_object( shield, THISP );                                      
}
