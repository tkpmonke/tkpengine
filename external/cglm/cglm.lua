-- BUILD CGLM 0.9.6

project "cglm"
   kind "SharedLib"
   language "C"
   cdialect "c99"
   targetdir "../../bin"

   includedirs { "cglm" }
   files { "src/**.c", "cglm/**.h" }
   
   links { "GL", "m" }

   filter "configurations:debug"
      defines { "DEBUG" }
      --optimize "On"
      symbols "On"

   filter "configurations:release"
      defines { "NDEBUG" }
      optimize "On"
