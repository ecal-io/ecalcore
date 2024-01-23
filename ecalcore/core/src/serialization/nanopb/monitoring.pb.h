/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9-dev */

#ifndef PB_ECAL_PB_MONITORING_PB_H_INCLUDED
#define PB_ECAL_PB_MONITORING_PB_H_INCLUDED
#include <pb.h>
#include "host.pb.h"
#include "process.pb.h"
#include "service.pb.h"
#include "topic.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _eCAL_pb_LogMessage {
    int64_t time; /* time */
    pb_callback_t hname; /* host name */
    int32_t pid; /* process id */
    pb_callback_t pname; /* process name */
    pb_callback_t uname; /* unit name */
    int32_t level; /* message level */
    pb_callback_t content; /* message content */
} eCAL_pb_LogMessage;

typedef struct _eCAL_pb_LogMessageList {
    pb_callback_t log_messages; /* log messages */
} eCAL_pb_LogMessageList;

typedef struct _eCAL_pb_Monitoring {
    pb_callback_t hosts; /* hosts */
    pb_callback_t processes; /* processes */
    pb_callback_t services; /* services */
    pb_callback_t topics; /* topics */
    pb_callback_t clients; /* clients */
} eCAL_pb_Monitoring;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define eCAL_pb_LogMessage_init_default          {0, {{NULL}, NULL}, 0, {{NULL}, NULL}, {{NULL}, NULL}, 0, {{NULL}, NULL}}
#define eCAL_pb_LogMessageList_init_default      {{{NULL}, NULL}}
#define eCAL_pb_Monitoring_init_default          {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define eCAL_pb_LogMessage_init_zero             {0, {{NULL}, NULL}, 0, {{NULL}, NULL}, {{NULL}, NULL}, 0, {{NULL}, NULL}}
#define eCAL_pb_LogMessageList_init_zero         {{{NULL}, NULL}}
#define eCAL_pb_Monitoring_init_zero             {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define eCAL_pb_LogMessage_time_tag              1
#define eCAL_pb_LogMessage_hname_tag             2
#define eCAL_pb_LogMessage_pid_tag               3
#define eCAL_pb_LogMessage_pname_tag             4
#define eCAL_pb_LogMessage_uname_tag             5
#define eCAL_pb_LogMessage_level_tag             6
#define eCAL_pb_LogMessage_content_tag           7
#define eCAL_pb_LogMessageList_log_messages_tag  1
#define eCAL_pb_Monitoring_hosts_tag             1
#define eCAL_pb_Monitoring_processes_tag         2
#define eCAL_pb_Monitoring_services_tag          3
#define eCAL_pb_Monitoring_topics_tag            4
#define eCAL_pb_Monitoring_clients_tag           5

/* Struct field encoding specification for nanopb */
#define eCAL_pb_LogMessage_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT64,    time,              1) \
X(a, CALLBACK, SINGULAR, STRING,   hname,             2) \
X(a, STATIC,   SINGULAR, INT32,    pid,               3) \
X(a, CALLBACK, SINGULAR, STRING,   pname,             4) \
X(a, CALLBACK, SINGULAR, STRING,   uname,             5) \
X(a, STATIC,   SINGULAR, INT32,    level,             6) \
X(a, CALLBACK, SINGULAR, STRING,   content,           7)
#define eCAL_pb_LogMessage_CALLBACK pb_default_field_callback
#define eCAL_pb_LogMessage_DEFAULT NULL

#define eCAL_pb_LogMessageList_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  log_messages,      1)
#define eCAL_pb_LogMessageList_CALLBACK pb_default_field_callback
#define eCAL_pb_LogMessageList_DEFAULT NULL
#define eCAL_pb_LogMessageList_log_messages_MSGTYPE eCAL_pb_LogMessage

#define eCAL_pb_Monitoring_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  hosts,             1) \
X(a, CALLBACK, REPEATED, MESSAGE,  processes,         2) \
X(a, CALLBACK, REPEATED, MESSAGE,  services,          3) \
X(a, CALLBACK, REPEATED, MESSAGE,  topics,            4) \
X(a, CALLBACK, REPEATED, MESSAGE,  clients,           5)
#define eCAL_pb_Monitoring_CALLBACK pb_default_field_callback
#define eCAL_pb_Monitoring_DEFAULT NULL
#define eCAL_pb_Monitoring_hosts_MSGTYPE eCAL_pb_Host
#define eCAL_pb_Monitoring_processes_MSGTYPE eCAL_pb_Process
#define eCAL_pb_Monitoring_services_MSGTYPE eCAL_pb_Service
#define eCAL_pb_Monitoring_topics_MSGTYPE eCAL_pb_Topic
#define eCAL_pb_Monitoring_clients_MSGTYPE eCAL_pb_Client

extern const pb_msgdesc_t eCAL_pb_LogMessage_msg;
extern const pb_msgdesc_t eCAL_pb_LogMessageList_msg;
extern const pb_msgdesc_t eCAL_pb_Monitoring_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define eCAL_pb_LogMessage_fields &eCAL_pb_LogMessage_msg
#define eCAL_pb_LogMessageList_fields &eCAL_pb_LogMessageList_msg
#define eCAL_pb_Monitoring_fields &eCAL_pb_Monitoring_msg

/* Maximum encoded size of messages (where known) */
/* eCAL_pb_LogMessage_size depends on runtime parameters */
/* eCAL_pb_LogMessageList_size depends on runtime parameters */
/* eCAL_pb_Monitoring_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
