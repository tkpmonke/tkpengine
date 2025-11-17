workspace "test-engine"
	architecture "x86_64"
	configurations { "Debug", "Release"}

include "external/cglm/cglm.lua"
include "external/rgfw/rgfw.lua"

project "tkpengine"

	-- ensure up to date modules when building
	prebuildcommands {
		"@{ECHO}\nBuilding Module Registry",
		"python modules/build_modules.py",
		"@{ECHO}\n",
	}

	kind "SharedLib"
	language "C"
	cdialect "c99"
	targetdir "bin"
	includedirs { "src", "modules", "external/cglm" }
	files { "src/**.c", "modules/**.c", "src/**.h", "modules/**.h" }

	links { "cglm", "rgfw" }

	warnings "Extra"

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

	links { "tkpengine" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

