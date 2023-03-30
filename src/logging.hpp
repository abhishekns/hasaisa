#include <iostream>

namespace logging {

static int loggingEnabled = 0;

inline void enableLogging() {
    loggingEnabled = 1;
}

inline void disableLogging() {
    loggingEnabled = 0;
}

#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__
        #define __LINE_NO__
        #define __FILE_NAME__
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__
        #define __LINE_NO__ __LINE__
        #define __FILE_NAME__ __FILE__
    #endif
#endif

#define TRACE(x) if (loggingEnabled) std::cout  << __TIMESTAMP__  << ":" << __FILE_NAME__ << ":" << __FUNCTION_NAME__  << ":" << __LINE_NO__ << x <<std::endl;

#define TRACE_FUNC_START    TRACE(": start")
#define TRACE_FUNC_END      TRACE(": end")

}
