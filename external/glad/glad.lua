project "glad"
	kind "SharedLib"
	language "C"
	cdialect "c99"
	targetdir "../../bin"

	includedirs { "include" }
	
	links { "GL", "m" }

	filter "configurations:debug"
		defines { "DEBUG" }
		--optimize "On"
		symbols "On"

	filter "configurations:release"
		defines { "NDEBUG" }
		optimize "On"
	
	filter "system:emscripten"
		files { "src/gles2.c", "**.h" }
		cdialect "gnu99"
		kind "StaticLib"
		buildoptions { "-sMEMORY64=1" }
		linkoptions { "-sMEMORY64=1", "-mwasm64" }
	filter "not system:emscripten"
		files { "src/gl.c", "**.h" }
