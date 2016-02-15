inherit "/obj/monster/ask_me";
inherit MonsterTalk;

void extra_create()

{

  set_name("battered Guard");
  set_name("guard");
  set_short("a tired Guard");
  set_long("This is one of the former defenders of Karst, wounded in the "+
  "fighting against the Dark. His eyes are bloodshot, and he looks as if he "+
  "has been awake for days.\n"+
"You may <ask guard about karst> and other things. Like "+
"what the hell you are about to get into..."
);
  set_race("human");
  set_toughness(10);
  set_max_damage(10);
  set_natural_ac(10);
  set_alignment("good");
  set_chat_rate(10);
   set_chat_chance(10);
  add_phrase("Guard says: The Dark Ones came from everywhere, it "+
  "seemed.\n");
  add_phrase("Guard says: Those damn monsters move like lightning.\n");
  add_phrase("Guard says: We did what we could... Karst is difficult "+
  "to defend.\n");
  add_phrase("Guard says: The whole Guard... most of my friends... "+
  "gone.\n");
  add_phrase("Guard says: Fear the black marble steps that lead into the "+
  "Nests of the Dark.\n");
  add_phrase("Guard says: Ingold the wizard tried to warn us... we "+
  "didn't listen.\n");
  add_phrase("Guard says: Ingold was captured in our foolish attempt "+
  "at burning the Nest under Karst out. Without him, it is just a matter "+
  "of time.\n");
  add_phrase("Guard says: Going alone into Karst is asking for death.\n");
  ask_me_about("dark ones","The Dark Ones are evil creatures... "+
  "they float on the air. You never see them alone... they are always "+
  "in groups. They have chitinous claws, cruel whip-like tails, and "+
  "huge mouths. They can change size when they are outside... it is "+
  "always better to fight them indoors. They usually fear light, hell, "+
  "even a bright moon will keep them away sometimes. The worst "+
  "thing about the Dark, if they don't kill you, is if they suck your "+
  "mind out. I hear they can.\n");
  ask_me_about("karst","Karst is the summer capital of the realm. "+
  "We all used to come here to escape the heat. The damn place is "+
  "about as easy to defend as floating rocks in water.  The Dark "+
  "rose from their Nest and decimated us. We didn't even have a "+
  "chance.\n");
   ask_me_about("nest","The Nest is the home of the Dark. There, "+
  "they have their huge underground caverns... many of them. "+
  "They also kidnap humans, for use in their 'herds.' The herds "+
  "are their source of food. We tried to go down "+
  "into the Nest, but we failed, and lost our best mage to them... "+
  "Ingold.\n");
  ask_me_about("ingold","Ingold Inglorian is the best swordsman "+
  "and wizard in this part of the world. He was our only real "+
  "defense against the Dark. He was captured in our mad attack "+
  "on the Dark. We must find a way to get him back.\n");
  }
