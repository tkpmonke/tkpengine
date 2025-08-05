workspace "test-engine"
	architecture "x86_64"
	configurations { "Debug", "Release"}

include "external/cglm/cglm.lua"

project "test-engine"

	-- ensure up to date modules when building
	prebuildcommands {
		"@{ECHO} Building Module Registry",
		"python modules/build_modules.py"
	}

	kind "SharedLib"
	language "C"
	cdialect "c99"
	targetdir "bin"
	includedirs { "src", "modules", "external/cglm" }
	files { "src/**.c", "modules/**.c", "src/**.h", "modules/**.h" }

	warnings "Extra"

	-- filter "system:linux" 
	-- 	links { "X11", "Xrandr", "GL", "GLX", "m" }

	-- filter "system:windows"
	-- 	links { "gdi32", "user32", "shell32", "opengl32", "glu32", "m" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

project "test-editor"
	kind "ConsoleApp"
	language "C"
	cdialect "c99"
	targetdir "bin"
	includedirs { "src", "modules", "external/cglm" }
	files { "editor/**.c", "editor/**.h" }

	warnings "Extra"
	--sanitize { "Address", "UndefinedBehavior" }

	links { "test-engine" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

