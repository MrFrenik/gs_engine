/*==============================================================================================================
    * File: gs_editor_main.c 
=================================================================================================================*/ 

/*
 * Main file for hooks into gunslinger backend. Sets up application to run.
 */

#include "gs_editor_config.c" 

gs_app_desc_t gs_main(int32_t argc, char** argv)
{ 
    return gs_editor_main(argc, argv);
}

