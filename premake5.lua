workspace "hazil"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "hazil/vendor/GLFW/include"
IncludeDir["Glad"] = "hazil/vendor/Glad/include"
IncludeDir["Imgui"] = "hazil/vendor/imgui"
IncludeDir["glm"] = "hazil/vendor/glm"
IncludeDir["stb_image"] = "hazil/vendor/stb_image"




-- Include premake.lua to the file
include "hazil/vendor/GLFW"
include "hazil/vendor/Glad"
include "hazil/vendor/imgui"


project "hazil"
	location "hazil"
	kind "StaticLib"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "hazil/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
		

	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "on"
	
	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "on"
	
	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "on"
	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"hazil/vendor/spdlog/include",
		"hazil/src",
		"hazil/vendor",
		"%{IncludeDir.glm}"

	}

	links
	{
		"hazil"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",

		}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "on"
	
	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "on"
	
	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "on"