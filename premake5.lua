workspace "ECSTestWorkspace"
    configurations {"Debug", "Release"}


project "ECSTest"
    kind "ConsoleApp"
    targetdir "bin"

    files {
        "src/**.cpp",
        "include/**.h",
        "include/**.cpp"
    }

    includedirs {
        "include/"
    }

    include("vendor/RocLogger")

    filter "configurations:Debug"
        defines {"ROC_DEBUG"}
        symbols "On"
    
    filter "configurations:Release"
        kind "WindowedApp"
        defines {"ROC_RELEASE"}
        optimize "On"
