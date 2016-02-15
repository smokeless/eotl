inherit NewThingCode;

#include <facility.h>

void extra_create()
{
    int what = random( 3 );
    string *ident;
    string short, long;
    switch( what )
    {
      case 0 : ident = ({ "plastic", "broken plastic", "piece" }); break;
      case 1 : ident = ({ "ram", "broken ram", "ram stick" }); break;
      case 2 : ident = ({ "trash", "sticky trash", "sticky" }); break;
    }
    switch( what )
    {
      case 0 : short = "a piece of plastic"; break;
      case 1 : short = "a broken RAM stick"; break;
      case 2 : short = "a piece of sticky trash"; break;
    }
    switch( what )
    {
      case 0 : long = "A fist sized piece of flat plastic. "
                      "It looks like it broke off the side of "
                      "a liqour store ATM. "; break;
      case 1 : long = "There is no way this stick is "
                      "salvalgeable. Hopefully whatever "
                      "computer this came out of has "
                      "extra."; break;
      case 2 : long = "A wadded up ball of sticky magazine "
                      "page. Unfolding it would tear it, "
                      "and the print is completely illegible. "
                      "It smells disgusting."; break;
     }
    set_ids( ident );
    set_short( short );
    set_long( long );
    set_value( 30 );
    set_weight( 25 );
}
    

 
