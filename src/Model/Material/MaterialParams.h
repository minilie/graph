/**
 * @file MaterialParams.h
 * @brief 声明材质参数管理类，用于统一缓冲中的材质存储与绑定。
 */

#ifndef MATERIAL_PARAMS_H
#define MATERIAL_PARAMS_H

#include "../../Helper/UniformBuffer.hpp"
#include "../../DataStore/ManagedBuffer.hpp"

#include "ColorFormat.hpp"
#include "Material.hpp"

namespace GL {
	class Program;
}

/**
 * @brief 管理所有材质的颜色数据，并将其存储到统一缓冲中。
 */
class MaterialParams
{
public:
	/**
	 * @brief 构造函数，预分配一定大小的材质缓冲。
	 */
	MaterialParams() :
		buffer(30000, GL_STATIC_DRAW)
	{
	}

	void Bind(const GL::Program& program);

	size_t Push(const ColorFormat& material);

	void UseMaterial(size_t id);
private:
	static constexpr const char* blockName = "MaterialParams";

	std::vector<Material> materials;

	GL::UniformBuffer bindingIndex;
	ManagedBuffer buffer;
};

#endif //MATERIAL_PARAMS_H
