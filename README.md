if wxWidget not found it should start downlanding and compiling it on it's own, otherwise install it from https://www.wxwidgets.org/ and add it's path to PATH in environment variables.

tldr;
cmake -S . -B build 
cmake --build build
