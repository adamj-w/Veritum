#pragma once

#include <glm/glm.hpp>
#include <stdint.h>
#include <VeritumTypes.h>

namespace vrtm {

/**
 * \brief This interface is to be extended for each windowing system.
 * 
 * It contains methods that must be implemented so it can be used by the Veritum::Window class
 */
class IWindow
{
public:
	virtual void create(const char* title, uint32_t width, uint32_t height) = 0;
	virtual void destroy() = 0;
	virtual void pollEvents() = 0;

	virtual void setTitle(const char* title) = 0;
	virtual void setDimensions(const glm::uvec2 dimension) = 0;
	virtual void setWidth(const uint32_t width) = 0;
	virtual void setHeight(const uint32_t height) = 0;

	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual glm::uvec2 getDimensions() = 0;

protected:
	//Veritum::Window& window;
};

}
