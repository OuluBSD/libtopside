# CMakeLists.txt generated Mon Nov 21 21:46:11 EET 2022
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

# library(LINUX USBONLY) hidapi-libusb;
if ((DEFINED flagLINUX AND DEFINED flagUSBONLY))
  list ( APPEND LINK_LIST hidapi-libusb )
endif()

# library(LINUX) hidapi-hidraw;
if ((DEFINED flagLINUX))
  list ( APPEND LINK_LIST hidapi-hidraw )
endif()

# library(FREEBSD) hidapi;
if ((DEFINED flagFREEBSD))
  list ( APPEND LINK_LIST hidapi )
endif()

list ( APPEND HEADER_LIST
      README.md
      LocalHMD.h
      Daemon.h
      System.h
      Public.h
      Internal.h
      Hid.h
      Platform.h
      Shaders.h
      Utils.h
      Log.h
      Fusion.h
      ConfigKey.h
      Wmr.h
      Psvr.h
      Android.h
      Math.h
      Miniz.h
      NxJson.h
)

list ( APPEND SOURCE_LIST_C
      Miniz.c
      NxJson.c
)

list ( APPEND SOURCE_LIST_CPP
      LocalHMD.cpp
      Daemon.cpp
      System.cpp
      Internal.cpp
      PlatformPosix.cpp
      PlatformWin32.cpp
      Shaders.cpp
      Fusion.cpp
      Dummy.cpp
      Wmr.cpp
      WmrPacket.cpp
      WmrController.cpp
      Psvr.cpp
      PsvrPacket.cpp
      Android.cpp
      Math.cpp
)

list ( APPEND LocalHMD_DEPEND_LIST
      Geometry-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( LocalHMD-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( LocalHMD-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET LocalHMD-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( LocalHMD_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( LocalHMD-lib ${LocalHMD_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( LocalHMD-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( LocalHMD-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( LocalHMD-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( LocalHMD-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/LocalHMD-lib )
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
      set_target_properties ( LocalHMD-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

