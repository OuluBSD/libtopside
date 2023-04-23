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

# uses(LINUX) ports/hcidump;
if ((DEFINED flagLINUX))
  list ( APPEND IHolograph_DEPEND_LIST ports_hcidump-lib )
endif()

# uses(LOCALHMD) LocalHMD;
if ((DEFINED flagLOCALHMD))
  list ( APPEND IHolograph_DEPEND_LIST LocalHMD-lib )
endif()

# library(LINUX & OPENHMD) "openhmd hidapi-libusb";
if ((DEFINED flagLINUX AND DEFINED flagOPENHMD))
  list ( APPEND LINK_LIST openhmd hidapi-libusb )
endif()

list ( APPEND HEADER_LIST
      IHolograph.h
      IfaceFuncs.inl
)

list ( APPEND SOURCE_LIST_CPP
      OpenHMD.cpp
      LocalHMD.cpp
      RemoteVRServer.cpp
      DevUsb.cpp
      DevBluetooth.cpp
      OpenVR.cpp
)

list ( APPEND IHolograph_DEPEND_LIST
      ParallelLib-lib
      IMedia-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( IHolograph-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( IHolograph-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET IHolograph-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( IHolograph_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( IHolograph-lib ${IHolograph_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( IHolograph-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( IHolograph-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( IHolograph-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( IHolograph-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/IHolograph-lib )
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
      set_target_properties ( IHolograph-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

