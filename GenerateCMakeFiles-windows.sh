source ./GenerateCMakeFiles-lib.sh

GENERATE_VERBOSE="1"        # set to "1" - enable additional output during script processing on the screen
GENERATE_DEBUG="1"          # set to "1" - enable debug output during script processing on the screen

GENERATE_NOT_Cxx="0"                # set to "1" - do not use compiler -std=c++14 parameter (compiler parameter is enabled as default)
GENERATE_NOT_PARALLEL="0"           # set to "1" - do not build with multiple processes (parralel build is enabled as default)
GENERATE_NOT_PCH="0"                # set to "1" - do not build with precompiled header support (precompiled header support is enabled as default)
GENERATE_NOT_REMOVE_UNUSED_CODE="0" # set to "1" - do not use compile and link parameters to remove unused code and functions (unused code and functions are removed as default)

CMAKE_SOURCE_DIR="."
UPP_SRC_BASE="."
UPP_SRC_DIR="${UPP_SRC_BASE}/src"
PROJECT_EXTRA_INCLUDE_DIR="${UPP_SRC_BASE}/alt" # this can be changed to u++'s uppsrc directory
PROJECT_NAME="${UPP_SRC_BASE}/reference/Shell/Shell.upp"
PROJECT_FLAGS="-DflagMSC22X64 -DflagMSC -DflagWIN32 -DflagGUI -DflagSCREEN -DflagDX12 -DflagVR -DflagUWP"
PROJECT_EXTRA_COMPILE_FLAGS=""
PROJECT_EXTRA_LINK_FLAGS=""

generate_main_cmake_file "${PROJECT_NAME}" "${PROJECT_FLAGS}"
