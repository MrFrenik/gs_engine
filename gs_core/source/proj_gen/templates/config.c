/*==============================================================================================================
    * File: %APP_NAME%_config.c
=================================================================================================================*/ 

/*
 *  Main configuration file for unity build.
 */ 

// Include core configuration file
#include "%CORE_DIR%/source/gs_config.c"

// App configuration file 
#define %APP_NAME%_GENERATED_IMPL
#include "reflection/%APP_NAME%_generated.h"

#define %APP_NAME%_IMPL
#include "%APP_NAME%.h" 

// %APP_NAME% Source Files
#include "reflection/%APP_NAME%_generated.c"

%END%
