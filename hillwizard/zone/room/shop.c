#define YX "/zone/fantasy/yxuxacta/"

#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

object shop_ob;

void extra_create()
{
    set( "short", "The Wartzhog Institute of Spellflingery "
      "General Store" );
    set( "ansi_short" , HIB "The Wartzhog Institute of "
      "Spellflingery General Store" NORM );
    set( "day_long" ,
      "Every school needs a bookshop to try to rip off all their "
      "students, and this here is the one at Wartzhog!  The store "
      "is actually outsourced to Junkbob, one of the local hillbillies "
      "that lives around here.  The store itself is a bit of a mess, "
      "but they tend to have what you need when you need it, so it's "
      "hard to complain.  Still though, if it didn't smell like a dead "
      "raccoon, that'd be nice."
    );
    set( "day_light" , WELL_LIT );
    set( "night_light", PART_LIT );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "south" : ZROOM "hallway1" ,
      ])
    );
    set( "reset_data" ,
      ([ 
        "junkbob" : ZMON "junkbob",
      ])
    );
    set( "descs" ,
      ([
      ])
    );

    shop_ob = clone_object( ShopCode );
      move_object( shop_ob, THISO );

    shop_ob->set( "owner_name", "Junkbob Johnson" );
    shop_ob->set( "active_owner", 1 );

    shop_ob->set( "sign_header", 
      "Junkbob's Banjers an' Stuff "  );
    shop_ob->set( "short", "a rusted out metal sign" );

    shop_ob->add( "permanent_item", ZOBJ "banjo" );
    shop_ob->add( "permanent_item", YX "obj/misc/shaftdust/mop_bucket" );
    shop_ob->add( "permanent_item", YX "obj/weapon/shaftdust/shovel" );
    shop_ob->add( "permanent_item", YX "obj/weapon/shaftdust/mop" );
}

int query_enter_ok( object item, object mover )
{
    if( is_player( item ) && present_clone( ZMON "junkbob", THISO ) )
    {
      call_out( "welcome", 2 );
    }
    return 0;
}

welcome()
{
    object o = present_clone( ZMON "junkbob" );

    if( !o )              { return 1; }
    if( o->in_combat() )  { return 1; }

    command( "say Well howdy!", o );
    command( "say Mah names Cletus, but erryone calls me "
      "Junkbob, on accounta i got alls this junk.", o );
    command( "say What'n I do's fer ya?", o );
    return 1;
}
