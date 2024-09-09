#include "models.hpp"

// ----------------------- SERIALIZATION ---------------------- //


// ----------------------- UTILS ---------------------- //
std::ostream& operator<<(std::ostream& os, const Row& row) {
	// Print the cells in the row
	for (const auto& cell : row.cells) {
		os << cell << ", ";
	}
	return os;
}

