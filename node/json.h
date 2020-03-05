#pragma once

#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

class json_file
{
public:
	json_file(const std::string& f);

private:
	ptree pt_;
};
