#include <ranger.h>
inherit RoomPlusCode;
object shop_ob;

void extra_create()
{
    set( "short", "A Kitchen" ); 
    set( "ansi_short", GRN "A Kitchen" );   
    
    set( "day_long", "This kitchen has been carved "
      "into solid rock. The room is small and cozy, "
      "it also smells absolutely delicious. Smoked "
      "meats and other delicacies hang from the ceiling. "
      "There is a large counter in the rear of the room, "
      "with a small oven behind it. The room is extremely "
      "bright due to huge gas lanterns that have been "
      "randomly attached to the rock wall." );
           
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    set( "day_light", BRIGHT );
    
    set( "descs",
    ([ 
      ({ "rock", "rocks", "wall", "ceiling", "ceilings" }) : 
         "The rock is extremely smooth. It "
         "appears to have been carved out using "
         "water instead of hand-tools",
      
      ({ "meat", "meats", "delicacies", "delicacy" }) :
         "There are hams, strings of garlic, salami, "
         "and more! All strung with care by thick hemp "
         "rope. All of it looks extremely tasty.",
         
      "counter" :
         "There are piles of meat in various stages of "
         "process on the counter. Fish, fowl, hoofed "
         "beast. Rangers must eat really well.",
      "oven" :
         "The oven is carved directly into the rock. "
         "There is currently nothing in it, but it is "
         "still glowing hot.",
      ({ "lantern", "gas lantern", "lanterns" }) :
         "While small these lanterns still put out an amazing "
         "amount of light. There are seven total and they are "
         "all burning strong."
    ]) );
      
      
    
    set( "exits", 
    ([
      "north" : ROOM "greatroom"      
    ]) );
    
    
    set( "reset_data" , 
    ([ 
      "monster" : MON "anful"
    ]) );
    
    shop_ob = clone_object( ShopCode );
    move_object( shop_ob, THISO );
    
    shop_ob->set( "sign_header", "Anful's kitchen and curios!" );
    shop_ob->set( "short", "a wooden sign" );
    shop_ob->set( "owner_name", "Anful" );
    shop_ob->set( "active_owner", 1 );
    shop_ob->set( "BignMeanstring", "says: I'm sorry "
      "but I just don't feel like dealing with you." );
    shop_ob->set( "permanent_item", OBJ "salami" );
    shop_ob->add( "permanent_item", "/zone/fantasy/yxuxacta/obj/heal/joint" );
    shop_ob->add( "permanent_item", "/obj/guild/forester/objects/herb/sticks" );
    shop_ob->add( "permanent_item", "/obj/guild/forester/objects/herb/feathers" );
}

void enter_signal( object inc, object vag )
{
    object anful;
    if( interactive( inc ) && objectp( anful = present( "Anful", THISO ) ) ) 
    {
	  anful->start_greet( inc );
      return 0;
    }
}   
