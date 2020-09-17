workspace "Game"
	configurations{"Debug","Release"}
	location "build"
	platforms{"x64"}

project "Game"
	location "build/Game"
	kind "WindowedApp"

files
{
	"Game/Source/**.cpp",
	"Game/Source/**.h",
	"GenerateProjectFiles.bat",
	"premake5.lua",
	".gitignore"
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
	kind "staticLib"
	location "build/Framework"

files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
	}

	includedirs {
		"Framework/Source",
	}
