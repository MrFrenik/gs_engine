#!/bin/bash

rm -rf bin
mkdir bin
cd bin 

set proj_name=gs_editor
set refl_name=reflection
set core_dir=../../gs_core/

flags=(
	-std=gnu99 -w -ldl -lGL -lX11 -pthread -lXi
)

# Reflection includes
refl_inc=(
    -I ${core_dir}/source/
)

# Reflection source
refl_src=(
    -I ${core_dir}/source/
)

# Editor includes
proj_inc=(
	-I ../third_party/include/
    -I ${core_dir}/source/ 
)

# Source files
proj_src=(
	../source/gs_editor_main.c
)

# Compile reflection
gcc -O3 ${refl_inc[*]} ${refl_src[*]} ${flags[*]} -lm -o ${refl_name}

# Run reflection for gs files
./${refl_name} "${core_dir}/source" "${core_dir}/source/reflection/" "gs"

# Run reflection for gs_editor files
./${refl_name} "$../source" "../source/reflection/" "gs_editor"

# Compile gs_editor (debug)
gcc -O0 ${proj_inc[*]} ${proj_src[*]} ${flags[*]} -lm -o ${proj_name}

# Compile gs_editor (release)
# gcc -O3 ${proj_inc[*]} ${proj_src[*]} ${flags[*]} -lm -o ${proj_name}

cd ..
