gShaderReplacer - OpenGL proxy dll for shader replacement and debugging.

Copyright 2009-2015 Henrik Münther - psycho@loonies.dk

WHY
===
-Use the included config to run stuff that does not work otherwise.
-Fix non-working stuff without help from the authors (and maybe tell him 
 what to fix afterwards).
-Easy debugging of your own stuff on different hardware, without the need 
 for dev-tools.
-Analyzing/optimizing of released stuff.
-Peek in other people's shader sources ;) (sorry, could not find a reasonable way
 to avoid that while keeping main functionality).

HOW
===
Place the opengl32.dll in the same directory as your executable and do the 
neccesary changes to gshaderreplacer.xml.
Depending on configuration the opengl will dump and/or replace all shaders 
sent to OpenGL from executables in the directory.

BUT HOW?
========
The included gshaderreplacer.xml should be more or less self explaining.
For the general configuration you can tell it to dump shaders to disk or not 
(no need to dump for "user" mode) and make global replacers. Replacers can also
be restricted to a specific .exe file, by putting it into an Application block. 
There is no pattern matching for executables, but several names can be written, 
like: <Application Name="intro.exe" Name0="intro_safe.exe" Name1="intro_low.exe">
etc.
Replacers can be either string (inlined in .xml file) or file (seperate file) 
based - FileReplacers are useful for debugging but final fixes should be a couple
of StringReplacers. 
Replacers can be restricted to a certain graphics card vendor, by using the 
Vendor=ATI or Vendor=NVIDIA attribute. So if you are making a workaround for a
specific vendor, you should use this, but if you are just making the code 
glsl-conformant (typically fixing something the nvidia compiler happily 
compiles) there is no reason for a vendor attribute.

UPDATES
=======
I hope we can extend the default gshaderreplacer.xml to fix (or optimize) more 
and more intros, so please send in additions to the file and I will update the
archive. Luckily the file is not too long at the moment, as most people fix the
errors when told how :)

PROBLEMS?
=========
For speed reasons it's not doing init code for every opengl function, so if 
someone (incorrectly) hits a normal gl function before the context is set up, 
it will crash. However, that's pretty easy to fix from the crash message,
where the  illegal jump adress tells which function that needs the init-code.
It intercepts shader source calls for the ARB extension and GL2.0.

HISTORY
=======
1.0 First public release.
1.0.1 Few fixes, more shaders
1.1 Support for glCreateShaderProgramv
1.2 Fixed a buffer overrun, more shaders
