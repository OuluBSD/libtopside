# CMakeLists.txt generated Sun Apr 23 22:09:00 EEST 2023
cmake_minimum_required ( VERSION 3.4.1 )

#################################################
# In-Source builds are strictly prohibited.
#################################################
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message ( FATAL_ERROR
  "\n****************************** ERROR ******************************\n"
  "In-source build are not allowed. "
  "Please do not polute the sources with binaries or any project unrelated files. "
  "To remove generated files run:\n"
  "'rm -rf CMakeCache.txt CMakeFiles'\n"
  "To build the project, please do the following:\n"
  "'mkdir build && cd build && cmake ..'"
  "\n****************************** ERROR ******************************\n")
endif()

# Set the default library directory to store built libraries
set ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Overwrite cmake verbose makefile output
# (e.g. do not generate cmake verbose makefile output even when the debug flag is set)
# not set - do not overwrite settings
# 0 - do not generate cmake verbose makefile output
# 1 - always generate cmake verbose makefile output
set ( CMAKE_VERBOSE_OVERWRITE  )

# Project name
project ( Shell )

# Set the project common path
set ( UPP_SOURCE_DIRECTORY ./src )
set ( UPP_EXTRA_INCLUDE ./alt )
set ( PROJECT_INC_DIR ${PROJECT_BINARY_DIR}/inc )
set ( PROJECT_PCH_DIR ${PROJECT_BINARY_DIR}/pch )

if ( MSVC )
SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /await /AI\"C:\\Program Files (x86)\\Windows Kits\\10\\UnionMetadata\\10.0.22000.0\\Facade;D:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\VC\\vcpackages\"" CACHE STRING "compile flags" FORCE)
endif()

# Set the default include directory for the whole project
include_directories ( BEFORE ${UPP_SOURCE_DIRECTORY} )
include_directories ( BEFORE ${PROJECT_INC_DIR} ${UPP_EXTRA_INCLUDE} )
include_directories ( BEFORE ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories ( BEFORE ${CMAKE_SOURCE_DIR}/./reference/Shell )
include_directories ( BEFORE ${CMAKE_SOURCE_DIR}/./reference )

# Set the default path for built executables to the bin directory
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

# Project definitions
add_definitions ( -DflagMSC22X64 -DflagMSC -DflagWIN32 -DflagGUI -DflagSCREEN -DflagDX12 -DflagVR -DflagUWP -DflagGNUC14 -DflagMP -DflagPCH )

# Option to distinguish whether to build binary with removed unused code and functions
option ( REMOVE_UNUSED_CODE "Build binary with removed unused code and functions." ON )

# Option to enable static analysis with include-what-you-use
option ( ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF )
if ( ENABLE_INCLUDE_WHAT_YOU_USE )
    find_program( INCLUDE_WHAT_YOU_USE include-what-you-use )
    if ( INCLUDE_WHAT_YOU_USE )
        set( CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE} )
    else()
        message( WARNING "include-what-you-use requested but executable not found" )
        set( CMAKE_CXX_INCLUDE_WHAT_YOU_USE "" CACHE STRING "" FORCE )
    endif()
endif()

# Option to enable static analysis with cppcheck
option ( ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF )
if ( ENABLE_CPPCHECK )
    find_program( CPPCHECK cppcheck)
    if ( CPPCHECK )
        set( CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --suppress=missingInclude
        --enable=all
        --inline-suppr
        --inconclusive
        -i
        ${CMAKE_SOURCE_DIR}/imgui/lib )
    else()
        message( WARNING "cppcheck requested but executable not found" )
        set( CMAKE_CXX_CPPCHECK "" CACHE STRING "" FORCE )
    endif()
endif()

# Option to enable static analysis with clang-tidy
option ( ENABLE_CLANG_TIDY "Run clang-tidy with the compiler." OFF )
if ( ENABLE_CLANG_TIDY )
    if ( CMake_SOURCE_DIR STREQUAL CMake_BINARY_DIR )
        message ( FATAL_ERROR "ENABLE_CLANG_TIDY requires an out-of-source build!" )
    endif()

    if ( CMAKE_VERSION VERSION_LESS 3.5 )
        message ( WARNING "ENABLE_CLANG_TIDY is ON but CMAKE_VERSION is less than 3.5!" )
        set( CMAKE_C_CLANG_TIDY "" CACHE STRING "" FORCE )
        set( CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE )
    else()
        find_program ( CLANG_TIDY_COMMAND NAMES clang-tidy )
        if ( NOT CLANG_TIDY_COMMAND )
            message ( WARNING "ENABLE_CLANG_TIDY is ON but clang-tidy is not found!" )
            set( CMAKE_C_CLANG_TIDY "" CACHE STRING "" FORCE )
            set( CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE )
        else()
            set( CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND}" )
            set( CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}" )
        endif()
    endif()
endif()

# Extra compilation and link 
set ( PROJECT_EXTRA_COMPILE_FLAGS "" )
message ( STATUS "Extra compilation flags: ${PROJECT_EXTRA_COMPILE_FLAGS}" )
set ( PROJECT_EXTRA_LINK_FLAGS "" )
message ( STATUS "Extra link flags: ${PROJECT_EXTRA_LINK_FLAGS}" )

# Remove flags which are set by CMake
remove_definitions( -DflagLINUX )
remove_definitions( -DflagBSD )
remove_definitions( -DflagFREEBSD )
remove_definitions( -DflagNETBSD )
remove_definitions( -DflagOPENBSD )
remove_definitions( -DflagSOLARIS )
remove_definitions( -DflagOSX )
remove_definitions( -DflagDRAGONFLY )
remove_definitions( -DflagANDROID )

# Read compiler definitions - used to set appropriate modules
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

# Platform flags settings
if ( WIN32 )
  remove_definitions( -DflagPOSIX )
  remove_definitions( -DflagOSX11 )

  if ( NOT "${FlagDefs}" MATCHES "flagWIN32(;|$)" )
    add_definitions ( -DflagWIN32 )
  endif()

  if ( CMAKE_SYSTEM_VERSION STREQUAL "10.0" AND NOT "${FlagDefs}" MATCHES "flagWIN10(;|$)" )
    add_definitions ( -DflagWIN10 )
  endif()

else()
  remove_definitions( -DflagWIN32 )

  if ( NOT "${FlagDefs}" MATCHES "flagSHARED(;|$)" )
    add_definitions ( -DflagSHARED )
  endif()

  if ( NOT "${FlagDefs}" MATCHES "POSIX(;|$)" )
    add_definitions ( -DflagPOSIX )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND NOT "${FlagDefs}" MATCHES "flagLINUX(;|$)" )
    add_definitions ( -DflagLINUX )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "BSD" AND NOT "${FlagDefs}" MATCHES "flagBSD(;|$)" )
    add_definitions ( -DflagBSD )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD" AND NOT "${FlagDefs}" MATCHES "flagFREEBSD(;|$)" )
    add_definitions ( -DflagFREEBSD )
    if ( NOT "${FlagDefs}" MATCHES "flagBSD(;|$)" )
      add_definitions ( -DflagBSD )
    endif()
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "NetBSD" AND NOT "${FlagDefs}" MATCHES "flagNETBSD(;|$)" )
    add_definitions ( -DflagNETBSD )
    if ( NOT "${FlagDefs}" MATCHES "flagBSD(;|$)" )
      add_definitions ( -DflagBSD )
    endif()
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "OpenBSD" AND NOT "${FlagDefs}" MATCHES "flagOPENBSD(;|$)" )
    add_definitions ( -DflagOPENBSD )
    if ( NOT "${FlagDefs}" MATCHES "flagBSD(;|$)" )
      add_definitions ( -DflagBSD )
    endif()
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Solaris" AND NOT "${FlagDefs}" MATCHES "flagSOLARIS(;|$)" )
    add_definitions ( -DflagSOLARIS )
    set ( REMOVE_UNUSED_CODE OFF )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "SunOS" AND NOT "${FlagDefs}" MATCHES "flagSOLARS(;|$)" )
    add_definitions ( -DflagSOLARIS )
    set ( REMOVE_UNUSED_CODE OFF )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" AND NOT "${FlagDefs}" MATCHES "flagOSX(;|$)" )
    add_definitions ( -DflagOSX )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "DragonFly" AND NOT "${FlagDefs}" MATCHES "flagDRAGONFLY(;|$)" )
    add_definitions ( -DflagDRAGONFLY )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" AND NOT "${FlagDefs}" MATCHES "flagANDROID(;|$)" )
    add_definitions ( -DflagANDROID )
  endif()

endif()
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

# Check supported compilation architecture environment
if ( "${FlagDefs}" MATCHES "flagGCC32(;|$)" OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )
  set ( STATUS_COMPILATION "32" )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -m32 -msse2 ${PROJECT_EXTRA_COMPILE_FLAGS}" )
else()
  set ( STATUS_COMPILATION "64" )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -m64 ${PROJECT_EXTRA_COMPILE_FLAGS}" )
  set ( MSVC_ARCH "X64" )
endif()
message ( STATUS "Build compilation: ${STATUS_COMPILATION} bits" )

# Set GCC builder flag
if ( ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" )
  set ( CMAKE_COMPILER_IS_GNUCC TRUE )

  if ( "${FlagDefs}" MATCHES "flagGNUC14(;|$)" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 )
    message ( FATAL_ERROR "GNU GCC version 4.9+ is required to use -std=c++14 parameter!" )
  endif()

  remove_definitions ( -DflagMSC )
  remove_definitions ( -DflagCLANG )

  if ( NOT "${FlagDefs}" MATCHES "flagGCC(;|$)" )
    add_definitions ( -DflagGCC )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set CLANG builder flag
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
  set ( CMAKE_COMPILER_IS_CLANG TRUE )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -Wno-logical-op-parentheses" )

  remove_definitions ( -DflagMSC )
  remove_definitions ( -DflagGCC )

  if ( NOT "${FlagDefs}" MATCHES "flagCLANG(;|$)" )
    add_definitions ( -DflagCLANG )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set MSVC builder flags
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" )
  remove_definitions ( -DflagGCC )
  remove_definitions ( -DflagCLANG )

  if ( NOT "${FlagDefs}" MATCHES "flagUSEMALLOC(;|$)" )
    add_definitions ( -DflagUSEMALLOC )
  endif()

  if ( NOT "${FlagDefs}" MATCHES "flagMSC(;|$)" )
    add_definitions ( -DflagMSC )
  endif()

  if ( ${MSVC_VERSION} EQUAL 1200 )
    add_definitions ( -DflagMSC6${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1300 OR ${MSVC_VERSION} EQUAL 1310)
    add_definitions ( -DflagMSC7${MSVC_ARCH} )
    add_definitions ( -DflagMSC71${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1400 )
    add_definitions ( -DflagMSC8${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1500 )
    add_definitions ( -DflagMSC9${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1600 )
    add_definitions ( -DflagMSC10${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1700 )
    add_definitions ( -DflagMSC11${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1800 )
    add_definitions ( -DflagMSC12${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1900 )
    add_definitions ( -DflagMSC14${MSVC_ARCH} )
  endif()
  if ( (${MSVC_VERSION} GREATER_EQUAL 1910) AND (${MSVC_VERSION} LESS_EQUAL 1919) )
    add_definitions ( -DflagMSC15${MSVC_ARCH} )
  endif()
  if ( (${MSVC_VERSION} GREATER_EQUAL 1920) AND (${MSVC_VERSION} LESS_EQUAL 1929) )
    add_definitions ( -DflagMSC16${MSVC_ARCH} )
  endif()

  if ( "${FlagDefs}" MATCHES "flagMP(;|$)" AND NOT ${MSVC_VERSION} LESS 1400 )
    set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MP" )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set Intel builder flag
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel" AND NOT "${FlagDefs}" MATCHES "flagINTEL(;|$)" )
  add_definitions ( -DflagINTEL )
  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set link directories on BSD systems
if ( ${CMAKE_SYSTEM_NAME} MATCHES BSD )
    link_directories ( /usr/local/lib )
endif()

# Set debug/release compiler options
if ( "${FlagDefs}" MATCHES "flagDEBUG(;|$)" )
  set ( CMAKE_VERBOSE_MAKEFILE 1 )
  set ( CMAKE_BUILD_TYPE DEBUG )
  add_definitions ( -D_DEBUG )

  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -O0" )

  if ( NOT "${FlagDefs}" MATCHES "flagDEBUG(;|$)" )
      add_definitions ( -DflagDEBUG )
  endif()

  if ( MSVC )
      if ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)X64" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -debug -OPT:NOREF" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -incremental:yes -debug -OPT:NOREF" )
      endif()
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
else()
  set ( CMAKE_VERBOSE_MAKEFILE 0 )
  set ( CMAKE_BUILD_TYPE RELEASE )
  add_definitions ( -D_RELEASE )

  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -O2" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GS-" )

  if ( NOT "${FlagDefs}" MATCHES "flagRELEASE(;|$)" )
      add_definitions ( -DflagRELEASE )
  endif()

  if ( MSVC )
      if ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)X64" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -release -OPT:REF,ICF" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -incremental:no -release -OPT:REF,ICF" )
      endif()
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()
message ( STATUS "Build type: " ${CMAKE_BUILD_TYPE} )

if ( REMOVE_UNUSED_CODE AND ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG ) )
  message ( STATUS "Build with remove unused code: TRUE" )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ffunction-sections -fdata-sections" )
  set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-s,--gc-sections" )
else()
  message ( STATUS "Build with remove unused code: FALSE" )
endif()

if ( CMAKE_VERBOSE_OVERWRITE EQUAL 0 OR CMAKE_VERBOSE_OVERWRITE EQUAL 1 )
  set ( CMAKE_VERBOSE_MAKEFILE ${CMAKE_VERBOSE_OVERWRITE} )
endif()

if ( "${FlagDefs}" MATCHES "flagDEBUG_MINIMAL(;|$)" )
  if ( NOT MINGW )
      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ggdb" )
  endif()
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -g1" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Zd" )
endif()

if ( "${FlagDefs}" MATCHES "flagDEBUG_FULL(;|$)" )
  if ( NOT MINGW )
      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ggdb" )
  endif()
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -g2" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Zi" )
endif()

# Set static/shared compiler options
if ( "${FlagDefs}" MATCHES "flagSO(;|$)" )
  set ( BUILD_SHARED_LIBS ON )
  set ( LIB_TYPE SHARED )
  if ( NOT "${FlagDefs}" MATCHES "flagSHARED(;|$)" )
      add_definitions ( -DflagSHARED )
      get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
  endif()
endif()

if ( "${FlagDefs}" MATCHES "flagSHARED(;|$)" )
  set ( STATUS_SHARED "TRUE" )
  set ( EXTRA_GXX_FLAGS "${EXTRA_GXX_FLAGS} -fuse-cxa-atexit" )
else()
  set ( STATUS_SHARED "FALSE" )
  set ( BUILD_SHARED_LIBS OFF )
  set ( LIB_TYPE STATIC )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -static -fexceptions" )

  if ( MINGW AND WIN32 AND "${CMAKE_HOST_WIN32}" STREQUAL "")
    # This link options are put at the end of link command. Required for MinGW cross compilation.
    # There can be an error: "rsrc merge failure: duplicate leaf: type: 10 (VERSION) name: 1 lang: 409" => it is OK, win32 version information of libwinpthread-1 is skipped
    set ( CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -Wl,-Bstatic,--whole-archive -lpthread -Wl,--no-whole-archive" )

    # This link options are put at the beginning of link command.
    # Disadvantage of using linker flags => win32 version information of libwinpthread-1 are used in the output binary instead of win32 version information of main target
    #set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lpthread -Wl,--no-whole-archive" )
  endif()

endif()
message ( STATUS "Build with flagSHARED: ${STATUS_SHARED}" )

# Precompiled headers support
if ( "${FlagDefs}" MATCHES "flagPCH(;|$)" )
  if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4 )
        message ( WARNING
            "Precompiled headers are introduced with GCC 3.4.\n"
            "No support of the PCH in any earlier releases. (current version ${CMAKE_CXX_COMPILER_VERSION})." )
        remove_definitions ( -DflagPCH )
    endif()
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5 )
        message ( WARNING
            "There are some problems with precompiled headers in Clang version less 3.5.\n"
            "No support of the PCH in any earlier releases. (current version ${CMAKE_CXX_COMPILER_VERSION})." )
        remove_definitions ( -DflagPCH )
    endif()
  else()
    remove_definitions ( -DflagPCH )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

if ( "${FlagDefs}" MATCHES "flagPCH(;|$)" )
  message ( STATUS "Build with flagPCH: TRUE" )
else()
  message ( STATUS "Build with flagPCH: FALSE" )
endif()

# Set compiler options
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )

  if ( "${FlagDefs}" MATCHES "flagGNUC14(;|$)" )
    set ( EXTRA_GXX_FLAGS "${EXTRA_GXX_FLAGS} -std=c++14" )
  endif()

  if ( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9 OR CMAKE_COMPILER_IS_CLANG )
      set ( EXTRA_GXX_FLAGSS "${EXTRA_GXX_FLAGS} -fdiagnostics-color")
  endif()

  if ( MINGW )
      # Set the minimum supported (API) version to Windows 7
      # add_definitions(-DWINVER=0x0601)
      # add_definitions(-D_WIN32_WINNT=0x0601)
      # get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

      if ( "${FlagDefs}" MATCHES "flagDLL(;|$)" )
          set ( BUILD_SHARED_LIBS ON )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -shared" )
          string ( REGEX REPLACE "-static " "" CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} )
      endif()

      if ( "${FlagDefs}" MATCHES "flagGUI(;|$)" )
          list ( APPEND main_LINK_LIST mingw32 )
      endif()

      # The workaround to avoid 'error: duplicate symbol: std::__throw_bad_alloc()'
      if ( CMAKE_COMPILER_IS_CLANG AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0 )
          add_definitions ( -DflagUSEMALLOC )
          get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
      endif()

      if ( CMAKE_COMPILER_IS_GNUCC )
          # The optimalization might be broken on MinGW - remove optimalization flag (cross compile).
          #string ( REGEX REPLACE "-O2" "" EXTRA_GCC_FLAGS ${EXTRA_GCC_FLAGS} )

          if( "${FlagDefs}" MATCHES "flagGUI(;|$)" )
              list ( APPEND main_LINK_LIST mingw32 )
              set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mwindows" )
          else()
              set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mconsole" )
          endif()

          if( "${FlagDefs}" MATCHES "flagMT(;|$)" )
              set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mthreads" )
          endif()
      endif()

  endif()

  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${EXTRA_GXX_FLAGS} ${EXTRA_GCC_FLAGS}" )
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${BUILD_TYPE}} ${EXTRA_GCC_FLAGS}" )

  set ( CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_CXX_ARCHIVE_APPEND "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )

elseif ( MSVC )
  set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nologo" )
    
  if ( "${FlagDefs}" MATCHES "flagEVC(;|$)" )
      if ( NOT "${FlagDefs}" MATCHES "flagSH3(;|$)" AND NOT "${FlagDefs}" MATCHES "flagSH4(;|$)" )
          # disable stack checking
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Gs8192" )
      endif()
      # read-only string pooling, turn off exception handling
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GF -GX-" )
  elseif ( "${FlagDefs}" MATCHES "flagCLR(;|$)" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -EHac" )
  elseif ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)X64" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -EHsc" )
  else()
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GX" )
  endif()
	
  if ( ${CMAKE_BUILD_TYPE} STREQUAL DEBUG )
      set ( EXTRA_MSVC_FLAGS_Mx "d" )
  endif()
  if ( "${FlagDefs}" MATCHES "flagSHARED(;|$)" OR "${FlagDefs}" MATCHES "flagCLR(;|$)" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MD${EXTRA_MSVC_FLAGS_Mx}" )
  else()
      if ( "${FlagDefs}" MATCHES "flagMT(;|$)" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15|16|17|19)X64" )
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MT${EXTRA_MSVC_FLAGS_Mx}" )
      else()
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -ML${EXTRA_MSVC_FLAGS_Mx}" )
      endif()
  endif()

  #,5.01 needed to support WindowsXP
  if ( NOT "${FlagDefs}" MATCHES "(flagMSC(8|9|10|11|12|14|15|16|17|19)X64)" )
      set ( MSVC_LINKER_SUBSYSTEM ",5.01" )
  endif()

  if ( "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:windowsce,4.20 /ARMPADCODE -NODEFAULTLIB:\"oldnames.lib\"" )
  else()
      if ( "${FlagDefs}" MATCHES "flagGUI(;|$)" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:windows${MSVC_LINKER_SUBSYSTEM}" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:console${MSVC_LINKER_SUBSYSTEM}" )
      endif()
  endif()

  if ( "${FlagDefs}" MATCHES "flagDLL(;|$)" )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -dll" )
  endif()

  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${EXTRA_MSVC_FLAGS}" )
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${BUILD_TYPE}} ${EXTRA_MSVC_FLAGS}" )
endif()

# Function to generate precompiled header
function ( generate_pch TARGET_NAME PCH_FILE PCH_INCLUDE_DIRS )
    set ( PCH_OUTPUT_DIR ${PROJECT_PCH_DIR}/${TARGET_NAME} )
    get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
    get_filename_component ( TARGET_DIR ${PCH_FILE} PATH )

    file ( COPY ${PCH_FILE} DESTINATION ${PCH_OUTPUT_DIR} )

    # Prepare compile flag definition
    get_target_property ( COMPILE_FLAGS_LIST ${TARGET_NAME} COMPILE_FLAGS_LIST )
    string ( REGEX REPLACE ";" " " COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
    set ( compile_flags "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} ${COMPILE_FLAGS_LIST}" )

    # Add main target defined include directories
    get_directory_property ( include_directories DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} INCLUDE_DIRECTORIES )
    foreach ( include_dir ${include_directories} )
        list ( APPEND compile_flags "-I${include_dir}" )
    endforeach()

    # Add source directory of the precompiled header file - for quoted include files
    list ( APPEND compile_flags "-iquote${TARGET_DIR}" )

    # Add included directories of the external packages collected from defintions of all targets
    foreach ( include_dir ${PCH_INCLUDE_DIRS} )
        list ( APPEND compile_flags "-I${include_dir}" )
    endforeach()

    # Add target compile definitions
    get_target_property ( PCH_COMPILE_DEFINITIONS ${TARGET_NAME} PCH_COMPILE_DEFINITIONS )
    foreach ( compile_def ${PCH_COMPILE_DEFINITIONS} )
        list ( APPEND compile_flags "-D${compile_def}" )
    endforeach()

    list ( REMOVE_DUPLICATES compile_flags )
    separate_arguments ( compile_flags )

    # Prepare compilations options
    set ( PCH_BINARY_SUFFIX ".pch" )
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
        set ( PCH_BINARY_SUFFIX ".gch" )
    endif()

    set ( PCH_HEADER "${PCH_OUTPUT_DIR}/${PCH_NAME}" )
    set ( PCH_BINARY "${PCH_HEADER}${PCH_BINARY_SUFFIX}" )
    set ( PCH_COMPILE_PARAMS -x c++-header -o ${PCH_BINARY} ${PCH_HEADER} )

    # Generate precompiled header file
    add_custom_command ( OUTPUT ${PCH_BINARY}
        COMMAND ${CMAKE_CXX_COMPILER} ${compile_flags} ${PCH_COMPILE_PARAMS}
        COMMENT "PCH for the file ${PCH_HEADER}"
    )

    add_custom_target ( ${TARGET_NAME}_gch DEPENDS ${PCH_BINARY} )
    add_dependencies ( ${TARGET_NAME} ${TARGET_NAME}_gch )
endfunction()

# Function to create cpp source from icpp files
function ( create_cpps_from_icpps )
  file ( GLOB icpp_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.icpp" )
  foreach ( icppFile ${icpp_files} )
      set ( output_file "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/${icppFile}.cpp" )
      file ( WRITE "${output_file}" "#include \"${CMAKE_CURRENT_SOURCE_DIR}/${icppFile}\"\n" )
  endforeach()
endfunction()

# Function to create cpp source file from binary resource definition
function ( create_brc_source input_file output_file symbol_name compression symbol_append )
  if ( NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} )
      message ( FATAL_ERROR "Input file does not exist: ${CMAKE_CURRENT_SOURCE_DIR}/${input_file}" )
  endif()
  message ( STATUS "Creating cpp source file \"${output_file}\" from the binary resource \"${input_file}\"" )

  file ( REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )

  if ( ${compression} MATCHES "[bB][zZ]2" )
      find_program ( BZIP2_EXEC bzip2 )
      if ( NOT BZIP2_EXEC )
          message ( FATAL_ERROR "BZIP2 executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "bz2" )
      set ( COMMAND_COMPRESS ${BZIP2_EXEC} -k -f ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  elseif ( ${compression} MATCHES "[zZ][iI][pP]" )
      find_program ( ZIP_EXEC zip )
      if ( NOT ZIP_EXEC )
          message ( FATAL_ERROR "ZIP executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "zip" )
      set ( COMMAND_COMPRESS ${ZIP_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} ${symbol_name} )
  elseif ( ${compression} MATCHES "[lL][zZ][mM][aA]" )
      find_program ( LZMA_EXEC lzma )
      if ( NOT LZMA_EXEC )
          message ( FATAL_ERROR "LZMA executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "lzma" )
      set ( COMMAND_COMPRESS ${LZMA_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  elseif ( ${compression} MATCHES "[lL][zZ]4" )
      find_program ( LZ4_EXEC lz4c )
      if ( NOT LZ4_EXEC )
          message ( FATAL_ERROR "LZ4 executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "lz4" )
      set ( COMMAND_COMPRESS ${LZ4_EXEC} -f ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} )
  elseif ( ${compression} MATCHES "[zZ][sS][tT[dD]" )
      find_program ( ZSTD_EXEC zstd )
      if ( NOT ZSTD_EXEC )
          message ( FATAL_ERROR "ZSTD executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "zst" )
      set ( COMMAND_COMPRESS ${ZSTD_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} -o ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} )
  endif()

  file ( COPY ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
  get_filename_component ( input_file_name ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} NAME )
  file ( RENAME ${CMAKE_CURRENT_BINARY_DIR}/${input_file_name} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  if ( COMMAND_COMPRESS )
      execute_process ( COMMAND ${COMMAND_COMPRESS} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} OUTPUT_VARIABLE XXXX )
      file ( RENAME ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  endif()

  file ( READ ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} hex_string HEX )

  set ( CUR_INDEX 0 )
  string ( LENGTH "${hex_string}" CUR_LENGTH )
  math ( EXPR FILE_LENGTH "${CUR_LENGTH} / 2" )
  set ( ${hex_string} 0)

  string ( REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " hex_converted ${hex_string} )

  set ( output_string "static unsigned char ${symbol_name}_[] = {\n" )
  set ( output_string "${output_string} ${hex_converted}0x00 }\;\n\n" )
  set ( output_string "${output_string}unsigned char *${symbol_name} = ${symbol_name}_\;\n\n" )
  set ( output_string "${output_string}int ${symbol_name}_length = ${FILE_LENGTH}\;\n\n" )

  if ( ${symbol_append} MATCHES "append" )
      file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/${output_file} ${output_string} )
  else()
      file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/${output_file} ${output_string} )
  endif()
endfunction()

# Initialize definition flags (flags are used during targets compilation)
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
foreach( comp_def ${FlagDefs} )
    message ( STATUS "  initialize flag " ${comp_def} )
    set ( ${comp_def} 1 )
endforeach()

message ( STATUS "Project compilation flags: ${EXTRA_GCC_FLAGS}" )

# Include dependent directories of the project
add_subdirectory ( ./src/Complete ${CMAKE_CURRENT_BINARY_DIR}/Complete )
add_subdirectory ( ./src/EcsComplete ${CMAKE_CURRENT_BINARY_DIR}/EcsComplete )
add_subdirectory ( ./src/AudioCore ${CMAKE_CURRENT_BINARY_DIR}/AudioCore )
add_subdirectory ( ./src/Shadertoy ${CMAKE_CURRENT_BINARY_DIR}/Shadertoy )
add_subdirectory ( ./src/AtomLocal ${CMAKE_CURRENT_BINARY_DIR}/AtomLocal )
add_subdirectory ( ./src/AudioHost ${CMAKE_CURRENT_BINARY_DIR}/AudioHost )
add_subdirectory ( ./src/GuboLib ${CMAKE_CURRENT_BINARY_DIR}/GuboLib )
add_subdirectory ( ./src/IMidiFile ${CMAKE_CURRENT_BINARY_DIR}/IMidiFile )
add_subdirectory ( ./src/IMidiHw ${CMAKE_CURRENT_BINARY_DIR}/IMidiHw )
add_subdirectory ( ./src/SerialLib ${CMAKE_CURRENT_BINARY_DIR}/SerialLib )
add_subdirectory ( ./src/AtomHandle ${CMAKE_CURRENT_BINARY_DIR}/AtomHandle )
add_subdirectory ( ./src/Physics ${CMAKE_CURRENT_BINARY_DIR}/Physics )
add_subdirectory ( ./src/EcsLocal ${CMAKE_CURRENT_BINARY_DIR}/EcsLocal )
add_subdirectory ( ./src/EcsMinimal ${CMAKE_CURRENT_BINARY_DIR}/EcsMinimal )
add_subdirectory ( ./src/EcsAudioCore ${CMAKE_CURRENT_BINARY_DIR}/EcsAudioCore )
add_subdirectory ( ./src/EcsCtrl ${CMAKE_CURRENT_BINARY_DIR}/EcsCtrl )
add_subdirectory ( ./src/EcsVR ${CMAKE_CURRENT_BINARY_DIR}/EcsVR )
add_subdirectory ( ./src/EcsWin ${CMAKE_CURRENT_BINARY_DIR}/EcsWin )
add_subdirectory ( ./src/Local ${CMAKE_CURRENT_BINARY_DIR}/Local )
add_subdirectory ( ./src/Geometry ${CMAKE_CURRENT_BINARY_DIR}/Geometry )
add_subdirectory ( ./src/MidiFile ${CMAKE_CURRENT_BINARY_DIR}/MidiFile )
add_subdirectory ( ./src/Structural ${CMAKE_CURRENT_BINARY_DIR}/Structural )
add_subdirectory ( ./src/ParallelLib ${CMAKE_CURRENT_BINARY_DIR}/ParallelLib )
add_subdirectory ( ./src/IHolograph ${CMAKE_CURRENT_BINARY_DIR}/IHolograph )
add_subdirectory ( ./src/IGraphics ${CMAKE_CURRENT_BINARY_DIR}/IGraphics )
add_subdirectory ( ./src/GuboCore ${CMAKE_CURRENT_BINARY_DIR}/GuboCore )
add_subdirectory ( ./src/VirtualGui3D ${CMAKE_CURRENT_BINARY_DIR}/VirtualGui3D )
add_subdirectory ( ./src/ports/portmidi ${CMAKE_CURRENT_BINARY_DIR}/ports/portmidi )
add_subdirectory ( ./src/High ${CMAKE_CURRENT_BINARY_DIR}/High )
add_subdirectory ( ./src/SerialScript ${CMAKE_CURRENT_BINARY_DIR}/SerialScript )
add_subdirectory ( ./src/AtomAudio ${CMAKE_CURRENT_BINARY_DIR}/AtomAudio )
add_subdirectory ( ./src/EcsLib ${CMAKE_CURRENT_BINARY_DIR}/EcsLib )
add_subdirectory ( ./src/DesktopSuite ${CMAKE_CURRENT_BINARY_DIR}/DesktopSuite )
add_subdirectory ( ./src/EcsPhysics ${CMAKE_CURRENT_BINARY_DIR}/EcsPhysics )
add_subdirectory ( ./src/GraphLib ${CMAKE_CURRENT_BINARY_DIR}/GraphLib )
add_subdirectory ( ./src/AtomVR ${CMAKE_CURRENT_BINARY_DIR}/AtomVR )
add_subdirectory ( ./src/ports/DirectXTK ${CMAKE_CURRENT_BINARY_DIR}/ports/DirectXTK )
add_subdirectory ( ./alt/Core ${CMAKE_CURRENT_BINARY_DIR}/Core )
add_subdirectory ( ./alt/Draw ${CMAKE_CURRENT_BINARY_DIR}/Draw )
add_subdirectory ( ./src/SharedCore ${CMAKE_CURRENT_BINARY_DIR}/SharedCore )
add_subdirectory ( ./src/StaticInterface ${CMAKE_CURRENT_BINARY_DIR}/StaticInterface )
add_subdirectory ( ./src/ports/mikktspace ${CMAKE_CURRENT_BINARY_DIR}/ports/mikktspace )
add_subdirectory ( ./src/ports/tiny_gltf ${CMAKE_CURRENT_BINARY_DIR}/ports/tiny_gltf )
add_subdirectory ( ./src/ports/assimp ${CMAKE_CURRENT_BINARY_DIR}/ports/assimp )
add_subdirectory ( ./src/ParallelCore ${CMAKE_CURRENT_BINARY_DIR}/ParallelCore )
add_subdirectory ( ./src/IMedia ${CMAKE_CURRENT_BINARY_DIR}/IMedia )
add_subdirectory ( ./src/ports/hcidump ${CMAKE_CURRENT_BINARY_DIR}/ports/hcidump )
add_subdirectory ( ./src/LocalHMD ${CMAKE_CURRENT_BINARY_DIR}/LocalHMD )
add_subdirectory ( ./src/ports/MingwDx ${CMAKE_CURRENT_BINARY_DIR}/ports/MingwDx )
add_subdirectory ( ./src/SoftRend ${CMAKE_CURRENT_BINARY_DIR}/SoftRend )
add_subdirectory ( ./src/ports/glew ${CMAKE_CURRENT_BINARY_DIR}/ports/glew )
add_subdirectory ( ./src/ports/glext ${CMAKE_CURRENT_BINARY_DIR}/ports/glext )
add_subdirectory ( ./alt/CtrlCore ${CMAKE_CURRENT_BINARY_DIR}/CtrlCore )
add_subdirectory ( ./src/SerialCore ${CMAKE_CURRENT_BINARY_DIR}/SerialCore )
add_subdirectory ( ./src/Backend ${CMAKE_CURRENT_BINARY_DIR}/Backend )
add_subdirectory ( ./src/ISynth ${CMAKE_CURRENT_BINARY_DIR}/ISynth )
add_subdirectory ( ./src/IEffect ${CMAKE_CURRENT_BINARY_DIR}/IEffect )
add_subdirectory ( ./src/EcsCore ${CMAKE_CURRENT_BINARY_DIR}/EcsCore )
add_subdirectory ( ./src/HighLib ${CMAKE_CURRENT_BINARY_DIR}/HighLib )
add_subdirectory ( ./alt/CtrlLib ${CMAKE_CURRENT_BINARY_DIR}/CtrlLib )
add_subdirectory ( ./src/VirtualGui/Atom ${CMAKE_CURRENT_BINARY_DIR}/VirtualGui/Atom )
add_subdirectory ( ./src/LocalCtrl ${CMAKE_CURRENT_BINARY_DIR}/LocalCtrl )
add_subdirectory ( ./src/SoftPhys ${CMAKE_CURRENT_BINARY_DIR}/SoftPhys )
add_subdirectory ( ./src/AtomMinimal ${CMAKE_CURRENT_BINARY_DIR}/AtomMinimal )
add_subdirectory ( ./src/ports/bz2lib ${CMAKE_CURRENT_BINARY_DIR}/ports/bz2lib )
add_subdirectory ( ./src/RTTI ${CMAKE_CURRENT_BINARY_DIR}/RTTI )
add_subdirectory ( ./src/ports/md5 ${CMAKE_CURRENT_BINARY_DIR}/ports/md5 )
add_subdirectory ( ./src/ports/MingwThreads ${CMAKE_CURRENT_BINARY_DIR}/ports/MingwThreads )
add_subdirectory ( ./src/ports/modernjson ${CMAKE_CURRENT_BINARY_DIR}/ports/modernjson )
add_subdirectory ( ./src/ports/stb ${CMAKE_CURRENT_BINARY_DIR}/ports/stb )
add_subdirectory ( ./src/ports/utf8 ${CMAKE_CURRENT_BINARY_DIR}/ports/utf8 )
add_subdirectory ( ./src/ports/poly2tri ${CMAKE_CURRENT_BINARY_DIR}/ports/poly2tri )
add_subdirectory ( ./src/ports/irrxml ${CMAKE_CURRENT_BINARY_DIR}/ports/irrxml )
add_subdirectory ( ./src/ports/rapidjson ${CMAKE_CURRENT_BINARY_DIR}/ports/rapidjson )
add_subdirectory ( ./src/ports/unzip ${CMAKE_CURRENT_BINARY_DIR}/ports/unzip )
add_subdirectory ( ./alt/plugin/z ${CMAKE_CURRENT_BINARY_DIR}/plugin/z )
add_subdirectory ( ./src/ParallelMach ${CMAKE_CURRENT_BINARY_DIR}/ParallelMach )
add_subdirectory ( ./src/SerialMach ${CMAKE_CURRENT_BINARY_DIR}/SerialMach )
add_subdirectory ( ./src/SoftInstru ${CMAKE_CURRENT_BINARY_DIR}/SoftInstru )
add_subdirectory ( ./src/SoftSynth ${CMAKE_CURRENT_BINARY_DIR}/SoftSynth )
add_subdirectory ( ./src/ports/fluidlite ${CMAKE_CURRENT_BINARY_DIR}/ports/fluidlite )
add_subdirectory ( ./src/ports/lilv ${CMAKE_CURRENT_BINARY_DIR}/ports/lilv )
add_subdirectory ( ./src/Agent ${CMAKE_CURRENT_BINARY_DIR}/Agent )
add_subdirectory ( ./src/EcsMach ${CMAKE_CURRENT_BINARY_DIR}/EcsMach )
add_subdirectory ( ./src/HighAnim ${CMAKE_CURRENT_BINARY_DIR}/HighAnim )
add_subdirectory ( ./src/VirtualGui ${CMAKE_CURRENT_BINARY_DIR}/VirtualGui )
add_subdirectory ( ./src/IAudio ${CMAKE_CURRENT_BINARY_DIR}/IAudio )
add_subdirectory ( ./src/IVolumetric ${CMAKE_CURRENT_BINARY_DIR}/IVolumetric )
add_subdirectory ( ./src/ICamera ${CMAKE_CURRENT_BINARY_DIR}/ICamera )
add_subdirectory ( ./src/IAudioFileOut ${CMAKE_CURRENT_BINARY_DIR}/IAudioFileOut )
add_subdirectory ( ./src/IHal ${CMAKE_CURRENT_BINARY_DIR}/IHal )
add_subdirectory ( ./src/IScreen ${CMAKE_CURRENT_BINARY_DIR}/IScreen )
add_subdirectory ( ./src/LocalPlan ${CMAKE_CURRENT_BINARY_DIR}/LocalPlan )
add_subdirectory ( ./src/ports/serd ${CMAKE_CURRENT_BINARY_DIR}/ports/serd )
add_subdirectory ( ./src/ports/sord ${CMAKE_CURRENT_BINARY_DIR}/ports/sord )
add_subdirectory ( ./src/ports/sratom ${CMAKE_CURRENT_BINARY_DIR}/ports/sratom )
add_subdirectory ( ./src/ports/zix ${CMAKE_CURRENT_BINARY_DIR}/ports/zix )
add_subdirectory ( ./alt/GLDraw ${CMAKE_CURRENT_BINARY_DIR}/GLDraw )
add_subdirectory ( ./src/ports/portaudio ${CMAKE_CURRENT_BINARY_DIR}/ports/portaudio )
add_subdirectory ( ./reference/Shell ${CMAKE_CURRENT_BINARY_DIR}/Shell )

# Creation of the file build_info.h
set ( BUILD_INFO_H ${PROJECT_INC_DIR}/build_info.h )
string ( TIMESTAMP bmYEAR %Y )
string ( TIMESTAMP bmMONTH %m )
string ( TIMESTAMP bmDAY %d )
string ( TIMESTAMP bmHOUR %H )
string ( TIMESTAMP bmMINUTE %M )
string ( TIMESTAMP bmSECOND %S )
string ( REGEX REPLACE "^0(.*)" \\1 bmMONTH ${bmMONTH} )
string ( REGEX REPLACE "^0(.*)" \\1 bmDAY ${bmDAY} )
string ( REGEX REPLACE "^0(.*)" \\1 bmHOUR ${bmHOUR} )
string ( REGEX REPLACE "^0(.*)" \\1 bmMINUTE ${bmMINUTE} )
string ( REGEX REPLACE "^0(.*)" \\1 bmSECOND ${bmSECOND} )
cmake_host_system_information ( RESULT bmHOSTNAME QUERY HOSTNAME )
file ( WRITE  ${BUILD_INFO_H} "#define bmYEAR ${bmYEAR}\n#define bmMONTH ${bmMONTH}\n#define bmDAY ${bmDAY}\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmHOUR ${bmHOUR}\n#define bmMINUTE ${bmMINUTE}\n#define bmSECOND ${bmSECOND}\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmTIME Time(${bmYEAR}, ${bmMONTH}, ${bmDAY}, ${bmHOUR}, ${bmMINUTE}, ${bmSECOND})\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmMACHINE \"${bmHOSTNAME}\"\n" )
if ( WIN32 )
  file ( APPEND ${BUILD_INFO_H} "#define bmUSER \"$ENV{USERNAME}\"\n" )
else()
  file ( APPEND ${BUILD_INFO_H} "#define bmUSER \"$ENV{USER}\"\n" )
endif()

find_package(Subversion)
if ( SUBVERSION_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.svn" )
  Subversion_WC_INFO(${CMAKE_SOURCE_DIR} SVN)
endif()

find_package(Git)
if ( GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git" )
  # Get the current working branch
  execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Get the latest abbreviated commit hash of the working branch
  execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Get remote tracking of actual branch
  execute_process(
    COMMAND git config --local branch.${GIT_BRANCH}.remote
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REMOTE_TRACKING
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Get remote tracking URL of actual branch
  execute_process(
    COMMAND git config --local remote.${GIT_REMOTE_TRACKING}.url
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REMOTE_URL
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if ( GIT_COMMIT_HASH )
  file (APPEND ${BUILD_INFO_H} "#define bmGIT_REVISION \"${GIT_COMMIT_HASH}\"\n" )
  file (APPEND ${BUILD_INFO_H} "#define bmGIT_BRANCH \"${GIT_BRANCH}\"\n" )
  file (APPEND ${BUILD_INFO_H} "#define bmGIT_URL \"${GIT_REMOTE_URL}\"\n" )
elseif ( SVN_WC_REVISION )
  file (APPEND ${BUILD_INFO_H} "#define bmSVN_REVISION \"${SVN_WC_REVISION}\"\n" )
endif()

# Collect icpp files
file ( GLOB_RECURSE cpp_ini_files "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/*.icpp.cpp" )

# Collect windows resource config file
if ( WIN32 )
  file ( GLOB rc_file "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/*.rc" )
endif()

# Main program definition
file ( WRITE ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp "" )
if ( "${FlagDefs}" MATCHES "(flagSO)(;|$)" )
  add_library ( Shell-bin ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp ${rc_file} ${cpp_ini_files} )
  if ( WIN32 )
    include ( GenerateExportHeader )
    generate_export_header ( Shell-bin
        BASE_NAME Shell-bin
        EXPORT_MACRO_NAME Shell-bin_EXPORT
        EXPORT_FILE_NAME Shell-bin_Export.h
        STATIC_DEFINE Shell-bin_BUILT_AS_STATIC
    )
  endif()
else()
  add_executable ( Shell-bin ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp ${rc_file} ${cpp_ini_files} )
endif()

# Main program dependecies
set ( Shell_DEPEND_LIST "Shell-lib;Agent-lib;AtomAudio-lib;AtomHandle-lib;AtomLocal-lib;AtomMinimal-lib;AtomVR-lib;AudioCore-lib;AudioHost-lib;Backend-lib;Complete-lib;Core-lib;CtrlCore-lib;CtrlLib-lib;DesktopSuite-lib;Draw-lib;EcsAudioCore-lib;EcsComplete-lib;EcsCore-lib;EcsCtrl-lib;EcsLib-lib;EcsLocal-lib;EcsMach-lib;EcsMinimal-lib;EcsPhysics-lib;EcsVR-lib;EcsWin-lib;GLDraw-lib;Geometry-lib;GraphLib-lib;GuboCore-lib;GuboLib-lib;High-lib;HighAnim-lib;HighLib-lib;IAudio-lib;IAudioFileOut-lib;ICamera-lib;IEffect-lib;IGraphics-lib;IHal-lib;IHolograph-lib;IMedia-lib;IMidiFile-lib;IMidiHw-lib;IScreen-lib;ISynth-lib;IVolumetric-lib;Local-lib;LocalCtrl-lib;LocalHMD-lib;LocalPlan-lib;MidiFile-lib;ParallelCore-lib;ParallelLib-lib;ParallelMach-lib;Physics-lib;RTTI-lib;SerialCore-lib;SerialLib-lib;SerialMach-lib;SerialScript-lib;Shadertoy-lib;SharedCore-lib;SoftInstru-lib;SoftPhys-lib;SoftRend-lib;SoftSynth-lib;StaticInterface-lib;Structural-lib;VirtualGui-lib;VirtualGui_Atom-lib;VirtualGui3D-lib;plugin_z-lib;ports_DirectXTK-lib;ports_MingwDx-lib;ports_MingwThreads-lib;ports_assimp-lib;ports_bz2lib-lib;ports_fluidlite-lib;ports_glew-lib;ports_glext-lib;ports_hcidump-lib;ports_irrxml-lib;ports_lilv-lib;ports_md5-lib;ports_mikktspace-lib;ports_modernjson-lib;ports_poly2tri-lib;ports_portaudio-lib;ports_portmidi-lib;ports_rapidjson-lib;ports_serd-lib;ports_sord-lib;ports_sratom-lib;ports_stb-lib;ports_tiny_gltf-lib;ports_unzip-lib;ports_utf8-lib;ports_zix-lib;" )

add_dependencies ( Shell-bin ${Shell_DEPEND_LIST} )
if ( DEFINED MAIN_TARGET_LINK_FLAGS )
  set_target_properties ( Shell-bin PROPERTIES LINK_FLAGS ${MAIN_TARGET_LINK_FLAGS} )
endif()

# Precompiled headers processing
if ( "${FlagDefs}" MATCHES "flagPCH(;|$)" )
  if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
    # Collect included directories of the external packages from all targets
    foreach ( target ${Shell_DEPEND_LIST} )
        get_target_property ( PCH_INCLUDE_LIST ${target} PCH_INCLUDE_LIST )
        list ( APPEND PCH_INCLUDE_DIRS ${PCH_INCLUDE_LIST} )
    endforeach()
    if ( PCH_INCLUDE_DIRS )
        list ( REMOVE_DUPLICATES PCH_INCLUDE_DIRS )
    endif()

    foreach ( target ${Shell_DEPEND_LIST} )
        get_target_property ( PCH_FILE ${target} PCH_FILE )
        if ( PCH_FILE )
            generate_pch ( ${target} ${PCH_FILE} "${PCH_INCLUDE_DIRS}" )
        endif()
    endforeach()
  endif()
endif()

# Main program link
target_link_libraries ( Shell-bin ${main_LINK_LIST} ${Shell_DEPEND_LIST} ${PROJECT_EXTRA_LINK_FLAGS} )
if ( TARGET_RENAME )
  set_target_properties ( Shell-bin PROPERTIES OUTPUT_NAME ${TARGET_RENAME} )
else()
  set_target_properties ( Shell-bin PROPERTIES OUTPUT_NAME Shell )
endif()
