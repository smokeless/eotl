#include <ansi.h>

inherit TrophyCaseCode;

void extra_create()
{
    set_ids( ({ "large box covered in skulls", "skulls", "skull box", "box",
      "case", "trophy case", "trophycase" }) );
    set_short( "a large box covered in skulls" );
    set_long( "This large box is made out of some sort of black wood. "
      "It is covered in animal skulls and carved runes. The hinges "
      "are solid ivory. There is solid silver binding on all of the "
      "edges." );      
    set_guild( "shaman" );
    set_guild_msgs( ({ "You cannot bring yourself to touch "
      "an item of such power.", CYAN, "%s gazes longingly at the "
      "guild trophy.", CYAN }) );
    set_defender( "Yachak" );
    set_defend_msgs( ({ "%s snaps out of his trance and attacks you!", CYAN,
      "%s snaps out of his trance and attacks %s!", CYAN }) );
}
