/**
 * @file ModelLoader.hpp
 * @brief 声明使用 Assimp 将模型加载到缓冲与材质系统中的工具类。
 */

#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include "../DataStore/ManagedBuffer.hpp"
#include "Mesh/BasicVertexFormat.h"
#include "RigidModel.hpp"

#include "../Helper/TypeEnum.hpp"

#include <vector>
#include <string>
#include <type_traits>
#include <cstdlib>
#include <ctime>

class aiMesh;
class Mesh3D;
class MaterialParams;

/**
 * @brief 负责从文件加载 3D 模型，将顶点/索引写入缓冲并生成刚体模型数据。
 */
class ModelLoader
{
private:
	ManagedBuffer& vertexBuffer;
	ManagedBuffer& indexBuffer;
	MaterialParams& materialParams;

	/**
	 * @brief 处理单个网格的索引数据，并将其添加到 RigidModel 中。
	 * @tparam T 索引类型（如 GLubyte/GLushort/GLuint）。
	 * @param mesh Assimp 网格对象。
	 * @param model 目标刚体模型。
	 * @param vertex 顶点缓冲偏移与大小信息。
	 */
	template <typename T>
	void HandleIndices(const aiMesh& mesh, RigidModel& model, const std::pair<GLuint, GLuint>& vertex);

	std::pair<GLuint, GLuint> InsertVertices(const std::vector<BasicVertexFormat>& vertices);
	GLuint InsertIndices (GLuint size, const void* data, GLuint alignment);

	/**
	 * @brief 从 Assimp 网格中提取索引数据。
	 * @tparam T 索引类型。
	 * @param mesh Assimp 网格对象。
	 * @return 索引数组。
	 */
	template <typename T>
	std::vector<T> GetIndices(const aiMesh& mesh);

	template <typename T>
	void PushIndex(Mesh3D& mesh, RigidModel& model);

	std::vector<BasicVertexFormat> GetVertices(const aiMesh& mesh);
public:
	/**
	 * @brief 构造函数，指定顶点/索引缓冲及材质参数对象。
	 * @param _vertexBuffer 顶点缓冲。
	 * @param _indexBuffer 索引缓冲。
	 * @param _materialParams 材质参数管理器。
	 */
	ModelLoader(ManagedBuffer& _vertexBuffer, ManagedBuffer& _indexBuffer, MaterialParams& _materialParams) :
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer),
		materialParams(_materialParams)
	{
		srand(time(0));
	}

	/**
	 * @brief 从指定文件导入模型，并填充到刚体模型对象中。
	 * @param filename 模型文件名。
	 * @param model 输出的刚体模型对象。
	 * @return 导入成功返回 true，失败返回 false。
	 */
	bool ImportFile(const std::string& filename, RigidModel& model);
};

#endif
