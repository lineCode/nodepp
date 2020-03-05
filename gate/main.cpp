#include "node/log.h"
#include "node/io_service_pool.h"

#include "app.h"

using namespace node;

int main(int argc, const char** argv) {
	logger::init(argv);
	logger::log("log test");

	io_service_pool pool(4);
	auto service(new app(pool));
	if (service->init())
		pool.run();
	delete service;
	return 0;
}
