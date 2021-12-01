/*==============================================================================================================
    * File: %APP_NAME%_main.c 
=================================================================================================================*/ 

/*
 * Main file for hooks into gunslinger backend. Sets up application to run.
 */

#include "%APP_NAME%_config.c" 

gs_app_desc_t gs_main(int32_t argc, char** argv)
{ 
    return %APP_NAME%_main(argc, argv);
}

%END%
