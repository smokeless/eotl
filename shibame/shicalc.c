// Test of a very simple custom function made into a basic item
// Shibame 2014.01.09

#include <ansi.h>

inherit NewThingCode;

//int firstnum, secondnum, result;
//result does not need to be a global
//variable. Nothing will call it.

int firstnum, secondnum;

void extra_create()
{
    set( "short", "a broken piece of electronics" );
    set( "id", ({ "electronics", "broken electronics", "calculator",
        "broken calculator", "calc" }) );
    //set( "ansi_short", RED "a broken piece of electronics" NORM );
    //You don't need to add NORM to the end of ansi short.
    set( "ansi_short", RED "a broken piece of electronics" );
    set( "long", "You hold in your hand what looks to be a smashed "
        "calculator. All the buttons are missing, except for the "
        "PLUS sign. Strangely, there is a tiny loudspeaker and a "
        "tiny microphone on the calculator. This looks to be one "
        "of those prototype models made for spastic children. The "
        "entire contraption is made of RED bright red NORM plastic. "
        "There are some instructions written on the back. ");
    set( "ansi_long", "You hold in your hand what looks to be a smashed "
        "calculator. All the buttons are missing, except for the "
        "PLUS sign. Strangely, there is a tiny loudspeaker and a "
        "tiny microphone on the calculator. This looks to be one "
        "of those prototype models made for spastic children. The "
        "entire contraption is made of " RED "bright red " NORM "plastic. "
        "There are some instructions written on the back. ");
    set( "value", 10 );
    set( "weight", 1 );
    set( "descs", ([
        "back" : "To add two numbers, you must set the first number "
            "with <SETFIRSTNUMBER x>, and then set the second number "
            "with <SETSECONDNUMBER y>. Use <CALCULATE> to get the "
            "result. ",
        "instructions" : "*back" ]) );
}

void extra_init()
{
    add_action( "setfirstnumber", "SETFIRSTNUMBER" );
    add_action( "setsecondnumber", "SETSECONDNUMBER" );
    add_action( "calculate", "CALCULATE" );
}

int setfirstnumber( string whathetypedx )
{
    /*
    Add action is expecting a string.
    Like always when you pass through the verb it
    expects a string.
    
    if( !intp( whathetypedx ) == -1 );
    Here you are seeing if whathetypedx is
    an int. 
    If !intp() means if not an int.
    So you don't need == -1. Also it won't
    evaluate to -1, that's more to do with
    arrays. It will either be 0 or 1.
    If what they typed was not an int
    it would execute the code below it.
    Since add_action is always passing
    a string we have to get tricky.
    */
    
    if( !to_int( whathetypedx ) )    
      return notify_fail( "x needs to be a number!\n" );
    
    /*We check to see if what they typed can actually be made
      into an int. If it can, we don't fail out. We continue
      forwards and make it an int. */
    
    firstnum = to_int( whathetypedx );
    

    tell_player( THISP, "First number set!\n" );
    
    return 1;
    
}

int setsecondnumber( string whathetypedy )
{
    /*
    This is the same code block as the first one
    so we stick to what works.
    */
    
    if( !to_int( whathetypedy ) )
      return notify_fail( "y needs to be a number!\n" );
    
    secondnum = to_int( whathetypedy );
    
    
    tell_player( THISP, "Second number set!\n" );
    
    return 1;
}
/* To comment out large sections of code like this
   just use */
 
// int calculate()
// {
//    int result = firstnum + secondnum;
//    
//   tell_player( THISP, "The total is " print( result );
//    
//    return 1;
// }

int calculate()
{
    /* We declare result here. As there is
       no reason for it be a global variable.
       Unless the result is going to be used
       by another function.
       
       Also notice we don't take an arg in the
       calculate function. That's because
       it's just a button. So we're not concerned
       with what they type after.
       
       Of course at some point we might be.
       So we could take an arg and run some
       checks.
       
       We tell the player what the sum is,
       passing %i to sprintf(), not %s
       i for integer, s for string.
       
       Then since we've completed our deal
       I went ahead and threw something in
       to clear out the global variables.
    */
    
    int result = firstnum + secondnum;
    tell_player( THISP, sprintf( "The total is %i. "
      "The caluclator is now clear.", result ) );
    firstnum = 0;
    secondnum = 0;
    return 1;
    
    /*Overall this file could probably be broken down
      into one function. Using add_action. I'd
      probably have the thing work like,
      add 2 and 3, then spit out the result.
      No need for global variables which are
      memory intensive. I think you have all
      the tools to make that happen right here.
      All you need to do is man sprintf, and sscanf.
      You should be able to get it working in one
      easy function.*/
}
