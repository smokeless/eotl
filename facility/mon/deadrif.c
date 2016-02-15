#include <facility.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_name( "the ghost of Rifrad" );
    add_alias( "rifrad" );
    add_alias( "ghost" );
    add_alias( "doctor" );
    add_alias( "ghost of rifrad" );
    
    set_short( "the ghost of Rifrad" );
    set_ansi_short( sprintf( "%sthe ghost of Rifrad", HIK ) );
    
    set_long( "Where there was once a being, there is now a fluctuating "
      "darkness. A cold ghastly presence. All that remains of Rifrad "
      "is his incorporal form." );   
    
    set_gender( "male" );
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str" , 200 );
    set_stat( "con" , 200 );
    set_stat( "wil" , 500 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 75 );
    set_skill( "dodge", 65 );
    
    set_type( "psychic" );
    
    set( NoStunP, 1 );
    set( UndeadP, 1 );
    
    set_aggressive( 1 );
    
    set_natural_ac( 3 );
    
    call_out( "hello", 1 );
    
    add_special_attack( "soulwell", THISO, 8 );
}    

int soulwell( object vic, object att )
{
    command( "say To me fiends! I crave your sustenence!" );
    
    ansi_tell_room( ENV( att ), "A black mist comprised of "
      "lost souls begins to rise from the ground. Rifrad breathes "
      "deeply.", HIK );
    
    att->add_hp( 30 + random( 30 ) );
    
    return 1;
}

//Is called when rifrad dies, from Rifrad himself.
void hello()
{
    string *says = ({ "I live... AGAIN! I cannot die!",
      "Death is merely a flesh wound.", "You may have destroyed my "
      "physical form, but I live on!" }) ;
    command( sprintf( "say %s", says[ random( sizeof( says ) ) ]  ) );
}

int DeathSequence( object killer, string cause, int nocorpse )
{
    if( killer->query_misc_proficiency( "dark touch" ) == 0 )
    {
      ansi_tell_room( ENV( THISO ), "A black mist rises from the ground. "
        "The room chills.\n", HIK, ({ }) );
      
      ansi_tell( killer, "You inhale some of the mist. You feel "
        "refreshed, and different.\n", BLU );
      
      killer->set_real_misc_proficiency_value( "dark touch", 1 );
      
      killer->add_hp( 20 + random( 10 ) );
      
      return( ::DeathSequence( killer, cause, 1 ) );
    }
    else
    {
      ansi_tell_room( ENV( THISO ), "A black mist rises from the ground. "
        "The room chills.\n", HIK, ({ }) );
      
      ansi_tell( killer, "You inhale some of the mist. You feel refreshed.\n", 
        BLU );
      
      killer->add_hp( 20 + random( 10 ) );
      
      return( ::DeathSequence( killer, cause, 1 ) );
    }
}
