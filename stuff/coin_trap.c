//A trap that takes 50% coins from inventory.
//This includes bags. These geese are relentless.
//Made to discourage hoarding coins on
//player.
//Taplash 2015
#include<ansi.h>
inherit "/zone/null/stuff/base/trap";
inherit AnsiTellCode;

void extra_create()
{
    set( "trap_name", "a coin stealing trap" );
    add( "id", "coin stealing trap" );
    add( "id", "trap" );
    add( "id", "coin" );
    add( "id", "coin stealing" );
    add( "id", "stealing" );
    set( "spawn_limit", 4 );
    set( "ready", 1 );
    set( "difficulty", 9 );
    set( "time_delay", 0 );
    set( "hidden", 0 );
    set( "reset_on_trip", 1 );
}

void effect( object tripper )
{
    object vic = tripper;
    object *inv = deep_inventory( vic );
    int totalLosses;
    foreach( object o : inv )
    {
      if( o->query( MoneyP ) > 0 )
      {
        int lost = o->query( "money" ) / 2;
        o->add( "money", -lost );
        totalLosses = totalLosses + lost;
      }
    }

    if( totalLosses == 0 )
    {
      ansi_tell( vic, sprintf( "You trigger a coin "
        "stealing trap! A gaggle of trained geese "
        "knock you over and rifle through your things "
        "searching for cash! Luckily you're a bum. "
        "They are gone as quickly as they arrived." ), RED );

      ansi_tell_room( ENV( vic ), sprintf( "%s steps "
        "on a coin stealing trap. %s is encased in a gaggle "
        "of money hungry geese. The geese realize %s is a "
        "bum and run off.", vic->query_name(),
        CAP(subjective( vic )) , subjective( vic ) ) , 
        RED, ({ vic }) );
      return;
    }

    ansi_tell( tripper, sprintf( "You trigger a coin "
      "stealing trap! A gaggle of trained geese "
      "knock you over and rifle through your belongings "
      "for cash! They are gone as quickly as they arrived. "
      "You notice you are missing %i coins.", totalLosses ), 
      RED );

    ansi_tell_room( ENV( THISO ), sprintf( "%s steps on a "
      "coin stealing trap. %s is encased in a gaggle of "
      "money hungry geese! They rough %s up a bit then "
      "run off.", vic->query_name(), CAP( subjective( vic ) ),
      objective( vic ) ), RED, ({ vic }) );
    return;
}
