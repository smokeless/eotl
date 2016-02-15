#include <city.h>

inherit MonsterAsk;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create() 
{
    set( "guard", 1 );
    //set up race and name
    string race, name, raceFile;
    switch( random( 4 ) )
    {
        case 0 : race = "dwarf"; name = "dwarven guard"; raceFile = "/obj/races/dwarf";
        break;
        case 1 : race = "human"; name = "human guard"; raceFile = "/obj/races/human";        
        break;
        case 2 : race = "pixie"; name = "pixie guard"; raceFile = "/obj/races/pixie";        
        break;
        case 3 : race = "draconian"; name = "draconian guard"; raceFile = "/obj/races/draconian";
        break;
    }
    set_race( raceFile );
    
    set_name( sprintf( "%s", CAP(name) ) );
    
    int genderSwitch = random( 2 );
    if( genderSwitch )
      set_gender( "female" );
    
    add_alias( race );
    add_alias( "guard" );
    add_alias( sprintf( "a %s", name ) );
    
    set_short( sprintf( "a %s", name ) );
    
    //Set up align
    int align = random( 4000 );
    if( random(2))
      align = -align;
    set_alignment( align );
    
    //Stat em up.
    set_stat( "str" , random( 500 ) + 200 );
    set_stat( "con" , random( 500 ) +200 );
    set_stat( "int" , 100 );
    set_stat( "wil" , 300 );
    set_stat( "dex" , random(300) );
    
    set_proficiency( "hands", 75 );
    set_proficiency( "heavy club", 70 );
    
    set_skill( "dodge", 65 );
    
    set_natural_ac( 5 );
    
    set_long( sprintf( "This is your run of the mill Chooli city guard. "
      "Just an average individual who picked up a suit of armor and "
      "decided to enforce the law. Of course that enforcement is really "
      "dependant on %s mood. Also on whether or not %s likes you. "
      "Though generally these guards have a kill outsiders first "
      "kind of attitude that really keeps Chooli free of "
      "hobos and heroes alike.", possessive(THISO), 
      subjective( THISO ) ) );
    
    
    set_chat_rate( 30 );
    set_chat_chance( 60 );
    
    add_phrase( "#say Just another shift." );
    add_phrase( "#say I'm tired of all this refugee paperwork." );
    add_phrase( "#cough" );
    add_phrase( "#peer" );
    add_phrase( "#say Move it along." );
    add_phrase( "@scan" );
    
    ask_me_about( "shift", "#say look at this idiot. "
      "Never had a real job. Asking me about a shift.");
      
    ask_me_about( "refugee", "#say Yeh, they're everywhere. "
      "Guess they want in for the safety we provide. "
      "Probably tired of Eternal and its severe "
      "murder hobo problem." );
    
    move_object( clone_object( "/obj/armor/armor/suits/plate_full" ), THISO );
    move_object( clone_object( "/obj/weapon/weapons/blunt/hmb_mace" ), THISO );
    command( "equip", THISO );
    
    add_special_attack( "kungfu", THISO, 10 );
}

void scan()
{
    object *x = filter( all_inventory( ENV(THISO)), #'living );
    object victim = x[random(sizeof(x))];
    command( "say Hey! You there, what are you trying to hide?", THISO );
    
    if( is_player( victim ) )
    {
      tell_player( victim, sprintf("%s scrutinizes you.", THISO->query_name() ));
      return;
    }
    if( victim->query("guard"))
        return;
    tell_room( ENV( THISO ), sprintf( "%s goes over to %s and shoves them "
      "to the ground.", THISO->query_name(), victim->query_name() ), ({}));
    return;
}

int kungfu( object victim, object attacker )
{
    int dam = random( THISO->query_max_damage() );
    string vil = victim->query_name();
    string hitType = "punches";
    if( random(2) )
        hitType = "kicks";
    
    ansi_tell_room( ENV( attacker ), sprintf(
      "The guard executes a series of crazy looking "
      "kung fu moves before landing a solid blow on %s.",
      vil), HIR, ({ victim, attacker}) );
    
    ansi_tell( victim, sprintf( "Whoa this guard is doing some "
      "crazy kung fu moves! %s %s you hard.", 
      CAP(subjective(THISO)), hitType ), HIR );
    
    victim->take_damage( dam, 0, "blunt", attacker );
    
    return 1;  
}
