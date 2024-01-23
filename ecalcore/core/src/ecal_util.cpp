/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include "ecal_global_accessors.h"
#include "registration/ecal_registration_receiver.h"
#include "pubsub/ecal_pubgate.h"

#include <list>
#include <string>

namespace eCAL
{
  namespace Util
  {
    void EnableLoopback(bool state_)
    {
#if ECALCORE_REGISTRATION
      if (g_registration_receiver() != nullptr) g_registration_receiver()->EnableLoopback(state_);
#endif
    }

    void PubShareType(bool state_)
    {
#if ECALCORE_PUBLISHER
      if (g_pubgate() != nullptr) g_pubgate()->ShareType(state_);
#endif
    }

    void PubShareDescription(bool state_)
    {
#if ECALCORE_PUBLISHER
      if (g_pubgate() != nullptr) g_pubgate()->ShareDescription(state_);
#endif
    }

    std::pair<std::string, std::string> SplitCombinedTopicType(const std::string& combined_topic_type_)
    {
      auto pos = combined_topic_type_.find(':');
      if (pos == std::string::npos)
      {
        std::string encoding;
        std::string type{ combined_topic_type_ };
        return std::make_pair(encoding, type);
      }
      else
      {
        std::string encoding = combined_topic_type_.substr(0, pos);
        std::string type = combined_topic_type_.substr(pos + 1);
        return std::make_pair(encoding, type);
      }
    }

    std::string CombinedTopicEncodingAndType(const std::string& topic_encoding_, const std::string& topic_type_)
    {
      if (topic_encoding_.empty())
      {
        return topic_type_;
      }
      else
      {
        return topic_encoding_ + ":" + topic_type_;
      }
    }
  }
}
