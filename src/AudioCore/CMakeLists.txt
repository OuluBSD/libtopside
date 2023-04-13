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
      Info.txt
      AudioCore.h
      ADSR.h
      Audio.h
      Asymptionic.h
      BandedWaveGuide.h
      BeeThree.h
      BiQuad.h
      Blit.h
      BlitSaw.h
      BlitSquare.h
      BlowBottle.h
      BlowHole.h
      Bowed.h
      BowTable.h
      Brass.h
      Chorus.h
      Clarinet.h
      Compressor.h
      Cubic.h
      Delay.h
      DelayA.h
      DelayL.h
      DevWaveOut.h
      Drummer.h
      Echo.h
      Effect.h
      Envelope.h
      FileLoop.h
      FileRead.h
      FileWrite.h
      FileWaveIn.h
      FileWaveOut.h
      Filter.h
      Fir.h
      Flute.h
      FM.h
      FMVoices.h
      FormSwep.h
      FreeVerb.h
      Function.h
      FunctionDiscoveryKeys_devpkey.h
      Generator.h
      Granulate.h
      Guitar.h
      HeavyMetal.h
      Iir.h
      Instrument.h
      JCRev.h
      JetTable.h
      LentPitchShift.h
      Mandolin.h
      Mesh2D.h
      Messenger.h
      MidiFileIn.h
      Modal.h
      ModalBar.h
      Modulate.h
      Moog.h
      Noise.h
      NRev.h
      OnePole.h
      OneZero.h
      PercFlut.h
      Phonemes.h
      PitchShift.h
      Plucked.h
      PoleZero.h
      PRCRev.h
      ReedTable.h
      Resonate.h
      Rhodey.h
      Sampler.h
      Saxofony.h
      Shakers.h
      Simple.h
      SineWave.h
      SingWave.h
      Sitar.h
      Script.h
      ScriptMsg.h
      ScriptTbl.h
      Sphere.h
      StifKarp.h
      TapDelay.h
      TubeBell.h
      Twang.h
      TwoPole.h
      TwoZero.h
      Voicer.h
      VoiceFormant.h
      Whistle.h
      Wurley.h
      WaveIn.h
      WaveOut.h
)

list ( APPEND SOURCE_LIST_CPP
      ADSR.cpp
      Audio.cpp
      Asymptionic.cpp
      BandedWaveGuide.cpp
      BeeThree.cpp
      BiQuad.cpp
      Blit.cpp
      BlitSaw.cpp
      BlitSquare.cpp
      BlowBottle.cpp
      BlowHole.cpp
      Bowed.cpp
      Brass.cpp
      Chorus.cpp
      Clarinet.cpp
      Compressor.cpp
      Delay.cpp
      DelayA.cpp
      DelayL.cpp
      DevWaveOut.cpp
      Drummer.cpp
      Echo.cpp
      Envelope.cpp
      FileLoop.cpp
      FileRead.cpp
      FileWrite.cpp
      FileWaveIn.cpp
      FileWaveOut.cpp
      Fir.cpp
      Flute.cpp
      FM.cpp
      FMVoices.cpp
      FormSwep.cpp
      FreeVerb.cpp
      Granulate.cpp
      Guitar.cpp
      HeavyMetal.cpp
      Iir.cpp
      Instrument.cpp
      JCRev.cpp
      LentPitchShift.cpp
      Mandolin.cpp
      Mesh2D.cpp
      Messenger.cpp
      MidiFileIn.cpp
      Modal.cpp
      ModalBar.cpp
      Modulate.cpp
      Moog.cpp
      Noise.cpp
      NRev.cpp
      OnePole.cpp
      OneZero.cpp
      PercFlut.cpp
      Phonemes.cpp
      PitchShift.cpp
      Plucked.cpp
      PoleZero.cpp
      PRCRev.cpp
      Resonate.cpp
      Rhodey.cpp
      Sampler.cpp
      Saxofony.cpp
      Shakers.cpp
      Simple.cpp
      SineWave.cpp
      SingWave.cpp
      Sitar.cpp
      Script.cpp
      ScriptTbl.cpp
      Sphere.cpp
      StifKarp.cpp
      TapDelay.cpp
      TubeBell.cpp
      Twang.cpp
      TwoPole.cpp
      TwoZero.cpp
      Voicer.cpp
      VoiceFormant.cpp
      Whistle.cpp
      Wurley.cpp
)

list ( APPEND AudioCore_DEPEND_LIST
      Local-lib
      Geometry-lib
      MidiFile-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( AudioCore-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C} ${HEADER_LIST} )
target_include_directories ( AudioCore-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET AudioCore-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module link
if ( AudioCore_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( AudioCore-lib ${AudioCore_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( AudioCore-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( AudioCore-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( AudioCore-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( AudioCore-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()

if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/AudioCore-lib )
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
      set_target_properties ( AudioCore-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

