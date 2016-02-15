#include <forest.h>

inherit MonsterCode;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create() 
{
    set_name( "an angel of decay" );
    
    add_alias( "angel" );
    add_alias( "decay" );
    add_alias( "angel of decay" );
    add_alias( "decay angel" );
    
    set_short( "an angel of decay" );
    set_ansi_short( YEL "an angel of decay" );
    
    set_long( "Standing nine feet tall this horror "
      "weighs in at a 700 pounds. Large festering wings are attached to "
      "a dripping putrid body. It has 3 fingers, each of them ending "
      "in a viciously sharp talon. Wet filthy juice trickles from its "
      "eye sockets down to a puddle at its feet. The air around it is "
      "mephitic." );
      
    set_gender( "unknown" );
    set_race( FRACE "dangel" );
    
    set_alignment( EVIL_AL );
    
    set_proficiency( "hands", 200 );
    
    set_stat( "str", 200 );
    set_stat( "con", 500 );
    set_stat( "int", 100 );
    set_stat( "wil", 100 );
    set_stat( "dex", 300 );
    
    
    set_skill( "dodge", 75 );
    set_skill( "Darktongue", 25 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_chat_rate( 10 );
    set_chat_chance( 50 );
     
    add_phrase( "#growl" );
    add_phrase( "#scream" );
    add_phrase( "#Darktongue When I am finished here I am coming for you." );
    add_phrase( "#Darktongue I will rot the very essence of your being." );
    
    set_heart_beat( 1 );
    
    add_special_attack( "claw",  THISO, 4 );
    add_special_attack( "rot", THISO,   2 );
}

void heart_beat()
{
    object *inv;
    if( random( 50 ) < 10 )
    {
    int i, dam, ftg, mana;
    dam = random( 75 );
    ftg = random( 75 );
    mana = random( 75 );
    ansi_tell_room( ENV( THISO ), "The air around the angel is rotting you!\n",
      RED );
    inv = filter_array( all_inventory( ENV( THISO ) ), #'living );
    i = sizeof( inv );
    while( i-- )
    {
      inv[ i ]->take_damage( dam, 0, "unholy", THISO );
      inv[ i ]->add_fatigue( -ftg );
      inv[ i ]->add_mana( -mana );
    }
    }
}
      
      

int claw( object vic, object att )
{
    int time;
    int dam = random( 75 ) + 75;
    object rot;
    
    ansi_tell_room( ENV( att ), sprintf(
     "The angel lashes out at %s with its claws.\n", 
     vic->query_name() ), RED, ({ vic }) );
    ansi_tell( vic, "The angel rips into you with "
      "its claws.\n", RED );
    if( 10 > random( 40 ) )
    {
      rot = clone_object( FOBJ "rotobj" );
      time = vic->query_stat( "str" );
      ansi_tell( vic, "The angel leaves some of its "
        "filth on your skin.\n", RED );
      move_object( rot , vic );
      rot->do_bonus( vic, time );
    }
    
    vic->take_damage( dam, 0, "disease", THISO );
    
    return 1;
}

int rot( object vic, object att )
{
    int item;
    object *worn;
    
    if( sizeof( vic->query_armor_worn() ) == 0 )
    {
      ansi_tell_room( ENV( att ), sprintf( "The angel spits a stream "
        "of rotted matter all over %s!\n", vic->query_name() ),
        YEL, ({ vic }) );
      ansi_tell( vic, sprintf( "The angel spits a stream "
        "of rotted matter all over you!\n" ), YEL );   
      return 1;
    }
    
    worn = vic->query_armor_worn();
    item = random( sizeof( worn ) );
    
    ansi_tell_room( ENV( att ), sprintf( "The angel spits a stream "
      "of rotted matter all over %s! Destroying %s %s.\n", 
      vic->query_name(), possessive( vic ), worn[ item ]->query_short() ),
      YEL, ({ vic }) );
    ansi_tell( vic, sprintf( "The angel spits a stream "
      "of rotted matter all over you! The liquid "
      "decays your %s\n", worn[ item ]->query_short() ), YEL );
    
    destruct( worn[ item ] );
    return 1;    
}

int DeathSequence( object killer, string cause, int nocorpse )
{
    ansi_tell_room( ENV( THISO ), "The angel sinks into "
      "a puddle of rot.", HIK, ({ }) );
      
    return( ::DeathSequence( killer, cause, 1 ) );
}
