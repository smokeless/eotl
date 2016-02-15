#include <popcontrol.h>

inherit RoomPlusCode;

int broken = 0;

void extra_create()
{
    set( "short", "Common room of the Deadliest Game Club" );
    
    set( "day_long", "You are in the common room of the Deadliest Game Club. "
      "Almost everything is made of pine. The floor creaks as you " 
      "walk on it. There are various trophy heads mounted on the walls. "
      "In the center of the room there is a square bar. Unfortunately there "
      "are no stools. It seems that people here are fond of standing. To "
      "the north there is a huge steel door with a camera above it." );
      
    set( "day_light", PART_LIT  );
    
    set( InsideP, 1 );
    set( NoCombatP, 1 );
    
    /*
    set( "exits", 
    ([
      "south" : PROOM "outside",
    ]) );
    */
   
    set( "reset_data", 
    ([ 
      "hank" : PMON "hank"
    ]) );
  
    set( "descs",
    ([ 
      "pine" : 
        "Cross sawn and finished with a clear coat "
        "whoever put this place together really liked "
        "wood.",
 
      ({ "trophy", "trophy heads", "head", "heads" }) :
        "Each one has been carefully preserved. There "
        "are deer, elk, bear, tiger, elephant, and even "
        "human heads here! This club obviously takes "
        "hunting seriously.", 
 
      "bar" :
        "It is very well stocked with alcohol of all sorts, "
        "ranging from Pabst Blue Ribbon to high end scotch.",
        
      ({ "steel", "door", "steel door" }) : 
        "You can't tell how thick it is. It looks "
        "like the only way to get in is for someone inside "
        "to let you in. You could try knocking on it.",
      
      "camera" : "@camera"
    ]) );
}

int camera()
{
    if( broken == 0 )
    {
      tell_player( THISP, "A large durable panasonic camera. The cable "
        "heads through the wall and presumably into "
        "a tv on the other side. If you felt like it "
        "you could probably vandalize the camera. Though "
        "you have no idea what response that might bring.\n" );
      return 1;
    }
    
    if( broken == 1 )
    {
      tell_player( THISP, "Someone has vandalized the camera. It "
        "is currently inoperative and awaiting repair." );
      return 1;
    }
}

void extra_init()
{
    add_action( "knock", "knock" );
    add_action( "vandalize", "vandalize" );
}

int knock( string arg )
{    
    if( broken == 1 )
    {
      tell_player( THISP, "You pound on the door as hard "
      "as you can. The camera is however broken, so no one " 
      "answers." );
      tell_room( ENV( THISP ), sprintf( "%s pounds on the steel "
      "door.\n", THISP->query_name() ), ({ THISP }) );
      return 1;
    }
    
    tell_player( THISP, "You pound on the door as hard "
      "as you can. The camera rotates a little and zooms "
      "in on your face.\n" );
    tell_room( ENV( THISP ), sprintf( "%s pounds on the steel "
      "door.\n", THISP->query_name() ), ({ THISP }) );
    
    if( THISP->query_prop_value( "Club_Member" ) == 1 )
    {
      tell_player( THISP, "The door opens quickly and you "
        "stroll inside.\n" );
      return 1;
    }
    return 1;
}

int vandalize( string arg )
{
    int dam = THISP->query( "con" ) + THISP->query( "str" )
      + random( 30 );
    string playeraction;
    object hank = present_clone( PMON "hank" );
    
    call_out( "repairbot", random( 500 ) );
  
    if( arg != "camera" )
      return 0;
  
    if( broken == 1 )
    {
      tell_player( THISP, "That's already been vandalized!\n" );
      return 1;
    }
  
    switch( random( 3 ) )
    {
      case 0 : playeraction = "You grab a hold of the wire sticking out "
               "of the camera and break it.\n"; break;
      case 1 : playeraction = "You get just within reach of the lense and "
        "hit it is hard as you can with your fist repeatedly. It "
        "shatters.\n";                          break;
      case 2 : playeraction = "You go hog wild spitting all over the camera "
        "until it short circuits. People shouldn't have nice "
        "things.\n";                            break;
    }
  
    tell_player( THISP, sprintf( "%s", playeraction ) );
    tell_room( ENV( THISP ), sprintf( "%s vandalizes the camera. "
      "What a dick.\n", THISP->query_name() ), ({ THISP }) );
    
    command( "roar", hank );
    
    tell_room( THISO, sprintf( "Hank grabs a shotgun from behind the "
      "bar and fires at %s! %s is knocked right out of the room!\n", 
      THISP->query_name(), CAP( subjective( THISP ) ) ), ({ THISP }) );
    tell_player( THISP, "Hank grabs a shotgun from behind the bar and "
      "fires at you! You are knocked right out of the room!\n" );
      
    THISP->add_hp( -dam );
    command( "hp", THISP );
    
    object shad = clone_object( PSHAD "shotgun.c");
    shad->sh_init( THISP );
    
    THISP->move_player( "&&", "/usr/socialism/workroom.c", 1 );
    
    tell_room( ENV( THISP ), sprintf( "%s slides in. %s body is riddled "
      "with bullet holes.\n", THISP->query_name(), 
      CAP( possessive( THISP ) ) ), ({ THISP }) );
    
    set( "day_long", "You are in the common room of the Deadliest Game Club. "
      "Almost everything is made of pine. The floor creaks as you " 
      "walk on it. There are various trophy heads mounted on the walls. "
      "In the center of the room there is a square bar. Unfortunately there "
      "are no stools. It seems that people here are fond of standing. To "
      "the north there is a huge steel door with a broken camera above it." );
    
    broken = 1;
    return 1;
}

int repairbot()
{
    broken = 0;
    
    tell_room( THISO, "A spider like repair bot creeps out from "
      "under the door. It climbs up the wall to the camera. There "
      "is some clicking and clacking. With the camera repaired "
      "the bot returns the same way it came.\n" );
    
    set( "day_long", "You are in the common room of the Deadliest Game Club. "
      "Almost everything is made of pine. The floor creaks as you " 
      "walk on it. There are various trophy heads mounted on the walls. "
      "In the center of the room there is a square bar. Unfortunately there "
      "are no stools. It seems that people here are fond of standing. To "
      "the north there is a huge steel door with a camera above it." );
    
    return 1;
}

void enter_signal( object inc, object person )
{
    object hank;
    if( interactive( inc ) && objectp( hank = present( "hank", THISO ) ) ) 
    {
	hank->start_greet( inc );
    return 0;
    }
} 
