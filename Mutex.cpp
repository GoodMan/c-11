#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <exception>

#include "BHSLog.h"

std::map< std::string, std::string > actions;
std::mutex							 mutexActions;


void meets( const std::string & whom )
{
	BHS_THREAD_FUNC_START;

	std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	std::string result( "this is " );
	result += whom;

	mutexActions.lock();

	actions[ whom ] = result;

	mutexActions.unlock();

	BHS_THREAD_FUNC_END;
}

int main()
{
	BHS_FUNC_START;

	BHS_DEBUG << std::endl;

	try {
		std::thread Cipher( meets, std::string( "Agent" ) );

		BHS_DEBUG << std::endl;
		std::thread Neo( meets, "Morpheus" );

		BHS_DEBUG << std::endl;

		if ( Cipher.joinable() ) {
			BHS_DEBUG << "Cipher.joinable()" << std::endl;
			Cipher.join();
		}

		BHS_DEBUG << std::endl;

		if ( Neo.joinable() ) {
			BHS_DEBUG << "Neo.joinable()" << std::endl;
			Neo.join();
		}
	} catch( std::exception &e ) {
//		std::exception_ptr ePtr = std::current_exception();
//
//		BHS_DEBUG << ePtr.what() << std::endl;
		BHS_DEBUG << e.what() << std::endl;
	}

	BHS_DEBUG << std::endl;

	mutexActions.lock();

	for( const auto &pair : actions ) {
		std::cout << pair.first << " => " << pair.second << std::endl;
	}

	BHS_DEBUG << "call mutexActions.unlock()" << std::endl;
	mutexActions.unlock();

	BHS_DEBUG << "call mutexActions.unlock() again" << std::endl;
	mutexActions.unlock();

	BHS_FUNC_END;
}
