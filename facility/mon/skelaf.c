#include <facility.h>

inherit MonsterAsk;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create() 
{
    object stuff;
    
    set_name( "Skelaf" );
    
    add_alias( "skelaf" );
    add_alias( "drow" );
    add_alias( "inquisitor" );
    add_alias( "skelaf the inquisitor" );
    
    set_short( "Skelaf the Inquisitor" );
    set_ansi_short( HIB "Skelaf the Inquisitor" );
    
    set_long( "Short well kept black hair gives away to "
      "skin riddled with spidery vericose veins. His "
      "bolbous nose sets on an otherwise well proportioned "
      "face. His eyes are bleak and grey, his lips "
      "are drawn tight against his face evealing yellowing "
      "dull teeth. His body shakes slightly as he moves."
    );
    
    set_gender( "male" );
    set_race( "drow_elf" );
    
    set_guild( "spellcaster" );
    set_specialization( "necromancer" );
    
    set_alignment( EVIL_AL );
    
    set_stat( "str" , 100 );
    set_stat( "con" , 200 );
    set_stat( "int" , 450 );
    set_stat( "wil" , 300 );
    set_stat( "dex" , 300 );
    
    set_proficiency( "hands", 75 );
    
    set_skill( "dodge", 65 );
    set_skill( "magic missile", 50 );
    set_skill( "spell casting", 45 );
    set_skill( "Darktongue", 25 );
    set_skill( "rebirth", 50 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_max_damage( 30 );
    set_chat_rate( 30 );
    set_chat_chance( 50 );
    
    add_phrase( "#mumble the old gods" );
    add_phrase( "#say I am tired of being oppressed!" );
    add_phrase( "#cackle" );
    add_phrase( "#say When will it stop!" );
    add_phrase( "#shudder" );
    add_phrase( "#cough" );
    
    listen_for( "explodes out of the well!", "Oh by all that is good! "
	  "The gods crave sustenance! If only someone would end it!"
	 );
    listen_for( "determined to find something.",
	  "That is not the solution, it will only make the thing stronger! "
	  "If only it were a solution. The only way is for someone to "
	  "go down there and take care of things!" 
    );
    
    ask_me_about( "facility", "#say Well, "
      "basically what we do here, is research "
      "of a pyschic nature. Nature of death, "
      "all that nonsense. All our work benefits "
      "the archives in Quardirrn." 
    );
    ask_me_about( "beast", "#say It waits below! "
      "If only someone would end it's existence! "
      "You will find it at the bottom of the well." 
    );
    ask_me_about( "quardirrn", "#say Ah, the "
      "homeland. Quardirrn has existed for "
      "centuries and will continue to exist "
      "for many more. It is very difficult to "
      "gain entry for those not of the Drow race." 
    );
    ask_me_about( "oppressed", "#say They stuck me "
	  "down here, with no regard for anything! "
	  "They force me to do horrible things to... to... "
	  "Sacrifice to the old gods."
    );
    ask_me_about( "gods", "#say There are many gods. "
	  "At the bottom of this pit there is only one. "
	  "It must be stopped! If only someone would "
	  "leap in! If someone would take charge!"
    );
    
    move_object( clone_object( FARMOR "shoes" ), THISO );
    move_object( clone_object( FARMOR "suit" ), THISO );
    command( "equip" );
    
    add_special_attack( "pain", THISO, 10 );
}

int pain( object victim, object attacker )
{
    int dam = 100 + random( 24 );
    string vil = victim->query_real_name();
    
    ansi_tell_room( ENV( attacker ), sprintf(
      "Skelaf cocks his head to the right, "
      "there is an intangible charge in the air. "
      "%s begins to bleed from %s eyes.\n", vil,
      subjective( victim ) ), HIR, 
      ({ victim, attacker}) );
    
    ansi_tell( victim, "Your eyes begin to bleed, " 
      "it feels like everything "
      "is against you.\n", HIR );
    
    victim->take_damage( dam, 0, "psychic", attacker );
    
    return 1;  
}

void start_greet( object vag ) 
{
    call_out("greet", 3, vag);
}

void greet()
{
    command( "say Thank all that is good that you are here "
	  "I've been waiting for someone to come and put a stop "
	  "to this. They've imprisoned me here! A brave adventurer "
	  "someone who can combat the beast in the pit! Just "
	  "go ahead and leap in the pit! End this all!", THISO );
}

start_panic()
{
    command( "say The beast! It hungers! Won't someone "
      "end this misery!", THISO );
}
