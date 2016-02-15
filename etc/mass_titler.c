inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "titler", "mass titler", "mass"}));
    set_short( "a mass titler");
    set_long( "Tired of everyone running around with custom "
      "titles? Not content to leave people alone? Great. "
      "This titler will fix all mortal titles! Take that "
      "whoever." );
    set_weight( 0 );
    set_value( 10 );
}

void extra_init()
{
    add_action( "title", "title");
}

int title( string arg )
{
    string titles;
    if( !stringp( arg ) )
    {
        tell_player(THISP, "Right on, using default!");
        call_out( "nonsense", 1);
        return 1;
    }
    titles = arg;
    object *x = filter_array( users(), #'living );
    x = x - filter_array( x, #'is_wizard );
    foreach( object b : x )
    {
      b->set_title( titles );
    }
    return 1;
}

int nonsense()
{
    object *x = filter_array( users(), #'living );
    x = x - filter_array( x, #'is_wizard );
    foreach( object b : x )
    {
      b->set_title( "if u can't handle me at my worst u don't deserve me at my best" );
    }
    return 1;
}
