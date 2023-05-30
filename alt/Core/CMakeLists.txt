# CMakeLists.txt generated Tue May 30 16:49:04 EEST 2023
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

# uses(GCC WIN32) ports/MingwThreads;
if ((DEFINED flagGCC AND WIN32))
  list ( APPEND Core_DEPEND_LIST ports_MingwThreads-lib )
endif()

# library(WIN32) "shlwapi comdlg32";
if ((WIN32))
  list ( APPEND LINK_LIST shlwapi comdlg32 )
endif()

# library(WIN32) Ws2_32;
if ((WIN32))
  list ( APPEND LINK_LIST Ws2_32 )
endif()

# library(POSIX & !EMSCRIPTEN) "pthread crypto bz2";
if ((DEFINED flagPOSIX AND NOT DEFINED flagEMSCRIPTEN))
  list ( APPEND LINK_LIST pthread crypto bz2 )
endif()

# library(WIN32 & (CLANG|GCC)) crypto;
if ((WIN32) AND (DEFINED flagCLANG OR DEFINED flagGCC))
  list ( APPEND LINK_LIST crypto )
endif()

# library(WIN32 & (CLANG|GCC) & MSYS2) "bz2 z iconv";
if ((WIN32) AND (DEFINED flagCLANG OR DEFINED flagGCC) AND (DEFINED flagMSYS2))
  list ( APPEND LINK_LIST bz2 z iconv )
endif()

# library(WIN32 & MSC & !DEBUG & UPPLIB) "libcryptoMT libsslMT Advapi32 User32";
if ((WIN32 AND DEFINED flagMSC AND NOT DEFINED flagDEBUG AND DEFINED flagUPPLIB))
  list ( APPEND LINK_LIST libcryptoMT libsslMT Advapi32 User32 )
endif()

# library(WIN32 & MSC & DEBUG & UPPLIB) "libcryptoMTd libsslMTd Advapi32 User32";
if ((WIN32 AND DEFINED flagMSC AND DEFINED flagDEBUG AND DEFINED flagUPPLIB))
  list ( APPEND LINK_LIST libcryptoMTd libsslMTd Advapi32 User32 )
endif()

# library(WIN32) "Userenv Shell32";
if ((WIN32))
  list ( APPEND LINK_LIST Userenv Shell32 )
endif()

# library(WIN32 & MSC) "libcrypto libssl Advapi32 User32";
if ((WIN32 AND DEFINED flagMSC))
  list ( APPEND LINK_LIST libcrypto libssl Advapi32 User32 )
endif()

# Precompiled headers file
set ( PCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Core.h )

list ( APPEND HEADER_LIST
      TODO.txt
      Core.h
      Core0.h
      config.h
      Defs.h
      Macros.h
      Fn.h
      Ops.h
      Atomic.h
      Mt.h
      Heap.h
      String_.h
      StrUtil.h
      SplitMerge.h
      CharSet.h
      Path.h
      App.h
      Tuple.h
      Stream.h
      Util.h
      Sort.h
      LocalProcess.h
      t_.h
      Algo.h
      Topt.h
      Vcont.h
      Function.h
      Callback.h
      CallbackN.i
      CallbackNP.i
      CallbackR.i
      Gate.h
      TimeDate.h
      Complex.h
      Color.h
      Value.h
      Gtypes.h
      i18n.h
      Parser.h
      Uuid.h
      Hash.h
      Ptr.h
      JSON.h
      Inet.h
      Http.h
)

list ( APPEND SOURCE_LIST_CPP
      Core.cpp
      Cpu.cpp
      Mt.cpp
      StringInline.cpp
      StringTmpl.cpp
      String.cpp
      StrUtil.cpp
      SplitMerge.cpp
      CharSet.cpp
      Path.cpp
      Stream.cpp
      Util.cpp
      Vcont.cpp
      Callback.cpp
      TimeDate.cpp
      Color.cpp
      Value.cpp
      Gtypes.cpp
      i18n.cpp
      Parser.cpp
      Uuid.cpp
      JSON.cpp
      Socket.cpp
      Http.cpp
)

list ( APPEND Core_DEPEND_LIST
      ports_bz2lib-lib
      RTTI-lib
      SharedCore-lib
      ports_md5-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( Core-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( Core-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET Core-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( Core_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( Core-lib ${Core_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( Core-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( Core-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( Core-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( Core-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/Core-lib )
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
      set_target_properties ( Core-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

