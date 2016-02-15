#include <grave.h>

inherit MonsterCode;
inherit MonsterTalk;
inherit MonsterMove;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create()
{
    set_name( "A traveller's ghost" );
    
    add_alias( "ghost" );
    add_alias( "traveller" );
    add_alias( "travellers ghost" );
    
    set_short( "a traveller's ghost" );
    set_long( "This ghost's face is heavily distorted. "
      "Its mouth is twisted in a permanent grin and its "
      "eyes glow bright yellow. Though you can tell it "
      "used to be a Kender. Long wispy trails make up "
      "its arms. Below the waist the body becomes completely "
      "incorporeal." );
    
    set_race( "kender" );    
    
    set_stat( "con", 1000 );
    set_stat( "dex", 1 );
    set_stat( "str", 1 );
    
    set( UndeadP, 1 );
    
    set_chat_chance( 10 );
    set_chat_rate( 50 );
    add_phrase( "@babble" );
    add_special_attack( "touch", THISO, 60 );
}

int babble()
{
    reset_combat();
    ansi_tell_room( ENV( THISO ), "The ghost begins to babble madly. "
      "You are enthralled by what it is saying. You feel "
      "excited to be listening! You never want to leave!\n", HIK );
    
    object *people = all_inventory( ENV( THISO ) );
    object *hypno;

    int x;
    
    hypno = ({});
    for( x = 0; x < sizeof( people ); x++ )
      if( GetOrdLevel( people[x] ) == MortalLevel )
        hypno += ({ people[x] });

    for( x = 0; x < sizeof( hypno ); x++)
    {
      object ob = clone_object( FOBJ "hypno_obj" );
      int time = hypno[x]->query_stat( "int" );
      ob->setup( time );
      move_object( FOBJ "hypno_obj", hypno[x] );
    }
}

int touch( object vic, object att )
{
    int wil = vic->query_stat( "wil" );
    
    if( wil < 2 )
      return 1;
      
    ansi_tell( vic, "The ghost reaches its wispy arms towards you! "
      "One of its arms makes contact with a piece of exposed skin. "
      "You feel a bit less sane.\n", YEL );
    ansi_tell_room( ENV( att ), sprintf( "The ghost of a traveller reaches its "
      "wispy arms out and touches %s.\n", vic->query_name() ), YEL, ({ vic }) );
    
    object bonus = clone_object( FOBJ "wil_obj" );
    move_object( bonus, ENV( vic ) );
    bonus->set_stat_bonus( "wil", -5 );
    bonus->set( "destruct_time", 100 );
    bonus->activate( vic );
}   
