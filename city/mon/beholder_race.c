inherit "/obj/races/bodies/squid_body";

void setup_race()
{
    set_race_name( "Beholder" );
    set_hand_name( "tentacle" );
    set_stat( "str", 12, 85 );
    set_stat( "int", 12, 90 );
    set_stat( "wil", 11, 95 );
    set_stat( "con", 10, 100 );
    set_stat( "dex", 9,  100 );
    set_stat( "chr", 6,  120 );
}

int query_speed( object attacker ) {
  return (int)::query_speed(attacker) * 3 / 2;
}
