# Create OpenGL
- with freeglut/vscode

A quick start template for starting an OpenGL project wtih vscode.

### prerequisites
- [setup mingw64](docs/mingw-setup.md)
- vscode

## running project with vscode
1. clone the repo
```
git clone https://github.com/your_username_/Project-Name.git
```
- or download as zip
  ![image](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/0748b673-1be1-4c92-b528-035b1f397346)

2. run build (currently configured through `tasks.json`)
 - note: if you have any extensions like `code runner` or any extensions related to compiling c++ projects, disable them. the extensions in ms c++ extensions pack is okay 
 - shortcut > `ctrl+shift+b` (executable is placed in build/ folder)
 - if you get errors at first, wait for a while since the tasks may take some time to load
 - restart vscode if you still get errors

![explorer_4G3FPNkqSo](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/dd017017-cfd0-4b80-8f2f-9e9553b124b2)


- all builds (executables) are placed in `/builds`
