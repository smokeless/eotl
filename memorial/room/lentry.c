#include <ansi.h>
inherit RoomPlusCode;
 
void extra_create()
{
    set( "short", "The South Wing of the E.C. Library" );
       
        
    set( "day_long" ,
       "This is the south wing of the Eternal City Library. To the north "
       "you can see the main part of the library. To the south, a finely"
       "expansive glass door opens up to a large grassy cemetery. There is "
       "a brass plaque above the southern door. Sunlight shines in  "
       "through the glass door and dust from the library is illuminated"
       "magically and dancing about in the warm glow. There are shelves "
           "upon shelves of books in this room, most dusty from years of"
           "loneliness."
    );
       
        set("night_long",
            "This is the south wing of the Eternal City Library. To the north"
                "you can see the main part of the library. To the south a finely crafted,"
                "expansive glass door opens up to a dark, torch-lit cemetery. The"
                "flickering tongues of flame dance about, casting shadows in through"
                "the beautiful panes of glass. The library is dimly lit, and the countless "
        "shelves of books stretch high to the ceiling and back into the shadows. A"
                "plaque made of brass is above the glass doorway, lit up by some kind of"
                "soft lighting." );
               
    set( "day_light" , 20 );
    set( "night_light", 18 );
   
    set( InsideP, 1 );
    set( "exits" ,
      ([
        "north" : "/zone/null/eternal/common",
        //"south" : ZROOM "cemetary1",
      ])
    );
    set( "reset_data" ,
      ([
      ])
    );
    
    // Mapping of descs for looking at things. Do this.
    set( "descs" ,
      ([
        "book"     : "*books",
                "shelf"    : "*books",
                "library"  : "*books",
                "plaque"   : "The plaque is engraved in bronze and reads 'The EOTL Memorial"
                             "Cemetery' in a beautiful , flowing script.",
                "books"    : "As you look around, the collection of books is overwhelming. You"
                             "notice most of the books are a bit dusty and must not have been"
                                         "checked out or even taken off of the shelf in quite some time. In"
                                         "this part of the library the books seem to be mainly non fiction.",
                                         
                                // Would like to add some books in here, either as objects or descs
                                // When time allows
       
       
        "glass"    : "*door",
        "doors"    : "*door",
        "door"     : "This is an impressive door, made of etched glass with "
                             "a view of the cemetery outside. The trim around the door is"
                                         "hand carved wood, with a spiralling pattern running the "
                                         "perimeter. The sunlight feels warm shining in through the glass,"
                                         "bathing the library in a warm glow. You can see the cemetery"
                                         "to the south, and it is a magnificent view, framed perfectly by"
                                         "the glass door. As you approach the door, it opens automatically,"
                                         "the two panes of glass separating with just the softest whisper of a sound.",
                                         
        ]) );
       
        set ("night_descs" ,
        ([
        "glass"    : "*door",
        "doors"    : "*door",
        "door"     : "This is an impressive door, made of etched glass with "
                             "a view of the cemetery outside. The trim around the door is"
                                         "hand carved wood, with a spiralling pattern running the "
                                         "perimeter. Shadows dance about the room and you notice that"
                                         "through the southern glass doorway is a large cemetery with"
                                         "torch lit paths. As you approach the door, it opens automatically,"
                                         "the two panes of glass separating with just the softest whisper of a"
                                         "sound.",
        ]) );
         /*
         set( "read", ([
      "plaque": "The EOTL Memorial Cemetery",
     
    ]);
    */
}
