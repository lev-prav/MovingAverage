// TestTask.cpp: определяет точку входа для приложения.
//

#include "moving_average.h"


int main()
{
	double* data_d = new double[10]{ 1,2,3,4,5,6,7,8,9,10 };
	int* data_i{ 0 };

	double data_arr[] = {1,2,3, 4, 5, 6, 7, 8, 9, 10};

	auto val = moving_avarage(data_arr, sizeof(data_arr)/sizeof(data_arr[0]), 5);
	
	for (auto num : val) {
		std::cout << num << " ";
	}
	std::cout << "\n";

	return 0;
}
