#include <string>
#include <cmath>
#include <fstream>

#include "tests/test.hpp"
#include "matrix.hpp"

int main(int argc, char **argv) {
	if (argc == 1) {
		test();
		return 0;
	}
	if (argv[1] == std::string("-p")) {
		Matrix<float> projection = Matrix<float>::projection(M_PI, 16. / 9., 1., 100.);
		std::ofstream output;
		output.open("matrix_display/proj");
		if (!output.is_open()) {
			return 1;
		}
		projection.foreach([&output](float& element, size_t row, size_t column) {
			(void)row;
			output << element;
			if (column == 3) {
				output << "\n";
			} else {
				output << ", ";
			}
		});
	}
}
