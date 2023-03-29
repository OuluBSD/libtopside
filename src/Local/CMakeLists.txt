# CMakeLists.txt generated Wed Mar 29 15:12:51 EEST 2023
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

list ( APPEND HEADER_LIST
      Local.h
      Before.h
      Compat.h
      Defs.h
      Types.h
      Chrono.h
      Recycler.h
      LinkedList.h
      TypeTraits.h
      Visitor.h
      Ref.h
      Exchange.h
      Realtime.h
      Interface.h
      Index.h
      Container.h
      RTuple.h
      StringUtil.h
      Util.h
      Process.h
      Math.h
      Crypto.h
      Neural.h
      CLI.h
      DCT.h
      GeneticOptimizer.h
      Version.h
      Coordinate.h
      Tokenizer.h
      ECS.h
      Upp.h
      FFT.h
      Record.h
      Color.h
      UnitTest.h
      Image.h
      Geom.h
      Audio.h
      Midi.h
      Html.h
      Url.h
      Debugging.h
      Draw2D.h
      Draw3D.h
      GeomInteraction.h
      ProgDraw.h
      ProgPainter.h
      Workspace.h
      Ctrl.h
      Ctrl.inl
      GEnums.h
      Daemon.h
      Network.h
)

list ( APPEND SOURCE_LIST_CPP
      Local.cpp
      Types.cpp
      Visitor.cpp
      Ref.cpp
      Exchange.cpp
      Index.cpp
      Container.cpp
      Util.cpp
      Process.cpp
      Math.cpp
      FastMath.cpp
      Crypto.cpp
      Neural.cpp
      CLI.cpp
      DCT.cpp
      Coordinate.cpp
      Tokenizer.cpp
      Upp.cpp
      FFT1.cpp
      FFT2.cpp
      Record.cpp
      Color.cpp
      UnitTest.cpp
      Image.cpp
      Geom.cpp
      Audio.cpp
      Midi.cpp
      Html.cpp
      Url.cpp
      Draw3D.cpp
      Debugging.cpp
      GIBase.cpp
      GI2D.cpp
      GI3D.cpp
      ProgDraw.cpp
      ProgPainter.cpp
      Graphics.cpp
      Daemon.cpp
      Network.cpp
)

list ( APPEND Local_DEPEND_LIST
      Core-lib
      Draw-lib
      SharedCore-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( Local-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( Local-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET Local-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( Local_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( Local-lib ${Local_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( Local-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( Local-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( Local-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( Local-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/Local-lib )
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
      set_target_properties ( Local-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

