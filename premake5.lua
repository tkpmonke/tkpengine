workspace "test-engine"
   architecture "x86_64"
   configurations { "Debug", "Release"}

project "test-engine"
   kind "SharedLib"
   language "C"
   cdialect "c99"
   targetdir "bin"
   includedirs { "src", "external" }
   files { "src/**.c", "src/**.h" }

	warnings "Extra"

	filter "system:linux" 
		links { "X11", "Xrandr", "GL", "GLX", "m" }

	filter "system:windows"
		links { "gdi32", "user32", "shell32", "opengl32", "glu32", "m" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
