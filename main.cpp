#include <random>
#include <iomanip>
#include <chrono>
#include <iostream>
#include "moving_average.h"


template<typename T>
std::vector<T>&& generate_signal(int signal_size) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<T> distr(-10'000.f, 10'000.f);

	std::vector<T> signal;
	signal.reserve(signal_size);

	for (int i = 0; i < signal_size; ++i) {
		signal.push_back(distr(eng));
	}

	return std::move(signal)
}

template<typename T>
long long test(int signal_size, int window_size, bool print = false){

	std::vector<T> random_signal = generate_signal(signal_size);

	auto begin = std::chrono::steady_clock::now();

	std::vector<T> smooth_signal = moving_avarage(random_signal.data(), random_signal.size(), window_size);

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	
	if (print) {
		std::cout << "Random signal: \n";
		for (T& num : random_signal) {
			std::cout << num << " ";
		}
		std::cout << "\n\n";

		std::cout << "Smooth signal: \n";
		for (T& num : smooth_signal) {
			std::cout << num << " ";
		}
		std::cout << "\n\n";
	}


	return elapsed_ms.count();
}


int main(int argc, char** argv) {
	
	auto time = test<double>(1024, 8);

	return 0;
}
