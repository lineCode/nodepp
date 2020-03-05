#pragma once

#include <functional>

namespace node {
	class logger {
	public:
		static void init(char**);

		static void log(const char* pattern, ...);

		static void set_cb(std::function<void(const char*)>);
	private:
		static std::function<void(const char*)> callback;
	};
};
