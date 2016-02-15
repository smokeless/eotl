mapping adventurer_desc,paladin_desc,black_dragon_desc;
int a;

create()
{
    black_dragon_desc = ([
      "a young black dragon":
      ({
        ({"young black dragon","young dragon","black dragon","dragon"}),
        "This is a young black dragon.  Though its skin is black as the sky "
        "it is obvious that this dragon is barely out of its youth.  Its "
        "size and its horns make the dragon about fifty years old but even "
        "so, it is imposing.  Slime and sticky film hang from the beasts "
        "great wings and saliva drips from its huge mouth.",
        9,
      }),
      "a foul tempered black dragon":
      ({
        ({"foul tempered black dragon","foul black dragon","foul dragon",
          "dragon","tempered black dragon","foul dragon"}), 
        "This is a foul black dragon that looks vicious and cruel.  Saliva "
        "drips from its gaping jaws to the ground as it stares at you.  The "
        "great wings spread for a moment as if it is going to take off, then "
        "they settle back in against its body.  Its midnight black scales "
        "look hard as iron, impenatrable with normal weapons.",
        12    
      }),
      "a malevolent black dragon":
      ({
        ({"malevolent black dragon","malevolent dragon","black dragon",
          "dragon"}),
        "This is a malevolent dragon and he is bad tempered and mean.  The "
        "great beast is probably over a hundred and fifty years old and is "
        "quite large.  Its dark black scales are so completely compacted "
        "together that no normal weapon could hurt this beast.  But that is "
        "probably the least of your worries.  This creature looks as if it "
        "could rip you apart.",
        15
      }),
      "a sinister black dragon":
      ({
        ({"sinister black dragon","sinister dragon","black dragon",
          "dragon"}),
        "This is a sinister dragon with evil written on its horrible black "
        "face.  Its slit-like eyes stare at you with venom and anger.  It "
        "looks as if it might attack at any moment.  Probably close to "
        "three hundred years old the dragon is immense and would be able "
        "to swallow you without chewing.  Its wings are huge and dark, "
        "and when it momentarily spreads them you see the full deadly "
        "being of this immense beast.",
        17
      }),
      "a monstrous black dragon":
      ({
        ({"monstrous black dragon","monstrous dragon","black dragon",
          "dragon"}),
        "This is a monstrous black dragon that is probably one of the "
        "oldest in existence.  Probably three or four hundred years old "
        "the scales are not quite as dark as they used to be but don't "
        "let that fool you.  The creature is immense and would kill you "
        "in a moments notice.  A deadly creature, be careful before "
        "approaching it.  It would more than likely kill you before "
        "you managed to speak a word.",
        20
      })
    ]);
    paladin_desc = ([
      "a dwarven paladin":
        ({
          ({"dwarf","dwarven paladin","adventurer","dwarven"}),
          "Renowed for their fighting prowess the dwarven paladins of "
          "Kolg have long been feared by those of evil.  Fierce and "
          "totally dedicated to their God, these paladins whether male "
          "or female are a force to be reckoned with.",
          ({160,140,170,180,130,130,35}),
          ({"hammer","short_sword"}),
          ({"light club","light sword"}),
        }),
      "a paladin":
        ({
          ({"human","paladin"}),
          "One of the most feared and beloved warriors the paladin has "
          "been the source of envy, fear, love and hate.  Hated by "
          "those who would seek to do evil and loved by those who stand "
          "for justice and righteousness, these men and women stand "
          "by the weak and protect the innocent.  Beware crossing on of "
          "these warriors of god for they will not hesitate to kill you "
          "if you do.",
          ({150,150,150,150,150,150,35}),
          ({"hammer","long_sword"}),
          ({"light club","light sword"}),
        })
    ]);
    adventurer_desc = ([
      "a dwarven adventurer":
        ({
          ({"dwarf","dwarven adventurer","adventurer","dwarven"}),
          "A dwarven adventurer that has probably encountered many "
          "interesting things in the wild.  He is short, perhaps four "
          "feet tall but very stocky.  His arms, legs and chest are "
          "solid muscle and he looks like he would be tough in a fight.",
          ({110,90,120,130,80,80,30}),
          ({"hammer","short_sword"}),
          ({"light club","light sword"}),
        }),
      "an adventurer":
        ({
          ({"human","human adventurer","adventurer"}),
          "Just another adventurer walking around on his way to some "
          "place or another.  His walk is strong and he looks like he "
          "has seen more than one battle.  His well-muscled arms have "
          "more than one scar and his face looks battle hardened.",
          ({100,100,100,100,100,100,35}),
          ({"hammer","short_sword","long_sword","voulge","dagger"}),
          ({"light club","light sword","light sword","light polearm",
            "knife"}),
        }),
      "an elven adventurer":
        ({ 
          ({"elf","elven adventurer","adventurer","elven"}),
          "This is a relatively young elf about ninety years of age.  "
          "Well muscled for an elf, he glides as he walks one of the "
          "trademarks of their race.  His almond shaped green eyes "
          "radiate a confidence that can only be gained from years "
          "of experience fighting off orcs or destroying evil where "
          "he finds it.",
          ({80,180,90,70,120,110,50}),
          ({"short_sword","long_sword","dagger"}),
          ({"light sword","light sword","knife"}),
        }),
      "a kender adventurer":
        ({
          ({"kender","kender adventurer","adventurer"}),
          "This is a kender and you know what that means.  Watch your "
          "coin purse because these little guys will steal things "
          "without even realizing it.  Their hands are just so quick "
          "that they move like a blur; a good attribute for a kender "
          "such as this.  For out in the wild someone of such small "
          "size has to be quick to avoid being prey to something big "
          "and nasty.",
          ({80,110,90,90,120,110,55}),
          ({"short_sword","dagger"}),
          ({"light sword","knife"}),
        }),
      "a teddy bear adventurer":
        ({
          ({"teddy bear","teddy bear adventurer","adventurer",
            "teddy","teddy adventurer","bear"}),
          "This is a teddy bear that has decided to spend his life "
          "out adventuring instead of staying at home being a plaything "
          "for a small child.  Fortunately his fur will keep him warm "
          "and he doesn't need much clothing.  It can get cold out in the "
          "wild and who needs all that clothing when you could have an "
          "extra sword in your pack?",
          ({50,110,90,110,150,250,45}),
          ({"long_sword","short_sword"}),
          ({"light sword","light sword"}),
        }),
      "a parthan adventurer":
        ({
          ({"parthan","parthan adventurer","adventurer"}),
          "This is a parthan adventurer.  Basically a large cat-like "
          "humanoid this race is bred for battle.  Tall and muscular with "
          "an orange coat, he looks almost noble.  A bit odd for a parthan "
          "to be out alone, as most of them keep to their own lairs and "
          "communities.  Perhaps he feels he was meant for more than "
          "that.",
          ({140,80,70,120,120,70,40}),
          ({"long_sword","short_sword","voulge"}),
          ({"light sword","light sword","light polearm"}),
        }),
      "a gnome adventurer":
        ({
          ({"gnome","gnome adventurer","adventurer"}),
          "Small and quick gnomes make for good adventurers.  Though most "
          "of them tend to become illusionists or priests some venture "
          "out into the world to find adventurer.  Smaller than kenders "
          "and just as quick they can cut your throat and be gone before "
          "you even saw them.  Because of their small size people tend "
          "to underestimate them, but be wary, to do that could mean your "
          "death.",
          ({90,110,120,120,80,80,60}),
          ({"short_sword","dagger"}),
          ({"light sword","knife"}),
        })  
    ]);
}

string GetShort(string montype)
{
    string *keys;
    switch(montype)
    {
      case "adventurer" :
        keys = m_indices(adventurer_desc);
        return(keys[random(sizeof(keys))]);
      break;
      case "paladin" :
        keys = m_indices(paladin_desc);
        return(keys[random(sizeof(keys))]);
      break;
      case "black dragon" :
        keys = m_indices(black_dragon_desc);
        return(keys[random(sizeof(keys))]);
      break;

    }
}
string *GetAlias(string montype,string key)
{
    switch(montype)
    {
      case "adventurer" :
        return(adventurer_desc[key][0]);
      break;
      case "paladin" :
        return(paladin_desc[key][0]);
      break;
      case "black dragon" :
        return(black_dragon_desc[key][0]);
      break;
    }
}

string GetRace(string montype,string key)
{
    switch(montype)
    {
      case "adventurer" :
        return(adventurer_desc[key][0][0]);
      break;
      case "paladin" :
        return(paladin_desc[key][0][0]);
      break;
    }
}

string GetLong(string montype,string key)
{
    switch(montype)
    {
      case "adventurer" :
        return(adventurer_desc[key][1]);
      break;
      case "paladin" :
        return(paladin_desc[key][1]);
      break;
      case "black dragon" :
        return(black_dragon_desc[key][1]);
      break;
    }
}

int GetLvl(string montype,string key)
{
    switch(montype)
    {
      case "black dragon" :
        return(black_dragon_desc[key][2]);
      break;
    }
}
int *GetStats(string montype,string key)
{
    switch(montype)
    {
      case "adventurer" :
        return(adventurer_desc[key][2]);
      break;
      case "paladin" :
        return(paladin_desc[key][2]);
      break;
    }
}

string GetWeapon(string montype,string key)
{
    string *weapons,weapon;

    switch(montype)
    {
      case "adventurer" :
        weapons = adventurer_desc[key][3];
        a = random(sizeof(weapons));
        weapon = weapons[a];
        return(weapon);
      break;
      case "paladin" :
        weapons = paladin_desc[key][3];
        a = random(sizeof(weapons));
        weapon = weapons[a];
        return(weapon);
      break;
    }
}

string GetProf(string montype,string key)
{
    switch(montype)
    {
      case "adventurer" :
        return(adventurer_desc[key][4][a]);
      break;
      case "paladin" :
        return(paladin_desc[key][4][a]);
      break;

    }
}
