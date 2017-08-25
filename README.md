# Anim Edit

AnimEdit is a very simple animation cycle editor coded with OpenGL.

Idea came with the need to design some simple character animation sequences, required by some mini-games i'm working on.

## Dependencies

There are not many dependencies, for such a project, i believe.

### Graphics

Rendering performed by OpenGL, GLFW used for OpenGL access, FTGL used for fonts.

### System

Boost system libraries (io_service) used for event passing infrastructure.

### JSON for Load / Save Animation

Version 2.1.1 of "JSON for Modern C++" library used to load/save animation data. Thanks Niels Lohmann for his great JSON library.

https://github.com/nlohmann/json.git