/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine
    * File: gs_graphics.h
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

#ifndef GS_GRAPHICS_H
#define GS_GRAPHICS_H

typedef struct gs_quad_vert_t
{ 
    gs_vec2 position;          
    gs_vec2 uv;
    gs_color_t color;
} gs_quad_vert_t; 

typedef struct gs_quad_t
{ 
    gs_vec2 position;
    gs_vec2 dimensions;
    gs_vec4 uvs;
    gs_color_t color;
    float depth;
} gs_quad_t;

int32_t gs_quad_compare(const void* a, const void* b)
{
    gs_quad_t* q0 = (gs_quad_t*)a;
    gs_quad_t* q1 = (gs_quad_t*)b;
    if (q0->depth < q1->depth) return -1;
    if (q0->depth > q1->depth) return 1;
    return 0;
}

typedef struct gs_quad_batch_t
{ 
    gs_dyn_array(gs_quad_t) quads;// Array of quads
    gs_vbo vbo;                // Vertex buffer handle
    gs_ibo ibo;                // Index buffer handle
    uint32_t material_hndl;    // Reference to a material asset
    uint32_t count;            // Total index buffer count for upload 
} gs_quad_batch_t; 

GS_API_DECL void gs_quad_batch_init(gs_quad_batch_t* qb, uint32_t mat_hndl); 
GS_API_DECL void gs_quad_batch_begin(gs_quad_batch_t* qb);
GS_API_DECL void gs_quad_batch_end(gs_quad_batch_t* qb, gs_command_buffer_t* cb);
GS_API_DECL void gs_quad_batch_add(gs_quad_batch_t* qb, const gs_vec2* position, const gs_vec2* dimensions, const gs_vec4* uvs, const gs_color_t* color, float depth);
GS_API_PRIVATE void gs_quad_batch_sort(gs_quad_batch_t* qb);

typedef struct gs_renderable_base_t
{ 
    uint32_t hndl;                          // Slot array renderable id handle
    gs_mat4 model_matrix;                   // Model matrix
    gs_dyn_array(gs_asset_handle_t	) materials; // Per primitive materials
} gs_renderable_base_t;

GS_API_DECL gs_renderable_base_set_material(gs_renderable_base_t* rend, gs_asset_handle_t mat, uint32_t idx); 

typedef struct gs_renderable_static_mesh_t
{
    base(gs_renderable_base_t)

    gs_asset_handle_t mesh;                    // Asset handle for static mesh

} gs_renderable_static_mesh_t;

GS_API_DECL gs_renderable_static_mesh_set_mesh(gs_renderable_static_mesh_t* rend, gs_asset_handle_t mesh); 

typedef struct gs_renderable_skeletal_mesh_t
{
    base(gs_renderable_base_t)

    gs_asset_handle_t mesh;                    // Asset handle for skeletal mesh

} gs_renderable_skeletal_mesh_t; 

GS_API_DECL void renderable_set_material_uniform(gs_renderable_base_t* rend, const char* name, void* data);

// Need a way to add renderables to a scene
typedef struct gs_graphics_scene_t 
{ 
	gs_slot_array(gs_renderable_static_mesh_t) static_meshes;

} gs_graphics_scene_t;

GS_API_DECL uint32_t gs_graphics_scene_add_renderable_static_mesh(gs_graphics_scene_t* scene, gs_renderable_static_mesh_t renderable); 
GS_API_DECL gs_renderable_static_mesh_t* gs_graphics_scene_get_renderable_static_mesh(gs_graphics_scene_t* scene, uint32_t hndl);

#ifdef GS_GRAPHICS_IMPL

GS_API_DECL void gs_quad_batch_init(gs_quad_batch_t* qb, uint32_t mat_hndl) 
{
    // Construct vbo
    gs_graphics_vertex_buffer_desc_t vdesc = gs_default_val();
    qb->vbo = gs_graphics_vertex_buffer_create(&vdesc);

    // Construct ibo
    gs_graphics_index_buffer_desc_t idesc = gs_default_val();
    qb->ibo = gs_graphics_index_buffer_create(&idesc);

    // Set mat handle
    qb->material_hndl = mat_hndl;
}

GS_API_DECL void gs_quad_batch_begin(gs_quad_batch_t* qb)
{
    // Could add these asserts to some debug define 
    gs_assert(qb->material_hndl != 0);
    gs_assert(qb->vbo.id != 0);
    gs_assert(qb->ibo.id != 0);
    gs_dyn_array_clear(qb->quads);
}

GS_API_DECL void gs_quad_batch_end(gs_quad_batch_t* qb, gs_command_buffer_t* cb)
{ 
    gs_dyn_array(gs_quad_vert_t) verts = {0};
    gs_dyn_array(uint32_t) indices = {0};

    // Push back all verts, store indices to verts for quads 
    // NOTE(john): This is ~4ms
    for (uint32_t i = 0; i < gs_dyn_array_size(qb->quads); ++i)
    {
        const gs_quad_t* q = &qb->quads[i]; 

        float l = q->position.x;
        float b = q->position.y;
        float r = q->position.x + q->dimensions.x;
        float t = q->position.y + q->dimensions.y; 

        gs_vec2 lb = gs_v2(l, b);
        gs_vec2 lt = gs_v2(l, t);
        gs_vec2 rb = gs_v2(r, b);
        gs_vec2 rt = gs_v2(r, t);

        float u0 = q->uvs.x; 
        float v0 = q->uvs.y;
        float u1 = q->uvs.z;
        float v1 = q->uvs.w; 

        gs_vec2 u0v0 = gs_v2(u0, v0);
        gs_vec2 u1v0 = gs_v2(u1, v0);
        gs_vec2 u0v1 = gs_v2(u0, v1);
        gs_vec2 u1v1 = gs_v2(u1, v1);

        // Capture vert size
        uint32_t vs = gs_dyn_array_size(verts);

        // Construct verts
        gs_quad_vert_t qlb = {0}; qlb.position = lb; qlb.uv = u0v0; qlb.color = q->color;
        gs_quad_vert_t qlt = {0}; qlt.position = lt; qlt.uv = u0v1; qlt.color = q->color;
        gs_quad_vert_t qrb = {0}; qrb.position = rb; qrb.uv = u1v0; qrb.color = q->color;
        gs_quad_vert_t qrt = {0}; qrt.position = rt; qrt.uv = u1v1; qrt.color = q->color; 

        // Push back verts
        gs_dyn_array_push(verts, qlb);    // 0
        gs_dyn_array_push(verts, qlt);    // 1
        gs_dyn_array_push(verts, qrb);    // 2
        gs_dyn_array_push(verts, qrt);    // 3

        // First triangle
        gs_dyn_array_push(indices, vs + 0);   // lb
        gs_dyn_array_push(indices, vs + 3);   // rb
        gs_dyn_array_push(indices, vs + 2);   // lt

        // Second triangle
        gs_dyn_array_push(indices, vs + 0);   // rb
        gs_dyn_array_push(indices, vs + 1);   // rt
        gs_dyn_array_push(indices, vs + 3);   // lt
    } 

    // Buffer descriptors
    gs_graphics_vertex_buffer_desc_t vdesc = {0};
    vdesc.data = verts;
    vdesc.size = gs_dyn_array_size(verts) * sizeof(gs_quad_vert_t);

    gs_graphics_vertex_buffer_desc_t idesc = {0};
    idesc.data = indices;
    idesc.size = gs_dyn_array_size(indices) * sizeof(uint32_t); 

    // Upload all data to graphics backend
    gs_graphics_vertex_buffer_request_update(cb, qb->vbo, &vdesc);
    gs_graphics_index_buffer_request_update(cb, qb->ibo, &idesc);

    // Set count
    qb->count = gs_dyn_array_size(indices); 

    // Free vertex/indices data (might hold these around later on)
    gs_dyn_array_free(verts);
    gs_dyn_array_free(indices);
} 

GS_API_DECL void gs_quad_batch_add(gs_quad_batch_t* qb, const gs_vec2* position, const gs_vec2* dimensions, const gs_vec4* uvs, const gs_color_t* color, float depth)
{ 
    // Make a quad out of this
    gs_quad_t q = {0};
    q.position = *position;
    q.dimensions = *dimensions;
    q.uvs = *uvs;
    q.color = *color;
    q.depth = depth; 
    gs_dyn_array_push(qb->quads, q); 
} 

GS_API_PRIVATE void gs_quad_batch_sort(gs_quad_batch_t* qb)
{
    // Sort all of our vertex data by y
    qsort(qb->quads, gs_dyn_array_size(qb->quads), sizeof(gs_quad_t), gs_quad_compare); 
}

// ==================== [ Renderable Base ] =============== //

GS_API_DECL gs_renderable_base_set_material(gs_renderable_base_t* rend, gs_asset_handle_t mat, uint32_t idx)
{
    // Check for availability (this should be based on setting the mesh)
    if (idx >= gs_dyn_array_size(rend->materials))
    {
        gs_dyn_array_reserve(rend->materials, idx + 1);
    }

    // Set material
    rend->materials[idx] = mat;
}

// ==================== [ Renderable Static Mesh ] =============== //

GS_API_DECL gs_renderable_static_mesh_set_mesh(gs_renderable_static_mesh_t* rend, gs_asset_handle_t mesh)
{
    // Get mesh primitive count
    gs_mesh_t* mp = gs_asset_handle_get	(&mesh);
    uint32_t cnt = gs_dyn_array_size(mp->mesh.primitives); 

    // Reserve material space if necessary
    gs_renderable_base_t* base = cast(rend, gs_renderable_base_t);
    if (gs_dyn_array_size(base->materials) < cnt) {
        gs_dyn_array_reserve(base->materials, cnt);
    }

    // Set mesh
    rend->mesh = mesh;
}

// ==================== [ Graphics Scene ] =============== //

GS_API_DECL uint32_t gs_graphics_scene_add_renderable_static_mesh(gs_graphics_scene_t* scene, gs_renderable_static_mesh_t rend)
{
    const uint32_t hndl = gs_slot_array_insert(scene->static_meshes, rend);
    gs_slot_array_getp(scene->static_meshes, hndl)->_base.hndl = hndl;
    return hndl;
} 

GS_API_DECL gs_renderable_static_mesh_t* gs_graphics_scene_get_renderable_static_mesh(gs_graphics_scene_t* scene, uint32_t hndl)
{
    return gs_slot_array_getp(scene->static_meshes, hndl);
}








#endif // GS_GRAPHICS_IMPL
#endif // GS_GRAPHICS_H
