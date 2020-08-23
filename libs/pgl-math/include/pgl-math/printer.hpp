#include <pgl-math/vector.hpp>
#include <pgl-math/matrix.hpp>
#include <pgl-math/quaternion.hpp>

#include <iostream>

template<typename type, int size>
std::ostream& operator<<(std::ostream& os, const pgl::vector<type,size>& vect) {
	const type* e = vect.elements;
	for (int i=0; i<size-1; ++i) {
		os << *(e++) << ' ';
	}
	os << e;
	return os;
}

template<typename type, int rows, int cols>
std::ostream& operator<<(std::ostream& os, const pgl::matrix<type,rows,cols>& mat) {
	for (int i=0; i<rows-1; ++i) {
		const type* elem = mat.elements + i*cols;
		for (const type* it=elem; it!=elem + (cols-1); ++it) {
			os << *it << ' ';
		}
		os << *(elem + (cols-1)) << '\n';
	}
	const type* elem = mat.elements + (rows-1)*cols;
	for (const type* it=elem; it!=elem + (cols-1); ++it) {
		os << *it << ' ';
	}
	os << *(elem + (cols-1));
	return os;
}
