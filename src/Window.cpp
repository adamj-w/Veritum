#include <Veritum.h>

#include <config.h>
#ifdef WIN32
#include "Win32Window.h"
#endif

namespace Veritum {

Window::Window(const char* title, unsigned int width, unsigned int height)
{
#ifdef WIN32
	_window = new vrtm::Win32Window();
	_window->create(title, width, height);
#else
#error "Unsure what windowing system to use. Please compile with cmake"
#endif
}

Window::~Window()
{
	close();
}

void Window::close()
{
	_window->destroy();
}

}