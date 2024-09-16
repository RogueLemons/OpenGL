=== README ===
The include .lib and headers are found in the CharisAPI folder.

This folder contains a project for a quick and easy to use graphics API called Charis. 
Charis is a wrapper around OpenGL where the intent is for the user to only care 
about designing models and shaders. Charis is not a project about optimization, but
instead a project about simplyfying the process of getting fun things on screen 
(and for me to better understand OpenGL).

The TestProject folder is not included in Charis. Instead it is a tiny demo of how
Charis works. Start by looking at the function HelloTriangle(), then HelloSquare(),
and finally HelloBackpack().

To load models the dll in the CharisAPI folder is required. Charis expects loaded 
models to use relative paths to textures, as is done in the HelloBackpack() example.
If that is confusing, look at this video: https://www.youtube.com/watch?v=4DQquG_o-Ac 
