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

# options(BUILDER_OPTION) NOWARNINGS;
if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -w")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -w")
elseif ( MSVC )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
endif()

list ( APPEND HEADER_LIST
      config.h
      z.h
      defs.h
      3DSExporter.h
      3DSHelper.h
      3DSLoader.h
      3MFXmlTags.h
      ACLoader.h
      ai_assert.h
      AMFImporter.hpp
      AMFImporter_Macro.hpp
      AMFImporter_Node.hpp
      anim.h
      ASELoader.h
      ASEParser.h
      assbin_chunks.h
      AssbinExporter.h
      AssbinLoader.h
      AssxmlExporter.h
      B3DImporter.h
      BaseImporter.h
      BaseProcess.h
      Bitmap.h
      BlenderBMesh.h
      BlenderDNA.h
      BlenderDNA.inl
      BlenderIntermediate.h
      BlenderLoader.h
      BlenderModifier.h
      BlenderScene.h
      BlenderSceneGen.h
      BlenderTessellator.h
      BlobIOSystem.h
      BVHLoader.h
      ByteSwapper.h
      C4DImporter.h
      CalcTangentsProcess.h
      camera.h
      cexport.h
      cfileio.h
      cimport.h
      CInterfaceIOWrapper.h
      CMakeLists.txt
      COBLoader.h
      COBScene.h
      ColladaExporter.h
      ColladaHelper.h
      ColladaLoader.h
      ColladaParser.h
      color4.h
      color4.inl
      ComputeUVMappingProcess.h
      config.h.in
      ConvertToLHProcess.h
      CreateAnimMesh.h
      CSMLoader.h
      D3MFExporter.h
      D3MFImporter.h
      D3MFOpcPackage.h
      DeboneProcess.h
      DefaultIOStream.h
      DefaultIOSystem.h
      DefaultLogger.hpp
      DefaultProgressHandler.h
      Defines.h
      DXFHelper.h
      DXFLoader.h
      Exceptional.h
      Exporter.hpp
      fast_atof.h
      FBXCompileConfig.h
      FBXConverter.h
      FBXDocument.h
      FBXDocumentUtil.h
      FBXImporter.h
      FBXImportSettings.h
      FBXMeshGeometry.h
      FBXParser.h
      FBXProperties.h
      FBXTokenizer.h
      FBXUtil.h
      FileLogStream.h
      FileSystemFilter.h
      FindDegenerates.h
      FindInstancesProcess.h
      FindInvalidDataProcess.h
      FIReader.hpp
      FixNormalsStep.h
      GenericProperty.h
      GenFaceNormalsProcess.h
      GenVertexNormalsProcess.h
      glTF2Asset.h
      glTF2Asset.inl
      glTF2AssetWriter.h
      glTF2AssetWriter.inl
      glTF2Exporter.h
      glTF2Importer.h
      glTFAsset.h
      glTFAsset.inl
      glTFAssetWriter.h
      glTFAssetWriter.inl
      glTFExporter.h
      glTFImporter.h
      HalfLifeFileData.h
      Hash.h
      HMPFileData.h
      HMPLoader.h
      IFCLoader.h
      IFCReaderGen.h
      IFCUtil.h
      IFF.h
      Importer.h
      Importer.hpp
      importerdesc.h
      ImproveCacheLocality.h
      IOStream.hpp
      IOStreamBuffer.h
      IOSystem.hpp
      IRRLoader.h
      IRRMeshLoader.h
      IRRShared.h
      irrXMLWrapper.h
      JoinVerticesProcess.h
      light.h
      LimitBoneWeightsProcess.h
      LineSplitter.h
      LogAux.h
      Logger.hpp
      LogStream.hpp
      LWOAnimation.h
      LWOFileData.h
      LWOLoader.h
      LWSLoader.h
      Macros.h
      makefile.mingw
      MakeVerboseFormat.h
      material.h
      material.inl
      MaterialSystem.h
      MathFunctions.h
      matrix3x3.h
      matrix3x3.inl
      matrix4x4.h
      matrix4x4.inl
      MD2FileData.h
      MD2Loader.h
      MD2NormalTable.h
      MD3FileData.h
      MD3Loader.h
      MD4FileData.h
      MD5Loader.h
      MD5Parser.h
      MDCFileData.h
      MDCLoader.h
      MDCNormalTable.h
      MDLDefaultColorMap.h
      MDLFileData.h
      MDLLoader.h
      MemoryIOWrapper.h
      mesh.h
      metadata.h
      MMDCpp14.h
      MMDImporter.h
      MMDPmdParser.h
      MMDPmxParser.h
      MMDVmdParser.h
      MS3DLoader.h
      NDOLoader.h
      NFFLoader.h
      NullLogger.hpp
      ObjExporter.h
      ObjFileData.h
      ObjFileImporter.h
      ObjFileMtlImporter.h
      ObjFileParser.h
      ObjTools.h
      OFFLoader.h
      OgreBinarySerializer.h
      OgreImporter.h
      OgreParsingUtils.h
      OgreStructs.h
      OgreXmlSerializer.h
      OpenGEXExporter.h
      OpenGEXImporter.h
      OpenGEXStructs.h
      OptimizeGraph.h
      OptimizeMeshes.h
      ParsingUtils.h
      PlyExporter.h
      PlyLoader.h
      PlyParser.h
      PolyTools.h
      postprocess.h
      PretransformVertices.h
      ProcessHelper.h
      Profiler.h
      ProgressHandler.hpp
      Q3BSPFileData.h
      Q3BSPFileImporter.h
      Q3BSPFileParser.h
      Q3BSPZipArchive.h
      Q3DLoader.h
      qnan.h
      quaternion.h
      quaternion.inl
      RawLoader.h
      RemoveComments.h
      RemoveRedundantMaterials.h
      RemoveVCProcess.h
      ScaleProcess.h
      scene.h
      SceneCombiner.h
      ScenePreprocessor.h
      ScenePrivate.h
      SGSpatialSort.h
      SIBImporter.h
      SkeletonMeshBuilder.h
      SMDLoader.h
      SmoothingGroups.h
      SmoothingGroups.inl
      SortByPTypeProcess.h
      SpatialSort.h
      SplitByBoneCountProcess.h
      SplitLargeMeshes.h
      StandardShapes.h
      StdOStreamLogStream.h
      StepExporter.h
      STEPFile.h
      STEPFileEncoding.h
      STEPFileReader.h
      STLExporter.h
      STLLoader.h
      StreamReader.h
      StreamWriter.h
      StringComparison.h
      StringUtils.h
      Subdivision.h
      TargetAnimation.h
      TerragenLoader.h
      texture.h
      TextureTransform.h
      TinyFormatter.h
      TriangulateProcess.h
      types.h
      UnrealLoader.h
      ValidateDataStructure.h
      vector2.h
      vector2.inl
      vector3.h
      vector3.inl
      version.h
      Vertex.h
      VertexTriangleAdjacency.h
      Win32DebugLogStream.h
      X3DExporter.hpp
      X3DImporter.hpp
      X3DImporter_Macro.hpp
      X3DImporter_Node.hpp
      XFileExporter.h
      XFileHelper.h
      XFileImporter.h
      XFileParser.h
      XGLLoader.h
      Compiler/poppack1.h
      Compiler/pstdint.h
      Compiler/pushpack1.h
      XMLTools.h
)

list ( APPEND SOURCE_LIST_CPP
      3DSConverter.cpp
      3DSExporter.cpp
      3DSLoader.cpp
      ACLoader.cpp
      AMFImporter.cpp
      AMFImporter_Geometry.cpp
      AMFImporter_Material.cpp
      AMFImporter_Postprocess.cpp
      ASELoader.cpp
      ASEParser.cpp
      AssbinExporter.cpp
      AssbinLoader.cpp
      Assimp.cpp
      AssimpCExport.cpp
      AssxmlExporter.cpp
      B3DImporter.cpp
      BaseImporter.cpp
      BaseProcess.cpp
      Bitmap.cpp
      BlenderBMesh.cpp
      BlenderDNA.cpp
      BlenderLoader.cpp
      BlenderModifier.cpp
      BlenderScene.cpp
      BlenderTessellator.cpp
      BVHLoader.cpp
      C4DImporter.cpp
      CalcTangentsProcess.cpp
      CInterfaceIOWrapper.cpp
      COBLoader.cpp
      ColladaExporter.cpp
      ColladaLoader.cpp
      ColladaParser.cpp
      ComputeUVMappingProcess.cpp
      ConvertToLHProcess.cpp
      CreateAnimMesh.cpp
      CSMLoader.cpp
      D3MFExporter.cpp
      D3MFImporter.cpp
      D3MFOpcPackage.cpp
      DeboneProcess.cpp
      DefaultIOStream.cpp
      DefaultIOSystem.cpp
      DefaultLogger.cpp
      DXFLoader.cpp
      Exporter.cpp
      FBXAnimation.cpp
      FBXBinaryTokenizer.cpp
      FBXConverter.cpp
      FBXDeformer.cpp
      FBXDocument.cpp
      FBXDocumentUtil.cpp
      FBXImporter.cpp
      FBXMaterial.cpp
      FBXMeshGeometry.cpp
      FBXModel.cpp
      FBXNodeAttribute.cpp
      FBXParser.cpp
      FBXProperties.cpp
      FBXTokenizer.cpp
      FBXUtil.cpp
      FindDegenerates.cpp
      FindInstancesProcess.cpp
      FindInvalidDataProcess.cpp
      FIReader.cpp
      FixNormalsStep.cpp
      GenFaceNormalsProcess.cpp
      GenVertexNormalsProcess.cpp
      glTF2Exporter.cpp
      glTF2Importer.cpp
      glTFExporter.cpp
      glTFImporter.cpp
      HMPLoader.cpp
      IFCBoolean.cpp
      IFCCurve.cpp
      IFCGeometry.cpp
      IFCLoader.cpp
      IFCMaterial.cpp
      IFCOpenings.cpp
      IFCProfile.cpp
      IFCReaderGen1.cpp
      IFCReaderGen2.cpp
      IFCUtil.cpp
      Importer.cpp
      ImporterRegistry.cpp
      ImproveCacheLocality.cpp
      IRRLoader.cpp
      IRRMeshLoader.cpp
      IRRShared.cpp
      JoinVerticesProcess.cpp
      LimitBoneWeightsProcess.cpp
      LWOAnimation.cpp
      LWOBLoader.cpp
      LWOLoader.cpp
      LWOMaterial.cpp
      LWSLoader.cpp
      MakeVerboseFormat.cpp
      MaterialSystem.cpp
      MD2Loader.cpp
      MD3Loader.cpp
      MD5Loader.cpp
      MD5Parser.cpp
      MDCLoader.cpp
      MDLLoader.cpp
      MDLMaterialLoader.cpp
      MMDImporter.cpp
      MMDPmxParser.cpp
      MS3DLoader.cpp
      NDOLoader.cpp
      NFFLoader.cpp
      ObjExporter.cpp
      ObjFileImporter.cpp
      ObjFileMtlImporter.cpp
      ObjFileParser.cpp
      OFFLoader.cpp
      OgreBinarySerializer.cpp
      OgreImporter.cpp
      OgreMaterial.cpp
      OgreStructs.cpp
      OgreXmlSerializer.cpp
      OpenGEXExporter.cpp
      OpenGEXImporter.cpp
      OptimizeGraph.cpp
      OptimizeMeshes.cpp
      PlyExporter.cpp
      PlyLoader.cpp
      PlyParser.cpp
      PostStepRegistry.cpp
      PretransformVertices.cpp
      ProcessHelper.cpp
      Q3BSPFileImporter.cpp
      Q3BSPFileParser.cpp
      Q3BSPZipArchive.cpp
      Q3DLoader.cpp
      RawLoader.cpp
      RemoveComments.cpp
      RemoveRedundantMaterials.cpp
      RemoveVCProcess.cpp
      ScaleProcess.cpp
      scene.cpp
      SceneCombiner.cpp
      ScenePreprocessor.cpp
      SGSpatialSort.cpp
      SIBImporter.cpp
      SkeletonMeshBuilder.cpp
      SMDLoader.cpp
      SortByPTypeProcess.cpp
      SpatialSort.cpp
      SplitByBoneCountProcess.cpp
      SplitLargeMeshes.cpp
      StandardShapes.cpp
      StepExporter.cpp
      STEPFileEncoding.cpp
      STEPFileReader.cpp
      STLExporter.cpp
      STLLoader.cpp
      Subdivision.cpp
      TargetAnimation.cpp
      TerragenLoader.cpp
      TextureTransform.cpp
      TriangulateProcess.cpp
      UnrealLoader.cpp
      ValidateDataStructure.cpp
      Version.cpp
      VertexTriangleAdjacency.cpp
      X3DExporter.cpp
      X3DImporter.cpp
      X3DImporter_Geometry2D.cpp
      X3DImporter_Geometry3D.cpp
      X3DImporter_Group.cpp
      X3DImporter_Light.cpp
      X3DImporter_Metadata.cpp
      X3DImporter_Networking.cpp
      X3DImporter_Postprocess.cpp
      X3DImporter_Rendering.cpp
      X3DImporter_Shape.cpp
      X3DImporter_Texturing.cpp
      X3DVocabulary.cpp
      XFileExporter.cpp
      XFileImporter.cpp
      XFileParser.cpp
      XGLLoader.cpp
)

list ( APPEND ports_assimp_DEPEND_LIST
      ports_utf8-lib
      ports_poly2tri-lib
      ports_tiny_gltf-lib
      ports_mikktspace-lib
      ports_stb-lib
      ports_irrxml-lib
      ports_rapidjson-lib
      ports_unzip-lib
      plugin_z-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( ports_assimp-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( ports_assimp-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET ports_assimp-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( ports_assimp_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( ports_assimp-lib ${ports_assimp_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( ports_assimp-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( ports_assimp-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( ports_assimp-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( ports_assimp-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/ports_assimp-lib )
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
      set_target_properties ( ports_assimp-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

