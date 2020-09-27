workspace "Game"
	configurations	{ "Debug", "Release" }
	platforms		{ "x64" }
	location		"build"
	characterset	"MBCS"
	startproject	"Game"

project "Game"
	kind		"WindowedApp"
	location	"build/Game"
	debugdir	"Game"

	files {
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"Game/Data/**.vert",
		"Game/Data/**.frag",
		"premake5.lua",
		".gitignore",
		"GenerateProjectFiles.bat",
	}

	includedirs {
		"Framework/Source",
		"Game/Source",
	}

	links {
		"Framework",
		"opengl32",
	}

project "Framework"
	kind		"StaticLib"
	location	"build/Framework"

	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/imgui/*.cpp",
		"Framework/Libraries/imgui/*.h",
	}

	includedirs {
		"Framework/Source",
	}
