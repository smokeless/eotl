inherit BaseCommand;

void extra_create()
{
    set( "name", "thankin bout stuff" );
    set( "guild", "hillwizard" );
    set( "class", "Other" );
    set( "no_combat", 1 );
    set( "no_rest", -1 );
    set( "private", 1 );
    set( "usage", "automatic" );
    set( "help",
         "Skill :        Thankin' 'bout stuff\n"
         "Type  :        Noncombat\n"
         "Usage :        Automatic while resting.\n"
         "Requirements : Must be at rest\n\n"
      "    Hillwizards aren't usually all that bright, but "
      "they like to take their time and think about stuff. "
      "Most of that thinking is about bodily functions, or "
      "cows, or sometimes the bodily functions of cows. "
      "There's just so much going on in the world, it can't "
      "hurt to just sit down and consider why a cow pissed in "
      "your cheerios."
      "\n"
      "\n"
      "This skill allows the hillwizard to recover mana quickly, "
      "at higher levels sometimes even a freedom point!\n"      );
}
