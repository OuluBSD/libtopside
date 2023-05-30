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

# append library "ole32 oleaut32 Kernel32";
  list ( APPEND LINK_LIST ole32 oleaut32 Kernel32 )

list ( APPEND HEADER_LIST
      EcsWin.h
      AppView.h
      CameraResources.h
      CommonComponents.h
      ControllerRendering.h
      DemoRoomMain.h
      DeviceResources.h
      DirectXHelper.h
      EntityPrefabs.h
      GltfHelper.h
      GltfLoader.h
      Haptics.h
      HolographicRenderer.h
      HolographicScene.h
      ListenerCollection.h
      PbrCommon.h
      PbrMaterial.h
      PbrModel.h
      PbrModelCache.h
      PbrPrimitive.h
      PbrResources.h
      Physics.h
      QuadRenderer.h
      SkyboxRenderer.h
      StepTimer.h
      TextRenderer.h
      TransformUtil.h
      EngineTypeTraits.h
      MotionControllerSystem.h
      PaintingSystem.h
      PaintStrokeSystem.h
      ShootingSystem.h
      SpatialInteractionSystem.h
      ThrowingSystem.h
      ToolboxSystem.h
      ToolSystem.h
      PhysicsSystem.h
      Engine.h
      Entity.h
      AppLogicSystem.h
      Component.h
      ComponentStore.h
      EasingSystem.h
      EngineCommon.h
      EntityStore.h
)

list ( APPEND SOURCE_LIST_CPP
      AppView.cpp
      CameraResources.cpp
      ControllerRendering.cpp
      DemoRoomMain.cpp
      DeviceResources.cpp
      GltfHelper.cpp
      GltfLoader.cpp
      HolographicRenderer.cpp
      HolographicScene.cpp
      PbrCommon.cpp
      PbrMaterial.cpp
      PbrModel.cpp
      PbrModelCache.cpp
      PbrPrimitive.cpp
      PbrResources.cpp
      QuadRenderer.cpp
      SkyboxRenderer.cpp
      TextRenderer.cpp
      MotionControllerSystem.cpp
      PaintingSystem.cpp
      PaintStrokeSystem.cpp
      ShootingSystem.cpp
      SpatialInteractionSystem.cpp
      ThrowingSystem.cpp
      ToolboxSystem.cpp
      ToolSystem.cpp
      PhysicsSystem.cpp
      Engine.cpp
      Entity.cpp
      ComponentStore.cpp
      EasingSystem.cpp
      EntityStore.cpp
)

list ( APPEND EcsWin_DEPEND_LIST
      ports_DirectXTK-lib
      EcsLocal-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( EcsWin-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( EcsWin-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET EcsWin-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( EcsWin_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( EcsWin-lib ${EcsWin_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( EcsWin-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( EcsWin-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( EcsWin-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( EcsWin-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/EcsWin-lib )
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
      set_target_properties ( EcsWin-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

