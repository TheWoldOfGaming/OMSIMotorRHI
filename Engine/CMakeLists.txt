add_library(Engine STATIC
	Platform/Win32Window.cpp
	Platform/WindowFactory.cpp
	Application/Application.cpp
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})