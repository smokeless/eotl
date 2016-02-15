inherit WeaponCode;

#include <ansi.h>

#define DMG   ({ "asphyxiation", "blunt", "cold", "corrosive", "disease", \
                 "drain", "edged", "electric", "energy", "fire", "holy", \
                 "magic", "magic_cold", "magic_elec","magic_fire", \
                 "piercing", "poison", "psionic", "psychic", "sonic", \
                 "unholy" })
#define PROFS ({ "hands", "heavy axe", "heavy club", "heavy flail", \
                 "heavy polearm", "heavy sword", "javelin", "knife", \
                 "light axe", "light club", "light flail", "light polearm", \
                 "light sword", "staff" })
#define HANDS ({ "1", "2", "3", "4" })

void show_help( object player );
void list_weapon_values( object player );
void reset_to_default( object player );
void mirror_players_weapon( string arg );
void mirror_file( string arg );
void set_it_up( object weapon );

void extra_create()
{
  add_ids( ({ "test", "test weapon" }) );
  set_short( "Poi's Weapon of Mighty Testing" );
  set_ansi_short( HIK "Poi's Weapon of Mighty Testing" );
  set_long(
    "Poi's test weapon.  It's pretty."
  );
  set_proficiency( "heavy sword" );
  set_damage_type( "edged" );
  set_material( "steel" );
  set_handed( 1 );
  set_value( 5000 );
  set_weight( 500 );

  set_base_damage( 32 );
  set_damage_step( 5 );
  set_prof_damage_mod( 7.5 );

  set_base_speed( 40 );
  set_speed_step( 6 );
  set_prof_speed_mod( 6.5 );

  set( NoSellP, 1 );
  set( NoStealP, 1 );
  set( NoStoreP, 1 );
}

void extra_init()
{
  add_action( "adjust_weapon", "wset" );
}

int adjust_weapon( string str )
{
  string var, arg;
  int i;
  float f;

  if( ENV( THISO ) != THISP )
    return 0;

  if( !IsWizard( THISP ) && THISP->query_real_name() != "zzpoi" )
    return 0;

  if( !str )
  {
    show_help( THISP );
    return 1;
  }

  if( str == "list" )
  {
    list_weapon_values( THISP );
    return 1;
  }

  if( str == "default" )
  {
    reset_to_default( THISP );
    return 1;
  }

  if( sscanf( str, "%s %s", var, arg ) != 2 )
  {
    show_help( THISP );
    return 1;
  }

  switch( var )
  {
    case "prof"        :
    case "proficiency" :
  	  if( member( PROFS, arg ) == -1 )
  	  {
  	    tell_player( THISP, sprintf( "Invalid arg.  Supported proficiencies "
  	      "are: %s", implode( PROFS, ", " ) ) );
  	  }
  	  else
  	  {
  	    THISO->set_proficiency( arg );
        tell_player( THISP, sprintf( "Proficiency set to: %s", arg ) );
      }
      break;
    case "hands"  :
    case "handed" :
      if( member( HANDS, arg ) == -1 )
      {
        tell_player( THISP, sprintf( "Invalid arg.  Supported handedness "
          "are: %s", implode( HANDS, ", " ) ) );
      }
      else
      {
        THISO->set_handed( to_int( arg ) );
        tell_player( THISP, sprintf( "Weapon is now %s handed", arg ) );
      }
      break;
    case "damage_type" :
    case "damtype"     :
      if( member( DMG, arg ) == -1 )
      {
        tell_player( THISP, sprintf( "Invalid damage type.  Support types "
          "are: %s", implode( DMG, ", " ) ) );
      }
      else
      {
        THISO->set_damage_type( arg );
        tell_player( THISP, sprintf( "Damage type set to: %s", arg ) );
      }
      break;
    case "weight" :
      if( !sscanf( arg, "%d", i ) > 0 )
      {
        tell_player( THISP, "Requires proper int.  Note: 50 == 1 pound." );
      }
      else
      {
        THISO->set_weight( i );
        tell_player( THISP, sprintf( "Weight set to: %s", to_string( i ) ) );
      }
      break;
    case "base_damage" :
    case "basedmg"     :
      if( !sscanf( arg, "%d", i ) > 0 )
      {
        tell_player( THISP, "Requires a proper int." );
      }
      else
      {
        THISO->set_base_damage( i );
        tell_player( THISP, sprintf( "Base damage set to: %s",
          to_string( i ) ) );
      }
      break;
    case "damage_step" :
    case "dmgstep"     :
      if( !sscanf( arg, "%d", f ) > 0 )
      {
        tell_player( THISP, "Requires a proper int or float." );
      }
      else
      {
        THISO->set_damage_step( f );
        tell_player( THISP, sprintf( "Damage step set to: %s", arg ) );
      }
      break;
    case "prof_damage_mod" :
    case "profdmg"      :
      if( !sscanf( arg, "%d", f ) > 0 )
      {
        tell_player( THISP, "Requires a proper int or float." );
      }
      else
      {
        THISO->set_prof_damage_mod( f );
        tell_player( THISP, sprintf( "Prof damage mod set to: %s", arg ) );
      }
      break;
    case "base_speed" :
    case "basespeed" :
      if( !sscanf( arg, "%d", i ) > 0 )
      {
        tell_player( THISP, "Requires a proper int." );
      }
      else
      {
        THISO->set_base_speed( i );
        tell_player( THISP, sprintf( "Base speed set to: %s",
          to_string( i ) ) );
      }
      break;
    case "speed_step" :
    case "speedstep"  :
      if( !sscanf( arg, "%d", f ) > 0 )
      {
        tell_player( THISP, "Requires a proper int or float." );
      }
      else
      {
        THISO->set_speed_step( f );
        tell_player( THISP, sprintf( "Speed step set to: %s", arg ) );
      }
      break;
    case "prof_speed_mod" :
    case "profspeed"   :
      if( !sscanf( arg, "%d", f ) > 0 )
      {
        tell_player( THISP, "Requires a proper int or float." );
      }
      else
      {
        THISO->set_prof_speed_mod( f );
        tell_player( THISP, sprintf( "Prof damage mod set to: %s", arg ) );
      }
      break;
    case "player" :
      mirror_players_weapon( arg );
      break;
    case "file" :
      mirror_file( arg );
      break;
    default:
      tell_player( THISP, "Invalid variable.  <wset list> to see list of "
        "acceptable vars that can be changed." );
      break;
  }

  return 1;
}

void list_weapon_values( object player )
{
  string s;

  s = sprintf(
    "Proficiency (proficiency/prof)............... %s\n"
    "Handedness (hands/handed).................... %s\n"
    "Damage type (damage_type/damtype)............ %s\n"
    "Weight (weight).............................. %s\n"
    "Base damage (base_damage/basedmg)............ %s\n"
    "Damage step (damage_step/dmgstep)............ %s\n"
    "Prof damage mod (prof_damage_mod/profdmg).... %s\n"
    "Base speed (base_speed/basespeed)............ %s\n"
    "Speed step (speed_step/speedstep)............ %s\n"
    "Prof speed mod (prof_speed_mod/profspeed).... %s\n\n"
    "<wset var arg> to change a variable.\n"
    "<wset default> to revert weapon to default.\n"
    "<wset player player> to mirror player's wielded weapon.\n"
    "<wset file file> to mirror stats of specified file.\n\n"
    "ex: wset prof light sword\n"
    "ex: wset dmgstep 5.2\n"
    "ex: wset player poi\n"
    "ex: wset file /obj/weapon/weapons/blunt/chain.c\n",
    THISO->query_proficiency(),
    to_string( THISO->query_handed() ),
    THISO->query_damage_type(),
    to_string( THISO->query_weight() ),
    to_string( THISO->query_base_damage() ),
    to_string( THISO->query_damage_step() ),
    to_string( THISO->query_prof_damage_mod() ),
    to_string( THISO->query_base_speed() ),
    to_string( THISO->query_speed_step() ),
    to_string( THISO->query_prof_speed_mod() ) );

  tell_player( player, s );
}

void show_help( object player )
{
  tell_player( player, "<wset list> to see which variables can be changed.\n"
    "<wset player player> to set variables the same as player's wielded "
    "weapon.\n<wset file file> to set variables the same as specified "
    "file." );
}

void reset_to_default( object player )
{
  THISO->set_proficiency( "heavy sword" );
  THISO->set_damage_type( "edged" );
  THISO->set_material( "steel" );
  THISO->set_handed( 1 );
  THISO->set_value( 5000 );
  THISO->set_weight( 500 );
  THISO->set_base_damage( 32 );
  THISO->set_damage_step( 5 );
  THISO->set_prof_damage_mod( 7.5 );
  THISO->set_base_speed( 40 );
  THISO->set_speed_step( 6 );
  THISO->set_prof_speed_mod( 6.5 );

  tell_player( player, "Weapon has been reset." );
}

void mirror_players_weapon( string arg )
{
  object player, weapon;

  if( player = FINDP( arg ) )
  {
    if( weapon = player->query_weapon() )
    {
      if( member( PROFS, weapon->query_proficiency() ) != -1 )
      {
        set_it_up( weapon );
      }
      else
      {
        tell_player( THISP, sprintf( "%s's weapon is a %s, which is not "
          "supported.  Supported weapon types are: %s",
          CAP( player->query_real_name() ), weapon->query_proficiency(),
          implode( PROFS, ", " ) ) );
      }
    }
    else
    {
      tell_player( THISP, sprintf( "%s isn't wielding a weapon.",
        CAP( player->query_real_name() ) ) );
    }
  }
  else
  {
    tell_player( THISP, sprintf( "%s doesn't exist or isn't online.",
      CAP( arg ) ) );
  }
}

void mirror_file( string arg )
{
  object weapon;
  string error;

  if( exists( arg ) )
  {
    if( sizeof( find_objects( arg[1..] ) ) < 1 )
    {
      if( !error = catch( weapon = load_object( arg[..<3] ) ) )
      {
        if( weapon->query_weapon() )
        {
          if( member( PROFS, weapon->query_proficiency() ) != -1 )
          {
            set_it_up( weapon );
          }
          else
          {
            tell_player( THISP, sprintf( "Specified weapon is a %s, which is "
              "not supported.  Supported weapon types are: %s",
              weapon->query_proficiency(), implode( PROFS, ", " ) ) );
          }
        }
        else
        {
          tell_player( THISP, "Specified file is not a weapon." );
        }
      }
      else
      {
        tell_player( THISP, sprintf( "Specified file would not load.  Error "
          "message: %s", error ) );
      }
    }
    else
    {
      weapon = FINDO( arg );
      if( weapon->query_weapon() )
      {
        if( member( PROFS, weapon->query_proficiency() ) != -1 )
        {
          set_it_up( weapon );
        }
        else
        {
          tell_player( THISP, sprintf( "Specified weapon is a %s, which is "
            "not supported.  Supported weapon types are: %s",
            weapon->query_proficiency(), implode( PROFS, ", " ) ) );
        }
      }
      else
      {
        tell_player( THISP, "Specified file is not a weapon." );
      }
    }
  }
  else
  {
    tell_player( THISP, "Specified file does not exist or incorrect "
      "syntax.  <wset list> to see example." );
  }
}

void set_it_up( object weapon )
{
  THISO->set_proficiency( weapon->query_proficiency() );
  THISO->set_handed( weapon->query_handed() );
  THISO->set_damage_type( weapon->query_damage_type() );
  THISO->set_weight( weapon->query_weight() );
  THISO->set_base_damage( weapon->query_base_damage() );
  THISO->set_damage_step( weapon->query_damage_step() );
  THISO->set_prof_damage_mod( weapon->query_prof_damage_mod() ?
    weapon->query_prof_damage_mod() : weapon->query_prof_mod() );
  THISO->set_base_speed( weapon->query_base_speed() );
  THISO->set_speed_step( weapon->query_speed_step() );
  THISO->set_prof_speed_mod( weapon->query_prof_speed_mod() ?
    weapon->query_prof_speed_mod() : weapon->query_prof_mod() );

  tell_player( THISP, "Done." );
}  

string post_long( object me )
{
  string plong;

  if( IsWizard( THISP ) )
    plong = "\n<wset> to see commands.\n";

  if( stringp( plong ) )
    return plong + ::post_long( me );

  return ::post_long( me );
}

varargs int query_max_damage( object player )
{
  object victim;

  if( !player )
    return ::query_max_damage();
    	
  if( !victim = player->choose_target() )
    return ::query_max_damage( player );

  if( victim && is_player( victim ) && GetLevel( victim ) == "mortal" )
  {
    player->reset_combat();
    return 0;
  }

  return ::query_max_damage( player );
}

int try_wield( object player )
{
  if( !IsWizard( player ) && player->query_real_name() != "zzpoi" )
  {
    tell_player( player, "Not a chance, shithead." );
    call_out( "destroy_me", 1 );
    return 1;
  }

  return 0;
}

void destroy_me()
{
  destruct( THISO );
}
