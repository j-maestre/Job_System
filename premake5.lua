build_configurations = { "Debug", "RelWithDebInfo", "Release"}

workspace "JobSystemEngine"
  architecture "x86_64"

  startproject "Sandbox"

  configurations{
    build_configurations
  }

  flags{
    "MultiProcessorCompile"
  }

group "Core"

project "JobSystem"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"
  staticruntime "Off"

  location "build/%{prj.name}"

  targetdir "bin/%{cfg.buildcfg}"

  objdir "build/%{prj.name}/%{cfg.buildcfg}"



  defines{
    "_CRT_SECURE_NO_WARNINGS"
  }

  includedirs{
    "include",
    "src",
  }

  files{
    "include/**.h",
    "include/**.hpp",
    "src/**.*",
    "premake5.lua"
  }


  filter "configurations:Debug"
    defines { "DEBUG" }
    runtime "Debug"
    optimize "Debug"
    symbols "on"

  filter "configurations:Release"
    defines { "NDEBUG" }
    runtime "Release"
    optimize "Speed"
    symbols "off"

  
  filter "configurations:RelWithDebInfo"
    defines { "DEBUG" }
    runtime "Release"
    optimize "on"
    symbols "on"

group ""

group "Examples"
  include "examples/Sandbox"
group ""