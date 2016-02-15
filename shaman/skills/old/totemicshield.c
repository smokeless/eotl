/*
Totemic shield code for shaman guild.
This skill interacts with the shamans
shadow. Causing them to do damage or 
healing with their shields.

Socialism 2012
*/

inherit SkillCode;

void extra_create()
{
    set( "name", "totemic shield" );
    set( "guild", "shaman" );
    set( "class", "other" );
    set( "help",
      "Skill : Totemic Shield\n"
      "Usage : Inherent\n\n"
      "A shaman is most at home when guarded by the spirits. This skill "
      "allows a shaman to channel the spirits through a shield. The "
      "more skilled a shaman is in this area the more helpful the spirits "
      "will be."
      );
    set( "private", 1);
}
