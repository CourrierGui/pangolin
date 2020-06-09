#include <pgl-tools/logger.hpp>

int main() {

	for (int i=0; i<2; ++i) {
		PGL_INFO("Hello" << ' ' << "World" << 0);
		PGL_WARN("Toto" << 32.1);
		PGL_ERROR("Titi" << 42);
		PGL_INFO_ONCE("Info once");
		PGL_WARN_ONCE("Warn once");
		PGL_ERROR_ONCE("Error once");
	}
	return 0;
}
