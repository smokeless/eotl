#include <facility.h>

inherit MonsterAsk;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create() 
{
    set_name( "Rifrad" );
    
    add_alias( "rifrad" );
    add_alias( "badgem" );
    add_alias( "doctor" );
    add_alias( "professor" );
    add_alias( "scientist" );
    add_alias( "doctor rifrad badgem" );
    
    set_short( "Doctor Rifrad Badgem" );
    
    set_long( "Rifrad stares dejectedly downwards. He barely "
      "acknowledges his own existence. His skin is old and wrinkled. "
      "He looks older than this building, older than time "
      "itself. His skin is extremely pale and his clothes are "
      "stained with sweat. He impatiently taps his fingers on the "
      "nearest table." );
    
    set_gender( "male" );
    set_race( "dwarf" );
    
    set_alignment( SAINTLY_AL );
    
    set_toughness( 45 );
    
    set_skill( "dodge", 65 );
    set_skill( "Darktongue", 25 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 3 );
    
    set_max_damage( 30 );
    
    set_chat_rate( 20 );
    set_chat_chance( 50 );
    
    add_phrase( "#shudder" );
    add_phrase( "#say So much has changed." );
    add_phrase( "#say What they do below, they will not say." );
    add_phrase( "#jitter" );
    
    listen_for( "shakes and rumbles", "AHAHAHAHA!!! THE "
	  "OLD ONE IS AWAKE!!!!!!" );
    
    ask_me_about( "change", "#say There was a time, "
      "when our work was new, and innocent. I "
      "fear that we may be overstepping the bounds." 
    );
    ask_me_about( "below", "#say This facility's location "
      "was carefully picked to be the most conducive to "
      "our needs. One of the things that enables us to "
      "delve so far into matters is the very earth itself. "
      "Our connection is through an ancient well that was dug "
      "here. It is older than time. Now I fear something "
      "sinister below. No one who works in that section "
      "will speak of it." 
    );
    ask_me_about( "experiments", "#say The screams... The screams..." );
    
    move_object( clone_object( FARMOR "pants" ), THISO );
    move_object( clone_object( FARMOR "shirt" ), THISO );
    command( "equip" );
  
    add_special_attack( "evasive", THISO, 10 );
    add_special_attack( "soulwell", THISO, 4 );
    add_special_attack( "banish", THISO, 1 );
}

int evasive( object vic, object att )
{
    ansi_tell_room( ENV( att ), sprintf(
     "Rifrad seems to speed up." ), BLU,
      ({ }) );
    
    set_skill( "dodge", 500 );
    
    call_out( "stopdodge", 5 );
    
    return 1;
}

int stopdodge()
{
    int dodge = random( 50 ) + 50;
    
    set_skill( "dodge", dodge );
    
    ansi_tell_room( ENV( THISO ), sprintf( "Rifrad slows down." ), BLU,
      ({ }) );
    
    return 1;
}

int jointhem( object vic, object att )
{
    int dam = 100 + random( 24 );
    string vict = vic->query_name();
    
    command( "say Enough of this! I will join the rest!" );
    ansi_tell_room( ENV( att ), sprintf(
      "Rifrad raises his hands in front of his face. "
      "His hands stretch in front of him and the fabric of "
      "reality tears." ), BLU,
      ({ att }) );
    
    destruct( THISO );
    
    return 1;  
}

int soulwell( object vic, object att )
{
    command( "say To me fiends! I must not join you! Yet..." );
    
    ansi_tell_room( ENV( att ), "A black mist comprised of "
      "lost souls begins to rise from the ground. Rifrad breathes "
      "deeply.", HIK );
    
    att->add_hp( 30 + random( 30 ) );
    return 0;
}

int DeathSequence( object killer, string cause, int nocorpse )
{
    ansi_tell_room( ENV( THISO ), "A black mist rises from the ground. "
      "The room chills.\n", HIK, ({ }) );
    
    object ghost = clone_object( FMONS "deadrif" );
    move_object( ghost, ENV( THISO ) );
    
    ghost->attack_object( killer );
    
    return( ::DeathSequence( killer, cause, 1 ) );
}
