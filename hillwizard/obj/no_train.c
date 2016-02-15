inherit "/usr/taplash/hillwizard/guild.c";

// train_ok overlaid to disable skill training
status train_ok( object me, string skill, int old, int gain, int prof )
{
    if( !::train_ok( me, skill, old, gain, prof ) ) 
      return 0;

  // allows player to 'cost all' or 'cost skill'
    if( skill )
    {
      write( "This isn't where you train that.\n" );
      return 0;
    }

  return 1;
}

join_guild( string arg )
{   
    return load_object( "/usr/taplash/hillwizard/guild" )->join_guild( arg );
}

leave_guild( string arg )
{   
    return load_object( "/usr/taplash/hillwizard/guild" )->leave_guild( arg );
}
