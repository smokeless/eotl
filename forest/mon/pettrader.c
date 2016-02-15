#include <forest.h>

inherit MonsterAsk;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create()
{
    set_name( "Ursis" );
    add_alias( "ursis" );
    add_alias( "trader" );
    add_alias( "ursis the trader" );
    
    set_short( "Ursis the animal trader" );
    set_long( "This goblin is wild and unkempt. His hair is matted "
      "and tangled. His skin is covered in grease and dirt. "
      "Where his left eye should be there is an empty socket, "
      "his right eye is lazy. He wears a filthy fraying sleeveless "
      "canvas bag. He stinks of animal urine. His arms are covered "
      "in scratches." );
      
    set_gender( "male" );
    set_race( "goblin" );
    set_toughness( 3 );
    
    ask_me_about( "pet", "I love animals so much. You "
      "should see my house! Soooo many animals. If you "
      "had a pet I might be willing to make a trade." );
    ask_me_about( "animals", "I love animals so much. You "
      "should see my house! Soooo many animals. If you "
      "had a pet I might be willing to make a trade." );
    ask_me_about( "trade", "I am really interested in wolves. "
      "I can't get enough wolves. I have so many animal corpses "
      "laying around! I need something to eat them all. You can " 
      "<trade wolf> and I'll give you something new." );
    ask_me_about( "home", "My home is such a wonderful place! "
      "I have so many animals that it's hard to keep track of "
      "them all." );
    ask_me_about( "house", "My home is such a wonderful place! "
      "I have so many animals that it's hard to keep track of "
      "them all." );
    
    set_chat_chance( 50 );
    set_chat_rate( 40 );
    
    add_phrase( "#say I love animals." );
    add_phrase( "#say I hope my animals are doing well." );
    add_phrase( "#giggle" );
    add_phrase( "#say I found a walrus corpse under my couch yesterday... "
      "Well, under all the cat corpses. I thought the couch wasn't really "
      "sitting level so I lifted it up and surprise!!!!" );
    add_phrase( "#say One time I brought home a giant alligator. The poor "
      "thing was lost in the sewers. People said I wouldn't have space for "
      "it in my house. But I found room." );
} 

void extra_init()
{
    add_action( "trade", "trade" );
}

int trade( string str )
{
    object pwolf, animal, owner;
    int stre, dex, con, wil, hands;
    string animalrename, ownername;
    ownername = THISP->query_real_name();
    owner = find_player( ownername );
    
    if( !stringp( str ) || str != "wolf" )
      return notify_fail( "Trade what?\n" );
    
    if( !present_clone( "/obj/guild/ranger/obj/wolf", ENV( THISO ) ) )
    {
      command( "say You don't have a wolf. Unless it's an "
      "invisible wolf... Those are pretty rare though.", THISO );
      command( "shake", THISO );
      return 1;
    }
    pwolf = present_clone( "/obj/guild/ranger/obj/wolf", ENV( THISO ) );
    if( pwolf->query_master() != THISP->query_real_name() )
    {
      command( "say You can't trade a wolf that belongs to someone else." );
      return 1;
    }
    command( "lick", THISO );
    tell_room( ENV( THISO ), sprintf( "Ursis lifts up the wolfs lips, "
      "he inspects the gums and teeth.", THISP->query_name() ) );
    command( "say Yep, this wolf is perfect. Hang on a second." );
    stre = pwolf->query_stat( "str" );
    dex = pwolf->query_stat( "dex" );
    wil = pwolf->query_stat( "wil" );
    con = pwolf->query_stat( "con" );
    hands = pwolf->query_proficiency( "hands" );
    
    animal = clone_object( FMONS "pet" );
    animal->change_stat( "str", stre );
    animal->change_stat( "dex", dex );
    animal->change_stat( "con", con );
    animal->change_stat( "wil", wil );
    animal->set_proficiency( "hands", hands );
    animal->full_heal();
    animalrename = animal->query_short();
    animal->set_short( sprintf( "%s, it belongs to %s", animalrename,
      CAP( THISP->query_real_name() ) ) );
    
    animal->set_up( owner, ownername );
    
    move_object( animal, ENV( THISO ) );
    
    command( sprintf( "defend %s", THISP->query_name() ), animal );
    command( sprintf( "follow %s", THISP->query_name() ), animal );
    command( "allow all", THISP );
    
    
    
    return 1;    
}
