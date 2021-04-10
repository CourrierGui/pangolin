#include <pgl-tools/logger.hpp>

void test_logs() {
  for (int i=0; i<2; ++i) {
    PglInfo  << "Hello" << ' ' << "World" << 0 << '\n';
    PglWarn  << "Toto" << 32.1 << '\n';
    PglError << "Titi" << 42 << '\n';

    PglInfoOnce  << "Info once\n";
    PglWarnOnce  << "Warn once\n";
    PglErrorOnce << "Error once\n";
  }
}

int main() {
  test_logs();
  return 0;
}
