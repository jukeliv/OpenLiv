![](https://github.com/susyboy23/OpenLiv/blob/main/res/textures/example_0.png)
# Simple Non-Profit 2D Game Engine made with C++ and OpenGL

## Dependencies
  - [GLFW](https://www.glfw.org)
  - [GLEW](http://glew.sourceforge.net)
  - [GLM](https://github.com/g-truc/glm)
  - [ImGui](https://github.com/ocornut/imgui)
  - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

## Screenshost
  - REMEMBER TO ADD SCREENSHOTS WHEN YOU HAVE SOMETHING TO SHOW DUMBASS
  
## Compiling - ( Only windows )
  -- Little side note, it only compiles on 32 bits, not 64, for now --
  - Get inside the solution, build "OpenLiv"
  - copy "res" and paste it inside "bin/Release-Win32/"
  - ( Last step is only on Release mode, in Debug, only open the app shortcut inside "bin/Debug-Win32/" )
  
## Comon errors
  - Shaders
    - So you are trying to compile a shader but it gives errors?
    - Maybe its cuz you have a "#version 330 core" or what ever version at the start, remove it
    - All that is handled by Shaders.h so you dont have to struggle with it
    - ( Also cuz it casued a lot of file reading errors )
    
## Plan
  - Editor
  - More devs
  - Make this Multiplatform
  - Add 64 bits build
  
## Thanks
  - [TheCherno](https://twitter.com/thecherno) for your epic OpenGL Series :)
