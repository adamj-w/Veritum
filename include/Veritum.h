#pragma once

#include "VeritumTypes.h"
#include "Window.h"

#include <stdexcept>

/**
 * \brief Starts the Veritum engine.
 * 
 * @returns 0 if the engine successfully initialized
 */
extern "C" SSEAPI int VeritumInit();

/**
 * \brief Stops the Veritum engine and destroy/closes all associated resources.
 */
extern "C" SSEAPI void VeritumClose();
