C++ encoder and decoder for FIX/FAST protocol (http://www.fixtradingcommunity.org/pg/structure/tech-specs/fast-protocol) without compression operators.

How to build project.

You need Visual Studio 2013 on Windows.

How to build project's dependencies on Windows:
1) Download boost 1.58.0 from http://sourceforge.net/projects/boost/files/boost/1.58.0/ to folder <project directory>\share.
2) Unpack it to <project directory>\share\boost_1_58_0
2) cd <project directory>\share\boost_1_58_0
3) Run bootstrap.bat
4) Run command: "b2 toolset=msvc address-model=64 --with-program_options --with-test --build-type=complete stage"
