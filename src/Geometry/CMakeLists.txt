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

# uses(BUILTIN_ASSIMP | MSC | LINUX) ports/assimp;
if ((DEFINED flagBUILTIN_ASSIMP OR DEFINED flagMSC OR DEFINED flagLINUX))
  list ( APPEND Geometry_DEPEND_LIST ports_assimp-lib )
endif()

# library(!BUILTIN_ASSIMP & POSIX & !LINUX) assimp;
if ((NOT DEFINED flagBUILTIN_ASSIMP AND DEFINED flagPOSIX AND NOT DEFINED flagLINUX))
  list ( APPEND LINK_LIST assimp )
endif()

# library(!BUILTIN_ASSIMP & WIN32 & (CLANG | GCC)) libassimp.dll.a;
if ((NOT DEFINED flagBUILTIN_ASSIMP AND WIN32) AND (DEFINED flagCLANG OR DEFINED flagGCC))
  list ( APPEND LINK_LIST libassimp.dll.a )
endif()

list ( APPEND HEADER_LIST
      Geometry.h
      Common.h
      Matrix.h
      Matrix.inl
      Util.h
      GeomCommon.h
      Geom2D.h
      Geom3D.h
      Quadtree.h
      Octree.h
      GeomTypes.h
      Material.h
      Mesh.h
      Model.h
      ModelBuilder.h
      Draw.h
      Frustum.h
      Compare.h
      Camera.h
      Pointcloud.h
      MeshTracker.h
      Uncamera.h
      Vr.h
      ModelPainter.h
      ModelDraw.h
)

list ( APPEND SOURCE_LIST_CPP
      Matrix.cpp
      Util.cpp
      Geom2D.cpp
      Geom3D.cpp
      Quadtree.cpp
      Octree.cpp
      GeomTypes.cpp
      BBox.cpp
      Material.cpp
      Mesh.cpp
      Model.cpp
      ModelBuilder.cpp
      Draw.cpp
      Frustum.cpp
      Compare.cpp
      Camera.cpp
      Pointcloud.cpp
      MeshTracker.cpp
      Uncamera.cpp
      Vr.cpp
      ModelPainter.cpp
      ModelDraw.cpp
)

list ( APPEND Geometry_DEPEND_LIST
      Local-lib
      ports_tiny_gltf-lib
      ports_mikktspace-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( Geometry-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( Geometry-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET Geometry-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( Geometry_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( Geometry-lib ${Geometry_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( Geometry-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( Geometry-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( Geometry-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( Geometry-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/Geometry-lib )
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
      set_target_properties ( Geometry-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

