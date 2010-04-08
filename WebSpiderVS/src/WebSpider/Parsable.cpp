# include "Parsable.h"

Parsable::Parsable(std::string data) {
	this->data = data;
}

std::string Parsable::getData() const {
	return data;
}
              
