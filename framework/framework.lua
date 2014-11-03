
dofile("../mySdk/links.lua")

local myPath = os.getcwd();
local usedLibs = {"sdl", "glew", "glm"}

function SetupSolution(slnName)
	local currPath = os.getcwd();
	os.chdir(myPath);
	os.chdir("..");
	solution(slnName)
		targetdir ( "bin" )
		configurations {"Debug", "Release"}
		defines {"_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE", "_SCL_SECURE_NO_WARNINGS", "TIXML_USE_STL"}
		defines {"FREEGLUT_STATIC"}
		
    	configuration "windows"
        	defines {"WIN32"}
        	
       	configuration "linux"
    	    defines {"LOAD_X11"}
		
	os.chdir(myPath);
		
	project "framework"
		kind "StaticLib"
		language "c++"
		
		files  "../framework/*.cpp"
		files  "../framework/*.h"
		files  "../framework/*.hpp"
		excludes "../framework/empty.cpp"
		
		targetdir ( "$(SolutionDir)$(Configuration)\\" )
		objdir "" --$(Configuration)\\

		includedirs {"../framework"}
		
		UseLibs(usedLibs)
		
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			targetname("$(ProjectName)")

		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
			targetname("$(ProjectName)")


	os.chdir(currPath);
end

function SetupProject(projName, ...)
	project(projName)
		kind "ConsoleApp"
		language "c++"

		targetdir ( "$(SolutionDir)$(Configuration)\\" )
		objdir "" 
		
		files {...}
		files  "*.cpp"
		files  "*.h"
		files  "*.hpp"

		includedirs {"../framework"}
			
		links "framework"

		--Must be after including framwork... because GCC is stupid.
		UseLibs(usedLibs)

		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags "Symbols"
			targetname("$(ProjectName)") --projName .. "D"
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"};
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
			targetname("$(ProjectName)")

		configuration {"windows"}
			links {"glu32", "opengl32", "gdi32", "winmm", "user32"}

	    configuration "linux"
	        links {"GL", "GLU"}

end

