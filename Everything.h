#pragma once

#include "types.h"
#include "StateStack.h"
#include <Furrovine++/ResourceCache.h>
#include <Furrovine++/WindowDriver.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/GraphicsDevice.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Text/TextDevice.h>
#include <functional>

struct Everything {
	std::reference_wrapper<Furrovine::WindowDriver> windowdriver;
	std::reference_wrapper<Furrovine::Graphics::Window> window;
	std::reference_wrapper<Furrovine::Graphics::GraphicsDevice> graphics;
	std::reference_wrapper<Furrovine::Text::TextDevice> textdevice;
	std::reference_wrapper<Furrovine::Graphics::NymphBatch> nymphbatch;
	std::reference_wrapper<Furrovine::ResourceCache<Furrovine::String>> cache;
	std::reference_wrapper<StateStack> states;
};
