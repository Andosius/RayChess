workspace "Chess"
    location "build"
    startproject "Game"

    configurations { "Debug", "Release"}
    platforms { "x64", "x86", "ARM64"}

    defaultplatform ("x64")

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }
        architecture "x86_64"
        
    filter { "platforms:Arm64" }
        architecture "ARM64"

    filter {}


include "Dependencies.lua"
include "Chess-Game/Build-Game.lua"
