#!/bin/bash
#
# Copyright (C) 2016-2020 Radek Malcic
# Copyright (C) 2022 Seppo Pakonen
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

source ./GenerateCMakeFiles-lib.sh

GENERATE_VERBOSE="1"        # set to "1" - enable additional output during script processing on the screen
GENERATE_DEBUG="1"          # set to "1" - enable debug output during script processing on the screen
#GENERATE_PACKAGE="1"        # set to "1" - create a tarball package of the project

#GENERATE_NOT_Cxx="1"                # set to "1" - do not use compiler -std=c++14 parameter (compiler parameter is enabled as default)
#GENERATE_NOT_PARALLEL="1"           # set to "1" - do not build with multiple processes (parralel build is enabled as default)
#GENERATE_NOT_PCH="1"                # set to "1" - do not build with precompiled header support (precompiled header support is enabled as default)
#GENERATE_NOT_REMOVE_UNUSED_CODE="1" # set to "1" - do not use compile and link parameters to remove unused code and functions (unused code and functions are removed as default)

#CMAKE_VERBOSE_OVERWRITE="0" # set to "0" - do not generate cmake verbose makefile output (even when the debug flag is set)
#CMAKE_VERBOSE_OVERWRITE="1" # set to "1" - always generate cmake verbose makefile output
CMAKE_SOURCE_DIR="."
UPP_SRC_BASE="."
UPP_SRC_DIR="${UPP_SRC_BASE}/src"
PROJECT_EXTRA_INCLUDE_DIR="${UPP_SRC_BASE}/alt" # this can be changed to u++'s uppsrc directory
#PROJECT_NAME="${UPP_SRC_DIR}/Shell/Shell.upp"
PROJECT_NAME="${UPP_SRC_BASE}/reference/Shell/Shell.upp"
PROJECT_FLAGS="-DflagGUI -DflagSCREEN -DflagSDL2 -DflagOGL -DflagFFMPEG -DflagOPENCV -DflagVR -DflagLOCALHMD -DflagFLUIDSYNTH -DflagBUILTIN_PORTAUDIO -DflagPORTMIDI -DflagSHARED -DflagCMAKE"

#  -DflagPOSIX -DflagLINUX -DflagGCC 

PROJECT_EXTRA_COMPILE_FLAGS="-I/usr/include/opencv4"
PROJECT_EXTRA_LINK_FLAGS=""


generate_main_cmake_file "${PROJECT_NAME}" "${PROJECT_FLAGS}"
