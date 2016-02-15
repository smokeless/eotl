inherit MonsterCode;
inherit MonsterTalk;
#define SHORT "Pamela Anderson is here, playing Twister"

void extra_create()
{
    set_name("pamela");
    add_alias("pam");
    set_short(SHORT);
    set("sdesc", SHORT);
    set_long("DOH!  What you are looking at probably has to "
          "be the finest specimen of human anatomy ever "
           "created.  Everything is in the right proportion "
           "and she knows how to use it.  The fact that she is "
           "naked almost drives you crazy, and you feel a "
           "sudden urge to stare at her.\n");
    set_race("human");
    set_gender("female");
    set_stat("str",120);
    set_stat("int",20);
    set_stat("wil",100);
    set_stat("con",250);
    set_stat("dex",100);
    set_stat("chr",300);
    set_proficiency("hands", 10 + random(5));
    set_aggressive(0);
    set_alignment("neutral");
    set_natural_ac(2);            //Silicone implants
    set(MonsterP, 1);
    set_chat_chance(95);
    set_chat_rate(random(10)+60);
    add_phrase("Pamela giggles.\n");
    add_phrase("Pamela wonders where the beach is.\n");
    add_phrase("Pamela looks at you.\n");
}
extra_init()
{
    add_action("stare","stare");
}
int stare(string wow)
{
    if(wow == "at pamela" || wow == "at pamela's breasts" ||
       wow == "pamela" || wow == "pam" || wow == "at pam")
    {
       write("You just can't stand it anymore. You strip down to "
                "nothing and join in!\n");
       tell_room(ENV(THISP),PNAME+" stares at Pam and "
                "suddenly decides to join in.\n",({THISP}));
       command("unequip", THISP);
       command("moan", THISP);
       return 1;
    }
    else
    {
       write("What do you want to stare at?\n");
        return 1;
    }
}

