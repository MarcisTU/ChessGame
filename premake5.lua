workspace "ChessGame"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

project "ChessGame"
    location "ChessGame"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/dependencies/SDL2/include"
    }

    links {
        "SDL2",
        "opengl32.lib",
        "SDL2main",
        "SDL2_image"
    }

    filter "system:windows"
        postbuildcommands {
            "{COPY} External %{cfg.targetdir}/",
            "{MKDIR} %{cfg.targetdir}/assets",
            "{COPY} assets %{cfg.targetdir}/assets"
        }

    libdirs { 
        "%{prj.name}/dependencies/SDL2/lib"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"