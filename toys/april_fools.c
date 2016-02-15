#define APRILFOOLS ({ "score", "list", "hp", "group" })

object me;

varargs void sh_init( object player, int time )
{
  me = player;
  shadow( me, 1 );

  call_out( "jokes_over", 600 - time );
}

void jokes_over()
{
  tell_player( me, "April fools!\n<3 Poi" );

  remove_shadow( THISO );
  destruct( THISO );
}

int query_stat( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 1;

  return me->query_stat( str );
}

int query_base_stat( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 1;

  return me->query_base_stat( str );
}

int query_stat_total()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 6;

  return me->query_stat_total();
}

int query_hp()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_hp();
}

int query_max_hp()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_max_hp();
}

int query_mana()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_mana();
}

int query_max_mana()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_max_mana();
}

int query_fatigue()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_fatigue();
}

int query_max_fatigue()
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 5;

  return me->query_max_fatigue();
}

int query_skill( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 0;

  return me->query_skill( str );
}

int query_base_skill( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 0;

  return me->query_base_skill( str );
}

int query_proficiency( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 0;

  return me->query_proficiency( str );
}

int query_base_proficiency( string str )
{
  if( member( APRILFOOLS, query_verb() ) != -1 )
    return 0;

  return me->query_base_proficiency( str );
}
