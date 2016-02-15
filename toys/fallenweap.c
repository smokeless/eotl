/* 
 * File:           fallen_sword.c
 * Date:           971117
 * Version:        2.0
 * Written by:     Maxim
 * Last change by: Socialism
 * History:
 *   941002: Additional functions for the anti-paladin's weapon.
 *           Must be included to the new weapon
 *   971117: This whole inherit shit sucks, Maxim was on crack.  Its been
 *           "Adjusted" so that there is only one 'executable' (sic) and 
 *           stores pdata in a similar manner to pdata.  Maxim and Jife sucked
 *           donkey nads, theres no function typin, etc.  This is annoyin.
 *   000420: Changed over to NewWeaponCode.
 *   130724: Modified and changed out to a shadow placed on a weapon.
 *           Accessible to anti-pals who seek out a powerful fallen.
 *           Other anti-pals can suck it. Or it can be later used as
 *           standard for guild.
 */
/*
#include <fallen_sword.h>
#define QUERIES ({ "query_base_speed", "query_base_damage", "query_speed_step",\
                   "query_damage_step", "query_prof_mod", "query_fatigue_cost",\
                   "query_damage_type", "query_handed", "query_proficiency",\
                   "query_short", "query_long", "query_material", "query_ids",\
                   "query_prof_speed_mod", "query_prof_damage_mod" })

#define SETS ({ "set_base_speed", "set_base_damage", "set_speed_step",\
                "set_damage_step", "set_prof_mod", "set_fatigue_cost",\
                "set_damage_type", "set_handed", "set_proficiency",\
                "set_short", "set_long", "set_material", "set_ids",\
                "set_prof_speed_mod", "set_prof_damage_mod" })

*/


void setup_dmg_type();

/*
 *-----------------------------------------------------------------------------
 * Variable Declarations
 *-----------------------------------------------------------------------------
 */
 
string hold_post_short, type;
int points, drain_delayed, broken;
string owner;
mixed *bog;
object me;
 
/*
 *-----------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------------
 */
 
/*
 *-----------------------------------------------------------------------------
 * Function BS
 *-----------------------------------------------------------------------------
 */
/*

static void 
setup()
{ 
  add_id( "unholy weapon" );
  set( NoSellP, 1 );
  set( NoBreakP, 1 );
  set( NoStoreP, 1 );
  set( AutoLoadP, 1 );
  set( NoEnchantP, 1 );
  set( NoEnhanceP, 1 );
  set( NoTemperP, 1 );
  set( NoBlessP, 1 );
  set( MagicP, 3 );
  add_material( "steel" );
  set_material_name( "unholy steel" );
  set_droppable( 1 );
  set_gettable( 1 );
}
 
void
create()
{            
  seteuid( getuid() );
  if( !clonep() )
    return;
  ::create();
  bog = ({ });
}
/* 
 * Anti-paladin weapon check (ie, this has been blessed and all).       
 */

void sh_init( object arg )
{
    me = arg;
    shadow( me, 1 );
    bog = ({ });
    //all temp
    string owner = "socialism";
}

int query_ap_weapon()
{
    return( 1 );
}
 
/*
 *  Return the owner of the weapon.
 */
string query_owner()
{
    return( owner );
}
 
/* Return the number of points the sword currently holds. */
int query_points()
{
    return( points );
}
/* 
 * Return the maximum number of points the sword can hold, which is
 * the lesser of 120 and the owner's wil.
 */
 
int query_max_points()
{
    object o;
    int w;
 
    if( !o = find_player( owner ) ) 
    {
      return 0;
    }
    w = o->query_stat( "wil" );
    return( w >= 120 ? 120 : w );
}
 
/* 
 * Check for soul drain skill.
 */
 
int query_drain_delay()
{
}
 
/* 
 * Set delay for soul drain skill.
 */
/*
void drain_delay( int leg )
{
    if( !intp( leg ) )
    {
      return;
    }
    drain_delayed = leg;
    call_out( "drain_delay", leg, 0 );
}
*/
 
void make_new_post_short()
{
    string output, tmp;
    int hands;
 
    switch( points )
    {
      case  0 .. 10:
        output = " with glowing crimson lines along the blade";
      break;
 
    case 11 .. 30:
      output = " with a crimson aura";
    break;
 
    case 31 .. 70:
      output = " radiating an aura of evil";
    break;
 
    case 71 .. 120:
      output = " bursting with evil power";
    break;
 
    default:
    output = " of a smoke grey color"; 
    break;
    }
 
    if( tmp = THISO->query_enhanced() )
    {
      output += " ("+tmp+")";
    }
    hold_post_short = output;
}
 
string post_short( object ob )
{
    string str;
    str = stringp( ::post_short( ob ) ) ? ::post_short( ob ) : "";
    return( stringp( hold_post_short ) ? hold_post_short + str : str );
}

string post_long( object ob )
{
    string out;
 
    if( !stringp( owner ) )
      out = "";
    else if( THISP && THISP->query_guild() == "dustman" )
      out = "\nEngraved on the hilt is the name '" + CAP( owner ) + "'.\n";
 
    else
      out = "";
 
    out += ::post_long();
    return( out );
}
 
//Borrowed from Krynns fuck_breaking_weapons.h; I fail to understand why
//magically blessed (cursed?) weapons would dull/break. 
//Guido.
 
int stop_break()
{
  return( 1 );
}
 
void check_break()
{
}
 
/*
 * Add a specified number of points to the sword.  If the max number of
 * points is exceeded, drop the excess.  Use only to increase the number
 * of points in the sword, not decrease.  Use use_points for decreasing.
 */
void setup_dmg_type()
{
  if( !type )
    type = query_damage_type();
//  if( points > 90 )    
//    set_damage_type( "unholy" );
}

void add_points( int num )
{
    int magic, max;
    string pname;
    object own;
    if( !num ) return;
    if( num < 0 ) return;
    pname = load_name( caller() );
    if( num + points >= ( max = query_max_points() ) )
      points = max;
    else
    points += num;
 
    make_new_post_short();
    setup_dmg_type();
}

 
/*
 * Use up a specified number of points from the sword.  Will zero out
 * if you try to use more than the number of points stored, so make
 * sure you carry out any checks for how many points are to be used
 * before calling this function.
 */
 
void use_points( int num )
{
  int magic;
 
  if ( !num ) return;
  if( num < 0 )
    return;
  points -= num;
  if( points < 0 )
    points = 0;
  make_new_post_short();
  setup_dmg_type();
}
 
/*
 * If someone other than the owner wields the sword, all the power points
 * in the sword should drain into the wielder, causing damage.  The sword
 * can still be wielded, however.
 */
 
void post_wield( object who )
{
    if( query_points() < 1 ) 
      return;
 
    if( who->query_real_name() != owner )
   {
     write( strformat( "The weapon does not recognize " +
       "you as its owner, and unleashes its " +
       "stored power upon you!" ) );
     say( strformat( "As " + capitalize( who->query_name() ) +
       " tries to wield the weapon, " +
       subjective( who ) + " is racked with pain " +
       "as its stored power is unleased " +
       "upon " + objective( who ) + "!" ) );
      who->take_damage( query_points(), 0, "unholy", THISO );
      points = 0;
    }
}
 
status try_unwield( object wielder )
{
    if( wielder->query_soul_shadow() )
    {
      tell_object( wielder, "You can't unwield while soul draining.\n" );
      return( 1 );
    }
    return( 0 );
}
  
/* 
int setup_new_sword( object dumbass, object sword )
{
  int x;
  if( !objectp( dumbass ) || !objectp( sword ) ) 
  {
    Exit( "objects passed to setup_new_sword() invalid" );
    return( 0 );
  }
  for(x=0;x<sizeof(QUERIES);x++)
  {
     bog += ({ call_other( sword, QUERIES[x] ) });
     call_other( THISO, SETS[x], bog[x] );
  }
  if( THISO->query_short()[<8..] == "(marked)" )
    THISO->set_short( THISO->query_short()[0..<10] );
  owner = getuid( dumbass );
  make_new_post_short();
  save_vars();
  return( 1 );
}
*/
