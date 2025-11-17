
project "rgfw"
   kind "SharedLib"
   language "C"
   cdialect "c99"
   targetdir "../../bin"

   includedirs { "cglm" }
   files { "**.c", "**.h" }
   
	filter "system:linux" 
		links { "X11", "Xrandr", "GL", "GLX" }

	filter "system:windows"
		links { "gdi32", "opengl32" }


   filter "configurations:debug"
      defines { "DEBUG" }
      --optimize "On"
      symbols "On"

   filter "configurations:release"
      defines { "NDEBUG" }
      optimize "On"
