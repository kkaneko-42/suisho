﻿#include "rendering/RenderingSystem.h"
#include <stdexcept>

using namespace suisho;

RenderingSystem::RenderingSystem() {
    if (!renderer_.initialize()) {
        throw std::runtime_error("Renderer2D initialization failed");
    }
}

RenderingSystem::~RenderingSystem() {
    renderer_.terminate();
}

void RenderingSystem::update(Params& params) {
    renderer_.draw();
}
