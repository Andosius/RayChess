-- Minecraft Bot Dependencies

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

IncludeDir = {}


LibraryDir = {}


if (not os.isdir("Dependencies/raylib-master")) then
    include "Dependencies/FetchRaylib.lua"
end
include "Dependencies/Raylib.lua"