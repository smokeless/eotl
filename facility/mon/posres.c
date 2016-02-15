#include <facility.h>;

inherit MonsterCode;
inherit MonsterMove;
inherit MonsterTalk;
inherit SpecialAttackCode;
inherit AnsiTellCode;

int arms = 2;
int legs = 2;
int healspecial = 5;
int accelspecial = 7;
int dodge = 5;

void extra_create()
{
    string variety;
    string mrace;    
    int strmod = random( 50 );
    int wilmod = random( 100 );
    int intmod = random(200);
      
    set_name( "an insane researcher" );
    
    add_alias("creature");
    add_alias("possessed");
    add_alias("researcher");
    add_alias("doctor");
    add_alias("scientist");
    add_alias("beast");
    add_alias("insane");
    add_alias( "insane researcher" );
    
    switch(random( 4 ) )
    {
      case 0 : mrace = "gnome";    break;
      case 1 : mrace = "human";    break;
      case 2 : mrace = "drow_elf"; break;
      case 3 : mrace = "dwarf";    break;
    }
    
    switch( random( 5 ) ) {
      case 0 : variety = "huddled in the corner";          break;
      case 1 : variety = "ripping at its own face";       break;
      case 2 : variety = "covered in its own blood";      break; 
      case 3 : variety = "wheezing through a broken nose"; break;
      case 4 : variety = "vomiting all over itself";       break;
    }
    
    set_short( sprintf( "a researcher, %s", variety ) );
    set_long( "You can't tell whether this was a man or a woman. "
              "It has long since passed beyond gender and "
              "into the inhuman. Scabs fester, crack, and "
              "bleed all over its skin. Its eyes are gone "
              "the sockets stained with blood. It appears that "
              "the wounds were self inflicted." );

    set_alignment( EVIL_AL );
    
    set_gender( "unknown" );
    
    set_aggressive( 5 );
    set_proficiency( "hands", 100 );
    
    add_combat_message( "rip", "rips" );
    
    set_chat_chance( 90 );
    set_chat_rate( 50 );
    
    add_phrase( "#say We went too far, " 
      "and yet it's all smiles here." ); 
    add_phrase( "#say The Darkness has shown me the "
      "light!" );
    add_phrase( "#say I found the taste of sentient beings "
      "to be so much sweeter than that of others." );
    add_phrase( "#say Is this my blood?" );
    add_phrase( "#say I will flay your skin and put you "
      "with the rest of them." );
    add_phrase( "#say Lost, lost, lost, lost, lost..." );
    add_phrase( "#say Stop screaming! ");
    add_combat_phrase( "#say I will swallow your soul!" );
    add_combat_phrase( "#say You will feed the old ones!" );
    add_combat_phrase( "#say Finish me, I crave the embrace!" );
    add_combat_phrase( "#say Who will lock you in the cellar..." );
    add_combat_phrase( "#say My pain has no meaning!" );
    
    set_avoid_props( ({ NoWanderRoomP }) );
    set_move_rate( 20 );
    set_move_chance( 85 );
    
    set_heal_rate( 15 );
    set_heal_amount( 20 );
    
    set_race( mrace );
    
    set_stat( "str", 120 + strmod );
    set_stat( "int", 140 + intmod );
    set_stat( "wil", 50 + wilmod );
    set_stat( "con", 250 );
    set_stat( "dex", 75 );
    set_stat( "chr", 3 );
    
    add_special_attack( "evil_limb", THISO, 8 );    
}

int evil_limb( object vic, object att )
{
    if( legs > 20 || arms > 20 )
      return 0;
    int mondex = THISO->query_stat( "dex" ); 
    int monstr = THISO->query_stat( "str" );
    string limb, attack, limbarm, limbleg;
    string newlong = "You can't tell whether this was a man or a woman. "
      "It has long since passed beyond gender and "
      "into the inhuman. Scabs fester, crack, and "
      "bleed all over it's skin. It's eyes are gone "
      "the sockets stained with blood. It appears that "
      "the wounds were self inflicted.";
    
    switch( random( 100 ) ){
    case 0..27 :  limb = "arm";
                  attack = "heal";
                  arms = arms + 1;
                  healspecial = healspecial + 5;
      add_special_attack( "heal", THISO, healspecial );              
                  set_stat( "str", monstr + 3 );
                  break;   
    case 28..99 : limb = "leg";
                  attack = "accelerate";
                  legs = legs + 1;
                  accelspecial = accelspecial + 5;
      add_special_attack( "accel", THISO, accelspecial );
                  set_stat( "dex", mondex + 5 );
                  break;
    }
    
    command( "scream" );
    command( "say Change!!! It is inevitable!!!" );
      
    ansi_tell_room( ENV( THISO ), sprintf( "There is a "
      "horrible sound as the researcher's bones "
      "snap, and it's tissue ruptures. An extra %s "
      "grows from it's body!", limb ), RED, ({ }) );
    
    set_long( sprintf( "%s It has %s arms, and %s legs.",
      newlong, to_string( arms ), to_string( legs ) ) );
    
    if( accelspecial > 25 )
      accelspecial = 26;

    if( healspecial > 20 )
      healspecial = 21;
    
    return 1;
}

int heal( object vic, object att )
{
    command( "cackle" );
    ansi_tell_room( ENV( THISO ), "The researcher's arms flail "
      "wildly. It's hands rip flesh from the uninjured parts of "
      "it's body. It shoves the bloody flesh into it's wounds, "
      "where it solidifies.", RED, ({ }) );
    THISO->add_hp( query_stat( "str" ) - random( 10 ) );
    return 1;
}

int accel( object vic, object att )
{
    if( THISO->query_skill( "dodge" ) >= 150 )
      return 0;
    
    dodge = dodge + 5;
    
    command( "roar" );
    
    ansi_tell_room( ENV( THISO ), "The researcher skitters "
      "around quickly", RED, ({ vic }) );
    ansi_tell( vic, "The researcher skitters "
      "around quickly, it's multiple legs aiding in "
      "it's speed. It's very hard to hit!", RED );
    
    set_skill( "dodge", dodge );
    
    return 1;
}    
