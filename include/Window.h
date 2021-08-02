#pragma once

#include "VeritumTypes.h"

namespace Veritum {

/**
 * \brief A class that wraps around the OS specific window.
 */
class SSEAPI Window final
{
public:
	/**
	 * \brief Creates a new window that can be used for rendering.
	 * 
	 * @param title The title of the window
	 * @param width The width of the windows renderable area in pixels
	 * @param height The height of the windows renderable area in pixels
	 */
	Window(const char* title = "Veritum", unsigned int width = 100, unsigned int height = 100);

	/**
	 * Closes the window and all associated resources.
	 */
	~Window();

	/**
	 * \brief Closes the window and all of the resources associated with that window.
	 */
	void close();

private:
	vrtm::IWindow* _window;
};

}
