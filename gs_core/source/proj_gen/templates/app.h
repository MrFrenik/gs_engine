/*==============================================================================================================
    * File: %APP_NAME%.h
=================================================================================================================*/

#ifndef %APP_NAME%_H
#define %APP_NAME%_H 

// App struct declaration 
typedef struct %APP_NAME%_t
{
    // Core data
    gs_core_t* core; 

    // Your app data here...
    gs_asset_handle_t tex;

} %APP_NAME%_t; 

// Main application interface functions
GS_API_DECL gs_app_desc_t %APP_NAME%_main(int32_t argc, char** argv);
GS_API_DECL void %APP_NAME%_init();
GS_API_DECL void %APP_NAME%_update();
GS_API_DECL void %APP_NAME%_shutdown(); 

// == [ Appplication Implementation ] == // 

#ifdef %APP_NAME%_IMPL 

GS_API_DECL void %APP_NAME%_init()
{
    // Initialize core
    %APP_NAME%_t* app = gs_engine_user_data(%APP_NAME%_t); 
    app->core = gs_core_new(); 

    // Register reflection for %APP_NAME%
    %APP_NAME%_meta_register_generated(&app->core->meta);

    // Import texture into asset manager
    app->tex = gs_assets_import(&app->core->assets, "../../gs_core/assets/textures/logo.png", NULL, false);
} 

GS_API_DECL void %APP_NAME%_update()
{
    // Cache app/core pointers
    %APP_NAME%_t* app = gs_engine_user_data(%APP_NAME%_t);
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
    gsi_text(gsi, 340.f, 300.f, "Project: %APP_NAME%", NULL, false, 255, 255, 255, 255); 
    gsi_texture(gsi, tex->texture.hndl);
    gsi_rectvd(gsi, gs_v2(150.f, 150.f), gs_v2(500.f, 500.f * 0.18f), gs_v2s(0.f), gs_v2s(1.f), GS_COLOR_WHITE, GS_GRAPHICS_PRIMITIVE_TRIANGLES);

    // Submit immediate draw render pass
    gsi_render_pass_submit(gsi, cb, gs_color(10, 10, 10, 255));

    // Submit command buffer for rendering
    gs_graphics_submit_command_buffer(cb); 
}

GS_API_DECL void %APP_NAME%_shutdown()
{
    %APP_NAME%_t* app = gs_engine_user_data(%APP_NAME%_t); 
    gs_core_delete(app->core); 
} 
        
GS_API_DECL gs_app_desc_t %APP_NAME%_main(int32_t argc, char** argv)
{
    return (gs_app_desc_t) 
    {
        .window_width = 800,
        .window_height = 400,
        .init = %APP_NAME%_init,
        .update = %APP_NAME%_update,
        .shutdown = %APP_NAME%_shutdown,
        .user_data = gs_malloc_init(%APP_NAME%_t)
    };
} 

#endif  // %APP_NAME%_IMPL 
#endif  // %APP_NAME%_H 

%END%
