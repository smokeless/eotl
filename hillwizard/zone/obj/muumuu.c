#include <ansi.h>

inherit ArmorCode;

void extra_create()
{
   set( "id", ({ "muumuu", "mumu", "a bright blue muumuu",
     "a blue muumuu", "blue muumuu", "a bright muumuu", }) );
   set( "short" , "a bright blue muumuu" );
   set_ansi_short( HIC "a bright blue muumuu" NORM );
   set( "long",
     "This is a large oversized shirt dress sort of thing that "
     "fat people wear to pretend they're not fat.  There is "
     "no reason to wear a muumuu.  Please don't wear it.  Oh, "
     "God, don't do it!"
   );
   set( "ac" , 3 );
   set( "weight", 25 );
   set( "value", 10 );
   set_material( "cloth" );
   set_material_name( "greasy cloth" );
}

int check_areas( object wearer )
{
    string *locs;
    int x;

    set("areas", ({ }) );
    locs = wearer->query_hit_locations();
    for( x = 0; x < sizeof( locs ); x++ )
      if( stringp( locs[x] ) &&
        locs[x] != "head" &&
        locs[x] != "neck" &&
        locs[x] != "left foot" &&
        locs[x] != "right foot" &&
        locs[x] != "right hand" &&
        locs[x] != "left hand" )
      add( "areas", ({ locs[x] }) );

    return ::check_areas( wearer );
}

void post_wear( object wearer )
{
    tell_player( wearer, "OH GOD WHY DID YOU PUT THIS ON?  "
      "YOU FEEL SO FAT AND UGLY OH GOD WHY?!??!" );
    wearer->add_bonus_object( THISO );
}

void post_remove( object wearer )
{
    tell_player( wearer, "You feel much better without "
      "that stupid muumuu." );
    wearer->remove_bonus_object( THISO );
}

int query_stat_bonus( string arg )
{
    if( arg == "chr" ) return -50;
}

int query_resist_bonus( string arg )
{
    if( arg == "ego" ) return -50;
}

int pigs_can_wear()
{
   return 1;
}
