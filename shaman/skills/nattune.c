inherit BaseCommand;
 
void extra_create()
{
    set( "name", "natural attunement" );
    set( "help",
        "Skill  : Natural Attunement\n"
        "Usage: Inherant\n"
        "\n"    
        "While many peoples focus on aggression, "
        "shaman focus on attunement with nature. "
        "Nature can be a cruel mistress, via "
        "attunement a shaman is capable of "
        "some degree of control over nature herself. "
        "The better attuned a shaman is, the less likely "
        "their control is to go awry." );
    set( "usage", "automatic" );
    set( "class", "universal" );
    set( "guild", "shaman"    );
    set( "private", 1 );
}
