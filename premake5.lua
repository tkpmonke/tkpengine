workspace "test-engine"
	architecture "x86_64"
	configurations { "Debug", "Release"}

include "external/cglm/cglm.lua"
include "external/glad/glad.lua"
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

	links { "cglm", "glad", "rgfw" }

	warnings "Extra"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	filter {}
		
	filter "system:emscripten"
		cdialect "gnu99"
		kind "StaticLib"
		buildoptions { "-sMEMORY64=1" }
		linkoptions { "-sMEMORY64=1", "-mwasm64", "-sUSE_WEBGL2=1", "-sASYNCIFY" }


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

	filter "system:emscripten"
		cdialect "gnu99"
		buildoptions { "-sMEMORY64=1" }
		linkoptions { "-sMEMORY64=1", "-mwasm64", "-sUSE_WEBGL2=1", "-sASYNCIFY" }
		targetextension ".html"
		
		links { "tkpengine", "cglm", "glad", "rgfw" }

