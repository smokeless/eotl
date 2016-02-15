/*
dummy by sk0rch@eotl
dumber by Poi
*/
inherit MonsterCode;
inherit MonsterNoHunt;

#define HPS 20000
#define LOG "/usr/poi/log/dummy"

int hits, damage, delays, maxrounds, rounds, att_per_round, logging;
string header;
object *haters;

void print_report();
int stop_attack();

void extra_create()
{
  maxrounds = 0;
  logging = 0;
  haters = ({ });

  set_name( "azalin" );
  set_short( "Azalin the Spaz" );
  set_long(
    "This attack dummy sucks even more than Ahab.  How one person could "
    "possibly suck that bad is beyond explanation.  Kill it!\n\nYou can "
    "<limit #> to limit the number of rounds on Azalin, or <limit> with "
    "no or any args for unlimited rounds.\nYou can stop combat at any point "
    "by typing <stop>.\nSet the dummy's hitpoints with <hps #>\nSet the "
    "dummy's alignment with <align #> or <align evil|saintly|min|etc>.\n"
    "Set logging, and header to logged report with <log header>, or disable "
    "with <log off>."
    );
  add_alias( "dummy" );
  set_race( "retard" );
  set_toughness( 1 );
  set_stat( "chr", 600000 );

  set_max_hp( HPS );
  set_max_fatigue( 50000 );

  if( clonep() )
    call_out( "check_for_duplicates", 1 );
}

string post_short()
{
  string pshort;

  pshort = sprintf( " - [HP : %d/%d] [Max rounds : %s] [Alignment : %d]",
    THISO->query_hp(), THISO->query_max_hp(), maxrounds ? 
    to_string( maxrounds ) : "unlimited", THISO->query_alignment() );

  return pshort;
}

void combat_round_start()
{
  if( in_combat() )
    rounds++;

  ::combat_round_start();
}

void combat_round_end()
{
  ::combat_round_end();

  if( in_combat() )
  {
    tell_room( ENV( THISO ), sprintf( "Round %d - %d hits\n", rounds, hits ) );

    if( rounds >= maxrounds && maxrounds > 0 )
      stop_attack();
  }
}

int add_hp( int num )
{
  tell_room( ENV( THISO ), sprintf( "%s: %d\n", num <= 0 ? "Damage" : "Heal",
    num ) );

  if( num <= 0 )
    hits++;

  damage -= num;

  if( damage >= THISO->query_max_hp() )
  {
    tell_room( ENV( THISO ), "Dummy is statistically dead!\n" );
    stop_attack();

    return 0;
  }

  return ::add_hp( num );
}

int take_damage( int d, int l, string t, object a, object w, int al )
{
  int tmp;
  string loc_name;

  tmp = modify_damage( d, t, l );
  tmp = query_race_ob()->signal_damage( THISO, tmp, t, l, a, w );
  
  tell_room( ENV( THISO ), sprintf( "Damage: %d\n", tmp ) );

  hits++;
  damage += tmp;

  if( member( haters, a ) == -1 )
    haters += ({ a });

  if( damage >= THISO->query_max_hp() )
  {
    loc_name = ( l ? THISO->query_hit_info( "name", l ) : 0 );    
    call_other( SHARED_DIR + "gcm", "get_combat_message",
      THISO, d, loc_name, a, w, t );
    tell_room( ENV( THISO ), "Dummy is statistically dead!\n" );
    stop_attack();

    return 0;
  }

  return( ::take_damage( d, l, t, a, w, al ) );
}

varargs void do_damage( object targ,  int dam, int loc, string type,
                        object w, int always )
{
}

void set_hit_delay( int i )
{
  if( intp( i ) && i >= 0 && THISO->query_hit_delay() <= i )
    delays += i - THISO->query_hit_delay();

  ::set_hit_delay( i );
}

void add_hit_delay( int i )
{
  if( intp( i ) && i > 0 && THISO->query_hit_delay() <= 0 )
    delays += i;

  ::add_hit_delay( i );
}

void extra_init()
{
  add_action( "stop_attack", "stop" );
  add_action( "set_attack_limit", "limit" );
  add_action( "set_hps", "hps" );
  add_action( "adjust_alignment", "align" );
  add_action( "set_logging", "log" );
}

int set_logging( string str )
{
  if( !str )
    return 0;

  if( str == "off" )
  {
    if( logging == 0 )
    {
      tell_player( THISP, "Logging was already off." );
      return 1;
    }
    else
    {
      logging = 0;
      tell_player( THISP, "Logging disabled." );
      return 1;
    }
  }

  sscanf( str, "%s", header );

  if( strlen( header ) > 32 )
  {
    tell_player( THISP, "Header length limited to 32." );
    logging = 0;
    return 1;
  }
  else
  {
    if( !write_file( LOG, "" ) )
    {
      tell_player( THISP, sprintf( "No write access to %s.  Inherit this "
        "file and change the #define LOG to something you have access to.",
        LOG ) );
      logging = 0;
      return 1;
    }
    else
    {
      tell_player( THISP, sprintf( "Header set to: %s", header ) );
      logging = 1;
      return 1;
    }
  }
}

int stop_attack()
{
  int i;

  if( !THISO->in_combat() && hits <= 0 && damage <= 0 && delays <= 0 &&
      rounds <= 0 )
    return( tell_player( THISP, "Stop what, dumbass?" ), 1 );

  THISO->reset_combat();
  destruct_inventory();

  tell_room( ENV( THISO ), "Combat with Azalin stopped.\n" );
  print_report();

  for( i = 0; i < sizeof( haters ); i++ )
  {
    THISO->stop_hunting( haters[i] );
  }

  THISO->full_heal();
  hits = 0;
  damage = 0;
  delays = 0;
  rounds = 0;

  return 1;
}

int set_attack_limit( string str )
{
  if( !str || !(int)str )
  {
    tell_room( ENV( THISO), "Azalin set to unlimited attack rounds.\n" );
    maxrounds = 0;
    return 1;
  }

  sscanf( str, "%d", maxrounds );
  tell_room( ENV( THISO), sprintf( "Azalin set to allow only %d rounds.\n",
      maxrounds ) );

  return 1;
}

int set_hps( string str )
{
  if( !str || !(int)str )
  {
    tell_player( THISP, sprintf( "Hitpoints currently set to: %d\n<hps #> "
      "to change.", THISO->query_max_hp() ) );
    return 1;
  }
   
  set_max_hp( (int)str );
  THISO->full_heal();

  tell_room( ENV( THISO ), sprintf( "Azalin set to %s hitpoints.\n", str ) );

  return 1;
}

void print_report()
{
  int num_rounds, num_hits;
  float hist_round, dam_hit, dam_round;

  num_rounds = rounds == 0 ? 1 : rounds;
  num_hits   = hits == 0 ? 1 : hits;
  hist_round = to_float( hits ) / num_rounds;
  dam_hit    = to_float( damage ) / num_hits;
  dam_round  = to_float( damage ) / num_rounds;

  tell_room( ENV( THISO ), sprintf( 
    "\n**--------------------------------------**\n"
    "Total Damage: %d\n"
    "Total Hits: %d\n"
    "Total Rounds: %d\n"
    "Total Combat Delay: %d\n"
    "Average hits/round: %.3f\n"
    "Average damage/hit: %.3f\n"
    "Average damage/round: %.3f\n", 
    damage, num_hits, num_rounds, delays, hist_round, dam_hit, dam_round ) );

  if( logging )
  {
    logf( LOG, sprintf(
      "\n**---%|32'-'s---**\n"
      "Total Damage: %d\n"
      "Total Hits: %d\n"
      "Total Rounds: %d\n"
      "Total Combat Delay: %d\n"
      "Average hits/round: %.3f\n"
      "Average damage/hit: %.3f\n"
      "Average damage/round: %.3f\n"
      "**--------------------------------------**\n\n", 
      header, damage, num_hits, num_rounds, delays, hist_round, dam_hit,
      dam_round ) );
  }
}

void check_for_duplicates()
{
  object *clones;
  int i, found;

  clones = clones( file_name( THISO ) );
  found = 0;

  if( sizeof( clones ) > 1 )
  {
    for( i = 0; i < sizeof( clones ); i++ )
    {
      if( ENV( clones[i] ) == ENV( THISO ) )
      {
        found++;
      }
    }
  }

  if( found > 1 )
    destruct( THISO );
}

int adjust_alignment( string str )
{
  int i;
  string alignment;

  if( !str )
    return 0;

  if( sscanf( str, "%s", alignment ) != 1 )
    return 0;

  switch( lower_case( alignment ) )
  {
    case "max"       : THISO->set_alignment( MAX_ALIGN );    break;
    case "angelic"   : THISO->set_alignment( ANGELIC_AL );   break;
    case "saintly"   : THISO->set_alignment( SAINTLY_AL );   break;
    case "very good" : THISO->set_alignment( VERY_GOOD_AL ); break;
    case "good"      : THISO->set_alignment( GOOD_AL );      break;
    case "honorable" : THISO->set_alignment( HONORABLE_AL ); break;
    case "neutral"   : THISO->set_alignment( NEUTRAL_AL );   break;
    case "0"         : THISO->set_alignment( 0 );            break;
    case "malicious" : THISO->set_alignment( MALICIOUS_AL ); break;
    case "evil"      : THISO->set_alignment( EVIL_AL );      break;
    case "very evil" : THISO->set_alignment( VERY_EVIL_AL ); break;
    case "devilish"  : THISO->set_alignment( DEVILISH_AL );  break;
    case "demonic"   : THISO->set_alignment( DEMONIC_AL );   break;
    case "min"       : THISO->set_alignment( MIN_ALIGN );    break;

    default :
      if( sscanf( alignment, "%d", i ) == 1 )
      {
        if( i > 4000 )
        {
          THISO->set_alignment( 4000 );
          break;
        }
        else if( i < -4000 )
        {
          THISO->set_alignment( -4000 );
          break;
        }
        else
        {
          THISO->set_alignment( i );
          break;
        }
      }
      else
      {
        tell_player( THISP, "Illegal syntax.  Use <align saintly>, "
          "<align min>, <align -2400>, etc." );
        return 1;
      }
  }

  tell_player( THISP, sprintf( "Alignment set to: %d",
    THISO->query_alignment() ) );

  return 1;
}
