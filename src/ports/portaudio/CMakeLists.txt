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

# options(BUILDER_OPTION) NOWARNINGS;
if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -w")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -w")
elseif ( MSVC )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
endif()

# library(WIN32) "User32 Advapi32 Winmm Ole32";
if ((WIN32))
  list ( APPEND LINK_LIST User32 Advapi32 Winmm Ole32 )
endif()

# library(LINUX) asound;
if ((DEFINED flagLINUX))
  list ( APPEND LINK_LIST asound )
endif()

list ( APPEND HEADER_LIST
      portaudio.h
      defs.h
      pa_allocation.h
      pa_converters.h
      pa_cpuload.h
      pa_debugprint.h
      pa_dither.h
      pa_endianness.h
      pa_gitrevision.h
      pa_hostapi.h
      pa_memorybarrier.h
      pa_process.h
      pa_ringbuffer.h
      pa_stream.h
      pa_trace.h
      pa_types.h
      pa_util.h
      iasiothiscallresolver.h
      pa_mac_core_blocking.h
      pa_mac_core_internal.h
      pa_mac_core_utilities.h
      pa_win_ds_dynlink.h
      audioclient.h
      devicetopology.h
      endpointvolume.h
      functiondiscoverykeys.h
      ks.h
      ksguid.h
      ksmedia.h
      ksproxy.h
      ksuuids.h
      mmdeviceapi.h
      propkeydef.h
      propsys.h
      rpcsal.h
      sal.h
      structuredquery.h
      pa_unix_util.h
      pa_win_coinitialize.h
      pa_win_wdmks_utils.h
      pa_x86_plain_converters.h
      pa_asio.h
      pa_jack.h
      pa_linux_alsa.h
      pa_mac_core.h
      pa_win_ds.h
      pa_win_wasapi.h
      pa_win_waveformat.h
      pa_win_wdmks.h
      pa_win_wmme.h
)

list ( APPEND SOURCE_LIST_C
      pa_allocation.c
      pa_converters.c
      pa_cpuload.c
      pa_debugprint.c
      pa_dither.c
      pa_front.c
      pa_process.c
      pa_ringbuffer.c
      pa_stream.c
      pa_trace.c
      pa_linux_alsa.c
      pa_linux_asihpi.c
      pa_mac_core.c
      pa_mac_core_blocking.c
      pa_mac_core_old.c
      pa_mac_core_utilities.c
      pa_win_ds.c
      pa_win_ds_dynlink.c
      pa_jack.c
      pa_unix_oss.c
      recplay.c
      pa_hostapi_skeleton.c
      pa_win_wasapi.c
      pa_win_wdmks.c
      pa_win_wmme.c
      pa_unix_hostapis.c
      pa_unix_util.c
      pa_win_coinitialize.c
      pa_win_hostapis.c
      pa_win_util.c
      pa_win_waveformat.c
      pa_win_wdmks_utils.c
      pa_x86_plain_converters.c
)

list ( APPEND SOURCE_LIST_CPP
      iasiothiscallresolver.cpp
      pa_asio.cpp
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( ports_portaudio-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( ports_portaudio-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET ports_portaudio-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( ports_portaudio_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( ports_portaudio-lib ${ports_portaudio_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( ports_portaudio-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( ports_portaudio-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( ports_portaudio-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( ports_portaudio-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/ports_portaudio-lib )
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
      set_target_properties ( ports_portaudio-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

