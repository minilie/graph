# 渲染模式切换功能更新记录（SPHWaterPhysics）

本文记录为项目新增“渲染模式切换（Render Mode Switch）”功能的改动内容、按键说明、涉及文件与实现细节，便于后续维护与继续扩展。

## 目标

- 在同一套 SPH 模拟逻辑不变的前提下，支持三种渲染模式快速切换：
  1. **Surface**：距离场（3D texture）+ raycast 的水体表面渲染（原默认方式）。
  2. **Points**：直接渲染所有粒子点（调试密度/分布更直观）。
  3. **EdgePoints**：渲染边界粒子点（由 SPH 压强/密度 shader 中提取的 edge particles）。
- 让 2/3 模式与 1 模式 **完全一致的轨道相机（OrbiterCamera）视角** 与 **重力方向**。

## 新增/调整的按键

在 `SPHWaterScene` 中（`src/Scene/SPHWaterScene.cpp`）：

- `1`：切换到 **Surface**
- `2`：切换到 **Points**
- `3`：切换到 **EdgePoints**
- `m`：三种模式循环切换（Surface → Points → EdgePoints → Surface）

保留原有按键：

- `W/A/S/D`：旋转轨道相机（现在对 1/2/3 三种模式均生效）
- `k`：暂停/继续模拟（松开触发）
- `ESC`：退出

## 实现概览

### 1）场景层：增加 RenderMode 并切换渲染路径

文件：

- `src/Scene/SPHWaterScene.hpp`
- `src/Scene/SPHWaterScene.cpp`

关键点：

- 在 `SPHWaterScene` 内新增 `RenderMode` 枚举：`Surface / Points / EdgePoints`。
- 在 `OnKeyboard()` 里处理 `1/2/3/m`，切换当前 `renderMode`。
- 在 `Render()` 中根据 `renderMode` 走不同渲染器：
  - `Surface`：`RenderSurface::Render()`
  - `Points`：`RenderPoints::Render(...)`
  - `EdgePoints`：`RenderEdgePoints::Render(...)`

### 2）避免不必要的距离场计算：distanceFieldDirty

文件：

- `src/Scene/SPHWaterScene.hpp`
- `src/Scene/SPHWaterScene.cpp`

关键点：

- 新增 `distanceFieldDirty` 标志位。
- 模拟推进（`grid.Run()` + `simulation.Run()` + `basic.comp` 积分）后标记 `distanceFieldDirty = true`。
- **只有在 Surface 模式实际渲染前**，才会调用 `renderSurface.UpdateParticles()` 来重建距离场，并将 `distanceFieldDirty = false`。

这样在 Points/EdgePoints 模式下不会额外消耗时间去生成 distance field。

### 3）相机/重力一致：复用 RenderSurface 的 OrbiterCamera

文件：

- `src/Program/Render/RenderSurface.hpp`
- `src/Scene/SPHWaterScene.cpp`

关键点：

- 在 `RenderSurface` 中新增访问器：
  - `GetWorld()`：返回与 Surface 渲染一致的 `world` 矩阵（实际上是 OrbiterCamera 的 view/world 变换）
  - `GetEye()`：返回相机 eye（与 `raycast.frag` 使用同一 eye）
- `SPHWaterScene` 的 `W/A/S/D` 始终只驱动 `renderSurface.SetHorizontalDirection/SetVerticalDirection`。
- 2/3 模式在渲染时直接读取 `renderSurface.GetWorld()/GetEye()`，保证：
  - 视角与 Surface 模式一致
  - `SPHWaterScene::Update()` 中的重力方向（`renderSurface.GetGravity()`）天然与三种模式一致

### 4）Points/EdgePoints 的投影方式重做：从“矩阵投影”改为“与 raycast 相同的屏幕平面投影”

为了做到 **2/3 与 1 的视角完全一致**，点渲染不再使用独立的 `perspective * lookAt * rotate`。

做法：

- Surface 渲染的屏幕 quad 顶点在 `shaders/Render/quad.vert` 中通过 `world` 变换生成 `rayStart`。
- 我们在 C++ 侧用同一个 `world`，计算出屏幕平面参数（3 个角点推导）：
  - `PlaneOrigin`：bottom-left
  - `PlaneAxisX`：bottom-right - bottom-left
  - `PlaneAxisY`：top-left - bottom-left
- 点渲染 shader 使用 `Eye + PlaneOrigin + PlaneAxisX + PlaneAxisY`：
  - 对每个粒子点，从 `Eye` 指向粒子位置形成射线
  - 与屏幕平面求交，得到平面坐标 `(u,v)`，再映射到 NDC

涉及文件：

- `src/Program/Render/RenderPoints.hpp` / `src/Program/Render/RenderPoints.cpp`
- `src/Program/Render/RenderEdgePoints.hpp` / `src/Program/Render/RenderEdgePoints.cpp`
- `shaders/Render/passthrough.vert`
- `shaders/Render/edgeOnly.vert`

同时，为了与 Surface 的体渲染空间对齐，点的位置也使用同一套归一化映射（与 `distanceField.comp` 一致）：

- `cubePos = pos * (1/2.2) + (1/2.2 + 0.05)`

### 5）Uniform 约定（重要）

由于点渲染改为“屏幕平面投影”，两个点渲染顶点着色器的 uniform 布局发生变化：

- `shaders/Render/passthrough.vert`
- `shaders/Render/edgeOnly.vert`

统一为：

- `layout(location = 0) uniform vec3 Eye;`
- `layout(location = 1) uniform vec3 PlaneOrigin;`
- `layout(location = 2) uniform vec3 PlaneAxisX;`
- `layout(location = 3) uniform vec3 PlaneAxisY;`

对应 C++ 在：

- `src/Program/Render/RenderPoints.cpp`
- `src/Program/Render/RenderEdgePoints.cpp`

中使用 `glUniform3fv(...)` 进行设置。

### 6）修复 EdgePoints 空白问题：补齐 gl_PointSize

问题现象：

- `EdgePoints`（模式 3）在部分驱动/环境下出现“全空白”。

原因：

- `shaders/Render/edgeOnly.vert` 在主路径未写 `gl_PointSize`，某些实现下点大小可能为 0 导致不可见。

修复：

- 在 `shaders/Render/edgeOnly.vert` 正常路径末尾补上 `gl_PointSize = 1;`。

## 代码改动清单（文件级）

- `src/Scene/SPHWaterScene.hpp`
  - 新增 `RenderMode`、新增三种渲染器成员、`distanceFieldDirty`。
- `src/Scene/SPHWaterScene.cpp`
  - 增加 `1/2/3/m` 切换逻辑
  - `Render()` 按模式分发渲染
  - 2/3 模式从 `RenderSurface` 获取 `Eye/world` 并计算屏幕平面参数传入点渲染
  - `distanceFieldDirty` 的更新与使用
- `src/Program/Render/RenderSurface.hpp`
  - 新增 `GetWorld()` / `GetEye()` 用于共享相机数据
- `src/Program/Render/RenderPoints.hpp` / `src/Program/Render/RenderPoints.cpp`
  - `Render(...)` 接口变更：由矩阵改为 `Eye + PlaneOrigin + PlaneAxisX + PlaneAxisY`
  - 设置新的 uniform location 0..3
- `src/Program/Render/RenderEdgePoints.hpp` / `src/Program/Render/RenderEdgePoints.cpp`
  - 同上
- `shaders/Render/passthrough.vert`
  - uniform 改为 `Eye/PlaneOrigin/PlaneAxisX/PlaneAxisY`
  - 增加射线-平面求交投影逻辑
- `shaders/Render/edgeOnly.vert`
  - uniform 改为 `Eye/PlaneOrigin/PlaneAxisX/PlaneAxisY`
  - 增加射线-平面求交投影逻辑
  - 修复：补齐 `gl_PointSize = 1`

（附带）构建层小修复：

- `makefile`
  - 为避免在非 Windows 环境下 `.d` 依赖文件含盘符路径 `D:/...` 导致 GNU make 解析失败，增加了对 depfile 的转义处理（仅在非 Windows 分支生效）。

## 运行/验证建议（手动测试）

1. 启动程序后按 `1/2/3` 检查三种模式是否都能切换。
2. 在任意模式下按住 `W/A/S/D`，确认视角一致旋转（2/3 应与 1 完全一致）。
3. 在 `3` 模式确认能看到边界点（若边界点数为 0，可能是阈值或模拟参数导致，可先运行一段时间再观察）。

