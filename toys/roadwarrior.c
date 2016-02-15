object me;
int x;
string *shit;
sh_init( object user )
{
    me = user;
    shadow( me, 1 );
    shit = ({ "*Burns tons of gas in order to capture slightly larger amount of gas*",
      "wakes up* yawn.... Another day of work ahead of me. Welp, better get up. "
      "*dons leather bondage gear* *applies face paint just so. ok, lets go guys, we've got victims to terrorize!*", 
      "Round and round, attack, "
      "attack, like angry ants mad for the smell of gazoline.", "I don't care what I wear on "
      "today's intertribal raid, as long as it's homoerotic as fuck.", "'Wez? Have you seen my gimp mask? "
      "'It's out for dry cleaning Lord Humungus' *sighs* *dons hockey mask* "
      "'Find something other than a Sports Authority to raid this time. I'd kill for an Old Navy.'",
      "*Falls off speeding car trying to rob someone*", "* has committed to memory the time it takes to cut through various "
      "objects with a hack-saw.", "oi'l droive tha tanka", "*uses a word no Australian would use, "
      "says it in a broad Aussie accent*" });
    call_out( "say_shit", random( 28800 ) );
}

void say_shit()
{
    string saying = shit[random( sizeof( shit ) )];
    command( sprintf( "channel gossip %s", saying ), me );
    call_out( "say_shit", random( 28800 ) );
}
    

kill_roadwarrior_shad()
{
   remove_shadow( THISO );
   destruct( THISO );
}
