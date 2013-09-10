solution "GWEN"

	language "C++"
	location ( _ACTION )
	flags { "Unicode", "Symbols", "NoMinimalRebuild", "NoEditAndContinue", "NoPCH", "No64BitChecks" }
	targetdir ( "../lib/" .. _ACTION )
	libdirs { "../lib/", "../lib/" .. _ACTION }

	configurations
	{ 
		"Release",
		"Debug"
	}
	
	-- Multithreaded compiling
	if _ACTION == "vs2010" or _ACTION=="vs2008" then
		buildoptions { "/MP"  }
	end 

configuration "Release"
	defines { "NDEBUG" }
	flags{ "Optimize", "FloatFast" }
	includedirs { "../include/" }
	
configuration "Debug"
	defines { "_DEBUG" }
	includedirs { "../include/" }

project "GWEN DLL"
	uuid ( "74670653-3D57-A243-91B4-B2EEDF35DA95" )
	defines { "GWEN_COMPILE_DLL" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	kind "SharedLib"
	
	configuration "Release"
		targetname( "gwen" )
		
	configuration "Debug"
		targetname( "gwend" )

project "GWEN Static"
	uuid ( "99E8E26E-4171-4a0a-B6D8-020A0E63E436" )
	defines { "GWEN_COMPILE_STATIC" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "gwen_static" )
		
	configuration "Debug"
		targetname( "gwend_static" )
		
project "UnitTest"
	uuid ( "00F7E527-468D-4b79-9A35-F3386C0CF7F9" )
	files { "../unittest/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "unittest" )
		
	configuration "Debug"
		targetname( "unittestd" )
	
project "Renderer-DirectX9"
	uuid ( "2B44E691-45AD-4d4c-80B2-14028BB2DD36" )
	files { "../Renderers/DirectX9/DirectX9.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-DirectX9" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-DirectX9d" )
		
project "Renderer-OpenGL"
	uuid ( "C105C99D-90DA-4a81-8BFA-A35AD91F1A91" )
	files { "../Renderers/OpenGL/OpenGL.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-OpenGL" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-OpenGL" )

project "Renderer-GDI"
	uuid ( "617E3FC9-9449-4599-8A48-899989C171B2" )
	files { "../Renderers/GDIPlus/GDIPlus.cpp" }
	files { "../Renderers/GDIPlus/GDIPlusBuffered.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-GDI" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-GDI" )
		
project "Renderer-SFML"
	uuid ( "C462DEDF-B4FD-4cc9-9288-337B9FD0E4D2" )
	files { "../Renderers/SFML/SFML.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-SFML" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-SFML" )
		
project "Sample-DirectX9"
	uuid ( "033DFF57-E9FD-480b-9CD4-88A41E51923C" )
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/Direct3D/Direct3DSample.cpp" }
	kind "WindowedApp"
	
	links { "Renderer-DirectX9", "GWEN Static", "UnitTest" }

	configuration "Release"
		targetname( "DX9Sample" )
		
	configuration "Debug"
		targetname( "DX9Sample_D" )
		
project "Sample-OpenGL"
	uuid ( "797F4AE2-8804-4a25-B61F-D53056D6B93C" )
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/OpenGL/OpenGLSample.cpp" }
	kind "WindowedApp"
	
	links { "Renderer-OpenGL", "GWEN Static", "UnitTest", "opengl32", "FreeImage" }

	configuration "Release"
		targetname( "OpenGLSample" )
		
	configuration "Debug"
		targetname( "OpenGLSample_D" )

project "Sample-WindowsGDI"
	uuid ( "3C9B0F29-1EE5-4653-93F0-5BE242190512" )
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/WindowsGDI/WindowsGDI.cpp" }
	kind "WindowedApp"
	links { "Renderer-GDI", "GWEN Static", "UnitTest" }	
	
	configuration "Release"
		targetname( "GDISample" )
		
	configuration "Debug"
		targetname( "GDISample_D" )
		
project "Sample-SFML"
	uuid ( "955FF76A-C25F-4bac-835C-4F958252F1FC" )
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/SFML/SFML.cpp" }
	kind "WindowedApp"
	links { "Renderer-SFML", "GWEN Static", "UnitTest" }
	
	configuration "Release"
		targetname( "SFMLSample" )
		links { "sfml-main", "sfml-window-s", "sfml-graphics-s", "sfml-system-s" }
		
	configuration "Debug"
		targetname( "SFMLSample_D" )
		links { "sfml-main-d", "sfml-window-s-d", "sfml-graphics-s-d", "sfml-system-s-d" }