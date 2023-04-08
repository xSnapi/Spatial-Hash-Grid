-- premake5.lua
workspace "Spatial Hash Grid"
   startproject "Flowers"
   architecture "x64"
   configurations {
      "Debug", 
      "Release" 
   }

   filter { "platforms:Win64" }
      system "Windows"
      
include "Sandbox"