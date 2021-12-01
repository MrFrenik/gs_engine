/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine
    * File: gs_object.h
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

#ifndef GS_OBJECT_H
#define GS_OBJECT_H

// Forward decl
struct gs_meta_t;

typedef struct gs_object_t	
{
	uint64_t cls_id;
} gs_object_t; 

// Function pointer typedefs
typedef void (* gs_obj_ctor_func)(gs_object_t* obj, void* args); 
typedef void (* gs_obj_dtor_func)(gs_object_t* obj); 
typedef gs_result (* gs_obj_serialize_func)(gs_byte_buffer_t*, const gs_object_t*); 
typedef gs_result (* gs_obj_deserialize_func)(gs_byte_buffer_t*, gs_object_t*); 
typedef void (*gs_obj_dtor_func)(gs_object_t* obj);
typedef void (*gs_obj_on_create_func)(gs_object_t* obj);
typedef void (*gs_obj_on_start_func)(gs_object_t* obj);
typedef void (*gs_obj_on_stop_func)(gs_object_t* obj);
typedef void (*gs_obj_on_update_func)(gs_object_t* obj);
typedef void (*gs_obj_on_destroy_func)(gs_object_t* obj);

// Default Functions
GS_API_DECL gs_result gs_object_serialize_default(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result gs_object_deserialize_default(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL gs_object_t* gs_object_malloc_default(size_t sz);
GS_API_DECL void gs_object_ctor_default(gs_object_t* obj);
GS_API_DECL void gs_object_dtor_default(gs_object_t* obj);

// Utility
GS_API_DECL void gs_obj_dump(struct gs_meta_t* meta, void* obj, gs_meta_class_t* cls);

// Internal functions
GS_API_PRIVATE gs_object_t* _gs_obj_new_internal(uint64_t id);
GS_API_PRIVATE void _gs_obj_ctor_internal(uint64_t id, gs_object_t* obj, void* args);
GS_API_PRIVATE void _gs_obj_dtor_internal(uint64_t id, gs_object_t* obj);
GS_API_PRIVATE gs_result _gs_obj_serialize_internal(uint64_t id, gs_byte_buffer_t* buffer, gs_object_t* in);
GS_API_PRIVATE gs_result _gs_obj_deserialize_internal(uint64_t id, gs_byte_buffer_t* buffer, gs_object_t* out); 

// Useful defines
#define base(T) T _base;
#define ctor(...) gs_empty_instruction()
#define dtor(...) gs_empty_instruction() 
#define introspect(...) gs_empty_instruction()
#define field(...) gs_empty_instruction()
#define serialize(...) gs_empty_instruction()
#define deserialize(...) gs_empty_instruction()
#define on_create(...)  gs_empty_instruction()
#define on_start(...)   gs_empty_instruction()
#define on_stop(...)    gs_empty_instruction()
#define on_update(...)  gs_empty_instruction()
#define on_destroy(...) gs_empty_instruction() 
#define cast(A, B) ((B*)(A)) 

// Reflection defines
#define vtable(...) /* __VA_ARGS__ */
#define ignore(...) gs_empty_instruction() 

// Object functions
#define gs_obj_id(OBJ)                (cast((OBJ), gs_object_t)->cls_id)  // Get object class id from instance
#define gs_obj_sid(T)                 gs_hash_str64(gs_to_str(T))    // Get object class id from static type
#define gs_obj_vtable_w_id(ID)        (&(gs_hash_table_getp(gs_meta_get_instance()->registry.classes, ID)->vtable)) // Get vtable for class
#define gs_obj_func_w_id(ID, NAME)    gs_meta_func_get_w_id(&gs_meta_get_instance()->registry, (ID), NAME) // Get function in vtable based on name
#define gs_obj_newid(ID)                _gs_obj_new_internal(ID) // Heap allocate object based on cls id 

#define gs_obj_ctor(T, ...)                 T##_ctor(__VA_ARGS__) 
#define gs_obj_newc(T, ...)                 (T*)(T##_new(__VA_ARGS__))
#define gs_obj_dtor(T, OBJ)                 T##_dtor(OBJ) 
#define gs_obj_serialize(T, BUFFER, OBJ)    T##_serialize(BUFFER, OBJ)
#define gs_obj_deserialize(T, BUFFER, OBJ)  T##_deserialize(BUFFER, OBJ)

#define gs_obj_ctor_w_id(ID, OBJ, ...)     gs_meta_func_get_w_id(&gs_meta_get_instance()->registry, (ID), gs_obj_ctor)(__VA_ARGS__)
#define gs_obj_dtor_w_id(ID)               gs_meta_func_get_w_id(&gs_meta_get_instance()->registry, (ID), gs_obj_dtor) 

typedef struct gs_meta_t
{
	gs_meta_registry_t registry;
} gs_meta_t;

// Get global instance to meta information
GS_API_DECL gs_meta_t gs_meta_new();
GS_API_DECL gs_meta_t* gs_meta_get_instance();
GS_API_DECL void gs_meta_set_instance(gs_meta_t* meta);
GS_API_DECL void gs_meta_register_gs(gs_meta_t* meta); 

#ifdef GS_OBJECT_IMPL

//==== [ Meta ] ====

gs_meta_t* g_meta = NULL;

GS_API_DECL gs_meta_t gs_meta_new()
{
	gs_meta_t meta = gs_default_val();
	return meta;
}

GS_API_DECL void gs_meta_set_instance(gs_meta_t* meta)
{
	g_meta = meta;
}

// Get global instance to meta information
GS_API_DECL gs_meta_t* gs_meta_get_instance()
{
	return g_meta;
} 

GS_API_DECL void gs_meta_register_gs(gs_meta_t* meta)
{
	//==== [ GS Meta ] ===== (these need to be manually registered for now)

	// gs_graphics_texture_desc_t
    gs_meta_class_register(&meta->registry, (&(gs_meta_class_decl_t){
        .properties = (gs_meta_property_t[]) {
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, width, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, height, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, format, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, wrap_s, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, wrap_t, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, min_filter, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, mag_filter, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, mip_filter, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, num_mips, GS_META_PROPERTY_TYPE_INFO_U32),
            gs_meta_property(gs_graphics_texture_desc_t, uint32_t, render_target, GS_META_PROPERTY_TYPE_INFO_U32)
        },
        .size = 10 * sizeof(gs_meta_property_t),
		.name = gs_to_str(gs_graphics_texture_desc_t)
    }));

	// gs_asset_texture_t
    gs_meta_class_register(&meta->registry, (&(gs_meta_class_decl_t){
        .properties = (gs_meta_property_t[]) {
            gs_meta_property(gs_asset_texture_t, gs_graphics_texture_desc_t, desc, GS_META_PROPERTY_TYPE_INFO_OBJ),
        },
        .size = 1 * sizeof(gs_meta_property_t),
		.name = gs_to_str(gs_asset_texture_t)
    }));
}

//===== [ Object functions ] ======

// Internal functions
GS_API_PRIVATE gs_object_t* _gs_obj_new_internal(uint64_t id)
{ 
    const gs_meta_class_t* cls = gs_meta_class_get_w_id(&gs_meta_get_instance()->registry, id);
    gs_object_t* obj = gs_malloc(cls->size);
    memset(obj, 0, cls->size);
    obj->cls_id = id;
    return obj;
} 

//===== [ Utils ] ======

GS_API_DECL void gs_obj_dump(gs_meta_t* meta, void* obj, gs_meta_class_t* cls)
{
	gs_println("cls: %s, ct: %zu", cls->name, cls->property_count);

	for (uint32_t i = 0; i < cls->property_count; ++i)
	{
		const gs_meta_property_t* prop = &cls->properties[i];
		switch (prop->type.id)
		{
			case GS_META_PROPERTY_TYPE_U32:
			{
				uint32_t* v = gs_meta_getvp(obj, uint32_t, prop);
				gs_println("\t%s (%s): %zu", prop->name, prop->type.name, *v);
			} break; 

			case GS_META_PROPERTY_TYPE_VEC3:
			{
				gs_vec3* v = gs_meta_getvp(obj, gs_vec3, prop);
				gs_println("\t%s (%s): <%.2f, %.2f, %.2f>", prop->name, prop->type.name, v->x, v->y, v->z);
			} break; 

            case GS_META_PROPERTY_TYPE_VQS: 
            {
				gs_vqs* v = gs_meta_getvp(obj, gs_vqs, prop);
                gs_quat* r = &v->rotation;
				gs_println("\t%s (%s): <%.2f, %.2f, %.2f, %.2f>", prop->name, prop->type.name,
                        r->x, r->y, r->z, r->w);
            } break;

			case GS_META_PROPERTY_TYPE_OBJ:
			{
				gs_println("\%s (%s): ", prop->name, prop->type.name);
				void* _obj = gs_meta_getvp(obj, void, prop);
				const gs_meta_class_t* clz = gs_meta_class_get_w_name(&meta->registry, prop->type_name); 
				if (_obj && clz)
				{
					gs_obj_dump(meta, _obj, clz);
				}
			} break;
		}
	}
} 

//==== [ Object defaults ] ====

GS_API_DECL gs_result gs_object_serialize_default(gs_byte_buffer_t* buffer, const gs_object_t	* in)
{
	return GS_RESULT_SUCCESS;
}

GS_API_DECL gs_result gs_object_deserialize_default(gs_byte_buffer_t* buffer, gs_object_t	* out)
{
	return GS_RESULT_SUCCESS;
} 


#endif // GS_OBJECT_IMPL
#endif // GS_OBJECT_H

















