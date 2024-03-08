project "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
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

    includedirs { "Source/Include" }

    -- Libraries
    include_raylib()
    link_raylib()

    postbuildcommands { "{COPYDIR} %[../Resources/] %[%{!cfg.targetdir}]" }

    -- Project settings
    filter {"action:vs*", "configurations:Release"}
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
	
    filter "configurations:Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        defines { "NDEBUG" }

    vpaths
    {
        ["Entrypoint"] = { "Source/Application.cpp", "Source/Include/Application.hpp", "Source/main.cpp" },
        ["Game/Rendering"] = { "Source/Chess.cpp", "Source/Include/Chess.hpp", "Source/Textures.cpp", "Source/Include/Textures.hpp" },
        ["Game/Logic"] = { "Source/GameState.cpp", "Source/Include/GameState.hpp", "Source/ChessField.cpp", "Source/Include/ChessField.hpp", "Source/Include/ChessColor.hpp", "Source/Include/ChessPiece.hpp" },
        ["Utility"] = { "Source/Utility.cpp", "Source/Include/Utility.hpp", "Source/Include/Constants.hpp", "Source/Include/Vector2.hpp" }
    }