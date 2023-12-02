#include "./include/solve.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	unsigned file_count = argc - 1;
	if (file_count == 0) {
		std::cout << "==========You should give the input files' paths==========\n";
		return 1;
	}

	std::vector<std::string> file_name(file_count);
	for (unsigned file_num = 1; file_num <= file_count; ++file_num) {
		file_name[file_num - 1] = argv[file_num];
	}

	std::string input_path;
	std::vector<Valuables> vals;
	unsigned vals_count;
	unsigned max_weight;
	std::vector<unsigned> path;

	for (unsigned file_num = 0; file_num < file_count; ++file_num) {
		std::ifstream file;
		input_path = "./input/" + file_name[file_num];
		file.open(input_path);
		file >> vals_count;
		file >> max_weight;
		vals.resize(vals_count);
		for (unsigned i = 0; i < vals_count; ++i) {
			file >> vals[i].value;
			file >> vals[i].weight;
		}
		file.close();
		unsigned answer = static_cast<unsigned>(-1);
		// std::cout << "\t\t==========Dynamic==========\n";
		answer = get_max_summary_value_dynamic(vals, max_weight, path);
		std::cout << "==========" << file_name[file_num] << "==========";
		std::cout << "\npath:\t";
		print_vec(path);
		std::cout << "The max summary value is: " << answer << std::endl;
		path.clear();
		input_path.clear();
		vals_count = max_weight = 0;
		vals.clear();
	}

	return 0;
}
