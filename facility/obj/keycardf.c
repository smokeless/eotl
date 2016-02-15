#include <facility.h>

inherit NewThingCode;

void extra_create()
{
    string *firstname = ({ "George", "Miles", "Bill",
      "Agnes", "Harlan", "Evelyn", "Mary", "Thelonious",
      "Sarah", "Susan" });
    string *lastname = ({ "Smith", "Cooper", "Daniel",
      "Skoal", "Pride", "Haggard", "Keef", "Grizzly",
      "Squizzo" });
    string first = firstname[ random( sizeof( firstname ) ) ];
    string last = lastname[ random( sizeof( lastname ) ) ];
    set( "id", ({ "card", "keycard", "key" }) );
    set( "short", "a keycard" );
    set( "ansi_short", YEL "a keycard" );
    set( "long", sprintf( "This card appears to have "
      "belonged to someone before you. It "
      "has been swiped numerous times, "
      "judging by the worn magnetic strip. "
      "There is a name on the card, %s %s. "
      "Seems like they don't work here anymore. ",
      first, last ) );
 
    set( "weight", 1 );
    set( "value", 1 );
} 
string *query_key_codes()
{ 
    return( ({ "security_access" }) ); 
}

