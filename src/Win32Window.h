#pragma once

#include <config.h>
#ifdef WIN32
#include <Windows.h>
#endif

#include "IWindow.h"

namespace vrtm {

/**
 * This serves to provide window functionality to the windows nt system.
 */
class Win32Window : public IWindow
{
public:
	virtual void create(const char* title, uint32_t width, uint32_t height);
	virtual void destroy();
	virtual void pollEvents();

	virtual void setTitle(const char* title);
	virtual void setDimensions(const glm::uvec2 dimension);
	virtual void setWidth(const uint32_t width) { setDimensions(glm::uvec2(width, getHeight())); }
	virtual void setHeight(const uint32_t height) { setDimensions(glm::uvec2(getWidth(), height)); }

	virtual uint32_t getWidth() { return getDimensions().x; }
	virtual uint32_t getHeight() { return getDimensions().y; }
	virtual glm::uvec2 getDimensions();

	/**
	 * Handles the event callbacks from the windowing system.
	 */
	virtual LRESULT _wndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	/**
	 * This is required to create the window.
	 * 
	 * It is set and found on the \ref Win32Window::create() function.
	 */
	HINSTANCE hInst = NULL;
	HWND hWnd = NULL;
};

}
