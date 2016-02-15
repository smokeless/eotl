inherit BaseCommand;

void extra_create()
{
    set( "name", "blockade" );
    set( "guild", "hillwizard" );
    set( "class", "Other" );
    set( "no_combat", 1 );
    set( "no_rest", 1 );
    set( "private", 1 );
    set( "usage", "automatic" );
    set( "help",
         "Skill :        Blockade\n"
         "Type  :        Passive\n"
         "Usage :        Automatic in combat.\n"
      "    Oh shit sometimes blocking just doesn't generate "
      "enough FREEDOM POWER (tm). So skilled hillwizards learned "
      "how to dodge in such a way that they feel free (tm) all the "
      "time."
      "\n"
      "\n"
      "This skill allows a hillwizard to also generate "
      "freedom power with some successful dodges!\n"      );
}
