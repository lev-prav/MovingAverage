#pragma once
#include <iostream>
#include <vector>
#include <cassert>

template<typename T>
using specializtion = std::enable_if_t <std::is_floating_point<T>::value>;


template<typename T, typename = specializtion<T>>
std::vector<T> moving_avarage(T* data, int data_size, int window_size) {
	std::cout << "Coming soon...\n";
	/*assert(data != NULL);
	assert(data_size > 0);
	assert(0 < window_size && window_size <= data_size);*/

	T sum = 0, window_koef = T(window_size);
	for (int i = 0; i < window_size; i++) {
		sum += *(data + i);
	}
	std::cout << sum<<"\n"; 

	std::vector<T> smooth_data{sum/window_koef};
	smooth_data.reserve(data_size - window_size + 1);

	for (int i = 0, window_end = window_size; window_end < data_size; window_end++, i++) {
		int window_start = window_end - window_size;
		T window_sum = sum - data[window_start] + data[window_end];
		smooth_data.push_back(window_sum / window_koef);
		sum = window_sum; 
	}

	return smooth_data;
}