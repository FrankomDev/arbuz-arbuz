workspace "game"
configurations { "Debug", "Release" }
location "build"

project "game"
kind "WindowedApp"
language "C++"
toolset "gcc"

files { "./src/*.cpp", "./src/*.h" }

-- libdirs { "./external/raylib/lib" }
-- includedirs { "./external/raylib/include" }

filter "system:Windows"
system "windows"
links { "raylib", "winmm", "gdi32", "ssp", "box2d" }
linkoptions { "-static-libgcc", "-static-libstdc++", "-static" }

filter "system:Linux"
system "linux"
links { "raylib", "box2d" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"
targetdir "build"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"
targetdir "build/release"
