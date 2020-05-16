#pragma once

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#ifdef PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__line__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_FUNCTION()
#endif

/* void* operator new(std::size_t size); */
/* void  operator delete(void* memory, std::size_t size); */
/* void  operator delete(void* memory); */

namespace pgl {
  namespace profile {

struct ProfileResult {
  std::string name;
  long long start, end;
  uint32_t thread_id;
};

struct InstrumentationSession {
  std::string Name;
};

class Instrumentor {
  private:
    InstrumentationSession* current_session;
    std::ofstream           output_stream;
    int                     profile_count;

    void write_header();
    void write_footer();

  public:
    Instrumentor();
    void begin_session(const std::string& name, const std::string& filepath);
    void end_session();
    void write_profile(const ProfileResult& result);
    static Instrumentor& get();
};

class InstrumentationTimer {
  public:
    InstrumentationTimer(const char* name);
    ~InstrumentationTimer();
    void stop();

  private:
    const char* name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_point;
    bool stoped;
};

  } /* end of namespace profile */
} /* end of namespace pgl */
