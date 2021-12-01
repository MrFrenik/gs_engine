#!bin/sh

rm -rf bin
mkdir bin
cd bin

refl_name=Reflection
proj_name=App
proj_root_dir=$(pwd)/../

flags=(
	-std=gnu99 -x -00 -w
)

# Include directories
inc=(
	-I ../third_party/include/			# Gunslinger includes
)

# Reflection include directories
refl_inc=(
    -I ../source/
)

# Source files
src=(
	../source/main.c
) 

refl_src=(
    ../source/reflection/main.c
)

libs=(
	-lopengl32
	-lkernel32 
	-luser32 
	-lshell32 
	-lgdi32 
    -lWinmm
	-lAdvapi32
)

# Build reflection
gcc ${inc[*]} ${refl_inc[*]} ${refl_src[*]} ${flags[*]} ${libs[*]} -lm -o ${refl_name}

# Run reflection
 ./${refl_name}.exe "../source/" "../source/reflection/"

# Build
gcc ${inc[*]} ${src[*]} ${flags[*]} ${libs[*]} -lm -o ${proj_name}

cd ..



