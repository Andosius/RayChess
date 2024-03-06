project "Core"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"
	staticruntime "off"

    -- Output directories
	targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
	objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    debugdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")

    -- Files to build and configurations
    files { 
        "Source/**.cpp", 
        "Source/Include/**.hpp"
    }

    files { "../Assets/**.png" }
    buildaction "Embed"

    includedirs { "Source/Include" }
    include_raylib()

    defines {
    }

    -- Libraries
    link_raylib()

    postbuildcommands { "{COPYFILE} %[../Assets/**.png] %[%{!cfg.targetdir}]" }

    -- Cross platform settings
    filter "configurations:Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        defines { "NDEBUG" }
--[[
    -- Windows
    -- Configure Debug
    filter { "system:windows", "configurations:Debug" }
        runtime "Debug"
        
        buildoptions { "/bigobj", "/sdl", "/Zc:preprocessor", "/MP", "/Od", "/DEBUG", "/utf-8" }
        linkoptions { "/DEBUG", "/NODEFAULTLIB:library" }
        defines { "DEBUG" }

    -- Configure Release
    filter { "system:windows", "configurations:Release" }
        runtime "Release"
        optimize "On"

        buildoptions { "/bigobj", "/sdl", "/Zc:preprocessor", "/MP", "/O2", "/Oi", "/Oy", "/GL", "/Gy" }
        linkoptions { "/NODEFAULTLIB:library" }
        defines { "NDEBUG" }

    -- Linux & macOS
    filter { "system:not windows", "configurations:Debug" }
        buildoptions { "-pthread", "-fPIC", "-g", "-Og" }

    filter { "system:not windows", "configurations:Release" }
        buildoptions { "-pthread", "-fPIC", "-O3" }
]]