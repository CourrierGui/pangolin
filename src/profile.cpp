#include <pangolin/profile.hpp>

#include <algorithm>
#include <thread>

namespace pgl {
  namespace profile {

Instrumentor::Instrumentor() : current_session(nullptr), profile_count(0) {}

void Instrumentor::begin_session(
  const std::string& name,
  const std::string& filepath)
{
  output_stream.open(filepath);
  write_header();
  current_session = new InstrumentationSession{ name };
}

void Instrumentor::end_session() {
  write_footer();
  output_stream.close();
  delete current_session;
  current_session = nullptr;
  profile_count = 0;
}

void Instrumentor::write_profile(const ProfileResult& result) {
  if (profile_count++ > 0)
    output_stream << ",";

  std::string name = result.name;
  std::replace(name.begin(), name.end(), '"', '\'');

  output_stream << "{"
    << "\"cat\":\"function\","
    << "\"dur\":" << (result.end - result.start) << ','
    << "\"name\":\"" << name << "\","
    << "\"ph\":\"X\","
    << "\"pid\":0,"
    << "\"tid\":" << result.thread_id << ","
    << "\"ts\":" << result.start
    << "}";

  output_stream.flush();
}

void Instrumentor::write_header() {
  output_stream << "{\"otherData\": {},\"traceEvents\":[";
  output_stream.flush();
}

void Instrumentor::write_footer() {
  output_stream << "]}";
  output_stream.flush();
}

Instrumentor& Instrumentor::get() {
  static Instrumentor instance;
  return instance;
}

InstrumentationTimer::InstrumentationTimer(const char* name)
  : name(name), start_point(std::chrono::high_resolution_clock::now()),
  stoped(false) { }

void InstrumentationTimer::stop() {
  auto end_point = std::chrono::high_resolution_clock::now();

  long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_point)
    .time_since_epoch().count();
  long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point)
    .time_since_epoch().count();

  uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
  Instrumentor::get().write_profile({name, start, end, thread_id});
  stoped = true;
}

InstrumentationTimer::~InstrumentationTimer() {
  if (!stoped) stop();
}


  } /* end of namespace profile */
} /* end of namespace pgl */

/* void* operator new(std::size_t size) { */
/*   return malloc(size); */
/* } */

/* void operator delete(void* memory, std::size_t size) { */
/*   free(memory); */
/* } */

/* void operator delete(void* memory) { */
/*   free(memory); */
/* } */
