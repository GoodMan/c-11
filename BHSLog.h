#include <iostream>
#include <string>
#include <iomanip>

#ifndef BHSLOG_H
#define BHSLOG_H

#define BHS_DEBUG		\
		std::cerr << __FILE__ << "(" << std::setw( 5 ) << std::setfill( '0' ) << __LINE__ << ") "

#define BHS_FUNC	\
		BHS_DEBUG << __func__ << " "

#define BHS_FUNC_START	\
		BHS_FUNC << "START" << std::endl

#define BHS_THREAD_FUNC_START	\
		BHS_FUNC << "START " << std::this_thread::get_id() << std::endl

#define BHS_FUNC_END  	\
		BHS_FUNC << "END" << std::endl

#define BHS_THREAD_FUNC_END	\
		BHS_FUNC << "END " << std::this_thread::get_id() << std::endl

#endif	//	BHSLOG_H
