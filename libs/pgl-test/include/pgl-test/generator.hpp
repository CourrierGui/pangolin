#include <random>

namespace pgl {
	namespace test {

		template<typename type>
			class random_generator {  };

		template<>
			class random_generator<int> {
				private:
					std::mt19937 gen;
					std::uniform_int_distribution<int> distrib;

				public:
					random_generator()
						: gen(std::random_device{}()),
						distrib{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}
					{
					}

					int get() { return distrib(gen); }
			};

	}
}
