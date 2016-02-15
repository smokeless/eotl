inherit MonsterCode;
inherit MonsterMove;
inherit QuestCode;

#define TIME 6
#define QUIET_IDLE TIME*6
#define MAX_IDLE 6*QUIET_IDLE
#define EXP_BONUS 100000
#define SAY_COMMAND "/secure/player/commands/say"

void extra_create();
string short( object looker );
void talk();
status valid_victim(object target);
void get_new_victim();
void do_say(string words);
void congrats();

object victim;
string *speech;
int speech_index;

void
extra_create()
{
    set_limit(1); //just in case

    speech =
    ({
      "Pleased to meet you, %s.",
      "Name's Francis Pumphandle, but everyone calls me Pip.",
      "",
      "Cheese balls are one of my all-time favorite foods.",
      "I always seem to meet the most interesting people when I'm around them, too.",
      "In fact, cheese balls bring to mind the time I met Bob Barker.",
      "",
      "Bob Barker.  Star of the most popular morning game show.",
      "He's an emcee, a host, and a celebrity all rolled into one.",
      "Anyway, eight months ago --",
      "-- it was Tuesday the 17th, I believe --",
      "-- or it might have been the 18th ...",
      "...  no, no, it was definitely the 17th, because it was precisely one week after my aunt Lucretia's birthday, which is the 10th.",
      "Aunt Lucretia's quite a woman.  Loves to cook.",
      "She prepares a fabulous war shu a.  That's a Chinese duck dish.",
      "I love Chinese food.",
      "I once went to a party where they served Chinese food and cheese balls.",
      "Now that was a Catch-22 situation.",
      "Catch-22 was a movie, you know.",
      "It was long, very long.",
      "They say the book was better, but it was a novel and I never finish reading those things.",
      "",
      "Of course, a lot of people don't read much nowadays.  They watch television.",
      "I caught a program on PBS last night.  A very good show on chimpanzees in the media.",
      "They had a clip of J. Fred Muggs, the chimp from the TODAY show.",
      "But it was Fred's chimpanzee girlfriend that had me stumped.",
      "I couldn't remember her name, so I looked it up.  Her name was Phoebe B. Beebe.",
      "",
      "Anyway, as I was saying, eight months ago, Tuesday the 17th, I went downtown on a nice, relaxing stroll.",
      "I love to relax.",
      "In fact, relaxing is a pastime of mine.",
      "Some people play golf.",
      "Others like tennis, horseshoes, bridge, canasta, and other such fancy hobbies.",
      "",
      "Now, another hobby enjoyed by many is knitting.",
      "My grandmother was a great knitter.",
      "Knitted this sweater I'm wearing.  It's red, which is not my favorite color.",
      "I prefer mauve or mustard yellow.",
      "Now, don't get me wrong: red is okay for ties and suspenders, but with sweaters I prefer more neutral colors.",
      "",
      "But when I'm relaxing, I don't care what I wear: long pants, Bermuda shorts, T-shirts, or formal attire.",
      "You name it, anything goes.",
      "Now, on the 17th, during my relaxing stroll, I recall wearing my herringbone jacket, my Laughlin, Nevada, souvenir tie, and my charcoal gray slacks.",
      "Or was it the navy slacks?",
      "Oh, I suppose it doesn't really matter.",
      "What matters is comfort.",
      "You know, I love comfort.",
      "It goes along with that pastime of mine, relaxing.",
      "Now, for me, there is nothing more relaxing than a nice leisurely stroll, like the one I took eight months ago on the 17th.",
      "It was a bright, sunny day, which of course is the optimum condition for relaxed strolling.",
      "And as I walked along, I found myself humming a haunting melody.",
      "I kept humming and humming and humming and humming.  I couldn't get the tune out of my head.",
      "",
      "I racked my brains to come up with the title, but to no avail.",
      "You see, I'm not terribly musical.",
      "And yet, I'd always wanted to play an instrument and be like my musical hero, Leo Sayer",
      "",
      "But who can compete with Leo?  I think I was just scared that I'd fail.",
      "",
      "Well, I decided right then and there to go buy a musical instrument.",
      "So on the particular Tuesday the 17th to which I was referring, I went down to the Sixth Street Music Emporium to buy a new tambourine, a terribly soothing instrument, contrary to popular opinion.",
      "And as I was strolling along, I detected a wonderful scent in the morning air.",
      "What could it be, I asked myself.",
      "",
      "",
      "",
      "So I went toward that marvelous scent, distracted by its aroma from my musical mission.",
      "The odor was a mix of orchid flowers and bologna, which of course is one of the world's most under-appreciated luncheon meats.",
      "That and pimento loaf.",
      "I _love_ a good pimento loaf and mayo sandwich -- the more pimentos, the better.",
      "Why, just the mention of pimentos makes my taste buds stand up and say, \"Howdy.\"",
      "Now there's an interesting word: \"Howdy.\"",
      "Is it from \"How are you\" or maybe \"How you doing\"?",
      "\"Howdy\"'s one of those strange words that really has no origin.",
      "I like saying \"How do\" more than \"Howdy\" -- more formal, I think.",
      "Not too flowery.",
      "But the flowery aroma of that particular morning carried me on my fragrant quest.",
      "",
      "Now, the smell was actually less bologna and more orchid -- the beautiful flower found on the island state of Hawaii.",
      "Of course, I wasn't in Hawaii, so I needed to search out the location of the nearest orchid.",
      "So, I visited every florist shop in town.",
      "Well, to make a long story short, not a single flower shop in town had any orchids in stock, which seemed mighty curious to me.",
      "Now, as we all know, curiosity killed the cat, but since I'm not a feline, I wasn't too worried.",
      "Felines are funny creatures, don't you think?",
      "I had a cat once.",
      "It used its claws to tear my living room couch to shreds.",
      "It was a comfy couch, too.",
      "Had a sleep-away bed in it with a foam rubber mattress.",
      "Now, I bought the couch and the mattress at Levine's Department Store on Third Avenue, the very same afternoon of that relaxing stroll aforementioned.",
      "I also bought myself a lovely tambourine on that same shopping expedition.",
      "Anyway, I didn't want to pay extra for the delivery of the couch, so I decided to carry the couch home myself.",
      "It was quite cumbersome.",
      "And getting it through the store's revolving doors was a bit of a challenge.",
      "And just as I emerged onto the street, by accident I bumped into a well-dressed man with an orchid in his lapel.",
      "It was Bob Barker and he was eating a bologna and cheese balls sandwich.",
      "",
      "Well, it's been nice chatting with you.",
    });
    speech_index = 0;

    set_quest_name("cheese_balls");

    set_name("Pip");
    add_alias("pip");
    add_alias("francis");
    add_alias("pumphandle");
    add_alias("francis pumphandle");

    set_short("Pip, everyone's favorite party-goer");
    set_long("Pip is wearing a red sweater which his grandmother knitted for "
             "him.  You have a sinking feeling that he's going to tell "
            "you all about it.");

    set_race("human");

    set_toughness(30);
    set_move_rate(0);  //only moves when i tell it to
    set_move_chance(100); //always moves when i tell it to

    if(root())
      return;

    call_out("talk", TIME);
}

string
short( object looker )
{
    if(valid_victim(victim))
      return "Pip is here, completely engrossed in conversation with "
            + (looker != victim ? victim->query_name() || "nobody" : "you" );
    else
      return ::short( looker );
}

void
talk()
{
    if(find_call_out("talk") == -1)
      call_out("talk", TIME);

    if(!valid_victim(victim))
      return get_new_victim();

    if(ENV(victim) != ENV(THISO))
    return THISO->move_player("X", ENV(victim), 1);

    if(query_idle(victim) > QUIET_IDLE)
      return;

    do_say( speech[speech_index] );
    speech_index++;

    if(speech_index >= sizeof(speech))
      congrats();
}

void
get_new_victim()
{
    object *victims;
    int victims_index;

    victims = filter_array(all_inventory(ENV(THISO)), "valid_victim");

    if(sizeof(victims))
    {
      victims_index = random(sizeof(victims));
      victim = victims[victims_index];
      command( "hshake "+victim->query_name() );
      speech_index = 0;
    }
    else
    {
      move_monster();
    }
}

status
valid_victim(object target)
{
    return (objectp(target) &&
            interactive(target) &&
            !target->query_ghost() &&
            query_idle(target) <= MAX_IDLE &&
            !has_completed_quest(target));
}

void
do_say( string words )
{
    if(!stringp(words) || words == "")
      return;

    if(speech_index == 0)
      words = sprintf(words,victim->query_name());

    SAY_COMMAND->do_command(THISO, words);
}

void
congrats()
{
    if(!valid_victim(victim))
      return;

    if(!completed_quest(victim))
      victim->add_quest_exp(EXP_BONUS);
}
