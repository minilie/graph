/**
 * @file Logger.h
 * @brief 提供简单的日志系统，支持多种日志等级和流式输出接口。
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Logging
{

/**
 * @brief 日志等级枚举，控制日志输出的详细程度。
 */
enum class Level: short
{
	Debug = 0,
	Info = 1,
	Warning = 2,
	Error = 3,
	None = 10
};

template<Level L>
struct LevelString
{
};

template<>
struct LevelString<Level::Debug>
{
	static constexpr char value[] = "[Debug]";
};

template<>
struct LevelString<Level::Info>
{
	static constexpr char value[] = "[Info]";
};

template<>
struct LevelString<Level::Warning>
{
	static constexpr char value[] = "[Warning]";
};

template<>
struct LevelString<Level::Error>
{
	static constexpr char value[] = "[Error]";
};

/**
 * @brief 日志全局设置，用于控制当前生效的日志等级。
 */
class Settings
{
private:
	static Level level;
public:
	/**
	 * @brief 设置全局日志等级，低于该等级的日志将被忽略。
	 * @param _level 要设置的日志等级。
	 */
	static void SetLevel(Level _level);

	/**
	 * @brief 获取当前全局日志等级。
	 * @return 当前日志等级。
	 */
	static Level GetLevel();
};

/**
 * @brief 日志实例模板，封装了特定等级的日志输出流。
 * @tparam L 日志等级。
 */
template<Level L>
class Instance
{
public:
	/**
	 * @brief 构造日志实例，在输出前写入等级前缀。
	 */
	Instance()
	{
		if(L >= Settings::GetLevel())
		{
			std::cerr << LevelString<L>::value << ' ';
		}
	}

	/**
	 * @brief 利用流式运算符输出任意类型的内容。
	 * @tparam T 输出数据类型。
	 * @param t 要输出的数据。
	 * @return 当前日志实例的引用，便于链式调用。
	 */
	template<typename T>
	Instance& operator<<(T&& t)
	{
		if(L >= Settings::GetLevel())
		{
			std::cerr << t;
		}
		return *this;
	}

	/**
	 * @brief 利用流式运算符输出常量右值的内容。
	 * @tparam T 输出数据类型。
	 * @param t 要输出的数据。
	 * @return 当前日志实例的引用。
	 */
	template<typename T>
	Instance& operator<<(const T&& t)
	{
		if(L >= Settings::GetLevel())
		{
			std::cerr << t;
		}
		return *this;
	}
};

/**
 * @brief 日志别名集合，方便按等级创建日志实例。
 */
struct Logger
{
	using Debug = Logging::Instance<Logging::Level::Debug>;
	using Info = Logging::Instance<Logging::Level::Info>;
	using Warning = Logging::Instance<Logging::Level::Warning>;
	using Error = Logging::Instance<Logging::Level::Error>;
};

}// namespace Logger

using Logger = Logging::Logger;

#endif
