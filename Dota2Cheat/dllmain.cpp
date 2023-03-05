﻿// dllmain.cpp : Определяет точку входа для приложения DLL.
#pragma once
#include "pch.h"

#include <cstdio>
#include <iostream>
#include "MatchStateHandling.h"
#include "HookHelper.h"
#include "Input.h"
#include "UIState.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "Config.h"
#include "DebugFunctions.h"

#include "Hooks/EntitySystemEvents.h"

#include "Drawing.h"

#include "Lua/LuaModules.h"
#include "Lua/LuaInitialization.h"

#include "SDK/Base/Vector.h"
#include <MinHook.h>
#include "SDK/Globals/Interfaces.h"
#include "SDK/Globals/Signatures.h"
#include "SDK/Globals/GameSystems.h"
#include "SDK/Globals/Context.h"
#include "UI/Pages/MainMenu.h"

#pragma region Static variables

Vector Vector::Zero = Vector(0, 0, 0);
std::vector<std::unique_ptr<IGameEventListener2>> CGameEventManager::EventListeners{};

#pragma endregion

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}


static inline void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

uintptr_t WINAPI HackThread(HMODULE hModule) {
	// Initialize MinHook.
	if (MH_Initialize() != MH_OK)
		FreeLibraryAndExitThread(hModule, 0);

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	ctx.CurProcId = GetCurrentProcessId();
	ctx.CurProcHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ctx.CurProcId);

	ctx.lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

	ctx.lua.script("print(\"works!\")");
	Interfaces::FindInterfaces();
	Interfaces::LogInterfaces();

	Interfaces::CVar->DumpConVarsToMap();
#ifdef _DEBUG
	Signatures::FindSignatures(true);
#else
	Signatures::FindSignatures(false);
#endif // _DEBUG


	GameSystems::FindGameSystems();
	Hooks::SetUpByteHooks();
	VMTs::EntitySystem = std::unique_ptr<VMT>(new VMT(Interfaces::EntitySystem));
	VMTs::EntitySystem->HookVM(Hooks::OnAddEntity, 14);
	VMTs::EntitySystem->HookVM(Hooks::OnRemoveEntity, 15);
	VMTs::EntitySystem->ApplyVMT();
	Hooks::SetUpVirtualHooks(true);

	Lua::InitEnums(ctx.lua);
	Lua::InitClasses(ctx.lua);
	Lua::InitInterfaces(ctx.lua);
	Lua::LoadScriptFiles(ctx.lua);

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	constexpr const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#ifndef _DEBUG // wouldn't want the window to obscure the screen on a breakpoint
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
	glfwWindowHint(GLFW_DECORATED, 0);
	glfwWindowHint(GLFW_FLOATING, 1);
	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_MAXIMIZED, 1);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, 1);
#endif // DEBUG

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	auto* monitor = glfwGetPrimaryMonitor();
	if (!monitor)
		return 0;

	auto videoMode = glfwGetVideoMode(monitor);

	GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Dota2Cheat", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//auto vbeFont = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\trebuc.ttf)", 80.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
	auto defaultFont = io.Fonts->AddFontDefault();


	bool menuVisible = false;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::PushFont(defaultFont);
		if (menuVisible)
			Pages::MainMenu::Display(window);

		if (IsKeyPressed(VK_INSERT)) {
			glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, menuVisible);
			menuVisible = !menuVisible;
		}

		ImGui::PopFont();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		CheckMatchState(); // checking every frame
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	if (ctx.gameStage != Context::GameStage::NONE)
		LeftMatch();
	Modules::TargetedSpellHighlighter.OnDisableTargetedSpells();
	Modules::TargetedSpellHighlighter.OnDisableLinken();

	MH_Uninitialize();
	if (f) fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		//imgui ver
		HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0);
		if (thread)
			CloseHandle(thread);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

