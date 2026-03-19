#include "UIEngine.hpp"
#include "ImGUILayer.hpp"
#include <iostream>

void render::UIEngine::init(GLFWwindow* window)
{
    std::cout << "[UIEngine] init called, window=" << window << std::endl;
    auto layer = std::make_unique<ImGUILayer>();
    layer->init(window);
    this->_layer = std::move(layer);
    std::cout << "[UIEngine] layer created: " << (this->_layer != nullptr) << std::endl;
}

void render::UIEngine::render()
{
    std::cout << "[UIEngine] render called, layer=" << (this->_layer != nullptr) << std::endl;
    if (this->_layer)
        this->_layer->render();
}

void render::UIEngine::update(float dt, float w, float h)
{
    (void)dt; (void)w; (void)h;
}