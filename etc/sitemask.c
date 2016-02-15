// Stolen from Morgaine by Poi
// Added Online and Net-dead notifiers
// Whee closures

#include <acme.h>

static inherit AcmeArgs;
static inherit AcmeGetOpts;

#include AcmeCommandInc
#include AcmeArgsInc
#include AcmeGetOptsInc

private closure data_walk, get_last_time;

nomask int do_cmd( string verb, string arg )
{
    object ob;
    mixed args, out, data;
    string regex;
    int count;

    if( !stringp( arg ) || !strlen( arg ) )
        return( 0 );

    args = getopts( explode_args( arg ), "unp" );

    if( strlen( args[ 2 ] ) || ( sizeof( args[ 0 ] ) != 1 ) )
        FailUsage( verb );

    if( !sizeof( args[ 1 ] ) || member( args[ 1 ], 'u' ) )
    {
        if( !strstr( args[ 0 ][ 0 ], "guest_" ) && ob = FINDP( args[ 0 ][ 0 ] ) )
            data = ({ 0, 0, 0, 0, query_ip_number( ob ), 0, query_ip_name( ob ) });
        else if( !PASSWDKEEPER->queryUser( args[ 0 ][ 0 ] ) )
            return( write( verb + ": invalid user.\n" ), 1 );
        else if( !pointerp( data = PASSWDKEEPER->returnUser( args[ 0 ][ 0 ] ) ) )
            return( write( verb + ": passwd data unavailable!\n" ), 1 );

        if( member( args[ 1 ], 'n' ) )
            regex = data[ 6 ];
        else
            regex = data[ 4 ];
    }
    else
        regex = args[ 0 ][ 0 ];

    out = ({ });
    walk_mapping( PASSWDKEEPER->queryUserlist(), data_walk, regex, &out, &count,
        member( args[ 1 ], 'n' ) ? 6 : 4, member( args[ 1 ], 'p' ) );

    if( !sizeof( out ) )
        return( write( verb + ": no match.\n" ), 1 );
    out = ({ "SITE MASK for \"" + regex + "\"", "---------------------------------"
        "-------------------------------------------------" }) + out + ({ "--------"
        "--------------------------------------------------------------------------",
        to_string( sizeof( out ) ) + " of " + to_string( count ) + " users "
        "processed" });
    THISP->more_string( out );
    return( 1 );
}

nomask void create()
{
    seteuid( getuid() );

    get_last_time = lambda( ({ 'l }),
      ({ #',,
        ({ #'=, 's, ({ #'%, 'l, 60 }) }),
        ({ #'=, 'l, ({ #'-, 'l, 's }) }),
        ({ #'=, 'l, ({ #'/, 'l, 60 }) }),
        ({ #'=, 'm, ({ #'%, 'l, 60 }) }),
        ({ #'=, 'l, ({ #'-, 'l, 'm }) }),
        ({ #'=, 'l, ({ #'/, 'l, 60 }) }),
        ({ #'=, 'h, ({ #'%, 'l, 24 }) }),
        ({ #'=, 'l, ({ #'-, 'l, 'h }) }),
        ({ #'=, 'l, ({ #'/, 'l, 24 }) }),
        ({ #'=, 'y, ({ #'/, 'l, 365 }) }),
        ({ #'=, 'd, ({ #'-, 'l, ({ #'*, 'y, 365 }) }) }),
        ({ #'=, 'r,
          ({ #'sprintf, "Last login: %s%s%s%s%s.",
            ({ #'?, 'y,
              ({ #'sprintf, "%dy ", 'y }),
              ""
            }),
            ({ #'?, 'd,
              ({ #'sprintf, "%dd ", 'd }),
              ""
            }),
            ({ #'?, 'h,
              ({ #'sprintf, "%dh ", 'h }),
              ""
            }),
            ({ #'?, 'm,
              ({ #'sprintf, "%dm ", 'm }),
              ""
            }),
            ({ #'?, 's,
              ({ #'sprintf, "%ds", 's }),
              ""
            })
          })
        }),
        ({ #'return, 'r })
      }) );

    data_walk = lambda( ({ 'k, 'd, 'r, 'o, 'c, 'i, 'p }),
      ({ #',,
        ({ #'?,
          ({ #'&&,
            ({ #'sizeof, ({ #'regexp, ({ #'({, ({ #'[, 'd, 'i }) }), 'r }) }),
            ({ #'||, ({ #'!, 'p }), ({ #'find_player, ({ #'[, 'd, 0 }) }) })
          }),
          ({ #'+=,
            'o,
            ({ #'({, ({ #'sprintf, "%2s  %-:14s %-15s %s",
              ({ #'?,
                ({ #'&&,
                  ({ #'=, 'a, ({ #'find_player, ({ #'[, 'd, 0 }) }) }),
                  ({ #'interactive, 'a })
                }),
                ({ #'?,
                  ({ #'call_other, ({ #'this_player }), "query_ansi" }),
                  ({ #'implode, ({ #'({, HIG, "On", NORM }), "" }), "On"
                }),
                ({ #'find_player, ({ #'[, 'd, 0 }) }),
                ({ #'?,
                  ({ #'call_other, ({ #'this_player }), "query_ansi" }),
                  ({ #'implode, ({ #'({, HIR, "ND", NORM }), "" }), "ND"
                }),
                ""
              }),
              ({ #'[, 'd, 0 }),
              ({ #'[, 'd, 'i }),
              ({ #'funcall, get_last_time, ({ #'-, ({ #'time }), ({ #'[, 'd, 5 }) }) })
            }) })
          })
        }),
        ({ #'+=, 'c, 1 })
      }) );
}

nomask string *cmd_usage( string func )
{
    return( ({ "-np [sitemask]", "-unp [player] " }) );
}

nomask string cmd_help( string func )
{
    return( "This function greps the password keeper for an ip number "
        "pattern (such as 36.21.*.*) and lists all users matching.  Use "
        "of the -u option indicates that the passed argument is not a "
        "pattern but a player name, and that players ip number will be used "
        "as a pattern.  Use of the -n option indicates that the passed "
        "argument is an ip name, and instructs the command to perform the "
        "search accordingly.  Using the -p option lists only matching players "
        "currently logged in." );
}

nomask string cmd_desc()
{
    return( "crossreference player sites" );
}
