/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Gunslinger Editor
    * File: gs_editor.h
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

#ifndef gs_editor_H
#define gs_editor_H 

// App struct declaration 
typedef struct gs_editor_t
{
    // Core data
    gs_core_t* core; 

    // Your app data here...
    gs_asset_handle_t tex;

} gs_editor_t; 

// Main application interface functions
GS_API_DECL gs_app_desc_t gs_editor_main(int32_t argc, char** argv);
GS_API_DECL void gs_editor_init();
GS_API_DECL void gs_editor_update();
GS_API_DECL void gs_editor_shutdown(); 

// == [ Appplication Implementation ] == // 

#ifdef gs_editor_IMPL 

GS_API_DECL void gs_editor_init()
{
    // Initialize core
    gs_editor_t* app = gs_engine_user_data(gs_editor_t); 
    app->core = gs_core_new(); 

    // Register reflection for gs_editor
    gs_editor_meta_register_generated(&app->core->meta);

    // Import texture into asset manager
    app->tex = gs_assets_import(&app->core->assets, "../../gs_core/assets/textures/logo.png", NULL, false);
} 

GS_API_DECL void gs_editor_update()
{
    // Cache app/core pointers
    gs_editor_t* app = gs_engine_user_data(gs_editor_t);
    gs_core_t* core = app->core;
    gs_command_buffer_t* cb = &core->cb;
    gs_immediate_draw_t* gsi = &core->gsi; 
    gs_entity_manager_t* em = &core->entities; 
    gs_mu_ctx* gmu = &core->gmu;

    // Get necessary platform metrics
    const gs_vec2 fb = gs_platform_framebuffer_sizev(gs_platform_main_window());
    const gs_vec2 ws = gs_platform_window_sizev(gs_platform_main_window()); 

    // Process input (closing window) 
    if (gs_platform_key_pressed(GS_KEYCODE_ESC)) gs_engine_quit(); 

    // Update entity manager
    gs_entities_update(em); 

    // Get texture
    gs_texture_t* tex = gs_asset_handle_get(&app->tex); 

    // Render hello to screen
    gsi_camera2D(gsi);
    gsi_text(gsi, 340.f, 300.f, "Project: gs_editor", NULL, false, 255, 255, 255, 255); 
    gsi_texture(gsi, tex->texture.hndl);
    gsi_rectvd(gsi, gs_v2(150.f, 150.f), gs_v2(500.f, 500.f * 0.18f), gs_v2s(0.f), gs_v2s(1.f), GS_COLOR_WHITE, GS_GRAPHICS_PRIMITIVE_TRIANGLES);

    // Submit immediate draw render pass
    gsi_render_pass_submit(gsi, cb, gs_color(10, 10, 10, 255));

    // Submit command buffer for rendering
    gs_graphics_submit_command_buffer(cb); 
}

GS_API_DECL void gs_editor_shutdown()
{
    gs_editor_t* app = gs_engine_user_data(gs_editor_t); 
    gs_core_delete(app->core); 
} 
        
GS_API_DECL gs_app_desc_t gs_editor_main(int32_t argc, char** argv)
{
    return (gs_app_desc_t) 
    {
        .window_width = 800,
        .window_height = 400,
        .init = gs_editor_init,
        .update = gs_editor_update,
        .shutdown = gs_editor_shutdown,
        .user_data = gs_malloc_init(gs_editor_t)
    };
} 

#endif  // gs_editor_IMPL 
#endif  // gs_editor_H 

