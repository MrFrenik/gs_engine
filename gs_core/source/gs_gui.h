/*==============================================================================================================
		* Copyright: 2020 John Jackson 
		* Gunslinger Engine
		* File: gs_gui.h
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


#ifndef GS_GUI_H
#define GS_GUI_H

#define GS_REFL_IGNORE_FILE 

// Directly modified from microui implementation: https://github.com/rxi/microui 

#define GS_GUI_MAX_CNT              1000

#define GS_GUI_COMMANDLIST_SIZE		(256 * 1024 * 4)
#define GS_GUI_ROOTLIST_SIZE		GS_GUI_MAX_CNT
#define GS_GUI_CONTAINERSTACK_SIZE	GS_GUI_MAX_CNT
#define GS_GUI_CLIPSTACK_SIZE		GS_GUI_MAX_CNT
#define GS_GUI_IDSTACK_SIZE			GS_GUI_MAX_CNT
#define GS_GUI_LAYOUTSTACK_SIZE		GS_GUI_MAX_CNT
#define GS_GUI_CONTAINERPOOL_SIZE	GS_GUI_MAX_CNT
#define GS_GUI_TREENODEPOOL_SIZE	GS_GUI_MAX_CNT
#define GS_GUI_MAX_WIDTHS			16
#define GS_GUI_REAL					float
#define GS_GUI_REAL_FMT				"%.3g"
#define GS_GUI_SLIDER_FMT			"%.2f"
#define GS_GUI_MAX_FMT				127

#define gs_gui_stack(T, n)			struct {int32_t idx; T items[n];}

enum {
	GS_GUI_CLIP_PART = 1,
	GS_GUI_CLIP_ALL
};

enum {
	GS_GUI_COMMAND_JUMP = 1,
	GS_GUI_COMMAND_CLIP,
	GS_GUI_COMMAND_RECT,
	GS_GUI_COMMAND_TEXT,
	GS_GUI_COMMAND_ICON,
	GS_GUI_COMMAND_MAX
};

enum {
	GS_GUI_COLOR_TEXT,
	GS_GUI_COLOR_BORDER,
	GS_GUI_COLOR_WINDOWBG,
	GS_GUI_COLOR_TITLEBG,
	GS_GUI_COLOR_TITLETEXT,
	GS_GUI_COLOR_PANELBG,
	GS_GUI_COLOR_BUTTON,
	GS_GUI_COLOR_BUTTONHOVER,
	GS_GUI_COLOR_BUTTONFOCUS,
	GS_GUI_COLOR_BASE,
	GS_GUI_COLOR_BASEHOVER,
	GS_GUI_COLOR_BASEFOCUS,
	GS_GUI_COLOR_SCROLLBASE,
	GS_GUI_COLOR_SCROLLTHUMB,
	GS_GUI_COLOR_MAX
};

enum {
	GS_GUI_ICON_CLOSE = 1,
	GS_GUI_ICON_CHECK,
	GS_GUI_ICON_COLLAPSED,
	GS_GUI_ICON_EXPANDED,
	GS_GUI_ICON_MAX
};

enum {
	GS_GUI_RES_ACTIVE			 = (1 << 0),
	GS_GUI_RES_SUBMIT			 = (1 << 1),
	GS_GUI_RES_CHANGE			 = (1 << 2)
};

enum {
	GS_GUI_OPT_ALIGNCENTER	= (1 << 0),
	GS_GUI_OPT_ALIGNRIGHT	= (1 << 1),
	GS_GUI_OPT_NOINTERACT	= (1 << 2),
	GS_GUI_OPT_NOFRAME		= (1 << 3),
	GS_GUI_OPT_NORESIZE		= (1 << 4),
	GS_GUI_OPT_NOSCROLL		= (1 << 5),
	GS_GUI_OPT_NOCLOSE		= (1 << 6),
	GS_GUI_OPT_NOTITLE		= (1 << 7),
	GS_GUI_OPT_HOLDFOCUS	= (1 << 8),
	GS_GUI_OPT_AUTOSIZE		= (1 << 9),
	GS_GUI_OPT_POPUP		= (1 << 10),
	GS_GUI_OPT_CLOSED		= (1 << 11),
	GS_GUI_OPT_EXPANDED		= (1 << 12)
};

enum {
	GS_GUI_MOUSE_LEFT		= (1 << 0),
	GS_GUI_MOUSE_RIGHT		= (1 << 1),
	GS_GUI_MOUSE_MIDDLE		= (1 << 2)
};

enum {
	GS_GUI_KEY_SHIFT		= (1 << 0),
	GS_GUI_KEY_CTRL			= (1 << 1),
	GS_GUI_KEY_ALT			= (1 << 2),
	GS_GUI_KEY_BACKSPACE	= (1 << 3),
	GS_GUI_KEY_RETURN		= (1 << 4)
}; 

typedef struct gs_gui_context_t gs_gui_context_t;
typedef unsigned gs_gui_id;
typedef GS_GUI_REAL gs_gui_real;

typedef struct {float x, y, w, h;} gs_gui_rect_t;
typedef struct {gs_gui_id id; int32_t last_update;} gs_gui_pool_item_t;

typedef struct {int32_t type, size;} gs_gui_basecommand_t;
typedef struct {gs_gui_basecommand_t base; void *dst;} gs_gui_jumpcommand_t;
typedef struct {gs_gui_basecommand_t base; gs_gui_rect_t rect;} gs_gui_clipcommand_t;
typedef struct {gs_gui_basecommand_t base; gs_gui_rect_t rect; gs_color_t color;} gs_gui_rectcommand_t;
typedef struct {gs_gui_basecommand_t base; gs_asset_font_t* font; gs_vec2 pos; gs_color_t color; char str[1];} gs_gui_textcommand_t;
typedef struct {gs_gui_basecommand_t base; gs_gui_rect_t rect; int32_t id; gs_color_t color;} gs_gui_iconcommand_t;

typedef union 
{
	int32_t type;
	gs_gui_basecommand_t base;
	gs_gui_jumpcommand_t jump;
	gs_gui_clipcommand_t clip;
	gs_gui_rectcommand_t rect;
	gs_gui_textcommand_t text;
	gs_gui_iconcommand_t icon;
} gs_gui_command_t;

typedef struct gs_gui_layout_t
{
	gs_gui_rect_t body;
	gs_gui_rect_t next;
	gs_vec2 position;
	gs_vec2 size;
	gs_vec2 max;
	int32_t widths[GS_GUI_MAX_WIDTHS];
	int32_t items;
	int32_t item_index;
	int32_t next_row;
	int32_t next_type;
	int32_t indent;
} gs_gui_layout_t;

typedef struct gs_gui_container_t 
{
	gs_gui_command_t *head, *tail;
	gs_gui_rect_t rect;
	gs_gui_rect_t body;
	gs_vec2 content_size;
	gs_vec2 scroll;
	int32_t zindex;
	int32_t open;
} gs_gui_container_t;

typedef struct gs_gui_style_t
{
	gs_asset_font_t* font;
	gs_vec2 size;
	int32_t padding;
	int32_t spacing;
	int32_t indent;
	int32_t title_height;
	int32_t scrollbar_size;
	int32_t thumb_size;
	gs_color_t colors[GS_GUI_COLOR_MAX];
} gs_gui_style_t;

typedef struct gs_gui_context_t 
{ 
	// Callbacks
    int32_t (*text_width)(gs_asset_font_t* font, const char* text, int32_t len);
    int32_t (*text_height)(gs_asset_font_t* font, const char* text, int32_t len);
    gs_vec2 (*text_dimensions)(gs_asset_font_t* font, const char* text, int32_t len);
	void (*draw_frame)(gs_gui_context_t *ctx, gs_gui_rect_t rect, int32_t colorid);

	// Core state
	gs_gui_style_t _style;
	gs_gui_style_t* style;
	gs_gui_id hover;
	gs_gui_id focus;
	gs_gui_id last_id;
	gs_gui_rect_t last_rect;
	int32_t last_zindex;
	int32_t updated_focus;
	int32_t frame;
	gs_gui_container_t* hover_root;
	gs_gui_container_t* next_hover_root;
	gs_gui_container_t* scroll_target;
	char number_edit_buf[GS_GUI_MAX_FMT];
	gs_gui_id number_edit;

	// Stacks
	gs_gui_stack(char, GS_GUI_COMMANDLIST_SIZE) command_list;
	gs_gui_stack(gs_gui_container_t*, GS_GUI_ROOTLIST_SIZE) root_list;
	gs_gui_stack(gs_gui_container_t*, GS_GUI_CONTAINERSTACK_SIZE) container_stack;
	gs_gui_stack(gs_gui_rect_t, GS_GUI_CLIPSTACK_SIZE) clip_stack;
	gs_gui_stack(gs_gui_id, GS_GUI_IDSTACK_SIZE) id_stack;
	gs_gui_stack(gs_gui_layout_t, GS_GUI_LAYOUTSTACK_SIZE) layout_stack;

	// Retained state pools
	gs_gui_pool_item_t container_pool[GS_GUI_CONTAINERPOOL_SIZE];
	gs_gui_container_t containers[GS_GUI_CONTAINERPOOL_SIZE];
	gs_gui_pool_item_t treenode_pool[GS_GUI_TREENODEPOOL_SIZE];

	// Input state
	gs_vec2 mouse_pos;
	gs_vec2 last_mouse_pos;
	gs_vec2 mouse_delta;
	gs_vec2 scroll_delta;
	int32_t mouse_down;
	int32_t mouse_pressed;
	int32_t key_down;
	int32_t key_pressed;
	char input_text[32];

    uint32_t window_hndl;

    gs_immediate_draw_t gsi;
    gs_handle(gs_graphics_texture_t) atlas_tex;

} gs_gui_context_t; 

gs_gui_rect_t gs_gui_rect(float x, float y, float w, float h);

GS_API_DECL void gs_gui_init(gs_gui_context_t *ctx, uint32_t window_hndl);
GS_API_DECL void gs_gui_begin(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_end(gs_gui_context_t *ctx); 
GS_API_DECL void gs_gui_render(gs_gui_context_t* ctx, gs_command_buffer_t* cb);
GS_API_DECL void gs_gui_set_focus(gs_gui_context_t *ctx, gs_gui_id id);
GS_API_DECL gs_gui_id gs_gui_get_id(gs_gui_context_t *ctx, const void *data, int32_t size);
GS_API_DECL void gs_gui_push_id(gs_gui_context_t *ctx, const void *data, int32_t size);
GS_API_DECL void gs_gui_pop_id(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_push_clip_rect(gs_gui_context_t *ctx, gs_gui_rect_t rect);
GS_API_DECL void gs_gui_pop_clip_rect(gs_gui_context_t *ctx);
GS_API_DECL gs_gui_rect_t gs_gui_get_clip_rect(gs_gui_context_t *ctx);
GS_API_DECL int32_t gs_gui_check_clip(gs_gui_context_t *ctx, gs_gui_rect_t r);
GS_API_DECL gs_gui_container_t* gs_gui_get_current_container(gs_gui_context_t *ctx);
GS_API_DECL gs_gui_container_t* gs_gui_gs_gui_get_container(gs_gui_context_t *ctx, const char *name);
GS_API_DECL void gs_gui_bring_to_front(gs_gui_context_t *ctx, gs_gui_container_t *cnt);

GS_API_DECL int32_t gs_gui_pool_init(gs_gui_context_t *ctx, gs_gui_pool_item_t *items, int32_t len, gs_gui_id id);
GS_API_DECL int32_t gs_gui_pool_get(gs_gui_context_t *ctx, gs_gui_pool_item_t *items, int32_t len, gs_gui_id id);
GS_API_DECL void gs_gui_pool_update(gs_gui_context_t *ctx, gs_gui_pool_item_t *items, int32_t idx);

GS_API_DECL void gs_gui_input_mousemove(gs_gui_context_t *ctx, int32_t x, int32_t y);
GS_API_DECL void gs_gui_input_mousedown(gs_gui_context_t *ctx, int32_t x, int32_t y, int32_t btn);
GS_API_DECL void gs_gui_input_mouseup(gs_gui_context_t *ctx, int32_t x, int32_t y, int32_t btn);
GS_API_DECL void gs_gui_input_scroll(gs_gui_context_t *ctx, int32_t x, int32_t y);
GS_API_DECL void gs_gui_input_keydown(gs_gui_context_t *ctx, int32_t key);
GS_API_DECL void gs_gui_input_keyup(gs_gui_context_t *ctx, int32_t key);
GS_API_DECL void gs_gui_input_text(gs_gui_context_t *ctx, const char *text);

GS_API_DECL gs_gui_command_t* gs_gui_push_command(gs_gui_context_t *ctx, int32_t type, int32_t size);
GS_API_DECL int32_t gs_gui_next_command(gs_gui_context_t *ctx, gs_gui_command_t **cmd);
GS_API_DECL void gs_gui_set_clip(gs_gui_context_t *ctx, gs_gui_rect_t rect);
GS_API_DECL void gs_gui_draw_rect(gs_gui_context_t *ctx, gs_gui_rect_t rect, gs_color_t color);
GS_API_DECL void gs_gui_draw_box(gs_gui_context_t *ctx, gs_gui_rect_t rect, gs_color_t color);
GS_API_DECL void gs_gui_draw_text(gs_gui_context_t *ctx, gs_asset_font_t* font, const char *str, int32_t len, gs_vec2 pos, gs_color_t color);
GS_API_DECL void gs_gui_draw_icon(gs_gui_context_t *ctx, int32_t id, gs_gui_rect_t rect, gs_color_t color);

GS_API_DECL void gs_gui_layout_row(gs_gui_context_t *ctx, int32_t items, const int32_t *widths, int32_t height);
GS_API_DECL void gs_gui_layout_width(gs_gui_context_t *ctx, int32_t width);
GS_API_DECL void gs_gui_layout_height(gs_gui_context_t *ctx, int32_t height);
GS_API_DECL void gs_gui_layout_begin_column(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_layout_end_column(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_layout_set_next(gs_gui_context_t *ctx, gs_gui_rect_t r, int32_t relative);
GS_API_DECL gs_gui_rect_t gs_gui_layout_next(gs_gui_context_t *ctx);

GS_API_DECL void gs_gui_draw_control_frame(gs_gui_context_t *ctx, gs_gui_id id, gs_gui_rect_t rect, int32_t colorid, int32_t opt);
GS_API_DECL void gs_gui_draw_control_text(gs_gui_context_t *ctx, const char *str, gs_gui_rect_t rect, int32_t colorid, int32_t opt);
GS_API_DECL int32_t gs_gui_mouse_over(gs_gui_context_t *ctx, gs_gui_rect_t rect);
GS_API_DECL void gs_gui_update_control(gs_gui_context_t *ctx, gs_gui_id id, gs_gui_rect_t rect, int32_t opt);

// Widgets
#define gs_gui_button(_CTX, _LABEL)				    gs_gui_button_ex((_CTX), (_LABEL), 0, GS_GUI_OPT_ALIGNCENTER)
#define gs_gui_textbox(_CTX, _BUF, _BUFSZ)			gs_gui_textbox_ex((_CTX), (_BUF), (_BUFSZ), 0)
#define gs_gui_slider(_CTX, _VALUE, _LO, _HI)		gs_gui_slider_ex((_CTX), (_VALUE), (_LO), (_HI), 0, GS_GUI_SLIDER_FMT, GS_GUI_OPT_ALIGNCENTER)
#define gs_gui_number(_CTX, _VALUE, _STEP)			gs_gui_number_ex((_CTX), (_VALUE), (_STEP), GS_GUI_SLIDER_FMT, GS_GUI_OPT_ALIGNCENTER)
#define gs_gui_gs_gui_header(_CTX, _LABEL)		    gs_gui_header_ex((_CTX), (_LABEL), 0)
#define gs_gui_begin_treenode(_CTX, _LABEL)	        gs_gui_begin_treenode_ex((_CTX), (_LABEL), 0)
#define gs_gui_begin_window(_CTX, _TITLE, _RECT)    gs_gui_begin_window_ex((_CTX), (_TITLE), (_RECT), 0)
#define gs_gui_begin_panel(_CTX, _NAME)			    gs_gui_begin_panel_ex((_CTX), (_NAME), 0)

GS_API_DECL void gs_gui_text(gs_gui_context_t *ctx, const char *text);
GS_API_DECL void gs_gui_label(gs_gui_context_t *ctx, const char *text);
GS_API_DECL int32_t gs_gui_button_ex(gs_gui_context_t *ctx, const char *label, int32_t icon, int32_t opt);
GS_API_DECL int32_t gs_gui_checkbox(gs_gui_context_t *ctx, const char *label, int32_t *state);
GS_API_DECL int32_t gs_gui_textbox_raw(gs_gui_context_t *ctx, char *buf, int32_t bufsz, gs_gui_id id, gs_gui_rect_t r, int32_t opt);
GS_API_DECL int32_t gs_gui_textbox_ex(gs_gui_context_t *ctx, char *buf, int32_t bufsz, int32_t opt);
GS_API_DECL int32_t gs_gui_slider_ex(gs_gui_context_t *ctx, gs_gui_real *value, gs_gui_real low, gs_gui_real high, gs_gui_real step, const char *fmt, int32_t opt);
GS_API_DECL int32_t gs_gui_number_ex(gs_gui_context_t *ctx, gs_gui_real *value, gs_gui_real step, const char *fmt, int32_t opt);
GS_API_DECL int32_t gs_gui_header_ex(gs_gui_context_t *ctx, const char *label, int32_t opt);
GS_API_DECL int32_t gs_gui_begin_treenode_ex(gs_gui_context_t *ctx, const char *label, int32_t opt);
GS_API_DECL void gs_gui_end_treenode(gs_gui_context_t *ctx);
GS_API_DECL int32_t gs_gui_begin_window_ex(gs_gui_context_t *ctx, const char *title, gs_gui_rect_t rect, int32_t opt);
GS_API_DECL void gs_gui_end_window(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_open_popup(gs_gui_context_t *ctx, const char *name);
GS_API_DECL int32_t gs_gui_begin_popup(gs_gui_context_t *ctx, const char *name);
GS_API_DECL void gs_gui_end_popup(gs_gui_context_t *ctx);
GS_API_DECL void gs_gui_begin_panel_ex(gs_gui_context_t *ctx, const char *name, int32_t opt);
GS_API_DECL void gs_gui_end_panel(gs_gui_context_t *ctx);

#ifdef GS_GUI_IMPL 

#define gs_gui_unused(x) ((void) (x))

#define gs_gui_expect(x)\
    do {																                    \
		if (!(x)) {																			\
			gs_println(stderr, "Fatal error: %s:%d: assertion '%s' failed\n",               \
				__FILE__, __LINE__, #x);												    \
			abort();																		\
		}																					\
	} while (0)

#define gs_gui_stack_push(stk, val)\
    do {												                                    \
		gs_gui_expect((stk).idx < (int32_t) (sizeof((stk).items) / sizeof(*(stk).items)));  \
		(stk).items[(stk).idx] = (val);													    \
		(stk).idx++; /* incremented after incase `val` uses this value */			        \
	} while (0)

#define gs_gui_stack_pop(stk)\
    do {			                    \
		gs_gui_expect((stk).idx > 0);   \
		(stk).idx--;					\
	} while (0) 

/* 32bit fnv-1a hash */
#define GS_GUI_HASH_INITIAL 2166136261

static void gs_gui_hash(gs_gui_id *hash, const void *data, int32_t size) 
{
	const unsigned char *p = data;
	while (size--) 
    {
		*hash = (*hash ^ *p++) * 16777619;
	}
} 

static gs_gui_rect_t gs_gui_unclipped_rect = { 0, 0, 0x1000000, 0x1000000 };

static gs_gui_style_t gs_gui_default_style = 
{
	/* font | size | padding | spacing | indent */
	NULL, { 68, 10 }, 5, 4, 24,
	/* title_height | scrollbar_size | thumb_size */
	24, 12, 8,
	{
		{ 230, 230, 230, 255 }, /* GS_GUI_COLOR_TEXT */
		{ 25,	25,	25,	255 }, /* GS_GUI_COLOR_BORDER */
		{ 50,	50,	50,	255 }, /* GS_GUI_COLOR_WINDOWBG */
		{ 25,	25,	25,	255 }, /* GS_GUI_COLOR_TITLEBG */
		{ 240, 240, 240, 255 }, /* GS_GUI_COLOR_TITLETEXT */
		{ 0,	 0,	 0,	 0	 }, /* GS_GUI_COLOR_PANELBG */
		{ 75,	75,	75,	255 }, /* GS_GUI_COLOR_BUTTON */
		{ 95,	95,	95,	255 }, /* GS_GUI_COLOR_BUTTONHOVER */
		{ 115, 115, 115, 255 }, /* GS_GUI_COLOR_BUTTONFOCUS */
		{ 30,	30,	30,	255 }, /* GS_GUI_COLOR_BASE */
		{ 35,	35,	35,	255 }, /* GS_GUI_COLOR_BASEHOVER */
		{ 40,	40,	40,	255 }, /* GS_GUI_COLOR_BASEFOCUS */
		{ 43,	43,	43,	255 }, /* GS_GUI_COLOR_SCROLLBASE */
		{ 30,	30,	30,	255 }	/* GS_GUI_COLOR_SCROLLTHUMB */
	}
}; 

GS_API_DECL gs_gui_rect_t gs_gui_rect(float x, float y, float w, float h) 
{
	gs_gui_rect_t res;
	res.x = x; res.y = y; res.w = w; res.h = h;
	return res;
} 

static gs_gui_rect_t gs_gui_expand_rect(gs_gui_rect_t rect, int32_t n) 
{
	return gs_gui_rect(rect.x - n, rect.y - n, rect.w + n * 2, rect.h + n * 2);
} 

static gs_gui_rect_t gs_gui_intersect_rects(gs_gui_rect_t r1, gs_gui_rect_t r2) 
{
	int32_t x1 = gs_max(r1.x, r2.x);
	int32_t y1 = gs_max(r1.y, r2.y);
	int32_t x2 = gs_min(r1.x + r1.w, r2.x + r2.w);
	int32_t y2 = gs_min(r1.y + r1.h, r2.y + r2.h);
	if (x2 < x1) { x2 = x1; }
	if (y2 < y1) { y2 = y1; }
	return gs_gui_rect(x1, y1, x2 - x1, y2 - y1);
}

static int32_t gs_gui_rect_overlaps_vec2(gs_gui_rect_t r, gs_vec2 p) 
{
	return p.x >= r.x && p.x < r.x + r.w && p.y >= r.y && p.y < r.y + r.h;
} 

static void gs_gui_draw_frame(gs_gui_context_t* ctx, gs_gui_rect_t rect, int32_t colorid) 
{
	gs_gui_draw_rect(ctx, rect, ctx->style->colors[colorid]);

	if (
        colorid == GS_GUI_COLOR_SCROLLBASE || 
        colorid == GS_GUI_COLOR_SCROLLTHUMB || 
        colorid == GS_GUI_COLOR_TITLEBG
    ) 
    { 
        return; 
    }

	// draw border
	if (ctx->style->colors[GS_GUI_COLOR_BORDER].a) 
    {
		gs_gui_draw_box(ctx, gs_gui_expand_rect(rect, 1), ctx->style->colors[GS_GUI_COLOR_BORDER]);
	}
}

static int32_t gs_gui_compare_zindex(const void *a, const void *b) 
{
	return (*(gs_gui_container_t**) a)->zindex - (*(gs_gui_container_t**) b)->zindex;
} 

static gs_gui_container_t* gs_gui_get_container(gs_gui_context_t *ctx, gs_gui_id id, int32_t opt) 
{
	gs_gui_container_t *cnt;

	/* try to get existing container from pool */
	int32_t idx = gs_gui_pool_get(ctx, ctx->container_pool, GS_GUI_CONTAINERPOOL_SIZE, id);

	if (idx >= 0) 
    {
		if (ctx->containers[idx].open || ~opt & GS_GUI_OPT_CLOSED) 
        {
			gs_gui_pool_update(ctx, ctx->container_pool, idx);
		}
		return &ctx->containers[idx];
	}

	if (opt & GS_GUI_OPT_CLOSED) { return NULL; }

	/* container not found in pool: init new container */
	idx = gs_gui_pool_init(ctx, ctx->container_pool, GS_GUI_CONTAINERPOOL_SIZE, id);
	cnt = &ctx->containers[idx];
	memset(cnt, 0, sizeof(*cnt));
	cnt->open = 1;
	gs_gui_bring_to_front(ctx, cnt);

	return cnt;
}

static void gs_gui_push_layout(gs_gui_context_t *ctx, gs_gui_rect_t body, gs_vec2 scroll) 
{
	gs_gui_layout_t layout;
	int32_t width = 0;
	memset(&layout, 0, sizeof(layout));
	layout.body = gs_gui_rect(body.x - scroll.x, body.y - scroll.y, body.w, body.h);
	layout.max = gs_v2(-0x1000000, -0x1000000);
	gs_gui_stack_push(ctx->layout_stack, layout);
	gs_gui_layout_row(ctx, 1, &width, 0);
} 

static gs_gui_layout_t* gs_gui_get_layout(gs_gui_context_t *ctx) 
{
	return &ctx->layout_stack.items[ctx->layout_stack.idx - 1];
}

static void gs_gui_pop_container(gs_gui_context_t *ctx) 
{
	gs_gui_container_t *cnt = gs_gui_get_current_container(ctx);
	gs_gui_layout_t *layout = gs_gui_get_layout(ctx);
	cnt->content_size.x = layout->max.x - layout->body.x;
	cnt->content_size.y = layout->max.y - layout->body.y;

	/* pop container, layout and id */
	gs_gui_stack_pop(ctx->container_stack);
	gs_gui_stack_pop(ctx->layout_stack);
	gs_gui_pop_id(ctx);
} 

static int32_t gs_gui_text_width(gs_asset_font_t* font, const char* text, int32_t len) 
{ 
    gs_vec2 td = gs_asset_font_get_text_dimensions(font, text, len);
    return (int32_t)td.x;
}

static int32_t gs_gui_text_height(gs_asset_font_t* font, const char* text, int32_t len) 
{
    gs_vec2 td = gs_asset_font_get_text_dimensions(font, text, len);
    return (int32_t)td.y;
} 

static gs_vec2 gs_gui_text_dimensions(gs_asset_font_t* font, const char* text, int32_t len) 
{
    gs_vec2 td = gs_asset_font_get_text_dimensions(font, text, len);
    return td;
} 

GS_API_DECL void gs_gui_init(gs_gui_context_t *ctx, uint32_t window_hndl)
{
	memset(ctx, 0, sizeof(*ctx));
    ctx->text_height = gs_gui_text_height;
    ctx->text_width = gs_gui_text_width;
    ctx->text_dimensions = gs_gui_text_dimensions;
	ctx->draw_frame = gs_gui_draw_frame; 
    ctx->gsi = gs_immediate_draw_new(window_hndl); 
	ctx->_style = gs_gui_default_style; 
    ctx->_style.font = &ctx->gsi.font_default;
	ctx->style = &ctx->_style;
    ctx->window_hndl = window_hndl;
} 

static const char button_map[256] = {
  [GS_MOUSE_LBUTTON  & 0xff] =  GS_GUI_MOUSE_LEFT,
  [GS_MOUSE_RBUTTON  & 0xff] =  GS_GUI_MOUSE_RIGHT,
  [GS_MOUSE_MBUTTON  & 0xff] =  GS_GUI_MOUSE_MIDDLE
};

static const char key_map[512] = {
  [GS_KEYCODE_LEFT_SHIFT    & 0xff] = GS_GUI_KEY_SHIFT,
  [GS_KEYCODE_RIGHT_SHIFT   & 0xff] = GS_GUI_KEY_SHIFT,
  [GS_KEYCODE_LEFT_CONTROL  & 0xff] = GS_GUI_KEY_CTRL,
  [GS_KEYCODE_RIGHT_CONTROL & 0xff] = GS_GUI_KEY_CTRL,
  [GS_KEYCODE_LEFT_ALT      & 0xff] = GS_GUI_KEY_ALT,
  [GS_KEYCODE_RIGHT_ALT     & 0xff] = GS_GUI_KEY_ALT,
  [GS_KEYCODE_ENTER         & 0xff] = GS_GUI_KEY_RETURN,
  [GS_KEYCODE_BACKSPACE     & 0xff] = GS_GUI_KEY_BACKSPACE
};

GS_API_DECL void gs_gui_begin(gs_gui_context_t* ctx) 
{
    // Capture event information
    gs_vec2 mouse_pos = gs_platform_mouse_positionv(); 
    gs_platform_event_t evt = gs_default_val(); 
    while (gs_platform_poll_events(&evt, false))
    {
        switch (evt.type)
        {
            case GS_PLATFORM_EVENT_MOUSE:
            {
                switch (evt.mouse.action)
                {
                    case GS_PLATFORM_MOUSE_MOVE:
                    {
                        ctx->mouse_pos = evt.mouse.move;
                    } break;

                    case GS_PLATFORM_MOUSE_WHEEL:
                    {
                        gs_gui_input_scroll(ctx, 0, (int32_t)evt.mouse.wheel.y);
                    } break;

                    case GS_PLATFORM_MOUSE_BUTTON_DOWN:
                    case GS_PLATFORM_MOUSE_BUTTON_PRESSED:
                    {
                        int32_t code = 1 << evt.mouse.button;
                        gs_gui_input_mousedown(ctx, (int32_t)mouse_pos.x, (int32_t)mouse_pos.y, code);
                    } break;

                    case GS_PLATFORM_MOUSE_BUTTON_RELEASED:
                    {
                        int32_t code = 1 << evt.mouse.button;
                        gs_gui_input_mouseup(ctx, (int32_t)mouse_pos.x, (int32_t)mouse_pos.y, code);
                    } break; 

                    case GS_PLATFORM_MOUSE_ENTER:
                    {
                        // If there are user callbacks, could trigger them here
                    } break;

                    case GS_PLATFORM_MOUSE_LEAVE:
                    {
                        // If there are user callbacks, could trigger them here
                    } break;

                    default: break; 
                }

            } break;

            case GS_PLATFORM_EVENT_TEXT:
            {
                // Input text
                char txt[2] = {(char)(evt.text.codepoint & 255), 0};
                gs_gui_input_text(ctx, txt);
            } break;

            case GS_PLATFORM_EVENT_KEY:
            {
                switch (evt.key.action)
                { 
                    case GS_PLATFORM_KEY_DOWN:
                    case GS_PLATFORM_KEY_PRESSED:
                    { 
                        gs_gui_input_keydown(ctx, key_map[evt.key.keycode & 511]); 
                    } break; 

                    case GS_PLATFORM_KEY_RELEASED:
                    {
                        gs_gui_input_keyup(ctx, key_map[evt.key.keycode & 511]);
                    } break;

                    default: break;
                }

            } break;

            case GS_PLATFORM_EVENT_WINDOW:
            {
                switch (evt.window.action)
                {
                    default: break;
                }

            } break;


            default: break;
        }
    }

	ctx->command_list.idx = 0;
	ctx->root_list.idx = 0;
	ctx->scroll_target = NULL;
	ctx->hover_root = ctx->next_hover_root;
	ctx->next_hover_root = NULL;
	ctx->mouse_delta.x = ctx->mouse_pos.x - ctx->last_mouse_pos.x;
	ctx->mouse_delta.y = ctx->mouse_pos.y - ctx->last_mouse_pos.y;
	ctx->frame++; 
} 

GS_API_DECL void gs_gui_end(gs_gui_context_t *ctx) 
{
	int32_t i, n;

	/* check stacks */
	gs_gui_expect(ctx->container_stack.idx == 0);
	gs_gui_expect(ctx->clip_stack.idx == 0);
	gs_gui_expect(ctx->id_stack.idx == 0);
	gs_gui_expect(ctx->layout_stack.idx	== 0);

	/* handle scroll input */
	if (ctx->scroll_target) 
    {
		ctx->scroll_target->scroll.x += ctx->scroll_delta.x;
		ctx->scroll_target->scroll.y += ctx->scroll_delta.y;
	}

	/* unset focus if focus id was not touched this frame */
	if (!ctx->updated_focus) { ctx->focus = 0; }
	ctx->updated_focus = 0;

	/* bring hover root to front if mouse was pressed */
	if (ctx->mouse_pressed && ctx->next_hover_root &&
			ctx->next_hover_root->zindex < ctx->last_zindex &&
			ctx->next_hover_root->zindex >= 0
	) 
    {
		gs_gui_bring_to_front(ctx, ctx->next_hover_root);
	}

	/* reset input state */
	ctx->key_pressed = 0;
	ctx->input_text[0] = '\0';
	ctx->mouse_pressed = 0;
	ctx->scroll_delta = gs_v2(0, 0);
	ctx->last_mouse_pos = ctx->mouse_pos;

	/* sort root containers by zindex */
	n = ctx->root_list.idx;
	qsort(ctx->root_list.items, n, sizeof(gs_gui_container_t*), gs_gui_compare_zindex);

	/* set root container jump commands */
	for (i = 0; i < n; i++) 
    {
		gs_gui_container_t *cnt = ctx->root_list.items[i];

		/* if this is the first container then make the first command jump to it.  
		** otherwise set the previous container's tail to jump to this one */ 
		if (i == 0) 
        {
			gs_gui_command_t *cmd = (gs_gui_command_t*) ctx->command_list.items;
			cmd->jump.dst = (char*) cnt->head + sizeof(gs_gui_jumpcommand_t);
		} 
        else 
        {
			gs_gui_container_t *prev = ctx->root_list.items[i - 1];
			prev->tail->jump.dst = (char*) cnt->head + sizeof(gs_gui_jumpcommand_t);
		}

		/* make the last container's tail jump to the end of command list */
		if (i == n - 1) 
        {
			cnt->tail->jump.dst = ctx->command_list.items + ctx->command_list.idx;
		}
	}
} 

GS_API_DECL void gs_gui_render(gs_gui_context_t* ctx, gs_command_buffer_t* cb)
{
    // mu_end(&ctx->mu);
    // gsi_texture(&ctx->gsi,ctx->atlas_tex);

    const gs_vec2 fb = gs_platform_framebuffer_sizev(ctx->window_hndl);

    gsi_camera2D(&ctx->gsi);

    gs_gui_command_t* cmd = NULL; 
    while (gs_gui_next_command(ctx, &cmd)) 
    {
      switch (cmd->type) 
      {
        case GS_GUI_COMMAND_TEXT:
        {
            const gs_vec2* tp = &cmd->text.pos;
            const char* ts = &cmd->text.str;
            const gs_color_t* tc = &cmd->text.color; 
            const gs_asset_font_t* tf = cmd->text.font;
            gsi_text(&ctx->gsi, tp->x, tp->y, ts, tf, false, tc->r, tc->g, tc->b, tc->a);
        } break;

        case GS_GUI_COMMAND_RECT:
        {
            gsi_texture(&ctx->gsi, gs_handle_invalid(gs_graphics_texture_t));
            gs_gui_rect_t* r = &cmd->rect.rect; 
            gs_color_t* c = &cmd->rect.color;
            gsi_rectvd(&ctx->gsi, gs_v2(r->x, r->y), gs_v2(r->w, r->h), gs_v2s(0.f), gs_v2s(1.f), *c, GS_GRAPHICS_PRIMITIVE_TRIANGLES);
        } break;

        case GS_GUI_COMMAND_ICON:
        {
            /*
            gsi_texture(&ctx->gsi, ctx->atlas_tex);
            gs_gui_rect_t src = atlas[cmd->icon.id];
            int x = cmd->icon.rect.x + (cmd->icon.rect.w - src.w) / 2;
            int y = cmd->icon.rect.y + (cmd->icon.rect.h - src.h) / 2;
            __push_quad(&ctx->gsi, (&(mu_Rect){.x = x, .y = y, .w = src.w, .h = src.h}), &src, &cmd->icon.color);
            */
        } break;

        case GS_GUI_COMMAND_CLIP:
        { 
            // Will project scissor/clipping rectangles into framebuffer space
            gs_vec2 clip_off = gs_v2s(0.f);     // (0,0) unless using multi-viewports
            gs_vec2 clip_scale = gs_v2s(1.f);   // (1,1) unless using retina display which are often (2,2) 

            gs_gui_rect_t clip_rect;
            clip_rect.x = (cmd->clip.rect.x - clip_off.x) * clip_scale.x;
            clip_rect.y = (cmd->clip.rect.y - clip_off.y) * clip_scale.y;
            clip_rect.w = (cmd->clip.rect.w - clip_off.x) * clip_scale.x;
            clip_rect.h = (cmd->clip.rect.h - clip_off.y) * clip_scale.y;

            clip_rect.x = gs_max(clip_rect.x, 0.f);
            clip_rect.y = gs_max(clip_rect.y, 0.f);
            clip_rect.w = gs_max(clip_rect.w, 0.f);
            clip_rect.h = gs_max(clip_rect.h, 0.f); 

            gsi_set_view_scissor(&ctx->gsi, 
                (int32_t)(clip_rect.x), 
                (int32_t)(fb.y - clip_rect.h - clip_rect.y), 
                (int32_t)(clip_rect.w), 
                (int32_t)(clip_rect.h));

        } break;
      }
    }
    gsi_draw(&ctx->gsi, cb); 
}

GS_API_DECL void gs_gui_set_focus(gs_gui_context_t* ctx, gs_gui_id id) 
{
	ctx->focus = id;
	ctx->updated_focus = 1;
}

GS_API_DECL gs_gui_id gs_gui_get_id(gs_gui_context_t* ctx, const void* data, int32_t size) 
{
	int32_t idx = ctx->id_stack.idx;
	gs_gui_id res = (idx > 0) ? ctx->id_stack.items[idx - 1] : GS_GUI_HASH_INITIAL;
	gs_gui_hash(&res, data, size);
	ctx->last_id = res;
	return res;
}

GS_API_DECL void gs_gui_push_id(gs_gui_context_t* ctx, const void* data, int32_t size) 
{
	gs_gui_stack_push(ctx->id_stack, gs_gui_get_id(ctx, data, size));
}

GS_API_DECL void gs_gui_pop_id(gs_gui_context_t* ctx) 
{
	gs_gui_stack_pop(ctx->id_stack);
} 

GS_API_DECL void gs_gui_push_clip_rect(gs_gui_context_t* ctx, gs_gui_rect_t rect) 
{
	gs_gui_rect_t last = gs_gui_get_clip_rect(ctx);
	gs_gui_stack_push(ctx->clip_stack, gs_gui_intersect_rects(rect, last));
} 

GS_API_DECL void gs_gui_pop_clip_rect(gs_gui_context_t* ctx) 
{
	gs_gui_stack_pop(ctx->clip_stack);
} 

GS_API_DECL gs_gui_rect_t gs_gui_get_clip_rect(gs_gui_context_t* ctx) 
{
	gs_gui_expect(ctx->clip_stack.idx > 0);
	return ctx->clip_stack.items[ctx->clip_stack.idx - 1];
} 

GS_API_DECL int32_t gs_gui_check_clip(gs_gui_context_t* ctx, gs_gui_rect_t r) 
{
	gs_gui_rect_t cr = gs_gui_get_clip_rect(ctx);

	if (r.x > cr.x + cr.w || r.x + r.w < cr.x ||
			r.y > cr.y + cr.h || r.y + r.h < cr.y) 
    { 
        return GS_GUI_CLIP_ALL; 
    }

	if (r.x >= cr.x && r.x + r.w <= cr.x + cr.w &&
			r.y >= cr.y && r.y + r.h <= cr.y + cr.h ) 
    { 
        return 0; 
    }

	return GS_GUI_CLIP_PART;
}

GS_API_DECL gs_gui_container_t* gs_gui_get_current_container(gs_gui_context_t* ctx) 
{
	gs_gui_expect(ctx->container_stack.idx > 0);
	return ctx->container_stack.items[ ctx->container_stack.idx - 1 ];
} 

GS_API_DECL gs_gui_container_t* gs_gui_gs_gui_get_container(gs_gui_context_t* ctx, const char* name) 
{
	gs_gui_id id = gs_gui_get_id(ctx, name, strlen(name));
	return gs_gui_get_container(ctx, id, 0);
}

GS_API_DECL void gs_gui_bring_to_front(gs_gui_context_t* ctx, gs_gui_container_t* cnt) 
{
	cnt->zindex = ++ctx->last_zindex;
} 

/*============================================================================
** Pool
**============================================================================*/

GS_API_DECL int32_t gs_gui_pool_init(gs_gui_context_t* ctx, gs_gui_pool_item_t* items, int32_t len, gs_gui_id id) 
{
	int32_t i, n = -1, f = ctx->frame;
	for (i = 0; i < len; i++) 
    {
		if (items[i].last_update < f) 
        {
			f = items[i].last_update;
			n = i;
		}
	}

	gs_gui_expect(n > -1);
	items[n].id = id;
	gs_gui_pool_update(ctx, items, n);

	return n;
} 

GS_API_DECL int32_t gs_gui_pool_get(gs_gui_context_t* ctx, gs_gui_pool_item_t* items, int32_t len, gs_gui_id id) 
{
	int32_t i;
	gs_gui_unused(ctx);
	for (i = 0; i < len; i++) 
    {
		if (items[i].id == id) 
        { 
            return i; 
        }
	}
	return -1;
}

GS_API_DECL void gs_gui_pool_update(gs_gui_context_t* ctx, gs_gui_pool_item_t* items, int32_t idx) 
{
	items[idx].last_update = ctx->frame;
} 

/*============================================================================
** input handlers
**============================================================================*/

GS_API_DECL void gs_gui_input_mousemove(gs_gui_context_t* ctx, int32_t x, int32_t y) 
{
	ctx->mouse_pos = gs_v2(x, y);
}

GS_API_DECL void gs_gui_input_mousedown(gs_gui_context_t* ctx, int32_t x, int32_t y, int32_t btn) 
{
	gs_gui_input_mousemove(ctx, x, y);
	ctx->mouse_down |= btn;
	ctx->mouse_pressed |= btn;
}

GS_API_DECL void gs_gui_input_mouseup(gs_gui_context_t* ctx, int32_t x, int32_t y, int32_t btn) 
{
	gs_gui_input_mousemove(ctx, x, y);
	ctx->mouse_down &= ~btn;
} 

GS_API_DECL void gs_gui_input_scroll(gs_gui_context_t* ctx, int32_t x, int32_t y) 
{
	ctx->scroll_delta.x += x;
	ctx->scroll_delta.y += y;
} 

GS_API_DECL void gs_gui_input_keydown(gs_gui_context_t* ctx, int32_t key) 
{
	ctx->key_pressed |= key;
	ctx->key_down |= key;
} 

GS_API_DECL void gs_gui_input_keyup(gs_gui_context_t* ctx, int32_t key) 
{
	ctx->key_down &= ~key;
} 

GS_API_DECL void gs_gui_input_text(gs_gui_context_t* ctx, const char* text) 
{
	int32_t len = strlen(ctx->input_text);
	int32_t size = strlen(text) + 1;
	if (len + size > (int32_t)sizeof(ctx->input_text)) return;
	memcpy(ctx->input_text + len, text, size);
} 

/*============================================================================
** commandlist
**============================================================================*/

static gs_gui_command_t* gs_gui_push_jump(gs_gui_context_t* ctx, gs_gui_command_t* dst) 
{
	gs_gui_command_t* cmd;
	cmd = gs_gui_push_command(ctx, GS_GUI_COMMAND_JUMP, sizeof(gs_gui_jumpcommand_t));
	cmd->jump.dst = dst;
	return cmd;
} 

GS_API_DECL gs_gui_command_t* gs_gui_push_command(gs_gui_context_t* ctx, int32_t type, int32_t size) 
{
	gs_gui_command_t* cmd = (gs_gui_command_t*) (ctx->command_list.items + ctx->command_list.idx);
	gs_gui_expect(ctx->command_list.idx + size < GS_GUI_COMMANDLIST_SIZE);
	cmd->base.type = type;
	cmd->base.size = size;
	ctx->command_list.idx += size;
	return cmd;
} 

GS_API_DECL int32_t gs_gui_next_command(gs_gui_context_t* ctx, gs_gui_command_t** cmd) 
{
	if (*cmd) 
    {
		*cmd = (gs_gui_command_t*) (((char*) *cmd) + (*cmd)->base.size);
	} 
    else 
    {
		*cmd = (gs_gui_command_t*) ctx->command_list.items;
	}

	while ((char*) *cmd != ctx->command_list.items + ctx->command_list.idx) 
    {
		if ((*cmd)->type != GS_GUI_COMMAND_JUMP) 
        { 
            return 1; 
        }
		*cmd = (*cmd)->jump.dst;
	}
	return 0;
} 

GS_API_DECL void gs_gui_set_clip(gs_gui_context_t* ctx, gs_gui_rect_t rect) 
{
	gs_gui_command_t* cmd;
	cmd = gs_gui_push_command(ctx, GS_GUI_COMMAND_CLIP, sizeof(gs_gui_clipcommand_t));
	cmd->clip.rect = rect;
} 

GS_API_DECL void gs_gui_draw_rect(gs_gui_context_t* ctx, gs_gui_rect_t rect, gs_color_t color) 
{
	gs_gui_command_t* cmd;
	rect = gs_gui_intersect_rects(rect, gs_gui_get_clip_rect(ctx));
	if (rect.w > 0 && rect.h > 0) 
    {
		cmd = gs_gui_push_command(ctx, GS_GUI_COMMAND_RECT, sizeof(gs_gui_rectcommand_t));
		cmd->rect.rect = rect;
		cmd->rect.color = color;
	}
} 

GS_API_DECL void gs_gui_draw_box(gs_gui_context_t* ctx, gs_gui_rect_t rect, gs_color_t color) 
{
	gs_gui_draw_rect(ctx, gs_gui_rect(rect.x + 1, rect.y, rect.w - 2, 1), color);
	gs_gui_draw_rect(ctx, gs_gui_rect(rect.x + 1, rect.y + rect.h - 1, rect.w - 2, 1), color);
	gs_gui_draw_rect(ctx, gs_gui_rect(rect.x, rect.y, 1, rect.h), color);
	gs_gui_draw_rect(ctx, gs_gui_rect(rect.x + rect.w - 1, rect.y, 1, rect.h), color);
}

GS_API_DECL void gs_gui_draw_text(gs_gui_context_t* ctx, gs_asset_font_t* font, const char* str, int32_t len,
	gs_vec2 pos, gs_color_t color)
{
    // Set to default font
    if (!font)
    {
        font = &ctx->gsi.font_default; 
    } 

	gs_gui_command_t* cmd;
    gs_vec2 td = ctx->text_dimensions(font, str, -1);
	gs_gui_rect_t rect = gs_gui_rect(pos.x, pos.y, td.x, td.y);
	int32_t clipped = gs_gui_check_clip(ctx, rect);

	if (clipped == GS_GUI_CLIP_ALL ) 
    { 
        return; 
    }

	if (clipped == GS_GUI_CLIP_PART) 
    { 
        gs_gui_rect_t crect = gs_gui_get_clip_rect(ctx);
	    gs_gui_draw_box(ctx, crect, GS_COLOR_GREEN);
	    gs_gui_draw_box(ctx, rect, GS_COLOR_RED);
        gs_gui_set_clip(ctx, crect); 
    }

	/* add command */
	if (len < 0) 
    { 
        len = strlen(str); 
    }

	cmd = gs_gui_push_command(ctx, GS_GUI_COMMAND_TEXT, sizeof(gs_gui_textcommand_t) + len);
	memcpy(cmd->text.str, str, len);
	cmd->text.str[len] = '\0';
	cmd->text.pos = pos;
	cmd->text.color = color;
	cmd->text.font = font;

	if (clipped) 
    { 
        gs_gui_set_clip(ctx, gs_gui_unclipped_rect); 
    }
} 

GS_API_DECL void gs_gui_draw_icon(gs_gui_context_t* ctx, uint32_t id, gs_gui_rect_t rect, gs_color_t color) 
{
	gs_gui_command_t* cmd;

	/* do clip command if the rect isn't fully contained within the cliprect */
	int32_t clipped = gs_gui_check_clip(ctx, rect);
	if (clipped == GS_GUI_CLIP_ALL ) {return;}
	if (clipped == GS_GUI_CLIP_PART) {gs_gui_set_clip(ctx, gs_gui_get_clip_rect(ctx));}

	/* do icon command */
	cmd = gs_gui_push_command(ctx, GS_GUI_COMMAND_ICON, sizeof(gs_gui_iconcommand_t));
	cmd->icon.id = id;
	cmd->icon.rect = rect;
	cmd->icon.color = color;

	/* reset clipping if it was set */
	if (clipped) { gs_gui_set_clip(ctx, gs_gui_unclipped_rect); }
} 

/*============================================================================
** layout
**============================================================================*/
enum {
    GS_GUI_RELATIVE = 1,
    GS_GUI_ABSOLUTE = 2
}; 

GS_API_DECL void gs_gui_layout_begin_column(gs_gui_context_t* ctx) 
{
	gs_gui_push_layout(ctx, gs_gui_layout_next(ctx), gs_v2(0, 0));
} 

GS_API_DECL void gs_gui_layout_end_column(gs_gui_context_t* ctx) 
{
	gs_gui_layout_t *a, *b;
	b = gs_gui_get_layout(ctx);
	gs_gui_stack_pop(ctx->layout_stack);

	/* inherit position/next_row/max from child layout if they are greater */
	a = gs_gui_get_layout(ctx);
	a->position.x = gs_max(a->position.x, b->position.x + b->body.x - a->body.x);
	a->next_row = gs_max(a->next_row, b->next_row + b->body.y - a->body.y);
	a->max.x = gs_max(a->max.x, b->max.x);
	a->max.y = gs_max(a->max.y, b->max.y);
} 

GS_API_DECL void gs_gui_layout_row(gs_gui_context_t* ctx, int32_t items, const int32_t* widths, int32_t height) 
{
	gs_gui_layout_t* layout = gs_gui_get_layout(ctx);
	if (widths) 
    {
		gs_gui_expect(items <= GS_GUI_MAX_WIDTHS);
		memcpy(layout->widths, widths, items * sizeof(widths[0]));
	}
	layout->items = items;
	layout->position = gs_v2(layout->indent, layout->next_row);
	layout->size.y = height;
	layout->item_index = 0;
} 

GS_API_DECL void gs_gui_layout_width(gs_gui_context_t *ctx, int32_t width) 
{
	gs_gui_get_layout(ctx)->size.x = width;
} 

GS_API_DECL void gs_gui_layout_height(gs_gui_context_t *ctx, int32_t height) 
{
	gs_gui_get_layout(ctx)->size.y = height;
} 

GS_API_DECL void gs_gui_layout_set_next(gs_gui_context_t *ctx, gs_gui_rect_t r, int32_t relative) 
{
	gs_gui_layout_t *layout = gs_gui_get_layout(ctx);
	layout->next = r;
	layout->next_type = relative ? GS_GUI_RELATIVE : GS_GUI_ABSOLUTE;
} 

GS_API_DECL gs_gui_rect_t gs_gui_layout_next(gs_gui_context_t *ctx) 
{
	gs_gui_layout_t* layout = gs_gui_get_layout(ctx);
	gs_gui_style_t* style = ctx->style;
	gs_gui_rect_t res;

	if (layout->next_type) 
    {
		/* handle rect set by `gs_gui_layout_set_next` */
		int32_t type = layout->next_type;
		layout->next_type = 0;
		res = layout->next;
		if (type == GS_GUI_ABSOLUTE) 
        { 
            return (ctx->last_rect = res); 
        }

	} 
    else 
    {
		/* handle next row */
		if (layout->item_index == layout->items) 
        {
			gs_gui_layout_row(ctx, layout->items, NULL, layout->size.y);
		}

		/* position */
		res.x = layout->position.x;
		res.y = layout->position.y;

		/* size */
		res.w = layout->items > 0 ? layout->widths[layout->item_index] : layout->size.x;
		res.h = layout->size.y;

		if (res.w == 0) { res.w = style->size.x + style->padding * 2; }
		if (res.h == 0) { res.h = style->size.y + style->padding * 2; }
		if (res.w <	0) { res.w += layout->body.w - res.x + 1; }
		if (res.h <	0) { res.h += layout->body.h - res.y + 1; }

		layout->item_index++;
	}

	/* update position */
	layout->position.x += res.w + style->spacing;
	layout->next_row = gs_max(layout->next_row, res.y + res.h + style->spacing);

	/* apply body offset */
	res.x += layout->body.x;
	res.y += layout->body.y;

	/* update max position */
	layout->max.x = gs_max(layout->max.x, res.x + res.w);
	layout->max.y = gs_max(layout->max.y, res.y + res.h);

	return (ctx->last_rect = res);
} 

/*============================================================================
** controls
**============================================================================*/

static int32_t gs_gui_in_hover_root(gs_gui_context_t *ctx) 
{
	int32_t i = ctx->container_stack.idx;
	while (i--) 
    {
		if (ctx->container_stack.items[i] == ctx->hover_root) { return 1; }

		/* only root containers have their `head` field set; stop searching if we've
		** reached the current root container */
		if (ctx->container_stack.items[i]->head) { break; }
	}
	return 0;
} 

GS_API_DECL void gs_gui_draw_control_frame(gs_gui_context_t *ctx, gs_gui_id id, gs_gui_rect_t rect,
	int32_t colorid, int32_t opt)
{
	if (opt & GS_GUI_OPT_NOFRAME) { return; }
	colorid += (ctx->focus == id) ? 2 : (ctx->hover == id) ? 1 : 0;
	ctx->draw_frame(ctx, rect, colorid);
} 

GS_API_DECL void gs_gui_draw_control_text(gs_gui_context_t *ctx, const char *str, gs_gui_rect_t rect,
	int32_t colorid, int32_t opt)
{
	gs_vec2 pos;
	gs_asset_font_t* font = ctx->style->font; 
    gs_vec2 td = ctx->text_dimensions(font, str, -1);
	int32_t tw = (int32_t)td.x;
    int32_t th = (int32_t)td.y;

	gs_gui_push_clip_rect(ctx, rect);
	pos.y = rect.y + (rect.h - th) / 2;

	if (opt & GS_GUI_OPT_ALIGNCENTER) 
    {
		pos.x = rect.x + (rect.w - tw) / 2;
	} 
    else if (opt & GS_GUI_OPT_ALIGNRIGHT) 
    {
		pos.x = rect.x + rect.w - tw - ctx->style->padding;
	} 
    else 
    {
		pos.x = rect.x + ctx->style->padding;
	} 

	gs_gui_draw_text(ctx, font, str, -1, pos, ctx->style->colors[colorid]);
	gs_gui_pop_clip_rect(ctx);
} 

GS_API_DECL int32_t gs_gui_mouse_over(gs_gui_context_t *ctx, gs_gui_rect_t rect) 
{
	return gs_gui_rect_overlaps_vec2(rect, ctx->mouse_pos) &&
		gs_gui_rect_overlaps_vec2(gs_gui_get_clip_rect(ctx), ctx->mouse_pos) &&
		gs_gui_in_hover_root(ctx);
} 

GS_API_DECL void gs_gui_update_control(gs_gui_context_t *ctx, gs_gui_id id, gs_gui_rect_t rect, int32_t opt) 
{
	int32_t mouseover = gs_gui_mouse_over(ctx, rect);

	if (ctx->focus == id) { ctx->updated_focus = 1; }
	if (opt & GS_GUI_OPT_NOINTERACT) { return; }
	if (mouseover && !ctx->mouse_down) { ctx->hover = id; }

	if (ctx->focus == id) 
    {
		if (ctx->mouse_pressed && !mouseover) { gs_gui_set_focus(ctx, 0); }
		if (!ctx->mouse_down && ~opt & GS_GUI_OPT_HOLDFOCUS) { gs_gui_set_focus(ctx, 0); }
	}

	if (ctx->hover == id) 
    {
		if (ctx->mouse_pressed) 
        {
			gs_gui_set_focus(ctx, id);
		} 
        else if (!mouseover) 
        {
			ctx->hover = 0;
		}
	}
} 

GS_API_DECL void gs_gui_text(gs_gui_context_t *ctx, const char *text) 
{
	const char *start, *end, *p = text;
	int32_t width = -1;
	gs_asset_font_t* font = ctx->style->font;
	gs_color_t color = ctx->style->colors[GS_GUI_COLOR_TEXT];
    int32_t th = ctx->text_height(font, text, -1);
	gs_gui_layout_begin_column(ctx);
	gs_gui_layout_row(ctx, 1, &width, th);

	do 
    {
	    gs_gui_rect_t r = gs_gui_layout_next(ctx);
		int32_t w = 0;
		start = end = p;
		do 
        {
			const char* word = p;
			while (*p && *p != ' ' && *p != '\n') 
            { 
                p++; 
            }

			w += ctx->text_width(font, word, p - word);
			if (w > r.w && end != start) 
            { 
                break; 
            }

			w += ctx->text_width(font, p, 1);
			end = p++;

		} while (*end && *end != '\n');

		gs_gui_draw_text(ctx, font, start, end - start, gs_v2(r.x, r.y), color);
		p = end + 1;

	} while (*end);

	gs_gui_layout_end_column(ctx);
} 

GS_API_DECL void gs_gui_label(gs_gui_context_t *ctx, const char *text) 
{
	gs_gui_draw_control_text(ctx, text, gs_gui_layout_next(ctx), GS_GUI_COLOR_TEXT, 0);
} 

GS_API_DECL int32_t gs_gui_button_ex(gs_gui_context_t *ctx, const char *label, int32_t icon, int32_t opt) 
{
	int32_t res = 0;
	gs_gui_id id = label ? gs_gui_get_id(ctx, label, strlen(label))
									 : gs_gui_get_id(ctx, &icon, sizeof(icon));
	gs_gui_rect_t r = gs_gui_layout_next(ctx);
	gs_gui_update_control(ctx, id, r, opt);

	/* handle click */
	if (ctx->mouse_pressed == GS_GUI_MOUSE_LEFT && ctx->focus == id) 
    {
		res |= GS_GUI_RES_SUBMIT;
	}

	/* draw */
	gs_gui_draw_control_frame(ctx, id, r, GS_GUI_COLOR_BUTTON, opt);
	if (label) { gs_gui_draw_control_text(ctx, label, r, GS_GUI_COLOR_TEXT, opt); }
	if (icon) { gs_gui_draw_icon(ctx, icon, r, ctx->style->colors[GS_GUI_COLOR_TEXT]); }

	return res;
}

GS_API_DECL int32_t gs_gui_checkbox(gs_gui_context_t *ctx, const char *label, int32_t *state) 
{
	int32_t res = 0;
	gs_gui_id id = gs_gui_get_id(ctx, &state, sizeof(state));
	gs_gui_rect_t r = gs_gui_layout_next(ctx);
	gs_gui_rect_t box = gs_gui_rect(r.x, r.y, r.h, r.h);
	gs_gui_update_control(ctx, id, r, 0);

	/* handle click */
	if (ctx->mouse_pressed == GS_GUI_MOUSE_LEFT && ctx->focus == id) 
    {
		res |= GS_GUI_RES_CHANGE;
		*state = !*state;
	}

	/* draw */
	gs_gui_draw_control_frame(ctx, id, box, GS_GUI_COLOR_BASE, 0);
	if (*state) 
    {
		gs_gui_draw_icon(ctx, GS_GUI_ICON_CHECK, box, ctx->style->colors[GS_GUI_COLOR_TEXT]);
	}

	r = gs_gui_rect(r.x + box.w, r.y, r.w - box.w, r.h);
	gs_gui_draw_control_text(ctx, label, r, GS_GUI_COLOR_TEXT, 0);
	return res;
}

GS_API_DECL int32_t gs_gui_textbox_raw(gs_gui_context_t *ctx, char *buf, int32_t bufsz, gs_gui_id id, gs_gui_rect_t r,
	int32_t opt)
{
	int32_t res = 0;
	gs_gui_update_control(ctx, id, r, opt | GS_GUI_OPT_HOLDFOCUS);

	if (ctx->focus == id) 
    {
		/* handle text input */
		int32_t len = strlen(buf);
		int32_t n = gs_min(bufsz - len - 1, (int32_t) strlen(ctx->input_text)); 
		if (n > 0) 
        {
			memcpy(buf + len, ctx->input_text, n);
			len += n;
			buf[len] = '\0';
			res |= GS_GUI_RES_CHANGE;
		}

		/* handle backspace */
		if (ctx->key_pressed & GS_GUI_KEY_BACKSPACE && len > 0) 
        {
			/* skip utf-8 continuation bytes */
			while ((buf[--len] & 0xc0) == 0x80 && len > 0);
			buf[len] = '\0';
			res |= GS_GUI_RES_CHANGE;
		}

		/* handle return */
		if (ctx->key_pressed & GS_GUI_KEY_RETURN) 
        {
			gs_gui_set_focus(ctx, 0);
			res |= GS_GUI_RES_SUBMIT;
		}
	}

	/* draw */

    // Textbox bg 
	gs_gui_draw_control_frame(ctx, id, r, GS_GUI_COLOR_BASE, opt);

    // Text and carret
	if (ctx->focus == id) 
    {
		gs_color_t color = ctx->style->colors[GS_GUI_COLOR_TEXT];
		gs_asset_font_t* font = ctx->style->font; 
		int32_t textw = ctx->text_width(font, buf, -1);
		int32_t texth = ctx->text_height(font, buf, -1);
		int32_t ofx = r.w - ctx->style->padding - textw - 1;
		int32_t textx = r.x + gs_min(ofx, ctx->style->padding);
		int32_t texty = r.y + (r.h - texth) / 2;
		int32_t cary = r.y + (r.h - texth) / 2; 
		gs_gui_draw_box(ctx, gs_gui_rect(textx, texty, textw, texth), GS_COLOR_RED); 
		gs_gui_push_clip_rect(ctx, r); 

        // Draw text
		gs_gui_draw_text(ctx, font, buf, -1, gs_v2(textx, texty), color);
		gs_gui_draw_rect(ctx, gs_gui_rect(textx + textw + 1, cary, 1, texth), color); 

		gs_gui_pop_clip_rect(ctx);
	} 
    else 
    {
		gs_color_t color = ctx->style->colors[GS_GUI_COLOR_TEXT];
		gs_asset_font_t* font = ctx->style->font; 
		int32_t textw = ctx->text_width(font, buf, -1);
		int32_t texth = ctx->text_height(font, buf, -1);
		int32_t textx = r.x + ctx->style->padding;
		int32_t texty = r.y + (r.h - texth) / 2;
		gs_gui_push_clip_rect(ctx, r); 
		gs_gui_draw_text(ctx, font, buf, -1, gs_v2(textx, texty), color);
		gs_gui_pop_clip_rect(ctx);
	}

	return res;
}

static int32_t gs_gui_number_textbox(gs_gui_context_t *ctx, gs_gui_real *value, gs_gui_rect_t r, gs_gui_id id) 
{
	if (ctx->mouse_pressed == GS_GUI_MOUSE_LEFT && ctx->key_down & GS_GUI_KEY_SHIFT &&
			ctx->hover == id
	) 
    {
		ctx->number_edit = id;
		gs_snprintf(ctx->number_edit_buf, GS_GUI_MAX_FMT, GS_GUI_REAL_FMT, *value);
	}
	if (ctx->number_edit == id) 
    {
		int32_t res = gs_gui_textbox_raw(
			ctx, ctx->number_edit_buf, sizeof(ctx->number_edit_buf), id, r, 0);
		if (res & GS_GUI_RES_SUBMIT || ctx->focus != id) 
        {
			*value = strtod(ctx->number_edit_buf, NULL);
			ctx->number_edit = 0;
		} 
        else 
        {
			return 1;
		}
	}
	return 0;
} 

GS_API_DECL int32_t gs_gui_textbox_ex(gs_gui_context_t *ctx, char *buf, int32_t bufsz, int32_t opt) 
{
	gs_gui_id id = gs_gui_get_id(ctx, &buf, sizeof(buf));
	gs_gui_rect_t r = gs_gui_layout_next(ctx);
	return gs_gui_textbox_raw(ctx, buf, bufsz, id, r, opt);
} 

GS_API_DECL int32_t gs_gui_slider_ex(gs_gui_context_t *ctx, gs_gui_real *value, gs_gui_real low, gs_gui_real high,
	gs_gui_real step, const char *fmt, int32_t opt)
{
	char buf[GS_GUI_MAX_FMT + 1];
	gs_gui_rect_t thumb;
	int32_t x, w, res = 0;
	gs_gui_real last = *value, v = last;
	gs_gui_id id = gs_gui_get_id(ctx, &value, sizeof(value));
	gs_gui_rect_t base = gs_gui_layout_next(ctx);

	/* handle text input mode */
	if (gs_gui_number_textbox(ctx, &v, base, id)) { return res; }

	/* handle normal mode */
	gs_gui_update_control(ctx, id, base, opt);

	/* handle input */
	if (ctx->focus == id &&
			(ctx->mouse_down | ctx->mouse_pressed) == GS_GUI_MOUSE_LEFT)
	{
		v = low + (ctx->mouse_pos.x - base.x) * (high - low) / base.w;
		if (step) { v = (((v + step / 2) / step)) * step; }
	}

	/* clamp and store value, update res */
	*value = v = gs_clamp(v, low, high);
	if (last != v) { res |= GS_GUI_RES_CHANGE; }

	/* draw base */
	gs_gui_draw_control_frame(ctx, id, base, GS_GUI_COLOR_BASE, opt);

	/* draw thumb */
	w = ctx->style->thumb_size;
	x = (v - low) * (base.w - w) / (high - low);
	thumb = gs_gui_rect(base.x + x, base.y, w, base.h);
	gs_gui_draw_control_frame(ctx, id, thumb, GS_GUI_COLOR_BUTTON, opt);

	/* draw text	*/
	gs_snprintf(buf, GS_GUI_MAX_FMT, fmt, v);
	gs_gui_draw_control_text(ctx, buf, base, GS_GUI_COLOR_TEXT, opt);

	return res;
} 

GS_API_DECL int32_t gs_gui_number_ex(gs_gui_context_t *ctx, gs_gui_real *value, gs_gui_real step,
	const char *fmt, int32_t opt)
{
	char buf[GS_GUI_MAX_FMT + 1];
	int32_t res = 0;
	gs_gui_id id = gs_gui_get_id(ctx, &value, sizeof(value));
	gs_gui_rect_t base = gs_gui_layout_next(ctx);
	gs_gui_real last = *value;

	/* handle text input mode */
	if (gs_gui_number_textbox(ctx, value, base, id)) { return res; }

	/* handle normal mode */
	gs_gui_update_control(ctx, id, base, opt);

	/* handle input */
	if (ctx->focus == id && ctx->mouse_down == GS_GUI_MOUSE_LEFT) 
    {
		*value += ctx->mouse_delta.x * step;
	}

	/* set flag if value changed */
	if (*value != last) { res |= GS_GUI_RES_CHANGE; }

	/* draw base */
	gs_gui_draw_control_frame(ctx, id, base, GS_GUI_COLOR_BASE, opt);

	/* draw text	*/
	gs_snprintf(buf, GS_GUI_MAX_FMT, fmt, *value);
	gs_gui_draw_control_text(ctx, buf, base, GS_GUI_COLOR_TEXT, opt);

	return res;
} 

static int32_t gs_gui_header(gs_gui_context_t *ctx, const char *label, int32_t istreenode, int32_t opt) 
{
	gs_gui_rect_t r;
	int32_t active, expanded;
	gs_gui_id id = gs_gui_get_id(ctx, label, strlen(label));
	int32_t idx = gs_gui_pool_get(ctx, ctx->treenode_pool, GS_GUI_TREENODEPOOL_SIZE, id);
	int32_t width = -1;
	gs_gui_layout_row(ctx, 1, &width, 0);

	active = (idx >= 0);
	expanded = (opt & GS_GUI_OPT_EXPANDED) ? !active : active;
	r = gs_gui_layout_next(ctx);
	gs_gui_update_control(ctx, id, r, 0);

	/* handle click */
	active ^= (ctx->mouse_pressed == GS_GUI_MOUSE_LEFT && ctx->focus == id);

	/* update pool ref */
	if (idx >= 0) 
    {
		if (active) 
        { gs_gui_pool_update(ctx, ctx->treenode_pool, idx); 
        } 
		else 
        { 
            memset(&ctx->treenode_pool[idx], 0, sizeof(gs_gui_pool_item_t)); 
        }

	} 
    else if (active) 
    {
		gs_gui_pool_init(ctx, ctx->treenode_pool, GS_GUI_TREENODEPOOL_SIZE, id);
	}

	/* draw */
	if (istreenode) 
    {
		if (ctx->hover == id) 
        { 
            ctx->draw_frame(ctx, r, GS_GUI_COLOR_BUTTONHOVER); 
        } 
	} 
    else 
    {
		gs_gui_draw_control_frame(ctx, id, r, GS_GUI_COLOR_BUTTON, 0);
	}

	gs_gui_draw_icon(
		ctx, expanded ? GS_GUI_ICON_EXPANDED : GS_GUI_ICON_COLLAPSED,
		gs_gui_rect(r.x, r.y, r.h, r.h), ctx->style->colors[GS_GUI_COLOR_TEXT]);
	r.x += r.h - ctx->style->padding;
	r.w -= r.h - ctx->style->padding;
	gs_gui_draw_control_text(ctx, label, r, GS_GUI_COLOR_TEXT, 0);

	return expanded ? GS_GUI_RES_ACTIVE : 0;
} 

GS_API_DECL int32_t gs_gui_header_ex(gs_gui_context_t *ctx, const char *label, int32_t opt) 
{
	return gs_gui_header(ctx, label, 0, opt);
}

GS_API_DECL int32_t gs_gui_begin_treenode_ex(gs_gui_context_t *ctx, const char *label, int32_t opt) 
{
	int32_t res = gs_gui_header(ctx, label, 1, opt);
	if (res & GS_GUI_RES_ACTIVE) 
    {
		gs_gui_get_layout(ctx)->indent += ctx->style->indent;
		gs_gui_stack_push(ctx->id_stack, ctx->last_id);
	}

	return res;
} 

GS_API_DECL void gs_gui_end_treenode(gs_gui_context_t *ctx) 
{
	gs_gui_get_layout(ctx)->indent -= ctx->style->indent;
	gs_gui_pop_id(ctx);
} 

#define gs_gui_scrollbar(ctx, cnt, b, cs, x, y, w, h)									    \
	do {																				    \
		/* only add scrollbar if content size is larger than body */						\
		int32_t maxscroll = cs.y - b->h;													\
																						    \
		if (maxscroll > 0 && b->h > 0) {													\
			gs_gui_rect_t base, thumb;														\
			gs_gui_id id = gs_gui_get_id(ctx, "!scrollbar" #y, 11);							\
																							\
			/* get sizing / positioning */													\
			base = *b;																	    \
			base.x = b->x + b->w;															\
			base.w = ctx->style->scrollbar_size;											\
																							\
			/* handle input */																\
			gs_gui_update_control(ctx, id, base, 0);										\
			if (ctx->focus == id && ctx->mouse_down == GS_GUI_MOUSE_LEFT) {					\
				cnt->scroll.y += ctx->mouse_delta.y * cs.y / base.h;					    \
			}																				\
			/* clamp scroll to limits */													\
			cnt->scroll.y = gs_clamp(cnt->scroll.y, 0, maxscroll);					        \
																							\
			/* draw base and thumb */														\
			ctx->draw_frame(ctx, base, GS_GUI_COLOR_SCROLLBASE);							\
			thumb = base;																    \
			thumb.h = gs_max(ctx->style->thumb_size, base.h * b->h / cs.y);			        \
			thumb.y += cnt->scroll.y * (base.h - thumb.h) / maxscroll;						\
			ctx->draw_frame(ctx, thumb, GS_GUI_COLOR_SCROLLTHUMB);							\
																							\
			/* set this as the scroll_target (will get scrolled on mousewheel) */           \
			/* if the mouse is over it */													\
			if (gs_gui_mouse_over(ctx, *b)) { ctx->scroll_target = cnt; }				    \
		} else {																			\
			cnt->scroll.y = 0;																\
		}																					\
	} while (0) 

static void gs_gui_scrollbars(gs_gui_context_t *ctx, gs_gui_container_t *cnt, gs_gui_rect_t *body) 
{
	int32_t sz = ctx->style->scrollbar_size;
	gs_vec2 cs = cnt->content_size;
	cs.x += ctx->style->padding * 2;
	cs.y += ctx->style->padding * 2;
	gs_gui_push_clip_rect(ctx, *body);

	/* resize body to make room for scrollbars */
	if (cs.y > cnt->body.h) { body->w -= sz; }
	if (cs.x > cnt->body.w) { body->h -= sz; }

	/* to create a horizontal or vertical scrollbar almost-identical code is
	** used; only the references to `x|y` `w|h` need to be switched */
	gs_gui_scrollbar(ctx, cnt, body, cs, x, y, w, h);
	gs_gui_scrollbar(ctx, cnt, body, cs, y, x, h, w);
	gs_gui_pop_clip_rect(ctx);
}

static void gs_gui_push_container_body(gs_gui_context_t *ctx, gs_gui_container_t *cnt, gs_gui_rect_t body, int32_t opt) 
{
	if (~opt & GS_GUI_OPT_NOSCROLL) {gs_gui_scrollbars(ctx, cnt, &body);}
	gs_gui_push_layout(ctx, gs_gui_expand_rect(body, -ctx->style->padding), cnt->scroll);
	cnt->body = body;
} 

static void gs_gui_begin_root_container(gs_gui_context_t *ctx, gs_gui_container_t *cnt) 
{
	gs_gui_stack_push(ctx->container_stack, cnt);

	/* push container to roots list and push head command */
	gs_gui_stack_push(ctx->root_list, cnt);
	cnt->head = gs_gui_push_jump(ctx, NULL);

	/* set as hover root if the mouse is overlapping this container and it has a
	** higher zindex than the current hover root */
	if (gs_gui_rect_overlaps_vec2(cnt->rect, ctx->mouse_pos) &&
			(!ctx->next_hover_root || cnt->zindex > ctx->next_hover_root->zindex)
	) 
    {
		ctx->next_hover_root = cnt;
	}

	/* clipping is reset here in case a root-container is made within
	** another root-containers's begin/end block; this prevents the inner
	** root-container being clipped to the outer */
	gs_gui_stack_push(ctx->clip_stack, gs_gui_unclipped_rect);
}

static void gs_gui_end_root_container(gs_gui_context_t *ctx) 
{
	/* push tail 'goto' jump command and set head 'skip' command. the final steps
	** on initing these are done in gs_gui_end() */
	gs_gui_container_t *cnt = gs_gui_get_current_container(ctx);
	cnt->tail = gs_gui_push_jump(ctx, NULL);
	cnt->head->jump.dst = ctx->command_list.items + ctx->command_list.idx;

	/* pop base clip rect and container */
	gs_gui_pop_clip_rect(ctx);
	gs_gui_pop_container(ctx);
} 

int32_t gs_gui_begin_window_ex(gs_gui_context_t* ctx, const char* title, gs_gui_rect_t rect, int32_t opt) 
{
	gs_gui_rect_t body;
	gs_gui_id id = gs_gui_get_id(ctx, title, strlen(title)); 
	gs_gui_container_t* cnt = gs_gui_get_container(ctx, id, opt);

	if (!cnt || !cnt->open) 
    {
        return 0;
    }

	gs_gui_stack_push(ctx->id_stack, id); 

	if (cnt->rect.w == 0.f) {cnt->rect = rect;}
	gs_gui_begin_root_container(ctx, cnt);
	rect = body = cnt->rect; 

    // To get rid of floating, calculate delta move FIRST 
    if (~opt & GS_GUI_OPT_NOTITLE) 
    {
        // Cache rect
		gs_gui_rect_t tr = cnt->rect;
		tr.h = ctx->style->title_height;
        gs_gui_id id = gs_gui_get_id(ctx, "!title", 6);
        gs_gui_update_control(ctx, id, tr, opt);

        if (id == ctx->focus && ctx->mouse_down == GS_GUI_MOUSE_LEFT) 
        {
            cnt->rect.x += ctx->mouse_delta.x;
            cnt->rect.y += ctx->mouse_delta.y; 
            body = cnt->rect;
        }
        body.y += tr.h;
        body.h -= tr.h;
    }

	/* draw frame */
	if (~opt & GS_GUI_OPT_NOFRAME) 
    {
		ctx->draw_frame(ctx, cnt->rect, GS_GUI_COLOR_WINDOWBG);
	}

	/* do title bar */
	if (~opt & GS_GUI_OPT_NOTITLE) 
    {
		gs_gui_rect_t tr = cnt->rect;
		tr.h = ctx->style->title_height;
		ctx->draw_frame(ctx, tr, GS_GUI_COLOR_TITLEBG);

		/* do title text */
		if (~opt & GS_GUI_OPT_NOTITLE) 
        {
			gs_gui_draw_control_text(ctx, title, tr, GS_GUI_COLOR_TITLETEXT, opt); 
		}

		/* do `close` button */
		if (~opt & GS_GUI_OPT_NOCLOSE) 
        {
			gs_gui_id id = gs_gui_get_id(ctx, "!close", 6);
			gs_gui_rect_t r = gs_gui_rect(tr.x + tr.w - tr.h, tr.y, tr.h, tr.h);
			tr.w -= r.w;
			gs_gui_draw_icon(ctx, GS_GUI_ICON_CLOSE, r, ctx->style->colors[GS_GUI_COLOR_TITLETEXT]);
			gs_gui_update_control(ctx, id, r, opt);
			if (ctx->mouse_pressed == GS_GUI_MOUSE_LEFT && id == ctx->focus) 
            {
				cnt->open = 0;
			}
		}
	}

	/* do `resize` handle */
	if (~opt & GS_GUI_OPT_NORESIZE) 
    {
		int32_t sz = ctx->style->title_height;
		gs_gui_id id = gs_gui_get_id(ctx, "!resize", 7);
		gs_gui_rect_t r = gs_gui_rect(cnt->rect.x + cnt->rect.w - sz, cnt->rect.y + cnt->rect.h - sz, sz, sz);
		gs_gui_update_control(ctx, id, r, opt);
		if (id == ctx->focus && ctx->mouse_down == GS_GUI_MOUSE_LEFT) 
        {
			cnt->rect.w = gs_max(96, cnt->rect.w + ctx->mouse_delta.x);
			cnt->rect.h = gs_max(64, cnt->rect.h + ctx->mouse_delta.y);
		}
	}

	/* resize to content size */
	if (opt & GS_GUI_OPT_AUTOSIZE) 
    {
		gs_gui_rect_t r = gs_gui_get_layout(ctx)->body;
		cnt->rect.w = cnt->content_size.x + (cnt->rect.w - r.w);
		cnt->rect.h = cnt->content_size.y + (cnt->rect.h - r.h);
	} 

	gs_gui_push_container_body(ctx, cnt, body, opt);

	/* close if this is a popup window and elsewhere was clicked */
	if (opt & GS_GUI_OPT_POPUP && ctx->mouse_pressed && ctx->hover_root != cnt) 
    {
		cnt->open = 0;
	}

	gs_gui_push_clip_rect(ctx, cnt->body);
	return GS_GUI_RES_ACTIVE;
} 

GS_API_DECL void gs_gui_end_window(gs_gui_context_t *ctx) 
{
	gs_gui_pop_clip_rect(ctx);
	gs_gui_end_root_container(ctx);
} 

GS_API_DECL void gs_gui_open_popup(gs_gui_context_t *ctx, const char *name) 
{
	gs_gui_container_t *cnt = gs_gui_gs_gui_get_container(ctx, name);

	// Set as hover root so popup isn't closed in begin_window_ex()
	ctx->hover_root = ctx->next_hover_root = cnt;

	// position at mouse cursor, open and bring-to-front
	cnt->rect = gs_gui_rect(ctx->mouse_pos.x, ctx->mouse_pos.y, 1, 1);
	cnt->open = 1;
	gs_gui_bring_to_front(ctx, cnt);
} 

GS_API_DECL int32_t gs_gui_begin_popup(gs_gui_context_t *ctx, const char *name) 
{
	int32_t opt = 
        GS_GUI_OPT_POPUP | GS_GUI_OPT_AUTOSIZE | 
        GS_GUI_OPT_NORESIZE | GS_GUI_OPT_NOSCROLL | 
        GS_GUI_OPT_NOTITLE | GS_GUI_OPT_CLOSED;

	return gs_gui_begin_window_ex(ctx, name, gs_gui_rect(0, 0, 0, 0), opt);
} 

GS_API_DECL void gs_gui_end_popup(gs_gui_context_t *ctx) 
{
	gs_gui_end_window(ctx);
} 

GS_API_DECL void gs_gui_begin_panel_ex(gs_gui_context_t *ctx, const char *name, int32_t opt) 
{
	gs_gui_container_t *cnt;
	gs_gui_push_id(ctx, name, strlen(name));
	cnt = gs_gui_get_container(ctx, ctx->last_id, opt);
	cnt->rect = gs_gui_layout_next(ctx);
	
    if (~opt & GS_GUI_OPT_NOFRAME) 
    {
		ctx->draw_frame(ctx, cnt->rect, GS_GUI_COLOR_PANELBG);
	}

	gs_gui_stack_push(ctx->container_stack, cnt);
	gs_gui_push_container_body(ctx, cnt, cnt->rect, opt);
	gs_gui_push_clip_rect(ctx, cnt->body);
} 

GS_API_DECL void gs_gui_end_panel(gs_gui_context_t *ctx) 
{
	gs_gui_pop_clip_rect(ctx);
	gs_gui_pop_container(ctx);
}

#endif // GS_GUI_IMPL 
#endif // GS_GUI_H














