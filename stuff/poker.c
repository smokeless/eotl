/*
// Poker Machine -- Play Poker!
// By : Matt D. Robinson, Copyright 1991 (Regret/Yakker)
// SCCS Directives: %W% %G%
//
// Objective:  Create a machine for a pub or bar that allows you to
//             play poker.  This is single handed poker, with varying
//             odds.  The game reshuffles every 4 rounds.
//
// Bug Reports, Problems, or Questions?  Email me at:  yakker@sgi.com
//
// Version: 1.6
// Developed at: Cornucopia MUD (no longer around)
// Bug Fixes: Fixed straight problem
//            Corrected problem between full house and three of a kind
//            Readjusted playerob = 0 in three necessary places
//            Added information for jacks or better
//            Put together a payoff() function.
// Ansi display added 5/29/95 by Deborah Robinson.
*/

inherit ThingCode;

/*---------------------------------------------------------------------------*/
/* BEGIN Modifiable Defines                                                  */
/*---------------------------------------------------------------------------*/
/*
// These two defines are for where the file will be kept.  They MUST be
// made to where you would like to keep the file in your system.  Please
// change them to whatever they need to be.
//
// NOTE:  Do not put on a "/" at the end of the PATH.  It will be done
//        automatically.
*/
#define PATH "/zone/fantasy/genious/city/Gam"  /* The file's directory location. */
#define FILENAME "poker"  /* The name of the file (without .c) */

/*
// Some basic defines for the odds, to change at your leisure.
// NOTE:  These MUST be integer types, not real.
*/
#define NOTHING     0   /* The player won nothing, so he gets nothing */
#define TWOKIND     1   /* Two of a Kind, Jacks or Better             */
#define TWOPAIR     3   /* Two Pair                                   */
#define THREEKIND   4   /* Three of a Kind                            */
#define STRAIGHT    5   /* Normal Straight                            */
#define FLUSH       4   /* Normal Flush                               */
#define FULLHOUSE   6   /* Full House (2 Kind/3 Kind)                 */
#define FOURKIND    7   /* Four of a Kind                             */
#define STRFLUSH    20  /* A Straight and a Flush Combined            */
#define ROYALFLUSH  40  /* Royal Flush                                */

/*
// This define can be changed for those who want to make the deck more
// fluid.  The game will reshuffle every four turns, so that the deck
// is pretty clean and the person who likes to count cards has a chance.
// To make the game harder, just lower this number.
*/
#define SHUFFLECNT  4   /* The number of rounds between shuffles      */

/*
// This define is for those who wish to set the time between moves.  Here I
// set it to 60 seconds, so that if a player doesn't move within that time,
// the game will exit him out and allow for other players.
*/
#define MAX_TIME  60    /* Total time allotted to one player game     */

/*---------------------------------------------------------------------------*/
/* END Modifiable Defines                                                    */
/*---------------------------------------------------------------------------*/

/*
// Add some easier stated defines in the game.
*/
#define NUM_CARDS  5
#ifndef TRUE
#define TRUE       1
#endif
#ifndef FALSE
#define FALSE      0
#endif
#ifndef HEARTS
#define HEARTS     0
#endif
#ifndef DIAMONDS
#define DIAMONDS   1
#endif
#define SPADES     2
#define CLUBS      3

/*
// Defines for the values of each card for indexing purposes.
*/
#define TWO     0
#define THREE   1
#define FOUR    2
#define FIVE    3
#define SIX     4
#define SEVEN   5
#define EIGHT   6
#define NINE    7
#define TEN     8
#define JACK    9
#define QUEEN  10
#define KING   11
#define ACE    12

/*
// These are to make looking into the cards easier.
*/
#define SUIT  0
#define CARD  1

/*
// Define the deck, cards, and shuffle integer values (deck and cards
// will be converted into integer arrays).
*/
mixed *deck;
mixed *cards;
int    shuffle;
object playerob;

int payoff_count;
int winners;
int losers;
int payin_count;
int amt;

void
extra_create()
{
    int cnt;

    /*
    // Allocate space for the deck.
    */
    deck     = allocate(4);
    deck[0]  = allocate(13);
    deck[1]  = allocate(13);
    deck[2]  = allocate(13);
    deck[3]  = allocate(13);
    for (cnt = 0; cnt < 13; ++cnt)
    {
        deck[0][cnt] = 0; deck[1][cnt] = 0;
        deck[2][cnt] = 0; deck[3][cnt] = 0;
    }

    /*
    // Initialize the values for the cards.
    */
    cards    = allocate(2);
    cards[0] = allocate(NUM_CARDS);
    cards[1] = allocate(NUM_CARDS);
    for (cnt = 0; cnt < NUM_CARDS; ++cnt)
    {
        cards[0][cnt] = 0; cards[1][cnt] = 0;
    }

    /*
    // Set the initial shuffle value.
    */
    shuffle = 1;
    playerob = 0;
    set( "id", ({ "machine", "poker machine" }) );
    set( "short", "a poker machine (Usage: play poker [amount])" );
    set( "long",
      "This is a poker machine, designed to play single-handed " +
      "poker with someone who wants to play.  For instructions on " +
      "how to play, type in 'help poker'.  To play poker, type " +
      "in 'play poker <amount>'.  Standard bet is 10 coins."
    );
    set( "gettable", 0 );
    payoff_count = 0;
    winners      = 0;
    losers       = 0;
    payin_count  = 0;
}

/*
// clean_deck() -- Reset the values in the deck.
*/
void
clean_deck()
{
    int cnt;

    /*
    // Perform a simple for loop through the deck, and zero out the values.
    */
    for (cnt = 0; cnt < 13; ++cnt)
    {
        deck[0][cnt] = 0; deck[1][cnt] = 0;
        deck[2][cnt] = 0; deck[3][cnt] = 0;
    }
}

/*
// clean_cards() -- Clean up the hand given out to the user.
*/
void
clean_cards()
{
    int cnt;

    /*
    // Perform a simple for loop through the hand, and zero out the values.
    */
    for (cnt = 0; cnt < NUM_CARDS; ++cnt)
    {
        cards[0][cnt] = 0; cards[1][cnt] = 0;
    }
}

/*
// init() -- Allow some initial actions for the game.
*/
void
extra_init()
{
    /*
    // Make "play" and "help" valid actions in the game.
    */
    add_action("do_help",    "help");
    add_action("do_play",    "play");
    add_action("do_balance", "balance");
}

/*
// do_balance() -- Show the balance of the machine.
*/
int
do_balance()
{
    string out;

    if (IsWizard(THISP))
    {
        out  = "Poker Machine Status:\n";
        out += "---------------------\n";
        out += "Winners:  " + winners      + "\n";
        out += " Losers:  " + losers       + "\n";
        out += " Payoff:  " + payoff_count + " coins\n";
        out += "  Payin:  " + payin_count  + " coins\n";
        out += "---------------------\n";
        out += "Total Machine Balance:  " +
            (payoff_count - payin_count) + " coins\n";
        return( write( out ), 1 );
    }
    return 0;
}

/*
// do_help(str) -- Show some help information to a player.
*/
int
do_help(string str)
{
    string out;

    /*
    // If they just type in "help", or not "help poker", return.
    */
    if ((!str) || (str != "poker"))
    {
        return 0;
    }

    /*
    // Write out some basic information.
    */
    out = strformat(
        "The game of poker is somewhat complex, but fun for those who " +
        "know how to play the game.  You are dealt five cards from a " +
        "normal deck, all of which will be different.  A normal hand " +
        "might look like:\n");
    out += "     -------    -------    -------    -------    -------\n" +
           "     |6C   |    |5D   |    |9C   |    |KH   |    |KD   |\n" +
           "     |     |    |     |    |     |    |     |    |     |\n" +
           "     |   6C|    |   5D|    |   9C|    |   KH|    |   KD|\n" +
           "     -------    -------    -------    -------    -------\n" +
           "        1           2         3          4          5   \n" +
           "\n";
    out += strformat(
        "In this hand, you have a 6 of clubs, 5 of diamonds, 9 of clubs, " +
        "and a king of hearts and diamonds.  The objective here is to " +
        "gather cards and make winning sets.  You are given one chance to " +
        "give up your cards for different ones, and on the second turn, " +
        "those will make up your final hand.");
    out += "\n[Press \"m\" or <RETURN> for more, other to quit]:";
    write( out );

    /*
    // Continue with more help in another function.  Use input_to() to
    // allow you to continue.
    */
    input_to("help2");
    return 1;
}

/*
// help2(str) -- The second set of help information.
*/
int
help2(string str)
{
    string out;

    /*
    // Make sure they want more information.
    */
    if ((str != "") && (str != "m") && (str != "M")) return 1;

    /*
    // Write out some more basic information.
    */
    out  = "The winning sets are, along with their odds:\n\n";
    out += "---------------------------------------------------\n";
    out += "   Two of a Kind will return odds (" + TWOKIND    + "/1)";
    out += "(Jacks or better)\n";
    out += "        Two Pair will return odds (" + TWOPAIR    + "/1)\n";
    out += " Three of a Kind will return odds (" + THREEKIND  + "/1)\n";
    out += "        Straight will return odds (" + STRAIGHT   + "/1)\n";
    out += "           Flush will return odds (" + FLUSH      + "/1)\n";
    out += "      Full House will return odds (" + FULLHOUSE  + "/1)\n";
    out += "  Four of a Kind will return odds (" + FOURKIND   + "/1)\n";
    out += "  Straight Flush will return odds (" + STRFLUSH   + "/1)\n";
    out += "     Royal Flush will return odds (" + ROYALFLUSH + "/1)\n";
    out += "---------------------------------------------------\n";
    out += "\nTo discard, enter the numbers in this fashion:\n";
    out += "Cards to discard [separated by spaces] -> 4 1\n";
    out += "This will discard the fourth and first card from your hand.\n\n";
    out += "Brought to you by Yakker/Regret, (C)1991 all rights reserved.\n";
    return( write( out ), 1 );
}

int
clean_player()
{
    string p;
    object ob;

    p = capitalize((string)playerob->query_name());
    say(p + " takes too long to play, and forefits his game.\n");
    tell_object(playerob, "\nYou have taken too long to play, and you " +
        "forfeit your turn and your money.\n");
    seteuid(getuid());
    ob = clone_object(PATH + "/" + FILENAME);
    move_object(ob, environment(playerob));
    destruct(this_object());
    return 1;
}

int
exit_out()
{
    remove_call_out("clean_player");
    playerob = 0; return 1;
}

/*
// get_number() -- Return a random number for the card. (2 -> A).
*/
int
get_number()
{
    /*
    // Return a random value between 0 to 12.
    */
    return random(13);
}

/*
// get_suit() -- Return a random number for the suit (H, D, S, C).
*/
int
get_suit()
{
    /*
    // Return a random value between 0 and 2.
    */
    return random(4);
}

/*
// display_cards() -- Display the cards, in ansi if the user has ansi set.
*/
void
display_cards(string c1, string c2, string c3, string c4, string c5)
{
    string out, red, blk, grn, wht, end;

    if(this_player()->query_ansi())
    {
        red = sprintf("%c[31m", 27); blk = sprintf("%c[30m", 27);
        grn = sprintf("%c[42m", 27); wht = sprintf("%c[47m", 27);
        end = sprintf("%c[2;37;0m%c[0;0m", 27, 27);
        c1 = sprintf("%s%s", ((c1[1..1]=="H" || c1[1..1]=="D")? red: blk), c1);
        c2 = sprintf("%s%s", ((c2[1..1]=="H" || c2[1..1]=="D")? red: blk), c2);
        c3 = sprintf("%s%s", ((c3[1..1]=="H" || c3[1..1]=="D")? red: blk), c3);
        c4 = sprintf("%s%s", ((c4[1..1]=="H" || c4[1..1]=="D")? red: blk), c4);
        c5 = sprintf("%s%s", ((c5[1..1]=="H" || c5[1..1]=="D")? red: blk), c5);
        out  = sprintf("%s                                                             %s\n",
            grn, end);
        out += sprintf("%s      %s%s   %s      %s%s   %s      %s%s   %s      %s%s   %s      %s%s   %s      %s\n",
            grn, wht, c1, grn, wht, c2, grn, wht, c3, grn, wht, c4, grn, wht, c5, grn, end );
        out += sprintf("%s      %s     %s      %s     %s      %s     %s      %s     %s      %s     %s      %s\n",
            grn, wht, grn, wht, grn, wht, grn, wht, grn, wht, grn, end );
        out += sprintf("%s      %s   %s%s      %s   %s%s      %s   %s%s      %s   %s%s      %s   %s%s      %s\n",
            grn, wht, c1, grn, wht, c2, grn, wht, c3, grn, wht, c4, grn, wht, c5, grn, end );
        out += sprintf("%s                                                             %s\n",
            grn, end );
    }
    else
    {
        out  = "     -------    -------    -------    -------    -------\n";
        out += sprintf(
               "     |%s   |    |%s   |    |%s   |    |%s   |    |%s   |\n",
               c1, c2, c3, c4, c5);
        out += "     |     |    |     |    |     |    |     |    |     |\n";
        out += sprintf(
               "     |   %s|    |   %s|    |   %s|    |   %s|    |   %s|\n",
               c1, c2, c3, c4, c5);
        out += "     -------    -------    -------    -------    -------\n";
    }
    write( out );
}

/*
// write_cards() -- Print out the cards for the user.
*/
void
write_cards()
{
    int cnt;
    string tmpstr, c1, c2, c3, c4, c5;

    /*
    // Initialize the card strings.
    */
    c1 = ""; c2 = ""; c3 = ""; c4 = ""; c5 = "";

    /*
    // Here, assign all of the string values for the cards.
    // It's important to note that I don't have a switch statement
    // yet, so when one comes out, please adapt to that policy.
    */
    for (cnt = 0; cnt < NUM_CARDS; ++cnt)
    {
        tmpstr = "";
        /*
        // Perform if checks for the card value.
        */
        if      (cards[CARD][cnt] == TWO)      { tmpstr = "2";          }
        else if (cards[CARD][cnt] == THREE)    { tmpstr = "3";          }
        else if (cards[CARD][cnt] == FOUR)     { tmpstr = "4";          }
        else if (cards[CARD][cnt] == FIVE)     { tmpstr = "5";          }
        else if (cards[CARD][cnt] == SIX)      { tmpstr = "6";          }
        else if (cards[CARD][cnt] == SEVEN)    { tmpstr = "7";          }
        else if (cards[CARD][cnt] == EIGHT)    { tmpstr = "8";          }
        else if (cards[CARD][cnt] == NINE)     { tmpstr = "9";          }
        else if (cards[CARD][cnt] == TEN)      { tmpstr = "T";          }
        else if (cards[CARD][cnt] == JACK)     { tmpstr = "J";          }
        else if (cards[CARD][cnt] == QUEEN)    { tmpstr = "Q";          }
        else if (cards[CARD][cnt] == KING)     { tmpstr = "K";          }
        else if (cards[CARD][cnt] == ACE)      { tmpstr = "A";          }
        else                                   { tmpstr = "X";          }

        /*
        // Perform if checks for the suit value.
        */
        if      (cards[SUIT][cnt] == HEARTS)   { tmpstr = tmpstr + "H"; }
        else if (cards[SUIT][cnt] == DIAMONDS) { tmpstr = tmpstr + "D"; }
        else if (cards[SUIT][cnt] == SPADES)   { tmpstr = tmpstr + "S"; }
        else if (cards[SUIT][cnt] == CLUBS)    { tmpstr = tmpstr + "C"; }
        else                                   { tmpstr = tmpstr + "X"; }

        /*
        // Now, assign the value to the card we are currently working on.
        */
        if      (cnt == 0)                     { c1 = tmpstr;           }
        else if (cnt == 1)                     { c2 = tmpstr;           }
        else if (cnt == 2)                     { c3 = tmpstr;           }
        else if (cnt == 3)                     { c4 = tmpstr;           }
        else if (cnt == 4)                     { c5 = tmpstr;           }
    }
    /*
    // Now write out the cards for the player.
    */
    display_cards(c1, c2, c3, c4, c5);
}

/*
// deal() -- Deal the initial cards to the user.
*/
void deal()
{
    int cnt, loop, number, suit;
    string card_suit;
    string numb_suit;

    /*
    // In this for loop, assign a card to a user only if the card
    // has not already been given out.  Once all five cards are
    // given out, print them out.
    */
    for (cnt = 0; cnt < NUM_CARDS; ++cnt)
    {
        loop = FALSE;
        while (!loop)
        {
            /*
            // Get random values from the get_suit() and get_number()
            // functions, and check to see if that card is taken.
            */
            suit   = get_suit();
            number = get_number();
            if (!deck[suit][number])
            {
                /*
                // Assign that card, and break from the loop.
                */
                deck[suit][number] = 1;
                cards[SUIT][cnt] = suit;
                cards[CARD][cnt] = number;
                loop = TRUE;
            }
        }
    }

    /*
    // Sort the cards, write out the cards, and give numbers to
    // each card. (For discard purposes.)
    */
    /* sort_cards(); */
    write_cards();
    write("        1          2          3          4          5   \n");
}

/*
// sort_cards() -- Perform a boolean sort on the cards in hand.
*/
void sort_cards()
{
    int tmp1, tmp2, sorted, cnt;

    /*
    // This is a simple bubble sort.  For more information on
    // how to do this, look it up in your nearest Pascal/C
    // beginner's book (I wanted to perform a quick sort, but
    // it would be worthless to write it out simply to perform
    // this.
    */
    do
    {
        sorted = TRUE;
        for (cnt = 0; cnt < 4; ++cnt)
        {
            if (cards[CARD][cnt] > cards[CARD][cnt+1])
            {
                tmp1               = cards[SUIT][cnt];
                tmp2               = cards[CARD][cnt];
                cards[SUIT][cnt]   = cards[SUIT][cnt+1];
                cards[CARD][cnt]   = cards[CARD][cnt+1];
                cards[SUIT][cnt+1] = tmp1;
                cards[CARD][cnt+1] = tmp2;
                sorted             = FALSE;
            }
        }
    }
    while (!sorted);
}

/*
// payoff(num) -- Check to see how much the player won.
*/
int payoff(int num)
{
    /*
    // Rather than commenting all of this, I'll just say that the odds
    // are used as a multiplier on their coins.
    */
    if (num == NOTHING)
    {
        say(capitalize((string)playerob->query_name()) +
                " loses " + amt + " coins from the poker machine!\n");
        losers++;
        payin_count += amt;
    }
    else
    {
        write(" The machine gives you " + (amt * num) + " coins.\n");
        playerob->add_money(amt * num);
        say(capitalize((string)playerob->query_name()) +
                " wins " + (amt * num) + " coins from the poker machine!\n");
        winners++;
        payoff_count += (amt * num);
    }
    return 1;
}

/*
// check_win() -- See if the player won something.
*/
void check_win()
{
    int flag, ident, flush, straight, suit, cnt;

    write("\n");
    /*
    // NOTE:  I'm sure this could be done better, so if you see some
    //        way to improve it, please do. ;)  But this method seems
    //        to work well on its own.
    */

    /*
    // Sort the cards.
    */
    sort_cards();

    /*
    // First, rule out the flush, if possible.  It seems to save time
    // in the long run.  Also rule out the straight.
    */
    flush = TRUE; straight = TRUE; suit = cards[SUIT][0];
    for (cnt = 0; cnt < NUM_CARDS; ++cnt)
    {
        if (cards[SUIT][cnt] != suit) flush    = FALSE;
    }
    for (cnt = 0; cnt < NUM_CARDS - 1; ++cnt)
    {
        if (cards[CARD][cnt] != cards[CARD][cnt+1]-1) straight = FALSE;
    }
    /*
    // If we get here, we only have a flush or a straight.  Check
    // the values of both.
    */
    if ((flush == TRUE) && (straight == FALSE))
    {
            write("FLUSH!");
            payoff(FLUSH);
    }
    else if ((straight == TRUE) && (flush == FALSE))
    {
            write("STRAIGHT!");
            payoff(STRAIGHT);
    }

    /*
    // If we don't have a flush or a straight, then we might as well
    // rule out a royal flush and a royal straight check.  We only need
    // to be concerned about two of a kind, three of a kind, two pair,
    // four of a kind or full house.
    */
    else if ((!flush) && (!straight))
    {
        /*
        // Check to see if we have a four of a kind.
        */
        if ((cards[CARD][0] == cards[CARD][3]) ||
            (cards[CARD][1] == cards[CARD][4]))
        {
            write("FOUR OF A KIND!");
            payoff(FOURKIND);
        }
        /*
        // Check to see if we have a full house.
        */
        else if (((cards[CARD][0] == cards[CARD][1])  &&
                  (cards[CARD][2] == cards[CARD][4])) ||
                 ((cards[CARD][0] == cards[CARD][2])  &&
                  (cards[CARD][3] == cards[CARD][4])))
        {
            write("FULL HOUSE!");
            payoff(FULLHOUSE);
        }
        /*
        // Check to see if we have three of a kind.
        */
        else if ((cards[CARD][0] == cards[CARD][2]) ||
            (cards[CARD][1] == cards[CARD][3]) ||
            (cards[CARD][2] == cards[CARD][4]))
        {
            write("THREE OF A KIND!");
            payoff(THREEKIND);
        }
        else
        {
            /*
            // Now perform a simple for loop through the cards.
            // Depending on the ident value, we will have a different
            // answer.  If you try this out on a piece of paper with
            // any set, you'll notice that the only ambiguous case
            // is between three of a kind and two pair, but we handle
            // three of a kind before we reach this case.
            */
            ident = 1;
            for (cnt = 0; cnt < NUM_CARDS - 1; ++cnt)
            {
                if (cards[CARD][cnt] == cards[CARD][cnt+1])
                {
                    ident = ident + 1;
                }
            }
            /*
            // Check to see if we have two of a kind. (Jacks or better)
            */
            if (ident == 2)
            {
                flag = TRUE;
                for (cnt = 0; cnt < NUM_CARDS - 1; ++cnt)
                {
                    if ((cards[CARD][cnt] == cards[CARD][cnt+1])
                        && (cards[CARD][cnt] < JACK))
                    {
                        flag = FALSE;
                    }
                }
                if (flag)
                {
                    write("TWO OF A KIND!");
                    payoff(TWOKIND);
                }
                else
                {
                    write("You have nothing in your hand.  The game ");
                    write("takes your coins.\n(You must have Jacks or ");
                    write("better for a pair.)\n");
                    payoff(NOTHING);
                }
            }
            /*
            // Check to see if we have two pair.
            */
            else if (ident == 3)
            {
                write("TWO PAIR!");
                payoff(TWOPAIR);
            }
            else
            {
                write("You have nothing in your hand.  The game ");
                write("takes your coins.\n");
                payoff(NOTHING);
            }
        }
    }
    else
    {
        /*
        // We also have to check for straight flush and royal flush.
        */
        if ((flush == TRUE) && (straight == TRUE))
        {
            /*
            // Check to see if we have a royal flush (*lucky bastard*)
            */
            if (cards[CARD][0] == TEN)
            {
                write("ROYAL FLUSH!!!");
                payoff(ROYALFLUSH);
            }
            /*
            // Check to see if we have a straight flush (*lucky bastard*)
            */
            else
            {
                write("STRAIGHT FLUSH!!\n");
                payoff(STRFLUSH);
            }
        }
    }
}

/*
// discard_second(str) -- Check for discards, and give out new cards.
*/
int discard_second(string str)
{
    int suit, number, cnt, loop, loop2;
    string *arr;

    /*
    // If we get a null string, they want to keep their cards.
    */
    if (str == "")
    {
        /*
        // Keep the cards, and check for a win.
        */
        write("\nOkay, keeping cards.\n");
        write("\nYour second set of cards are:\n\n");
        write_cards();
        check_win();
        exit_out();
        return 1;
    }
    /*
    // If we get to this point, we separate out their answers by
    // spaces, and then change the card for each inputted answer.
    // If we have a bad answer, then we want to just exit out.
    // Don't take away coins, but don't give any payoff.
    */

    /*
    // Use explode to the the numbers into an array of strings.
    */
/*
    str = str + " ";
*/
    arr = explode(str, " ");
    loop = sizeof(arr); loop = loop - 1;

    /*
    // While we have a number of items in our array, go through all
    // of them.  Use sscanf() to get the number in the array, and
    // assign a free card to that spot in the card set.
    */
    while (loop >= 0)
    {
        /*
        // Convert the string number to an integer (atoi()!  Gotta have it.)
        */
        if (sscanf(arr[loop], "%d", cnt) != 1)
        {
            write("Bad entry of discard cards.  All bets are off.\n");
            exit_out();
            return 1;
        }
        /*
        // This is so we don't get a number out of range.
        */
        if ((cnt < 1) || (cnt > NUM_CARDS))
        {
            write("Bad entry of discard cards.  All bets are off.\n");
            exit_out();
            return 1;
        }
        /*
        // Assign the card.
        */
        cnt = cnt - 1; loop2 = FALSE;
        while (!loop2)
        {
            suit   = get_suit();
            number = get_number();
            if (!deck[suit][number])
            {
                deck[suit][number] = 1;
                cards[SUIT][cnt] = suit;
                cards[CARD][cnt] = number;
                loop2 = TRUE;
            }
        }
        loop = loop - 1;
    }
    /*
    // Sort the cards, show the cards, and check for a win.
    */
    /* sort_cards(); */
    write("\nYour second set of cards are:\n\n");
    write_cards();
    check_win();
    exit_out();
    return 1;
}

/*
// play(str) -- Play a game of poker.
*/
int do_play(string str)
{
    string tmpstr;

    if ((!str) || (str == ""))
    {
        return 0;
    }
    if (str == "poker")
    {
        amt = 10;
        write("Defaulting to a standard bet of 10 coins.\n");
        if (THISP->query_money() < amt)
        {
            write("You don't have the money!\n");
            return 1;
        }
    }
    else
    {
        if (sscanf(str, "%s %d", tmpstr, amt) != 2)
        {
            write("Usage: play poker [amount]\n");
            return 1;
        }
        if (tmpstr != "poker")
        {
            return 0;
        }
        if (amt < 10)
        {
            write("Defaulting to a standard bet of 10 coins.\n");
            amt = 10;
            if (THISP->query_money() < amt)
            {
                write("You don't have the money!\n");
                return 1;
            }
        }
        else if (amt > 1000)
        {
            write("Maximum bet is 50 coins.  Betting 50 coins.\n");
            amt = 50;
            if (THISP->query_money() < amt)
            {
                write("You don't have the money!\n");
                return 1;
            }
        }
    else
    {
        if (THISP->query_money() < amt)
        {
            write("You don't have the money!\n");
            return 1;
        }
    }
    }
    if (!playerob)
    {
        playerob = THISP; 
    }
    else
    {
        write(capitalize((string)playerob->query_name()) +
            " is playing poker.  Wait until " + subjective(playerob) +
            " is done.\n");
        return 1;
    }
    say(capitalize((string)playerob->query_name())
                   + " plays a game of poker on the poker machine.\n");
    THISP->add_money(-amt);
    write("You drop " + amt + " coins into the machine.\n");
    call_out("clean_player", MAX_TIME);
    playerob = THISP;
    /*
    // Clean up the cards.
    */
    clean_cards();

    /*
    // Check to see if we need to reshuffle.  If not, we just increment
    // the shuffle count for next time.  Otherwise, we call clean_deck()
    // and reshuffle.
    */
    if (SHUFFLECNT == shuffle)
    {
        write("The dealer reshuffles the deck.\n");
        clean_deck(); shuffle = 1;
    }
    else
    {
        shuffle = shuffle + 1;
    }
    /*
    // Print out the cards, and ask for discards.
    */
    write("The machine deals you some cards:\n\n"); deal(); write("\n");
    write("Which ones would you like to discard? [<RETURN> for none]\n");
    write("Cards to discard [separated by spaces] -> ");
    input_to("discard_second");
    return 1;
}
