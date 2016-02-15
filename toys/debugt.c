inherit NewThingCode;

int time;
int last_time;

void extra_create()
{
    set_ids( ({ "debug log", "debugger", "debug log wizard",
      "log wizard", "thingy" }) );
    set_short( "a debug log thingy" );
    set_long( "This little thingymabobber will keep a "
      "wizard up to date on the debug log located at "
      "/Debug.log. Syntax is <debugger [on|off] time >" );
    set_weight( 0 );
    set_value( 0 );
    set_heart_beat( 0 );
}

int query_prevent_shadow()
{
    return 1;
}

void extra_init()
{
    add_action( "debugger", "debugger" );
}

int debugger( string arg )
{
    string on;
   
    if( !is_wizard( THISP ) )
    {
       tell_player( THISP, "You shouldn't have this.\n" );
       destruct( THISO );
       return 1;
    }
    
    if( !stringp( arg ) )
      return notify_fail( "Need string.\n" );
    
    sscanf( arg, "%s %s", on, time );
    to_int( time );    
    
    if( time < 2 )
    {
      tell_player( THISP, "That is way too fast. Try a longer "
        "time frame." );
      return 1;
    }      
    
    if( on == "on" )
    {
      set_heart_beat( 1 );
      last_time = time();
      return 1;
    }
    
    if( on == "off" )
    {
      set_heart_beat( 0 );
    }
    
    return 1;
}

void heart_beat()
{ 
    if( time() - last_time <= time )
    {  
      tail( "/Debug.log" );
      last_time = time();
    }
}
    
