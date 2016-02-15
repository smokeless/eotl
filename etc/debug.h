#ifndef DEBUGGER
#define DEBUGGER "anthrax"
#endif
#define NOTIFY(s) tell_object(FINDP(DEBUGGER), sprintf("%O\n", s));
