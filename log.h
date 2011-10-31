#ifndef LOG_H_
#define LOG_H_
#include <iostream>
#include <stdint.h>
enum LogLevel {
  LOG_NONE           = 0x00000000, // no logging

  LOG_ERROR          = 0x00000001, // serious error messages only
  LOG_LEVEL_ERROR    = 0x00000001,

  LOG_WARN           = 0x00000002, // warning messages
  LOG_LEVEL_WARN     = 0x00000003,

  LOG_DEBUG          = 0x00000004, // rare ad-hoc debug messages
  LOG_LEVEL_DEBUG    = 0x00000007,

  LOG_INFO           = 0x00000008, // informational messages (e.g., banners)
  LOG_LEVEL_INFO     = 0x0000000f,

  LOG_FUNCTION       = 0x00000010, // function tracing
  LOG_LEVEL_FUNCTION = 0x0000001f,

  LOG_LOGIC          = 0x00000020, // control flow tracing within functions
  LOG_LEVEL_LOGIC    = 0x0000003f,

  LOG_ALL            = 0x1fffffff, // print everything
  LOG_LEVEL_ALL      = LOG_ALL,

  LOG_PREFIX_FUNC    = 0x80000000, // prefix all trace prints with function
  LOG_PREFIX_TIME    = 0x40000000, // prefix all trace prints with simulation time
  LOG_PREFIX_NODE    = 0x20000000  // prefix all trace prints with simulation node
};

#define LOG_COMPONENT_DEFINE(name)                           \
  static LogComponent g_log = LogComponent (name)

#define LOG_APPEND_TIME_PREFIX                               \

#define LOG_APPEND_NODE_PREFIX                               \

#define LOG_APPEND_FUNC_PREFIX                               \

#define LOG_APPEND_FUNC_PREFIX                               \



#define LOG(level, msg)                                      \
  do                                                            \
    {                                                           \
      if (g_log.IsEnabled (level))                              \
        {                                                       \
          LOG_APPEND_TIME_PREFIX;                            \
          LOG_APPEND_NODE_PREFIX;                            \
          LOG_APPEND_CONTEXT;                                \
          LOG_APPEND_FUNC_PREFIX;                            \
          std::clog << msg << std::endl;                        \
        }                                                       \
    }                                                           \
  while (false)

#define LOG_ERROR(msg) \
  NS_LOG (LOG_ERROR, msg)

#define LOG_WARN(msg) \
  NS_LOG (LOG_WARN, msg)

#define LOG_DEBUG(msg) \
  NS_LOG (LOG_DEBUG, msg)

#define LOG_INFO(msg) \
  NS_LOG (LOG_INFO, msg)

#ifdef LOG_ENABLE

#define NS_LOG(level, msg)
#define NS_LOG_ERROR(msg)
#define NS_LOG_WARN(msg)
#define NS_LOG_DEBUG(msg)
#define NS_LOG_INFO(msg)
#define NS_LOG_FUNCTION_NOARGS()
#define NS_LOG_FUNCTION(msg)
#define NS_LOG_LOGIC(msg)
#define NS_LOG_UNCOND(msg)

#else /* LOG_ENABLE */

#define NS_LOG(level, msg)
#define NS_LOG_ERROR(msg)
#define NS_LOG_WARN(msg)
#define NS_LOG_DEBUG(msg)
#define NS_LOG_INFO(msg)
#define NS_LOG_FUNCTION_NOARGS()
#define NS_LOG_FUNCTION(msg)
#define NS_LOG_LOGIC(msg)
#define NS_LOG_UNCOND(msg)

#endif /* LOG_ENABLE */

class LogComponent {
public:
  LogComponent (char const *name);
//  void EnvVarCheck (char const *name);
  bool IsEnabled (enum LogLevel level) const;
  bool IsNoneEnabled (void) const;
  void Enable (enum LogLevel level);
  void Disable (enum LogLevel level);
  char const *Name (void) const;
private:
  int32_t     m_levels;
  char const *m_name;
};

#endif
