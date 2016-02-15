inherit NewThingCode;

void extra_create()
{
    set( "id", ({ "diabetes" }) );
    set( "short", "diabetes");
    set( "long", "This is diabetes.  You do not want diabetes." );
    set( "value", 0 );
    set( "weight", 0 );
    set( "gettable", 1 );
    set( "droppable", 1 );
    set( "sellable", 0 );
    set( NoStoreP, 1 );
    set_limit( 1 );
}

void move_signal(object oldenv, object mover)
{
    if( living( oldenv ) )
    {
      oldenv->remove_bonus_object( THISO ); 
    }

    if( living( ENV( THISO ) ) )
    {
      ENV( THISO )->add_bonus_object( THISO );
    }
}

query_skill_bonus(string skill)
{ 
    if( skill == "scant" || skill == "cant" ) return 0;
    else return -5; 
}

int query_resist_bonus( string resist )
{ return -5; }

query_proficiency_bonus( string prof )
{ return -5; }

query_stat_bonus( string stat )
{ return -25; }
