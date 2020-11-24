workspace "Game"

	configurations{"Debug","Release"}
	platforms{"x64"}

	location "build"
	characterset "MBCS"
	startproject	"Game"

filter"configurations:Debug"
	symbols "on"

project "Game"
	location "build/Game"
	kind "WindowedApp"
	debugdir "Game"

files
{
	"Game/Source/**.cpp",
	"Game/Source/**.h",
	"Game/Data/**.vert",
	"Game/Data/**.frag",
	"GenerateProjectFiles.bat",
	"premake5.lua",
	".gitignore",
}

includedirs
{
	"Framework/Source",
	"Game/Source",
	
}

links
{
	"Framework",
	"opengl32",
}

pchheader"GamePCH.h"
pchsource "Game/Source/WinMain.cpp"


project "GameTileMap"
	location "build/GameTileMap"
	kind "WindowedApp"
	debugdir "GameTileMap"

files
{
	"GameTileMap/Source/**.cpp",
	"GameTileMap/Source/**.h",
	"GameTileMap/Data/**.vert",
	"GameTileMap/Data/**.frag",
	"GameTileMap/Data/**.json",
}

includedirs
{
	"Framework/Source",
	"GameTileMap/Source",
	
}

links
{
	"Framework",
	"opengl32",
}

pchheader"GamePCH.h"
pchsource "GameTileMap/Source/WinMain.cpp"

project "Framework"
	kind		"StaticLib"
	location	"build/Framework"

files 
{
	"Framework/Source/**.cpp",
	"Framework/Source/**.h",
	"Framework/Libraries/imgui/*.cpp",
	"Framework/Libraries/imgui/*.h",
	"Framework/Libraries/stb/*.h",
	"Framework/Libraries/rapidjson/**.h",
}

includedirs
{
	"Framework/Source",
}
pchheader "FrameworkPCH.h"
pchsource "Framework/Source/Core/FWCore.cpp"

filter "files:Framework/Libraries/imgui/*.cpp"
	flags { "NoPCH" }