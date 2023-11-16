#include "./include/solve.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	size_t file_count = static_cast<size_t>(argc - 1);
	if (file_count == 0)
	{
		std::cout << "==========You should give the input files' paths==========\n";
		return 1;
	}
	std::string input_path;
	std::vector<std::string> file_name(file_count);
	for (size_t file_num = 1; file_num <= file_count; ++file_num)
	{
		file_name[file_num - 1] = argv[file_num];
	}

	std::vector<Valuables> vals;
	size_t vals_count;
	unsigned max_weight;
	std::ifstream file;

	for (size_t file_num = 0; file_num < file_count; ++file_num)
	{
		input_path = "./input" + file_name[file_num];
		file.open(input_path);
		file >> vals_count;
		file >> max_weight;
		vals.resize(vals_count);
		for (size_t i = 0; i < vals_count; ++i)
		{
			file >> vals[i].value;
			file >> vals[i].weight;
		}
		file.close();
		unsigned answer = static_cast<unsigned>(-1);
		if (vals_count < 30 && (1 << vals_count) < vals_count * max_weight) {
			std::cout << "\t\t==========Recursive==========\n";
			answer = get_max_summary_value_recursive(vals, max_weight, 0, max_weight, vals_count - 1);
		} else {
			std::cout << "\t\t==========Dynamic==========\n";
			answer = get_max_summary_value_dynamic(vals, max_weight);
		}
		std::cout << answer << std::endl;
		input_path.clear();
		vals_count = max_weight = 0;
		vals.clear();
	}

	return 0;
}
