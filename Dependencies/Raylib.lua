
function platform_defines()
    defines{"PLATFORM_DESKTOP"}

    filter {"options:graphics=opengl43"}
        defines{"GRAPHICS_API_OPENGL_43"}

    filter {"options:graphics=opengl33"}
        defines{"GRAPHICS_API_OPENGL_33"}

    filter {"options:graphics=opengl21"}
        defines{"GRAPHICS_API_OPENGL_21"}

    filter {"options:graphics=opengl11"}
        defines{"GRAPHICS_API_OPENGL_11"}

    filter {"system:macosx"}
        disablewarnings {"deprecated-declarations"}

    filter {"system:linux"}
        defines {"_GNU_SOURCE"}
-- This is necessary, otherwise compilation will fail since
-- there is no CLOCK_MONOTOMIC. raylib claims to have a workaround
-- to compile under c99 without -D_GNU_SOURCE, but it didn't seem
-- to work. raylib's Makefile also adds this flag, probably why it went
-- unnoticed for so long.
-- It compiles under c11 without -D_GNU_SOURCE, because c11 requires
-- to have CLOCK_MONOTOMIC
-- See: https://github.com/raysan5/raylib/issues/2729

    filter{}
end

function link_raylib()
    links {"raylib"}

    includedirs {"../Dependencies/raylib-master/src" }
    includedirs {"../Dependencies/raylib-master/src/external" }
    includedirs {"../Dependencies/raylib-master/src/external/glfw/include" }
    platform_defines()

    filter "action:vs*"
        defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        dependson {"raylib"}
        links {"raylib.lib"}
        characterset ("MBCS")
        buildoptions { "/Zc:__cplusplus" }

    filter "system:windows"
        defines{"_WIN32"}
        links {"winmm", "kernel32", "opengl32", "gdi32"}
        libdirs { "../Binaries/" .. OutputDir .. "/raylib" }

    filter "system:linux"
        links {"pthread", "GL", "m", "dl", "rt", "X11"}

    filter "system:macosx"
        links {"OpenGL.framework", "Cocoa.framework", "IOKit.framework", "CoreFoundation.framework", "CoreAudio.framework", "CoreVideo.framework", "AudioToolbox.framework"}

    filter{}
end

function include_raylib()
    includedirs {"../Dependencies/raylib-master/src" }
    includedirs {"../Dependencies/raylib-master/src/external" }
    includedirs {"../Dependencies/raylib-master/src/external/glfw/include" }
    platform_defines()

    filter "action:vs*"
        defines {"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}

    filter{}
end

project "raylib"
    kind "StaticLib"
    language "C"

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
	objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    
    platform_defines()

    filter "action:vs*"
        defines {"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS"}
        characterset ("MBCS")
        buildoptions { "/Zc:__cplusplus" }
    filter{}

    includedirs {
        "../Dependencies/raylib-master/src",
        "../Dependencies/raylib-master/src/external/glfw/include" 
    }
    
    files {
        "../Dependencies/raylib-master/src/*.h", 
        "../Dependencies/raylib-master/src/*.c"
    }

    removefiles {"../Dependencies/raylib-master/src/rcore_*.c"}

    filter { "system:macosx", "files:Dependencies/raylib-master/src/rglfw.c" }
        compileas "Objective-C"

    filter{}

    vpaths
    {
        ["Header Files"] = { "../Dependencies/raylib-master/src/**.h"},
        ["Source Files/*"] = { "../Dependencies/raylib-master/src/**.c"},
    }
