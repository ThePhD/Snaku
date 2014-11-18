#pragma once

#include "StateStack.hpp"
#include <Furrovine++/ResourceCache.hpp>
#include <Furrovine++/WindowDriver.hpp>
#include <Furrovine++/Graphics/Window.hpp>
#include <Furrovine++/Graphics/GraphicsDevice.hpp>
#include <Furrovine++/Graphics/NymphBatch.hpp>
#include <Furrovine++/Text/TextDevice.hpp>
#include <functional>

struct Everything {
	std::reference_wrapper<Furrovine::WindowDriver> windowdriver;
	std::reference_wrapper<Furrovine::Graphics::Window> window;
	std::reference_wrapper<Furrovine::Graphics::GraphicsDevice> graphics;
	std::reference_wrapper<Furrovine::Text::TextDevice> textdevice;
	std::reference_wrapper<Furrovine::Graphics::NymphBatch> nymphbatch;
	std::reference_wrapper<Furrovine::ResourceCache<Furrovine::string>> cache;
	std::reference_wrapper<StateStack> states;
};
