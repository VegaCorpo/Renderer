#include "ImGUILayer.hpp"
#include "imgui.h"
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "raylib.h"
#include "rlgl.h"
#include <GLFW/glfw3.h>

void render::ImGUILayer::init(GLFWwindow* window)
{
    std::cout << "[ImGUILayer] init called, window=" << window << std::endl;
    this->_window = window;
    this->_isShutdown = false;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    bool glfw_ok = ImGui_ImplGlfw_InitForOpenGL(window, true);
    bool gl_ok   = ImGui_ImplOpenGL3_Init("#version 130");
    std::cout << "[ImGUILayer] glfw_ok=" << glfw_ok << " gl_ok=" << gl_ok << std::endl;
}

void render::ImGUILayer::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)GetRenderWidth(), (float)GetRenderHeight());

    ImGui::NewFrame();

    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    static float f = 0.0f;
    static int counter = 0;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::End();

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();

    rlDrawRenderBatchActive();
    rlDisableScissorTest();
    rlDisableDepthTest();
    rlDisableBackfaceCulling();

    glViewport(0, 0, GetRenderWidth(), GetRenderHeight());
    ImGui_ImplOpenGL3_RenderDrawData(drawData);

    rlEnableDepthTest();
    rlEnableBackfaceCulling();
}

void render::ImGUILayer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    if (ImGui::GetCurrentContext() != nullptr)
        ImGui::DestroyContext();
    this->_isShutdown = true;
}
