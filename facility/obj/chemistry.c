#include <facility.h>

inherit NewThingCode;
inherit AnsiTellCode;
int howmany;

void extra_create()
{
    howmany = 10;
    set_ids( ({ "set", "chemistry set", "equipment", "lab equipment" }) );
    set_short( "some lab equipment" );
    set_long( "This facility is clearly well stocked. The equipment here "
      "is more than you have ever seen in your life. Incubators, beakers, "
      "bunson burners all lay around waiting for someone to perform an "
      "experiment." );

    set_gettable( 0 );
    set_droppable( 0 );
}

void extra_init()
{
    add_action( "experiment", "perform" );
}

int experiment( string arg )
{
    string *colors = ({ "red", "white", "blue", "purple", "orange"
      "green", "mauve", "pink", "brown" });
    string *chemical = ({ "mephitic", "pleasant", "glowing"
      "ephorvesant", "bubbling", "delicious" });
    string *items = ({ "incubator", "centrifuge", "test tube" });
    string hero = THISP->query_name();
    int event = random( 100 );
    int dam = THISP->query_stat( "con" ) + random ( 40 );
    
    if( !stringp( arg ) || arg != "experiment" )
        return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    howmany = howmany - 1;    
    
    if( howmany <= 0 )
    {
      tell_player( THISP, "Looks like someone has used up all "
        "the supplies! Hopefully it will be restocked soon.\n" );
      call_out( "restock", 1000 );
      return 1;
    }
    
    tell_room( THISO, sprintf( "%s gets a wild look in %s eyes, the "
      "experiment is afoot!\n", hero, possessive( THISP ) ), 
      ({ THISP }) );
    
    if( event <= 30 )
    {
      tell_player( THISP, sprintf( "You twist open a jar and "
      "pull out some sort of preserved animal parts. You grab a "
      "container of %s powder and mix it with some %s chemicals. "
      "you throw the whole mess in a nearby incubator.\n", 
      colors[ random( sizeof( colors ) ) ],
      chemical[ random( sizeof( chemical ) ) ] ) );
      
      tell_player( THISP, "Your creation emerges! "
        "You have done it! You have created sticky smelly garbage. "
        "But with an alcohol content!\n" );
      move_object( clone_object( FOBJ "cheworgans" ), THISP );
      
      return 1;
    }

    if( event > 30 && event <= 55 )
    {
      tell_player( THISP, sprintf( "You mix together "
        "some %s powder, a bit of %s chemicals, and "
        "throw them in a %s.\nNothing happens.\n", 
        colors[ random( sizeof( colors ) ) ],
        chemical[ random( sizeof( chemical ) ) ],
        items[ random( sizeof( items ) ) ] ) );
    
        return 1;
    }
    
    if( event > 55 && event <= 70 )
    {
      tell_player( THISP, sprintf( "You mix together "
        "some %s powder, a bit of %s chemicals, and "
        "throw them on the near by bunson burner!\n "
        "They explode!",
        colors[ random( sizeof( colors ) ) ],
        chemical[ random( sizeof( chemical ) ) ] ) );
      
      ansi_tell_room( ENV( THISO ), sprintf( "%s "
        "is knocked back as %s experiment explodes!",
        hero, possessive( THISP ) ), YEL, ({ THISP }) );

      THISP->take_damage( dam, 0, "fire", THISO );
      return 1;
    }      
    
    if( event > 70 && event < 80 )
    {
      tell_player( THISP, sprintf( "Inspired "
        "by some divine force you make a deep "
        "cut in your arm! You mix the blood "
        "with some %s powder, it smells awful. "
        "Suddenly something explodes from the "
        "floor!\n",
        colors[ random( sizeof( colors ) ) ] ) );

      ansi_tell_room( ENV( THISO ), "There is a "
        "horrible smell, then a tentacle erupts "
        "from the floor!\n", RED, ({ THISP }) );
      
      object ten = clone_object( FMONS "tendrils" );
      move_object( ten, ENV( THISO ) );
      ten->attack_object( THISP );
	  THISP->add_combat_delay( 5 );
      
      return 1;
    }
    
    if( event > 80 )
    {    
      tell_player( THISP, "You grab a bit of old chewing "
        "gum from under a nearby table. In a frenzy of science "
        "you open a jar of organs and throw it in with the "
        "gum in an incubator! The incubator dings, you have "
        "created a gum beast!" );
        
      ansi_tell_room( ENV( THISO ), sprintf( "The incubator dings and "
        "a horrible gum beast emerges! You wish that %s would "
        "leave science to the scientists.", hero ), RED, ({ THISP }) );
      
      object gum = clone_object( FMONS "gum" ); 
      move_object( gum, ENV( THISO ) );
      gum->attack_object( THISP );
      
      return 1;
    }
}

void restock()
{
    howmany = 10;
}
