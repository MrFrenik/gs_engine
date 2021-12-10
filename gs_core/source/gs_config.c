/*==============================================================================================================
    * Copyright: 2020 John Jackson 
    * Gunslinger Engine
    * File: gs_config.c
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

/*
 *  Main configuration file for unity build.
 */

#define GS_IMPL
#include <gs/gs.h>

#define GS_IMMEDIATE_DRAW_IMPL
#include <gs/util/gs_idraw.h> 

#define GS_GFXT_IMPL
#include <gs/util/gs_gfxt.h>

#define GS_META_IMPL
#include <gs/util/gs_meta.h>

#define GS_PHYSICS_IMPL
#include <gs/util/gs_physics.h> 

#define GS_GUI_IMPL
#include "gs_gui.h" 

#define GS_OBJECT_IMPL
#include "gs_object.h"

#define GS_ASSET_IMPL
#include "gs_asset.h"

#define GS_GRAPHICS_IMPL
#include "gs_graphics.h" 

#define GS_COMPONENT_IMPL
#include "gs_component.h"

#define GS_ENTITY_IMPL
#include "gs_entity.h"

#define GS_GENERATED_IMPL
#include "../source/reflection/gs_generated.h"

#define GS_CORE_IMPL
#include "gs_core.h"

// Source files
#include "../source/reflection/gs_generated.c"
#include "gs_component.c"


