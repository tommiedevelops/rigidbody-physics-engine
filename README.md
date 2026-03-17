# CPP 3D Physics Engine

A 3D Physics engine written in C++ for the purpose of learning how they work.

## Requirements
* OpenGL 3.0 or greater
- Check with OpenGL Viewer Extension on Windows
- Check with XXX for Linux
- Check with XXX for mac

* GLAD for dynamically retrieving OpenGL functions
- Use this website to get zip file and extract into external/glad directory
- https://glad.dav1d.de/

* GLFW for handling Window creation and management
- should already be a submodule but if not clone from glfw github


## Scope
- Develop a 3D physics engine with collisions, gravity, friction, restitution.
- Render the scene with a basic renderer using OpenGL
- Write the engine in C++

## Initial System Design
- It will use an App / Core architecture
- App contains application specific code and the main function
- Core is remains constant regardless of the application and contains a renderer and physics solver

<img src="Docs/Diagrams/system_diagram.svg" width = "800">

## Dependencies
- For WSL2

```
sudo apt update
```

installing OpenGL:
```
sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

installing g++ (cpp compiler)
```
sudo apt install -y build-essential
```

installing cmake
```
sudo apt install -y cmake
```

