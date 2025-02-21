#include "core/exceptions.hpp"

using namespace suisho;

NotImplementedException::NotImplementedException(const std::string& feature)
: std::logic_error(feature + " is not implemented")
{}

NotImplementedException::NotImplementedException(const char* feature)
: NotImplementedException(std::string(feature))
{}
