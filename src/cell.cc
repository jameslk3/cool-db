#include "models.hpp"

#include <stdexcept>
#include <iostream>


// ----------------------- SERIALIZATION ---------------------- //
void Cell::serialize(std::ostream& os) const {
	uint8_t type = static_cast<uint8_t>(value.index());
	os.write(reinterpret_cast<const char*>(&type), sizeof(type));

	std::visit([&os](const auto& val) {
    using T = std::decay_t<decltype(val)>;
		if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
			os.write(reinterpret_cast<const char*>(&val), sizeof(val));
		} else if constexpr (std::is_same_v<T, std::string>) {
    uint32_t size = val.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(val.c_str(), size);
		}
	}, value);
}

void Cell::deserialize(std::istream& is) {
	uint8_t type;
	is.read(reinterpret_cast<char*>(&type), sizeof(type));

	switch (type) {
	case 0: { // int
		int val;
		is.read(reinterpret_cast<char*>(&val), sizeof(val));
		value = val;
		break;
	}
	case 1: { // double
		double val;
		is.read(reinterpret_cast<char*>(&val), sizeof(val));
		value = val;
		break;
	}
	case 2: { // string
    uint32_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::string val(size, '\0');
    is.read(&val[0], size);
    value = val;
    break;
	}
	default:
		throw std::runtime_error("Invalid type");
	}
}

// --------------------------- UTILS --------------------------- //
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	std::visit([&os](const auto& value) {
			os << value;
	}, cell.value);
	return os;
}