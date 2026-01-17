/**
 * @file Logger.cpp
 * @brief 实现日志系统的全局设置接口。
 */

#include "Logger.h"

namespace Logging
{
	/**
	 * @brief 设置当前全局日志等级。
	 * @param _level 要生效的日志等级。
	 */
	void Settings::SetLevel(Level _level)
	{
		level = _level;
	}

	/**
	 * @brief 获取当前全局日志等级。
	 * @return 当前生效的日志等级。
	 */
	Level Settings::GetLevel()
	{
		return level;
	}

	/**
	 * @brief 日志系统的默认日志等级，初始为 Debug。
	 */
	Level Settings::level = Level::Debug;
}
