#include <facility.h>

inherit MonsterCode;
inherit MonsterTalk;
inherit MonsterMove;

int mountable = 0;
int eggs = 5;

void extra_create()
{
    set_name( "Super Mega Ultra Chicken" );
    add_alias( "mega chicken" );
    add_alias( "chicken" );
    add_alias( "super chicken" );
    add_alias( "ultra chicken" );
    add_alias( "super mega ultra chicken" );
    
    set_short( "Super Mega Ultra Chicken" );
    set_ansi_short ( HIK "Super Mega Ultra Chicken" );
    
    set_long( "This chicken must have soaked up some of "
      "the energy from the experiments at Facility 31. "
      "It is easily ten feet from it's head to it's claws. "
      "It's eyes are neon green and it's black feathers are falling "
      "out in spots. It looks like it might be mountable. "
      "You have no idea as to whether or not you can steer it though. "
      "You also doubt there will be much visibility, this is a very "
      "fat chicken."
    );
    
    set_gender( "female" );
    set_race( "chicken" );
    
    set_alignment( MALICIOUS_AL );
    
    set_stat( "str" , 200 );
    set_stat( "con" , 300 );
    set_stat( "wil" , 500 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 150 );
    set_skill( "dodge", 300 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_avoid_props( ({ NoWanderRoomP }) );
    set_move_rate( 20 );
    set_move_chance( 20 + random( 20 ) );
    
    set_chat_rate( 10 );
    set_chat_chance( 50 );
    
    add_phrase( "#bawk" );
    add_phrase( "#peck" );
    add_phrase( "#growl" );
    
    call_out( "egg", 10 );
}

void extra_init()
{
    add_action( "mount", "mount" );
    add_action( "dismount", "dismount" );
}

string long() 
{ 
    if( THISP && ENV( THISP ) == THISO ) 
      return "/secure/player/commands/look"->look_at_env( ENV( THISO ) ); 
    else
      return ::long(); 
}
    
int mount( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "chicken" )
        return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    if( mountable == 1 )
    {
      tell_player( THISP, "Someone is already riding that!" );
      return 1;
    }
    
    tell_player( THISP, "You climb up onto the back of the chicken! "
      "The chicken nods at you.\n" );
    tell_room( ENV( THISO ), sprintf( "%s climbs onto the back of "
      "the chicken! Amazing!\n", hero ), ({ THISP }) );
    
    set_short( sprintf( "Super Mega Ultra Chicken - %s is "
      "riding it!", hero ) );
    set_ansi_short( sprintf( "%sSuper Mega Ultra Chicken - "
      "%s is riding it!", HIK, hero ) );
    
    move_object( THISP, THISO );
    
    set_move_rate( 10 );
    set_move_chance( 80 );
    
    mountable = 1;
    
    return 1;
}

int dismount( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "chicken" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    tell_player( THISP, "You climb down off the back of the chicken.\n" );
    tell_room( ENV( THISO ), sprintf( "%s climbs off the back of the "
    "chicken.\n", hero ), ({ THISP }) );
      
    move_object( THISP, ENV( THISO ) );
    
    set_short( "Super Mega Ultra Chicken" );
    set_ansi_short( HIK "Super Mega Ultra Chicken" );
    
    set_move_rate( 20 );
    set_move_chance( 20 + random( 20 ) );
    
    mountable = 0;
    return 1;
}

int egg()
{
    eggs = eggs - 1;
    
    if( eggs == 1 )
      return 0;
    
    tell_room( ENV( THISO ), "The chicken begins clucking loudly! "
      "It sits down. When it stands up you see that it has laid "
      "a black egg.\n", ({ }) );
    
    move_object( clone_object( FOBJ "egg" ), ENV( THISO ) );
    
    call_out( "egg", 100 + random( 10 ) );
    
    return 1;
}
