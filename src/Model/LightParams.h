/**
 * @file LightParams.h
 * @brief 声明光源参数及其用于 GPU 传输的封装类。
 */

#ifndef LIGHT_PARAMS_H
#define LIGHT_PARAMS_H

#include "../Helper/UniformBuffer.hpp"
#include "../Helper/Buffer.hpp"

#include <glm/glm.hpp>


namespace GL {

	class Program;
	
}

/**
 * @brief 表示一个简单光源，可作为点光源或方向光使用。
 */
struct Light
{
	Light() = default;

	/**
	 * @brief 通过位置/方向、颜色和强度初始化光源。
	 * @param p 光源位置或方向。
	 * @param c 光源颜色。
	 * @param s 光照强度。
	 */
	Light(const glm::vec3& p, const glm::vec3& c, float s) :
		pos(p),
		color(c),
		strength(s)
	{
	}

	union alignas(16)
	{
		glm::vec3 pos;
		glm::vec3 dir;
	};
	alignas(16) glm::vec3 color;
	float strength;
};

/**
 * @brief 管理多个光源参数并负责将其上传到统一缓冲的工具类。
 */
class LightParams
{
public:
	/**
	 * @brief 获取内部光源数组指针，可直接修改光源数据。
	 * @return 光源数组起始指针。
	 */
	Light* Lights()
	{
		return data.lights;
	}

	void Update();

	/**
	 * @brief 设置当前有效光源数量。
	 * @param count 光源数量。
	 */
	void SetCount(unsigned int count)
	{
		data.lightCount = count;
	}

	/**
	 * @brief 获取当前有效光源数量。
	 * @return 光源数量。
	 */
	unsigned int GetCount()
	{
		return data.lightCount;
	}

	void Bind(const GL::Program& program);
private:
	static constexpr const char* blockName = "LightParams";

	GL::UniformBuffer bindingPoint;
	GL::Buffer buffer;

	struct Data
	{
		Light lights[10];
		unsigned int lightCount = 1;
	};
	Data data;
};

#endif //LIGHT_PARAMS_H
