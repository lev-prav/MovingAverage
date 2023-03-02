#pragma once
#include <vector>
#include <cassert>

template<typename T>
using specializtion = std::enable_if_t <std::is_floating_point<T>::value>;


template<typename T, typename = specializtion<T>>
std::vector<T>&& moving_avarage(T* signal, int signal_length, int window_size) {

	assert(0 < window_size && window_size <= data_size);

	T sum = 0, window_koef = T(window_size);
	for (int i = 0; i < window_size; i++) {
		sum += data[i];
	}

	std::vector<T> smooth_data{sum/window_koef};
	smooth_data.reserve(signal_length - window_size + 1);

	for (int i = 0, window_end = window_size; window_end < signal_length; window_end++, i++) {
		int window_start = window_end - window_size;
		T window_sum = sum - data[window_start] + data[window_end];
		smooth_data.push_back(window_sum / window_koef);
		sum = window_sum; 
	}

	return std::move(smooth_data);
}