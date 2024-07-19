#include "models.hpp"

std::ostream& operator<<(std::ostream& os, const Column& column) {
	os << "(";
	switch (column.type) {
	case ColumnType::INT:
		os << "INT";
		break;
	case ColumnType::DOUBLE:
		os << "DOUBLE";
		break;
	case ColumnType::STRING:
		os << "STRING";
		break;
	}
	os << ", " << column.name << ")";
	return os;
}