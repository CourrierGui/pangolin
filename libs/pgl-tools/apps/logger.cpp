#include <pgl-tools/logger.hpp>

int main() {
	PGL_INFO("Hello" << ' ' << "World" << 0);
	PGL_WARN("Toto" << 32.1);
	PGL_ERROR("Titi" << 42);
	return 0;
}
