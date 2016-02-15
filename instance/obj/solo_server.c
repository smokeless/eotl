#include <instance.h>
int ilvl;
object who;
object where;
string monster;
object room;
void go( int monsterLevel, int dungeonLevel, object room, object player,
string monsterName )
{
    /*
      The following comments are for anyone who
      may have to fix anything, so they don't have
      to read through a shit ton of garbage. Well
      documented code helps with things.
      This particular version only deals with up
      to blue items. Purples/Legendary are dealt
      with in the other server.
      Taplash 2015
    */
    
    /* 
    Item levels:
    1: white, just a standard shitty item. Any monster.
    2: green, an ok item, loyal as soon as equipped.
    3: blue, a solo encounter boss monster decent item. 
       Items are auto-loyal to killer.
    4: purple, top of the line item. loyal to those who
       were in the room with the monster for the encounter
       or took part in the encounter.
    5: legendary, loyal to one person. Top tier item,
       only works for one class type. probably won't see
       drops.
    */
    
    /*
    Monster levels:
    1: Drops white items, rare chance for a green.
       Fairly weak monster. Solo capable.
    2: Drops white items, medium chance for a green,
       Harder monster. Solo capable.
    3: Drops blue items, chance for green.
       Boss monster, very difficult. Solo capable.
    4: Drops purple items, chance for blue.
       Not soloable. You will need the holy trinity!
    5: Drops legendary. Not soloable, complicated fight,
       You will need a large group.
    */
    
    /*
    Dungeon level is the challenge level of the dungeon.
    What level range it is targeted at. The range is
    1-5, 5 being the highest difficulty and 1 being the
    lowest. This changes the stats on the weapons.
    Level 1: eval range of  50-70
    level 2: eval range of  70-120
    level 3: eval range of  100-150
    level 4: group of 5 eval 120+
    level 5: >5 group of eval 120+
    */
    int x = monsterLevel;
    ilvl = dungeonLevel;
    object who = player;
    where = room;
    monster = monsterName;
    room = room;
    switch( x )
    {
        case 1  : call_out( "trash",  1 ); break;
        case 2  : call_out( "green",  1 ); break;
        case 3  : call_out( "blue",   1 ); break;
        default : call_out( "trash",  1 ); break;
    }
}

void trash()
{
    //Trash has no adjustments.
    //It's just garbage.
    if( random( 50 ) + 1 > 25 )
    {
      object x = clone_object( WEAP "trash" );
      move_object( x, room );
      tell_room( room, sprintf( "%s falls to the ground.", x->query_short() ) );
    }
    object x = clone_object( ARMOR "trash" );
    move_object( x, room );
    tell_room( room, sprintf( "%s falls to the ground.", x->query_short() ) );
}
    
