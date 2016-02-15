#include <instance.h>
inherit MonsterCode;

void extra_create()
{
    set_name( "a goblin digger" );
    add_alias( "goblin" );
    add_alias( "goblin digger" );
    add_alias( "digger" );
    set_short( "a goblin digger" );
    set_long( "This ugly goblin looks really worn out. "
      "It's dressed in just a loin cloth. It's nails are "
      "yellow with fungus, and dirt is lodged underneath them. "
      "It toils away digging for something valuable." );
    
    if( random( 2 ) )
      set_gender( "male" );
    else
     set_gender( "female" );

    set_race( "goblin" );
    set_alignment( random( -4000 ) );
    if( random( 2 ) )
        set_alignment( random(4000 ) );
    set_stat( "str", 100 + random( 100 ) );
    set_stat( "wil", 150 + random( 100 ) );
    set_stat( "int", random( 100 ) );
    set_stat( "con", 140 + random( 40 ) );
    set_skill( "dodge", 40 );
    set_proficiency( "hands", 60 );
    set_aggressive( 0 );
    switch( random( 3 ) + 1 )
    {
      case 1 : THISO->ogre(); break;
      case 2 : THISO->body(); break;
      case 3 : break;
      default : break;
    }
}

void ogre()
{
    set_name( "an ogre henchman" );
    add_alias( ({ "ogre", "ogre henchman", "henchman"}) );
    set_short( "an ogre henchman" );
    set_long( "This medium sized ogre looks really mean. "
      "It's large and in charge. Its yellow eyes flick "
      "side to side looking for something to terrorize. "
      "Over all it's a nasty thing." );
    set_aggressive( 5 );
    set_race( MON "ogre" );
    set_stat( "str", 200 + random( 100 ) );
    set_stat( "wil", 240 + random( 20 ) );
    set_stat( "con", 300 );
    set_skill( "dodge", 60 );
    set_proficiency( "hands", 60 );
}

void body()
{
    set_name( "an ogre bodyguard" );
    add_alias( ({ "ogre", "bodyguard", "ogre bodyguard" }) );
    set_short( "an ogre bodyguard" );
    set_long( "This is one big ass ogre. It's also one "
      "mad ogre. It's obviously one of the higher ranked "
      "miners. Its muscles bulge and flex. Its got thighs "
      "the size of a gnomes body. Going up against this "
      "thing might be tough." );
    set_race( MON "ogre" );
    set_aggressive( 1 );
    set_stat( "str", 300 + random(50) );
    set_stat( "wil", 300 + random( 50 ) );
    set_stat( "con", 400 );
    set_skill( "dodge", 70 );
    set_proficiency( "hands", 70 );
    set_guild( "fighter" );
    set_specialization( "bodyguard" );
}
    
