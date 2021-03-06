#ifndef __GS_IMGUI_IMPL_H__
#define __GS_IMGUI_IMPL_H__

#define IM_ASSERT gs_assert

// Need some sort of docking here...

typedef void (* gs_imgui_func)(void* user_data);

typedef struct gs_imgui_callback_desc_t
{
    gs_imgui_func cb;
    void* user_data;
    const char* name;
    const char* category;
} gs_imgui_callback_desc_t; 

typedef struct gs_imgui_menu_t
{
    const char* name;
    gs_hash_table(uint64_t, gs_imgui_callback_desc_t) items;
} gs_imgui_menu_t;

typedef struct gs_imgui_context_t
{
    double time;
    uint32_t win_hndl;
    bool32 mouse_just_pressed[ImGuiMouseButton_COUNT]; 
    bool32 mouse_cursors[ImGuiMouseCursor_COUNT];
    gs_handle(gs_graphics_pipeline_t) pip;
    gs_handle(gs_graphics_vertex_buffer_t) vbo;
    gs_handle(gs_graphics_index_buffer_t) ibo;
    gs_handle(gs_graphics_shader_t) shader;
    gs_handle(gs_graphics_texture_t) font_tex; 
    gs_handle(gs_graphics_uniform_t) u_tex; 
    gs_handle(gs_graphics_uniform_t) u_proj;
    ImGuiContext* ctx;
    gs_hash_table(uint64_t, gs_imgui_callback_desc_t) windows;  
    gs_hash_table(uint64_t, gs_imgui_menu_t) menus;  
} gs_imgui_context_t;

// Main context for necessary imgui information
typedef struct gs_imgui_t
{
    gs_hash_table(uint32_t, ImGuiContext*) contexts;
} gs_imgui_t;

typedef struct gs_imgui_vertex_t 
{
    float position[2];
    float uv[2];
    uint8_t col[4];
} gs_imgui_vertex_t;

#ifdef GS_PLATFORM_WEB
    #define GS_IMGUI_SHADER_VERSION "#version 300 es\n" 
#else
    #define GS_IMGUI_SHADER_VERSION "#version 330 core\n"
#endif

GS_API_DECL void                gs_imgui_context_new(gs_imgui_t* gs, uint32_t hndl, bool install_callbacks);
GS_API_DECL void                gs_imgui_device_create(gs_imgui_context_t* ctx);
GS_API_DECL bool                gs_imgui_create_fonts_texture(gs_imgui_context_t* ctx);
GS_API_DECL void                gs_imgui_render(gs_imgui_context_t* ctx, gs_command_buffer_t* cb, const gs_color_t* clear_color);
GS_API_DECL void                gs_imgui_new_frame(gs_imgui_context_t* ctx);
GS_API_DECL gs_imgui_context_t* gs_imgui_get_context(gs_imgui_t* gs, uint32_t window_hndl); 
GS_API_DECL void                gs_imgui_register_window(gs_imgui_context_t* ctx, gs_imgui_callback_desc_t* cb);
GS_API_DECL void                gs_imgui_register_menu_item(gs_imgui_context_t* ctx, const char* name, gs_imgui_callback_desc_t* cb);

/*===============================
//      Implementation
================================*/

#ifdef GS_IMGUI_IMPL

GS_API_DECL void gs_imgui_device_create(gs_imgui_context_t* ctx)
{
    static const char* imgui_vertsrc =
        GS_IMGUI_SHADER_VERSION
        "uniform mat4 ProjMtx;\n"
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 TexCoord;\n"
        "layout (location = 2) in vec4 Color;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main() {\n"
        "   Frag_UV = TexCoord;\n"
        "   Frag_Color = Color;\n"
        "   gl_Position = ProjMtx * vec4(Position.xy, 0, 1);\n"
        "}\n";

    static const char* imgui_fragsrc =
        GS_IMGUI_SHADER_VERSION
        "precision mediump float;\n"
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "out vec4 Out_Color;\n"
        "void main(){\n"
        "   Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

    // Shader source description
    gs_graphics_shader_source_desc_t sources[2] = gs_default_val();
    sources[0].type = GS_GRAPHICS_SHADER_STAGE_VERTEX; sources[0].source = imgui_vertsrc;
    sources[1].type = GS_GRAPHICS_SHADER_STAGE_FRAGMENT; sources[1].source = imgui_fragsrc;

    // Shader desc
    gs_graphics_shader_desc_t sdesc = gs_default_val();
    sdesc.sources = sources;
    sdesc.size = sizeof(sources);
    strncpy(sdesc.name, "imgui", 5);

    // Create shader
    ctx->shader = gs_graphics_shader_create (&sdesc);

    // Uniform texture
    gs_graphics_uniform_layout_desc_t slayout = gs_default_val();
    slayout.type = GS_GRAPHICS_UNIFORM_SAMPLER2D;
    gs_graphics_uniform_desc_t utexdesc = gs_default_val();
    strncpy(utexdesc.name, "Texture", 7);
    utexdesc.layout = &slayout;
    ctx->u_tex = gs_graphics_uniform_create(&utexdesc);

    // Construct uniform
    gs_graphics_uniform_layout_desc_t ulayout = gs_default_val();
    ulayout.type = GS_GRAPHICS_UNIFORM_MAT4;
    gs_graphics_uniform_desc_t udesc = gs_default_val();
    strncpy(udesc.name, "ProjMtx", 7);
    udesc.layout = &ulayout;

    // Construct project matrix uniform
    ctx->u_proj = gs_graphics_uniform_create(&udesc);

    // Vertex buffer description
    gs_graphics_vertex_buffer_desc_t vbufdesc = gs_default_val();
    vbufdesc.usage = GS_GRAPHICS_BUFFER_USAGE_STREAM;
    vbufdesc.data = NULL;

    // Construct vertex buffer
    ctx->vbo = gs_graphics_vertex_buffer_create(&vbufdesc);

    // Index buffer desc
    gs_graphics_index_buffer_desc_t ibufdesc = gs_default_val();
    ibufdesc.usage = GS_GRAPHICS_BUFFER_USAGE_STREAM;
    ibufdesc.data = NULL;

    // Create index buffer
    ctx->ibo = gs_graphics_index_buffer_create(&ibufdesc);

    // Vertex attr layout
    gs_graphics_vertex_attribute_desc_t vattrs[3] = gs_default_val();
    vattrs[0].format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2;   // Position
    vattrs[1].format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2;   // UV
    vattrs[2].format = GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE4;    // Color

    // Pipeline desc
    gs_graphics_pipeline_desc_t pdesc = gs_default_val();
    pdesc.raster.shader = ctx->shader;
    pdesc.raster.index_buffer_element_size = (sizeof(ImDrawIdx) == 2) ? sizeof(uint16_t) : sizeof(uint32_t);
    pdesc.blend.func = GS_GRAPHICS_BLEND_EQUATION_ADD;
    pdesc.blend.src = GS_GRAPHICS_BLEND_MODE_SRC_ALPHA;
    pdesc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_SRC_ALPHA;
    pdesc.layout.attrs = vattrs;
    pdesc.layout.size = sizeof(vattrs);

    // Create pipeline
    ctx->pip = gs_graphics_pipeline_create(&pdesc);

    // Create default fonts texture
    gs_imgui_create_fonts_texture(ctx);
}

GS_API_DECL void gs_imgui_context_new(gs_imgui_t* gs, uint32_t hndl, bool install_callbacks)
{
    gs_imgui_context_t* ctx = gs_malloc_init(gs_imgui_context_t);
    ctx->ctx = igCreateContext(NULL);
    igSetCurrentContext(ctx->ctx);

    gs_hash_table_insert(gs->contexts, hndl, ctx); 
    ctx->time = 0.0;
    ctx->win_hndl = hndl;

    // Setup backend capabilities flags
    ImGuiIO* io = igGetIO(); 

    // Config flags
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Backend Flags
    io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
    io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
    io->BackendPlatformName = "imgui_impl_gs";

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io->KeyMap[ImGuiKey_Tab]         = gs_platform_key_to_codepoint(GS_KEYCODE_TAB);
    io->KeyMap[ImGuiKey_LeftArrow]   = gs_platform_key_to_codepoint(GS_KEYCODE_LEFT);
    io->KeyMap[ImGuiKey_RightArrow]  = gs_platform_key_to_codepoint(GS_KEYCODE_RIGHT);
    io->KeyMap[ImGuiKey_UpArrow]     = gs_platform_key_to_codepoint(GS_KEYCODE_UP);
    io->KeyMap[ImGuiKey_DownArrow]   = gs_platform_key_to_codepoint(GS_KEYCODE_DOWN);
    io->KeyMap[ImGuiKey_PageUp]      = gs_platform_key_to_codepoint(GS_KEYCODE_PAGE_UP);
    io->KeyMap[ImGuiKey_PageDown]    = gs_platform_key_to_codepoint(GS_KEYCODE_PAGE_DOWN);
    io->KeyMap[ImGuiKey_Home]        = gs_platform_key_to_codepoint(GS_KEYCODE_HOME);
    io->KeyMap[ImGuiKey_End]         = gs_platform_key_to_codepoint(GS_KEYCODE_END);
    io->KeyMap[ImGuiKey_Insert]      = gs_platform_key_to_codepoint(GS_KEYCODE_INSERT);
    io->KeyMap[ImGuiKey_Delete]      = gs_platform_key_to_codepoint(GS_KEYCODE_DELETE);
    io->KeyMap[ImGuiKey_Backspace]   = gs_platform_key_to_codepoint(GS_KEYCODE_BACKSPACE);
    io->KeyMap[ImGuiKey_Space]       = gs_platform_key_to_codepoint(GS_KEYCODE_SPACE);
    io->KeyMap[ImGuiKey_Enter]       = gs_platform_key_to_codepoint(GS_KEYCODE_ENTER);
    io->KeyMap[ImGuiKey_Escape]      = gs_platform_key_to_codepoint(GS_KEYCODE_ESC);
    io->KeyMap[ImGuiKey_KeyPadEnter] = gs_platform_key_to_codepoint(GS_KEYCODE_KP_ENTER);
    io->KeyMap[ImGuiKey_A]           = gs_platform_key_to_codepoint(GS_KEYCODE_A);
    io->KeyMap[ImGuiKey_C]           = gs_platform_key_to_codepoint(GS_KEYCODE_C);
    io->KeyMap[ImGuiKey_V]           = gs_platform_key_to_codepoint(GS_KEYCODE_V);
    io->KeyMap[ImGuiKey_X]           = gs_platform_key_to_codepoint(GS_KEYCODE_X);
    io->KeyMap[ImGuiKey_Y]           = gs_platform_key_to_codepoint(GS_KEYCODE_Y);
    io->KeyMap[ImGuiKey_Z]           = gs_platform_key_to_codepoint(GS_KEYCODE_Z);

    // Rendering
    io->BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    gs_imgui_device_create(ctx);

//     io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
//     io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
//     io.ClipboardUserData = g_Window;
// #if defined(_WIN32)
//     io.ImeWindowHandle = (void*)glfwGetWin32Window(g_Window);
// #endif

    // Create mouse cursors
    // (By design, on X11 cursors are user configurable and some cursors may be missing. When a cursor doesn't exist,
    // GLFW will emit an error which will often be printed by the app, so we temporarily disable error reporting.
    // Missing cursors will return NULL and our _UpdateMouseCursor() function will use the Arrow cursor instead.)
//     GLFWerrorfun prev_error_callback = glfwSetErrorCallback(NULL);
//     g_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
// #if GLFW_HAS_NEW_CURSORS
//     g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
// #else
//     g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
//     g_MouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
// #endif
//     glfwSetErrorCallback(prev_error_callback);

    // Chain GLFW callbacks: our callbacks will call the user's previously installed callbacks, if any.
    // g_PrevUserCallbackMousebutton = NULL;
    // g_PrevUserCallbackScroll = NULL;
    // g_PrevUserCallbackKey = NULL;
    // g_PrevUserCallbackChar = NULL;
    // if (install_callbacks)
    // {
    //     g_InstalledCallbacks = true;
    //     g_PrevUserCallbackMousebutton = glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
    //     g_PrevUserCallbackScroll = glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
    //     g_PrevUserCallbackKey = glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
    //     g_PrevUserCallbackChar = glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
    // }

    // g_ClientApi = client_api;

    return gs;

}

GS_API_DECL gs_imgui_context_t* gs_imgui_get_context(gs_imgui_t* gs, uint32_t window_hndl)
{
    return gs_hash_table_get(gs->contexts, window_hndl);
}

GS_API_DECL bool     
gs_imgui_create_fonts_texture(gs_imgui_context_t* ctx)
{
    // Build texture atlas
    ImGuiIO* io = igGetIO();
    unsigned char* pixels;
    int32_t width, height, bytes_per_pixel;

    ImFontAtlas_GetTexDataAsRGBA32(io->Fonts, &pixels, &width, &height, &bytes_per_pixel);
    // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

    // Create font texture
    gs_graphics_texture_desc_t tdesc = gs_default_val();
    tdesc.width = width;
    tdesc.height = height;
    tdesc.format = GS_GRAPHICS_TEXTURE_FORMAT_RGBA8;
    tdesc.min_filter = GS_GRAPHICS_TEXTURE_FILTER_LINEAR; 
    tdesc.mag_filter = GS_GRAPHICS_TEXTURE_FILTER_LINEAR; 
    tdesc.data = (void*)pixels;

    ctx->font_tex = gs_graphics_texture_create(&tdesc);

    // Store our identifier
    io->Fonts->TexID = (ImTextureID)(intptr_t)ctx->font_tex.id; 

    return true;
}

void gs_imgui_update_mouse_and_keys(gs_imgui_context_t* ctx)
{
    ImGuiIO* io = igGetIO();

    // Need to add an input character...check to see if it's an alpha/numeric string

    // Have to poll events from platform layer to do this
    gs_platform_event_t evt = gs_default_val();
    while(gs_platform_poll_events(&evt, false))
    {
        switch (evt.type)
        {
            case GS_PLATFORM_EVENT_KEY:
            {
                switch (evt.key.action)
                {
                    case GS_PLATFORM_KEY_PRESSED:
                    {
                        // Not sure if this is correct at all.
                        uint32_t cp = evt.key.codepoint;
                        if (cp <= IM_UNICODE_CODEPOINT_MAX) {
                            ImGuiIO_AddInputCharacter(io, cp); 
                        }

                        // io.KeysDown[io.KeyMap[evt.key.codepoint]] = true;

                    } break;

                    case GS_PLATFORM_KEY_RELEASED:
                    {
                        io->KeysDown[evt.key.codepoint] = false;
                    } break;

                    default: break;
                }
            } break;

            default: break;
        }
    }

    if (gs_platform_key_pressed(GS_KEYCODE_TAB)) gs_println("tab");
    if (gs_platform_key_pressed(GS_KEYCODE_ENTER)) gs_println("enter");
    if (gs_platform_key_pressed(GS_KEYCODE_BACKSPACE)) gs_println("bspace");
    if (gs_platform_key_pressed(GS_KEYCODE_LEFT)) gs_println("left");
    if (gs_platform_key_pressed(GS_KEYCODE_RIGHT)) gs_println("right");
    if (gs_platform_key_pressed(GS_KEYCODE_UP)) gs_println("up");
    if (gs_platform_key_pressed(GS_KEYCODE_DOWN)) gs_println("down");

    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_BACKSPACE)] = gs_platform_key_pressed(GS_KEYCODE_BACKSPACE);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_TAB)]       = gs_platform_key_pressed(GS_KEYCODE_TAB);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_ENTER)]     = gs_platform_key_pressed(GS_KEYCODE_ENTER);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_LEFT)]      = gs_platform_key_pressed(GS_KEYCODE_LEFT);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_RIGHT)]     = gs_platform_key_pressed(GS_KEYCODE_RIGHT);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_UP)]        = gs_platform_key_pressed(GS_KEYCODE_UP);
    io->KeysDown[gs_platform_key_to_codepoint(GS_KEYCODE_DOWN)]      = gs_platform_key_pressed(GS_KEYCODE_DOWN);

    // Modifiers
    io->KeyCtrl   = gs_platform_key_down(GS_KEYCODE_LEFT_CONTROL) || gs_platform_key_down(GS_KEYCODE_RIGHT_CONTROL);
    io->KeyShift  = gs_platform_key_down(GS_KEYCODE_LEFT_SHIFT) || gs_platform_key_down(GS_KEYCODE_RIGHT_SHIFT);
    io->KeyAlt    = gs_platform_key_down(GS_KEYCODE_LEFT_ALT) || gs_platform_key_down(GS_KEYCODE_RIGHT_ALT);
    io->KeySuper  = false;

    // Update buttons
    io->MouseDown[0] = gs_platform_mouse_down(GS_MOUSE_LBUTTON);
    io->MouseDown[1] = gs_platform_mouse_down(GS_MOUSE_RBUTTON);
    io->MouseDown[2] = gs_platform_mouse_down(GS_MOUSE_MBUTTON);

    // Mouse position
    int32_t mpx = 0, mpy = 0;
    gs_platform_mouse_position(&mpx, &mpy);
    io->MousePos = (ImVec2){(float)mpx, (float)mpy};

    // Mouse wheel
    gs_platform_mouse_wheel(&io->MouseWheelH, &io->MouseWheel);
}

GS_API_DECL void gs_imgui_new_frame(gs_imgui_context_t* ctx)
{
    igSetCurrentContext(ctx->ctx);
    gs_assert(igGetCurrentContext() != NULL);

    ImGuiIO* io = igGetIO();
    IM_ASSERT(ImFontAtlas_IsBuilt(io->Fonts) && "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

    // Setup display size (every frame to accommodate for window resizing)
    uint32_t w, h;
    uint32_t display_w, display_h;

    // Get platform window size and framebuffer size from window handle
    gs_platform_window_size(ctx->win_hndl, &w, &h);
    gs_platform_framebuffer_size(ctx->win_hndl, &display_w, &display_h);

    io->DisplaySize = (ImVec2){(float)w, (float)h};
    if (w > 0 && h > 0)
        io->DisplayFramebufferScale = (ImVec2){(float)display_w / w, (float)display_h / h};

    // Setup time step
    io->DeltaTime = gs_engine_subsystem(platform)->time.delta;
    ctx->time = (double)gs_platform_elapsed_time();

    gs_imgui_update_mouse_and_keys(ctx);

    igNewFrame();
}

GS_API_DECL void gs_imgui_render(gs_imgui_context_t* ctx, gs_command_buffer_t* cb, const gs_color_t* clear_color)
{ 
    // Set current context
    igSetCurrentContext(ctx->ctx);

    // Do da drawing   
    igRender();

    // Cache draw data
    ImDrawData* draw_data = igGetDrawData();

    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    // Setup viewport, orthographic projection matrix
    float l = draw_data->DisplayPos.x;
    float r = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float t = draw_data->DisplayPos.y;
    float b = draw_data->DisplayPos.y + draw_data->DisplaySize.y; 

    const float ortho[4][4] =
    {
        { 2.0f/(r-l),   0.0f,         0.0f,   0.0f },
        { 0.0f,         2.0f/(t-b),   0.0f,   0.0f },
        { 0.0f,         0.0f,        -1.0f,   0.0f },
        { (r+l)/(l-r),  (t+b)/(b-t),  0.0f,   1.0f },
    };

    // gs_mat4 m = gs_mat4_identity();
    gs_mat4 m = gs_mat4_elem((float*)ortho);

    // Set up data binds
    gs_graphics_bind_vertex_buffer_desc_t vbuffers = gs_default_val();
    vbuffers.buffer = ctx->vbo;

    gs_graphics_bind_index_buffer_desc_t ibuffers = gs_default_val();
    ibuffers.buffer = ctx->ibo;

    gs_graphics_bind_uniform_desc_t ubuffers = gs_default_val();
    ubuffers.uniform = ctx->u_proj;
    ubuffers.data = &m;

    // Set up data binds
    gs_graphics_bind_desc_t binds = gs_default_val();
    binds.vertex_buffers.desc = &vbuffers;
    binds.vertex_buffers.size = sizeof(vbuffers);
    binds.index_buffers.desc = &ibuffers;
    binds.index_buffers.size = sizeof(ibuffers);
    binds.uniforms.desc = &ubuffers;
    binds.uniforms.size = sizeof(ubuffers);

    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

    // Render pass action for clearing the screen
    gs_graphics_clear_desc_t clear = gs_default_val();
    gs_graphics_clear_action_t action = gs_default_val(); 
    if (clear_color)
    {
        action.color[0] = clear_color->r; 
        action.color[1] = clear_color->g; 
        action.color[2] = clear_color->b; 
        action.color[3] = clear_color->a;
        clear.actions = &action;
    }

    // Default action pass
    gs_handle(gs_graphics_render_pass_t) def_pass = gs_default_val();
    def_pass.id = 0;

    // Render pass action for clearing screen (could handle this if you wanted to render gui into a separate frame buffer)
    gs_graphics_begin_render_pass(cb, def_pass);
    {
        // Bind pipeline
        gs_graphics_bind_pipeline(cb, ctx->pip);

        // Set viewport
        gs_graphics_set_viewport(cb, 0, 0, fb_width, fb_height);

        // Clear screen
        gs_graphics_clear(cb, &clear);

        // Global bindings for pipeline
        gs_graphics_apply_bindings(cb, &binds);

         // Render command lists
        for (int n = 0; n < draw_data->CmdListsCount; n++)
        {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];

            // Update vertex buffer
            gs_graphics_vertex_buffer_desc_t vdesc = gs_default_val();
            vdesc.usage = GS_GRAPHICS_BUFFER_USAGE_STREAM;
            vdesc.data = cmd_list->VtxBuffer.Data;
            vdesc.size = cmd_list->VtxBuffer.Size * sizeof(ImDrawVert);
            gs_graphics_vertex_buffer_request_update(cb, ctx->vbo, &vdesc);

            // Update index buffer
            gs_graphics_index_buffer_desc_t idesc = gs_default_val();
            idesc.usage = GS_GRAPHICS_BUFFER_USAGE_STREAM;
            idesc.data = cmd_list->IdxBuffer.Data;
            idesc.size = cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx);
            gs_graphics_index_buffer_request_update(cb, ctx->ibo, &idesc);

            // Iterate through command buffer
            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
            {
                const ImDrawCmd* pcmd = &cmd_list->CmdBuffer.Data[cmd_i];
                if (pcmd->UserCallback != NULL)
                {
                    // User callback, registered via ImDrawList::AddCallback()
                    // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                    // if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    if (false)
                    {
                        // Could add something here...not sure what though
                        // ImGui_ImplOpenGL3_SetupRenderState(draw_data, fb_width, fb_height, vertex_array_object);
                    }
                    else
                        pcmd->UserCallback(cmd_list, pcmd);
                }
                else
                {
                    // Project scissor/clipping rectangles into framebuffer space
                    ImVec4 clip_rect;
                    clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                    clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                    clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                    clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

                    // Render
                    if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                    {
                        // Set view scissor
                        gs_graphics_set_view_scissor(cb, 
                            (int)clip_rect.x, 
                            (int)(fb_height - clip_rect.w), 
                            (int)(clip_rect.z - clip_rect.x), 
                            (int)(clip_rect.w - clip_rect.y)
                        );

                        // Grab handle from command texture id
                        gs_handle(gs_graphics_texture_t) tex = gs_handle_create(gs_graphics_texture_t, (uint32_t)(intptr_t)pcmd->TextureId);

                        gs_graphics_bind_uniform_desc_t sbuffer = gs_default_val();
                        sbuffer.uniform = ctx->u_tex;
                        sbuffer.data = &tex;
                        sbuffer.binding = 0;

                        gs_graphics_bind_desc_t sbind = gs_default_val();
                        sbind.uniforms.desc = &sbuffer;
                        sbind.uniforms.size = sizeof(sbuffer);

                        // Bind individual texture bind
                        gs_graphics_apply_bindings(cb, &sbind);

                        // Draw elements
                        gs_graphics_draw_desc_t draw = gs_default_val();
                        draw.start = (size_t)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx));
                        draw.count = (size_t)pcmd->ElemCount;
                        gs_graphics_draw(cb, &draw); 
                    }
                }
            }
        }
    }
    gs_graphics_end_render_pass(cb);
}

GS_API_DECL void gs_imgui_register_window(gs_imgui_context_t* ctx, gs_imgui_callback_desc_t* cb)
{
    gs_assert(ctx); gs_assert(cb); gs_assert(cb->name);
    gs_hash_table_insert(ctx->windows, cb->name, *cb);
}

GS_API_DECL void gs_imgui_register_menu_item(gs_imgui_context_t* ctx, const char* menu_name, gs_imgui_callback_desc_t* cb)
{ 
    gs_assert(ctx); gs_assert(cb);
    if (!ctx->menus || !gs_hash_table_key_exists(ctx->menus, gs_hash_str64(menu_name)))
    {
        gs_hash_table_insert(ctx->menus, gs_hash_str64(menu_name), (gs_imgui_menu_t){.name = menu_name}); 
    }

    gs_imgui_menu_t* menu = gs_hash_table_getp(ctx->menus, gs_hash_str64(menu_name));
    gs_assert(menu); 
    gs_hash_table_insert(menu->items, gs_hash_str64(cb->name), *cb);
}

#endif // GS_IMGUI_IMPL

#endif // __GS_IMGUI_IMPL_H__
