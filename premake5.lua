---@diagnostic disable: undefined-global
workspace "Chess"
    architecture "x64"
    configurations { "Debug", "Release" }

OUTPUTDIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Chess"
    location "Chess"
    kind "WindowedApp"
    language "C++"
    cppdialect "c++20"

    targetdir("bin/" .. OUTPUTDIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUTDIR .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
    includedirs { "vendor/SFML-2.5.1/include" }
    libdirs { "vendor/SFML-2.5.1/lib" }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
        defines { "SFML_STATIC" }
        files { "%{prj.name}/resource.h", "%{prj.name}/assets/**.ico", "%{prj.name}/**.rc" }
        vpaths { ['Resources/*'] = { '*.rc', '**.ico' }}
        --        linkoptions "/NODEFAULTLIB:MSVCRTD"
        
        filter "configurations:Release"
        buildoptions "/MD"
        defines { "NDEBUG" }
        optimize "On"
        links {
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "sfml-graphics-s",
            "sfml-window-s",
            "sfml-system-s",
            "sfml-main"
        }
        filter "configurations:Debug"
        defines { "_DEBUG" }
        buildoptions "/MDd"
        linkoptions "/SUBSYSTEM:CONSOLE"
        symbols "On"
        links {
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "sfml-graphics-s-d",
            "sfml-window-s-d",
            "sfml-system-s-d"
        }

--        postbuildcommands {
--            "{COPY} source target"
--        }