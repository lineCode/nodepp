#include "program_options.h"

using namespace node;

//TODO: not thread safe
//it should read only.
std::map<std::string, std::string> program_options::Value;
