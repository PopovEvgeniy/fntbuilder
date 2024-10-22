                             FNT BUILDER

                 Mugen font compiler by Popov Evgeniy Alekseyevich

                              Version 2.2.4.1

System requirements

64 kilobytes of free space on storage media.

Description and usage

This program lets you create a font for the MUGEN game engine.
This program takes 3 command-line arguments: a graphics file, a text file, and the font file.

Exit codes

0: Operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE

Source code

The code was compiled under Open Watcom.
But you can compile it under any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history

1.0: Initial version.
1.1: The small changes in the source code. The program was recompiled under Open Watcom.
1.2-1.9: The small changes in the source code.
2.0: The source code is improved. Linux support has been added.
2.0.1-2.0.2: The small changes in source code.
2.0.2.0.1: Documentation updated.
2.0.3-2.0.5: Small changes.
2.0.5.1: The makefile updated.
2.0.6: The small changes.
2.0.7-2.0.8: The small bug is fixed.
2.0.9-2.1: The small changes.
2.1.0.1-2.1.0.2: The makefile updated.
2.2-2.2.2: The small changes.
2.2.3: Visual C++ support improved.
2.2.3.1: Documentation updated.
2.2.4: The small changes.
2.2.4.1: Documentation updated.