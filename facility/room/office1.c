#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "Facility 31 Office Space" );
    set( "ansi_short", YEL "Facility 31 Office Space" );
    
    set( "day_long", "Everything that made this an office is gone. "
      "All of the computers and tables have been removed. The only "
      "evidence they were ever here is clean white carpet in the "
      "shape of tables. Of course the clean carpet is still surrounded "
      "by stains. To the north you can see the intern area. To the " 
      "west there is a stairwell heading down. To the east is the lobby." );      
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", 
    ([
      "east"  :  FROOM  "lobby1",
      "north" :  FROOM "intern1",
      "west"  :  FROOM "ustair1"        
    ]) );
    set( "descs",
    ([ 
    ({ "carpet", "stains" }) :
      "It's amazing how much dirt and filth carpet can "
      "soak up. The stains vary from brown to black. "
      "It's quite the contrast to the fresh white carpet "
      "that has been revealed."      
    ]) );    

	set( "reset_data" , 
    ([ 
      "dark"  : FMONS "darkness",
      "dark1" : FMONS "darkness"
    ]) );
}
