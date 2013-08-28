// Copyright (C) 2004-2009 Joe Linhoff, All Rights Reserved
// gpreadme.h -- notes and doc
#if 0 // notes

- GP = game platform, modules
- QE = quarter engine, built with GP
- tab size 3 with spaces

== Game Platform (GP) ==

gpreadme.h -- this file
gptypes.h -- base types (no dependencies)
gperr.h -- error defines and common types
gpsz.h -- fast, safe string routines (gptypes)
gpmem.h -- memory module
gpmath.h -- math functions, C structures
gpgl.h -- extended OpenGL functions / extensions
gpfile.h -- file functions
gpuno.h -- uno

== QE Platform (QE) ==

qedraw.h -- draw interface, OpenGL
qeinp.h -- input functions
qenet.h -- networking functions
qevid.h -- video functions
qeinst.h -- instance and animation functions
qelibdef.h -- library definitions
qeeng.h -- engine functions
qesnd.h -- sound functions
qesl.h -- scripting functions

== OTHER FILES ==

qegreen.lib -- library file
qegreen.dll -- executable

#endif // notes
