#include <facility.h>

inherit MonsterAsk; 

void extra_create()
{
    if( random( 5 ) > 2 )
      listen_for( "A voice booms over the", "@leave" );
    
    else
      listen_for( "A voice booms over the", "@shrug" );
  
    switch( random( 2 ) )
    {
      case 0 : set_gender( "male" ); break;
      case 1 : set_gender( "female" ); break;
    }
    
    set_name( "an intern" );
    
    add_alias( "intern" ); 

    set_short( "an intern" );
    
    set_long( sprintf( "A fairly nondescript worker stands "
      "here waiting for a task to do. %s seems bored. %s "
      "wears very informal attire, maybe %s hasn't been issued "
      "a Facility 31 uniform yet.", 
      CAP( subjective( THISO ) ), CAP( subjective( THISO ) ), 
      subjective( THISO ) ) );      
    
    set_race( "human" );
    
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str" , 100 );
    set_stat( "con" , 100 );
    set_stat( "wil" , 200 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 75 );
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 3 );

    move_object( clone_object( "/obj/armor/armor/clothing/t_shirt" ), THISO );
    move_object( clone_object( "/obj/armor/armor/clothing/breeches" ), THISO );
    move_object( clone_object( "/obj/armor/armor/boots/soft_leather_shoes" ), 
      THISO );
    command( "equip" );
}

void leave( string arg )
{
    command( "say Hmm, better take care of this." );
    
    tell_room( ENV( THISO ), "An intern wanders off to heed " 
      "the voice on the speaker.\n" );
    
    THISO->destruct_inventory();
    
    destruct( THISO );
}

void shrug( string arg )
{
    command( "shrug" );
}
