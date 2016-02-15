inherit ScrollStuff;

void extra_create()
{
  set( "short", "a scroll of net-dead reaping" );
  set( "id", ({ "a scroll of net-dead reaping",
    "net-dead reaping", "reaping", "scroll" }) );
    
  set( "weight", 10 );
  set( "value", 30 );
  
  set( "spawn_limit", 2 );   // limits scroll to 2 copies at a time
  set( "spawn_rate", 100 );  // adds 100% chance of spawning
  return;
}

void read( object who )
{
  tell_object( who, "You read a scroll of net-dead reaping!\n" );
  tell_room( ENV( who ), sprintf( "%s reads from a scroll.\n",
    who->query_name() ) ({ who }) );
  return;
}

void cursed_read( object who )
{
  tell_object( who, "You feel uncool.\n" );
  return;
}

void blessed_read( object who )
{
  tell_object( who, "You feel really cool.\n" );
  return;
}
