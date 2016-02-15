inherit MonsterCode;

#include BobCode
#include "local_defs.h"

int room, x;
string indir, outdir, task, *chatting, *responses;
object hall;

void extra_create()
{
  string *killem;
  seteuid(getuid());
  set_name( "googor" );
  set_short( "Googor is sitting on a chair in "
    "the corner, twiddling his thumbs." );
  set_long( "Googer is a hulking troll, rather oddly "
    "outfitted in a polo shirt and khakis.  He doesn't "
    "look particularly bright but, by the looks you've "
    "noticed him give Knacker, he's loyal." );
  set_gender( "male" );
  set_race( "troll" );
  set_toughness( 1000 );
  set("emetic_group", "rebellion");
  set("emetic_status", 1);
  set( NoCharmP, 1 );
  mp_setup( MOV "googor1" );
  task = "evict";
  killem = grab_file( HOUSING "kill_on_sight" );
  chatting = ({
    "whys it so hot alls the time?",
    "Because of the war Googor.  The bombs messed up the atmosphere.",
    "how comes we dont live in the dome?  it looks neat.",
    "Because they don't allow gnomes into Ptarmagon City Googor.  "
      "They're a bunch of fuckin' racists in there.",
    "can i gets some more of that candy stuff?  it was goooood.",
    "Not unless you eat all your supper Googor.",
    "how comes when i walks to the dome i cants get in?",
    "Ptarmagon City?  They've sealed it off because of the heavy "
      "gang fighting Googor.  Nobody is allowed in or out until the "
      "CIA has put down the gangs.",
    "these walls sure are purty.  i like this brass!",
    "Yes, well my Dad taught me everything I knew back when I was "
      "growing up in the GnomeLands.  He was the best ever.",
    "which do u like science or magic the bestest?",
    "Well you can always depend on science Googor.",
    "im bored.. is theres anyones to evictapate?",
    "Not right now Googor..  I'll check the books again a little later.",
    "yer my bestest friend knacker.",
    "And you are a fine, stalwart companion, Googor.  Always glad "
      "for your company.",
    "i really hate that " + killem[sizeof(killem)-1] + "!  i cant "
      "believes anybody would wants to hurts us!",
    "Yeah I hate that fucker too.  We'll have a surprise waiting "
      "next time that creep pokes around here!",
  });

  responses = ({ "say hmm", "say oh i sees now", "emote thinks hard.",
    "say well son of a gun", "say gosh", "blink", "say really?",
    "say no WAY!", "say hrm", "say geez", "say you dont say" });

    set(NoTeleportP, 1);
    set(NoControlP, 1);
}

init()
{
  string *killem;
  killem = grab_file( HOUSING "kill_on_sight" );
  if( member( killem, PRNAME ) != -1 && is_player(THISP) )
    call_out( "take_em_down", 1, THISP );
}

take_em_down( object killee )
{
    command( "say YOU!#@!!!", THISO );
    command( "emote roars with rage!", THISO );
    command( "kill " + PRNAME, THISO );
}

take_damage( int dam, int loc, string type, object att, object w )
{
  string *killem;
  if( is_player(att) )
  {
    killem = grab_file( HOUSING "kill_on_sight" );
    command( "say OW!!!", THISO );
    if( member( killem, att->query_real_name() ) == -1 )
      write_file( HOUSING "kill_on_sight", att->query_real_name() + "\n" );
    if( present("knacker applebanger", ENV(THISO)) )
      present("knacker applebanger", ENV(THISO))->take_em_down(att);
  }
  return ::take_damage( dam, loc, type, att, w );
}

check_evicted_list()
{
  int *rooms;
  rooms=APARTMENT->query("roomstoclean");
  task = "evict";
  if( rooms == ({}) )
  {
    task = "repair";
    rooms = APARTMENT->query("doorstofix");
    if( rooms == ({ }) )
    {
      command( "say nothin' to do", THISO );
      return 1;
    }
  }
  room = rooms[0];
  if( query_short() == "Googor is sitting on a chair "
    "in the corner, twiddling his thumbs." );
  {
    command( "emote lumbers to his feet.", THISO );
    set_short( "Googor is standing here in a hulkingly "
      "huge sort of way." );
  }
  mp_setup( MOV "go_to_elevator" );
  return 1;
}

go_to_elevator()
{
  if( !present("elevator entrance",ENV(THISO)) )
    command( INBOUND, THISO );
  else
  {
    if( (present("elevator entrance",ENV(THISO))->query_doors_open()) )
    {
      command( "enter elevator", THISO );
      mp_setup( MOV "find_room" );
      return 1;
    }
    else
      command( "press call button", THISO );
  }
  return 0;
}

find_room()
{
  if( load_name(ENV(THISO)) == (HOUSING"elev") )
  {
    if( ( (ENV(THISO)->query_current_floor()) == ((room/100)-1) )
      && ( (ENV(THISO)->query_doors_open()) == 1 ) )
      command( "out", THISO );
    else
      command( "press " + (room/100), THISO );
    return 0;
  }
  if( ((ENV(THISO)->query("room_number"))!=room) &&
    (((ENV(THISO)->query("room_number"))+1)!=room) )
    command( OUTBOUND, THISO );
  else
  {
    hall = ENV(THISO);
    if( hall->query("room_number") == room )
      { indir  = ROOMONEDIR; outdir = ROOMTWODIR; }
    else
      { indir  = ROOMTWODIR; outdir = ROOMONEDIR; }
    switch( task )
    {
      case "evict" :
        mp_setup( MOV "clean_room" );
        return 1;
        break;
      case "repair" :
        repair();
        return 0;
        break;
    }
  }
  return 0;
}

repair()
{
  int *rooms;
  object note;
  command( "emote fixes the door to apartment " + room + " with "
    "a new door he pulls out of his pocket.", THISO );
  note = clone_object( HOUSING "doornote" );
  move_object( note, ENV(THISO) );
  note -> set("short", "a note stuck on the door to room " + room );
  command( "emote attaches a note to apartment " + room + ".", 
    THISO );
  APARTMENT->finish_repair(room);
  command( "smile", THISO );
  rooms=APARTMENT->query("roomstoclean");
  task = "evict";
  if( rooms == ({}) )
  {
    task = "repair";
    rooms = APARTMENT->query("doorstofix");
    if( rooms == ({ }) )
    {
      command( "say no more rooms to fix", THISO );
      room = 0;
      mp_setup( MOV "back_to_lobby" );
      return 1;
    }
  }
  room = rooms[0];
  mp_setup( MOV "go_to_elevator" );
  return 1;
}

clean_room()
{
  int *rooms;
  object key, stuff, note, *stuffs;
  string short;

  if( ENV(THISO) == hall && room )
  {
    if( !present("master key") )
    {
      key = clone_object( HOUSING "master_key" );
      move_object( key, THISO );
      tell_room( hall, "Googor hums a spell and a key appears in his hand.\n" );
      command( "unlock " + to_string(room), THISO );
    }
    command( indir, THISO );
    tell_room( ENV(THISO), "Googor hums a spell and his key vanishes.\n" );
    destruct( present("master key") );
    command( "say 'k everybody outs; yer bein' evicted.  if you dont "
      "leaves now, i's gunna throws you out.", THISO );
    return 0;
  }
  if( ENV(THISO) == hall && room == 0 )
  {
    rooms=APARTMENT->query("roomstoclean");
    command( "smile", THISO );
    task = "evict";
    if( rooms == ({}) )
    {
      task = "repair";
      rooms = APARTMENT->query("doorstofix");
      if( rooms == ({ }) )
      {
        command( "say no more rooms to clean", THISO );
        room = 0;
        mp_setup( MOV "back_to_lobby" );
        return 1;
      }
    }
    room = rooms[0];
    mp_setup( MOV "go_to_elevator" );
    return 1;
  }
  stuff = all_inventory(ENV(THISO));
  stuff -= ({THISO});
  if( present("walker",ENV(THISO)) )
    stuff -= ({ present("walker",ENV(THISO)) });
  if( stuff == ({}) )
  {
    command( "emote does a final check around the room.", THISO );
    if( !present("master key") )
    {
      key = clone_object( HOUSING "master_key" );
      move_object( key, THISO );
      tell_room( hall, "Googor hums a spell and a key appears in his hand.\n" );
    }
    command( "unlock " + to_string(room), THISO );
    command( outdir, THISO );
    command( "lock " + to_string(room), THISO );
    tell_room( ENV(THISO), "Googor hums a spell and his key vanishes.\n" );
    destruct( present("master key") );
    note = clone_object( HOUSING "evictnote" );
    move_object( note, ENV(THISO) );
    note -> set("short", "a note stuck on the door to room " + room );
    command( "emote attaches a note to apartment " + room + ".", 
      THISO );
    APARTMENT->finish_cleanup(room);
    room = 0;
    return 0;
  }
  if( living(stuff[0]) )
  {
    short = stuff[0]->query_name();
    tell_object( stuff[0], strformat( "Googor picks you up and tosses "
      "you out the door to the " + outdir + "." ) );
    tell_room( hall, strformat( short + " sails out "
      "of the apartment to the " + indir + ", landing with a thump." ) );
    move_object( stuff[0], hall );
    tell_room( ENV(THISO), strformat( "Googor tosses " +
      short + " out the door to the " + outdir + "." ) );
    command( "glance", stuff[0] );
    return 0;
  }
  if( stuff[0]->query("installed_furniture") )
    command( "remove " + stuff[0]->query("id")[0], THISO );
  short = stuff[0]->query("short");
  if( !short )
    short = stuff[0]->query("id")[0];
  if( member(stuff[0]->query("id"),"^MoNeY$") != -1 )
  {
    tell_room( ENV(THISO), strformat( "Googor picks up the coins"
      " and stuffs them in his pocket." ) );
    APARTMENT->add_skim(stuff[0]->query("value"));
    destruct( stuff[0] );
    return 0;
  }
  tell_room( ENV(THISO), strformat( "Googor tosses " +
    short + " out the door to the " + outdir + "." ) );
  move_object( stuff[0], hall );
  tell_room( hall, strformat( short + " sails out "
    "of the apartment to the " + indir + ", landing with a thump." ) );
  return 0;
}

back_to_lobby()
{
  if( load_name(ENV(THISO)) == (HOUSING"lobby") )
  {
    command( "emote plunks down heavily in the chair across "
      "from Knacker Applebanger", THISO );
    set_short( "Googor is sitting on a chair in the corner, "
      "twiddling his thumbs." );
    command( "say all done", THISO );
    mp_setup( MOV "googor1" );
    return 1;
  }
  if( load_name(ENV(THISO)) == (HOUSING"elev") )
  {
    if( ( (ENV(THISO)->query_current_floor()) == 0 )
      && ( (ENV(THISO)->query_doors_open()) == 1 ) )
      command( "out", THISO );
    else
      command( "press 1", THISO );
    return 0;
  }
  if( !present("elevator entrance",ENV(THISO)) )
    command( INBOUND, THISO );
  else
  {
    if( (present("elevator entrance",ENV(THISO))->query_doors_open()) )
      command( "enter elevator", THISO );
    else
      command( "press call button", THISO );
  }
  return 0;
}

set_task( string str )
{
  task = str;
}

status question( string *str )
{
  int y;
  y=x;
  while( x==y )
    x=random(sizeof(chatting)/2);
  command( "say " + chatting[2*x], THISO );
  return 0;
}

status answer( string *str )
{
  object knacker;
  if( knacker=present("knacker applebanger", ENV(THISO)) )
  {
    command( "say " + chatting[(2*x)+1], knacker );
    return 0;
  }
  command( "say knacker?", THISO );
  command( "sigh", THISO );
  return 0;
}

status response( string *str )
{
  if( present("knacker applebanger", ENV(THISO)) )
  {
    
    command( responses[random(sizeof(responses))], THISO );
    return 0;
  }
  command( "say durnit i wantsted to know!", THISO );
  return 0;
}

regen_googor()
{
/*
  move_object( THISO, HOUSING "lobby" );
  ENV(THISO) -> extra_reset();
*/
  return 0;
}
