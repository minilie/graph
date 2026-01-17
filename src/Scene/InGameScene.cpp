/**
 * @file InGameScene.cpp
 * @brief 实现 InGameScene 的加载、更新与渲染逻辑。
 */

#include "InGameScene.h"

#include "../Log/Logger.h"
#include "../Main/Game.h"
#include "../Helper/UniformBuffer.hpp"
#include "../Model/Material/ColorFormat.hpp"
#include "../Model/ModelLoader.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <cmath>

/**
 * @brief 场景开始时初始化 OpenGL 状态、加载着色器和模型数据。
 * @return 初始化成功返回 true，失败时返回 false。
 */
bool InGameScene::Begin()
{
	glClearColor(0.3, 0., 0., 1.);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	//glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable( GL_POINT_SMOOTH );
	//glPointSize( 10 );

	if(!LoadShaders())
	{
		Logger::Error() << "Failed to load Shaders" << '\n';
		return false;
	}

	if(!LoadData())
	{
		Logger::Error() << "Loading data failed" << '\n';
		return false;
	}

	Logger::Info() << "RenderManager.Init() finished succesfully" << '\n'; //std::endl;

	return true;
}

/**
 * @brief 加载模型数据到顶点与索引缓冲中。
 * @return 加载成功返回 true，否则返回 false。
 */
bool InGameScene::LoadData()
{
	desc.AttachVertex(vertexBuffer.GetBuffer());
	desc.AttachIndex(indexBuffer.GetBuffer());

	ModelLoader loader(vertexBuffer, indexBuffer, program.GetMaterialParams());

	if(	!loader.ImportFile("../assets/cube.obj", cube)
		|| !loader.ImportFile("../assets/alfa.obj", car))
	{
		Logger::Error() << "Model loading failed\n";
		return false;
	}

	return true;
}

/**
 * @brief 加载并初始化用于渲染的着色器程序及其统一变量。
 * @return 初始化成功返回 true，否则返回 false。
 */
bool InGameScene::LoadShaders()
{
	Logger::Debug() << "UniformLocation(model): " << (modelID = program.Program().GetUniformLocation("model")) << '\n';

	program.SetProj(glm::perspective(45.0f, 640/360.0f, 0.01f, 500.0f));
	program.SetView(glm::lookAt(glm::vec3( 0.f,  1.f,  6.f), glm::vec3( 0,  0,  0), glm::vec3( 0,  1,  0)));

	program.Lights()[0] = Light(glm::vec3(0., 0., 1.), glm::vec3(.8, .7, .6), 30);

	program.Update();

	return true;
}

/**
 * @brief 更新场景时间等与逻辑相关的数据。
 * @param deltaTime 距离上一帧经过的时间。
 */
void InGameScene::Update(double deltaTime)
{
	time = SDL_GetTicks() / 300.0f;
}

/**
 * @brief 场景结束时调用，当前未做额外清理工作。
 */
void InGameScene::End()
{
}

/**
 * @brief 场景被暂停时调用，当前未做额外处理。
 */
void InGameScene::Pause()
{
}

/**
 * @brief 渲染前的准备阶段，当前未做额外处理。
 */
void InGameScene::PrepareRender()
{
}

/**
 * @brief 执行渲染逻辑，绘制加载的模型。
 */
void InGameScene::Render()
{
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.Use();

	program.Update();

	matModel =
		glm::rotate(time * 0.002f, glm::vec3(0.f, 0.f, 1.f)) *
		glm::rotate(time * 0.3f, glm::vec3(0.f, 1.f, 0.f)) *
		glm::rotate(time * 0.1f, glm::vec3(1.f, 0.f, 0.f));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &(matModel[0][0]));

	//modelManager.Draw("iphone");
	desc.Bind();

	for(unsigned i = 0; i < cube.meshes.size(); ++i)
	{
		program.UseMaterial(cube.materials[i]);
		cube.meshes[i].Draw();
	}

	for(unsigned i = 0; i < car.meshes.size(); ++i)
	{
		program.UseMaterial(car.materials[i]);
		car.meshes[i].Draw();
	}

	program.Unuse();
}

/**
 * @brief 处理退出事件，触发场景退出。
 * @param event SDL 退出事件。
 */
void InGameScene::OnQuit(SDL_QuitEvent& event)
{
	Quit();
}

/**
 * @brief 处理窗口事件，主要在窗口尺寸变化时更新视口和投影矩阵。
 * @param event SDL 窗口事件。
 */
void InGameScene::OnWindow(SDL_WindowEvent& event)
{
	switch(event.event)
	{
		case SDL_WINDOWEVENT_RESIZED:
			glViewport(0, 0, event.data1, event.data2);
			program.SetProj(glm::perspective(45.0f, event.data1 / static_cast<float>(event.data2), 0.01f, 500.0f));
		default:
			break;
	}
}

/**
 * @brief 请求退出游戏，将 Game::running 置为 false。
 */
void InGameScene::Quit()
{
	Logger::Debug() << "Exit" << '\n';
	game->running = false;
}

/**
 * @brief 处理键盘事件，支持退出与简单日志输出。
 * @param event SDL 键盘事件。
 */
void InGameScene::OnKeyboard(SDL_KeyboardEvent& event)
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE:
			Quit();
			break;
		default:
			Logger::Debug() << "Pressed key with code: " << event.keysym.sym << '\n';
			break;
	}
}
