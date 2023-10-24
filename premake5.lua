filter {}

    files {
        "src/**.cpp",
        "include/**.h",
        "include/**.cpp"
    }

    dofile("vendor/RocLogger/premake5.lua")

    filter "configurations:Debug"
        defines {"ROC_DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        kind "WindowedApp"
        defines {"ROC_RELEASE"}
        optimize "On"

filter {}
