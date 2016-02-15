#include <facility.h>

inherit NewThingCode;
inherit PropertyCode;

int monsterlim;

void extra_create()
{
    int timetilhungry = random( 200 );
    monsterlim = 3;
    
    set_ids( ({ "well", "old well", "pit", "ancient" }) );
    
    set_short( "an ancient well" );
    set_ansi_short( HIK "an ancient well" );
    
    set_long( "The mortar holding together the stone "
      "is rotted and chipping. The stones somehow have not fallen "
      "apart and into the well. There is no mechanism "
      "to retrieve water from the well. It appears it was "
      "never built with one. Some of the stones at one point "
      "had runes carved into them. Someone has removed as "
      "much as they can of most of the runes. The top "
      "stones are stained and mossy. There is no apparent "
      "bottom to the thing, just inky darkness and humidity. "
      "There is an ancient copper gong sitting next to the "
      "well." );
    
    set_descs( ([ 
      "gong"                  : 
        "All of it has turned green, except for the "
        "word \"C'Szandth\" which is as shiny as the day it "
        "was built. If you hit it, it would probably ring.",
      
      ({ "rune", "runes" })   :
        "They are like nothing you have ever encountered before. "
        "Maybe some sort of ancient language? Maybe a mad mans "
        "sketching.",
        
      ({ "stone", "stones" }) :
        "They look very old. They are almost entirely granite with "
        "bits of slate stuck in as filler."
    ]) );
      
    set_gettable( 0 );
    call_out( "beast", timetilhungry );
}

void extra_init()
{
    add_action( "jump", "jump" );
    add_action( "jump", "leap" );
    add_action( "push", "push" );
    add_action( "hit", "hit" );
}

int jump( string strarg )
{
    string idiot = THISP->query_real_name();
    object room = ENV( THISP );
    
    if( !stringp( strarg ) ||  strarg != "in well" && strarg != "in pit"  )
      return notify_fail( query_verb()  + "in where?\n" );
  
    tell_room( room, sprintf( "%s leaps into the pit! %s "
      "will surely vanquish whatever evil lies below!\n", idiot,
      CAP( subjective( THISP ) ) ), ({ THISP }) );
    
    tell_object( THISP, "Fearlessly you leap into the pit! Someone "
      "has to do it!\n" );
    
    write_file( FROOM "phased", sprintf("%s jumped in well.\n", idiot ) );
    
    THISP->move_player( "&&", FROOM "falling", 1 );
    load_object( FROOM "falling" )->start( THISP );
    
    return 1;
}

int beast()
{
    object skelaf;
    object monster;
    int rawr = random ( 500 );
    
    if( monster = present_clone( FMONS "creature.c", ENV( THISO ) ) )
    {
      tell_room( ENV( THISO ), "A loud roar emits from below\n",
      ({ }) );
      call_out( "beast", rawr );
      return 1;
    }
    
    tell_room( ENV( THISO ), "There is a horrible sound from the "
      "well! Something explodes over the top of the slabs!\n",
      ({ }) );
    
    move_object( clone_object( FMONS+"creature" ), ENV( THISO ) );	
    
    return 1;
}

int hit( string strarg )
{
    int rawr = random ( 500 );
    string hero = THISP->query_name();
    object skelaf;
    object monster;
    monsterlim--;
    
    if( !stringp( strarg ) || strarg != "gong" )
      return notify_fail( query_verb() + " what?\n" );
    
    tell_room( ENV( THISO ), sprintf( "%s goes over to "
      "the gong and hits it. You can hear something moving "
      "around the bottom of the well.\n", hero ), 
      ({ THISP }) );
     
    tell_object( THISP, "You walk over to the gong and "
      "punch it as hard as you can. There is a loud "
      "reverberating ring and you hear something moving "
      "at the bottom of the well.\n" );
    
    if( monsterlim < 1 )
      return 1;    
    
    if( monster = present_clone( FMONS "creature.c", ENV( THISO ) ) )
    {
      tell_room( ENV( THISO ), "A loud roar emits from below\n" );
      call_out( "beast", rawr );
      return 1;
    } 
    
    tell_room( ENV( THISO ), "There is a horrible sound from the "
      "well! Something explodes over the top of the slabs!\n" );
    move_object( clone_object( FMONS+"creature" ), ENV( THISO ) );	
    
    return 1;
}   
