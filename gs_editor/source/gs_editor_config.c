/*==============================================================================================================
    * File: gs_editor_config.c
=================================================================================================================*/ 

/*
 *  Main configuration file for unity build.
 */ 

// Include core configuration file
#include "../../gs_core//source/gs_config.c"

// App configuration file 
#define gs_editor_GENERATED_IMPL
#include "reflection/gs_editor_generated.h"

#define gs_editor_IMPL
#include "gs_editor.h" 

// gs_editor Source Files
#include "reflection/gs_editor_generated.c"

