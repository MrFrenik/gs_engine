#ifndef gs_GENERATED_H
#define gs_GENERATED_H

/*
 * This file has been generated. All modifications will be lost.
*/

// ==== Main API === //
GS_API_DECL void gs_meta_register_generated(gs_meta_registry_t* meta);

// ==== Objects API === //

// == gs_asset_t API == //

struct gs_asset_t;
#define gs_asset_t_ctor obj_ctor_460992599
#define gs_asset_t_new obj_new_460992599
#define gs_asset_t_dtor obj_dtor_460992599
#define gs_asset_t_serialize obj_serialize_460992599
#define gs_asset_t_deserialize obj_deserialize_460992599
#define gs_asset_t_on_create obj_on_create_460992599
#define gs_asset_t_on_start obj_on_start_460992599
#define gs_asset_t_on_stop obj_on_stop_460992599
#define gs_asset_t_on_update obj_on_update_460992599
#define gs_asset_t_on_destroy obj_on_destroy_460992599

GS_API_DECL struct gs_asset_t obj_ctor_460992599();
GS_API_DECL gs_object_t* obj_new_460992599();
GS_API_DECL void obj_dtor_460992599(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_460992599(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_460992599(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_460992599(gs_object_t* in);
GS_API_DECL void obj_on_start_460992599(gs_object_t* in);
GS_API_DECL void obj_on_stop_460992599(gs_object_t* in);
GS_API_DECL void obj_on_update_460992599(gs_object_t* in);
GS_API_DECL void obj_on_destroy_460992599(gs_object_t* in);

// == gs_mesh_t API == //

struct gs_mesh_t;
#define gs_mesh_t_ctor obj_ctor_4125999924
#define gs_mesh_t_new obj_new_4125999924
#define gs_mesh_t_dtor obj_dtor_4125999924
#define gs_mesh_t_serialize obj_serialize_4125999924
#define gs_mesh_t_deserialize obj_deserialize_4125999924
#define gs_mesh_t_on_create obj_on_create_4125999924
#define gs_mesh_t_on_start obj_on_start_4125999924
#define gs_mesh_t_on_stop obj_on_stop_4125999924
#define gs_mesh_t_on_update obj_on_update_4125999924
#define gs_mesh_t_on_destroy obj_on_destroy_4125999924

GS_API_DECL struct gs_mesh_t obj_ctor_4125999924();
GS_API_DECL gs_object_t* obj_new_4125999924();
GS_API_DECL void obj_dtor_4125999924(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_4125999924(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_4125999924(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_4125999924(gs_object_t* in);
GS_API_DECL void obj_on_start_4125999924(gs_object_t* in);
GS_API_DECL void obj_on_stop_4125999924(gs_object_t* in);
GS_API_DECL void obj_on_update_4125999924(gs_object_t* in);
GS_API_DECL void obj_on_destroy_4125999924(gs_object_t* in);

// == gs_material_t API == //

struct gs_material_t;
#define gs_material_t_ctor obj_ctor_3458782124
#define gs_material_t_new obj_new_3458782124
#define gs_material_t_dtor obj_dtor_3458782124
#define gs_material_t_serialize obj_serialize_3458782124
#define gs_material_t_deserialize obj_deserialize_3458782124
#define gs_material_t_on_create obj_on_create_3458782124
#define gs_material_t_on_start obj_on_start_3458782124
#define gs_material_t_on_stop obj_on_stop_3458782124
#define gs_material_t_on_update obj_on_update_3458782124
#define gs_material_t_on_destroy obj_on_destroy_3458782124

GS_API_DECL struct gs_material_t obj_ctor_3458782124(gs_asset_handle_t pip);
GS_API_DECL gs_object_t* obj_new_3458782124(gs_asset_handle_t pip);
GS_API_DECL void obj_dtor_3458782124(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3458782124(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3458782124(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3458782124(gs_object_t* in);
GS_API_DECL void obj_on_start_3458782124(gs_object_t* in);
GS_API_DECL void obj_on_stop_3458782124(gs_object_t* in);
GS_API_DECL void obj_on_update_3458782124(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3458782124(gs_object_t* in);

// == gs_texture_t API == //

struct gs_texture_t;
#define gs_texture_t_ctor obj_ctor_3860267416
#define gs_texture_t_new obj_new_3860267416
#define gs_texture_t_dtor obj_dtor_3860267416
#define gs_texture_t_serialize obj_serialize_3860267416
#define gs_texture_t_deserialize obj_deserialize_3860267416
#define gs_texture_t_on_create obj_on_create_3860267416
#define gs_texture_t_on_start obj_on_start_3860267416
#define gs_texture_t_on_stop obj_on_stop_3860267416
#define gs_texture_t_on_update obj_on_update_3860267416
#define gs_texture_t_on_destroy obj_on_destroy_3860267416

GS_API_DECL struct gs_texture_t obj_ctor_3860267416();
GS_API_DECL gs_object_t* obj_new_3860267416();
GS_API_DECL void obj_dtor_3860267416(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3860267416(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3860267416(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3860267416(gs_object_t* in);
GS_API_DECL void obj_on_start_3860267416(gs_object_t* in);
GS_API_DECL void obj_on_stop_3860267416(gs_object_t* in);
GS_API_DECL void obj_on_update_3860267416(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3860267416(gs_object_t* in);

// == gs_font_t API == //

struct gs_font_t;
#define gs_font_t_ctor obj_ctor_1745959604
#define gs_font_t_new obj_new_1745959604
#define gs_font_t_dtor obj_dtor_1745959604
#define gs_font_t_serialize obj_serialize_1745959604
#define gs_font_t_deserialize obj_deserialize_1745959604
#define gs_font_t_on_create obj_on_create_1745959604
#define gs_font_t_on_start obj_on_start_1745959604
#define gs_font_t_on_stop obj_on_stop_1745959604
#define gs_font_t_on_update obj_on_update_1745959604
#define gs_font_t_on_destroy obj_on_destroy_1745959604

GS_API_DECL struct gs_font_t obj_ctor_1745959604();
GS_API_DECL gs_object_t* obj_new_1745959604();
GS_API_DECL void obj_dtor_1745959604(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_1745959604(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_1745959604(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_1745959604(gs_object_t* in);
GS_API_DECL void obj_on_start_1745959604(gs_object_t* in);
GS_API_DECL void obj_on_stop_1745959604(gs_object_t* in);
GS_API_DECL void obj_on_update_1745959604(gs_object_t* in);
GS_API_DECL void obj_on_destroy_1745959604(gs_object_t* in);

// == gs_component_base_t API == //

struct gs_component_base_t;
#define gs_component_base_t_ctor obj_ctor_3988592418
#define gs_component_base_t_new obj_new_3988592418
#define gs_component_base_t_dtor obj_dtor_3988592418
#define gs_component_base_t_serialize obj_serialize_3988592418
#define gs_component_base_t_deserialize obj_deserialize_3988592418
#define gs_component_base_t_on_create obj_on_create_3988592418
#define gs_component_base_t_on_start obj_on_start_3988592418
#define gs_component_base_t_on_stop obj_on_stop_3988592418
#define gs_component_base_t_on_update obj_on_update_3988592418
#define gs_component_base_t_on_destroy obj_on_destroy_3988592418

GS_API_DECL struct gs_component_base_t obj_ctor_3988592418();
GS_API_DECL gs_object_t* obj_new_3988592418();
GS_API_DECL void obj_dtor_3988592418(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3988592418(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3988592418(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3988592418(gs_object_t* in);
GS_API_DECL void obj_on_start_3988592418(gs_object_t* in);
GS_API_DECL void obj_on_stop_3988592418(gs_object_t* in);
GS_API_DECL void obj_on_update_3988592418(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3988592418(gs_object_t* in);

// == gs_sound_t API == //

struct gs_sound_t;
#define gs_sound_t_ctor obj_ctor_4054288004
#define gs_sound_t_new obj_new_4054288004
#define gs_sound_t_dtor obj_dtor_4054288004
#define gs_sound_t_serialize obj_serialize_4054288004
#define gs_sound_t_deserialize obj_deserialize_4054288004
#define gs_sound_t_on_create obj_on_create_4054288004
#define gs_sound_t_on_start obj_on_start_4054288004
#define gs_sound_t_on_stop obj_on_stop_4054288004
#define gs_sound_t_on_update obj_on_update_4054288004
#define gs_sound_t_on_destroy obj_on_destroy_4054288004

GS_API_DECL struct gs_sound_t obj_ctor_4054288004();
GS_API_DECL gs_object_t* obj_new_4054288004();
GS_API_DECL void obj_dtor_4054288004(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_4054288004(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_4054288004(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_4054288004(gs_object_t* in);
GS_API_DECL void obj_on_start_4054288004(gs_object_t* in);
GS_API_DECL void obj_on_stop_4054288004(gs_object_t* in);
GS_API_DECL void obj_on_update_4054288004(gs_object_t* in);
GS_API_DECL void obj_on_destroy_4054288004(gs_object_t* in);

// == gs_pipeline_t API == //

struct gs_pipeline_t;
#define gs_pipeline_t_ctor obj_ctor_350524197
#define gs_pipeline_t_new obj_new_350524197
#define gs_pipeline_t_dtor obj_dtor_350524197
#define gs_pipeline_t_serialize obj_serialize_350524197
#define gs_pipeline_t_deserialize obj_deserialize_350524197
#define gs_pipeline_t_on_create obj_on_create_350524197
#define gs_pipeline_t_on_start obj_on_start_350524197
#define gs_pipeline_t_on_stop obj_on_stop_350524197
#define gs_pipeline_t_on_update obj_on_update_350524197
#define gs_pipeline_t_on_destroy obj_on_destroy_350524197

GS_API_DECL struct gs_pipeline_t obj_ctor_350524197(void);
GS_API_DECL gs_object_t* obj_new_350524197(void);
GS_API_DECL void obj_dtor_350524197(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_350524197(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_350524197(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_350524197(gs_object_t* in);
GS_API_DECL void obj_on_start_350524197(gs_object_t* in);
GS_API_DECL void obj_on_stop_350524197(gs_object_t* in);
GS_API_DECL void obj_on_update_350524197(gs_object_t* in);
GS_API_DECL void obj_on_destroy_350524197(gs_object_t* in);

// == gs_component_transform_t API == //

struct gs_component_transform_t;
#define gs_component_transform_t_ctor obj_ctor_3943274619
#define gs_component_transform_t_new obj_new_3943274619
#define gs_component_transform_t_dtor obj_dtor_3943274619
#define gs_component_transform_t_serialize obj_serialize_3943274619
#define gs_component_transform_t_deserialize obj_deserialize_3943274619
#define gs_component_transform_t_on_create obj_on_create_3943274619
#define gs_component_transform_t_on_start obj_on_start_3943274619
#define gs_component_transform_t_on_stop obj_on_stop_3943274619
#define gs_component_transform_t_on_update obj_on_update_3943274619
#define gs_component_transform_t_on_destroy obj_on_destroy_3943274619

GS_API_DECL struct gs_component_transform_t obj_ctor_3943274619(gs_vqs xform);
GS_API_DECL gs_object_t* obj_new_3943274619(gs_vqs xform);
GS_API_DECL void obj_dtor_3943274619(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3943274619(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3943274619(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3943274619(gs_object_t* in);
GS_API_DECL void obj_on_start_3943274619(gs_object_t* in);
GS_API_DECL void obj_on_stop_3943274619(gs_object_t* in);
GS_API_DECL void obj_on_update_3943274619(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3943274619(gs_object_t* in);

// == gs_component_static_mesh_t API == //

struct gs_component_static_mesh_t;
#define gs_component_static_mesh_t_ctor obj_ctor_1659109731
#define gs_component_static_mesh_t_new obj_new_1659109731
#define gs_component_static_mesh_t_dtor obj_dtor_1659109731
#define gs_component_static_mesh_t_serialize obj_serialize_1659109731
#define gs_component_static_mesh_t_deserialize obj_deserialize_1659109731
#define gs_component_static_mesh_t_on_create obj_on_create_1659109731
#define gs_component_static_mesh_t_on_start obj_on_start_1659109731
#define gs_component_static_mesh_t_on_stop obj_on_stop_1659109731
#define gs_component_static_mesh_t_on_update obj_on_update_1659109731
#define gs_component_static_mesh_t_on_destroy obj_on_destroy_1659109731

GS_API_DECL struct gs_component_static_mesh_t obj_ctor_1659109731(gs_graphics_scene_t* scene);
GS_API_DECL gs_object_t* obj_new_1659109731(gs_graphics_scene_t* scene);
GS_API_DECL void obj_dtor_1659109731(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_1659109731(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_1659109731(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_1659109731(gs_object_t* in);
GS_API_DECL void obj_on_start_1659109731(gs_object_t* in);
GS_API_DECL void obj_on_stop_1659109731(gs_object_t* in);
GS_API_DECL void obj_on_update_1659109731(gs_object_t* in);
GS_API_DECL void obj_on_destroy_1659109731(gs_object_t* in);

// == gs_component_physics_t API == //

struct gs_component_physics_t;
#define gs_component_physics_t_ctor obj_ctor_3872275868
#define gs_component_physics_t_new obj_new_3872275868
#define gs_component_physics_t_dtor obj_dtor_3872275868
#define gs_component_physics_t_serialize obj_serialize_3872275868
#define gs_component_physics_t_deserialize obj_deserialize_3872275868
#define gs_component_physics_t_on_create obj_on_create_3872275868
#define gs_component_physics_t_on_start obj_on_start_3872275868
#define gs_component_physics_t_on_stop obj_on_stop_3872275868
#define gs_component_physics_t_on_update obj_on_update_3872275868
#define gs_component_physics_t_on_destroy obj_on_destroy_3872275868

GS_API_DECL struct gs_component_physics_t obj_ctor_3872275868();
GS_API_DECL gs_object_t* obj_new_3872275868();
GS_API_DECL void obj_dtor_3872275868(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3872275868(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3872275868(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3872275868(gs_object_t* in);
GS_API_DECL void obj_on_start_3872275868(gs_object_t* in);
GS_API_DECL void obj_on_stop_3872275868(gs_object_t* in);
GS_API_DECL void obj_on_update_3872275868(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3872275868(gs_object_t* in);

// == gs_entity_t API == //

struct gs_entity_t;
#define gs_entity_t_ctor obj_ctor_3007819484
#define gs_entity_t_new obj_new_3007819484
#define gs_entity_t_dtor obj_dtor_3007819484
#define gs_entity_t_serialize obj_serialize_3007819484
#define gs_entity_t_deserialize obj_deserialize_3007819484
#define gs_entity_t_on_create obj_on_create_3007819484
#define gs_entity_t_on_start obj_on_start_3007819484
#define gs_entity_t_on_stop obj_on_stop_3007819484
#define gs_entity_t_on_update obj_on_update_3007819484
#define gs_entity_t_on_destroy obj_on_destroy_3007819484

GS_API_DECL struct gs_entity_t obj_ctor_3007819484();
GS_API_DECL gs_object_t* obj_new_3007819484();
GS_API_DECL void obj_dtor_3007819484(struct gs_object_t* obj);
GS_API_DECL gs_result obj_serialize_3007819484(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result obj_deserialize_3007819484(gs_byte_buffer_t* buffer, gs_object_t* out);
GS_API_DECL void obj_on_create_3007819484(gs_object_t* in);
GS_API_DECL void obj_on_start_3007819484(gs_object_t* in);
GS_API_DECL void obj_on_stop_3007819484(gs_object_t* in);
GS_API_DECL void obj_on_update_3007819484(gs_object_t* in);
GS_API_DECL void obj_on_destroy_3007819484(gs_object_t* in);

#endif // gs_GENERATED_H
