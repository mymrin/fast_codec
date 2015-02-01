How to build project.

You need Visual Studio 2013 on Windows.

Project dependency on Windows:
1) Download boost 1.57.0 from http://sourceforge.net/projects/boost/files/boost/1.57.0/ to folder fast_codec\share.
Unpack it fast_codec\share\boost_1_57_0
2) cd fast_codec\share\boost_1_57_0
3) To build boost programm_options run command:
b2 toolset=msvc address-model=64 --with-program_options --build-type=complete stage
