// **********************************************************************
//
// Copyright (c) 2012-2013 Bernard Luo. All rights reserved.
//
// <Email: luo (dot) xiaowei (at) hotmail (dot) com>
//
// **********************************************************************

#ifndef TESTING_CONFIG_H
#define TESTING_CONFIG_H

#include <Build/BuildConfig.h>
//
// NAMESPACE 
//
#if defined(__cplusplus)
#    define TESTING_BEGIN            namespace Testing {
#    define TESTING_END                }
#    define USING_TESTING            using namespace Testing;
#    define TESTING                    ::Testing::

#else // __cplusplus

#    define TESTING_BEGIN            
#    define TESTING_END                
#    define USING_TESTING            
#    define TESTING                    

#endif // __cplusplus


#ifndef TESTING_API
#   ifdef TESTING_API_EXPORTS
#       define TESTING_API DECLSPEC_EXPORT
#    else
#       define TESTING_API DECLSPEC_IMPORT
#    endif
#endif


#endif //TESTING_CONFIG_H
