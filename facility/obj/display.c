#include <facility.h>;

inherit NewThingCode;

int featured;

void extra_create()
{
    string item;
    featured = random( 3 );
    switch( featured )
    {
      case 0 : item = "a spooky doll";
               set_descs( ([ ({ "doll", "spooky doll", "a spooky doll" }) :
                 "This is an old porcelain doll. Its eyes have been ripped "
                 "out of its head. Its matted hair looks like it once "
                 "belonged to a living creature." ]) );
               featured = 0;
               break;              
      case 1 : item = "a spirit board";
               set_descs( ([ ({ "board", "spirit board", "ouija board" }) :
                 "This board was cut from the top of an old oak stump. "
                 "All the letters of the alphabet have been burned into "
                 "the top of it." ]) );
               featured = 1;
               break;
      case 2 : item = "a book of summoning";
               set_descs( ([ ({ "book", "book of summoning", "necronomicon" }) :
                 "The book is bound in some sort of flesh. Someone has "
                 "taken the time to carve a smiling face into the front "
                 "of the cover. It would be cute, if it wasn't for the "
                 "rows of sharp teeth." ]) );
               featured = 2;
               break;
    }
    
    set_ids( ({ "display", "museum display" }) );
    
    set_short( sprintf( "a museum display of %s", item ) );
    set_ansi_short( sprintf( "%sa museum display of %s", YEL, item ) );   
    
    set_long( sprintf( "A large metal case with clear plexiglass windows "
      "set on top of a small stage. It is cordoned off with velvet rope. "
      "At the moment it features %s.",
      item ) );
    
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "button", "press" );
    add_action( "button", "push" );
}

int button( string arg )
{
    string item;
    string hero = THISP->query_name();
    object env = ENV( THISO );
    
    if( !stringp( arg ) && arg != "button" && arg != "illuminated button" )
    {
        return notify_fail( CAP( query_verb() ) + " what?\n" );
    }
    
    tell_player( THISP, "You press the button on the display, "
      "gears clank and turn, the stage lowers, and clanks back "
      "up.\n" );
    tell_room( THISO, sprintf( "%s presses the button on the "
      "display case, gears crank and turn, the stage lowers "
      "then clanks back up.\n", hero) );
    
    
    if( featured == 0 )
    {
      switch( random( 2 ) )
      {     
        case 0 : item = "a spirit board";
                 set_descs( ([ ({ "board", "spirit board", "ouija board" }) :
                   "This board was cut from the top of an old oak stump. "
                   "All the letters of the alphabet have been burned into "
                   "the top of it." ]) );
                 featured = 1;
                 break;
        case 1 : item = "a book of summoning";
                 set_descs( ([ ({ "book", "book of summoning", "necronomicon" }) :
                   "The book is bound in some sort of flesh. Someone has "
                   "taken the time to carve a smiling face into the front "
                   "of the cover. It would be cute, if it wasn't for the "
                   "rows of sharp teeth." ]) );
                 featured = 2;
                 break;
      }
      set_short( sprintf( "a display of %s", item ) );
      set_ansi_short( sprintf( "%sa display of %s", YEL, item) );
  
      set_long( sprintf( "A large metal case with clear plexiglass windows, "
        "set on top of a small stage. It is cordoned off with velvet rope. "
        "At the moment it features %s.",
        item ) );

      return 1;
    }
    
    if( featured == 1 )
    {
      switch( random( 2 ) )
      {
        case 0 : item = "a spooky doll";
                 set_descs( ([ ({ "doll", "spooky doll", "a spooky doll" }) :
                   "This is an old porcelain doll. Its eyes have been ripped "
                   "out of its head. Its matted hair looks like it once "
                   "belonged to a living creature." ]) );
                 featured = 0;
                 break;              
        case 1 : item = "a book of summoning";
                 set_descs( ([ ({ "book", "book of summoning", "necronomicon" }) :
                   "The book is bound in some sort of flesh. Someone has "
                   "taken the time to carve a smiling face into the front "
                   "of the cover. It would be cute, if it wasn't for the "
                   "rows of sharp teeth." ]) );
                 featured = 2;
                 break;
      }
      set_short( sprintf( "a display of %s", item ) );
      set_ansi_short( sprintf( "%sa display of %s", YEL, item) );
  
      set_long( sprintf( "A large metal case with clear plexiglass windows, "
        "set on top of a small stage. It is cordoned off with velvet rope. "
        "At the moment it features %s.",
        item ) );

      return 1;
    }
    
    if( featured == 2 )
    {
      switch( random( 2 ) )
      {
        case 0 : item = "a spooky doll";
                 set_descs( ([ ({ "doll", "spooky doll", "a spooky doll" }) :
                   "This is an old porcelain doll. Its eyes have been ripped "
                   "out of its head. Its matted hair looks like it once "
                   "belonged to a living creature." ]) );
                 featured = 0;
                 break;              
        case 1 : item = "a spirit board";
                 set_descs( ([ ({ "board", "spirit board", "ouija board" }) :
                   "This board was cut from the top of an old oak stump. "
                   "All the letters of the alphabet have been burned into "
                   "the top of it." ]) );
                 featured = 1;
                 break;
      }
      set_short( sprintf( "a display of %s", item ) );
      set_ansi_short( sprintf( "%sa display of %s", YEL, item) );
  
      set_long( sprintf( "A large metal case with clear plexiglass windows, "
        "set on top of a small stage. It is cordoned off with velvet rope. "
        "At the moment it features %s.",
        item ) );

      return 1;
    }
}    
