# Simple Non-Profit 2D Game Engine made with C++ and OpenGL
![](https://github.com/susyboy23/OpenLiv/blob/main/res/textures/Logo.png)

![](https://github.com/susyboy23/OpenLiv/blob/main/res/textures/Examples/example_image_0.png)
  
# Compiling - ( Only windows )
  -- Little side note, it only compiles on 32 bits, not 64, for now --
  - Get inside the solution, build "OpenLiv"
  - copy "res" and paste it inside "bin/Release-Win32/"
  - ( Last step is only on Release mode, in Debug, only open the app shortcut inside "bin/Debug-Win32/" )
  
# Comon errors
  ### Textures
    Your texture shows in screen, but it looks strange?
    The reason is that this engine, only suports square res images
    i.e 24x24, 50x50, 124x123
    and it will deform everything that isnt in a square res
  ### Shaders
    So you are trying to compile a shader but it gives errors?
    maybe its cuz you have a "#version 330 core" or what ever version at the start, remove it
    all that is handled by Shaders.h so you dont have to struggle with it
    ( Also cuz it casued a lot of file reading errors )


# Dependencies
  - [GLFW](https://github.com/taniwha/glfw/commits/master/include/GLFW/glfw3.h)
  - [GLEW](http://glew.sourceforge.net)
  - [GLM](https://github.com/g-truc/glm)
  - [ImGui](https://github.com/ocornut/imgui)
  - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

# Plan
  - Simple escene Editor
  - Make this Multiplatform
  - Add 64 bits build
  - 3D Rendering in the future?
  
# Thanks
  - [TheCherno](https://twitter.com/thecherno) for your epic OpenGL Series :)
  - [Taniwha](https://github.com/taniwha) thanks for all the help in discord mate
