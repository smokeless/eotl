inherit NewThingCode;
inherit AnsiTellCode;
#include <ansi.h>

void extra_create()
{
	int time = random( 500 )+1;
	set_ids( ({ "x77Y" }) );
	set( InvisP, 1 );
	set_short( "jacks" );
	set_gettable( 0 );
	call_out( "phase1", time );
}

void phase1()
{
    int time = random( 200 )+1;
	tell_room( ENV( THISO ), "The sound of chainsaws is "
	  "audible in the distance.\n" );
	call_out( "phase2", time );
}

void phase2()
{    
    int time = random( 100 )+1;
	tell_room( ENV( THISO ), "You can hear the clomping of boots. "
	  "The air is thick with diesel fumes.\n" );
    call_out( "phase3", time );
}
void phase3()
{
    object tree = present_clone( "/zone/null/newhaven/obj/plants/tree.c", ENV( THISO ) );
	string owner = tree->query_owner();
	tell_room( ENV( THISO ), "A group of angry looking "
	  "lumber jacks march into the room!\n" );
	tell_room( ENV( THISO ), sprintf( "With no hesitation they "
	  "bring down %s's tree.\n", owner ) );
	destruct( tree );
	destruct( THISO );
}
	  
