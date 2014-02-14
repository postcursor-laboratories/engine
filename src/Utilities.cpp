#include "Utilities.hpp"

bool Utilities::stringEndsWith(std::string s, std::string suffix){
    if(suffix.length() > s.length())
	return false;
    return 0==s.compare(s.length()-suffix.length(),suffix.length(),suffix);
}
