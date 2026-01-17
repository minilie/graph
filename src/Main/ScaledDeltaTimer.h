/**
 * @file ScaledDeltaTimer.h
 * @brief 声明带时间缩放功能的帧间计时器。
 */

#ifndef SCALED_DELTA_TIMER_H
#define SCALED_DELTA_TIMER_H

#include <cstdint>

/**
 * @brief 负责计算每帧时间间隔，并支持按比例缩放时间的计时器。
 */
class ScaledDeltaTimer
{
public:
	ScaledDeltaTimer() = default;
	ScaledDeltaTimer(const ScaledDeltaTimer&) = default;
	ScaledDeltaTimer& operator=(const ScaledDeltaTimer& t) = default;

	/**
	 * @brief 启动计时器，记录第一帧的起始时间。
	 */
	void Start();

	/**
	 * @brief 更新当前帧与上一帧之间的时间，并计算缩放后的时间。
	 */
	void Update();

	/**
	 * @brief 设置时间缩放因子。
	 * @param newScale 新的时间缩放比例，大于 1 表示加速，小于 1 表示减速。
	 */
	void SetScaleFactor(const double newScale)
	{
		timeScale = newScale;
	}

	/**
	 * @brief 获取当前时间缩放因子。
	 * @return 当前时间缩放比例。
	 */
	double GetScaleFactor() const
	{
		return timeScale;
	}

	/**
	 * @brief 获取缩放后的上一帧到当前帧的时间间隔（秒）。
	 * @return 缩放后的时间间隔。
	 */
	double GetScaledTime() const
	{
		return scaledDelta;
	}

	/**
	 * @brief 获取未缩放的上一帧到当前帧的时间间隔（秒）。
	 * @return 未缩放的时间间隔。
	 */
	double GetUnscaledTime() const
	{
		return unscaledDelta;
	}

	/**
	 * @brief 获取上一帧开始的时间戳（毫秒）。
	 * @return 上一帧开始的时间戳。
	 */
	std::uint32_t GetFrameStart() const
	{
		return lastFrameTime;
	}

protected:
private:
	double timeScale;
	double unscaledDelta;
	double scaledDelta;
	std::uint32_t lastFrameTime;
};

#endif //SCALED_DELTA_TIMER_H
