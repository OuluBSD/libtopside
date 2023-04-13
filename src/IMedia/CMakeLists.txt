# CMakeLists.txt generated Fri Apr 14 01:52:15 EEST 2023
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

# library(FFMPEG) "swscale avcodec avformat avutil swresample avdevice avfilter";
if ((DEFINED flagFFMPEG))
  list ( APPEND LINK_LIST swscale avcodec avformat avutil swresample avdevice avfilter )
endif()

# library(OPENCV & POSIX) v4l2;
if ((DEFINED flagOPENCV AND DEFINED flagPOSIX))
  list ( APPEND LINK_LIST v4l2 )
endif()

# library(OPENCV & POSIX) "opencv_core opencv_imgproc opencv_highgui opencv_videoio opencv_shape";
if ((DEFINED flagOPENCV AND DEFINED flagPOSIX))
  list ( APPEND LINK_LIST opencv_core opencv_imgproc opencv_highgui opencv_videoio opencv_shape )
endif()

# library(OPENCV & WIN32 & DEBUG) opencv_world454d;
if ((DEFINED flagOPENCV AND WIN32 AND DEFINED flagDEBUG))
  list ( APPEND LINK_LIST opencv_world454d )
endif()

# library(OPENCV & WIN32 & !DEBUG) opencv_world454;
if ((DEFINED flagOPENCV AND WIN32 AND NOT DEFINED flagDEBUG))
  list ( APPEND LINK_LIST opencv_world454 )
endif()

list ( APPEND HEADER_LIST
      IMedia.h
      Types.h
      MediaAtomBase.h
      FileIn.h
      Audio.h
      Video.h
      Media.h
      DeviceManager_V4L2.h
      DeviceManager_Win32.h
      Capture_DShow.h
      Capture_OpenCV.h
      Capture_V4L2.h
)

list ( APPEND SOURCE_LIST_CPP
      Types.cpp
      MediaAtomBase.cpp
      FileIn.cpp
      Audio.cpp
      Video.cpp
      Media.cpp
      DeviceManager_V4L2.cpp
      DeviceManager_Win32.cpp
      Capture_DShow.cpp
      Capture_OpenCV.cpp
      Capture_V4L2.cpp
)

list ( APPEND IMedia_DEPEND_LIST
      ParallelLib-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( IMedia-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( IMedia-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET IMedia-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( IMedia_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( IMedia-lib ${IMedia_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( IMedia-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( IMedia-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( IMedia-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( IMedia-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/IMedia-lib )
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
      set_target_properties ( IMedia-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

