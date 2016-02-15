#include <facility.h>

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "egg", "black egg" }) );
    set_short( "a gigantic black egg" );
    set_ansi_short( HIK "a gigantic black egg" );
    set_long( "This egg has got to be two feet in diameter at "
      "it's largest point. The shell is a shiny and black. "
      "The shell is thick but someone with enough "
      "strength could probably crack it open." );

    set_gettable( 0 );
    call_out( "hatch", 45 + random( 20 ) );
}

void extra_init()
{
    add_action( "crack", "crack" );
}

int crack( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "egg" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );

    if( THISP->query_stat( "str" ) < 70 )
    {
      tell_player( THISP, "You try as hard as you can, but "
        "the shell is too thick.\n" );
      tell_room( ENV( THISO ), sprintf( "%s tries to break "
        "the egg open. %s fails miserably.\n", hero, 
        subjective( THISP ) ), ({ THISP }) );
      return 1;
    }
    
    tell_player( THISP, "You decide you've had enough "
      "of this egg. You round house kick your way through "
      "the shell. A gooey mess seeps out and into the ground.\n" );
    
    tell_room( ENV( THISO ), sprintf( "%s goes over to the egg "
      "and begins round house kicking it! It cracks and "
      "a gooey mess seeps into the ground.\n", hero ),
      ({ THISP }) );
    
    destruct( THISO );
    return 1;
}

int hatch()
{
    tell_room( ENV( THISO ), "The egg begins to shake violently! "
      "Tiny cracks form along it's surface, suddenly the entire "
      "thing explodes! It looks like this egg was a tendril "
      "egg!\n", ({ }) );
    
    move_object( clone_object( FMONS "tendrils" ), ENV( THISO ) );
    
    destruct( THISO );
    return 1;
}
