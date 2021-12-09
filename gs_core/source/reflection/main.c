/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine : Reflection Generator
    * File: main.c
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

#define GS_NO_HIJACK_MAIN
#define GS_IMPL
#include <gs/gs.h>

#define GS_META_IMPL
#include <gs/util/gs_meta.h>

#define META_STR_MAX 1024 

#define FUNC_DECL(NAME)\
    typedef struct NAME\
    {\
        char func[META_STR_MAX * 4];\
        char params[META_STR_MAX];\
    } NAME;

FUNC_DECL(ctor_t);
FUNC_DECL(dtor_t);
FUNC_DECL(serialize_t);
FUNC_DECL(deserialize_t); 
FUNC_DECL(on_create_t); 
FUNC_DECL(on_start_t); 
FUNC_DECL(on_stop_t); 
FUNC_DECL(on_update_t); 
FUNC_DECL(on_destroy_t); 

typedef struct vtable_func_t
{
    char name[META_STR_MAX];
    char func_ptr[META_STR_MAX];
} vtable_func_t;

typedef struct vtable_t
{
    gs_dyn_array(vtable_func_t) funcs;
} vtable_t;

typedef struct meta_enum_val_t
{
	char name[META_STR_MAX];
} meta_enum_val_t;

typedef struct meta_enum_t
{
	char name[META_STR_MAX];
	gs_dyn_array(meta_enum_val_t) values;
} meta_enum_t;

typedef struct meta_prop_t 
{
	char name[META_STR_MAX];
	char type[META_STR_MAX];
	bool is_const_ptr;
	uint32_t pointer_count;	
} meta_prop_t;

typedef struct meta_class_t
{
	char name[META_STR_MAX];
	char base[META_STR_MAX];
	gs_dyn_array(meta_prop_t) properties;
    vtable_t vtable;
    ctor_t ctor; 
    dtor_t dtor;
    serialize_t serialize;
    deserialize_t deserialize;
    on_create_t on_create;
    on_start_t on_start;
    on_stop_t on_stop;
    on_update_t on_update;
    on_destroy_t on_destroy;
} meta_class_t;

typedef struct reflection_data_t
{
	gs_hash_table(uint64_t, meta_class_t) classes;
	gs_hash_table(uint64_t, meta_enum_t) enums;
	gs_hash_table(uint64_t, const char*) type2info;
} reflection_data_t;

void reflection_data_init(reflection_data_t* refl)
{
	gs_hash_table_insert(refl->type2info, gs_hash_str64("uint8_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U8));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("u8"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U8));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("int8_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S8));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("s8"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S8));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("i8"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S8));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("uint16_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U16));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("u16"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U16));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("int16_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S16));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("i16"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S16));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("s16"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S16));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("uint32_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("u32"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("int32_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("i32"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("s32"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("uint64_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("u64"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_U64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("int64_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("s64"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("i64"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_S64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("float"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_F32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("f32"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_F32));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("double"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_F64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("f64"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_F64));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_vec2"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC2));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("v2"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC2));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_vec3"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC3));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("v3"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC3));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_vec4"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC4));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("v4"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VEC4));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_mat4"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_MAT4));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("mat4"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_MAT4));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_quat"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_QUAT));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("quat"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_QUAT));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_vqs"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VQS));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("vqs"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_VQS));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("gs_uuid_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_UUID));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("uuid"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_UUID));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("size_t"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_SIZE_T));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("char"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_STR));
	gs_hash_table_insert(refl->type2info, gs_hash_str64("void"), gs_to_str(GS_META_PROPERTY_TYPE_INFO_OBJ));
}

bool prop_is_enum(reflection_data_t* refl, const char* type)
{
	return (gs_hash_table_exists(refl->enums, gs_hash_str64(type)));
}

const char* prop_type_to_type_info(reflection_data_t* refl, const char* type)
{
	uint64_t hash = gs_hash_str64(type);
	if (gs_hash_table_exists(refl->type2info, hash))
	{
		return gs_hash_table_get(refl->type2info, hash);
	}

	return "GS_META_PROPERTY_TYPE_INFO_OBJ";
}

void parse_struct_field(reflection_data_t* refl, meta_class_t* c, gs_lexer_t* lex)
{
	gs_token_t t = lex->current_token;
	
	// Parse 'BASE' tag
	if (gs_token_compare_text(&t, "base"))
	{
		// Get opening paren
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false); 
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) gs_assert(false);
		t = lex->current_token;
		
		// Now we have the base class
		memcpy(c->base, t.text, t.len);

		// Move to the semicolon
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_RPAREN)) gs_assert(false);
	}
    // Ctor
    else if (gs_token_compare_text(&t, "ctor"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);
        
        // Continue until right paren is found to exit
        do
        {
            t = lex->next_token(lex); 
            switch (t.type)
            {
                case GS_TOKEN_IDENTIFIER:
                {
                    // Parameters
                    if (gs_token_compare_text(&t, "params")) 
                    { 
		                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) 
                        {
                            gs_println("params failed!");
                            gs_assert(false);
                        }
                        
                        // Continue until right paren is found to close
                        uint32_t pc = 1; 
                        gs_token_t _c = lex->next_token(lex);
                        do
                        { 
                            t = lex->next_token(lex); 
                            switch (t.type)
                            {
                                default: break;
                                case GS_TOKEN_LPAREN: pc++; break;
                                case GS_TOKEN_RPAREN: pc--;
                            } 
                        } while (pc);

                        // Copy text now for params
                        const size_t len = t.text - _c.text;
                        gs_assert(len < META_STR_MAX);
                        memcpy(c->ctor.params, _c.text, len); 

                        // Get next token afterwards to move forward 
                        t = lex->next_token(lex);
                    }

                    // Function
                    else if (gs_token_compare_text(&t, "func"))
                    { 
		                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) 
                        { 
                            gs_println("func failed!");
                            gs_assert(false);
                        }

                        // Continue until right paren is found to close
                        uint32_t pc = 1; 
                        gs_token_t _c = lex->next_token(lex);
                        do
                        { 
                            t = lex->next_token(lex); 
                            switch (t.type)
                            {
                                default: break;
                                case GS_TOKEN_LPAREN: pc++; break;
                                case GS_TOKEN_RPAREN: pc--;
                            } 
                        } while (pc);

                        const size_t len = t.text - _c.text;
                        gs_assert(len < META_STR_MAX);
                        memcpy(c->ctor.func, _c.text, len); 

                        // Get next token afterwards to move forward
                        t = lex->next_token(lex);
                    }
                } break; 
            }
        } while (t.type != GS_TOKEN_RPAREN);
    }
    // Dtor
    else if (gs_token_compare_text(&t, "dtor"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->dtor.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // Serialize
    else if (gs_token_compare_text(&t, "serialize"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->serialize.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    } 
    // Deserialize
    else if (gs_token_compare_text(&t, "deserialize"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->deserialize.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // On Create
    else if (gs_token_compare_text(&t, "on_create"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->on_create.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // On Start
    else if (gs_token_compare_text(&t, "on_start"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->on_start.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // On Stop
    else if (gs_token_compare_text(&t, "on_stop"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->on_stop.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // On Update
    else if (gs_token_compare_text(&t, "on_update"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->on_update.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // On Destroy
    else if (gs_token_compare_text(&t, "on_destroy"))
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Continue until right paren is found to close
        uint32_t pc = 1; 
        gs_token_t _c = lex->next_token(lex);
        do
        { 
            t = lex->next_token(lex); 
            switch (t.type)
            {
                default: break;
                case GS_TOKEN_LPAREN: pc++; break;
                case GS_TOKEN_RPAREN: pc--;
            } 
        } while (pc);

        // Copy text now for params
        const size_t len = t.text - _c.text;
        gs_assert(len < META_STR_MAX);
        memcpy(c->on_destroy.func, _c.text, len); 

        // Get next token afterwards to move forward 
        t = lex->next_token(lex);
    }
    // VTable
    else if (gs_token_compare_text(&t, "vtable")) 
    {
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LPAREN)) gs_assert(false);

        // Just copy everything in vtable description for now (not individual functions)
        if (gs_lexer_peek(lex).type != GS_TOKEN_RPAREN) 
        {
            vtable_func_t f = {0};
            gs_token_t cur = lex->next_token(lex);
            t = cur;
            bool expect_fp = false;
            while (t.type != GS_TOKEN_RPAREN)
            {
                t = lex->next_token(lex); 
                switch (t.type)
                {
                    case GS_TOKEN_IDENTIFIER: 
                    {
                        if (expect_fp)
                        { 
                            memcpy(f.func_ptr, t.text, t.len); 
                            f.func_ptr[t.len] = '\0';
                            gs_dyn_array_push(c->vtable.funcs, f);
                        }
                        else
                        {
                            memcpy(f.name, t.text, t.len); 
                            f.name[t.len] = '\0';
                        }
                        expect_fp = !expect_fp;
                    } break;

                    case GS_TOKEN_EQUAL: 
                    {
                    } break; 
                } 
            } 
        } 
    }
	// Otherwise, it's a field
    else if (gs_token_compare_text(&t, "field")) 
	{
		meta_prop_t p = {0};
		bool set_type = false;

        // Skip to end of field param
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_RPAREN)) gs_assert(false);
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) gs_assert(false); 

		// Need to deal with any qualifier shit 
		if (gs_token_compare_text(&t, "const"))
		{
			p.is_const_ptr = true;
			if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) gs_assert(false);
		} 

		// Get next field, require identifier for field type
		t = lex->current_token;
		memcpy(p.type, t.text, t.len);

		// Do remainder of field (account for asterisks)
		t = lex->next_token(lex);
		while (t.type != GS_TOKEN_IDENTIFIER)
		{
			t = lex->next_token(lex);
			switch (t.type)
			{
				case GS_TOKEN_ASTERISK:
				{
					p.pointer_count++;
				} break;
			}
		}

		// Require identifier for field name
		t = lex->current_token;
		memcpy(p.name, t.text, t.len);

		// Require semi colon
		if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_SEMI_COLON)) gs_assert(false);

		// Add to class properties
		gs_dyn_array_push(c->properties, p);
	}
    else
    {
		// Move to the semicolon
		gs_lexer_find_next_token_type(lex, GS_TOKEN_SEMI_COLON);
    }
}

void parse_struct(reflection_data_t* refl, gs_lexer_t* lex)
{
	// Store current token for lexer
	gs_token_t t = lex->current_token;
	meta_class_t cls = {0};

	// Find opening brace (if identifier found, store name)
	while (lex->can_lex(lex) && t.type != GS_TOKEN_LBRACE)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			case GS_TOKEN_IDENTIFIER:
			{
				memcpy(cls.name, t.text, t.len);
			} break;
		}
	}

	// Parse to end of block
	while (lex->can_lex(lex) && t.type != GS_TOKEN_RBRACE)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			// Parse all fields
			case GS_TOKEN_IDENTIFIER: 
			{
				parse_struct_field(refl, &cls, lex);
			} break;
		}
	}

	// Parse to semi colon (if identifier found, store name)
	while (lex->can_lex(lex) && t.type != GS_TOKEN_SEMI_COLON)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			case GS_TOKEN_IDENTIFIER:
			{
				memcpy(cls.name, t.text, t.len);
			} break;
		}
	}

	// Add to reflection data
	gs_hash_table_insert(refl->classes, gs_hash_str64(cls.name), cls);
}

void parse_enum(reflection_data_t* refl, gs_lexer_t* lex)
{
	// Store current token
	gs_token_t t = lex->current_token;
	meta_enum_t e = {0};

	// Find opening brace (if identifier found, store name)
	while (lex->can_lex(lex) && t.type != GS_TOKEN_LBRACE)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			case GS_TOKEN_IDENTIFIER:
			{
				memcpy(e.name, t.text, t.len);
			} break;
			default: break;
		}
	}

	// While identifiers are available, print them (these are enum vals), stop at closing brace
	while (lex->can_lex(lex) && t.type != GS_TOKEN_RBRACE)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			case GS_TOKEN_IDENTIFIER:
		  	{
				// Add enum val
				meta_enum_val_t v = {0};
				memcpy(v.name, t.text, t.len);
				gs_dyn_array_push(e.values, v);
		  	} break;
			case GS_TOKEN_EQUAL:
			{
				// Need to skip through values, like 0x00
				gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER);
			} break;
			default: break;
		}
	}

	// Find semi colon
	while (lex->can_lex(lex) && t.type != GS_TOKEN_SEMI_COLON)
	{
		t = lex->next_token(lex);
		switch (t.type)
		{
			case GS_TOKEN_IDENTIFIER:
			{
				memcpy(e.name, t.text, t.len);
			} break;
		}
	}

	// Add into reflection data
	gs_hash_table_insert(refl->enums, gs_hash_str64(e.name), e);
}

void parse_file(reflection_data_t* refl, const char* path)
{
	gs_println("generating reflection: %s", path);

    /*
    if (gs_string_compare_equal(path, "../../gs_core//source/gs_gui.h"))
	{
		return;
	}
    */

	char* contents = gs_platform_read_file_contents(path, "r", NULL);
	if (contents)
	{
		gs_lexer_t lex = gs_lexer_c_ctor(contents);
		while (lex.can_lex(&lex))
		{
			gs_token_t token = lex.next_token(&lex);
			switch (token.type)
			{
				case GS_TOKEN_IDENTIFIER:
				{
                    if (gs_token_compare_text(&token, "GS_REFL_IGNORE_FILE"))
                    {
                        goto lex_end;
                    }
                    else if (gs_token_compare_text(&token, "introspect"))
					{
						// Move to ending parens for introspect tag (can parse tags here)
						gs_lexer_find_next_token_type(&lex, GS_TOKEN_RPAREN);

						// Now to determine if parsing enum or structure
						gs_lexer_find_next_token_type(&lex, GS_TOKEN_IDENTIFIER);

						// If typedefed
						if (gs_token_compare_text(&lex.current_token, "typedef"))
						{
							// Advance to next after typedef
							gs_lexer_find_next_token_type(&lex, GS_TOKEN_IDENTIFIER);
						}

						// Struct
						if (gs_token_compare_text(&lex.current_token, "struct"))
						{
							gs_token_t* t = &lex.current_token;
							parse_struct(refl, &lex);
						}
						// Enum
						else if (gs_token_compare_text(&lex.current_token, "enum"))
						{
							gs_token_t* t = &lex.current_token;
							parse_enum(refl, &lex);
						}
					}
				} break;
			}
		}
    lex_end:
		gs_free(contents);
	}
}

void write_reflection_file(reflection_data_t* refl, const char* dir, const char* namespace)
{
	// Path to write to
	gs_snprintfc(PATH, META_STR_MAX, "%s/%s_generated.h", dir, namespace);

	// Open file, then dump meta information
	FILE* fp = fopen(PATH, "w");
	if (!fp) 
	{
		return;
	}

	// Write out header information
	gs_fprintln(fp, "#ifndef %s_GENERATED_H", namespace);	
	gs_fprintln(fp, "#define %s_GENERATED_H\n", namespace);	

	// Write out warning information
	gs_fprintln(fp, "/*");	
	gs_fprintln(fp, " * This file has been generated. All modifications will be lost.");	
	gs_fprintln(fp, "*/");	

	// Formatting
	gs_fprintln(fp, "");	

	gs_fprintln(fp, "// ==== Main API === //");	
	
	// Functions API
	gs_fprintln(fp, "GS_API_DECL void %s_meta_register_generated(gs_meta_registry_t* meta);", namespace);	

    // Formatting
	gs_fprintln(fp, "");	

	gs_fprintln(fp, "// ==== Objects API === //\n");	

    if (!refl->classes)
    {
        goto interface_end; 
    }    

    // Generated Functions API 
    for 
    (
        gs_hash_table_iter it = gs_hash_table_iter_new(refl->classes);
        gs_hash_table_iter_valid(refl->classes, it);
        gs_hash_table_iter_advance(refl->classes, it)
    )
    {

        meta_class_t* c = gs_hash_table_iter_getp(refl->classes, it);

        const char* name = c->name;
        const char* base = c->base;
        uint32_t prop_cnt = gs_dyn_array_size(c->properties);

        gs_fprintln(fp, "// == %s API == //", name);	

        // Format
        gs_fprintln(fp, "");

        // Forward decl
        gs_fprintln(fp, "struct %s;", name);	

        // Class name hashed id
        const uint64_t id = gs_hash_str64(name);

        // Defines
        {
            // Ctor
            const char* params =  c->ctor.params;
            gs_fprintln(fp, "#define %s_ctor obj_ctor_%zu", name, id);	

            // New
            gs_fprintln(fp, "#define %s_new obj_new_%zu", name, id);	

            // Dtor
            gs_fprintln(fp, "#define %s_dtor obj_dtor_%zu", name, id);	

            // Serialize
            gs_fprintln(fp, "#define %s_serialize obj_serialize_%zu", name, id);	

            // Deserialize
            gs_fprintln(fp, "#define %s_deserialize obj_deserialize_%zu", name, id);	

            // On Create
            gs_fprintln(fp, "#define %s_on_create obj_on_create_%zu", name, id);	

            // On Start
            gs_fprintln(fp, "#define %s_on_start obj_on_start_%zu", name, id);	

            // On Stop
            gs_fprintln(fp, "#define %s_on_stop obj_on_stop_%zu", name, id);	

            // On Update
            gs_fprintln(fp, "#define %s_on_update obj_on_update_%zu", name, id);	

            // On Destroy
            gs_fprintln(fp, "#define %s_on_destroy obj_on_destroy_%zu", name, id);	
        }
        
        // Format
        gs_fprintln(fp, "");

        // Functions
        {
            // Ctor
            const char* params =  c->ctor.params;
            gs_fprintln(fp, "GS_API_DECL struct %s obj_ctor_%zu(%s);", name, id, params);	

            // New
            gs_fprintln(fp, "GS_API_DECL gs_object_t* obj_new_%zu(%s);", id, params);	

            // Dtor
            gs_fprintln(fp, "GS_API_DECL void obj_dtor_%zu(struct gs_object_t* obj);", id);	

            // Serialize
            gs_fprintln(fp, "GS_API_DECL gs_result obj_serialize_%zu(gs_byte_buffer_t* buffer, const gs_object_t* in);", id);	

            // Deserialize
            gs_fprintln(fp, "GS_API_DECL gs_result obj_deserialize_%zu(gs_byte_buffer_t* buffer, gs_object_t* out);", id);	

            // On Create
            gs_fprintln(fp, "GS_API_DECL void obj_on_create_%zu(gs_object_t* in);", id);	

            // On Start
            gs_fprintln(fp, "GS_API_DECL void obj_on_start_%zu(gs_object_t* in);", id);	

            // On Stop
            gs_fprintln(fp, "GS_API_DECL void obj_on_stop_%zu(gs_object_t* in);", id);	

            // On Update
            gs_fprintln(fp, "GS_API_DECL void obj_on_update_%zu(gs_object_t* in);", id);	

            // On Destroy
            gs_fprintln(fp, "GS_API_DECL void obj_on_destroy_%zu(gs_object_t* in);", id);	
        } 


        // Formatting
        gs_fprintln(fp, "");	
    }

interface_end:

	gs_fprintln(fp, "#endif // %s_GENERATED_H", namespace);	

	// Close the file
	fclose(fp);

implementation_begin:

	// Path to write to
	gs_snprintfc(FPATH, META_STR_MAX, "%s/%s_generated.c", dir, namespace);


	// Open file, then dump meta information
	fp = fopen(FPATH, "w");
	if (!fp) 
	{
		return;
	}

	// Implementation
	gs_fprintln(fp, "\n//============[ Implementation ]==============//\n");	

	// Write out warning information
	gs_fprintln(fp, "/*");	
	gs_fprintln(fp, " * This file has been generated. All modifications will be lost.");	
	gs_fprintln(fp, "*/");	
	gs_fprintln(fp, "");	

	// Register meta information function implementation
	gs_fprintln(fp, "GS_API_DECL void %s_meta_register_generated(gs_meta_registry_t* meta)", namespace);	
	gs_fprintln(fp, "{");	
	{
		// Register enums
		gs_fprintln(fp, "\t// == [ enums ] == \n");	

        if (refl->enums)
        {
            for
            (
                gs_hash_table_iter it = gs_hash_table_iter_new(refl->enums);
                gs_hash_table_iter_valid(refl->enums, it);
                gs_hash_table_iter_advance(refl->enums, it)
            )
            {
                meta_enum_t* e = gs_hash_table_iter_getp(refl->enums, it);

                const char* name = e->name;
                uint32_t val_cnt = gs_dyn_array_size(e->values);

                // Write out name as comment
                gs_fprintln(fp, "\t// %s", name);	
                gs_fprintln(fp, "\tgs_meta_enum_register(meta, (&(gs_meta_enum_decl_t) {");	
                {
                    gs_fprintln(fp, "\t\t.values = (gs_meta_enum_value_t[]) {");	
                    {
                        gs_for_range_i(val_cnt)
                        { 
                            const meta_enum_val_t* v = &e->values[i];
                            gs_fprintf(fp, "\t\t\t(gs_meta_enum_value_t){.name = gs_to_str(%s)}", v->name);	
                            if (i < val_cnt - 1)
                            {
                                gs_fprintf(fp, ",");	
                            }
                            gs_fprintf(fp, "\n");
                        }
                    }
                    gs_fprintln(fp, "\t\t},");	
                    gs_fprintln(fp, "\t\t.size = %zu * sizeof(gs_meta_enum_value_t),", val_cnt);	
                    gs_fprintln(fp, "\t\t.name = gs_to_str(%s)", name);	
                }
                gs_fprintln(fp, "\t}));");	
            }
        }

		// Formatting
		gs_fprintln(fp, "");	

		// Register classes
		gs_fprintln(fp, "\t// == [ classes ] == \n");	

        if (!refl->classes)
        {
            goto register_implementation_end; 
        }

		for 
		(
            gs_hash_table_iter it = gs_hash_table_iter_new(refl->classes);
            gs_hash_table_iter_valid(refl->classes, it);
            gs_hash_table_iter_advance(refl->classes, it)
		)
		{
			meta_class_t* c = gs_hash_table_iter_getp(refl->classes, it);

			const char* name = c->name;
			const char* base = c->base;
			uint32_t prop_cnt = gs_dyn_array_size(c->properties);
            const uint64_t id = gs_hash_str64(name);

            // Write out vtable to pass in
			gs_fprintln(fp, "\t// vtable");	
            gs_fprintln(fp, "\tgs_meta_vtable_t %s_vt = gs_default_val();", name);	
            for (uint32_t i = 0; i < gs_dyn_array_size(c->vtable.funcs); ++i)
            {
                vtable_func_t* f = &c->vtable.funcs[i];
                gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(%s)), (void*)%s);", name, f->name, f->func_ptr);	
            }

            // Standard VTable functions
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_%zu);", name, id);	
            gs_fprintln(fp, "\tgs_hash_table_insert(%s_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_%zu);", name, id);	
            
            // Formatting
			gs_fprintln(fp, "");	

			// Write out name as comment
			gs_fprintln(fp, "\t// %s", name);	
			gs_fprintln(fp, "\tgs_meta_class_register(meta, (&(gs_meta_class_decl_t) {");	
			{
				if (prop_cnt)
				{
					// Write out properties
					gs_fprintln(fp, "\t\t.properties = (gs_meta_property_t[]) {");	
					{
						gs_for_range_i(prop_cnt)
						{
							// Write out property
							meta_prop_t* p = &c->properties[i];

							// Type of property
							const char* type = NULL;
							if (prop_is_enum(refl, p->type))
							{
								type = gs_to_str(GS_META_PROPERTY_TYPE_INFO_ENUM);
							}
							else
							{
								type = prop_type_to_type_info(refl, p->type);
							}

							gs_fprintf(fp, "\t\t\tgs_meta_property(%s, %s, %s, %s)", 
								name, 
								p->type, 
								p->name, 
								type
							);	

							if (i < prop_cnt - 1)
							{
								gs_fprintf(fp, ",");	
							}
							gs_fprintf(fp, "\n");	
						}
					}
					gs_fprintln(fp,  "\t\t},");	
					gs_fprintln(fp,  "\t\t.size = %zu * sizeof(gs_meta_property_t),", prop_cnt);	
				}

				gs_fprintln(fp,  "\t\t.vtable = &%s_vt,", name);	
				gs_fprintln(fp,  "\t\t.name = gs_to_str(%s),", name);	
				gs_fprintln(fp,  "\t\t.base = gs_to_str(%s),", base);	
                gs_fprintln(fp,  "\t\t.cls_size = sizeof(%s)", name);
			}
			gs_fprintln(fp, "\t}));");	

			// Formatting
			gs_fprintln(fp, "");	
		}
	}

register_implementation_end:

	gs_fprintln(fp, "}");	

	// Formatting
	gs_fprintln(fp, "");

    // Formatting
	gs_fprintln(fp, "");	

	gs_fprintln(fp, "// ==== Objects API === //\n");	

    if (!refl->classes)
    {
        goto implementation_end;
    }
    
    // Generated Functions API 
    for 
    (
        gs_hash_table_iter it = gs_hash_table_iter_new(refl->classes);
        gs_hash_table_iter_valid(refl->classes, it);
        gs_hash_table_iter_advance(refl->classes, it)
    )
    {
        meta_class_t* c = gs_hash_table_iter_getp(refl->classes, it); 

        const char* name = c->name;
        const char* base = c->base;
        uint32_t prop_cnt = gs_dyn_array_size(c->properties);
        const uint64_t id = gs_hash_str64(name);

        gs_fprintln(fp, "// == %s API == //\n", name);	

        // Ctor
        {
            const char* params =  c->ctor.params;
            const char* func = c->ctor.func;

            gs_fprintln(fp, "GS_API_DECL %s obj_ctor_%zu(%s)", name, id, params);	
            gs_fprintln(fp, "{"); 

            gs_fprintln(fp, "\t%s _obj = gs_default_val();", name);	
            gs_fprintln(fp, "\t%s* this = &_obj;", name);	

            // Set object id here
            gs_fprintln(fp, "\tcast(this, gs_object_t)->cls_id = gs_obj_sid(%s);", name);	
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s", func);	
            }

            // Return
            gs_fprintln(fp, "\treturn _obj;");	

            gs_fprintln(fp, "}");	
        }

        // New
    
        {
            const char* params =  c->ctor.params;
            const char* func = c->ctor.func;

            gs_fprintln(fp, "GS_API_DECL gs_object_t* obj_new_%zu(%s)", id, params);	
            gs_fprintln(fp, "{"); 

            gs_fprintln(fp, "\t%s* _obj = gs_malloc_init(%s);", name, name);	
            gs_fprintln(fp, "\t%s* this = _obj;", name);	

            // Set object id here
            gs_fprintln(fp, "\tcast(this, gs_object_t)->cls_id = gs_obj_sid(%s);", name);	
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s", func);	
            }

            // Return
            gs_fprintln(fp, "\treturn (gs_object_t*)_obj;");	

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // Dtor 
        {
            const char* func = c->dtor.func;

            gs_fprintln(fp, "GS_API_DECL void obj_dtor_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // Serialize
        {
            const char* func = c->serialize.func;

            gs_fprintln(fp, "GS_API_DECL gs_result obj_serialize_%zu(gs_byte_buffer_t* buffer, const gs_object_t* in)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\tconst %s* this = (const %s*)in;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
                gs_fprintln(fp, "\treturn GS_RESULT_SUCCESS;");	
            } 
            else
            {
                // Default serialization function
                gs_fprintln(fp, "\treturn GS_RESULT_INCOMPLETE;");	
            }

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // Deserialize
        {
            const char* func = c->deserialize.func;

            gs_fprintln(fp, "GS_API_DECL gs_result obj_deserialize_%zu(gs_byte_buffer_t* buffer, gs_object_t* out)", id);	
            gs_fprintln(fp, "{"); 

            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s* this = (%s*)out;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
                gs_fprintln(fp, "\treturn GS_RESULT_SUCCESS;");	
            } 
            else
            {
                // Default deserialization function
                gs_fprintln(fp, "\treturn GS_RESULT_INCOMPLETE;");	
            }

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // On Create 
        {
            const char* func = c->on_create.func;

            gs_fprintln(fp, "GS_API_DECL void obj_on_create_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // On Start 
        {
            const char* func = c->on_start.func;

            gs_fprintln(fp, "GS_API_DECL void obj_on_start_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 

            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // On Stop 
        {
            const char* func = c->on_stop.func;

            gs_fprintln(fp, "GS_API_DECL void obj_on_stop_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            {
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // On Update 
        {
            const char* func = c->on_update.func;

            gs_fprintln(fp, "GS_API_DECL void obj_on_update_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            { 
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	

        // On Destroy 
        {
            const char* func = c->on_destroy.func;

            gs_fprintln(fp, "GS_API_DECL void obj_on_destroy_%zu(gs_object_t* obj)", id);	
            gs_fprintln(fp, "{"); 
            
            // Print the function box
            if (*func)
            { 
                gs_fprintln(fp, "\t%s* this = (%s*)obj;", name, name);	
                gs_fprintln(fp, "\t%s", func);	
            } 

            gs_fprintln(fp, "}");	
        }

        // Formatting
        gs_fprintln(fp, "");	
    } 

implementation_end:

	// Close the file
	fclose(fp);
}

int32_t main(int32_t argc, char** argv)
{
	// Init reflection data structure
	reflection_data_t refl = {0};
	reflection_data_init(&refl);

	if (!argc > 1)
	{
		return 0;
	}

	// Iterate through directory, collect files to open, generate data
	const char* path = argv[1];
	const char* output_dir = argv[2];
    const char* namespace = argv[3];
	DIR* dir = opendir(path);	
	if (dir)
	{
		struct dirent* ent = NULL;
		while ((ent = readdir(dir)) != NULL)
		{
			switch (ent->d_type)
			{
				case DT_REG: 
				{
					// Files
					gs_transient_buffer(FILE_EXT, 10);
					gs_platform_file_extension(FILE_EXT, 10, ent->d_name); 
					if (gs_string_compare_equal(FILE_EXT, "h"))
					{
						gs_snprintfc(PATH, META_STR_MAX, "%s%s", path, ent->d_name);
						parse_file(&refl, PATH);
					}
				} break;

				case DT_DIR: 
				{
					// Skip these
					if (gs_string_compare_equal(ent->d_name, ".") || gs_string_compare_equal(ent->d_name, ".."))
					{
						continue;
					}
				} break;

				default:
				{
				} break;
			}
		}

		closedir(dir);
	}

	// Write reflection data to file
	write_reflection_file(&refl, output_dir, namespace);
}
