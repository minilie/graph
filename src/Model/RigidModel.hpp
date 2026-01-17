/**
 * @file RigidModel.hpp
 * @brief 声明由若干网格与材质组成的刚体模型结构。
 */

#ifndef RIGID_MODEL_HPP
#define RIGID_MODEL_HPP

#include "Mesh/Mesh3D.hpp"
#include <vector>

using MaterialId = unsigned int;

/**
 * @brief 表示一个刚体模型，由多个 Mesh3D 与对应材质组成。
 */
class RigidModel
{
public:
	std::vector<Mesh3D> meshes;
	std::vector<MaterialId> materials;

	RigidModel() = default;
	RigidModel(const RigidModel&) = delete;
	RigidModel(RigidModel&&) = default;

	RigidModel& operator=(const RigidModel&) = delete;
	RigidModel& operator=(RigidModel&&) = default;
/*
	void AddPart(MeshId mesh, MaterialId material);*/
};
#endif
