//A poison vial. Poison some food or drink.
//Taplash 2015

#include <ansi.h>
inherit NewThingCode;
inherit AnsiTellCode;
#define SUPPORT "/usr/taplash/stuff/poisonsupport"

void extra_create()
{
    set_ids( ({ "poison", "vial of poison", "vial" }) );
    set_short( "a vial of poison" );
    set_long( "This is a vial of poison. It has a picture of a "
      "crossed out dead bug on the label. It is clearly for "
      "killing insects. The fluid inside is odorless, probably "
      "tasteles. The label reads: \"Not for human consumption.\"" );
    set_weight( 1 );
    set_value( 300 );
    set( NoStoreP, 1 );
}

void extra_init()
{
    add_action( "poison", "poison" );
    add_action( "drink", "drink");
}
int drink( string arg )
{
    if( arg != "poison")
    {
        tell_player( THISP, "What are you trying to drink?");
        return 1;
    }
    if( arg == "poison")
    {
        ansi_tell( THISP, "You down a vial of poison. It tastes "
          "like grape soda. Also death.", RED );
        ansi_tell_room( ENV(THISP), sprintf( "%s downs a vial of poison.",
          THISP->query_name() ), RED, ({ THISP }));
        THISP->DeathSequence( THISP, "drinking poison. Who knows why" );
        //Don't drink poison? wtf.
        destruct( THISO );
        return 1;
    }
    return 1;
}

mixed poison( string str )
{
    object poisonedItem, shad;
    object poisoner = THISP;
    
    if( !present( str, THISP ) )
      return notify_fail( "You don't have that.\n" );
    
    poisonedItem = present( str, THISP );
    
    if( !poisonedItem->query( "heal_action" ) )
      return notify_fail( "That would not be a suitable use of this poison.\n" );
    
    if( poisonedItem->poisoned_item() )
        return notify_fail( "That's already poisoned.\n");
      
    tell_player( THISP, sprintf( "You poison %s.", poisonedItem->query( "short" ) ) );
    
    tell_room( ENV( THISP ), sprintf( "%s pours a vial of liquid over %s.\n",
      THISP->query_name(), poisonedItem->query( "short" ) ), ({ THISP }) );
    
    shad = clone_object( "/usr/taplash/stuff/poisonsupport" );
    
    shad->sh_init( poisonedItem, poisoner );
    
    destruct( THISO );
    return 1;
}
