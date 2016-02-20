#include <iostream>
#include <string>
#include <thread>
#include <future>

#include "BHSLog.h"

void threadFunction( std::promise< std::string > && pms ) 
{
	BHS_FUNC_START;

	std::string str( "Hello world from future!" );

	pms.set_value( str );
	BHS_FUNC_END;
}

int main()
{
	BHS_FUNC_START;

	std::promise< std::string > pms;

	std::future< std::string > ftr = pms.get_future();

	std::thread objThread( &threadFunction, std::move( pms ) );

	BHS_DEBUG << "Hello world from main()" << std::endl;

	std::string str = ftr.get();

	BHS_DEBUG << "str from future=(" << str << ")" << std::endl;

	objThread.join();

	BHS_FUNC_END;;
	return 0;
}
