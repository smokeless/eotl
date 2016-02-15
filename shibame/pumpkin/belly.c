/*
Belly of The Great Pumpkin. It's for halloween.
It ties into the pumpkin. It's fun.
Socialism 2012
*/

#include <ansi.h>

inherit RoomPlusCode;
inherit AnsiTellCode;

#define LOCS ({ \
"/zone/fantasy/kanori/calador/fishers_edge/rooms/001", \
"/zone/fantasy/krynn/rooms/forest/15", \
"/zone/present/hillbilly/room/parkinglot1", \
"/zone/present/sports/football/rooms/homezone_1", \
"/zone/null/newhaven/rooms/streets/Prosp03", \
})

#define PUMP "/usr/socialism/pumpkin/pumpkin"
#define BLINDOBJ "/usr/socialism/pumpkin/blindobj"

void extra_create()
{
    set( "short", "The Great Pumpkin's Belly" );
    set( "ansi_short", YEL "The Great Pumpkin's Belly" );
    
    set( "day_long", "This place is digusting. It smells "
      "of pumpkiny stomach acid. The acid comes up to your "
      "knees, but doesn't seem to be digesting you. Though "
      "it is possible that you just don't have enough of it "
      "on you. The walls and ceiling are made of soft orange "
      "flesh. Just underneath the flesh someone has installed "
      "electrical conduits." );
    
    set( "day_light", PART_LIT  );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( NoCombatP, 1 );
    
    set( "descs",
    ([ 
       "acid" : 
         "The acid is light orange and smells awful. "
         "Every once in awhile it bubbles. It's deep "
         "enough that you could swim in it. There is "
         "absolutely no way that swimming in acid is "
         "a bad idea.",
 
      ({ "wall", "walls", "ceiling", "flesh"  }) :
        "The flesh pulses with the Great Pumpkin's "
        "heart beat. It looks soft enough "
        "that you might be able to rip some "
        "free. The Great Pumpkin probably wouldn't "
        "even notice!",
      
      ({ "conduit", "conduits", "electrical" }) :
        "The conduit is weather-proof. It runs all "
        "through the stomach walls. You might be able to "
        "tear some of it out. What could go "
        "wrong?"        
    ]) );
    
    call_out( "sick", 300 );
}

void extra_init()
{
    add_action( "flesh"    , "rip" );
    add_action( "conduit"  , "tear" );
    add_action( "swim"     , "swim" );
    add_action( "donothing", "quit" );
}

int conduit( string arg )
{
    object *blind = all_inventory( THISO );
    object pumpkin, tmp, *blinded;
    string player;
    int x, i;
    
    if( !stringp( arg ) || arg != "conduit" && arg != "out conduit" )
      return notify_fail( "Tear out what?\n" );
    
    if( !sizeof( clones( PUMP ) ) )
    {  
      tell_player( THISP, "Something is broken. Mail Socialism.\n" );    
      return 0;
    }
    
    object *y = clones( PUMP );
    pumpkin = y[0];
    
    tell_room( THISO, sprintf( "%s froths at the mouth! %s has spent "
      "too much time in here! %s tears a piece of conduit out from "
      "the wall! There is a flash of white light you are blinded!!!\n",
      THISP->query_name(), CAP( subjective( THISP ) ),
      CAP( subjective( THISP ) ) ), ({ THISP }) );
    tell_player( THISP, "You've had enough of this. You march over "
      "to the wall and rip out a piece of conduit. There is a "
      "flash of bright light. You are blinded!!!!\n" );
    
    blinded = ({ });
    for( x = 0; x < sizeof( blind ); x++ )
      if( living( blind[x] ) )
        blinded += ({ blind[x] });
    
    for( i = 0; i < sizeof( blinded ); i++)
    {
      tmp = clone_object( BLINDOBJ );
      move_object( tmp, blinded[ i ] );      
    }
    
    return 1;
}    
    
int flesh( string arg )
{
    object pumpkin;
    
    if( !sizeof( clones( PUMP ) ) )
    {
      tell_room( THISO, "Something is broken! Mail Socialism!\n" );
      return 1;
    }
    
    if( !stringp( arg ) || arg != "flesh" )
      return notify_fail( "Rip what?\n" );
    
    object *y = clones( PUMP );
    pumpkin = y[0];
    
    tell_room( THISO, sprintf( "%s walks over to the "
      "wall and rips at the orange flesh! You hear a loud "
      "groaning sound. A giant Tums tablet falls into the "
      "room narrowly missing you. It is quickly absorbed in "
      "the acid.\n", THISP->query_name() ), ({ THISP }) );
    tell_player( THISP, "You walk over and begin ripping at the "
      "orange flesh. You hear a loud groaning sound.  A giant Tums "
      "tablet falls into the room narrowly missing you. It is "
      "quickly absorbed in the acid.\n" );
    
    pumpkin->heartburn( THISP->query_name() );
    
    return 1;
}

int donothing( string arg )
{
    tell_player( THISP, "Quit? Now? You'll miss "
      "out on so much fun!\n" );
    return 1;
}

int sick()
{
    object pumpkin;
    object *chunks = all_inventory( THISO );
    int x;
    
    if( !sizeof( clones( PUMP ) ) )
    {
      tell_room( THISO, "If you are seeing this something is "
        "broken. Mail Socialism.\n" );
      call_out( "sick", 300 );
      return 1;
    }
    
    object *y = clones( PUMP );
    pumpkin = y[0];
    int i = random( sizeof( LOCS ) );
    string location = LOCS[ i ];
    
    if( sizeof( chunks ) < 1 )
    {
        call_out( "sick", 300 );
        return 1;
    }
    
    tell_room( ENV( pumpkin ), "The Great Pumpkin suddenly looks "
      "sick. It begins to projectile vomit, the distance the "
      "vomit is travelling is incredible!\n" );
      
    tell_room( THISO, "The stomach acid burbles! Suddenly the "
      "acid is expelled and everything with it! You fly through " 
      "the air riding on a stream of vomit!\n" );
    
    for( x = 0; x < sizeof( chunks ); x++)
    {
      move_object( chunks[x], location );
      
      tell_object( chunks[x], "You crash into the ground. "
        "You are stinky but alive.\n" );
      tell_room( ENV( pumpkin ), sprintf( "%s flies out of the "
        "pumpkins mouth along with a stream of projectile vomit.\n",
      chunks[x]->query_name() ), 
     ({ chunks[x] }) );      
    }
    
    call_out( "sick", 300 );
    return 1;
}

int swim( string arg )
{
    object *worn;
    string short;
    int item;
    if( !stringp( arg ) || arg != "acid" &&
      arg != "in acid" )
      return notify_fail( "Swim in what?\n" );
    
    tell_room( ENV( THISP ), sprintf( "%s holds %s "
      "nose and goes for a swim in the stomach acid.\n",
      THISP->query_name(), possessive( THISP ) ),
      ({ THISP }) );
    
    if( sizeof( THISP->query_armor_worn() ) == 0 )
    {
      tell_player( THISP, "You swim around in the acid. "
        "It's disgusting.\n" );
      return 1;
    }
    
    worn = THISP->query_armor_worn();
    item = random( sizeof( worn ) );
    tell_player( THISP, sprintf( "You swim around in the acid, "
      "%s melts right off your body.\n", 
      worn[ item ]->query_short() ) );
    
    destruct( worn[ item ] );
    
    return 1;
}
