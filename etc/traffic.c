#include <ansi.h>
#define TIME 40 + random( 30 )

inherit NewThingCode;

int check_crash();

string *reds, *greens;
object room;
int g;

void extra_create()
{
  if( root() ) return;
  g = 0;
  set_ids( ({ "light", "traffic light" }) );
  set_short( "a traffic light" );
  set_long( "This is a traffic light. Please wait your turn." );

  set_gettable( -1 );
  set_droppable( -1 );

  set( NoStoreP, 1 );
  set( NoSellP, 1 );
  set( NoCleanUpP, 1 );

  call_out("change", TIME);
}

void get_exits()
{
  string *exit_names;
  int i, del;

  if( !ENV( THISO ) && !root() )
    destruct( THISO );

  if( !room->query( "exits" ) )
    return;

  exit_names = m_indices( room->query( "exits" ) );

  if( sizeof( exit_names ) == 1 ) 
  {
    tell_room( ENV( THISO ), "No light needed here!\n" );
    destruct( THISO );
  }

  greens = exit_names[0..sizeof( exit_names ) / 2 - 1];
  reds = exit_names[sizeof( exit_names ) / 2..];
}

void extra_init()
{
  if( ENV( THISO ) != room ) 
  {
    room = ENV( THISO );
    get_exits();
  }
  if( ENV( THISP ) == room )
    add_action( "check_command", "", 2 );
}

int check_command( string s )
{
  if( !g && searcha( reds, s ) != -1 )
  {
    if( !random( 20 ) )
      return( check_crash() );

    tell_object( THISP, sprintf( "The traffic light is red for %s.  You must "
      "stop.\n", s ) );

    return 1;
  }
  else if( g && searcha( greens, s ) != -1 )
  {
    if( !random( 20 ) )
      return( check_crash() );

    tell_object( THISP, sprintf( "The traffic light is red for %s.  You must "
      "stop.\n", s ) );

    return 1;
  }
  else
    return 0;
}

int check_crash() 
{
 object *inv, picked;
 int hp;

  if( random( 10 ) )
  {
    tell_object( THISP, "You run the red light!\n" );
    tell_room( ENV( THISO ), sprintf( "%s runs the red light!\n",
      THISP->query_name() || "Somebody" ), ({ THISP }) );
    inv = all_inventory( room ) - ({ THISP });

    if( sizeof( inv ) )
    {
      picked = inv[random( sizeof( inv ) )];
      hp = THISP->query_hp() / 4;

      tell_object( THISP, sprintf( "You nail %s in a head on collison!\n",
        picked->query_name() || picked->short() || "something" ) );
      tell_room( ENV( THISO ), sprintf( "%s nails %s in a head in collision!\n",
        THISP->query_name() || "Somebody", picked->query_name() ||
        picked->short() || "something" ), ({ THISP, picked }) );

      THISP->take_damage( random( hp ) + random( hp ), 0, "blunt", picked, 0, 1 );

      if( picked->is_player() )
      {
        tell_object( picked, sprintf( "%s runs a red light and hits you!\n",
          THISP->query_name() || "Somebody" ) );

        hp = picked->query_hp() / 4;
        picked->take_damage( random( hp ) + random( hp ), 0, "blunt", THISP );
      }

      return 0;
    }
 }
 else
   tell_object( THISP, "You successfully run the red light.\n" );
   tell_room( ENV( THISO ), sprintf( "%s successfully runs the red light.\n",
     THISP->query_name() || "Somebody" ), ({ THISP }) );

  return 0;
}
 
void change()  
{
  if( find_call_out( "change" ) == -1 )
    call_out("change", TIME);

  g = ( g == 1 ? 0 : 1 );

  tell_room( ENV( THISO ), "The traffic light changes.\n" );
}

string post_short()
{
  string ret;
  int i;

  if( THISP && THISP->query_ansi() )
  {
    if( g )
    {
      ret = sprintf( "%s[ %sRed: ", HIW, HIR );

      for( i = 0; i < sizeof( greens ); i++ )
      {
        ret = sprintf( "%s%s", ret, greens[i] );

        if( i < sizeof( greens ) - 1 ) 
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s%s - %sGreen: ", ret, HIW, HIG );

      for( i = 0; i < sizeof( reds ); i++ )
      {
        ret = sprintf( "%s%s", ret, reds[i] );

        if( i < sizeof( reds ) - 1 )
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf("%s %s] %s", ret, HIW, NOR NOR2 );
    }
    else
    {
      ret = sprintf( "%s[ %sRed: ", HIW, HIR );

      for( i = 0; i < sizeof( reds ); i++ )
      {
        ret = sprintf( "%s%s", ret, reds[i] );

        if( i < sizeof( reds ) - 1 )
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s%s - %sGreen: ", ret, HIW, HIG );

      for( i = 0; i < sizeof( greens ); i++ )
      {
        ret = sprintf( "%s%s", ret, greens[i] );

      if( i < sizeof( greens ) - 1 ) 
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s %s] %s", ret, HIW, NOR NOR2 );
    }
  }
  else
  {
    if( g )
    {
      ret = "[ Red: ";

      for( i = 0; i < sizeof( greens ); i++ )
      {
        ret = sprintf( "%s%s", ret, greens[i] );

        if( i < sizeof( greens ) - 1 ) 
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s - Green: ", ret );

      for( i = 0; i < sizeof( reds ); i++ )
      {
        ret = sprintf( "%s%s", ret, reds[i] );

        if( i < sizeof( reds ) - 1 )
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s ]", ret );
    }
    else
    {
      ret = "[ Red: ";

      for( i = 0; i < sizeof( reds ); i++ )
      {
        ret = sprintf( "%s%s", ret, reds[i] );

        if( i < sizeof( reds ) - 1 )
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s - Green: ", ret );

      for( i = 0; i < sizeof( greens ); i++ )
      {
        ret = sprintf( "%s%s", ret, greens[i] );

        if( i < sizeof( greens ) - 1 ) 
          ret = sprintf( "%s, ", ret );
      }

      ret = sprintf( "%s ]", ret );
    }
  }

  return sprintf( " %s", ret );
}
