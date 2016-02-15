// File: /obj/races/death/corpse
// Desc: corpse of players and monsters
// Revamped by Gunthar to remove heart_beat()
// 940509 Purge Added a query_victim_guild() function.
// 940629 Zippo recoded basics, introduced CORPSEMASTER!
// 950302 Deathdealer revamped and streamlined
// 040630 Anthrax changed first_decay from nomask void to status; added altered
//          decay times for corpses in hot/cold environments
//          Also added support for corpses of varying weights.
// 040729 Anthrax added check for VacuumP ENV to avoid decay
// 040821 Anthrax disabled putting things in a corpse if it has an ENV
//          (instead of using corpse weight as a limit)
// 041211 Anthrax changed default corpse weight to be more realistic ( 180 lb.)

inherit NewThingCode;

#define START_WEIGHT 900               // non-decayed corpse weight
#define DECAY_FACTOR 0.80               // weight multiplier for decayed corpse
#define CHILL_DELAY 3    // # of decay cycles before corpse decays in cold

/*===[ Queries ]==========================================================*/

status query_corpse() { return( 1 ); }
status can_put_and_get() { return 1; }
status query_enter_ok( object item, object mover ) {
    return objectp(ENV(THISO));
}

mixed query( string var )
{
    if( var == CorpseP )
      return 1;
    if( var == "weight" )
        return( total_array( all_inventory(), "query", "weight" ) +
         ::query( "c_weight" ) );
    else
        return( ::query( var ) );
}

status set( string var, mixed val ) {
    if(!stringp(var)) return 0;
    switch(var) {
        case "decay_cycles":
            if(!intp(val)) return 0;
            break;
        default: break;
    }
    return ( :: set( var, val ) );
}

status add( string var, string val ) {
    if(!stringp(var)) return 0;
    if( var == "decay_cycles" )
        if( !intp(val) ) return 0;
    return ::add( var, val );
}

query_weight() { return query("weight"); }

/*===[ Guts ]=============================================================*/

/* Name: setupCorpse( string, string, int, string )
 * Func: called after creation to set player/monster specific descs
 */
nomask void
setupCorpse( string victim, string cause )
{
    string long_msg;

    CORPSEMASTER->register_corpse();
    if( victim )
    {
        add( "id", "corpse of " + lower_case( victim ) );
        add( "id", lower_case( victim ) + "'s corpse" );
        set( "victim_name", lower_case( victim ) );
        set( "short", "the corpse of " + capitalize( victim ) );
        long_msg = sprintf( "This is the body of %s.\n%s",
         capitalize( victim ),
         ( cause ? sprintf( "Death seems to have occured %s.\n", cause ) :
          "" ) );
        set( "long", long_msg );
    }
}

/* Name: final_decay()
 * Func: called by CORPSEMASTER to induce destruction of the corpse (decay)
 */
nomask void final_decay()
{
    string vic;
    object obj;

    obj = ENV( THISO );

    if( obj )
        if( obj->query(VacuumP) ) return;

    if( obj )
        tell_room( obj, sprintf(
          "A writhing mass of maggots consumes the corpse%s.\n",
          ( ( vic = query( "victim_name" ) ) ?
           " of " + capitalize( vic ) : "" ) ) );
    destruct( THISO );
}

/* Name: first_decay()
 * Func: called by the CORPSEMASTER to induce the first decay stage
 */
status first_decay()
{
    string capname;
    object where;
    int i;

// This section deals with corpses in hot/cold environments - Anthrax
//    Also, vacuum environments - no air, no decay! - Anthrax
    where = ENV(THISO);
    if( objectp(where) ) {
        if( where->query(VacuumP) ) return 1;
        i = query("decay_cycles");
        if( where->query(HotP) ) {
            if( i >= 0 ) {  // i < 0 means 'preservative' applied
                call_out("final_decay", 2);
                return 1;
            }
            i+=2;
            set("decay_cycles", i);
            return 1;
        } else
        if( i < 0 || ( i < CHILL_DELAY && where->query(ColdP) ) ) {
            i++;
            set("decay_cycles", i);
            return 1;
        }
    }

    capname = query( "victim_name" );
    if ( capname )
        capname = capitalize( capname );
    set( "short", sprintf( "the decayed remains of %s",
      ( capname ? capname : "something" ) ) );
    set( "long", capname ?
      sprintf( "This corpse is so rotted that you can barely tell that " +
        "the body originally belonged to %s.", capname ) :
      "This is a partially decayed corpse." );
    i = to_int( to_float(query("c_weight")) * DECAY_FACTOR );
    if( i == query("c_weight") ) i--;
    set("c_weight", i);
    set( "decayed", 1 );
    return 0;
}

/* Name: extra_create()
 * Func: called upon creation
 */
void extra_create()
{
    if( !clonep(THISO) )
        return;
    set( "id", ({ "corpse", "remains" }) );
    set( "short", "a fresh corpse" );
    set( "long", "This is a fresh corpse.\n" );
    set( "c_weight", START_WEIGHT );
    set( "decayed", 0 );
    set( "decay_cycles", 0 );
    set( NoStoreP, 1 );
}

/*===[ EOF ]==============================================================*/
