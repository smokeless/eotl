//an explosive trap that blows your armor off
//and does some damage.
//Taplash 2015
#include<ansi.h>
inherit "/zone/null/stuff/base/trap";
inherit AnsiTellCode;

void extra_create()
{
    set( "trap_name", "an explosive trap" );
    add( "id", "explosive trap" );
    add( "id", "trap" );
    add( "id", "explosive" );
    set( "spawn_limit", 3 );
    set( "ready", 1 );
    set( "difficulty", 8 );
    set( "time_delay", 0 );
    set( "hidden", 1 );
    set( "reset_on_trip", 0 );
}

void effect( object tripper )
{
    object vic = tripper;
    int nearBlastDam = random( ( vic->query_max_hp() )/ 10 ) + 10; 
    int splashDamage;
    object *vicArmor = vic->query_armor_worn();
    object *roomInventory = all_inventory( ENV( THISO ) );
    
    ansi_tell_room( ENV( THISO ), sprintf( "%s triggers an explosive trap! "
      "A loud *BANG* proceeds the flames that engulf you.", vic->query_name() ), 
      RED, ({ vic }) );
    
    ansi_tell( vic, sprintf( "You hear a loud *BANG* as you trigger " 
      "an explosive trap! The blast knocks your equipment off of you." ), 
      RED );
    
    foreach( object o : vicArmor )
      call_other( "/secure/player/commands/remove", "remove_armor", vic, o, 0 );
    
    if( !vic->query_weapon() == 0 )
      command( "unwield", vic );
    
    if( vic->query_hp() <= nearBlastDam )
      vic->DeathSequence( vic, "didn't MacGyver a bomb properly" );
    
    vic->take_damage( nearBlastDam, 0, "fire", THISO );
    
    foreach( object o : roomInventory )
    {
      if( o->is_player() && o != vic )
      {
        splashDamage = random( ( o->query_max_hp() ) / 20 ) + 10;
        o->take_damage( splashDamage, 0, "fire", THISO );
      }
    }
    set( "trap_name", "a detonated explosive trap" );
}
