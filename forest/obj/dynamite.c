#include <forest.h>
inherit NewThingCode;

//based on dynamite from addams.

int pin;

void extra_create()
{
    set_ids( ({ "stick of dynamite", "dynamite", "stick",
      "east face" }) );
    set_short( "a stick of East Face dynamite" );
    set_long( "This is a stick of dynamite.  It has a red waxed paper covering "
    "and a very long fuse extending from one end. The East Face company logo "
    "is stamped on the side. It seems to be intended for trail maitenance.  "
    "It could definately cause a large explosion if it was lit." );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "weight", 100 );
    set( "value", 100 );

    pin = 1;
    set( FlammableP, 1 );
}

string post_long()
{
    if( pin )
        return "The fuse is not lit.\n";
    else
        return "The fuse is burning!\n";
}

string post_short()
{ 
    if( !pin ) return "(lit)";
}

void extra_init()
{
    add_action( "do_light", "light" );
    add_action( "do_throw", "throw" );
}

status boot_them( object them )
{
    string *dirs, dir;
    object e, dest;
    mapping m;

    if( them->test_prop( NoStunP ) ) 
      return 0;
    if( them->test_prop( NoControlP ) ) 
      return 0;
    if( strstr( file_name( ENV( them ) ), "/zone/guild/" ) >= 0 ) 
      return 0;

    e = ENV( them );
    m = e->query( "exits" )+e->query( "invis_exits" );

    if(!m)
      return( 0 );

    if( !sizeof( dirs = m_indices( m ) ) )
        return( 0 );

    dir = dirs[ random( sizeof( dirs ) ) ];
    dest = m[ dir ];

    if( move_object( them, dest ) ) 
    {
      them->glance();
      return(1);
    }
}

int do_light( string s )
{
    if( !s )
      return 0;
      
    if( s != "fuse" && s != "dynamite" )
      return( notify_fail( "What do you want to light?\n" ) );
      
    if( !pin )
      return 0;

    tell_object( THISP, "You light the fuse on the dynamite.\n "
      "A hissing and crackling sound comes from it as the fuse "
      "burns.\n" );
    tell_room( ENV( THISP ), sprintf( "%s lights a stick "
    "of dynamite!\n", PNAME ), ( { THISP } ) );

    pin = 0;
    
    set( NoStoreP, 1 );
    set( NoSellP, 1 );
   
    call_out( "boom", 45 );

    return 1;
}

ignite()
{
    THISO->boom();
}

int boom()
{
    object *all;
    object room;
    object dumbass;
    int x;
    string *dirs;
    string dir;
    object e, dest;
    mapping m;


    if( living( ENV( THISO ) ) )
        room = ENV( ENV( THISO ) );
    else
        room = ENV( THISO );

    if( room->query( NoCombatP ) ) 
    {
        tell_room( room, "The fuse runs out "
        "but nothing happens.\nMust have been a dud.\n" );
        destruct( THISO );
        return 1;
    }

    if( living( ENV( THISO ) ) ) 
    {
        dumbass = ENV( THISO );
        int dam = dumbass->query_hp() / 2;
        dam = dam + random( 4 );
        if( dam > dumbass->query_hp() )
          dam = dumbass->query_hp() - 5;
        
        tell_object( dumbass, "A lit stick of dynamite explodes in "
          "your inventory.\n Guess you forgot you had that huh?\n" );
        tell_room( ENV( dumbass ), sprintf( "%s yelps as a lit stick of "
          "dynamite explodes in %s inventory.\n", dumbass->query_name(),
          possessive( dumbass ) ), ( { dumbass } ) );

        dumbass->take_damage( dam, 0, "fire", dumbass );
    }

    tell_room( room,
"\n"
"      .  .  .\n"
"    . *\\*|*/* .\n"
"  .-***BOOOM***-.\n"
"    . *\\*|*/* .\n"
"      .  .  .\n"
    );

    m = room->query("exits")+room->query("invis_exits");

    all = all_inventory( room );
    for( x = 0; x < sizeof( all ); x++ )  
        if( !all[ x ]->test_prop( GhostP ) && living( all[ x ] ) ) {
            all[ x ]->take_damage( random( 50 )+20, 0, "fire", all[ x ] );
            if( !objectp( all[ x ] ) ) continue;

            if( boot_them( all[ x ] ))
                tell_room( ENV( all[ x ] ), all[ x ]->query_name()+" lands with a heavy "
                "\"THUMP!\"\nThat looks like it hurt.\n",
                ({ all[ x ] }) );
        }

    destruct( THISO );
}

int do_throw( string s )
{
    string dest;
    string egg, dir;
    mapping exits;

    if( !s )
        return 0;
    if( sscanf( s, "%s %s", egg, dir ) != 2 )
        return 0;
    if( !id( egg ) )
        return 0;

    exits = ENV( THISP )->query( "exits" );
    if( !( dest = exits[ dir ] ) )
        return( notify_fail( "There is a wall there.\n" ), 0 );
    if( dest[ 0 ] == '@' &&
            !stringp( dest = eval_arg( dest, dir ) ) )
        return( notify_fail( "Something blocks your way.\n" ), 0 );

    move_object( THISO, dest );
    tell_object( THISP, "You huck the dynamite " + dir + ".\n" );
    tell_room( ENV( THISP ), PNAME + " hucks an stick of dynamite " + s +
    ".\n", ({ THISP }));
    tell_room( ENV( THISO ), "A stick of dynamite flies into the room.\n" );

    return 1;
}
