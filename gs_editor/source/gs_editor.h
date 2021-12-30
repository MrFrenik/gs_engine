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

    // Want to load application library
        - Gives access to all meta information for application 
        - Gives access to project's assets
        - Don't want to make any assumptions about structure of user's application
        - Just want an editor to help create assets: 
            - Entity scenes (a collection of serialized entities)
            - Pipelines (full graphics pipelines, to either be bound separately or used with materials)
            - Materials
            - Meshes
            - Textures
            - Render Passes
            - Components
            - Code (hot reloadable code) 
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
	gs_asset_handle_t font;
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

static bool logbuf_updated = false;
static char logbuf[64000] = {0};

typedef struct font_info
{
    uint32_t point;
    const char* path;
} font_info;

GS_API_DECL void gs_editor_init()
{
    // Initialize core
    gs_editor_t* app = gs_engine_user_data(gs_editor_t); 
    app->core = gs_core_new(); 

    // Register reflection for gs_editor
    gs_editor_meta_register_generated(&app->core->meta);

    font_info fonts[] = 
    {
        {.point = 14, .path = "inconsolata.otf"},
        {.point = 13, .path = "hack_regular.ttf"},
        {.point = 16, .path = "crisp.ttf"},
        {.point = 14, .path = "courier_prime_code.ttf"},
        {.point = 13, .path = "pt_mono.ttf"},
        {.point = 13, .path = "droid_sans_mono.ttf"},
        {.point = 16, .path = "liberation_mono_regular.ttf"},
        {.point = 13, .path = "input_mono_regular.ttf"}
    };
    const uint32_t fi = 0;

    // Import texture into asset manager 
    app->tex = gs_assets_import(&app->core->assets, "../../gs_core/assets/textures/logo.png", NULL, false); 
    app->font = gs_assets_import(&app->core->assets, fonts[fi].path, &fonts[fi].point, false);

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

static void dockspace(gs_gui_context_t* ctx) 
{
    int32_t opt = GS_GUI_OPT_NOCLIP | GS_GUI_OPT_NOFRAME | GS_GUI_OPT_FORCESETRECT | GS_GUI_OPT_NOTITLE | GS_GUI_OPT_DOCKSPACE | GS_GUI_OPT_FULLSCREEN | GS_GUI_OPT_NOMOVE | GS_GUI_OPT_NOBRINGTOFRONT | GS_GUI_OPT_NOFOCUS | GS_GUI_OPT_NORESIZE;
    gs_gui_begin_window_ex(ctx, "Dockspace", gs_gui_rect(350, 40, 600, 500), opt);
    {
        // Empty dockspace...
    }
    gs_gui_end_window(ctx);
}

static void test_window(gs_gui_context_t *ctx) 
{
    //Color picker
    static float bg[3] = {90, 95, 100};

    /* do window */
    if (gs_gui_begin_window(ctx, "Demo", gs_gui_rect(40, 40, 300, 450)))
    {
        if (gs_gui_header(ctx, "Window Info")) 
        {
            gs_gui_container_t* win = gs_gui_get_current_container(ctx);
            char buf[64];
            gs_gui_layout_row(ctx, 2, (int[]) { 65, -1 }, 0);
            gs_gui_label(ctx,"Position:");
            gs_snprintf(buf, 64, "%.2f, %.2f", win->rect.x, win->rect.y); gs_gui_label(ctx, buf);
            gs_gui_label(ctx, "Size:");
            gs_snprintf(buf, 64, "%.2f, %.2f", win->rect.w, win->rect.h); gs_gui_label(ctx, buf);
        }

        if (gs_gui_header_ex(ctx, "Test Buttons", 0x00)) 
        {
            gs_gui_layout_row(ctx, 3, (int[]) { 120, 100, 100 }, 0);
            gs_gui_label(ctx, "Test buttons 1:");
            if (gs_gui_button(ctx, "Button 1")) { write_log(logbuf, "Pressed button 1", &logbuf_updated); }
            if (gs_gui_button(ctx, "Button 2")) { write_log(logbuf, "Pressed button 2", &logbuf_updated); }
            gs_gui_label(ctx, "Test buttons 2:");
            if (gs_gui_button(ctx, "Button 3")) { write_log(logbuf, "Pressed button 3", &logbuf_updated); }
            if (gs_gui_button(ctx, "Popup")) 
            { 
                gs_gui_open_popup(ctx, "Test Popup"); 
            }
            gs_vec2 ws = gs_platform_window_sizev(ctx->window_hndl);
            if (gs_gui_begin_popup_ex( ctx, "Test Popup", gs_gui_rect((ws.x - 400) / 2.f, (ws.y - 100) / 2.f, 400, 100), GS_GUI_OPT_NORESIZE | GS_GUI_OPT_FORCESETRECT | GS_GUI_OPT_NOTITLE)) 
            {
                gs_gui_container_t* cnt = gs_gui_get_current_container(ctx);
                gs_gui_layout_row(ctx, 1, (int[]) { -1 }, 20);
                gs_gui_text(ctx, "Close the text box.", 0);
                gs_gui_layout_row(ctx, 2, (int[]) { -200, -1 }, 20);
                if (gs_gui_button(ctx, "Okay") || gs_gui_button(ctx, "Cancel"))
                {
                    cnt->open = 0;
                } 
                gs_gui_end_popup(ctx);
            }
        }

        if (gs_gui_header_ex(ctx, "Tree and Text", 0x00)) 
        {
            gs_gui_layout_row(ctx, 2, (int[]) { 250, -1 }, 0);
            gs_gui_layout_begin_column(ctx);
            if (gs_gui_begin_treenode(ctx, "Test 1")) {
                if (gs_gui_begin_treenode(ctx, "Test 1a")) {
                    gs_gui_label(ctx, "Hello");
                    gs_gui_label(ctx, "world");
                    gs_gui_end_treenode(ctx);
                }
                if (gs_gui_begin_treenode(ctx, "Test 1b")) {
                    if (gs_gui_button(ctx, "Button 1")) { write_log(logbuf, "Pressed button 1", &logbuf_updated); }
                    if (gs_gui_button(ctx, "Button 2")) { write_log(logbuf, "Pressed button 2", &logbuf_updated); }
                    gs_gui_end_treenode(ctx);
                }
                gs_gui_end_treenode(ctx);
            }

            if (gs_gui_begin_treenode(ctx, "Test 2")) 
            {
                gs_gui_layout_row(ctx, 3, (int[]) { 65, 65, 65 }, 0);
                if (gs_gui_button(ctx, "Button 3")) { write_log(logbuf, "Pressed button 3", &logbuf_updated); }
                if (gs_gui_button(ctx, "Button 4")) { write_log(logbuf, "Pressed button 4", &logbuf_updated); }
                if (gs_gui_button(ctx, "Button 5")) { write_log(logbuf, "Pressed button 5", &logbuf_updated); }
                if (gs_gui_button(ctx, "Button 6")) { write_log(logbuf, "Pressed button 6", &logbuf_updated); }
                gs_gui_end_treenode(ctx);
            }

            if (gs_gui_begin_treenode(ctx, "Test 3")) 
            {
                static int checks[3] = { 1, 0, 1 };
                gs_gui_checkbox(ctx, "Checkbox 1", &checks[0]);
                gs_gui_checkbox(ctx, "Checkbox 2", &checks[1]);
                gs_gui_checkbox(ctx, "Checkbox 3", &checks[2]);
                gs_gui_end_treenode(ctx);
            }
            gs_gui_layout_end_column(ctx);

            gs_gui_layout_begin_column(ctx);
            gs_gui_layout_row(ctx, 1, (int[]) { -1 }, 0);
            gs_gui_text(ctx, "Lorem ipsum dolor sit amet, consectetur adipiscing "
                         "elit. Maecenas lacinia, sem eu lacinia molestie, mi risus faucibus "
                         "ipsum, eu varius magna felis a nulla.", 1);
            gs_gui_layout_end_column(ctx);
        }

        if (gs_gui_header_ex(ctx, "Background Color", 0x00)) 
        {
            gs_gui_layout_row(ctx, 2, (int[]) { -78, -1 }, 74);
            gs_gui_layout_begin_column(ctx);
            gs_gui_layout_row(ctx, 2, (int[]) { 46, -1 }, 0);
            gs_gui_label(ctx, "Red:");   gs_gui_slider(ctx, &bg[0], 0, 255);
            gs_gui_label(ctx, "Green:"); gs_gui_slider(ctx, &bg[1], 0, 255);
            gs_gui_label(ctx, "Blue:");  gs_gui_slider(ctx, &bg[2], 0, 255);
            gs_gui_layout_end_column(ctx);
            gs_gui_rect_t r = gs_gui_layout_next(ctx);
            gs_gui_draw_rect(ctx, r, gs_color(bg[0], bg[1], bg[2], 255));
            char buf[32];
            gs_snprintf(buf, 32, "#%02X%02X%02X", (int) bg[0], (int) bg[1], (int) bg[2]);
            gs_gui_draw_control_text(ctx, buf, r, GS_GUI_COLOR_TEXT, GS_GUI_OPT_ALIGNCENTER);
        }

        if (gs_gui_header_ex(ctx, "Shapes", 0x00)) 
        { 
            gs_gui_container_t* cnt = gs_gui_get_current_container(ctx);
            gs_gui_layout_row(ctx, 1, (int[]) { -1 }, 50);
            gs_gui_begin_panel_ex(ctx, "!panel", GS_GUI_OPT_NOSCROLL); 
            gs_gui_layout_row(ctx, 3, (int[]) { 20, 10, -1 }, 0);
            gs_gui_rect_t next = gs_gui_layout_next(ctx); 
            gs_gui_draw_circle(ctx, gs_v2(next.x + 10.f, next.y + 10.f), 10.f, GS_COLOR_RED);
            next = gs_gui_layout_next(ctx); 
            gs_gui_draw_triangle(ctx, gs_v2(next.x, next.y), gs_v2(next.x + 10.f, next.y + 10.f), gs_v2(next.x, next.y + 10.f), GS_COLOR_WHITE);
            next = gs_gui_layout_next(ctx); 
            gs_gui_draw_rect(ctx, gs_gui_rect(next.x, next.y, 10.f, 10.f), GS_COLOR_BLUE);
            gs_gui_end_panel(ctx);
        }

        gs_gui_end_window(ctx);
    }
}

static void log_window(gs_gui_context_t* ctx) 
{
    if (gs_gui_begin_window_ex(ctx, "Log Window", gs_gui_rect(350, 40, 300, 200), GS_GUI_OPT_NOSCROLL)) 
    { 
        gs_gui_container_t* cnt = gs_gui_get_current_container(ctx);
        gs_gui_layout_row(ctx, 1, (int[]) { -1 }, gs_max(cnt->rect.h - 80, 80));
        gs_gui_begin_panel_ex(ctx, "Panel", GS_GUI_OPT_NOSCROLL); 
        gs_gui_container_t* panel  = gs_gui_get_current_container(ctx);
        gs_gui_layout_row(ctx, 1, (int[]) { -1 }, -1);
        gs_gui_text(ctx, logbuf, 0);
        gs_gui_end_panel(ctx);
        if (logbuf_updated) {
            // panel->scroll.y = panel->content_size.y;
            logbuf_updated = 0;
        }

        // input textbox + submit button
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

static int uint8_slider(gs_gui_context_t *ctx, unsigned char *value, int low, int high) {
  static float tmp;
  gs_gui_push_id(ctx, &value, sizeof(value));
  tmp = *value;
  int res = gs_gui_slider_ex(ctx, &tmp, low, high, 0, "%.0f", GS_GUI_OPT_ALIGNCENTER);
  *value = tmp;
  gs_gui_pop_id(ctx);
  return res;
}


static void style_window(gs_gui_context_t *ctx) 
{
  static struct { const char *label; int idx; } colors[] = {
    { "text:",         GS_GUI_COLOR_TEXT        },
    { "border:",       GS_GUI_COLOR_BORDER      },
    { "windowbg:",     GS_GUI_COLOR_WINDOWBG    },
    { "titlebg:",      GS_GUI_COLOR_TITLEBG     },
    { "titletext:",    GS_GUI_COLOR_TITLETEXT   },
    { "panelbg:",      GS_GUI_COLOR_PANELBG     },
    { "button:",       GS_GUI_COLOR_BUTTON      },
    { "buttonhover:",  GS_GUI_COLOR_BUTTONHOVER },
    { "buttonfocus:",  GS_GUI_COLOR_BUTTONFOCUS },
    { "base:",         GS_GUI_COLOR_BASE        },
    { "basehover:",    GS_GUI_COLOR_BASEHOVER   },
    { "basefocus:",    GS_GUI_COLOR_BASEFOCUS   },
    { "scrollbase:",   GS_GUI_COLOR_SCROLLBASE  },
    { "scrollthumb:",  GS_GUI_COLOR_SCROLLTHUMB },
    { NULL }
  };

  if (gs_gui_begin_window(ctx, "Style Editor", gs_gui_rect(350, 250, 300, 240))) 
  {
    int sw = gs_gui_get_current_container(ctx)->body.w * 0.14;
    gs_gui_layout_row(ctx, 6, (int[]) { 80, sw, sw, sw, sw, -1 }, 0);
    for (int i = 0; colors[i].label; i++) 
    {
      gs_gui_label(ctx, colors[i].label);
      uint8_slider(ctx, &ctx->style->colors[i].r, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].g, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].b, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].a, 0, 255);
      gs_gui_draw_rect(ctx, gs_gui_layout_next(ctx), ctx->style->colors[i]);
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

    // Get texture
    gs_texture_t* tex = gs_asset_handle_get(&app->tex); 
	// Get font
	gs_font_t* font = gs_asset_handle_get(&app->font);

	static bool blah = false;
	if (gs_platform_key_pressed(GS_KEYCODE_0)) blah = !blah;
	if (blah) gsgui->style->font = &font->font;
	else gsgui->style->font = gsi_default_font();

    // Get necessary platform metrics
    const gs_vec2 fb = gs_platform_framebuffer_sizev(gs_platform_main_window());
    const gs_vec2 ws = gs_platform_window_sizev(gs_platform_main_window()); 

    // Process input (closing window) 
    if (gs_platform_key_pressed(GS_KEYCODE_ESC)) gs_engine_quit(); 

    gs_gui_begin(gsgui);

    // Update entity manager
    gs_entities_update(em); 

    // Get dimensions for text
    gs_vec2 td = gs_asset_font_text_dimensions(gsi_default_font(), "Project: gs_editor", -1);
    // Dimensions for texture
    gs_vec2 ts = gs_v2(500.f, 500.f * 0.18f);

    // Render hello to screen
    gsi_camera2D(gsi);
    gsi_text(gsi, (fb.x - td.x) * 0.5f, (fb.y - td.y) * 0.5f, "Project: gs_editor", NULL, false, 255, 255, 255, 255); 
    gsi_texture(gsi, tex->texture.hndl);
    gsi_rectvd(gsi, gs_v2((fb.x - ts.x) * 0.5f, (fb.y - ts.y) * 0.5f - td.y - 50.f), ts, gs_v2s(0.f), gs_v2s(1.f), GS_COLOR_WHITE, GS_GRAPHICS_PRIMITIVE_TRIANGLES);

    // Submit immediate draw render pass
    gsi_render_pass_submit(gsi, cb, gs_color(10, 10, 10, 255)); 

#define WIN_CNT  1

    // Draw dockspace
    dockspace(gsgui);

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
            r.w = 400.f;
            r.h = 300.f;
        #endif

		if (gs_gui_begin_window(gsgui, TMP, r))
		{ 
            static char BUF[256] = {0};
            if (gs_gui_textbox(gsgui, BUF, 256))
            {
            }

            for (uint32_t j = 0; j < 20; ++j)
            {
                gs_snprintfc(BTMP, 256, "Hello_%zu", j);
                if (gs_gui_button(gsgui, BTMP))
                {
                    gs_println("Hello: %zu", j);
                }
            }

            gs_gui_end_window(gsgui);
		}
	} 

    log_window(gsgui);
    test_window(gsgui);
    style_window(gsgui);

    gs_gui_end(gsgui);

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
        .window_width = 1200,
        .window_height = 700,
        .init = gs_editor_init,
        .update = gs_editor_update,
        .shutdown = gs_editor_shutdown,
        .user_data = gs_malloc_init(gs_editor_t)
    };
} 

#endif  // gs_editor_IMPL 
#endif  // gs_editor_H 

