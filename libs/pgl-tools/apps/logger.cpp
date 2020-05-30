#include <pgl-tools/logger.hpp>

int main() {
	PGL_INFO("Hello" << ' ' << "World" << 0);
	PGL_WARN("Toto" << 32.1);
	PGL_ERROR("Titi" << 42);

	for (int i=0; i<2; ++i) {
		PGL_INFO_ONCE("Hello once");
		PGL_WARN_ONCE("Hello once");
		PGL_ERROR_ONCE("Hello once");
	}
	return 0;
}
