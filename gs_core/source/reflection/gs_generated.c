
//============[ Implementation ]==============//

/*
 * This file has been generated. All modifications will be lost.
*/

GS_API_DECL void gs_meta_register_generated(gs_meta_registry_t* meta)
{
	// == [ enums ] == 

	// gs_asset_state
	gs_meta_enum_register(meta, (&(gs_meta_enum_decl_t) {
		.values = (gs_meta_enum_value_t[]) {
			(gs_meta_enum_value_t){.name = gs_to_str(GS_ASSET_STATE_UNLOADED)},
			(gs_meta_enum_value_t){.name = gs_to_str(GS_ASSET_STATE_LOADED)}
		},
		.size = 2 * sizeof(gs_meta_enum_value_t),
		.name = gs_to_str(gs_asset_state)
	}));
	// componentsble_freet
	gs_meta_enum_register(meta, (&(gs_meta_enum_decl_t) {
		.values = (gs_meta_enum_value_t[]) {
			(gs_meta_enum_value_t){.name = gs_to_str(for)},
			(gs_meta_enum_value_t){.name = gs_to_str(gs_hash_table_iter)},
			(gs_meta_enum_value_t){.name = gs_to_str(it)},
			(gs_meta_enum_value_t){.name = gs_to_str(entities)},
			(gs_meta_enum_value_t){.name = gs_to_str(components)},
			(gs_meta_enum_value_t){.name = gs_to_str(gs_hash_table_iter_valid)},
			(gs_meta_enum_value_t){.name = gs_to_str(entities)},
			(gs_meta_enum_value_t){.name = gs_to_str(components)},
			(gs_meta_enum_value_t){.name = gs_to_str(it)},
			(gs_meta_enum_value_t){.name = gs_to_str(gs_hash_table_iter_advance)},
			(gs_meta_enum_value_t){.name = gs_to_str(entities)},
			(gs_meta_enum_value_t){.name = gs_to_str(components)},
			(gs_meta_enum_value_t){.name = gs_to_str(it)},
			(gs_meta_enum_value_t){.name = gs_to_str(gs_free)},
			(gs_meta_enum_value_t){.name = gs_to_str(gs_hash_table_iter_get)},
			(gs_meta_enum_value_t){.name = gs_to_str(entities)},
			(gs_meta_enum_value_t){.name = gs_to_str(components)},
			(gs_meta_enum_value_t){.name = gs_to_str(it)}
		},
		.size = 18 * sizeof(gs_meta_enum_value_t),
		.name = gs_to_str(componentsble_freet)
	}));

	// == [ classes ] == 

	// vtable
	gs_meta_vtable_t gs_asset_t_vt = gs_default_val();
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_460992599);
	gs_hash_table_insert(gs_asset_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_460992599);

	// gs_asset_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_asset_t_vt,
		.name = gs_to_str(gs_asset_t),
		.base = gs_to_str(gs_object_t),
		.cls_size = sizeof(gs_asset_t)
	}));

	// vtable
	gs_meta_vtable_t gs_mesh_t_vt = gs_default_val();
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_4125999924);
	gs_hash_table_insert(gs_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_4125999924);

	// gs_mesh_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_mesh_t_vt,
		.name = gs_to_str(gs_mesh_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_mesh_t)
	}));

	// vtable
	gs_meta_vtable_t gs_material_t_vt = gs_default_val();
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3458782124);
	gs_hash_table_insert(gs_material_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3458782124);

	// gs_material_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_material_t, gs_asset_handle_t, pipeline, GS_META_PROPERTY_TYPE_INFO_OBJ)
		},
		.size = 1 * sizeof(gs_meta_property_t),
		.vtable = &gs_material_t_vt,
		.name = gs_to_str(gs_material_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_material_t)
	}));

	// vtable
	gs_meta_vtable_t gs_texture_t_vt = gs_default_val();
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3860267416);
	gs_hash_table_insert(gs_texture_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3860267416);

	// gs_texture_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_texture_t, gs_asset_texture_t, texture, GS_META_PROPERTY_TYPE_INFO_OBJ)
		},
		.size = 1 * sizeof(gs_meta_property_t),
		.vtable = &gs_texture_t_vt,
		.name = gs_to_str(gs_texture_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_texture_t)
	}));

	// vtable
	gs_meta_vtable_t gs_font_t_vt = gs_default_val();
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_1745959604);
	gs_hash_table_insert(gs_font_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_1745959604);

	// gs_font_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_font_t_vt,
		.name = gs_to_str(gs_font_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_font_t)
	}));

	// vtable
	gs_meta_vtable_t gs_component_base_t_vt = gs_default_val();
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3988592418);
	gs_hash_table_insert(gs_component_base_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3988592418);

	// gs_component_base_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_component_base_t, uint32_t, entity, GS_META_PROPERTY_TYPE_INFO_U32)
		},
		.size = 1 * sizeof(gs_meta_property_t),
		.vtable = &gs_component_base_t_vt,
		.name = gs_to_str(gs_component_base_t),
		.base = gs_to_str(gs_object_t),
		.cls_size = sizeof(gs_component_base_t)
	}));

	// vtable
	gs_meta_vtable_t gs_sound_t_vt = gs_default_val();
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_4054288004);
	gs_hash_table_insert(gs_sound_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_4054288004);

	// gs_sound_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_sound_t_vt,
		.name = gs_to_str(gs_sound_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_sound_t)
	}));

	// vtable
	gs_meta_vtable_t gs_pipeline_t_vt = gs_default_val();
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_350524197);
	gs_hash_table_insert(gs_pipeline_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_350524197);

	// gs_pipeline_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_pipeline_t_vt,
		.name = gs_to_str(gs_pipeline_t),
		.base = gs_to_str(gs_asset_t),
		.cls_size = sizeof(gs_pipeline_t)
	}));

	// vtable
	gs_meta_vtable_t gs_component_transform_t_vt = gs_default_val();
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3943274619);
	gs_hash_table_insert(gs_component_transform_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3943274619);

	// gs_component_transform_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_component_transform_t, gs_vqs, transform, GS_META_PROPERTY_TYPE_INFO_VQS)
		},
		.size = 1 * sizeof(gs_meta_property_t),
		.vtable = &gs_component_transform_t_vt,
		.name = gs_to_str(gs_component_transform_t),
		.base = gs_to_str(gs_component_base_t),
		.cls_size = sizeof(gs_component_transform_t)
	}));

	// vtable
	gs_meta_vtable_t gs_component_static_mesh_t_vt = gs_default_val();
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_1659109731);
	gs_hash_table_insert(gs_component_static_mesh_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_1659109731);

	// gs_component_static_mesh_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_component_static_mesh_t, uint32_t, renderable_id, GS_META_PROPERTY_TYPE_INFO_U32),
			gs_meta_property(gs_component_static_mesh_t, gs_graphics_scene_t, scene, GS_META_PROPERTY_TYPE_INFO_OBJ)
		},
		.size = 2 * sizeof(gs_meta_property_t),
		.vtable = &gs_component_static_mesh_t_vt,
		.name = gs_to_str(gs_component_static_mesh_t),
		.base = gs_to_str(gs_component_base_t),
		.cls_size = sizeof(gs_component_static_mesh_t)
	}));

	// vtable
	gs_meta_vtable_t gs_component_physics_t_vt = gs_default_val();
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3872275868);
	gs_hash_table_insert(gs_component_physics_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3872275868);

	// gs_component_physics_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.properties = (gs_meta_property_t[]) {
			gs_meta_property(gs_component_physics_t, gs_vec3, velocity, GS_META_PROPERTY_TYPE_INFO_VEC3),
			gs_meta_property(gs_component_physics_t, gs_vec3, acceleration, GS_META_PROPERTY_TYPE_INFO_VEC3)
		},
		.size = 2 * sizeof(gs_meta_property_t),
		.vtable = &gs_component_physics_t_vt,
		.name = gs_to_str(gs_component_physics_t),
		.base = gs_to_str(gs_component_base_t),
		.cls_size = sizeof(gs_component_physics_t)
	}));

	// vtable
	gs_meta_vtable_t gs_entity_t_vt = gs_default_val();
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_ctor)), (void*)obj_ctor_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_new)), (void*)obj_new_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_dtor)), (void*)obj_dtor_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_serialize)), (void*)obj_serialize_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_deserialize)), (void*)obj_deserialize_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_create)), (void*)obj_on_create_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_start)), (void*)obj_on_start_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_stop)), (void*)obj_on_stop_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_update)), (void*)obj_on_update_3007819484);
	gs_hash_table_insert(gs_entity_t_vt.funcs, gs_hash_str64(gs_to_str(gs_obj_on_destroy)), (void*)obj_on_destroy_3007819484);

	// gs_entity_t
	gs_meta_class_register(meta, (&(gs_meta_class_decl_t) {
		.vtable = &gs_entity_t_vt,
		.name = gs_to_str(gs_entity_t),
		.base = gs_to_str(gs_object_t),
		.cls_size = sizeof(gs_entity_t)
	}));

}


// ==== Objects API === //

// == gs_asset_t API == //

GS_API_DECL gs_asset_t obj_ctor_460992599()
{
	gs_asset_t _obj = gs_default_val();
	gs_asset_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_asset_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_460992599()
{
	gs_asset_t* _obj = gs_malloc_init(gs_asset_t);
	gs_asset_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_asset_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_460992599(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_460992599(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_460992599(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_460992599(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_460992599(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_460992599(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_460992599(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_460992599(gs_object_t* obj)
{
}

// == gs_mesh_t API == //

GS_API_DECL gs_mesh_t obj_ctor_4125999924()
{
	gs_mesh_t _obj = gs_default_val();
	gs_mesh_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_mesh_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_4125999924()
{
	gs_mesh_t* _obj = gs_malloc_init(gs_mesh_t);
	gs_mesh_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_mesh_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_4125999924(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_4125999924(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_4125999924(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_4125999924(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_4125999924(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_4125999924(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_4125999924(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_4125999924(gs_object_t* obj)
{
}

// == gs_material_t API == //

GS_API_DECL gs_material_t obj_ctor_3458782124(gs_asset_handle_t pip)
{
	gs_material_t _obj = gs_default_val();
	gs_material_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_material_t);
	{
            gs_pipeline_t* pipe = gs_asset_handle_get(&pip);
            gs_assert(pipe);
            this->pipeline = pip;
            this->material = gs_gfxt_material_create(&(gs_gfxt_material_desc_t){
                .pip_func = {
                    .func = gs_get_pipeline_raw	,
                    .hndl = pipe
                }
            });
            gs_assert(this->material.desc.pip_func.hndl);
        }
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3458782124(gs_asset_handle_t pip)
{
	gs_material_t* _obj = gs_malloc_init(gs_material_t);
	gs_material_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_material_t);
	{
            gs_pipeline_t* pipe = gs_asset_handle_get(&pip);
            gs_assert(pipe);
            this->pipeline = pip;
            this->material = gs_gfxt_material_create(&(gs_gfxt_material_desc_t){
                .pip_func = {
                    .func = gs_get_pipeline_raw	,
                    .hndl = pipe
                }
            });
            gs_assert(this->material.desc.pip_func.hndl);
        }
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3458782124(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3458782124(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_3458782124(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_3458782124(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3458782124(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3458782124(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3458782124(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3458782124(gs_object_t* obj)
{
}

// == gs_texture_t API == //

GS_API_DECL gs_texture_t obj_ctor_3860267416()
{
	gs_texture_t _obj = gs_default_val();
	gs_texture_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_texture_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3860267416()
{
	gs_texture_t* _obj = gs_malloc_init(gs_texture_t);
	gs_texture_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_texture_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3860267416(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3860267416(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	const gs_texture_t* this = (const gs_texture_t*)in;
	{
        return gs_texture_serialize(buffer, this);
    }
	return GS_RESULT_SUCCESS;
}

GS_API_DECL gs_result obj_deserialize_3860267416(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	gs_texture_t* this = (gs_texture_t*)out;
	{
        return gs_texture_deserialize(buffer, this);
    }
	return GS_RESULT_SUCCESS;
}

GS_API_DECL void obj_on_create_3860267416(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3860267416(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3860267416(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3860267416(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3860267416(gs_object_t* obj)
{
}

// == gs_font_t API == //

GS_API_DECL gs_font_t obj_ctor_1745959604()
{
	gs_font_t _obj = gs_default_val();
	gs_font_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_font_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_1745959604()
{
	gs_font_t* _obj = gs_malloc_init(gs_font_t);
	gs_font_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_font_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_1745959604(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_1745959604(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_1745959604(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_1745959604(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_1745959604(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_1745959604(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_1745959604(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_1745959604(gs_object_t* obj)
{
}

// == gs_component_base_t API == //

GS_API_DECL gs_component_base_t obj_ctor_3988592418()
{
	gs_component_base_t _obj = gs_default_val();
	gs_component_base_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_base_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3988592418()
{
	gs_component_base_t* _obj = gs_malloc_init(gs_component_base_t);
	gs_component_base_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_base_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3988592418(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3988592418(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_3988592418(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_3988592418(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3988592418(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3988592418(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3988592418(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3988592418(gs_object_t* obj)
{
}

// == gs_sound_t API == //

GS_API_DECL gs_sound_t obj_ctor_4054288004()
{
	gs_sound_t _obj = gs_default_val();
	gs_sound_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_sound_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_4054288004()
{
	gs_sound_t* _obj = gs_malloc_init(gs_sound_t);
	gs_sound_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_sound_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_4054288004(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_4054288004(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_4054288004(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_4054288004(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_4054288004(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_4054288004(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_4054288004(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_4054288004(gs_object_t* obj)
{
}

// == gs_pipeline_t API == //

GS_API_DECL gs_pipeline_t obj_ctor_350524197(void)
{
	gs_pipeline_t _obj = gs_default_val();
	gs_pipeline_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_pipeline_t);
	{
            gs_println("PIPELINE CTOR");
        }
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_350524197(void)
{
	gs_pipeline_t* _obj = gs_malloc_init(gs_pipeline_t);
	gs_pipeline_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_pipeline_t);
	{
            gs_println("PIPELINE CTOR");
        }
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_350524197(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_350524197(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_350524197(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_350524197(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_350524197(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_350524197(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_350524197(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_350524197(gs_object_t* obj)
{
}

// == gs_component_transform_t API == //

GS_API_DECL gs_component_transform_t obj_ctor_3943274619(gs_vqs xform)
{
	gs_component_transform_t _obj = gs_default_val();
	gs_component_transform_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_transform_t);
	{
            this->transform = xform;
        }
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3943274619(gs_vqs xform)
{
	gs_component_transform_t* _obj = gs_malloc_init(gs_component_transform_t);
	gs_component_transform_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_transform_t);
	{
            this->transform = xform;
        }
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3943274619(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3943274619(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_3943274619(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_3943274619(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3943274619(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3943274619(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3943274619(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3943274619(gs_object_t* obj)
{
}

// == gs_component_static_mesh_t API == //

GS_API_DECL gs_component_static_mesh_t obj_ctor_1659109731(gs_graphics_scene_t* scene)
{
	gs_component_static_mesh_t _obj = gs_default_val();
	gs_component_static_mesh_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_static_mesh_t);
	{
            gs_renderable_static_mesh_t rend = {0};
            this->renderable_id = gs_graphics_scene_add_renderable_static_mesh(scene, rend);
            this->scene = scene;
        }
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_1659109731(gs_graphics_scene_t* scene)
{
	gs_component_static_mesh_t* _obj = gs_malloc_init(gs_component_static_mesh_t);
	gs_component_static_mesh_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_static_mesh_t);
	{
            gs_renderable_static_mesh_t rend = {0};
            this->renderable_id = gs_graphics_scene_add_renderable_static_mesh(scene, rend);
            this->scene = scene;
        }
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_1659109731(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_1659109731(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_1659109731(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_1659109731(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_1659109731(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_1659109731(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_1659109731(gs_object_t* obj)
{
	gs_component_static_mesh_t* this = (gs_component_static_mesh_t*)obj;
	{ 
        gs_component_static_mesh_update(this);
    }
}

GS_API_DECL void obj_on_destroy_1659109731(gs_object_t* obj)
{
}

// == gs_component_physics_t API == //

GS_API_DECL gs_component_physics_t obj_ctor_3872275868()
{
	gs_component_physics_t _obj = gs_default_val();
	gs_component_physics_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_physics_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3872275868()
{
	gs_component_physics_t* _obj = gs_malloc_init(gs_component_physics_t);
	gs_component_physics_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_component_physics_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3872275868(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3872275868(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_3872275868(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_3872275868(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3872275868(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3872275868(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3872275868(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3872275868(gs_object_t* obj)
{
}

// == gs_entity_t API == //

GS_API_DECL gs_entity_t obj_ctor_3007819484()
{
	gs_entity_t _obj = gs_default_val();
	gs_entity_t* this = &_obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_entity_t);
	return _obj;
}
GS_API_DECL gs_object_t* obj_new_3007819484()
{
	gs_entity_t* _obj = gs_malloc_init(gs_entity_t);
	gs_entity_t* this = _obj;
	cast(this, gs_object_t)->cls_id = gs_obj_sid(gs_entity_t);
	return (gs_object_t*)_obj;
}

GS_API_DECL void obj_dtor_3007819484(gs_object_t* obj)
{
}

GS_API_DECL gs_result obj_serialize_3007819484(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL gs_result obj_deserialize_3007819484(gs_byte_buffer_t* buffer, gs_object_t* out)
{
	return GS_RESULT_INCOMPLETE;
}

GS_API_DECL void obj_on_create_3007819484(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_start_3007819484(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_stop_3007819484(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_update_3007819484(gs_object_t* obj)
{
}

GS_API_DECL void obj_on_destroy_3007819484(gs_object_t* obj)
{
}

