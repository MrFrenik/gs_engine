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
    	-I ../../gs_core/source/
    	-I ../../gs_core/third_party/include/
)

# Reflection source
refl_src=(
   	../../gs_core/source/reflection/main.c
)

# Editor includes
proj_inc=(
	-I ../../gs_core/third_party/include/
    	-I ../../gs_core/source/ 
)

# Source files
proj_src=(
	../source/gs_editor_main.c
)

# Compile reflection
gcc -O0 ${refl_inc[*]} ${refl_src[*]} ${flags[*]} -lm -o reflection

# Run reflection for gs files
./reflection "${core_dir}/source" "${core_dir}/source/reflection/" "gs"

# Run reflection for gs_editor files
./reflection "$../source" "../source/reflection/" "gs_editor"

# Compile gs_editor (debug)
gcc -O0 ${proj_inc[*]} ${proj_src[*]} ${flags[*]} -lm -o gs_editor

# Compile gs_editor (release)
# gcc -O3 ${proj_inc[*]} ${proj_src[*]} ${flags[*]} -lm -o gs_editor

cd ..
