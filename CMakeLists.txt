	################################################################################
# Copyright (c) 2024 Continental Corporation
# 
# This program and the accompanying materials are made available under the
# terms of the Apache License, Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0.
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
# 
# SPDX-License-Identifier: Apache-2.0
################################################################################

cmake_minimum_required(VERSION 3.13)

include(CMakeDependentOption)

# Project call
include("${CMAKE_CURRENT_LIST_DIR}/ecalcore/core/version.cmake")
project(ecalcore VERSION ${ECALCORE_VERSION_MAJOR}.${ECALCORE_VERSION_MINOR}.${ECALCORE_VERSION_PATCH})

# Normalize backslashes from Windows paths
file(TO_CMAKE_PATH "${CMAKE_MODULE_PATH}" CMAKE_MODULE_PATH)
file(TO_CMAKE_PATH "${CMAKE_PREFIX_PATH}" CMAKE_PREFIX_PATH)
message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")


# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# configurable build options
# command line usage: cmake .. -DECALCORE_BUILD_SAMPLES=ON -DECALCORE_BUILD_ECAL_TESTS=OFF -DECALCORE_CONFIG_INIFILE=OFF
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# additional builds (adapt to your needs)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
option(ECALCORE_BUILD_SAMPLES                            "Build the eCAL samples"                                                                               OFF)
option(ECALCORE_BUILD_SAMPLES_PROTOBUF                   "Build the eCAL samples using google protobuf message definition"                                      OFF)
option(ECALCORE_BUILD_ECAL_TESTS                         "Build the eCAL google tests"                                                                          OFF)
option(ECALCORE_BUILD_ECAL_TESTS_PROTOBUF                "Build the eCAL google tests using google protobuf message definition"                                 OFF)

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# core internal feature configuration (adapt to your needs)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
option(ECALCORE_CONFIG_INIFILE                          "Enables to configure eCAL via ecal.ini file"                                                           OFF)
option(ECALCORE_COMMAND_LINE                            "Enables eCAL application cmd line interfaces"                                                          OFF)
option(ECALCORE_REGISTRATION                            "Enables the eCAL registration layer"                                                                    ON)
option(ECALCORE_PUBLISHER                               "Enables the eCAL publisher functionality"                                                               ON)
option(ECALCORE_SUBSCRIBER                              "Enables the eCAL subscriber functionality"                                                              ON)
option(ECALCORE_SERVICE                                 "Enables the eCAL server/client functionality"                                                          OFF)
option(ECALCORE_TIMEPLUGIN                              "Enables the eCAL time plugin functionality"                                                            OFF)

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# core registration layer options (change with care)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
option(ECALCORE_REGISTRATION_SHM                        "Enables the eCAL registration layer over shared memory"                                                OFF)

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# core transport layer options (change with care)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
option(ECALCORE_TRANSPORT_UDP                           "Enables the eCAL to transport payload via UDP multicast"                                                ON)
option(ECALCORE_TRANSPORT_TCP                           "Enables the eCAL to transport payload via TCP"                                                         OFF)
option(ECALCORE_TRANSPORT_SHM                           "Enables the eCAL to transport payload via local shared memory"                                         OFF)

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
# third party library options (do not change)
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------
option(ECALCORE_THIRDPARTY_BUILD_ASIO                   "Build asio with eCAL"                                                                                   ON)
option(ECALCORE_THIRDPARTY_BUILD_CMAKEFUNCTIONS         "Build CMakeFunctions with eCAL"                                                                         ON)
option(ECALCORE_NPCAP_SUPPORT                           "Enable the eCAL Npcap Receiver (i.e. the Win10 performance fix)"                                       OFF)

cmake_dependent_option(ECAL_THIRDPARTY_BUILD_GTEST       "Build gtest with eCAL"               ON   "ECALCORE_BUILD_ECAL_TESTS"                                 OFF)
cmake_dependent_option(ECAL_THIRDPARTY_BUILD_TCP_PUBSUB  "Build tcp_pubsub library with eCAL"  ON   "ECALCORE_TRANSPORT_TCP"                                    OFF)
cmake_dependent_option(ECAL_THIRDPARTY_BUILD_RECYCLE     "Build steinwurf::recylce with eCAL"  ON   "ECALCORE_TRANSPORT_TCP"                                    OFF)
cmake_dependent_option(ECAL_THIRDPARTY_BUILD_SIMPLEINI   "Build simpleini with eCAL"           ON   "ECALCORE_CONFIG_INIFILE"                                   OFF)
cmake_dependent_option(ECAL_THIRDPARTY_BUILD_TCLAP       "Build tclap library with eCAL"       ON   "ECALCORE_COMMAND_LINE"                                     OFF)

if(WIN32)
  cmake_dependent_option(ECALCORE_THIRDPARTY_BUILD_PROTOBUF  "Build protobuf with eCAL"       OFF   "NOT ECALCORE_BUILD_SAMPLES_PROTOBUF; NOT ECALCORE_BUILD_ECAL_TESTS_PROTOBUF"  ON)
else()
  option(ECALCORE_NPCAP_SUPPORT                          "Enable the eCAL Npcap Receiver (i.e. the Win10 performance fix)"                                      OFF)
  option(ECALCORE_THIRDPARTY_BUILD_PROTOBUF              "Build protobuf with eCAL"                                                                             OFF)
endif()

cmake_dependent_option(ECAL_THIRDPARTY_BUILD_UDPCAP      "Build udpcap library with eCAL"      ON   "ECALCORE_NPCAP_SUPPORT"                                    OFF)

if(NOT ECALCORE_REGISTRATION)
  if(ECALCORE_TRANSPORT_TCP)
    message(STATUS "Switching ECALCORE_TRANSPORT_TCP to OFF because registration (ECALCORE_REGISTRATION) is not activated")
	set(ECALCORE_TRANSPORT_TCP OFF)
  endif()
  if(ECALCORE_TRANSPORT_SHM)
    message(STATUS "Switching ECALCORE_TRANSPORT_SHM to OFF because registration (ECALCORE_REGISTRATION) is not activated")
	set(ECALCORE_TRANSPORT_SHM OFF)
  endif()
endif()

# Set Debug postfix
set(CMAKE_DEBUG_POSTFIX            d)
set(CMAKE_MINSIZEREL_POSTFIX       minsize)
set(CMAKE_RELWITHDEBINFO_POSTFIX   reldbg)

# Use builtin asio
if (ECALCORE_THIRDPARTY_BUILD_ASIO)
    include("${CMAKE_CURRENT_LIST_DIR}/thirdparty/build-asio.cmake")
endif()

# Use builtin recycle
if (ECAL_THIRDPARTY_BUILD_RECYCLE)
    include("${CMAKE_CURRENT_LIST_DIR}/thirdparty/build-recycle.cmake")
endif()

# Use builtin gtest
if (ECAL_THIRDPARTY_BUILD_GTEST)
    include("${CMAKE_CURRENT_LIST_DIR}/thirdparty/build-gtest.cmake")
endif()

# For tests we need to make sure that all shared libraries and executables are 
# put into the same directory. Otherwise the tests will fail on windows.
if(ECALCORE_BUILD_TESTS AND BUILD_SHARED_LIBS AND ECALCORE_USE_BUILTIN_GTEST)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# ecalcore library
add_subdirectory(ecalcore)

# Add the ecalcore dummy module
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ecalcore-module)

# ecalcore samples
add_subdirectory(samples)

# ecalcore tests
add_subdirectory(tests)

# Make this package available for packing with CPack
include("${CMAKE_CURRENT_LIST_DIR}/cpack_config.cmake")
