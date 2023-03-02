#include <random>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <fstream>
#include "moving_average.h"


template<typename T>
std::vector<T> generate_signal(int signal_size) {
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution distr(-10'000.f, 10'000.f);

	std::vector<T> signal;
	signal.reserve(signal_size);

	for (int i = 0; i < signal_size; ++i) {
		signal.push_back(distr(eng));
	}

	return signal;
}

template<typename T>
long long test(int signal_size, int window_size, bool print = false){

	std::vector<T> random_signal = generate_signal<T>(signal_size);

	auto begin = std::chrono::steady_clock::now();

	std::vector<T> smooth_signal = moving_avarage(random_signal.data(), random_signal.size(), window_size);

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	
	if (print) {
		auto type_name = typeid(random_signal[0]).name();
		{
			char file_name[120];
			std::sprintf(file_name, "signals_random_%s.txt", type_name);

			std::ofstream fout(file_name);

			//fout << "Random signal: \n";
			for (T& num : random_signal) {
				fout << num << " ; ";
			}
			//fout << "\n\n";
		}
		{
			char file_name[120];
			std::sprintf(file_name, "signals_smooth_%s.txt", type_name);

			std::ofstream fout(file_name);

			//fout << "Smooth signal: \n";
			for (T& num : smooth_signal) {
				fout << num << " ; ";
			}
			//fout << "\n\n";
		}
	}


	return elapsed_ms.count();
}


int main(int argc, char** argv) {
	int signal_size = 1'000'000;
	int windows[]{ 4, 8, 16, 32, 64, 128 };
	//std::cout << "Measure double: \n";
	//for (int window_size : windows) {
	//	auto time = test<double>(signal_size, window_size);
	//	std::cout << window_size << " : " << time << " mls \n";
	//}

	//std::cout << "Measure float:\n";
	//for (int window_size : windows) {
	//	auto time = test<float>(signal_size, window_size);
	//	std::cout << window_size << " : " << time << " mls \n";
	//}

	auto time_d = test<double>(signal_size, windows[1], true);
	std::cout << "Double done\n";
	auto time_f = test<float>(signal_size, windows[1], true);
	std::cout << "Float done\n";

	return 0;
}
