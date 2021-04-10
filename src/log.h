#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <syslog.h>

#include <iostream>
#include <streambuf>
#include <string>

enum LogPriority {
  kLogEmerg = LOG_EMERG,      // system is unusable
  kLogAlert = LOG_ALERT,      // action must be taken immediately
  kLogCrit = LOG_CRIT,        // critical conditions
  kLogErr = LOG_ERR,          // error conditions
  kLogWarning = LOG_WARNING,  // warning conditions
  kLogNotice = LOG_NOTICE,    // normal, but significant, condition
  kLogInfo = LOG_INFO,        // informational message
  kLogDebug = LOG_DEBUG       // debug-level message
};

std::ostream& operator<<(std::ostream& os, const LogPriority& log_priority);

class Log : public std::basic_streambuf<char, std::char_traits<char> > {
  // https://stackoverflow.com/questions/2638654/
 public:
  explicit Log(std::string ident, int facility);
  // ~ destructor?
  // closelog();
  // // LOG_USER?
  // MACRO around debug?

 protected:
  int sync();
  int overflow(int c);

 private:
  friend std::ostream& operator<<(std::ostream& os,
                                  const LogPriority& log_priority);
  std::string buffer_;
  int facility_;
  int priority_;
  char ident_[50];
};

#endif  // SRC_LOG_H_
