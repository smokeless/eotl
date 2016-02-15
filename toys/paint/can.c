inherit NewThingCode;
inherit AnsiTellCode;
#include <ansi.h>

void extra_create()
{
	set_ids( ({ "paint", "spraypaint", "marking", "marking paint", "can" }) );
    set_short( "a can of marking paint" );
    set_ansi_short( HIY "a can of marking paint" );
    set_long( "This is a can of marking paint. "
	  "The lid is bright orange. This is just like "
	  "the stuff professional loggers use to paint "
	  "trees. Maybe you should try it out?"
    );
	set( "value", 50000 );
    set( NoStoreP, 1);
}

void extra_init()
{
    add_action( "paint", "paint" );
}

int paint( string strarg )
{
    string person = THISP->query_name();
    object hero = ENV( THISP );
	object tree;
	if( !stringp( strarg ) ||  strarg != "tree"  )
    {
      return notify_fail( query_verb()  + " what?\n" );
    } 
	if( !present_clone( "/zone/null/newhaven/obj/plants/tree.c", ENV( THISP ) ) )
	{
	tell_object( THISP, "There are no trees to paint here!\n" );
	return 1;
	}
	if( present_clone( "/usr/socialism/paint/jackobj.c", ENV( THISP ) ) )
	{
	tell_object( THISP, "Someone has already marked that tree.\n" );
	return 1;
	}
	if( present_clone( "/zone/null/newhaven/obj/plants/tree.c", ENV( THISP ) ) )
	{
	tell_object( THISP, "You rip the lid off the can and spray a huge X on the tree.\n" 
	  "Unfortunately you used all the paint!!!!\n");
	tell_room( ENV( THISP ), sprintf( "%s pops the lid off a can of paint and "
	  "goes hog wild marking up a nearby tree.\n", person ), ({ THISP }) );
	tree = present_clone( "/zone/null/newhaven/obj/plants/tree.c", ENV( THISP ) );
	tree->set( "short", sprintf( "a large, spreading tree. "
	  "%s has marked this tree.", person ) );
	tree->set( "long", sprintf( "You spot a sturdy treehouse "
	  "in the upper branches. This tree has been painted by "
	  "%s for demolition by Nationalized Logging.", person ) );
	string owner = tree->query_owner();
	tell_object( THISP, sprintf( "%s is not going to be happy about this.\n", owner ) );
	object jacks;
    jacks = clone_object( "/usr/socialism/paint/jackobj" );
	move_object( jacks, hero );
	destruct( THISO );
	return 1;
    }
}


