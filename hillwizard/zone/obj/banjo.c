inherit InstrumentCode;

void extra_create()
{
    set( "id", ({ "banjo", "a banjo", "a beat up banjo",
      "an old banjo", "old banjo", "beat up banjo",
      "an old beat up banjo" }) );
    set( "short", "an old beat up banjo" );
    set( "long",
      "Ahhhhh yes, the banjo.  An instrument as hard to play as it "
      "is horrible to hear.  Twangy and unlistenable, this banjo is "
      "exactly what you'd expect it to be.  It also is quite beat up, "
      "and has surely seen decades of use."
    );
    set( "proficiency", "string" );
    set( "weight", 20 );
    set( "value", 100 );
}

query_skill_bonus( string str )
{
   if( str == "comfort" )
     return -2;
   if( str == "deafen" || str == "panhandle" )
     return 5;
}

query_stat_bonus( string str )
{
   if( str == "chr" )
      return -5;
}
