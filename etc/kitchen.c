/*---------------------------------------------------------
     Make sure the oven and kitchen are both loaded.
              Written by Speed - 07.26.04
---------------------------------------------------------*/
#include <ansi.h>
#include <lumberjack.h>
#include <kitchen.h>

inherit RoomPlusCode;

int closed;   //Closed is 1, opened is 0, locked is 2
int on;       //On is 1, off is 0 (for oven)
int faucet;   //On is 1, off is 0 (for sink)
int count;    //Counts the heartbeats
int cup;      //No cup 0, cup there is 1
object oven;  //The oven in the kitchen

int  kill_corpse();
int  door_status();
void change_status();

void extra_create()
{
   //make sure everything is in place beforehand
   count  = 0;
   on     = 0;
   faucet = 0;
   closed = 1;
   cup    = 1;

   oven = load_object( OVEN );
// load_object( oven );
   set_heart_beat( 0 );

   set( "short", "Kitchen" );
   set( "ansi_short" , BRN "Kitchen" NORM );
   set( "day_long" ,
     "It appears this kitchen has never been used.  The "
     "linoleum floor is a bright white, matching the "
     "countertops and the refrigerator on the right side of "
     "the room.  An immense oven rests under the countertop "
     "on the left side of the kitchen."
   );
   set( "day_light" , WELL_LIT );
   set( InsideP, 1 );
   set( "exits" ,
     ([
       "east" : ROOMS "living" ,
       "oven" : "@oven",
     ])
   );
   set( "descs" ,
     ([
       "floor" : "The linoleum flooring is unstained and "
         "totally clean.  Cleaner linoleum would be hard "
         "to find.",
       "counter" : "Spotless.  Nothing on these counters.",
       "refrigerator" : "The refrigerator is completely "
         "empty.  There is nothing on any of the shelves, "
         "in the door, the freezer... nothing!",
       "ceiling" : "You stare at the ceiling.  How exciting.",
       "knob" : "This black knob is used to start the oven.",

       "linoleum floor" : "*floor",
       "countertops" : "*counter",
       "fridge" : "*refrigerator",

       "window"    : "@window_desc",
       "sink"      : "@sink_desc",
       "faucet"    : "@faucet_desc",
       "cupboard"  : "@cupboard_desc",
       "cupboards" : "@cupboard_desc",
       "oven"      : "@oven_desc",
     ])
   );
}

void extra_init()
{
   add_action( "open_door",     "open" );
   add_action( "close_door",    "close" );
   add_action( "lock_door",     "lock" );
   add_action( "unlock_door",   "unlock" );
   add_action( "oven_cook",     "start" );
   add_action( "stop_oven",     "stop" );
   add_action( "get_cup",       "grab" );
   add_action( "faucet_switch", "turn" );
   if(!oven) { oven; }
}

void heart_beat()
{
   count++;

   if( count == 6 )
     call_out( "hot_one", 0 );
   if( count == 12 )
     call_out( "hot_two", 0 );
   if( count == 18 )
     call_out( "hot_three", 0 );
   if( count > 18 && count % 6 == 0)
     call_out( "hot_dead", 0 );

   //dont kill the mud, stops after 5 mins
   if( count == 150 )
   {
     tell_room( KITCHEN, format( "The EnergySaver[tm] "
       "feature kicks in, and the oven automatically "
       "shuts itself down." ) );
     tell_room( oven, format( "The oven shuts off." ) );
     set_heart_beat( 0 );
     count = 6;   //Cools down a lot, has some heat
     on = 0;
   }
}

reset()
{
   ::reset();
   cup = 1;     //Respawns the cup at reset
}

/*---------------------------------------------------------
  Set descriptions for various things within the kitchen
---------------------------------------------------------*/
window_desc()
{
   return( COMMAND_DIR "look"->look_at_env(
     FINDO( eval_arg( oven, 0 ) ) ), 1 );
}

sink_desc()
{
   string fauceton, faucetoff;

   faucetoff = SINKDESC + SINK0;
   fauceton  = SINKDESC + SINK1;

   if( !faucet )
     return( sprintf( "%=-70s", faucetoff ) );

   else
     return( sprintf( "%=-70s", fauceton ) );
}

faucet_desc()
{
   if( !faucet == 0 )
     return SINK0;

   else
     return SINK1;
}

cupboard_desc()
{
   string empty, full;

   empty = CUPBOARDDESC + CUPBOARD0;
   full  = CUPBOARDDESC + CUPBOARD1;

   if( !cup )
     return( sprintf( "%=-70s", empty ) );

   else
     return( sprintf( "%=-70s", full ) );
}

oven_desc()
{
   string oven_close, oven_open, oven_lock;

   oven_close = OVENDESC + OVEN0;
   oven_open  = OVENDESC + OVEN1;
   oven_lock  = OVENDESC + OVEN2;

   if( closed == 1 )
     return( sprintf( "%=-70s", oven_close ) );

   else if( !closed )
     return( sprintf( "%=-70s", oven_open ) );

   else
     return( sprintf( "%=-70s", oven_lock ) );
}
/*---------------------------------------------------------
                  Oven door related things
---------------------------------------------------------*/
oven()   //Allows or disallows players to enter the oven
{
   if( closed )
     return( tell_player( THISP, "You cannot climb "
       "into the oven when the door is closed!" ), 1 );

   if( sizeof( filter_array(
         all_inventory( oven ), #'living ) ) )
       return( tell_player( THISP, "There is already someone "
         "inside the oven.\nTwo people will not fit!" ), 1 );

   return OVEN;
}

int open_door( string arg )   //Opens the oven door
{
   string *valid_args = ({ "door", "oven", "oven door" });

   if( member( valid_args, arg ) ==-1 )
     return notify_fail( format( "Open what?" ) );

   if( closed == 2 )
     return( tell_player( THISP, "The oven is locked "
       "tight." ), 1 );

   if( !closed )
     return( tell_player( THISP, "The oven door is already "
       "open." ), 1 );

   tell_player( THISP, "You open the oven door." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
     " opens the oven door." ) , ({ THISP }) );
   tell_room( oven, format( "The oven door opens." ) );

   closed = 0;
   return 1;
}

int close_door( string arg )   //Closes the oven door
{
   string *valid_args = ({ "door", "oven", "oven door" });

   if( member( valid_args, arg ) ==-1 )
     return notify_fail( format( "Close what?" ) );

   if( closed )
     return( tell_player( THISP, "The oven door is already "
       "closed." ), 1 );

   tell_player( THISP, "You close the oven door." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
      " closes the oven door." ) , ({ THISP }) );
   tell_room( oven, format( "The oven door closes." ) );

   closed = 1;
   return 1;
}

int lock_door( string arg )   //Locks the oven door
{
   string *valid_args = ({ "door","oven","oven door" });

   if( member( valid_args, arg ) == -1 )
     return notify_fail( format( "Lock what?" ) );

   if( !closed )
     return( tell_player( THISP, "You cannot lock the "
       "door while it is open." ), 1 );

   if( closed == 2 )
     return( tell_player( THISP, "The oven door is "
       "already locked." ), 1 );

   tell_player( THISP, "You lock the oven door." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
     " locks the oven door." ) , ({ THISP }) );
   tell_room( oven, format( "You hear a CLUNK as the oven "
     "door is locked from the outside!" ) );

   closed = 2;
   return 1;
}

int unlock_door( string arg )   //Unlocks the oven door
{
   string *valid_args = ({ "door", "oven", "oven door" });

   if( member( valid_args, arg ) ==-1 )
     return notify_fail( format( "You can't unlock that." ) );

   if( closed < 2 )
     return( tell_player( THISP,
       "The oven door is not locked." ), 1 );

   tell_player( THISP, "You unlock the oven door." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
     " unlocks the oven door." ) , ({ THISP }) );
   tell_room( oven, format( "You hear a CLUNK as the oven "
     "door is unlocked." ) );

   closed = 1;
   return 1;
}
/*---------------------------------------------------------
                 Oven power related things
---------------------------------------------------------*/
int oven_cook( string arg )   //Starts the oven
{
   if( arg != "oven" )
     return notify_fail( format( "Start what?" ) );

   if( on )
     return( tell_player( THISP, "The oven is already "
       "turned on." ), 1 );

   tell_player( THISP, "You turn the knob and "
     "start the oven." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
     " turns on the oven." ), ({ THISP }) );
   tell_room( oven, format( "Oh no!  Someone has "
     "turned the oven on!!!" ) );

   //Starts heartbeat when the oven turns on
   set_heart_beat( 1 );

   on = 1;
   return 1;
}

int stop_oven( string arg )   //Player stops the oven
{
   if( arg != "oven" )
     return notify_fail( format( "Stop what?" ) );

   if( !on )
     return( tell_player( THISP,
       "The oven is already off." ), 1 );

   tell_player( THISP, "You turn the oven off." );
   tell_room( ENV( THISP ), format( THISP->query_name() +
     " shuts the oven off." ), ({THISP}) );
   tell_room( oven, format( "The oven shuts off." ) );

   //Stop the heartbeat when the oven shuts off
   set_heart_beat( 0 );

   on = 0;
   count = 6;   //Cools down a lot, has some heat
   return 1;
}

int hot_one()   //Message 1, oven gets warm
{
   if( !closed )
   {
     tell_room( oven, format( "It is kinda hot in here.  "
       "Good thing the door is open, letting all the hot "
       "air escape, or you might be cooked alive!" ) );
     tell_room( KITCHEN, format( "The EnergySaver[tm] "
       "feature detects the door being open, and "
       "automatically shuts the oven down." ) );

     set_heart_beat( 0 );
     count = 0;
     on = 0;
     return 1;
   }

   tell_room( oven, format( "It is beginning to "
       "get hot in here..." ) );

   return 1;
}

int hot_two()   //Message 2, oven gets hot
{
   if( !closed )
   {
     tell_room( oven, format( "It is kinda hot in here.  "
       "Good thing the door is open, letting all the hot "
       "air escape, or you might be cooked alive!" ) );
     tell_room( KITCHEN, format( "The EnergySaver[tm] "
       "feature detects the door being open, and "
       "automatically shuts the oven down." ) );

     set_heart_beat( 0 );
     count = 0;
     on = 0;
     return 1;
   }

   tell_room( oven, format( "It is fairly hot in here..." ) );
     call_out( "hot_three", 15 );

   return 1;
}
int hot_three()   //Message 3, oven gets very hot
{
   if( !closed )
   {
     tell_room( oven, format( "It is kinda hot in here.  "
       "Good thing the door is open, letting all the hot "
       "air escape, or you might be cooked alive!" ) );
     tell_room( KITCHEN, format( "The EnergySaver[tm] "
       "feature detects the door being open, and "
       "automatically shuts the oven down." ) );

     set_heart_beat( 0 );
     count = 0;
     on = 0;
     return 1;
   }

   tell_room( oven, format( "Damn, it is reeeeally "
     "hot in here!" ) );

   return 1;
}

int hot_dead()   //Message 4, you're dead!
{
   object *ob;
   int a, k, b;

   a = 0;
   k = 0;
   b = 0;
   ob = all_inventory( oven );

   if( !closed )
   {
     tell_room( oven, format( "It is kinda hot in here.  "
       "Good thing the door is open, letting all the hot "
       "air escape, or you might be cooked alive!" ) );
     tell_room( KITCHEN, format( "The EnergySaver[tm] "
       "feature detects the door being open, and "
       "automatically shuts the oven down." ) );

     set_heart_beat( 0 );
     count = 0;
     on = 0;
     return 1;
   }

   for( k = 0; k < sizeof( ob ); k++ )
   {
     if( living( ob[k] ) && !IsGhost( ob[k] ) )
     {
       tell_room( oven, format( "The heat is "
         "absolutely unbearable!" ) );

       ob[k]->DeathSequence( THISP, "baking" );
     }
   }

   kill_corpse();
   return 1;
}

int kill_corpse()  //Corpses turn into cooked meat, yum
{
   int a;
   object yum;
   object *ob;
   ob = all_inventory( oven );

   for( a = 0; a < sizeof( ob ); a++ )
   {
     if( ob[a]->query( CorpseP ) || ob[a]->query_corpse() )
     {
       destruct( ob[a] );
       yum = clone_object( OBJ "cooked" );
       move_object( yum, oven );
     }
   }
   return 1;
}

/*---------------------------------------------------------
       Non-Oven kitchen things - Cupboards and Sink
---------------------------------------------------------*/
get_cup( string arg )   //Get the cup from the cupboards
{
   string *valid_args = ({ "cup", "cup from cupboard",
                           "cup from cupboards" });

   if( member( valid_args, arg ) ==-1 )
     return notify_fail( format( "Grab what?" ) );

   if( !cup )
   {
     tell_player( THISP, "There are no cups in the cupboard." );
     return 1;
   }
   else
   {
     tell_player( THISP, "You grab a cup from the cupboard." );
     tell_room( ENV( THISP ), PNAME+" grabs a cup from the "
       "cupboard." , ({ THISP }) );

     move_object( clone_object( OBJ "empty_cup" ), THISP );
     cup = 0;
     return 1;
   }
}

int faucet_switch( string arg )   //The sink and faucet
{
   string *args_on  = ({ "faucet on",   "on faucet" });
   string *args_off = ({ "faucet off", "off faucet" });

   if( member( args_on, arg ) >= 0 )
   {
     if( faucet == 0 )
     {
       tell_player( THISP, "You turn the faucet on." );
       tell_room( ENV( THISP ), format( THISP->query_name() +
         "turns the kitchen faucet on." ) , ({ THISP }) );

       faucet = 1;
       return 1;
     }
     else
     {
       tell_player( THISP, "The faucet is already on." );
       return 1;
     }
   }
   else if( member( args_off, arg ) >= 0 )
   {
     if( faucet )
     {
       tell_player( THISP, "You turn the faucet off." );
       tell_room( ENV( THISP ), format( THISP->query_name() +
         "turns the kitchen faucet off." ) , ({ THISP }) );

       faucet = 0;
       return 1;
     }
     else
     {
       return( tell_player( THISP, "The faucet is already "
         "off."), 1 );
     }
   }
   else
   {
     return notify_fail( format( "Do what?" ) );
   }
}

/*---------------------------------------------------------
                Keeping track of some stuff
---------------------------------------------------------*/
int door_status() { return( closed ); }
int faucet_status() { return( faucet ); }
void change_status( int x ) { closed = x; }
