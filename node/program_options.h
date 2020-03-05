#pragma once
#include <string>
#include <map>
#include <unistd.h>
#include <boost/lexical_cast.hpp>

namespace node {
	class program_options {
	public:
		static std::map<std::string, std::string> Value;

		template<class T> static T get(const std::string& key) {
			return boost::lexical_cast<T>(Value[key]);
		}

		static void parse(const int argc, char** argv) {
			Value["Daemon"] = "0";
			Value["ThreadNum"] = "1";
			int ch = 0;
			while ((ch = getopt(argc, argv, "t:dc:")) != -1) {
				switch(ch) {
					case 't':
						{
							Value["ThreadNum"] = optarg;
						}
						break;
					case 'd':
						{
							Value["Daemon"] = "1";
						}
						break;
					case 'c':
						{
							Value["ConfigFile"] = optarg;
						}
						break;
				}
			}
		}
	};
};
