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

/**
 * @brief  Implementation of the eCAL dll interface
**/

#include <mutex>

#include <ecal/ecal.h>
#include <ecal/ecal_c.h>

static int CopyBuffer(void* target_, int target_len_, const std::string& source_s_)
{
  if(target_ == nullptr) return(0);
  if(source_s_.empty())  return(0);
  if(target_len_ == ECAL_ALLOCATE_4ME)
  {
    void* buf_alloc = malloc(source_s_.size());
    if(buf_alloc == nullptr) return(0);
    int copied = CopyBuffer(buf_alloc, static_cast<int>(source_s_.size()), source_s_);
    if(copied > 0)
    {
      *((void**)target_) = buf_alloc; //-V206
      return(copied);
    }
    else
    {
      // copying buffer failed, so free allocated memory.
      free(buf_alloc);
    }
  }
  else
  {
    if(target_len_ < static_cast<int>(source_s_.size())) return(0);
    memcpy(target_, source_s_.data(), source_s_.size());
    return(static_cast<int>(source_s_.size()));
  }
  return(0);
}

/////////////////////////////////////////////////////////
// Core
/////////////////////////////////////////////////////////
extern "C"
{
  ECALC_API const char* eCAL_GetVersionString()
  {
    return(ECALCORE_VERSION);
  }

  ECALC_API const char* eCAL_GetVersionDateString()
  {
    return(ECALCORE_DATE);
  }

  ECALC_API int eCAL_GetVersion(int* major_, int* minor_, int* patch_)
  {
    if((major_ == nullptr) || (minor_ == nullptr) || (patch_ == nullptr)) return(-1); 
    *major_ = ECALCORE_VERSION_MAJOR;
    *minor_ = ECALCORE_VERSION_MINOR;
    *patch_ = ECALCORE_VERSION_PATCH;
    return(0);
  }

  ECALC_API int eCAL_Initialize(int argc_, char **argv_, const char *unit_name_, unsigned int components_)
  {
    return(eCAL::Initialize(argc_, argv_, unit_name_, components_));
  }

  ECALC_API int eCAL_SetUnitName(const char *unit_name_)
  {
    return(eCAL::SetUnitName(unit_name_));
  }

  ECALC_API int eCAL_Finalize(unsigned int components_)
  {
    return(eCAL::Finalize(components_));
  }

  ECALC_API int eCAL_IsInitialized(unsigned int component_)
  {
    return(eCAL::IsInitialized(component_));
  }

  ECALC_API int eCAL_Ok()
  {
    return(eCAL::Ok());
  }

  ECALC_API void eCAL_FreeMem(void* mem_)
  {
    free(mem_);
  }
}

/////////////////////////////////////////////////////////
// Util
/////////////////////////////////////////////////////////
extern "C"
{
  ECALC_API void eCAL_Util_EnableLoopback(int state_)
  {
    eCAL::Util::EnableLoopback(state_ != 0);
  }
}

/////////////////////////////////////////////////////////
// Process
/////////////////////////////////////////////////////////
extern "C"
{
  ECALC_API void eCAL_Process_DumpConfig()
  {
    eCAL::Process::DumpConfig();
  }

  ECALC_API int eCAL_Process_GetHostName(void* name_, int name_len_)
 {
    std::string name = eCAL::Process::GetHostName();
    if(!name.empty())
    {
      return(CopyBuffer(name_, name_len_, name));
    }
    return(0);
  }

  ECALC_API int eCAL_Process_GetUnitName(void* name_, int name_len_)
  {
    std::string name = eCAL::Process::GetUnitName();
    if(!name.empty())
    {
      return(CopyBuffer(name_, name_len_, name));
    }
    return(0);
  }

  ECALC_API int eCAL_Process_GetTaskParameter(void* par_, int par_len_, const char* sep_)
  {
    std::string par = eCAL::Process::GetTaskParameter(sep_);
    if(!par.empty())
    {
      return(CopyBuffer(par_, par_len_, par));
    }
    return(0);
  }

  ECALC_API void eCAL_Process_SleepMS(long time_ms_)
  {
    eCAL::Process::SleepMS(time_ms_);
  }

  ECALC_API int eCAL_Process_GetProcessID()
  {
    return(eCAL::Process::GetProcessID());
  }

  ECALC_API int eCAL_Process_GetProcessName(void* name_, int name_len_)
  {
    std::string name = eCAL::Process::GetProcessName();
    if(!name.empty())
    {
      return(CopyBuffer(name_, name_len_, name));
    }
    return(0);
  }

  ECALC_API int eCAL_Process_GetProcessParameter(void* par_, int par_len_)
  {
    std::string par = eCAL::Process::GetProcessParameter();
    if(!par.empty())
    {
      return(CopyBuffer(par_, par_len_, par));
    }
    return(0);
  }

  ECALC_API void eCAL_Process_SetState(enum eCAL_Process_eSeverity severity_, enum eCAL_Process_eSeverity_Level level_, const char* info_)
  {
    eCAL::Process::SetState(severity_, level_, info_);
  }
}

/////////////////////////////////////////////////////////
// Logging
/////////////////////////////////////////////////////////
extern "C"
{
  ECALC_API void eCAL_Logging_SetLogLevel(enum eCAL_Logging_eLogLevel level_)
  {
    eCAL::Logging::SetLogLevel(level_);
  }

  ECALC_API enum eCAL_Logging_eLogLevel eCAL_Logging_GetLogLevel()
  {
    return(eCAL::Logging::GetLogLevel());
  }

  ECALC_API void eCAL_Logging_Log(const char* const msg_)
  {
    eCAL::Logging::Log(msg_);
  }
}

/////////////////////////////////////////////////////////
// Publisher
/////////////////////////////////////////////////////////
extern "C"
{
  ECALC_API ECAL_HANDLE eCAL_Pub_New()
  {
#if ECAL_CORE_PUBLISHER
    auto* pub = new eCAL::CPublisher;
    return(pub);
#else
    return(nullptr);
#endif
  }

  ECALC_API int eCAL_Pub_Create(ECAL_HANDLE handle_, const char* topic_name_, const char* topic_type_encoding_, const char* topic_type_name_, const char* topic_desc_, int topic_desc_len_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    struct eCAL::SDataTypeInformation topic_info = { topic_type_encoding_, topic_type_name_, std::string(topic_desc_, static_cast<size_t>(topic_desc_len_)) };
    if (!pub->Create(topic_name_, topic_info)) return(0);
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Pub_Destroy(ECAL_HANDLE handle_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    delete pub;
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Pub_SetAttribute(ECAL_HANDLE handle_, const char* attr_name_, int attr_name_len_, const char* attr_value_, int attr_value_len_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    if (pub->SetAttribute(std::string(attr_name_, static_cast<size_t>(attr_name_len_)), std::string(attr_value_, static_cast<size_t>(attr_value_len_)))) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Pub_ClearAttribute(ECAL_HANDLE handle_, const char* attr_name_, int attr_name_len_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    if (pub->ClearAttribute(std::string(attr_name_, static_cast<size_t>(attr_name_len_)))) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Pub_ShareType(ECAL_HANDLE handle_, int state_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    pub->ShareType(state_ != 0);
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Pub_ShareDescription(ECAL_HANDLE handle_, int state_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    pub->ShareDescription(state_ != 0);
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Pub_SetID(ECAL_HANDLE handle_, long long id_)
  {
#if ECAL_CORE_PUBLISHER
    if (handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    if (pub->SetID(id_)) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Pub_IsSubscribed(ECAL_HANDLE handle_)
  {
#if ECAL_CORE_PUBLISHER
    if(handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    if(pub->IsSubscribed()) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Pub_Send(ECAL_HANDLE handle_, const void* const buf_, int buf_len_, long long time_)
  {
#if ECAL_CORE_PUBLISHER
    if(handle_ == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    const size_t ret = pub->Send(buf_, static_cast<size_t>(buf_len_), time_);
    if(static_cast<int>(ret) == buf_len_)
    {
      return(buf_len_);
    }
#endif
    return(0);
  }

  ECALC_API int eCAL_Pub_Dump(ECAL_HANDLE handle_, void* buf_, int buf_len_)
  {
#if ECAL_CORE_PUBLISHER
    if(handle_   == nullptr) return(0);
    auto* pub = static_cast<eCAL::CPublisher*>(handle_);
    const std::string dump = pub->Dump();
    if(!dump.empty())
    {
      return(CopyBuffer(buf_, buf_len_, dump));
    }
#endif
    return(0);
  }
}

/////////////////////////////////////////////////////////
// Subscriber
/////////////////////////////////////////////////////////
#if ECAL_CORE_SUBSCRIBER
static std::recursive_mutex g_sub_callback_mtx;
static void g_sub_receive_callback(const char* topic_name_, const struct eCAL::SReceiveCallbackData* data_, const ReceiveCallbackCT callback_, void* par_)
{
  const std::lock_guard<std::recursive_mutex> lock(g_sub_callback_mtx);
  SReceiveCallbackDataC data{};
  data.buf   = data_->buf;
  data.size  = data_->size;
  data.id    = data_->id;
  data.time  = data_->time;
  data.clock = data_->clock;
  callback_(topic_name_, &data, par_);
}
#endif

extern "C"
{
  ECALC_API ECAL_HANDLE eCAL_Sub_New()
  {
#if ECAL_CORE_SUBSCRIBER
    auto* sub = new eCAL::CSubscriber;
    return(sub);
#else
    return(nullptr);
#endif
  }

  ECALC_API int eCAL_Sub_Create(ECAL_HANDLE handle_, const char* topic_name_, const char* topic_type_encoding_, const char* topic_type_name_, const char* topic_desc_, int topic_desc_len_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    struct eCAL::SDataTypeInformation topic_info = { topic_type_encoding_, topic_type_name_, std::string(topic_desc_, static_cast<size_t>(topic_desc_len_)) };
    if (!sub->Create(topic_name_, topic_info)) return(0);
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Sub_Destroy(ECAL_HANDLE handle_)
  {
#if ECAL_CORE_SUBSCRIBER
    if(handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    delete sub;
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Sub_SetID(ECAL_HANDLE handle_, const long long* id_array_, const int id_num_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    std::set<long long> id_set;
    if (id_array_ != nullptr)
    {
      for (size_t i = 0; i < static_cast<size_t>(id_num_); ++i)
      {
        id_set.insert(id_array_[i]);
      }
    }
    if (sub->SetID(id_set)) return(1);
    return(1);
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Sub_SetAttribute(ECAL_HANDLE handle_, const char* attr_name_, int attr_name_len_, const char* attr_value_, int attr_value_len_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    if (sub->SetAttribute(std::string(attr_name_, static_cast<size_t>(attr_name_len_)), std::string(attr_value_, static_cast<size_t>(attr_value_len_)))) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_ClearAttribute(ECAL_HANDLE handle_, const char* attr_name_, int attr_name_len_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    if (sub->ClearAttribute(std::string(attr_name_, static_cast<size_t>(attr_name_len_)))) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_Receive(ECAL_HANDLE handle_, void* buf_, int buf_len_, long long* time_, int rcv_timeout_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (buf_len_ == ECAL_ALLOCATE_4ME)
    {
      return eCAL_Sub_Receive_Alloc(handle_, static_cast<void**>(buf_), time_, rcv_timeout_); //-V206
    }
    else
    {
      return eCAL_Sub_Receive_ToBuffer(handle_, buf_, buf_len_, time_, rcv_timeout_);
    }
#else
    return(0);
#endif
  }

  ECALC_API int eCAL_Sub_Receive_ToBuffer(ECAL_HANDLE handle_, void* buf_, int buf_len_, long long* time_, int rcv_timeout_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);

    std::string buf;
    if (sub->ReceiveBuffer(buf, time_, rcv_timeout_))
    {
      return(CopyBuffer(buf_, buf_len_, buf));
    }
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_Receive_Alloc(ECAL_HANDLE handle_, void** buf_, long long* time_, int rcv_timeout_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);

    std::string buf;
    if (sub->ReceiveBuffer(buf, time_, rcv_timeout_))
    {
      return(CopyBuffer(buf_, ECAL_ALLOCATE_4ME, buf));
    }
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_Receive_Buffer_Alloc(ECAL_HANDLE handle_, void** buf_, int* buf_len_, long long* time_, int rcv_timeout_)
  {
#if ECAL_CORE_SUBSCRIBER
    if (handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);

    std::string buf;
    if (sub->ReceiveBuffer(buf, time_, rcv_timeout_))
    {
      CopyBuffer(buf_, ECAL_ALLOCATE_4ME, buf);
      if (buf_len_) *buf_len_ = static_cast<int>(buf.size());
      return(1);
    }
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_AddReceiveCallback(ECAL_HANDLE handle_, ReceiveCallbackCT callback_, void* par_)
  {
#if ECAL_CORE_SUBSCRIBER
    if(handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    auto callback = std::bind(g_sub_receive_callback, std::placeholders::_1, std::placeholders::_2, callback_, par_);
    if(sub->AddReceiveCallback(callback)) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_RemReceiveCallback(ECAL_HANDLE handle_)
  {
#if ECAL_CORE_SUBSCRIBER
    if(handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    if(sub->RemReceiveCallback()) return(1);
#endif
    return(0);
  }

  ECALC_API int eCAL_Sub_Dump(ECAL_HANDLE handle_, void* buf_, int buf_len_)
  {
#if ECAL_CORE_SUBSCRIBER
    if(handle_ == nullptr) return(0);
    auto* sub = static_cast<eCAL::CSubscriber*>(handle_);
    const std::string dump = sub->Dump();
    if(!dump.empty())
    {
      return(CopyBuffer(buf_, buf_len_, dump));
    }
#endif
    return(0);
  }
}

/////////////////////////////////////////////////////////
// Time
/////////////////////////////////////////////////////////
ECALC_API int eCAL_Time_GetName(void* name_, int name_len_)
{
  const std::string name = eCAL::Time::GetName();
  if (!name.empty())
  {
    return(CopyBuffer(name_, name_len_, name));
  }
  return(0);
}

ECALC_API long long eCAL_Time_GetMicroSeconds()
{
  return(eCAL::Time::GetMicroSeconds());
}

ECALC_API long long eCAL_Time_GetNanoSeconds()
{
  return(eCAL::Time::GetNanoSeconds());
}

ECALC_API int eCAL_Time_SetNanoSeconds(long long time_)
{
  return(eCAL::Time::SetNanoSeconds(time_));
}

ECALC_API int eCAL_Time_IsTimeSynchronized()
{
  return(eCAL::Time::IsSynchronized());
}

ECALC_API int eCAL_Time_IsTimeMaster()
{
  return(eCAL::Time::IsMaster());
}

ECALC_API void eCAL_Time_SleepForNanoseconds(long long duration_nsecs_)
{
  eCAL::Time::SleepForNanoseconds(duration_nsecs_);
}

ECALC_API int eCAL_Time_GetStatus(int* error_, char** status_message_, const int max_len_)
{
  if (max_len_ == ECAL_ALLOCATE_4ME || max_len_ > 0)
  {
    std::string status_message;
    eCAL::Time::GetStatus(*error_, &status_message);

    if (!status_message.empty())
    {
      return CopyBuffer(status_message_, max_len_, status_message);
    }
    return 0;
  }
  else 
  {
    eCAL::Time::GetStatus(*error_, nullptr);
    return 0;
  }
}
