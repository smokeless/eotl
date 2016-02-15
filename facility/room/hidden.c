#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Facility 31 Security Room" );
    set( "ansi_short", YEL "The Facility 31 Security Room" );
    
    set( "day_long", "This is what remains of the security room. "
      "A couple broken closed circuit televisions lay in a pile "
      "of glass on the ground. There is a desk pushed up against the "
      "east wall. Various papers are strewn all over the floor. " 
      "Through an opening to the west you can see the museum." );
    
    set( "day_light", PART_LIT  );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "descs",
    ([ 
      ({ "desk", "wall", "east wall" })      : 
        "A cheap office supply center desk. It is cracked in half "
        "in the center. Judging from the scratch marks on the floor "
        "something pushed this desk away from the window. "
        "Behind the desk there is a door.",
      "door"                                 :
        "The door is made out of solid steel and appears to "
        "be very heavy. The handle is broken off. You don't "
        "think you will be able to get through.",
      ({ "television", "televisions" })      :
        "They are very small, only eight inches. There's no way anyone could see detail "
        "on these things. Fortunately you won't have to strain your eyes using them. "
        "All the glass has been broken out and the components don't look to be in "
        "very good shape either.",
      ({ "glass", "pile", "pile of glass" }) :
        "This pile is a mix of two way mirror glass and monitor glass. It's "
        "quite a bit of glass. You are careful not to cut yourself.",
      ({ "paper", "papers" })                :
        "None of them seem to be particularly important. They range from pornography to "
        "time sheets."
    ]) );
    set( "exits", 
    ([
      "west" : FROOM "museum1",
    ]) );
    
    set( "reset_data" , 
    ([ 
      "tablet" : FOBJ "securitytab",
    ]) );
}

void extra_init()
{
    add_action( "open", "open" );
}

int open( string arg )
{
    if( !stringp( arg ) || arg != "door" )
      return notify_fail( "Open what?\n" );
    
    tell_player( THISP, "As you touch the door a powerful "
      "force pulls you in.\n" );
    
    tell_room( ENV( THISP ), sprintf( "%s struggles with the "
      "door behind the desk. Suddenly %s vanishes.\n", THISP->query_name(), 
      subjective( THISP ) ), ({ THISP }) );
    
    move_player( &&, FROOM "cell", 0 );
    
    tell_room( ENV( THISP ), sprintf( "%s appears, looking confused.\n",
      THISP->query_name() ), ({ THISP }) );
    
    return 1;
}
