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

cmake_minimum_required(VERSION 3.13)

if(ECALCORE_BUILD_TESTS)

  enable_testing()
  add_subdirectory(expmap_test)
  add_subdirectory(topic2mcast_test)
  add_subdirectory(util_test)

  if(ECALCORE_REGISTRATION_SHM OR ECALCORE_TRANSPORT_SHM)
    add_subdirectory(io_memfile_test)
  endif()

  if(ECALCORE_PUBLISHER AND ECALCORE_SUBSCRIBER)
    add_subdirectory(core_test)
    add_subdirectory(pubsub_test)
    add_subdirectory(serialization_test)
    if(ECALCORE_BUILD_TESTS_PROTOBUF)
      add_subdirectory(pubsub_proto_test)
    endif()
  endif()

  if(ECALCORE_SERVICE)
    add_subdirectory(clientserver_test)
    if(ECALCORE_BUILD_TESTS_PROTOBUF)
      add_subdirectory(clientserver_proto_test)
    endif()
  endif()

endif()
