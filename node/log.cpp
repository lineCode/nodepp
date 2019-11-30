#include "log.h"
#include <stdarg.h>
#include <stdio.h>

using namespace node;

const int MAX_LOG_SIZE = 4096;
thread_local char buff[MAX_LOG_SIZE];	//thread safe

#define avar(buff, len, pat) \
	va_list ap;\
	va_start(ap, pat);\
	vsnprintf(buff, len-1, pat, ap);\
	buff[len-1] = '\0';\
	va_end(ap);


static void default_log_cb(const char* b)
{
	printf("%s\n", b);
}

std::function<void(const char*)> logger::callback = default_log_cb;

void logger::log(const char* pattern, ...)
{
	avar(buff, MAX_LOG_SIZE, pattern);
	callback(buff);	
}

void logger::init(const char**)
{
	callback = default_log_cb;
}

void logger::set_cb(std::function<void (const char*)> cb)
{
	callback = cb;
}
