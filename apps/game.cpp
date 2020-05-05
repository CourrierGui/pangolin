#include <iostream>

#include <pangolin/profile.hpp>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

void f2() {
  pgl::profile::PROFILE_FUNCTION();

  int value = 0;
  for (int i=0; i<2000000; ++i) {
    value += 2*i;
  }
}

void f1() {
  pgl::profile::PROFILE_FUNCTION();
  std::this_thread::sleep_for(0.5s);
  f2();
}
int main() {
  pgl::profile::Instrumentor::get().begin_session("Session", "profile.json");

  std::thread thread(f2);
  f1();
  f2();

  thread.join();
  pgl::profile::Instrumentor::get().end_session();

  return 0;
}
