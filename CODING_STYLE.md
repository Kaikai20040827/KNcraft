# 📘 KNcraft C++ 命名规范（Coding Style Guide）

> 目标：
>
> * 一眼分清 **类型 / 成员 / 局部变量 / 全局**
> * IDE 自动补全友好
> * 规模变大后不崩
> * **工程 > 炫技**

---

## 1️⃣ 文件命名（Files）

### ✅ 规则

* **小写 + 下划线**
* `.h` / `.cpp` 同名
* 一对文件 = 一个模块 / 一个类

```text
window.h
window.cpp

camera.h
camera.cpp

renderer.h
renderer.cpp
```

### ❌ 不推荐

```text
Window.cpp
CameraClass.h
myRenderer.cpp
```

---

## 2️⃣ 目录命名（Folders）

* 全小写
* 表示 **系统职责**

```text
src/
├── app/        # 应用生命周期 & Game Loop
├── render/     # OpenGL / Vulkan / 渲染管线
├── scene/      # Scene / World / Level
├── entity/     # Entity / Component
├── physics/    # 碰撞 / 刚体
├── input/      # 键盘 / 鼠标
├── resource/   # 纹理 / 模型 / Shader
├── core/       # 日志 / 时间 / 平台层
```

---

## 3️⃣ 类命名（Class / Struct）

### ✅ 类（class）

* **PascalCase**
* 名词
* 一个类 = 一个清晰职责

```cpp
class Window;
class Camera;
class Renderer;
class InputSystem;
```

### ✅ 结构体（struct）

* 同样 **PascalCase**
* 但：**偏数据，不负责逻辑**

```cpp
struct Vertex;
struct Transform;
struct CollisionInfo;
```

---

## 4️⃣ 成员变量（Member Variables）

### ✅ 统一加 `m_`

> **这是引擎级写法，不是“多余”**

```cpp
class Camera {
public:
    void update();

private:
    glm::vec3 m_position;
    glm::vec3 m_forward;
    float     m_fov;
};
```

### ❗为什么要 `m_`

* 一眼区分 **成员 / 局部**
* 构造函数不混
* IDE 补全直接过滤

```cpp
void Camera::setFov(float fov) {
    m_fov = fov;   // 成员
}
```

---

## 5️⃣ 结构体成员要不要 `m_`？

### ✅ 推荐 **不加**

> struct 本质是 **纯数据**

```cpp
struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
};
```

### ❌ 不推荐

```cpp
struct Vertex {
    glm::vec3 m_position;
};
```

---

## 6️⃣ 函数命名（Functions / Methods）

### ✅ lowerCamelCase

* 动词开头
* 表示行为

```cpp
void init();
void update();
void render();
void handleInput();
```

### Getter / Setter

```cpp
float getFov() const;
void  setFov(float fov);
```

---

## 7️⃣ 局部变量（Local Variables）

* **lowerCamelCase**
* 简短、明确
* 生命周期短

```cpp
float deltaTime;
int vertexCount;
glm::mat4 modelMatrix;
```

---

## 8️⃣ 函数参数（Parameters）

* **lowerCamelCase**
* 不加 `m_`
* 不加前缀

```cpp
void move(float deltaTime);
void setPosition(const glm::vec3& position);
```

---

## 9️⃣ 常量（Constants）

### ✅ 编译期常量

```cpp
constexpr int MAX_LIGHTS = 8;
constexpr float PI = 3.1415926f;
```

### ✅ 枚举

```cpp
enum class RenderMode {
    Solid,
    Wireframe
};
```

---

## 🔟 宏（Macros）

* **全大写 + 下划线**
* 只用于：

  * Debug
  * 平台判断

```cpp
#define DEBUG_BREAK() __debugbreak()
#define ASSERT(x) if (!(x)) DEBUG_BREAK()
```

---

## 1️⃣1️⃣ 命名空间（Namespace）

* 全小写
* 用于模块隔离

```cpp
namespace kn {
    class Window;
}
```

---

## 1️⃣2️⃣ OpenGL / Vulkan 对象命名

```cpp
unsigned int m_vao;
unsigned int m_vbo;
unsigned int m_ibo;
unsigned int m_shaderId;
```

---

## 1️⃣3️⃣ 布尔变量（bool）

* 用 `is / has / can`

```cpp
bool isRunning;
bool hasFocus;
bool canJump;
```

---

## 1️⃣4️⃣ 示例：标准类模板

```cpp
// camera.h
#pragma once

class Camera {
public:
    Camera();

    void update(float deltaTime);

    void setPosition(const glm::vec3& position);
    const glm::vec3& getPosition() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_forward;
    float     m_fov;
};
```

---

## 1️⃣5️⃣ 一句话总结（你要记住的）

> **看到名字，就知道它是谁、在哪、活多久**

* 类：`PascalCase`
* 成员：`m_`
* 局部：`lowerCamelCase`
* struct 成员：**不加 m_**
* 文件：`snake_case`

## RAII:

| 情况                         | RAII？  |
| ---------------------------- | ------- |
| `new / malloc / create()`  | ✅ 必须 |
| 引擎 / 库返回内部指针        | ❌ 不要 |
| 只是“引用 / 观察”          | ❌      |
| 枚举 / struct / 值           | ❌      |
| `CreateXXX`+`DestroyXXX` | ✅      |
