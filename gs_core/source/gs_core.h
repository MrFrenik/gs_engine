/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine
    * File: gs_core.h
    * Github: https://github.com/MrFrenik/gs_engine

    All Rights Reserved

    BSD 3-Clause License

    Copyright (c) 2020 John Jackson

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
    endorse or promote products derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIEDi
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=================================================================================================================*/ 

#ifndef GS_CORE_H
#define GS_CORE_H

// Core systems and data for app
typedef struct gs_core_t
{
    gs_command_buffer_t cb; 
    gs_immediate_draw_t gsi; 
	gs_entity_manager_t	entities;
	gs_asset_manager_t 	assets;
	gs_meta_t 			meta;
    gs_imgui_t          imgui;
    gs_gui_context_t    gsgui;
    gs_mu_ctx_t         gsmui;
} gs_core_t;

GS_API_DECL gs_core_t* gs_core_new();
GS_API_DECL void gs_core_delete(gs_core_t* core);

#ifdef GS_CORE_IMPL

GS_API_DECL gs_core_t* gs_core_new()
{
	gs_core_t* core = gs_malloc_init(gs_core_t);

    //=== [ Structures ] ===// 
	
    core->cb = gs_command_buffer_new();
    core->gsi = gs_immediate_draw_new(gs_platform_main_window());

	//=== [ Meta ] ====//
	
	core->meta = gs_meta_new();
	gs_meta_set_instance(&core->meta); 

	// Register gunslinger meta information
	gs_meta_register_gs(&core->meta); 

	// Register all generated meta information
	gs_meta_register_generated(&core->meta);

    //=== [ ImGui ] ===// 
    
    gs_imgui_context_new(&core->imgui, gs_platform_main_window(), false); 

    //=== [ GUI ] ===// 

    gs_gui_init(&core->gsgui, gs_platform_main_window());

    //=== [ MicroUI ] ===// 
    core->gsmui = gs_mu_new(gs_platform_main_window()); 

	//=== [ Assets ] ====//
	
	// Initialize asset manager with root assets path
    const char* assets_path = gs_platform_dir_exists("./assets/") ? "./assets" : "../assets";
	gs_assets_init(&core->assets, assets_path);

	//==== [ Entity ] ===//

    // Init entity manager
    gs_entity_manager_init(&core->entities);
	
	// Register core components	
	gs_entities_register_component(&core->entities, gs_component_transform_t);
	gs_entities_register_component(&core->entities, gs_component_physics_t);
	gs_entities_register_component(&core->entities, gs_component_static_mesh_t);

	return core;
}

GS_API_DECL void gs_core_delete(gs_core_t* core)
{
    gs_immediate_draw_free(&core->gsi);
    gs_command_buffer_free(&core->cb); 
}


#endif // GS_CORE_IMPL
#endif // GS_CORE_H

