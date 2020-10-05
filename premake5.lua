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
<<<<<<< HEAD
	"Framework/Libraries/imgui/*cpp",
	"Framework/Libraries/imgui/*.h",	
=======
	"Framework/Libraries/iamgui/*cpp",
	"Framework/Libraries/iamgui/*.h",	
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
}

includedirs
{
	"Framework/Source",
<<<<<<< HEAD
=======
	"Framework/Libraries",
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
}
