#include "models.hpp"

#include <stdexcept>

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	std::visit([&os](const auto& value) {
			os << value;
	}, cell.value);
	return os;
}