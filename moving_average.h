#pragma once
#include <iostream>
#include <vector>

template<typename T>
constexpr bool is_float_or_double = std::is_same<T, float>::value || std::is_same<T, double>::value;


template<typename T, typename = std::enable_if_t <is_float_or_double<T>>>
std::vector<T>
moving_avarage(T* data, int data_size, int window_size) {
	std::cout << "Coming soon...\n";

	return std::vector <T>();
}