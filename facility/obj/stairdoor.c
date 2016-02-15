#include <facility.h>

inherit DoorObjCode;

void extra_create()
{
    set( "id", ({ "door", "steel door" }) );
    
    set( "long", "Faded dented steel seals the entry to a room "
	  "hidden deep within in the depths of the facility. " 
      "You can hear the hum of machinery coming from behind it "
      "and something else... Something more primal. Every so often "
      "there is a sound, as if something is eating messily." );
    
    set( "closeable", 1 );
    set( "lockable", 1 );
    set( "closed", 1 );
    set( "locked", 1 );
    set( "obvious", 1 );
    set( "no_smash", 1 );
    set( "lock_level", 10 );
    set( "key_codes", "security_access" );
}
