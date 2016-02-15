#include <ansi.h>
inherit NewThingCode;

string type;
int healpower;

void extra_create()
{
    set_id( "plant" );
    set( InvisP, 1 );
    set_gettable( 0 );
    set_value( 0 );
    call_out( "sprout", 15 );
}

void set_me_up( int skill )
{
    healpower = skill;
}

int sprout()
{
    THISO->add_ids( ({ "sprout", "sprouting plant" }) );
    THISO->set( InvisP, 0 );
    
    THISO->set_short( "a sprouting plant" );
    THISO->set_long( "The area around this sprouting plant "
      "has been carefully mulched. It looks like someone actually "
      "cultivated this plant." );
    
    call_out( "mature", 15 );
    return 1;
}

int mature()
{
    THISO->set_ids( ({ "plant", "maturing plant" } ) );
    THISO->set_short( "a maturing plant" );
    THISO->set_long( "The area around this maturing plant "
      "has been carefully mulched. It looks like whoever "
      "cultivated this plant did a good job. At least "
      "judging by how green it is. Unfortunately it is "
      "still too young to tell what kind of plant it will "
      "be." );
    call_out( "ripe", 15 );
    return 1;
}

int ripe()
{
    switch( random( 5 ) )
    {
      case 0 : type = "weed";
               THISO->set_ids( ({ "plant", "weed",
                 "a fully grown weed", "grown plant" }) );
               THISO->set_short( "a fully grown weed" );
               THISO->set_long( "All that care and time put in, "
                 "just to grow a weed! It is a very healthy looking "
                 "weed though. Unfortunately it is too thick and "
                 "coarse to be edible." );
               break;
      
      case 1 : type = "legume";
               THISO->set_ids( ({ "plant", "bean", "bean plant",
                 "grown plant", "fully grown plant", "fully grown "
                 "bean plant" }) );
               THISO->set_short( "a fully grown bean plant" );
               THISO->set_long( "This plant looks extremely "
                 "healthy. The vines and leaves are bright "
                 "green. It has produced a number of blue "
                 "wizard beans. It might be time to harvest "
                 "this plant." );
               break;                 
  
      case 2 : type = "leaf vegetable";   
               THISO->set_ids( ({ "plant", "lettuce",
                 "lettuce plant", "fully grown letttuce plant" }) );
               THISO->set_short( "a fully grown lettuce plant" );
               THISO->set_long( "Crisp, fresh, refreshing. Your "
                 "mouth waters as you look at the leaves. They "
                 "are varying in color from bright green to dark "
                 "red. This plant is obviously a wild mix. It "
                 "might be time to harvest it." );
               break;
    
      case 3 : type = "berry bush";       
               THISO->set_ids( ({ "bush", "berry bush", "berry"
                 "fully grown plant", "fully grown berry bush" }) );
               THISO->set_short( "a fully grown berry bush" );
               THISO->set_long( "This bush is made up of thick "
                 "thorny vines. It has bright blue leaves and there "
                 "are delicious berries all over it. It might be "
                 "time to harvest it." );
               break;
      
      case 4 : type = "root vegetable";   
               THISO->set_ids( ({ "vegetable", "root vegetable",
                 "fully grown vegetable", "fully grown root vegetable" }) );
               THISO->set_short( "a fully grown root vegetable" );
               THISO->set_long( "Some sort of root vegetable cluster "
                 "bulges out from underneath soft green leaves. It's "
                 "hard to tell what is underneath. Maybe it is time "
                 "to harvest it!" );
               break;
    }
    add_action( "harvest", "harvest" );
    call_out( "die", 15 );
    return 1;
 }
 
 int harvest( string arg )
 {
    if( !stringp( arg ) || arg != "plant" )
      return notify_fail( "Harvest what?" );
    if( type == "weed" )
    {
      tell_player( THISP, "You pull the weed out of "
        "the ground and discard it." );
      tell_room( ENV( THISP ), sprintf( "%s pulls a weed "
        "out of the ground and discards it.",
        THISP->query_name() ) );
      destruct( THISO );
    }
    
    tell_player( THISP, "You carefully harvest "
      "the plant." );
    tell_room( ENV( THISP ), sprintf( "%s harvests a %s.",
      THISP->query_name(), THISO->query_short() ), ({}) );
    
    destruct( THISO );
    return 1;
}
 
void die()
{
    tell_room( ENV( THISO ), sprintf( "%s withers and dies, "
      "absorbing back into the ground where it was born.",
      THISO->query_short() ), ({ }) );
    destruct( THISO );
}
