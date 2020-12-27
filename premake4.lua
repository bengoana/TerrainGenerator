
solution ("PTG" .. _ACTION)
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	language "C++"
	location ("build")	

  includedirs {
  	"./include",
    "deps",
    "./deps/glfw/src",
    "./deps/glfw/deps",
    "./deps/glfw/deps/glad",
    "./deps/glfw/deps/mingw",
    "./deps/glfw/deps/vs2008",
    "./deps/glfw/include",
  }  

  project "Procedural Terrain"
  kind "ConsoleApp"
	targetname ("NGE")
	language "C++"
  prj_path = "./build/" .. "NGE"
  --links {"./deps/libs/NGEL" }

  location (prj_path .. "/" .. _ACTION)

  defines { "_CRT_SECURE_NO_WARNINGS", "_GLFW_WIN32", "WITH_MINIAUDIO", "__STDC_LIMIT_MACROS"}
  flags { "ExtraWarnings" }

  configuration "vs2019"
    windowstargetplatformversion "10.0.18362.0"
    --windowstargetplatformversion "10.0.17763.0"
  
  configuration "Debug"
    defines { "DEBUG" }
    targetdir ("bin/executables/Debug")
    targetsuffix "_d"
    objdir ("build/" .. "Debug")
    flags { "Symbols", "NoPCH" }
    
  configuration "Release"
    targetdir ("bin/executables/Release")
    objdir ("build/" .. "Release")
    flags { "Optimize", "NoPCH" }

  project "Procedural Terrain"
  files {
  --GLFW common headers
    "./deps/glfw/src/internal.h",
    "./deps/glfw/src/mappings.h",
    "./deps/glfw/src/glfw_config.h.in",
    "./deps/glfw/include/GLFW/glfw3.h", 
    "./deps/glfw/include/GLFW/glfw3native.h",
    --GLFW win32 headers
    "./deps/glfw/src/win32_platform.h" ,
    "./deps/glfw/src/win32_joystick.h" ,
    "./deps/glfw/src/wgl_context.h" ,
    "./deps/glfw/src/egl_context.h",
    "./deps/glfw/src/osmesa_context.h",
    --GLFW common src
    "./deps/glfw/src/context.c",
    "./deps/glfw/src/init.c",
    "./deps/glfw/src/input.c",
    "./deps/glfw/src/monitor.c",
    "./deps/glfw/src/window.c",
    "./deps/glfw/deps/glad_gl.c",
    "./deps/glfw/deps/glad_vulkan.c",
    "./deps/glfw/src/vulkan.c",
    --GLFW win32 src
    "./deps/glfw/src/win32_init.c",
    "./deps/glfw/src/win32_joystick.c",
    "./deps/glfw/src/win32_monitor.c",
    "./deps/glfw/src/win32_time.c",
    "./deps/glfw/src/win32_thread.c",
    "./deps/glfw/src/win32_window.c",
    "./deps/glfw/src/wgl_context.c",
    "./deps/glfw/src/egl_context.c",
    "./deps/glfw/src/osmesa_context.c",
    --GLM
    "./deps/glm/**.h",
    "./deps/glm/**.inl",


    "./deps/*.h",
    "./include/**.h",
    "./src/**.cc",
    "src/main.cc",
  }


