# Gunslinger Engine

You can also check the main **Gunslinger** repository here, where you'll find a documentation for you to get started and learn how to use it:
[Gunlinger repository](https://github.com/MrFrenik/gunslinger)
 
And you can also find a complete list of examples for you to learn from and test on your machine here: 
[Gunslinger examples](https://github.com/MrFrenik/gs_examples)

## Cloning instructions: 
- Use the following command to clone the repo and init the gunslinger submodule
```bash
git clone --recursive https://github.com/MrFrenik/gs_engine
```

## Updating GS instructions (updates gunslinger submodule and rebases to main branch): 
```bash
git submodule update --remote --rebase --recursive
```

## Build Instructions:

### Windows
## MSVC:
- From start menu, open `{x86|x64} Native Tools for {VS Version Here}`
- cd to `root dir` where you downloaded gs_engine
- cd to `gs_editor dir`
- To compile the project, run:
```bash
proc\win\cl.bat
```
- To execute the editor, run: 
```bash
bin\gs_editor.exe
```

### Linux

## Before Compiling:
- Make sure the following development libraries are installed: 
```bash
sudo apt install git gcc mesa-common-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev
```
- For Mesa and OpenGL, need to export the following: 
```bash
export MESA_GL_VERSION_OVERRIDE=3.3
```
- Credit to https://github.com/Samdal

## GCC:
- Open terminal
- cd to `root dir/gs_editor/` where you downloaded project template
- To compile the project, run:
```bash
bash ./proc/linux/gcc.sh
```
- To execute the program, run: 
```bash
./bin/App
```
