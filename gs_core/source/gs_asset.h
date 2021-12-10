/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine
    * File: gs_asset.h
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

#ifndef GS_ASSET_H
#define GS_ASSET_H

#define GS_ASSET_STR_MAX 1024

// Forward decls.
struct gs_asset_importer_t;
struct gs_asset_record_t;
struct gs_asset_storage_t;

/*
 * TODO(john):
 * 		Create default assets as fallbacks (in case of loading issues)
 * 		Try to load an animation file and animate for 3d shit
 * 		Use dirent.h for file iteration to get around windows garbage
*/

introspect()
typedef enum gs_asset_state
{
	GS_ASSET_STATE_UNLOADED = 0x00,
	GS_ASSET_STATE_LOADED
} gs_asset_state;

// Functions
GS_API_DECL void gs_asset_qualified_name(const char* src, char* dst, size_t sz);

introspect()
typedef struct gs_asset_t
{
    base(gs_object_t)

	// Fields
    uint32_t record_hndl;    // Handle to internal record for asset
	gs_asset_state state;

} gs_asset_t; 

typedef struct gs_asset_handle_t
{ 
    uint32_t hndl;              // Slot array handle to raw asset in importer
    uint32_t importer;     // Slot array handle to raw Importer data in asset manager 
} gs_asset_handle_t;

GS_API_DECL gs_asset_handle_t gs_asset_handle_invalid();
GS_API_DECL gs_asset_handle_t gs_asset_handle_create(const gs_asset_t* asset);
GS_API_DECL gs_asset_t* gs_asset_handle_get(gs_asset_handle_t	* hndl);

introspect()
typedef struct gs_mesh_t 
{
	base(gs_asset_t) 
	
	// Fields
	gs_gfxt_mesh_t mesh;

} gs_mesh_t;

#define gs_mesh_draw(CB, MESH)\
    gs_gfxt_mesh_draw((CB), &((MESH)->mesh))

GS_API_DECL bool gs_mesh_load_resource_from_file(const char* path, gs_asset_t* out, void* import_options /*gs_gfxt_mesh_import_options_t*/);

introspect()
typedef struct gs_texture_t
{
	base(gs_asset_t)

    serialize({
        return gs_texture_serialize(buffer, this);
    })

    deserialize({
        return gs_texture_deserialize(buffer, this);
    })

	// Fields
    field()
	gs_asset_texture_t texture;

} gs_texture_t; 

GS_API_DECL gs_result gs_texture_serialize(gs_byte_buffer_t* buffer, const gs_object_t* in);
GS_API_DECL gs_result gs_texture_deserialize(gs_byte_buffer_t* buffer, gs_object_t* out); 
GS_API_DECL bool gs_texture_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data);

introspect()
typedef struct gs_font_t
{
	base(gs_asset_t)

	// Fields
	gs_asset_font_t font;

} gs_font_t;

introspect()
typedef struct gs_sound_t
{
    base(gs_asset_t)

	// Fields
	gs_asset_audio_t audio;

} gs_sound_t;

GS_API_DECL bool gs_sound_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data);

introspect()
typedef struct gs_pipeline_t	
{
    base(gs_asset_t)

    ctor({
        params(void),
        func({
            gs_println("PIPELINE CTOR");
        })
    })

    // Fields
    gs_gfxt_pipeline_t pipeline;
    gs_dyn_array(gs_gfxt_mesh_layout_t) mesh_layout;

} gs_pipeline_t;

GS_API_DECL gs_gfxt_pipeline_t* gs_get_pipeline_raw(GS_GFXT_HNDL hndl, void* user_data)
{
    gs_pipeline_t* pip = (gs_pipeline_t*)hndl;
    return &pip->pipeline;
}

GS_API_DECL bool gs_pipeline_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data);
GS_API_DECL gs_gfxt_mesh_import_options_t gs_pipeline_get_mesh_import_options(const gs_pipeline_t* pipe);

introspect()
typedef struct gs_material_t
{
	base(gs_asset_t)

    ctor({
        params(gs_asset_handle_t pip),
        func({
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
        })
    })

	// Fields 
    field()
    gs_asset_handle_t pipeline;

	gs_gfxt_material_t material;

} gs_material_t;

GS_API_DECL void gs_material_set_uniform(gs_material_t* mat, const char* name, void* data); 

#define gs_material_bind(CB, MAT)\
    gs_gfxt_material_bind((CB), &((MAT)->material))

#define gs_material_bind_uniforms(CB, MAT)\
    gs_gfxt_material_bind_uniforms((CB), &((MAT)->material)) 

// VTable functions
GS_API_DECL gs_result gs_material_serialize(gs_byte_buffer_t* buffer, gs_object_t* in);
GS_API_DECL gs_result gs_material_deserialize(gs_byte_buffer_t* buffer, gs_object_t* out); 

// Should these be assets as well?
/*
typedef struct material_instance_t
{
    base(gs_asset_t);

    uint32_t parent;            // Asset handle to parent material/instance
    gs_byte_buffer_t overrides; // Override of uniform data (don't want to copy data...)
} material_instance_t;
*/ 

typedef struct gs_asset_record_t
{
	base(gs_asset_t)

	// Fields
	uint32_t hndl;		        // Handle to asset slot array in storage
    char path[GS_ASSET_STR_MAX];   // Absolute path to asset on disk
    gs_uuid_t uuid;             // UUID for asset
    char name[GS_ASSET_STR_MAX];   // Qualified name for asset
} gs_asset_record_t	;

#define GS_ASSET_IMPORTER_FILE_EXTENSIONS_MAX 10
#define GS_ASSETS_FILE_EXTENSION_MAX_LENGTH 32

typedef struct gs_asset_importer_desc_t
{
	bool (* load_resource_from_file)(const char* path, gs_asset_t* out, void* user_data);
	char* file_extensions[GS_ASSET_IMPORTER_FILE_EXTENSIONS_MAX	];
	size_t file_extensions_size;
    char file_extension[GS_ASSETS_FILE_EXTENSION_MAX_LENGTH	];
} gs_asset_importer_desc_t;

typedef struct gs_asset_importer_t
{
	base(gs_object_t)

	gs_slot_array(gs_asset_record_t	) records;		// Slot array of asset records
	gs_hash_table(uint64_t, uint32_t) uuid2id;  // Lookup mapping from uuid to record slot id
	gs_hash_table(uint64_t, uint32_t) name2id;  // Lookup mapping from name to record slot id
	gs_slot_array(gs_asset_t*) assets;			    // Slot array of raw asset data (could try to come up with a way to not malloc this)

	bool (* load_resource_from_file)(const char* path, gs_asset_t* out, void* user_data);
	uint64_t asset_cls_id;
	size_t cls_sz;
    char file_extension[GS_ASSETS_FILE_EXTENSION_MAX_LENGTH	];
} gs_asset_importer_t;

typedef struct gs_asset_manager_t
{
	base(gs_object_t)

	// Fields
	char root_path[GS_ASSET_STR_MAX];
	gs_slot_array(gs_asset_importer_t*) importers;	    // Slot array of asset data
	gs_hash_table(uint64_t, uint32_t) cid2importer; // Mapping from cls id to importer data
	gs_hash_table(uint64_t, uint32_t) fe2importer;  // Mapping from file extension to importer data

} gs_asset_manager_t;

GS_API_DECL void gs_assets_init(gs_asset_manager_t* am, const char* root_path);
GS_API_DECL const char* assets_get_internal_file_extension(gs_asset_manager_t* am, const char* ext);
GS_API_DECL gs_asset_handle_t gs_assets_import(gs_asset_manager_t* am, const char* path, void* user_data, bool serialize_to_disk);
GS_API_DECL gs_asset_handle_t gs_assets_add_to_database(gs_asset_manager_t* am, gs_asset_t* asset, const char* dir, const char* name, bool serialize_to_disk);
GS_API_DECL gs_result gs_assets_serialize_asset(gs_asset_manager_t* am, const char* path, const gs_asset_t* in);
GS_API_DECL gs_result gs_assets_deserialize_asset(gs_asset_manager_t* am, const char*path, gs_asset_t* out);
GS_API_DECL void* gs_assets_get_data_internal(uint64_t cls_id);
GS_API_DECL  const gs_asset_t* _gs_assets_get_w_name_internal(const gs_asset_manager_t* am, uint64_t cid, const char* name);
GS_API_DECL void _gs_assets_register_importer_internal(gs_asset_manager_t* am, uint64_t cid, size_t cls_sz, gs_asset_importer_desc_t* desc); 

#define gs_assets_register_importer(ASSETS, T, DESC)\
	_gs_assets_register_importer_internal(ASSETS, gs_obj_sid(T), sizeof(T), DESC);

#define gs_assets_getp(ASSETS, T, NAME)\
	_gs_assets_get_w_name_internal(ASSETS, gs_hash_str64(gs_to_str(T)), NAME)

// Mechanism for getting asset manager instance
#define gs_asset_manager_instance() _g_asset_manager

#ifdef GS_ASSET_IMPL

// Global instance of asset manager
gs_asset_manager_t* _g_asset_manager = NULL; 

// Maps resource file extension to internal engine file extension
GS_API_DECL const char* assets_get_internal_file_extension(gs_asset_manager_t* am, const char* ext)
{
    // Find importer from file extension mapping
    uint64_t hash = gs_hash_str64(ext);
    bool exists = gs_hash_table_exists(am->fe2importer, hash);
    if (!exists)
    {
        gs_println("warning::gs_asset_manager_t::assets_get_internal_file_extension::%s not registered", ext);
        return "ass"; 
    } 

    // Get importer
    gs_asset_importer_t* importer = gs_slot_array_get(am->importers, gs_hash_table_get(am->fe2importer, hash)); 
    return importer->file_extension; 
}

GS_API_DECL const gs_asset_t* _gs_assets_get_w_name_internal(const gs_asset_manager_t* am, uint64_t cid, const char* name)
{
	if (!gs_hash_table_exists(am->cid2importer, cid)) 
	{
		gs_timed_action(60, {
			gs_println("error::gs_asset_manager_t	::getp:: asset type t doesn't exist: %s", name);
		});
		return NULL;
	}

	// Get the storage
	uint32_t shndl = gs_hash_table_get(am->cid2importer, cid);
	gs_asset_importer_t* importer = gs_slot_array_get(am->importers, shndl);
	gs_assert(importer);

	// Get the asset from storage by name
	// TODO(john): Need to load asset if not loaded by default yet	
	uint64_t hash = gs_hash_str64(name);	
	if (!gs_hash_table_exists(importer->name2id, hash))
	{
		gs_timed_action(60, {
			gs_println("error::gs_asset_manager_t	::getp::asset doesn't exist: %s", name);
		});
		return NULL;
	}

	uint32_t rhndl = gs_hash_table_get(importer->name2id, hash);
	const gs_asset_record_t* record = gs_slot_array_getp(importer->records, rhndl);
	gs_assert(record);

	const gs_asset_t* asset = gs_slot_array_get(importer->assets, record->hndl);
	return asset;
}

GS_API_DECL void _gs_assets_register_importer_internal(gs_asset_manager_t* am, uint64_t cid, size_t cls_sz, gs_asset_importer_desc_t* desc)
{
	gs_asset_importer_t* importer = gs_malloc_init(gs_asset_importer_t	);	
	importer->load_resource_from_file = desc->load_resource_from_file;
	importer->asset_cls_id = cid;
	importer->cls_sz = cls_sz;
    memcpy(importer->file_extension, desc->file_extension ? desc->file_extension : "ass", GS_ASSETS_FILE_EXTENSION_MAX_LENGTH);
	uint32_t hndl = gs_slot_array_insert(am->importers, importer);
	gs_hash_table_insert(am->cid2importer, cid, hndl);
	uint32_t ct = desc->file_extensions_size ? desc->file_extensions_size / sizeof(char*) : 0;
	for (uint32_t i = 0; i < ct; ++i)
	{
		gs_hash_table_insert(am->fe2importer, gs_hash_str64(desc->file_extensions[i]), hndl);
	}
}

GS_API_DECL gs_asset_handle_t gs_assets_import(gs_asset_manager_t* am, const char* path, void* user_data, bool serialize_to_disk)	
{
	// Create record for asset, set path to asset using qualified name
	gs_asset_record_t record = {0};

    // Asset handle to create and return
    gs_asset_handle_t asset_hndl = gs_asset_handle_invalid();

	// Get importer from importers
	gs_transient_buffer(FILE_EXT, 10);
	gs_platform_file_extension(FILE_EXT, 10, path);

	if (!gs_hash_table_exists(am->fe2importer, gs_hash_str64(FILE_EXT)))
	{
        gs_println("error::asset_import::impoter does not exist for file extension %s", FILE_EXT);
		return asset_hndl;
	}

	// Get asset storage
	uint32_t importer_hndl = gs_hash_table_get(am->fe2importer, gs_hash_str64(FILE_EXT));
	gs_asset_importer_t	* importer = gs_slot_array_get(am->importers, importer_hndl); 

	// Get class id from storage
	uint64_t id = importer->asset_cls_id;

	// Get absolute path to asset
	gs_snprintfc(PATH, GS_ASSET_STR_MAX, "%s/%s", am->root_path, path);

	// Get qualified name of asset
	gs_transient_buffer(QUAL_NAME, GS_ASSET_STR_MAX);
	gs_asset_qualified_name(path, QUAL_NAME, GS_ASSET_STR_MAX);
	memcpy(record.name, QUAL_NAME, GS_ASSET_STR_MAX);

	// Create final save path for asset
	gs_transient_buffer(FINAL_PATH_TMP, GS_ASSET_STR_MAX);
	gs_transient_buffer(FINAL_PATH, GS_ASSET_STR_MAX);
	gs_snprintf(FINAL_PATH_TMP, GS_ASSET_STR_MAX, "%s/%s", am->root_path, QUAL_NAME);
	gs_util_string_replace((FINAL_PATH_TMP + 1), (FINAL_PATH + 1), GS_ASSET_STR_MAX, '.', '/');
	FINAL_PATH[0] = '.';

	// Get file extension from registered mappings
	const char* file_ext = assets_get_internal_file_extension(am, FILE_EXT);
	gs_snprintf(record.path, GS_ASSET_STR_MAX, "%s.%s", FINAL_PATH, file_ext);

       // Generate uuid for asset
	record.uuid = gs_platform_uuid_generate(); 

	// Need to construct asset type here using vtable
    gs_asset_t* asset = gs_obj_newid(id); 
	gs_assert(asset); 

	// Construct raw asset (this will also place into storage and give asset the record's handle)
	bool loaded = importer->load_resource_from_file(PATH, asset, user_data); 
	if (loaded)
	{
        gs_println("asset_import::imported %s to %s", path, record.path);

		// Insert into data array
		uint32_t hndl = gs_slot_array_insert(importer->assets, asset);

		// Set up tables
		gs_transient_buffer(UUID_BUF, 34);
		gs_platform_uuid_to_string(UUID_BUF, &record.uuid);
		gs_hash_table_insert(importer->uuid2id, gs_hash_str64(UUID_BUF), hndl);
		gs_hash_table_insert(importer->name2id, gs_hash_str64(record.name), hndl); 

        // Assign asset handle to record
        record.hndl = hndl;

		// Store record in storage
		uint32_t rhndl = gs_slot_array_insert(importer->records, record);

		// Set asset record hndl
		asset->record_hndl = rhndl; 

		// Serialize asset to disk
        if (serialize_to_disk)
        {
		    gs_assets_serialize_asset(am, record.path, asset);
        }

        // Set asset handle data
        asset_hndl.hndl = hndl; 
        asset_hndl.importer = importer_hndl;
	}

    return asset_hndl;
}

GS_API_DECL gs_asset_handle_t gs_assets_add_to_database(gs_asset_manager_t* am, gs_asset_t* asset, const char* dir, const char* name, bool serialize_to_disk)
{
	// Create record for asset, set path to asset using qualified name
	gs_asset_record_t record = gs_default_val();

    // Asset handle to create and return
    gs_asset_handle_t asset_hndl = gs_asset_handle_invalid();

    if (!asset)
    { 
        gs_println("error::gs_assets_add_to_database::asset id %zu does not exist.", gs_obj_id(asset));
        return asset_hndl;
    } 

    if (!gs_hash_table_key_exists(am->cid2importer, gs_obj_id(asset)))
    {
        gs_println("error::gs_assets_add_to_database::asset id %zu does not exist.", gs_obj_id(asset));
        return asset_hndl;
    }

	// Get asset storage
	uint32_t importer_hndl = gs_hash_table_get(am->cid2importer, gs_obj_id(asset));
	gs_asset_importer_t* importer = gs_slot_array_get(am->importers, importer_hndl); 

	// Get class id from storage
	uint64_t id = importer->asset_cls_id;

    // Get relative path to asset
    gs_snprintfc(REL_PATH, GS_ASSET_STR_MAX, "%s/%s.%s", dir, name, importer->file_extension);

    // Get absolute directory
    gs_snprintfc(ABS_DIR, GS_ASSET_STR_MAX, "%s/%s/", am->root_path, dir);

	// Get absolute path to asset
	gs_snprintfc(ABS_PATH, GS_ASSET_STR_MAX, "%s/%s", am->root_path, REL_PATH); 

    // Copy final path
	gs_snprintf(record.path, GS_ASSET_STR_MAX, "%s", ABS_PATH);

	// Get qualified name of asset
	gs_transient_buffer(QUAL_NAME, GS_ASSET_STR_MAX);
	gs_asset_qualified_name(REL_PATH, QUAL_NAME, GS_ASSET_STR_MAX);
	memcpy(record.name, QUAL_NAME, GS_ASSET_STR_MAX); 

    // Generate uuid for asset
	record.uuid = gs_platform_uuid_generate(); 

    // Add to database
    gs_println("gs_assets_add_to_database::asset %s", name);

    // Insert into data array
    uint32_t hndl = gs_slot_array_insert(importer->assets, asset);

    // Set up tables
    gs_transient_buffer(UUID_BUF, 34);
    gs_platform_uuid_to_string(UUID_BUF, &record.uuid);
    gs_hash_table_insert(importer->uuid2id, gs_hash_str64(UUID_BUF), hndl);
    gs_hash_table_insert(importer->name2id, gs_hash_str64(record.name), hndl); 

    // Assign asset handle to record
    record.hndl = hndl;

    // Store record in storage
    uint32_t rhndl = gs_slot_array_insert(importer->records, record);

    // Set asset record hndl
    asset->record_hndl = rhndl; 

    // Serialize asset to disk
    if (serialize_to_disk)
    {
        DIR* _dir = opendir(ABS_DIR);
        if (!_dir) {
            mkdir(ABS_DIR, S_IWRITE | S_IREAD);
        }

        gs_assets_serialize_asset(am, record.path, asset);
    }

    // Set asset handle data
    asset_hndl.hndl = hndl; 
    asset_hndl.importer = importer_hndl;

    // Return asset handle
    return asset_hndl;
}

GS_API_DECL gs_result gs_assets_serialize_asset(gs_asset_manager_t* am, const char* path, const gs_asset_t* in)
{ 
    // Get class id
    uint64_t id = gs_obj_id(in);

    // Get asset importer based on type of asset
    uint32_t sid = gs_hash_table_get(am->cid2importer, id);
    gs_asset_importer_t	* importer = gs_slot_array_get(am->importers, sid);
    const gs_asset_record_t	* record = gs_slot_array_getp(importer->records, in->record_hndl);

	gs_byte_buffer_t bb = gs_byte_buffer_new();

	// === Object Header === //
	gs_byte_buffer_write(&bb, uint64_t, id);	// Class id (not sure about this) should write out class name instead?

	// === Asset Header === //
	gs_byte_buffer_write(&bb, gs_uuid_t, record->uuid);
	gs_byte_buffer_write_str(&bb, record->name);

	// Serialize asset data 
    gs_obj_serialize_func serialize = gs_obj_func_w_id(id, gs_obj_serialize);
    gs_result res = (*serialize)(&bb, in);
		
	// Default serialization if no serializer provider
	if (res == GS_RESULT_INCOMPLETE)
	{
        res = gs_object_serialize_default(&bb, in);
	} 

	// Write to file
	gs_byte_buffer_write_to_file(&bb, path);

	// Free buffer
	gs_byte_buffer_free(&bb);

	return GS_RESULT_SUCCESS;
}

/*
gs_result gs_asset_manager_t	::deserialize_asset(const char* path, gs_asset_t* out)
{ 
    // NOTE(john): Object should already be instantiated.
    gs_assert(out);

    // Cache global asset manager instance
    gs_asset_manager_t	* am = gs_asset_manager_instance();

	gs_byte_buffer_t bb = gs_byte_buffer_new();

	// Read buffer from file
	gs_byte_buffer_read_from_file(&bb, path);

	// === Object Header === //
	gs_byte_buffer_readc(&bb, uint64_t, id);	// Class id

    // Get storage based on id, need a record handle somehow. Don't have that yet.
    // Let's assume the asset has a record handle. It should, since we place that on load.  
	uint32_t sid = am->cid2assets.get(id);
    asset_storage_base_t* storage = am->assets.get(sid);
    const gs_asset_record_t	* record = storage->records.getp(out->record_hndl);

	// === Asset Header === //
	gs_byte_buffer_read(&bb, gs_uuid_t, &record->uuid);
	gs_byte_buffer_read_str(&bb, (char*)record->name);

	// Serialize asset data 
	gs_result res = out->deserialize(&bb);	
	
	// Default serialization if no serializer provider
	if (res == GS_RESULT_INCOMPLETE)
	{
		gs_object_t	::deserialize_default(&bb, out);
	}

	// Free buffer
	gs_byte_buffer_free(&bb);

	return GS_RESULT_SUCCESS;
} 
*/

void gs_asset_recurse_dir(const char* path, DIR* dir)
{
	struct dirent* ent = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		switch (ent->d_type)
		{
			case DT_REG:
			{
				// Files
				gs_println("reg: %s", ent->d_name);
			} break;

			case DT_DIR:
			{
				// Skip these
				if (gs_string_compare_equal(ent->d_name, ".") || gs_string_compare_equal(ent->d_name, ".."))
				{
					continue;
				}
				
				gs_snprintfc(DIRPATH, GS_ASSET_STR_MAX, "%s/%s", path, ent->d_name);
				gs_println("dir: %s", DIRPATH);
				DIR* cdir = opendir(DIRPATH);
				if (cdir)
				{
					gs_asset_recurse_dir(DIRPATH, cdir);
				}
				closedir(cdir);
			} break;

			case DT_LNK:
			{
				gs_println("link: %s", ent->d_name);
			} break;

			default:
			{
				gs_println("def: %s", ent->d_name);
			} break;
		}
	}
}

// Set root path, begin importing all assets
GS_API_DECL void gs_assets_init(gs_asset_manager_t* am, const char* path)
{
    // Set global asset manager instance
    _g_asset_manager = am;

	// Clear all previous records, if necessary
	memcpy(am->root_path, path, GS_ASSET_STR_MAX);

	// Register texture importer
	gs_assets_register_importer(am, gs_texture_t, (&(gs_asset_importer_desc_t){
		.load_resource_from_file = gs_texture_load_resource_from_file,
		.file_extensions = {"png", "jpg"},
		.file_extensions_size = 2 * sizeof(char*),
        .file_extension = "tex"
	}));

    // Register audio importer
    gs_assets_register_importer(am, gs_sound_t, (&(gs_asset_importer_desc_t){
        .load_resource_from_file = gs_sound_load_resource_from_file,
        .file_extensions = {"ogg", "wav", "mp3"}, 
        .file_extensions_size = 3 * sizeof(char*),
        .file_extension = "aud"
    })); 

    // Register pipeline importer
    gs_assets_register_importer(am, gs_pipeline_t, (&(gs_asset_importer_desc_t){
        .load_resource_from_file = gs_pipeline_load_resource_from_file,
        .file_extensions = {"sf"}, 
        .file_extensions_size = 1 * sizeof(char*),
        .file_extension = "pip"
    })); 

    // Register material importer
    gs_assets_register_importer(am, gs_material_t, (&(gs_asset_importer_desc_t){
        .file_extension = "mat"
    })); 

    // Register mesh importer
    gs_assets_register_importer(am, gs_mesh_t, (&(gs_asset_importer_desc_t){
        .load_resource_from_file = gs_mesh_load_resource_from_file,
        .file_extensions = {"glb", "gltf"}, 
        .file_extensions_size = 2 * sizeof(char*),
        .file_extension = "msh"
    })); 

	// Open directory
	DIR* dir = opendir(path);
	if (!dir) {
		gs_println("error::gs_asset_manager_t	::init::could not open path: %s", path);
		return;
	}

    // Recursive through directory structure for assets
	gs_asset_recurse_dir(path, dir);

	// Close dir
	closedir(dir);
}

typedef struct string_split_t 
{
	uint32_t start;
	uint32_t count;
} string_split_t;

GS_API_DECL void gs_asset_qualified_name(const char* src, char* dst, size_t sz)
{
    // Need to remove extension
    uint32_t idx = 0;
    gs_transient_buffer(TMP, 1024);
    for (uint32_t i = gs_string_length(src) - 1; i >= 0; --i) {
        if (src[i] == '.') {
            idx = i;
            break;
        }
    }
    gs_util_string_substring(src, TMP, 1024, 0, idx);

    // Split string
    gs_dyn_array(string_split_t) splits = NULL;
    gs_dyn_array_reserve(splits, 1);

    // Take in delimiter character, then split based on that
    size_t len = gs_string_length(TMP);
    uint32_t start = 0;
	uint32_t rem = 0;
    for (uint32_t i = 0; i < len; ++i)
    {
        if (TMP[i] == '/') {
            string_split_t split = gs_default_val();
			split.start = start;
			split.count = i - start;
            gs_dyn_array_push(splits, split);
            start = i;
			rem = len - start;
        }
    }
	// Push last bit into split
	string_split_t split = {0};
	split.start = start;
	split.count = rem;
	gs_dyn_array_push(splits, split);

    // If no splits, then push back entire string into split
    if (gs_dyn_array_empty(splits)) {
        string_split_t split = gs_default_val();
		split.start = 0; split.count = len;
        gs_dyn_array_push(splits, split);
    }
	else
	{
		// For each split, print
		uint32_t c = 0;
		gs_for_range_i(gs_dyn_array_size(splits))
		{
			string_split_t* s = &splits[i];
			gs_transient_buffer(TMP2, GS_ASSET_STR_MAX);
			gs_transient_buffer(TMP3, GS_ASSET_STR_MAX);
			memcpy(TMP2, (TMP + s->start), s->count);
			gs_util_string_replace(TMP2, TMP3, GS_ASSET_STR_MAX, '/', '.');
			memcpy((dst + c), TMP3, s->count);
			c += s->count;
		}

		// Need the last remainder of the string as well
		gs_dyn_array_free(splits);
	}
}

//=======[ Asset Handle ]==============================================================

GS_API_DECL gs_asset_handle_t gs_asset_handle_invalid()
{
    return (gs_asset_handle_t){
        .hndl = UINT32_MAX,
        .importer = UINT32_MAX
    };
}

GS_API_DECL gs_asset_handle_t gs_asset_handle_create(const gs_asset_t* asset)
{ 
    // Get asset manager instance
    gs_asset_manager_t* am = gs_asset_manager_instance(); 

    // Get asset importer based on type of asset
    const uint32_t id = gs_obj_id(asset);
    uint32_t iid = gs_hash_table_get(am->cid2importer, id);
    gs_asset_importer_t	* importer = gs_slot_array_get(am->importers, iid);

    // Get record for asset
    const gs_asset_record_t* record = gs_slot_array_getp(importer->records, asset->record_hndl); 

    // Construct asset handle
    gs_asset_handle_t hndl = (gs_asset_handle_t	){
        .hndl = record->hndl, 
        .importer = iid
    };

    return hndl;
}

GS_API_DECL gs_asset_t* gs_asset_handle_get(gs_asset_handle_t* hndl)
{
    // Get raw asset from slot handles 
    const gs_asset_manager_t* am = gs_asset_manager_instance();
    const gs_asset_importer_t* importer = gs_slot_array_get(am->importers, hndl->importer);
    return gs_slot_array_get(importer->assets, hndl->hndl);
}

//=======[ Texture ]==================================================================

GS_API_DECL bool gs_texture_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data)
{
	// Need to load up texture data, store in storage (slot array), then return pointer to asset for serialization.
	gs_graphics_texture_desc_t* desc = (gs_graphics_texture_desc_t*)user_data;		

	// Load texture data from file, keep data	
	gs_texture_t* t = (gs_texture_t*)out;
	gs_asset_texture_t* tex = &t->texture;
	bool loaded = gs_asset_texture_load_from_file(path, tex, desc, false, true);

	if (!loaded)
	{
		// Error
		gs_println("error::assets_texture_t_load_resource_from_file:: texture: %s not loaded.", path);
		gs_free(t);
		return false;
	}

	return true;
} 

GS_API_DECL gs_result gs_texture_serialize(gs_byte_buffer_t* buffer, const gs_object_t* in)
{
    gs_println("SERIALIZE!");
    return GS_RESULT_INCOMPLETE;
	const gs_texture_t* t = (gs_texture_t*)in;
	const gs_asset_texture_t* tex = &t->texture;

    // Verify that data is available first in desc
    if (!tex->desc.data) 
	{
        gs_println("error:assets_texture_t::serialize:: texture desc data is NULL");
        return GS_RESULT_FAILURE;
    }

    // Write out desc information
    gs_byte_buffer_write(buffer, uint32_t, tex->desc.width);                                 // Width
    gs_byte_buffer_write(buffer, uint32_t, tex->desc.height);                                // Height
    gs_byte_buffer_write(buffer, gs_graphics_texture_format_type, tex->desc.format);         // Texture Format
    gs_byte_buffer_write(buffer, gs_graphics_texture_wrapping_type, tex->desc.wrap_s);       // S Wrap
    gs_byte_buffer_write(buffer, gs_graphics_texture_wrapping_type, tex->desc.wrap_t);       // T Wrap
    gs_byte_buffer_write(buffer, gs_graphics_texture_filtering_type, tex->desc.min_filter);  // Min Filter Format
    gs_byte_buffer_write(buffer, gs_graphics_texture_filtering_type, tex->desc.mag_filter);  // Mag Filter Format
    gs_byte_buffer_write(buffer, uint32_t, tex->desc.num_mips);                              // Num Mips

    // TODO(): Need to switch on format type to get this information
    uint32_t num_comps = 4;
    size_t sz = tex->desc.width * tex->desc.height * 4;

    // Write out data
    gs_byte_buffer_write_bulk(buffer, tex->desc.data, sz);

	// Serialize texture data
	return GS_RESULT_SUCCESS;
}

GS_API_DECL gs_result gs_texture_deserialize(gs_byte_buffer_t* buffer, gs_object_t	* out)
{
    gs_println("DESERIALIZE!");
    return GS_RESULT_INCOMPLETE;
	// Deserialize texture data
	gs_texture_t* t = (gs_texture_t*)out;
	gs_asset_texture_t* tex = &t->texture;

    // Read in desc information
    gs_byte_buffer_read(buffer, uint32_t, &tex->desc.width);                                 // Width
    gs_byte_buffer_read(buffer, uint32_t, &tex->desc.height);                                // Height
    gs_byte_buffer_read(buffer, gs_graphics_texture_format_type, &tex->desc.format);         // Texture Format
    gs_byte_buffer_read(buffer, gs_graphics_texture_wrapping_type, &tex->desc.wrap_s);       // S Wrap
    gs_byte_buffer_read(buffer, gs_graphics_texture_wrapping_type, &tex->desc.wrap_t);       // T Wrap
    gs_byte_buffer_read(buffer, gs_graphics_texture_filtering_type, &tex->desc.min_filter);  // Min Filter Format
    gs_byte_buffer_read(buffer, gs_graphics_texture_filtering_type, &tex->desc.mag_filter);  // Mag Filter Format
    gs_byte_buffer_read(buffer, uint32_t, &tex->desc.num_mips);                              // Num Mips

    // TODO(): Need to switch on format type to get this information
    uint32_t num_comps = 4;
    size_t sz = tex->desc.width * tex->desc.height * 4;

    // Allocate texture data
    tex->desc.data = gs_malloc(sz);

    // Read in texture data
    gs_byte_buffer_read_bulk(buffer, &tex->desc.data, sz);

    // Construct graphics texture handle
    tex->hndl = gs_graphics_texture_create(&tex->desc);

    // Free texture data
    gs_free(tex->desc.data);
	
	return GS_RESULT_SUCCESS;
}

//=======[ Audio ]====================================================================

GS_API_DECL bool gs_sound_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data)
{ 
    gs_sound_t* sound = (gs_sound_t*)out;  
	return gs_asset_audio_load_from_file(path, &sound->audio);
}

//=======[ Font ]=====================================================================

GS_API_DECL bool gs_font_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data)
{
	// Need to load up data, store in storage (slot array), then return pointer to asset for serialization.
	gs_font_t* font = (gs_font_t*)out;
	return gs_asset_font_load_from_file(path, &font->font, user_data ? *((uint32_t*)user_data) : 12);
}

//=======[ Mesh ]=====================================================================

GS_API_DECL bool gs_mesh_load_resource_from_file(const char* path, gs_asset_t* out, void* import_options /*gs_gfxt_mesh_import_options_t*/)
{
	// Need to load up data, store in storage (slot array), then return pointer to asset for serialization.
	gs_mesh_t* mesh = (gs_mesh_t*)out;
	mesh->mesh = gs_gfxt_mesh_load_from_file(path, import_options);
	return true;
} 

//=======[ Material ]================================================================= 

GS_API_DECL void gs_material_set_uniform(gs_material_t* mat, const char* name, void* data)
{
    gs_gfxt_material_set_uniform(&mat->material, name, data);
}

//=======[ Pipeline ]================================================================= 

typedef struct tmp_buffer_t
{
    char txt[1024]; 
} tmp_buffer_t; 

typedef struct gs_shader_io_data_t
{
    char type[64];
    char name[64];
} gs_shader_io_data_t;

typedef struct gs_pipeline_parse_data_t 
{ 
    gs_dyn_array(gs_shader_io_data_t) io_list[3];
    gs_dyn_array(gs_gfxt_mesh_layout_t) mesh_layout;
    char* code[3];
} gs_ppd_t; 

#define gs_parse_warning(TXT, ...)\
    do {\
        gs_printf("WARNING::");\
        gs_printf(TXT, ##__VA_ARGS__);\
        gs_println("");\
    } while (0)

#define gs_parse_error(TXT, ASSERT, ...)\
    do {\
        gs_printf("ERROR::");\
        gs_printf(TXT, ##__VA_ARGS__);\
        gs_println("");\
        if (ASSERT) gs_assert(false);\
    } while (0)

#define gs_parse_block(NAME, ...)\
    do {\
        gs_println("gs_pipeline_load_resource_from_file::parsing::%s", #NAME);\
        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LBRACE))\
        {\
            gs_println("error::gs_pipeline_load_resource_from_file::error parsing raster from .sf resource");\
            gs_assert(false);\
        }\
\
        uint32_t bc = 1;\
        while (bc)\
        {\
            gs_token_t token = lex->next_token(lex);\
            switch (token.type)\
            {\
                case GS_TOKEN_LBRACE: {bc++;} break;\
                case GS_TOKEN_RBRACE: {bc--;} break;\
\
                case GS_TOKEN_IDENTIFIER:\
                {\
                    __VA_ARGS__\
                }\
            }\
        }\
    } while (0)

const char* gs_get_vertex_attribute_string(gs_graphics_vertex_attribute_type type)
{ 
    switch (type)
    {
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT:   return "float"; break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2:  return "vec2";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT3:  return "vec3";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT4:  return "vec4";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT:    return "int";   break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT2:   return "vec2";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT3:   return "vec3";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT4:   return "vec4";  break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE:    return "float"; break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE2:   return "vec2"; break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE3:   return "vec3"; break;
        case GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE4:   return "vec4"; break;
        default: return "UNKNOWN"; break;
    }
}

gs_graphics_vertex_attribute_type gs_get_vertex_attribute_from_token(const gs_token_t* t)
{ 
    if (gs_token_compare_text(t, "float"))       return GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT;
    else if (gs_token_compare_text(t, "float2")) return GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2;
    else if (gs_token_compare_text(t, "float3")) return GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT3;
    else if (gs_token_compare_text(t, "float4")) return GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT4;
    else if (gs_token_compare_text(t, "uint4"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT4;
    else if (gs_token_compare_text(t, "uint3"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT3;
    else if (gs_token_compare_text(t, "uint2"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT2;
    else if (gs_token_compare_text(t, "uint"))   return GS_GRAPHICS_VERTEX_ATTRIBUTE_UINT;
    else if (gs_token_compare_text(t, "byte4"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE4;
    else if (gs_token_compare_text(t, "byte3"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE3;
    else if (gs_token_compare_text(t, "byte2"))  return GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE2;
    else if (gs_token_compare_text(t, "byte"))   return GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE;
    return 0x00;
}

gs_graphics_uniform_type gs_uniform_type_from_token(const gs_token_t* t)
{
    if (gs_token_compare_text(t, "float"))               return GS_GRAPHICS_UNIFORM_FLOAT; 
    else if (gs_token_compare_text(t, "int"))            return GS_GRAPHICS_UNIFORM_INT;
    else if (gs_token_compare_text(t, "vec2"))           return GS_GRAPHICS_UNIFORM_VEC2;
    else if (gs_token_compare_text(t, "vec3"))           return GS_GRAPHICS_UNIFORM_VEC3; 
    else if (gs_token_compare_text(t, "vec4"))           return GS_GRAPHICS_UNIFORM_VEC4; 
    else if (gs_token_compare_text(t, "mat4"))           return GS_GRAPHICS_UNIFORM_MAT4; 
    else if (gs_token_compare_text(t, "sampler2D"))      return GS_GRAPHICS_UNIFORM_SAMPLER2D; 
    else if (gs_token_compare_text(t, "img2D_rgba32f"))  return GS_GRAPHICS_UNIFORM_IMAGE2D_RGBA32F; 
    return 0x00;
}

const char* gs_uniform_string_from_type(gs_graphics_uniform_type type)
{
    switch (type)
    {
        case GS_GRAPHICS_UNIFORM_FLOAT:           return "float"; break; 
        case GS_GRAPHICS_UNIFORM_INT:             return "int"; break;
        case GS_GRAPHICS_UNIFORM_VEC2:            return "vec2"; break;
        case GS_GRAPHICS_UNIFORM_VEC3:            return "vec3"; break; 
        case GS_GRAPHICS_UNIFORM_VEC4:            return "vec4"; break; 
        case GS_GRAPHICS_UNIFORM_MAT4:            return "mat4"; break;
        case GS_GRAPHICS_UNIFORM_SAMPLER2D:       return "sampler2D"; break; 
        case GS_GRAPHICS_UNIFORM_IMAGE2D_RGBA32F: return "image2D"; break; 
        default: return "UNKNOWN"; break;
    }
    return 0x00;
}

void gs_parse_uniforms(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd, gs_graphics_shader_stage_type stage)
{
    uint32_t image_binding = 0;

    gs_parse_block(
    PIPELINE::UNIFORMS,
    {
        gs_gfxt_uniform_desc_t uniform = {0};
        uniform.type = gs_uniform_type_from_token(&token); 
        uniform.stage = stage;

        switch (uniform.type)
        {
            default: break;

            case GS_GRAPHICS_UNIFORM_SAMPLER2D:
            case GS_GRAPHICS_UNIFORM_IMAGE2D_RGBA32F:
            {
                uniform.binding = image_binding++;
            } break;
        } 

        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) 
        { 
            gs_assert(false);
        } 
        token = lex->current_token;

        memcpy(uniform.name, token.text, token.len);

        // Add uniform to ublock descriptor
        gs_dyn_array_push(desc->ublock_desc.layout, uniform); 
    });
}

void gs_parse_in(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd, gs_graphics_shader_stage_type type)
{
    gs_parse_block(
    PIPELINE::IN,
    {
    });
}

void gs_parse_io(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd, gs_graphics_shader_stage_type type)
{
    gs_parse_block(
    PIPELINE::IO,
    {
        gs_shader_io_data_t io = {0}; 
        memcpy(io.type, token.text, token.len);

        switch (type)
        {
            case GS_GRAPHICS_SHADER_STAGE_VERTEX:
            {
                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) 
                { 
                    gs_parse_error(false, "PIPELINE::IO::expected identifier name after type.");
                } 
                token = lex->current_token;
                memcpy(io.name, token.text, token.len);
                gs_dyn_array_push(ppd->io_list[0], io);
            } break;

            case GS_GRAPHICS_SHADER_STAGE_FRAGMENT:
            {
                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER)) 
                {
                    gs_parse_error(false, "PIPELINE::IO::expected identifier name after type.");
                }
                token = lex->current_token;
                memcpy(io.name, token.text, token.len);
                gs_dyn_array_push(ppd->io_list[1], io);
            } break;

            case GS_GRAPHICS_SHADER_STAGE_COMPUTE:
            {
                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_NUMBER)) 
                {
                    gs_parse_error(false, "PIPELINE::IO::expected number after type.");
                }
                token = lex->current_token;
                memcpy(io.name, token.text, token.len);
                gs_dyn_array_push(ppd->io_list[2], io);
            } break;
        } 
    }); 
}

void gs_parse_code(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd, gs_graphics_shader_stage_type stage)
{
	if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LBRACE)) 
    { 
        gs_assert(false);
    } 

    uint32_t bc = 1; 
    gs_token_t cur = lex->next_token(lex);
    gs_token_t token = lex->current_token;
    while (bc)
    {
        switch (token.type)
        { 
            case GS_TOKEN_LBRACE: {bc++;} break; 
            case GS_TOKEN_RBRACE: {bc--;} break; 
        }
        token = lex->next_token(lex);
    }

    const size_t sz = (size_t)(token.text - cur.text - 1);
    char* code = gs_malloc(sz + 1);
    memset(code, 0, sz);
    memcpy(code, cur.text, sz - 1);

    switch (stage)
    {
        case GS_GRAPHICS_SHADER_STAGE_VERTEX: ppd->code[0]   = code; break; 
        case GS_GRAPHICS_SHADER_STAGE_FRAGMENT: ppd->code[1] = code; break;
        case GS_GRAPHICS_SHADER_STAGE_COMPUTE: ppd->code[2] = code; break;
    }
}

gs_gfxt_mesh_attribute_type gs_mesh_attribute_type_from_token(const gs_token_t* token)
{
    if (gs_token_compare_text(token, "POSITION"))       return GS_GFXT_MESH_ATTRIBUTE_TYPE_POSITION;
    else if (gs_token_compare_text(token, "NORMAL"))    return GS_GFXT_MESH_ATTRIBUTE_TYPE_NORMAL;
    else if (gs_token_compare_text(token, "TEXCOORD"))  return GS_GFXT_MESH_ATTRIBUTE_TYPE_TEXCOORD;
    else if (gs_token_compare_text(token, "COLOR"))     return GS_GFXT_MESH_ATTRIBUTE_TYPE_COLOR;

    // Default
    return 0x00;
    // else if (gs_token_compare_text(token, "TANGENT"))   return GS_GFXT_MESH_ATTRIBUTE_TYPE_TANGENT;
    // else if (gs_token_compare_text(token, "JOINT"))     return GS_GFXT_MESH_ATTRIBUTE_TYPE_JOINT;
    // else if (gs_token_compare_text(token, "WEIGHT"))    return GS_GFXT_MESH_ATTRIBUTE_TYPE_WEIGHT;
} 

void gs_parse_vertex_buffer_attributes(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{
    gs_parse_block(
    PIPELINE::VERTEX_BUFFER_ATTRIBUTES,
    {
    });
}

void gs_parse_vertex_mesh_attributes(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{
	if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LBRACE)) 
    { 
        gs_assert(false);
    } 

    uint32_t bc = 1; 
    while (bc)
    {
        gs_token_t token = lex->next_token(lex);
        switch (token.type)
        { 
            case GS_TOKEN_LBRACE: {bc++;} break; 
            case GS_TOKEN_RBRACE: {bc--;} break;
            
            case GS_TOKEN_IDENTIFIER: 
            {
                // Get mesh attribute type from  
                gs_gfxt_mesh_attribute_type mesh_type = gs_mesh_attribute_type_from_token(&token);

                // Build vertex attribute desc
                gs_graphics_vertex_attribute_desc_t attr = {0}; 
                // attr.format = gs_get_vertex_attribute_from_token(&token); 

                // Get attribute name
                if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
                {
                    gs_assert(false);
                } 

                token = lex->current_token;
                memcpy(attr.name, token.text, token.len); 

                switch (mesh_type)
                {
                    default: 
                    {
                    } break;

                    case GS_GFXT_MESH_ATTRIBUTE_TYPE_POSITION: 
                    {
                        attr.format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT3; 
                    } break;

                    case GS_GFXT_MESH_ATTRIBUTE_TYPE_NORMAL: 
                    {
                        attr.format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT3; 
                    } break;

                    case GS_GFXT_MESH_ATTRIBUTE_TYPE_TEXCOORD:
                    {
                        attr.format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2; 
                    } break;

                    case GS_GFXT_MESH_ATTRIBUTE_TYPE_COLOR:
                    {
                        attr.format = GS_GRAPHICS_VERTEX_ATTRIBUTE_BYTE4; 
                    } break;

                    /*
                    GS_GFXT_MESH_ATTRIBUTE_TYPE_TANGENT,
                    GS_GFXT_MESH_ATTRIBUTE_TYPE_JOINT,
                    GS_GFXT_MESH_ATTRIBUTE_TYPE_WEIGHT,
                    */
                }
                
                // Push back mesh buffer
                gs_dyn_array_push(ppd->mesh_layout, (gs_gfxt_mesh_layout_t){.type = mesh_type}); 

                // Push back into layout
                gs_dyn_array_push(desc->pip_desc.layout.attrs, attr);


                // TODO(): Need to do idx as well for later...
            }
        }
    }
}

void gs_parse_vertex_attributes(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{
	if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LBRACE)) 
    { 
        gs_assert(false);
    } 

    uint32_t bc = 1; 
    while (bc)
    {
        gs_token_t token = lex->next_token(lex);
        switch (token.type)
        { 
            case GS_TOKEN_LBRACE: {bc++;} break; 
            case GS_TOKEN_RBRACE: {bc--;} break;
            
            case GS_TOKEN_IDENTIFIER: {

                // Parse mesh attributes
                if (gs_token_compare_text(&token, "mesh"))
                {
                    gs_parse_vertex_mesh_attributes(lex, desc, ppd);
                }

                // Parse buffer attributes
                else if (gs_token_compare_text(&token, "buffer"))
                {
                    gs_parse_vertex_buffer_attributes(lex, desc, ppd);
                } 

            } break;
        }
    }
}

void gs_parse_shader_stage(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd, gs_graphics_shader_stage_type stage)
{
    gs_parse_block(
    PIPELINE::SHADER_STAGE,
    {
        if (stage == GS_GRAPHICS_SHADER_STAGE_VERTEX && 
             gs_token_compare_text(&token, "attributes"))
        {
            gs_println("parsing attributes...");
            gs_parse_vertex_attributes(lex, desc, ppd);
        }

        else if (gs_token_compare_text(&token, "uniforms"))
        {
            gs_parse_uniforms(lex, desc, ppd, stage);
        }

        else if (gs_token_compare_text(&token, "out"))
        {
            gs_parse_io(lex, desc, ppd, stage);
        }

        else if (gs_token_compare_text(&token, "in"))
        {
            gs_parse_io(lex, desc, ppd, stage);
        }

        else if (gs_token_compare_text(&token, "code"))
        {
            gs_parse_code(lex, desc, ppd, stage);
        }
    }); 
}

void gs_parse_compute_shader_stage(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{
    gs_parse_block(
    PIPELINE::COMPUTE_SHADER_STAGE,
    { 
        if (gs_token_compare_text(&token, "uniforms"))
        {
            gs_parse_uniforms(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_COMPUTE);
        }

        else if (gs_token_compare_text(&token, "in"))
        {
            gs_parse_in(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_COMPUTE);
        } 

        else if (gs_token_compare_text(&token, "code"))
        {
            gs_parse_code(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_COMPUTE);
        }
    }); 
}

void gs_parse_shader(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{ 
	if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_LBRACE)) 
    { 
        gs_println("error::gs_pipeline_load_resource_from_file	::error parsing shader from .sf resource");
        gs_assert(false);
    } 

    // Braces
    uint32_t bc = 1; 
    while (bc)
    {
        gs_token_t token = lex->next_token(lex);
        switch (token.type)
        {
            case GS_TOKEN_LBRACE: {bc++;} break; 
            case GS_TOKEN_RBRACE: {bc--;} break;

            case GS_TOKEN_IDENTIFIER:
            {
                // Vertex shader
                if (gs_token_compare_text(&token, "vertex"))
                {
                    gs_println("parsing vertex shader");
                    gs_parse_shader_stage(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_VERTEX);
                }

                // Fragment shader
                else if (gs_token_compare_text(&token, "fragment"))
                {
                    gs_println("parsing fragment shader");
                    gs_parse_shader_stage(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_FRAGMENT);
                } 

                // Compute shader
                else if (gs_token_compare_text(&token, "compute"))
                {
                    gs_println("parsing compute shader");
                    gs_parse_shader_stage(lex, desc, ppd, GS_GRAPHICS_SHADER_STAGE_COMPUTE);
                } 

            } break;
        }
    }
}

void gs_parse_depth(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* pdesc, gs_ppd_t* ppd)
{
    gs_parse_block(
    PIPELINE::DEPTH,
    { 
        // Depth function
        if (gs_token_compare_text(&token, "func"))
        {
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::DEPTH::func type not found after function decl.");
            }

            token = lex->current_token;
            
            if      (gs_token_compare_text(&token, "LESS"))     pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_LESS;
            else if (gs_token_compare_text(&token, "EQUAL"))    pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_EQUAL;
            else if (gs_token_compare_text(&token, "LEQUAL"))   pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_LEQUAL;
            else if (gs_token_compare_text(&token, "GREATER"))  pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_GREATER;
            else if (gs_token_compare_text(&token, "NOTEQUAL")) pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_NOTEQUAL;
            else if (gs_token_compare_text(&token, "GEQUAL"))   pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_GEQUAL;
            else if (gs_token_compare_text(&token, "ALWAYS"))   pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_ALWAYS; 
            else if (gs_token_compare_text(&token, "NEVER"))    pdesc->pip_desc.depth.func = GS_GRAPHICS_DEPTH_FUNC_NEVER; 
            else
            {
                gs_parse_warning("PIPELINE::DEPTH::func type %.*s not valid.", token.len, token.text);
            }
        }
    });
}

void gs_parse_blend(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* pdesc, gs_ppd_t* ppd)
{
    gs_parse_block(
    PIPELINE::BLEND,
    { 
        // Blend function
        if (gs_token_compare_text(&token, "func"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::BLEND::func type not found after function decl.");
            }

            token = lex->current_token;
            
            if      (gs_token_compare_text(&token, "ADD"))              pdesc->pip_desc.blend.func = GS_GRAPHICS_BLEND_EQUATION_ADD;
            else if (gs_token_compare_text(&token, "SUBTRACT"))         pdesc->pip_desc.blend.func = GS_GRAPHICS_BLEND_EQUATION_SUBTRACT;
            else if (gs_token_compare_text(&token, "REVERSE_SUBTRACT")) pdesc->pip_desc.blend.func = GS_GRAPHICS_BLEND_EQUATION_REVERSE_SUBTRACT;
            else if (gs_token_compare_text(&token, "MIN"))              pdesc->pip_desc.blend.func = GS_GRAPHICS_BLEND_EQUATION_MIN;
            else if (gs_token_compare_text(&token, "MAX"))              pdesc->pip_desc.blend.func = GS_GRAPHICS_BLEND_EQUATION_MAX;
            else
            {
                gs_parse_warning("PIPELINE::BLEND::func type %.*s not valid.", token.len, token.text);
            } 
        }

        // Source blend
        else if (gs_token_compare_text(&token, "src"))
        {
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::BLEND::src type not found after decl.");
            }

            token = lex->current_token;
            
            if      (gs_token_compare_text(&token, "ZERO"))                     pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ZERO;
            else if (gs_token_compare_text(&token, "ONE"))                      pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE; 
            else if (gs_token_compare_text(&token, "SRC_COLOR"))                pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_SRC_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_SRC_COLOR"))      pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_SRC_COLOR; 
            else if (gs_token_compare_text(&token, "DST_COLOR"))                pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_DST_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_DST_COLOR"))      pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_DST_COLOR; 
            else if (gs_token_compare_text(&token, "SRC_ALPHA"))                pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_SRC_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_SRC_ALPHA"))      pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_SRC_ALPHA; 
            else if (gs_token_compare_text(&token, "DST_ALPHA"))                pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_DST_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_DST_ALPHA"))      pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_DST_ALPHA; 
            else if (gs_token_compare_text(&token, "CONSTANT_COLOR"))           pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_CONSTANT_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_CONSTANT_COLOR")) pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_CONSTANT_ALPHA; 
            else if (gs_token_compare_text(&token, "CONSTANT_ALPHA"))           pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_CONSTANT_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_CONSTANT_ALPHA")) pdesc->pip_desc.blend.src = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_CONSTANT_ALPHA; 
            else
            {
                gs_parse_warning("PIPELINE::BLEND::src type %.*s not valid.", token.len, token.text);
            } 
        }

        // Dest blend
        else if (gs_token_compare_text(&token, "dst"))
        {
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::BLEND::dst type not found after decl.");
            }

            token = lex->current_token;
            
            if      (gs_token_compare_text(&token, "ZERO"))                     pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ZERO;
            else if (gs_token_compare_text(&token, "ONE"))                      pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE; 
            else if (gs_token_compare_text(&token, "SRC_COLOR"))                pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_SRC_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_SRC_COLOR"))      pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_SRC_COLOR; 
            else if (gs_token_compare_text(&token, "DST_COLOR"))                pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_DST_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_DST_COLOR"))      pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_DST_COLOR; 
            else if (gs_token_compare_text(&token, "SRC_ALPHA"))                pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_SRC_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_SRC_ALPHA"))      pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_SRC_ALPHA; 
            else if (gs_token_compare_text(&token, "DST_ALPHA"))                pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_DST_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_DST_ALPHA"))      pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_DST_ALPHA; 
            else if (gs_token_compare_text(&token, "CONSTANT_COLOR"))           pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_CONSTANT_COLOR; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_CONSTANT_COLOR")) pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_CONSTANT_ALPHA; 
            else if (gs_token_compare_text(&token, "CONSTANT_ALPHA"))           pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_CONSTANT_ALPHA; 
            else if (gs_token_compare_text(&token, "ONE_MINUS_CONSTANT_ALPHA")) pdesc->pip_desc.blend.dst = GS_GRAPHICS_BLEND_MODE_ONE_MINUS_CONSTANT_ALPHA; 
            else
            {
                gs_parse_warning("PIPELINE::BLEND::dst type %.*s not valid.", token.len, token.text);
            } 
        }

    });
}

void gs_parse_stencil(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* pdesc, gs_ppd_t* ppd)
{ 
    gs_parse_block(
    PIPELINE::STENCIL,
    { 
        // Function
        if (gs_token_compare_text(&token, "func"))
        {
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::func type not found after decl.");
            }

            else
            {
                token = lex->current_token; 
                
                if      (gs_token_compare_text(&token, "LESS"))     pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_LESS;
                else if (gs_token_compare_text(&token, "EQUAL"))    pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_EQUAL;
                else if (gs_token_compare_text(&token, "LEQUAL"))   pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_LEQUAL;
                else if (gs_token_compare_text(&token, "GREATER"))  pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_GREATER;
                else if (gs_token_compare_text(&token, "NOTEQUAL")) pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_NOTEQUAL;
                else if (gs_token_compare_text(&token, "GEQUAL"))   pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_GEQUAL;
                else if (gs_token_compare_text(&token, "ALWAYS"))   pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_ALWAYS; 
                else if (gs_token_compare_text(&token, "NEVER"))    pdesc->pip_desc.stencil.func = GS_GRAPHICS_STENCIL_FUNC_NEVER; 
                else
                {
                    gs_parse_warning("PIPELINE::STENCIL::func type %.*s not valid.", token.len, token.text);
                } 
            }

        }

        // Reference value
        else if (gs_token_compare_text(&token, "ref"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_NUMBER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::reference value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 
                gs_snprintfc(TMP, 16, "%.*s", token.len, token.text);
                pdesc->pip_desc.stencil.ref = atoi(TMP); 
            }
        }

        // Component mask
        else if (gs_token_compare_text(&token, "comp_mask"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_NUMBER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::component mask value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 
                gs_snprintfc(TMP, 16, "%.*s", token.len, token.text);
                pdesc->pip_desc.stencil.comp_mask = atoi(TMP); 
            }
        }

        // Write mask
        else if (gs_token_compare_text(&token, "write_mask"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_NUMBER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::write mask value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 
                gs_snprintfc(TMP, 16, "%.*s", token.len, token.text);
                pdesc->pip_desc.stencil.write_mask = atoi(TMP); 
            }
        }

        // Stencil test failure
        else if (gs_token_compare_text(&token, "sfail"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::sfail value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 

                if (gs_token_compare_text(&token, "KEEP"))              pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_KEEP;
                else if (gs_token_compare_text(&token, "ZERO"))         pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_ZERO;
                else if (gs_token_compare_text(&token, "REPLACE"))      pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_REPLACE;
                else if (gs_token_compare_text(&token, "INCR"))         pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_INCR;
                else if (gs_token_compare_text(&token, "INCR_WRAP"))    pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_INCR_WRAP;
                else if (gs_token_compare_text(&token, "DECR"))         pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_DECR;
                else if (gs_token_compare_text(&token, "DECR_WRAP"))    pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_DECR_WRAP;
                else if (gs_token_compare_text(&token, "INVERT"))       pdesc->pip_desc.stencil.sfail = GS_GRAPHICS_STENCIL_OP_INVERT;
                else
                {
                    gs_parse_warning("PIPELINE::STENCIL::sfail type %.*s not valid.", token.len, token.text);
                } 
            }
        }

        // Stencil test pass, Depth fail
        else if (gs_token_compare_text(&token, "dpfail"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::dpfail value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 

                if (gs_token_compare_text(&token, "KEEP"))              pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_KEEP;
                else if (gs_token_compare_text(&token, "ZERO"))         pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_ZERO;
                else if (gs_token_compare_text(&token, "REPLACE"))      pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_REPLACE;
                else if (gs_token_compare_text(&token, "INCR"))         pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_INCR;
                else if (gs_token_compare_text(&token, "INCR_WRAP"))    pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_INCR_WRAP;
                else if (gs_token_compare_text(&token, "DECR"))         pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_DECR;
                else if (gs_token_compare_text(&token, "DECR_WRAP"))    pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_DECR_WRAP;
                else if (gs_token_compare_text(&token, "INVERT"))       pdesc->pip_desc.stencil.dpfail = GS_GRAPHICS_STENCIL_OP_INVERT;
                else
                {
                    gs_parse_warning("PIPELINE::STENCIL::dpfail type %.*s not valid.", token.len, token.text);
                } 
            }
        }

        // Stencil test pass, Depth pass
        else if (gs_token_compare_text(&token, "dppass"))
        { 
            if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::STENCIL::dppass value not found after decl."); 
            }

            else
            {
                token = lex->current_token; 

                if (gs_token_compare_text(&token, "KEEP"))              pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_KEEP;
                else if (gs_token_compare_text(&token, "ZERO"))         pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_ZERO;
                else if (gs_token_compare_text(&token, "REPLACE"))      pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_REPLACE;
                else if (gs_token_compare_text(&token, "INCR"))         pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_INCR;
                else if (gs_token_compare_text(&token, "INCR_WRAP"))    pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_INCR_WRAP;
                else if (gs_token_compare_text(&token, "DECR"))         pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_DECR;
                else if (gs_token_compare_text(&token, "DECR_WRAP"))    pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_DECR_WRAP;
                else if (gs_token_compare_text(&token, "INVERT"))       pdesc->pip_desc.stencil.dppass = GS_GRAPHICS_STENCIL_OP_INVERT;
                else
                {
                    gs_parse_warning("PIPELINE::STENCIL::dppass type %.*s not valid.", token.len, token.text);
                } 
            }
        }
    });
}

void gs_parse_raster(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* pdesc, gs_ppd_t* ppd)
{
    gs_parse_block(
    PIPELINE::RASTER,
    { 
        // Index Buffer Element Size 
        if (gs_token_compare_text(&token, "index_buffer_element_size"))
        { 
	        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::RASTER::index buffer element size not found.", token.len, token.text);
            }
            
            token = lex->current_token;

            if (gs_token_compare_text(&token, "UINT32") || gs_token_compare_text(&token, "uint32_t") || gs_token_compare_text(&token, "u32"))
            { 
                pdesc->pip_desc.raster.index_buffer_element_size = sizeof(uint32_t); 
            }

            else if (gs_token_compare_text(&token, "UINT16") || gs_token_compare_text(&token, "uint16_t") || gs_token_compare_text(&token, "u16"))
            {
                pdesc->pip_desc.raster.index_buffer_element_size = sizeof(uint16_t); 
            }
            
            // Default
            else
            {
                pdesc->pip_desc.raster.index_buffer_element_size = sizeof(uint32_t); 
            }
        } 

        // Face culling 
        if (gs_token_compare_text(&token, "face_culling"))
        { 
	        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::RASTER::face culling type not found.");
            }
            
            token = lex->current_token;

            if (gs_token_compare_text(&token, "FRONT"))               pdesc->pip_desc.raster.face_culling = GS_GRAPHICS_FACE_CULLING_FRONT;
            else if (gs_token_compare_text(&token, "BACK"))           pdesc->pip_desc.raster.face_culling = GS_GRAPHICS_FACE_CULLING_BACK;
            else if (gs_token_compare_text(&token, "FRONT_AND_BACK")) pdesc->pip_desc.raster.face_culling = GS_GRAPHICS_FACE_CULLING_FRONT_AND_BACK;
            else
            {
                gs_parse_warning("PIPELINE::RASTER::face culling type %.*s not valid.", token.len, token.text);
            }
        } 

        // Winding order 
        if (gs_token_compare_text(&token, "winding_order"))
        { 
	        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::RASTER::winding order type not found.");
            }
            
            token = lex->current_token;

            if (gs_token_compare_text(&token, "CW"))         pdesc->pip_desc.raster.face_culling = GS_GRAPHICS_WINDING_ORDER_CW;
            else if (gs_token_compare_text(&token, "CCW"))   pdesc->pip_desc.raster.face_culling = GS_GRAPHICS_WINDING_ORDER_CCW;
            else
            {
                gs_parse_warning("PIPELINE::RASTER::winding order type %.*s not valid.", token.len, token.text);
            }
        } 

        // Primtive 
        if (gs_token_compare_text(&token, "primitive"))
        { 
	        if (!gs_lexer_find_next_token_type(lex, GS_TOKEN_IDENTIFIER))
            {
                gs_parse_error(false, "PIPELINE::RASTER::primitive type not found.");
            }
            
            token = lex->current_token;

            if (gs_token_compare_text(&token, "LINES"))            pdesc->pip_desc.raster.primitive = GS_GRAPHICS_PRIMITIVE_LINES;
            else if (gs_token_compare_text(&token, "TRIANGLES"))   pdesc->pip_desc.raster.primitive = GS_GRAPHICS_PRIMITIVE_TRIANGLES;
            else if (gs_token_compare_text(&token, "QUADS"))       pdesc->pip_desc.raster.primitive = GS_GRAPHICS_PRIMITIVE_QUADS;
            else
            {
                gs_parse_warning("PIPELINE::RASTER::primitive type %.*s not valid.", token.len, token.text);
            }
        } 
    });
}

void gs_parse_pipeline(gs_lexer_t* lex, gs_gfxt_pipeline_desc_t* desc, gs_ppd_t* ppd)
{ 
    // Get next identifier
    while (lex->can_lex(lex))
    {
        gs_token_t token = lex->next_token(lex);
        switch (token.type)
        {
            case GS_TOKEN_IDENTIFIER:
            {
                if (gs_token_compare_text(&token, "shader"))
                {
                    gs_println("parsing shader");
                    gs_parse_shader(lex, desc, ppd);
                }

                else if (gs_token_compare_text(&token, "raster"))
                {
                    gs_parse_raster(lex, desc, ppd); 
                }

                else if (gs_token_compare_text(&token, "depth"))
                {
                    gs_parse_depth(lex, desc, ppd);
                }

                else if (gs_token_compare_text(&token, "stencil"))
                {
                    gs_parse_stencil(lex, desc, ppd);
                }

                else if (gs_token_compare_text(&token, "blend"))
                {
                    gs_parse_blend(lex, desc, ppd);
                }

            } break;
        }
    }
}

char* gs_pipeline_generate_shader_code(gs_gfxt_pipeline_desc_t* pdesc, gs_ppd_t* ppd, gs_graphics_shader_stage_type stage)
{
    gs_println("GENERATING CODE...");

    // Shaders
    #ifdef GS_PLATFORM_WEB
        #define _GS_VERSION_STR "#version 300 es\n"
    #else
        #define _GS_VERSION_STR "#version 330 core\n"
    #endif

    // Source code 
    char* src = NULL; 
    uint32_t sidx = 0;

    // Set sidx
    switch (stage)
    {
        case GS_GRAPHICS_SHADER_STAGE_VERTEX:   sidx = 0; break;
        case GS_GRAPHICS_SHADER_STAGE_FRAGMENT: sidx = 1; break;
        case GS_GRAPHICS_SHADER_STAGE_COMPUTE:  sidx = 2; break;
    }

    // Early out for now...
    if (!ppd->code[sidx])
    {
        return src;
    }

    const char* shader_header = 
    stage == GS_GRAPHICS_SHADER_STAGE_COMPUTE ? 
    "#version 430\n" : 
    _GS_VERSION_STR
    "precision mediump float;\n";

    // Generate shader code
    if (ppd->code[sidx])
    {
        const size_t header_sz = (size_t)gs_string_length(shader_header);
        size_t total_sz = gs_string_length(ppd->code[sidx]) + header_sz + 2048;
        src = gs_malloc(total_sz); 
        memset(src, 0, total_sz);
        strncat(src, shader_header, header_sz);
        
        // Attributes
        if (stage == GS_GRAPHICS_SHADER_STAGE_VERTEX)
        {
            for (uint32_t i = 0; i < gs_dyn_array_size(pdesc->pip_desc.layout.attrs); ++i)
            { 
                const char* aname = pdesc->pip_desc.layout.attrs[i].name;
                const char* atype = gs_get_vertex_attribute_string(pdesc->pip_desc.layout.attrs[i].format); 

                gs_snprintfc(ATTR, 64, "layout(location = %zu) in %s %s;\n", i, atype, aname);
                const size_t sz = gs_string_length(ATTR);
                strncat(src, ATTR, sz);
            } 
        }

        // Compute shader image buffer binding
        uint32_t img_binding = 0;

        // Uniforms
        for (uint32_t i = 0; i < gs_dyn_array_size(pdesc->ublock_desc.layout); ++i)
        { 
            gs_gfxt_uniform_desc_t* udesc = &pdesc->ublock_desc.layout[i]; 

            if (udesc->stage != stage) continue;

            switch (stage)
            {
                case GS_GRAPHICS_SHADER_STAGE_COMPUTE:
                {
                    // Need to go from uniform type to string
                    const char* utype = gs_uniform_string_from_type(udesc->type);
                    const char* uname = udesc->name;

                    switch (udesc->type)
                    {
                        default:
                        {
                            gs_snprintfc(TMP, 64, "uniform %s %s;\n", utype, uname);
                            const size_t sz = gs_string_length(TMP);
                            strncat(src, TMP, sz);
                        } break;

                        case GS_GRAPHICS_UNIFORM_IMAGE2D_RGBA32F:
                        {
                            gs_snprintfc(TMP, 64, "layout (rgba32f, binding = %zu) uniform image2D %s;\n", img_binding++, uname);
                            const size_t sz = gs_string_length(TMP);
                            strncat(src, TMP, sz);
                        } break;
                    }
                } break;

                default:
                {
                    // Need to go from uniform type to string
                    const char* utype = gs_uniform_string_from_type(udesc->type);
                    const char* uname = udesc->name;
                    gs_snprintfc(TMP, 64, "uniform %s %s;\n", utype, uname);
                    const size_t sz = gs_string_length(TMP);
                    strncat(src, TMP, sz);
                } break;
            }

        }

        // Out
        switch (stage)
        {
            case GS_GRAPHICS_SHADER_STAGE_FRAGMENT:
            case GS_GRAPHICS_SHADER_STAGE_VERTEX:
            {
                for (uint32_t i = 0; i < gs_dyn_array_size(ppd->io_list[sidx]); ++i)
                {
                    gs_shader_io_data_t* out = &ppd->io_list[sidx][i];
                    const char* otype = out->type;
                    const char* oname = out->name;
                    gs_transient_buffer(TMP, 64);
                    if (stage == GS_GRAPHICS_SHADER_STAGE_FRAGMENT)
                    {
                        gs_snprintf(TMP, 64, "layout(location = %zu) out %s %s;\n", i, otype, oname);
                    }
                    else
                    {
                        gs_snprintf(TMP, 64, "out %s %s;\n", otype, oname);
                    }
                    const size_t sz = gs_string_length(TMP);
                    strncat(src, TMP, sz); 
                }
            } break; 

            default: break;
        }

        // In
        switch (stage)
        {
            case GS_GRAPHICS_SHADER_STAGE_FRAGMENT:
            {
                for (uint32_t i = 0; i < gs_dyn_array_size(ppd->io_list[0]); ++i)
                {
                    gs_shader_io_data_t* out = &ppd->io_list[0][i];
                    const char* otype = out->type;
                    const char* oname = out->name;
                    gs_snprintfc(TMP, 64, "in %s %s;\n", otype, oname);
                    const size_t sz = gs_string_length(TMP);
                    strncat(src, TMP, sz); 
                }
            } break;

            case GS_GRAPHICS_SHADER_STAGE_COMPUTE:
            {
                gs_snprintfc(TMP, 64, "layout(");
                strncat(src, "layout(", 7);

                for (uint32_t i = 0; i < gs_dyn_array_size(ppd->io_list[2]); ++i)
                {
                    gs_shader_io_data_t* out = &ppd->io_list[2][i];
                    const char* otype = out->type;
                    const char* oname = out->name;
                    gs_snprintfc(TMP, 64, "%s = %s%s", otype, oname, i == gs_dyn_array_size(ppd->io_list[2]) - 1 ? "" : ", ");
                    const size_t sz = gs_string_length(TMP);
                    strncat(src, TMP, sz); 
                }

                strncat(src, ") in;\n", 7);
            } break;

            default: break;
        }

        // Code
        { 
            const size_t sz = gs_string_length(ppd->code[sidx]);
            strncat(src, ppd->code[sidx], sz); 
        } 
    } 

    return src;
}

GS_API_DECL bool gs_pipeline_load_resource_from_file(const char* path, gs_asset_t* out, void* user_data)
{
    // Cast to pip
    gs_pipeline_t* pip = (gs_pipeline_t	*)out;

    // Load file, generate lexer off of file data, parse contents for pipeline information 
    size_t len = 0;
    char* file_data = gs_platform_read_file_contents(path, "r", &len);
    gs_assert(file_data); 

    gs_ppd_t ppd = {0};
    gs_gfxt_pipeline_desc_t pdesc = {0};
    pdesc.pip_desc.raster.index_buffer_element_size = sizeof(uint32_t); 

	gs_lexer_t lex = gs_lexer_c_ctor(file_data);
    while (lex.can_lex(&lex))
    {
        gs_token_t token = lex.next_token(&lex);
        switch (token.type)
        {
            case GS_TOKEN_IDENTIFIER:
            {
                if (gs_token_compare_text(&token, "pipeline"))
                {
                    gs_parse_pipeline(&lex, &pdesc, &ppd); 
                }
            } break;
        }
    }

    // Generate vertex shader code
    char* v_src = gs_pipeline_generate_shader_code(&pdesc, &ppd, GS_GRAPHICS_SHADER_STAGE_VERTEX);

    // gs_println("%s", v_src);

    // Generate fragment shader code
    char* f_src = gs_pipeline_generate_shader_code(&pdesc, &ppd, GS_GRAPHICS_SHADER_STAGE_FRAGMENT); 
    
    // gs_println("%s", f_src);
    
    // Generate compute shader code (need to check for this first)
    char* c_src = gs_pipeline_generate_shader_code(&pdesc, &ppd, GS_GRAPHICS_SHADER_STAGE_COMPUTE);
    // gs_println("%s", c_src);

    // Construct compute shader
    if (c_src)
    {
        pdesc.pip_desc.compute.shader = gs_graphics_shader_create(&(gs_graphics_shader_desc_t){
            .sources = (gs_graphics_shader_source_desc_t[]){ 
                {.type = GS_GRAPHICS_SHADER_STAGE_COMPUTE, .source = c_src}
            },
            .size = 1 * sizeof(gs_graphics_shader_source_desc_t),
            .name = path
        }); 
    }

    // Construct raster shader
    else
    {
        pdesc.pip_desc.raster.shader = gs_graphics_shader_create(&(gs_graphics_shader_desc_t){
            .sources = (gs_graphics_shader_source_desc_t[]){ 
                {.type = GS_GRAPHICS_SHADER_STAGE_VERTEX, .source = v_src},
                {.type = GS_GRAPHICS_SHADER_STAGE_FRAGMENT, .source = f_src}
            },
            .size = 2 * sizeof(gs_graphics_shader_source_desc_t),
            .name = path
        }); 
    }
    

    // Set up layout
    pdesc.pip_desc.layout.size = gs_dyn_array_size(pdesc.pip_desc.layout.attrs) * sizeof(gs_graphics_vertex_attribute_desc_t);

    // Set up ublock
    pdesc.ublock_desc.size = gs_dyn_array_size(pdesc.ublock_desc.layout) * sizeof(gs_gfxt_uniform_desc_t); 

    // Create pipeline
    pip->pipeline = gs_gfxt_pipeline_create(&pdesc);

    // Create mesh layout
    if (ppd.mesh_layout)
    {
        for (uint32_t i = 0; i < gs_dyn_array_size(ppd.mesh_layout); ++i)
        {
            gs_dyn_array_push(pip->mesh_layout, ppd.mesh_layout[i]);
        }
    }

    // Free all malloc'd data 
    if (v_src) gs_free(v_src);
    if (f_src) gs_free(f_src); 
    if (c_src) gs_free(c_src);
    gs_free(file_data); 
    gs_dyn_array_free(pdesc.pip_desc.layout.attrs);
    gs_dyn_array_free(pdesc.ublock_desc.layout);
    gs_dyn_array_free(ppd.mesh_layout);
    
    for (uint32_t i = 0; i < 3; ++i)
    {
        if (ppd.code[i]) gs_free(ppd.code[i]);
        gs_dyn_array_free(ppd.io_list[i]);
    }

    return true;
}

GS_API_DECL gs_gfxt_mesh_import_options_t gs_pipeline_get_mesh_import_options(const gs_pipeline_t* pipe)
{ 
    // Get pipeline descriptor
    gs_graphics_pipeline_desc_t pdesc = gs_default_val();
    gs_graphics_pipeline_desc_query(pipe->pipeline.hndl, &pdesc);

    // Construct mesh import options
    gs_gfxt_mesh_import_options_t options = gs_default_val(); 
    options.index_buffer_element_size = pdesc.raster.index_buffer_element_size; 

    // Copy mesh layout from pipeline
    for (uint32_t i = 0; i < gs_dyn_array_size(pipe->mesh_layout); ++i)
    {
        gs_dyn_array_push(options.layout, pipe->mesh_layout[i]);
    }
    options.size = sizeof(gs_gfxt_mesh_layout_t) * gs_dyn_array_size(options.layout);

    // Free pipeline descriptor
    gs_dyn_array_free(pdesc.layout.attrs);

    return options;
}

#endif // GS_ASSET_IMPL
#endif // GS_ASSET_H








