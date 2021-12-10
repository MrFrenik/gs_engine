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

// Main menu
// Dockspace
// Editor views
// Load/Reload/Unload application
// Sandbox for play
// Core update...?

/*
    From Enjon: 

    // Grab the context from core for your window
    GUIContext* ctx = window->GetGUIContext( );

    // Register main menu option
    ctx->RegisterMenuOption( "View", mName, [ & ] ( )
    {
        ImGui::MenuItem( Utils::format( "%s##options%zu", mName.c_str(), (u32)(usize)this ).c_str( ), NULL, &mViewEnabled );
    });

    // Register imgui window 
    ctx->RegisterWindow( mName, [ & ] ( )
    {
        // Docking windows
        if ( ImGui::BeginDock( GetViewName().c_str(), &mViewEnabled, GetViewFlags() ) )
        {
            Update( );
        }
        ImGui::EndDock( ); 
    }); 

    // Register docking layout with context
    guiContext->RegisterDockingLayout( GUIDockingLayout( "Inspector", "World Outliner", GUIDockSlotType::Slot_Top, 0.50f ) ); 

    // Example for simple view 

    typedef void (* gs_imgui_window_func)(gs_imgui_ctx_t* ctx, void* user_data); 

    typedef struct gs_editor_view_data_t
    {
        const char* category;
        const char* name;
        uint32_t flags;
        bool32 enabled;
        gs_imgui_window_func func;
        uint32_t window_handle;
    } gs_editor_view_data_t;

    typedef gs_editor_view_data_t gs_editor_view_desc_t;

    typedef struct gs_editor_t
    {
        gs_hash_table(uint64_t, gs_editor_view_data_t*) view_data;
    } gs_editor_t;

    GS_API_DECL void gs_editor_view_create(gs_editor_t* editor, gs_editor_view_desc_t* desc)
    { 
        gs_core_t* core = &editor->core;
        gs_imgui_t* gimgui = &core->imgui; 
        gs_imgui_ctx_t* ctx = gs_imgui_get_context(gimgui, desc->window_handle);
        gs_assert(ctx);

        // Construct view data, store in editor
        gs_editor_view_data_t view = gs_malloc_init(gs_editor_view_data_t);
        view->name = desc->name; 
        view->category = desc->category;
        view->enabled = desc->enabled;
        view->flags = desc->flags;
        view->func = desc->func;
        view->window_handle = desc->window_handle;

        // Want data for this to be accessible for the view itself...
        gs_imgui_ctx_register_window(ctx, view->name, gs_editor_view_func, view);
        gs_imgui_ctx_register_main_menu_option(ctx, view->category, view->name, gs_editor_menu_option_func, view); 

        // Insert data into editor
        gs_hash_table_insert(gs_hash_str64(view_data->name), view_data);
    }

    // Option
    GS_API_DECL void gs_editor_menu_option_func(gs_imgui_ctx_t* ctx, void* data)
    {
        // Grab view data
        gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
        gs_assert(scene);

        // Construct menu option name
        gs_snprintfc(OPTION, 256, "%s##options%zu", view->name, (uint32_t)(size_t)view); 

        // Menu option
        igMenuItem(OPTION, NULL, &view->enabled);
    }

    GS_API_DECL void gs_editor_view_func(gs_imgui_ctx_t* ctx, void* data)
    {
        // Grab view data
        gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
        gs_assert(view);

        if (igBegin(view->name, &view->enabled, view->flags))
        {
            if (view->func)
            {
                view->func(ctx, view);
            }
            igEnd();
        }
    }

    // 
*/

/*
typedef struct gs_editor_view_data_t
{
    const char* category;
    const char* name;
    uint32_t flags;
    bool32 enabled;
    gs_imgui_func func;
    uint32_t window_handle;
} gs_editor_view_data_t;

typedef gs_editor_view_data_t gs_editor_view_desc_t;
*/

// App struct declaration 
typedef struct gs_editor_t
{
    // Core data
    gs_core_t* core; 

    // Your app data here...
    gs_asset_handle_t tex;
    // gs_hash_table(uint64_t, gs_editor_view_data_t*) views; 
    gs_mt_rand_t rand; 
} gs_editor_t; 

// Main application interface functions
GS_API_DECL gs_app_desc_t gs_editor_main(int32_t argc, char** argv);
GS_API_DECL void gs_editor_init();
GS_API_DECL void gs_editor_update();
GS_API_DECL void gs_editor_shutdown(); 

/*
GS_API_DECL void gs_editor_view_create(gs_editor_t* editor, gs_editor_view_desc_t* desc);
GS_API_DECL void gs_editor_scene_view(void* data);
GS_API_DECL void gs_editor_world_outliner_view(void* data);
GS_API_DECL void gs_editor_asset_browser_view(void* data);
*/

// == [ Appplication Implementation ] == // 

#ifdef gs_editor_IMPL 

/*
GS_API_DECL void gs_editor_world_outliner_view(void* data)
{
    gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
    gs_snprintfc(TMP, 256, "Enabled: %s", view->enabled ? "true" : "false");
    igText("World Outliner: %s", TMP);
}

GS_API_DECL void gs_editor_asset_browser_view(void* data)
{
    gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
    gs_snprintfc(TMP, 256, "Enabled: %s", view->enabled ? "true" : "false");
    igText("Asset Browser: %s", TMP);
}

GS_API_DECL void gs_editor_scene_view(void* data)
{
    gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
    gs_snprintfc(TMP, 256, "Enabled: %s", view->enabled ? "true" : "false");
    igText("Scene View: %s", TMP);
}
*/

GS_API_DECL void gs_editor_init()
{
    // Initialize core
    gs_editor_t* app = gs_engine_user_data(gs_editor_t); 
    app->core = gs_core_new(); 

    // Register reflection for gs_editor
    gs_editor_meta_register_generated(&app->core->meta);

    // Import texture into asset manager
    app->tex = gs_assets_import(&app->core->assets, "../../gs_core/assets/textures/logo.png", NULL, false); 

    /*
    // Create scene view
    gs_editor_view_create(app, &(gs_editor_view_desc_t){
        .category = "Views", 
        .name = "Scene", 
        .flags = 0x00,
        .enabled = true,
        .func = gs_editor_scene_view,
        .window_handle = gs_platform_main_window()
    });

    // Create world outliner view
    gs_editor_view_create(app, &(gs_editor_view_desc_t){
        .category = "Views", 
        .name = "World Outliner", 
        .flags = 0x00,
        .enabled = true,
        .func = gs_editor_world_outliner_view,
        .window_handle = gs_platform_main_window()
    });

    // Create asset browser view
    gs_editor_view_create(app, &(gs_editor_view_desc_t){
        .category = "Views", 
        .name = "Asset Browser", 
        .flags = 0x00,
        .enabled = true,
        .func = gs_editor_asset_browser_view,
        .window_handle = gs_platform_main_window()
    });
    */

    app->rand = gs_rand_seed((uint64_t)time(NULL));
} 

/*
GS_API_DECL void gs_editor_view_func(void* data)
{
    // Grab view data
    gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;
    gs_assert(view); 

    if (view->enabled)
    {
        igBegin(view->name, &view->enabled, view->flags);
        {
            if (view->func) view->func(view);
        }
        igEnd();
    }
}

GS_API_DECL void gs_editor_menu_func(void* data)
{
    gs_editor_view_data_t* view = (gs_editor_view_data_t*)data;

    // Need all the categories here
    igMenuItem_BoolPtr(view->name, NULL, &view->enabled, true);
}

GS_API_DECL void gs_editor_view_create(gs_editor_t* editor, gs_editor_view_desc_t* desc)
{
    gs_core_t* core = editor->core;
    gs_imgui_t* gimgui = &core->imgui; 
    gs_imgui_context_t* ctx = gs_imgui_get_context(gimgui, desc->window_handle);
    gs_assert(ctx);

    // Construct view data, store in editor
    gs_editor_view_data_t* view = gs_malloc_init(gs_editor_view_data_t);
    view->name = desc->name; 
    view->category = desc->category;
    view->enabled = desc->enabled;
    view->flags = desc->flags;
    view->func = desc->func;
    view->window_handle = desc->window_handle; 

    // Want data for this to be accessible for the view itself...
    gs_imgui_register_window(ctx, &(gs_imgui_callback_desc_t){
        .name = view->name,
        .cb = gs_editor_view_func,
        .user_data = view
    });

    gs_imgui_register_menu_item(ctx, "Views", &(gs_imgui_callback_desc_t){
        .name = view->name,
        .cb = gs_editor_menu_func,
        .user_data = view
    }); 

    // Insert data into editor
    gs_hash_table_insert(editor->views, gs_hash_str64(view->name), view);
}
*/

static void write_log(char* logbuf, const char* text, bool* updated) {
    /* FIXME: THIS IS UNSAFE! */
    if (logbuf[0]) {
        strcat(logbuf, "\n");
    }
    strcat(logbuf, text);
    *updated = 1;
}

static void log_window(gs_gui_context_t* ctx) {

    static bool logbuf_updated = false;
    static char logbuf[64000] = {0};

    if (gs_gui_begin_window(ctx, "Log Window", gs_gui_rect(350, 40, 300, 200))) 
    { 
        gs_gui_layout_row(ctx, 1, (int[]) { -1 }, -28);
        gs_gui_begin_panel(ctx, "Panel"); 
        gs_gui_container_t* panel  = gs_gui_get_current_container(ctx);
        gs_gui_layout_row(ctx, 1, (int[]) { -1 }, -1);
        gs_gui_text(ctx, logbuf, 0);
        gs_gui_end_panel(ctx);
        if (logbuf_updated) {
            panel->scroll.y = panel->content_size.y;
            logbuf_updated = 0;
        }

        /* input textbox + submit button */
        static char buf[1024];
        int submitted = 0;
        gs_gui_layout_row(ctx, 2, (int[]) { -70, -1 }, 0);
        if (gs_gui_textbox(ctx, buf, sizeof(buf)) & GS_GUI_RES_SUBMIT) {
            gs_gui_set_focus(ctx, ctx->last_id);
            submitted = 1;
        }
        if (gs_gui_button(ctx, "Submit")) { submitted = 1; }
        if (submitted) {
            write_log(logbuf, buf, &logbuf_updated);
            buf[0] = '\0';
        }
        gs_gui_end_window(ctx);
    }
}

GS_API_DECL void gs_editor_update()
{
    // Cache app/core pointers
    gs_editor_t* app = gs_engine_user_data(gs_editor_t);
    gs_core_t* core = app->core;
    gs_command_buffer_t* cb = &core->cb;
    gs_immediate_draw_t* gsi = &core->gsi; 
    gs_entity_manager_t* em = &core->entities; 
    gs_gui_context_t* gsgui = &app->core->gsgui;

    // Get necessary platform metrics
    const gs_vec2 fb = gs_platform_framebuffer_sizev(gs_platform_main_window());
    const gs_vec2 ws = gs_platform_window_sizev(gs_platform_main_window()); 

    // Process input (closing window) 
    if (gs_platform_key_pressed(GS_KEYCODE_ESC)) gs_engine_quit(); 

    gs_gui_begin(gsgui);

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

// Need to speed up the hash table immensely now...

#define DO_IMGUI 0
#define WIN_CNT 1

/*
#if DO_IMGUI

    // New frame for imgui
    gs_imgui_new_frame(gsimgui);

    // Want to make a dockspace...
#ifdef DO_IMGUI_DOCK
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = igGetMainViewport();
        igSetNextWindowPos(viewport->WorkPos, 0, (ImVec2){0.f, 0.f});
        igSetNextWindowSize(viewport->WorkSize, 0);
        igSetNextWindowViewport(viewport->ID);
        igPushStyleVar_Float(ImGuiStyleVar_WindowRounding, 0.0f);
        igPushStyleVar_Float(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});

    ImGuiWindowClass cls = {
        .ClassId = 0,
        .ParentViewportId = -1,
        .DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoSplit,
        .DockingAllowUnclassed = true
    };
        igSetNextWindowClass(&cls);           // set next window class (control docking compatibility + provide hints to platform backend via custom viewport flags and platform parent/child relationship)

    igBegin("DockSpace Demo", NULL, window_flags);
    { 
        if (!opt_padding)
            igPopStyleVar(1);

        if (opt_fullscreen)
            igPopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO* io = igGetIO();
        if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
            igDockSpace(dockspace_id, (ImVec2){0.0f, 0.0f}, dockspace_flags, NULL);
        } 

        if (igBeginMenuBar())
        { 
            // Iterate through all gui menu options in this context, then draw
            for (
                gs_hash_table_iter it = gs_hash_table_iter_new(gsimgui->menus);
                gs_hash_table_iter_valid(gsimgui->menus, it);
                gs_hash_table_iter_advance(gsimgui->menus, it)
            )
            {
                gs_imgui_menu_t* menu = gs_hash_table_iter_getp(gsimgui->menus, it);
                if (igBeginMenu(menu->name, true)) 
                {
                    for (
                        gs_hash_table_iter mit = gs_hash_table_iter_new(menu->items);
                        gs_hash_table_iter_valid(menu->items, mit);
                        gs_hash_table_iter_advance(menu->items, mit)
                    )
                    {
                        gs_imgui_callback_desc_t* cb = gs_hash_table_iter_getp(menu->items, mit);
                        gs_assert(cb); gs_assert(cb->cb); 
                        cb->cb(cb->user_data);
                    }
                    igEndMenu();
                }
            }

            igEndMenuBar();
        }
    } 
    igEnd(); 

    // Iterate through all gui windows in this context, then draw
    for (
        gs_hash_table_iter it = gs_hash_table_iter_new(gsimgui->windows);
        gs_hash_table_iter_valid(gsimgui->windows, it);
        gs_hash_table_iter_advance(gsimgui->windows, it)
    )
    { 
        gs_imgui_callback_desc_t* cb = gs_hash_table_iter_getp(gsimgui->windows, it);
        gs_assert(cb); gs_assert(cb->cb);
        cb->cb(cb->user_data);
    }
#endif

    for (uint32_t i = 0; i < WIN_CNT; ++i)
    { 
        gs_snprintfc(TMP, 256, "Test_%zu", i); 
        igSetNextWindowPos((ImVec2){100.f + i * 10.f}, 0, (ImVec2){0.f, 0.f});
        igSetNextWindowSize((ImVec2){200.f, 300.f}, 0);
        igBegin(TMP, NULL, 0x00);
        igEnd(); 
    }

    // Imgui render
    gs_imgui_render(gsimgui, cb, NULL);

#else
    for (uint32_t i = 0; i < WIN_CNT; ++i)
    {
        gs_snprintfc(TMP, 256, "Test_%zu", i);
        // Gui code
        gs_gui_window_set_next_position(gsgui, gs_v2s(100.f + i * 10.f));
        gs_gui_window_set_next_size(gsgui, gs_v2(200.f, 300.f));
        if (gs_gui_window_begin(gsgui, TMP))
        { 
        }
        gs_gui_window_end(gsgui); 
    } 

    // Render
    gs_gui_render(gsgui, cb, NULL); 
#endif
*/ 
    /* do window */
    /*
    if (gs_gui_begin_window(&gsmui->mu, "Demo Window", gs_gui_rect(40, 40, 300, 450))) 
    {
        gs_gui_Container *win = gs_gui_get_current_container(&gsmui->mu);
        win->rect.w = gs_gui_max(win->rect.w, 240);
        win->rect.h = gs_gui_max(win->rect.h, 300);
        gs_gui_end_window(&gsmui->mu);
    } 
    
    gs_gs_gui_render(gsmui, cb);
    */

	for ( uint32_t i = 0; i < WIN_CNT; ++i )
	{ 
        double rx = gs_rand_gen(&app->rand);
        double ry = gs_rand_gen(&app->rand);
        double rw = gs_rand_gen(&app->rand);
        double rh = gs_rand_gen(&app->rand); 
		gs_gui_rect_t r = gs_gui_rect(rx * 800.f, ry * 400.f, rw * 100.f, rh * 100.f);
		gs_snprintfc(TMP, 256, "Test_%zu", i);

        #define STATIC_WIN_DIMS 1
        #if STATIC_WIN_DIMS
            r.x = 100.f;
            r.y = 100.f;
            r.w = 100.f;
            r.h = 100.f;
        #endif

		if (gs_gui_begin_window(gsgui, TMP, r))
		{ 
            for (uint32_t j = 0; j < 20; ++j)
            {
                gs_snprintfc(BTMP, 256, "Hello_%zu", j);
                if (gs_gui_button(gsgui, BTMP))
                {
                    gs_println("Hello: %zu", j);
                }
            }

            static char BUF[256] = {0};
            if (gs_gui_textbox(gsgui, BUF, 256))
            {
            }
            gs_gui_end_window(gsgui);
		}
	}

    log_window(gsgui);

    gs_gui_end(gsgui, cb);
    gs_gui_render(gsgui, cb);

    gs_timed_action(60, {
        gs_println("frame: %.2f", gs_engine_subsystem(platform)->time.frame);
    }); 

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

