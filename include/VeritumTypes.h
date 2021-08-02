#pragma once

// contains all of the predefinitions for the classes both private and public
#include <stdint.h>
#include <sse_engine_export.h>

/**
 * Contains the implementation of the engine. This shouldn't be directly used from the application
 */
namespace vrtm {
	class IWindow;
	class Win32Window;
}

/**
 * Contains all of the classes available to use in the application.
 */
namespace Veritum {
	class Window;
}
