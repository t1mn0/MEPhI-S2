#include "Sequence.hpp"
#include "Exception.hpp"

template<typename T>
bool Sequence<T>::empty() const {
	if (this->get_size() == 0) {
		return true;
	}
	return false;
}

template<typename T>
T Sequence<T>::front() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return get(0);
}

template<typename T>
T Sequence<T>::back() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return get(this->get_size() - 1);
}