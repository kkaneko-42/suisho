#include "rendering/Renderer2D.h"

using namespace suisho;

Renderer2D::Renderer2D() {

}

Renderer2D::~Renderer2D() {

}

bool Renderer2D::initialize() {
    return device_.initialize();
}

void Renderer2D::terminate() {
    device_.terminate();
}

bool Renderer2D::shouldWindowClose() const {
    return device_.isWindowClosed();
}

bool Renderer2D::beginFrame() {
    return true;
}

void Renderer2D::endFrame() {

}
