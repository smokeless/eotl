#include <facility.h>
inherit MonsterCode;
inherit MonsterTalk;


void extra_create()
{
    set_name( "a horror" );
    add_alias( "creature" );
    add_alias( "horror" );
    add_alias( "indescribable horror" );
 
    set_short( "an indescribable horror" );
    set_ansi_short( "an indescribable horror", HIK  );
    set_long( "Parts, parts, and more parts! This thing has tentacles, "
      "it has arms, legs, and many mouths. You notice it is missing " 
      "eyes. It is coated in a thick gelatinous black slime. The tentacles "
      "writhe around its back and its mouths chomp. It flicks its tongues "
      "out into the air." );   
    
    set_gender( "other" );
    
    set_damage_bonus( 2 );
       
    set_alignment( EVIL_AL );
    
    set_stat( "str" , 100 );
    set_stat( "con" , 50 );
    set_stat( "wil" , 500 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 75 );
    
    set_skill( "dodge", 65 );
    
    set_type( "pyschic" );
    
    set( NoStunP, 1 );
    
    set_aggressive( 4 );
    
    set_natural_ac( 3 );
    
    set_chat_rate( 20 );
    set_chat_chance( 20 );
    
    add_phrase( "#say Ack'cthun." );
    add_phrase( "#say Masr'snaff. ct'oon." );
    add_phrase( "#say Snaral d'fan ar'marak" );
}

