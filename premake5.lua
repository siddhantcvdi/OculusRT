-- premake5.lua
workspace "OculusRT"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "OculusRT"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "OculusRT"