solution "planfloor_solution"
  configurations { "Release", "Debug" }


project "PlanFloor"
  kind "ConsoleApp"
  language "C++"
  files    { "src/**.h","src/**.cpp" }
  includedirs { "src", "../kick/libs/include", "../kick/src", "/Users/morten/Programmering/cpp/boost_1_57_0" }
  buildoptions "-std=c++1y -stdlib=libc++"
  links { "Cocoa.framework", "GLUT.framework", "OpenGL.framework", "/Library/Frameworks/SDL2.framework", "/Library/Frameworks/SDL2_image.framework" }

  buildoptions { "-F/Library/Frameworks/" }
  linkoptions { "-F/Library/Frameworks/", "-lkick", "-L/Users/morten/Programmering/cpp/kick/lib/debug", "-F/Users/morten/Programmering/cpp/kick/lib/debug"}
  configuration "Debug"
    targetdir "bin/debug"
    defines { "DEBUG",  "GLM_FORCE_RADIANS" }
    flags { "Symbols" }		
    debugdir "../.."

  configuration "Release"
    targetdir "bin/release"
    defines { "NDEBUG",  "GLM_FORCE_RADIANS" }
    flags { "Optimize" } 	
    debugdir "../.."
	
  if _ACTION == "clean" then
    os.rmdir("bin")
  end
