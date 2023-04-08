project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"
  
   targetdir "bin/%{cfg.buildcfg}"
   objdir    "bin/Obj/%{cfg.buildcfg}"

   files {
      "**.h", 
      "**.hpp", 
      "**.cpp",
      "*.lua",
      "*.dll"
   }

   defines { 
      "SFML_STATIC",
   }

   includedirs {
      "include",
      "../include",
   }

   libdirs {
      "../libs/SFML/ext",
   }

   links {
      "opengl32",
      "openal32",
      "freetype",
      "winmm",
      "gdi32",
      "flac",
      "vorbisenc",
      "vorbisfile",
      "vorbis",
      "ogg",
      "ws2_32",
      "legacy_stdio_definitions",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      libdirs { 
         "../libs/SFML/debug",
      }

      links {
         "sfml-graphics-s-d",
         "sfml-window-s-d",
         "sfml-system-s-d",
         "sfml-audio-s-d",
         "sfml-network-s-d"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      libdirs { 
         "../libs/SFML/release",
      }

      links {
         "sfml-graphics-s",
         "sfml-window-s",
         "sfml-system-s",
         "sfml-audio-s",
         "sfml-network-s"
      }