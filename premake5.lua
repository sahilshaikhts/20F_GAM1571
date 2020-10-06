workspace "Game"

	configurations{"Debug","Release"}
	platforms{"x64"}

	location "build"
	characterset "MBCS"
	startproject	"Game"

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

project "Framework"
	kind "staticlib"
	location "build/Framework"

files
{
	"Framework/Source/**.cpp",
	"Framework/Source/**.h",
	"Framework/Libraries/imgui/*cpp",
	"Framework/Libraries/imgui/*.h",	
}

includedirs
{
	"Framework/Source",
}
