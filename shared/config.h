#pragma once
#include <cstdint>


class Config
{
public:
	Config();
	~Config();
public:
	static Config& Instance() {
		//thread safe
		static Config s;
		return s;
	}

};

#define sConfig Config::Instance()
