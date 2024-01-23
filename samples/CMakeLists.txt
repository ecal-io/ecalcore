# ========================= eCAL LICENSE =================================
#
# Copyright (C) 2016 - 2019 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================
cmake_minimum_required(VERSION 3.10)

project(eCAL_samples VERSION "${ECAL_VERSION_STRING}")

# --------------------------------------------------------
# c samples
# --------------------------------------------------------
# pubsub
if(ECAL_CORE_PUBLISHER)
#  add_subdirectory(c/pubsub/string/minimal_snd)
endif()

if(ECAL_CORE_SUBSCRIBER)
#  add_subdirectory(c/pubsub/string/minimal_rec)
#  add_subdirectory(c/pubsub/string/minimal_rec_cb)
endif()

# --------------------------------------------------------
# cpp samples
# --------------------------------------------------------
# benchmarks
if(ECAL_CORE_PUBLISHER)
  add_subdirectory(cpp/benchmarks/counter_snd)
  add_subdirectory(cpp/benchmarks/many_connections_snd)
  add_subdirectory(cpp/benchmarks/multiple_snd)
  add_subdirectory(cpp/benchmarks/performance_snd)
  if (ECAL_CORE_COMMAND_LINE)
    add_subdirectory(cpp/benchmarks/datarate_snd)
    add_subdirectory(cpp/benchmarks/latency_snd)
  endif()
endif()

if(ECAL_CORE_SUBSCRIBER)
  add_subdirectory(cpp/benchmarks/counter_rec)
  add_subdirectory(cpp/benchmarks/many_connections_rec)
  add_subdirectory(cpp/benchmarks/multiple_rec)
  add_subdirectory(cpp/benchmarks/performance_rec)
  if (ECAL_CORE_COMMAND_LINE)
    add_subdirectory(cpp/benchmarks/datarate_rec)
    add_subdirectory(cpp/benchmarks/latency_rec)
  endif()
endif()

if(ECAL_CORE_PUBLISHER AND ECAL_CORE_SUBSCRIBER)
  add_subdirectory(cpp/benchmarks/perftool)
endif()

# pubsub
if(ECAL_CORE_PUBLISHER)
  add_subdirectory(cpp/pubsub/binary/binary_snd)
  add_subdirectory(cpp/pubsub/binary/ping)
  add_subdirectory(cpp/pubsub/string/minimal_snd)
  if(BUILD_SAMPLES_PROTOBUF)
    add_subdirectory(cpp/pubsub/protobuf/person_events_snd)
    add_subdirectory(cpp/pubsub/protobuf/person_snd)
  endif()
endif()

if(ECAL_CORE_SUBSCRIBER)
  add_subdirectory(cpp/pubsub/binary/binary_rec)
  add_subdirectory(cpp/pubsub/binary/pong)
  add_subdirectory(cpp/pubsub/string/minimal_rec)
  add_subdirectory(cpp/pubsub/string/minimal_rec_cb)
  if(BUILD_SAMPLES_PROTOBUF)
    add_subdirectory(cpp/pubsub/protobuf/person_events_rec)
    add_subdirectory(cpp/pubsub/protobuf/person_rec)
  endif()
endif()

if(ECAL_CORE_PUBLISHER AND ECAL_CORE_SUBSCRIBER)
  if(BUILD_SAMPLES_PROTOBUF)
    add_subdirectory(cpp/pubsub/protobuf/person_loopback)
  endif()
endif()

# services
if(ECAL_CORE_SERVICE)
  add_subdirectory(cpp/services/latency_client)
  add_subdirectory(cpp/services/latency_server)
  add_subdirectory(cpp/services/minimal_client)
  add_subdirectory(cpp/services/minimal_server)
  if(BUILD_SAMPLES_PROTOBUF)
    add_subdirectory(cpp/services/math_client)
    add_subdirectory(cpp/services/math_server)
    add_subdirectory(cpp/services/ping_client)
    add_subdirectory(cpp/services/ping_server)
  endif()
endif()