# CMakeLists.txt generated Wed Apr  5 12:23:14 EEST 2023
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

# library(SDL2 POSIX) "SDL2 SDL2main GL";
if ((DEFINED flagSDL2 AND DEFINED flagPOSIX))
  list ( APPEND LINK_LIST SDL2 SDL2main GL )
endif()

# library(SDL2 WIN32 MSC) "SDL2.lib OpenGL32.lib";
if ((DEFINED flagSDL2 AND WIN32 AND DEFINED flagMSC))
  list ( APPEND LINK_LIST SDL2.lib OpenGL32.lib )
endif()

# library(SDL2 WIN32 (GCC | CLANG)) "SDL2.lib SDL2main.lib  opengl32";
if ((DEFINED flagSDL2 AND WIN32) AND (DEFINED flagGCC OR DEFINED flagCLANG))
  list ( APPEND LINK_LIST SDL2.lib SDL2main.lib opengl32 )
endif()

# pkg_config(SDL2 !MSC) sdl2;
if ((DEFINED flagSDL2 AND NOT DEFINED flagMSC))
  find_package ( PkgConfig REQUIRED )
  pkg_check_modules ( SDL2 REQUIRED sdl2)
  if ( SDL2_FOUND )
      list ( APPEND INCLUDE_LIST ${SDL2_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${SDL2_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
endif()

list ( APPEND HEADER_LIST
      Atom.h
)

list ( APPEND SOURCE_LIST_CPP
      Window.cpp
      Draw.cpp
      Keys.cpp
      Event.cpp
      Cursor.cpp
)

list ( APPEND VirtualGui_Atom_DEPEND_LIST
      VirtualGui-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( VirtualGui_Atom-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( VirtualGui_Atom-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET VirtualGui_Atom-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( VirtualGui_Atom_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( VirtualGui_Atom-lib ${VirtualGui_Atom_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( VirtualGui_Atom-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( VirtualGui_Atom-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( VirtualGui_Atom-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( VirtualGui_Atom-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/VirtualGui_Atom-lib )
  set ( PCH_HEADER ${PCH_DIR}/${PCH_NAME} )
  if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
      if ( ${CMAKE_VERBOSE_MAKEFILE} EQUAL 1 )
        set ( PCH_INCLUDE_PARAMS " -H -Winvalid-pch -include ${PCH_HEADER}" )
      else()
        set ( PCH_INCLUDE_PARAMS " -Winvalid-pch -include ${PCH_HEADER}" )
      endif()
  endif()
  if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
      set ( PCH_INCLUDE_PARAMS " -Winvalid-pch -include-pch ${PCH_HEADER}.pch" )
  endif()
  if ( MSVC )
      set_target_properties ( VirtualGui_Atom-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

