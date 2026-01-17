/**
 * @file ScaledDeltaTimer.cpp
 * @brief 实现 ScaledDeltaTimer 的帧间计时与时间缩放逻辑。
 */

#include "ScaledDeltaTimer.h"

#include <SDL2/SDL.h>

/**
 * @brief 启动计时器，记录当前时间为上一帧时间。
 */
void ScaledDeltaTimer::Start()
{
	lastFrameTime = SDL_GetTicks();
}

/**
 * @brief 根据当前时间更新未缩放与缩放后的时间间隔。
 */
void ScaledDeltaTimer::Update()
{
	std::uint32_t ticks = SDL_GetTicks();
	unscaledDelta = static_cast<double>(ticks - lastFrameTime) / 1000.;
	scaledDelta = unscaledDelta * timeScale;
	lastFrameTime = ticks;
}
