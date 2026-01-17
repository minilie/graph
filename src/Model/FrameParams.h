/**
 * @file FrameParams.h
 * @brief 声明每帧渲染相关的视图与投影参数封装类。
 */

#ifndef FRAME_PARAMS_H
#define FRAME_PARAMS_H

#include "../Helper/UniformBuffer.hpp"
#include "../Helper/Buffer.hpp"

#include <glm/glm.hpp>

namespace GL
{
	class Program;
}

/**
 * @brief 封装每帧需要上传到 GPU 的视图矩阵和投影矩阵。
 */
class FrameParams
{
public:
	/**
	 * @brief 设置视图矩阵。
	 * @param v 新的视图矩阵。
	 */
	void SetView(const glm::mat4 v)
	{
		data.view = v;
	}

	/**
	 * @brief 设置投影矩阵。
	 * @param p 新的投影矩阵。
	 */
	void SetProj(const glm::mat4 p)
	{
		data.proj = p;
	}

	/**
	 * @brief 获取当前视图矩阵。
	 * @return 视图矩阵常量引用。
	 */
	const glm::mat4& GetView() const
	{
		return data.view;
	}

	/**
	 * @brief 获取当前投影矩阵。
	 * @return 投影矩阵常量引用。
	 */
	const glm::mat4& GetProj() const
	{
		return data.proj;
	}

	void Bind(const GL::Program& program);

	void Update();
private:
	struct Data
	{
		glm::mat4 view;
		glm::mat4 proj;
	};

	static constexpr const char* blockName = "FrameParams";

	GL::UniformBuffer bindingPoint;
	GL::Buffer buffer;

	Data data;
};

#endif //FRAME_PARAMS_H
