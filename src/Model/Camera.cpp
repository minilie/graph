/**
 * @file Camera.cpp
 * @brief 实现 Camera 类的视图矩阵计算与访问接口。
 */

#include "Camera.h"

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

/**
 * @brief 通过目标点和上方向初始化摄像机，并计算视图矩阵。
 * @param e 观察者位置。
 * @param t 观察目标位置。
 * @param u 世界上方向向量。
 */
Camera::Camera(vec3 e, vec3 t, vec3 u)
{
	LookAt(e, t, u);
}

/**
 * @brief 通过欧拉角（水平/垂直旋转）初始化摄像机。
 * @param e 观察者位置。
 * @param U 绕 X 轴的旋转角。
 * @param V 绕 Y 轴的旋转角。
 */
Camera::Camera(glm::vec3 e, float U, float V) :
	eye(e),
	u(U),
	v(V)
{
	UpdateView();
}

/**
 * @brief 设定摄像机的位置与朝向，并构建视图矩阵。
 * @param e 观察者位置。
 * @param t 观察目标位置。
 * @param u 世界上方向向量。
 */
void Camera::LookAt(vec3 e, vec3 t, vec3 u)
{
	eye = e;
	vec3 vz = normalize(e - t);
	vec3 vx = normalize(cross(u, vz));
	vec3 vy = cross(vz, vx);
	
	view = mat4(
		vec4(vx.x, vy.x, vz.x, 0),
		vec4(vx.y, vy.y, vz.y, 0),
		vec4(vx.z, vy.z, vz.z, 0),
		vec4(-dot(vx, eye), -dot(vy, eye), -dot(vz, eye), 1)
	);
}

/**
 * @brief 获取摄像机位置。
 * @return 观察者位置向量的常量引用。
 */
const vec3& Camera::GetEye() const
{
	return eye;
}

/**
 * @brief 获取摄像机前方向向量。
 * @return 朝前的单位向量（右值）。
 */
vec3&& Camera::GetForward() const
{
	return std::move(vec3(row(view, 2)));
}

/**
 * @brief 获取摄像机横向（平移）方向向量。
 * @return 向右的单位向量（右值）。
 */
vec3&& Camera::GetStrafe() const
{
	return std::move(vec3(row(view, 0)));
}

/**
 * @brief 获取摄像机上方向向量。
 * @return 向上的单位向量（右值）。
 */
vec3&& Camera::GetUp() const
{
	return std::move(vec3(row(view, 1)));
}

/**
 * @brief 获取绕 X 轴的旋转角 U。
 * @return U 角度值。
 */
float Camera::GetU() const
{
	return u;
}

/**
 * @brief 获取绕 Y 轴的旋转角 V。
 * @return V 角度值。
 */
float Camera::GetV() const
{
	return v;
}

/**
 * @brief 获取当前视图矩阵。
 * @return 视图矩阵的常量引用。
 */
const mat4& Camera::GetView() const
{
	return view;
}

/*mat4 Camera::GetViewInv() const
{
	return mat4(
		vec4(vx, 0),
		vec4(vy, 0),
		vec4(vz, 0),
		vec4(eye, 1)
	);
}*/

/**
 * @brief 设置摄像机位置，但不立即更新视图矩阵。
 * @param e 新的观察者位置。
 */
void Camera::SetEye(const vec3& e)
{
	eye = e;
}

/**
 * @brief 设置摄像机的两个欧拉角（U、V），用于控制视角。
 * @param U 绕 X 轴的旋转角。
 * @param V 绕 Y 轴的旋转角。
 */
void Camera::SetUV(float U, float V)
{
	u = U;
	v = V;
}
	
/**
 * @brief 根据当前位置和欧拉角重新计算视图矩阵。
 */
void Camera::UpdateView()
{
	mat4 I(1);
	view = glm::translate(I, eye)  * glm::rotate(I, v, vec3(0, 1, 0)) * glm::rotate(I, u, vec3(1, 0, 0));
	view = inverse(view);
}
