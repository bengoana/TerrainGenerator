# Procedural terrain

Procedural terrain generator in openGL for graphics course. It uses a 2D perlin noise implementation to generate the terrain and water. The terrain is divided in chunks
that are rendered as the camera moves over the scene. The terrain has grass rendered using the geometry shader and the water uses multiple maps to simulate movement.

Camera controls:

wasd: movement.
qe: vertical movement.
mouse: camera.

Used libraries:

Rendering: OpenGL 3
Graphic window and input: GLFW https://www.glfw.org/.
Math operations: GLM https://glm.g-truc.net/0.9.9/index.html.
Threading (not currently used): px sched (pplux) https://github.com/pplux/px_sched.
Texture loading: stb_image https://github.com/nothings/stb.
Data arrays: scoped array (pplux).

