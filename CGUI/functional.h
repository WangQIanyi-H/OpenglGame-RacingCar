#pragma once

#include<glad\glad.h>
#include<iostream>

struct point_f {
    float x;
    float y;
    point_f() {
        x = 0.0f;
        y = 0.0f;
    }
    point_f(float a, float b) {
        x = a;
        y = b;
    }
};

//计算 | p1 p2 | X | p1 p3 |
float GetCross(point_f p1, point_f p3, point_f p2) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
//判断点p是否在p1p2p3p4的正方形内
//判断p点是否在矩形区域内部
bool IS_IN_AREA(point_f click, point_f rect[4]) {
    if (GetCross(rect[0], rect[1], click) * GetCross(rect[2], rect[3], click) >= 0
        && GetCross(rect[1], rect[2], click) * GetCross(rect[3], rect[0], click) >= 0)
        return true;
    else {
        return false;
    }
}

//起步
struct Start {
    //开左转向灯，挂D挡，松手刹。
    bool Session1 = false;
    bool Session2 = false;
    bool Session3 = false;
    int Score() {
        return (int)Session3 * 10;
    }
};
Start start;

//路口直行
struct CrossingStraight {
    //先刹车,再直行
    bool Session1 = false;
    bool Session2 = false;
    point_f Area1[4] = {
        point_f(-0.6f, 7.0f),
        point_f(-0.6f, 2.0f),
        point_f(1.2f, 2.0f),
        point_f(1.2f, 7.0f),
    }; 
    point_f Area2[4] = {
        point_f(-0.6f, 17.0f),
        point_f(-0.6f, 7.0f),
        point_f(1.2f, 7.0f),
        point_f(1.2f, 17.0f),
    };
    int Score() {
        return (int)Session1 * 5 + (int)Session2 * 5;
    }
};
CrossingStraight crossingStraight;

//直线行驶
struct GoStraight {
    bool Session;
    point_f Area[4] = {
        point_f(-0.6f, 27.0f),
        point_f(-0.6f, 17.0f),
        point_f(1.2f, 17.0f),
        point_f(1.2f, 27.0f),
    };
    int Score() {
        return (int)Session*10;
    }
};
GoStraight goStraight;

//会车
struct GiveWay{
    //刹车
    bool Session1 = false;
    point_f Area1[4] = {
        point_f(-0.6f, 48.0f),
        point_f(-0.6f, 30.0f),
        point_f(1.2f, 30.0f),
        point_f(1.2f, 48.0f),
    };
    int Score(){
        return (int)Session1 * 5;
    }
};
GiveWay giveWay;

//左转弯
struct TurnLeft{
    //提前开启左转向灯，路过斑马线前点一下刹车，需要转向靠路中心的那个车道。

    //开启左转向灯：
    bool Session1 = false;
    //斑马线前踩刹车：
    bool Session2 = false;
    //确定转向靠路中心的车道：
    bool Session3 = false;

    //开启左转向灯：
    point_f Area1[4] = {
        point_f(-0.6f, 54.0f),
        point_f(-0.6f, 48.0f),
        point_f(1.2f, 48.0f),
        point_f(1.2f, 54.0f),
    };
    //斑马线前踩刹车：
    point_f Area2[4] = {
        point_f(-0.6f, 59.0f),
        point_f(-0.6f, 54.0f),
        point_f(1.2f, 54.0f),
        point_f(1.2f, 59.0f),
    };
    //确保区域是在靠近栅栏的车道：
    point_f Area3[4] = {
        point_f(4.9f, 65.5f),
        point_f(4.9f, 64.7f),
        point_f(6.6f, 64.7f),
        point_f(6.6f, 65.5f),
    };
    int Score() {
        return (int)Session1 * 5 + (int)Session2 * 5 + (int)Session3 * 5;
    }
};
TurnLeft turnleft;

//路过学校：
struct PassingSchool {
    //刹车
    bool Session1 = false;
    point_f Area1[4] = {
        point_f(6.0f, 66.9f),
        point_f(6.0f, 65.1f),
        point_f(15.0f, 65.1f),
        point_f(15.0f, 66.9f),
    };
    int Score() {
        return (int)Session1 * 5;
    }
};
PassingSchool passingSchool;

//变更车道
struct MoveLane {
    int changeNumber = 0;
    int lane1=0;
    int lane2=0;
    int lane3=0;
    point_f Area1[4] = {
        point_f(1.5f, 56.0f),
        point_f(1.5f, 46.0f),
        point_f(2.1f, 46.0f),
        point_f(2.1f, 56.0f),
    };
    point_f Area2[4] = {
        point_f(2.1f, 56.0f),
        point_f(2.1f, 46.0f),
        point_f(2.7f, 46.0f),
        point_f(2.7f, 56.0f),
    };
    point_f Area3[4] = {
        point_f(2.7f, 56.0f),
        point_f(2.7f, 46.0f),
        point_f(3.3f, 46.0f),
        point_f(3.3f, 56.0f),
    };
    point_f Area4[4] = {
        point_f(3.3f, 56.0f),
        point_f(3.3f, 46.0f),
        point_f(3.9f, 46.0f),
        point_f(3.9f, 56.0f),
    };
    int detect(point_f p) {
        if (IS_IN_AREA(p, Area1))return 1;
        if (IS_IN_AREA(p, Area2))return 2;
        if (IS_IN_AREA(p, Area3))return 3;
        if (IS_IN_AREA(p, Area4))return 4;
    }
    int Score() {
        return 10;
    }
};
MoveLane moveLane;



//向右转：
struct TurnRight {
    //提前开启左转向灯，路过斑马线前点一下刹车，需要转向靠路中心的那个车道。

    //开启右转向灯：
    bool Session1 = false;
    //斑马线前踩刹车：
    bool Session2 = false;
    //确定转向靠路中心的车道：
    bool Session3 = false;

    //开启右转向灯：
    point_f Area1[4] = {
        point_f(14.7f, 64.5f),
        point_f(14.7f, 62.7f),
        point_f(7.0f, 62.7f),
        point_f(7.0f, 64.5f),
    };

    //斑马线前踩刹车：
    point_f Area2[4] = {
        point_f(8.6f, 64.5f),
        point_f(8.6f, 62.7f),
        point_f(6.4f, 62.7f),
        point_f(6.4f, 64.5f),
    };
    //确保区域是在靠近栅栏的车道：
    point_f Area3[4] = {
        point_f(3.2f, 61.5f),
        point_f(3.2f, 56.0f),
        point_f(4.0f, 56.0f),
        point_f(4.0f, 61.5f),
    };
    int Score() {
        return (int)Session1 * 5 + (int)Session2 * 5 + (int)Session3 * 5;
    }
};
TurnRight turnright;

//路过公交车站：
struct PassingBusStop {
    //刹车
    bool Session1 = false;
    point_f Area[4] = {
        point_f(1.8f,55.82f),
        point_f(1.8f,37.0f),
        point_f(3.6f,35.0f),
        point_f(3.6f,25.85f),
    };
    int Score() {
        return (int)Session1 * 5;
    }
};
PassingBusStop passingBusStop;


//===============记录每个具体操作=================
int automatic = 1;                  //--------自动挡挡位
 
//===============记录每个环节的完成与否==============

//bool CrossingStraight = false;    //路口直行
//bool GoStraight = false;          //直线行驶
//bool GiveWay = false;             //会车
//bool TurnLeft = false;            //左转弯
//bool PassingSchool = false;       //路过学校
//bool UTurn = false;               //掉头
//bool Overtake = false;            //超车
//bool MoveLane = false;            //变更车道
//bool PassingBusStop = false;      //路过公交车站
//bool PullOver = false;            //靠边停车



//全局变量——鼠标按下时的位置
point_f mouse_pos;
point_f car_pos;
//优化——用许多个points[4]来表示10个矩形区域
point_f Area1_1[4] = {
    point_f(-0.6f, 6.2f),
    point_f(-0.6f, 1.2f),
    point_f(1.2f, 1.2f),
    point_f(1.2f, 6.2f),
};
point_f Area1_2[4] = {
    point_f(-0.6f, 24.0f),
    point_f(-0.6f, 20.0f),
    point_f(1.2f, 20.0f),
    point_f(1.2f, 24.0f),
};
point_f Area1_3[4] = {
    point_f(-0.6f, 34.0f),
    point_f(-0.6f, 30.0f),
    point_f(1.2f, 30.0f),
    point_f(1.2f, 34.0f),
};
point_f Area1_4[4] = {
    point_f(-0.6f, 56.0f),
    point_f(-0.6f, 48.0f),
    point_f(1.2f, 48.0f),
    point_f(1.2f, 56.0f),
};
point_f Area2_1[4] = {
    point_f(6.4f, 66.9f),
    point_f(6.4f, 65.1f),
    point_f(9.0f, 65.1f),
    point_f(9.0f, 66.9f),
};
point_f Area2_2[4] = {
    point_f(19.0f, 66.9f),
    point_f(19.0f, 65.1f),
    point_f(25.0f, 65.1f),
    point_f(25.0f, 66.9f),
};
point_f Area2_3[4] = {
    point_f(19.0f, 64.5f),
    point_f(19.0f, 62.7f),
    point_f(26.0f, 62.7f),
    point_f(26.0f, 64.5f),
};
point_f Area2_4[4] = {
    point_f(15.0f, 64.5f),
    point_f(15.0f, 62.7f),
    point_f(10.0f, 62.7f),
    point_f(10.0f, 64.5f),
};
point_f Area3_1[4] = {
    point_f(1.8f, 56.0f),
    point_f(1.8f, 46.0f),
    point_f(3.6f, 46.0f),
    point_f(3.6f, 56.0f),
};
point_f Area3_2[4] = {
    point_f(1.8f, 35.0f),
    point_f(1.8f, 30.0f),
    point_f(3.6f, 30.0f),
    point_f(3.6f, 35.0f),
};
point_f Area3_3[4] = {
    point_f(1.8f, 6.0f),
    point_f(1.8f, 0.0f),
    point_f(3.6f, 0.0f),
    point_f(3.6f, 6.0f),
};




//全局变量
//窗口分辨率
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
// 渲染阴影时的窗口分辨率（会影响阴影的锯齿边情况）
const unsigned int SHADOW_WIDTH = 1024 * 10;
const unsigned int SHADOW_HEIGHT = 1024 * 10;
// 是否为线框图模式
bool isPolygonMode = false;
// 世界坐标系Y轴单位向量
glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);
// timing 用来平衡不同电脑渲染水平所产生的速度变化
float deltaTime = 0.0f;
float lastFrame = 0.0f;
//摄像机
//Camera camera(glm::vec3(4.0f, 10.0f, 1.5f));
Camera camera(glm::vec3(0.0f, 15.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//car
glm::vec3 carPos = glm::vec3(0.0f, 0.0f, 0.0f);
Car car(carPos);

//灯光
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
// 天空盒
unsigned int cubemapTexture;
unsigned int skyboxVAO, skyboxVBO;
// 天空盒顶点数据
const float skyboxVertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};
// 天空盒的面数据
//const vector<std::string> faces{
//    "asset/textures/skybox/right.tga",
//    "asset/textures/skybox/left.tga",
//    "asset/textures/skybox/top.tga",
//    "asset/textures/skybox/bottom.tga",
//    "asset/textures/skybox/front.tga",
//    "asset/textures/skybox/back.tga"
//};
//const vector<std::string> faces{
//    "asset/textures/5/rainbow_rt.png",
//    "asset/textures/5/rainbow_lf.png",
//    "asset/textures/5/rainbow_up.png",
//    "asset/textures/5/rainbow_dn.png",
//    "asset/textures/5/rainbow_ft.png",
//    "asset/textures/5/rainbow_bk.png"
//};
const vector<std::string> faces
{
    "asset/textures/13/right.tga",
    "asset/textures/13/left.tga",
    "asset/textures/13/top.tga",
    "asset/textures/13/bottom.tga",
    "asset/textures/13/front.tga",
    "asset/textures/13/back.tga"
};


// 将六份纹理加载为一个cubemap纹理
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void skyboxInit()
{
    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 纹理加载
    cubemapTexture = loadCubemap(faces);
}

void renderSkyBox(Shader& shader)
{
    // viewMatrix 通过构造，移除相机的移动
    glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    // 投影
    glm::mat4 projMatrix = camera.GetProjMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);

    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", projMatrix);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


void handleKeyInput(GLFWwindow* window)
{
    // esc退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //控制摄像机
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)// && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)// && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        car.ProcessKeyboard(CAR_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        car.ProcessKeyboard(CAR_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        car.ProcessKeyboard(CAR_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        car.ProcessKeyboard(CAR_RIGHT, deltaTime);
}


//转换鼠标点击时的二维坐标系
void turn_to_view(double& a, double& b) {
    point_f point;

    point.x = a - SCR_WIDTH / 2;
    point.y = SCR_HEIGHT / 2 - b;
    a = point.x / (SCR_WIDTH / 2);
    b = point.y / (SCR_HEIGHT / 2);
}


//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//    {
//        double xpos, ypos;
//        //getting cursor position 
//        glfwGetCursorPos(window, &xpos, &ypos);
//        turn_to_view(xpos, ypos);
//
//        //给鼠标点击位置赋值
//        mouse_pos.x = xpos;
//        mouse_pos.y = ypos;
//        std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << std::endl;
//        std::cout << "ICON_1:" << IS_IN_AREA(mouse_pos, ICON_RECT_1) << std::endl;
//        std::cout << "ICON_2:" << IS_IN_AREA(mouse_pos, ICON_RECT_2) << std::endl;
//    }
//}




void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}






// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void setDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

//窗口初始化
GLFWwindow* windowInit() {
    //setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return NULL;

    // GL 3.0 + GLSL 330 core 配置
    const char* glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return NULL;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //初始化 OpenGL loader
    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 配置ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}

unsigned int* mainBackgroundLoader()
{
      //背景视图不使用坐标变换
    float vertices[] = {
        //     ---- 位置 ----   -------color------   - 纹理坐标 -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/main/background_menu.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1};
    return param;
}
unsigned int* ruleBackgroundLoader()
{
    //背景视图不使用坐标变换
    float vertices[] = {
        //     ---- 位置 ----   -------color------   - 纹理坐标 -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data =  stbi_load("asset/image/rule/rule.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}
unsigned int* main_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/main/begin.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/main/rule.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/main/set.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/main/quit.png", &width, &height, &nrChannels, 0);
        break;
    }    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* rule_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/rule/back.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/rule/rule.png", &width, &height, &nrChannels, 0);
        break;
    }
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* game_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/game/安全带.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/game/地图.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/game/视角.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/game/暂停.png", &width, &height, &nrChannels, 0);
        break;
    case 5:
        data = stbi_load("asset/image/game/油门.png", &width, &height, &nrChannels, 0);
        break;
    case 6:
        data = stbi_load("asset/image/game/刹车.png", &width, &height, &nrChannels, 0);
        break;
    case 7:
        data = stbi_load("asset/image/game/手刹.png", &width, &height, &nrChannels, 0);
        break;
    case 8:
        data = stbi_load("asset/image/game/危险警示灯.png", &width, &height, &nrChannels, 0);
        break;
    case 9:
        data = stbi_load("asset/image/game/方向盘.png", &width, &height, &nrChannels, 0);
        break;
    case 10:
        data = stbi_load("asset/image/game/速度显示框.png", &width, &height, &nrChannels, 0);
        break;
    case 11:
        data = stbi_load("asset/image/game/自动挡p.png", &width, &height, &nrChannels, 0);
        break;
    case 12:
        data = stbi_load("asset/image/game/自动挡r.png", &width, &height, &nrChannels, 0);
        break;  
    case 13:
        data = stbi_load("asset/image/game/自动挡n.png", &width, &height, &nrChannels, 0);
        break;
    case 14:
        data = stbi_load("asset/image/game/自动挡d.png", &width, &height, &nrChannels, 0);
        break;
    case 15:
        data = stbi_load("asset/image/game/左转弯灯.png", &width, &height, &nrChannels, 0);
        break;
    case 16:
        data = stbi_load("asset/image/game/右转弯灯.png", &width, &height, &nrChannels, 0);
        break;
    case 17:
        data = stbi_load("asset/image/game/安全带1.png", &width, &height, &nrChannels, 0);
        break;
    case 18:
        data = stbi_load("asset/image/game/手刹1.png", &width, &height, &nrChannels, 0);
        break;
   
    }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* tips_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/tip/变更车道.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/tip/超车.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/tip/掉头.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/tip/公交车站.png", &width, &height, &nrChannels, 0);
        break;
    case 5:
        data = stbi_load("asset/image/tip/会车.png", &width, &height, &nrChannels, 0);
        break;
    case 6:
        data = stbi_load("asset/image/tip/靠边停车.png", &width, &height, &nrChannels, 0);
        break;
    case 7:
        data = stbi_load("asset/image/tip/路口直行.png", &width, &height, &nrChannels, 0);
        break;
    case 8:
        data = stbi_load("asset/image/tip/上车准备.png", &width, &height, &nrChannels, 0);
        break;
    case 9:
        data = stbi_load("asset/image/tip/学校.png", &width, &height, &nrChannels, 0);
        break;
    case 10:
        data = stbi_load("asset/image/tip/右转弯.png", &width, &height, &nrChannels, 0);
        break;
    case 11:
        data = stbi_load("asset/image/tip/直线行驶.png", &width, &height, &nrChannels, 0);
        break;
    case 12:
        data = stbi_load("asset/image/tip/左转弯.png", &width, &height, &nrChannels, 0);
        break;
    case 13:
        data = stbi_load("asset/image/tip/好.png", &width, &height, &nrChannels, 0);
        break;
    }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}

unsigned int* groundLoader()
{
    float vertices[] = {
        //     ---- 位置 ----    - 纹理坐标 -
           -25.0f, -25.0f, 0.0f,  0.0f, 0.0f,
            25.0f, -25.0f, 0.0f,  1.0f, 0.0f,
            25.0f,  25.0f, 0.0f,  1.0f, 1.0f,
            25.0f,  25.0f, 0.0f,  1.0f, 1.0f,
           -25.0f,  25.0f, 0.0f,  0.0f, 1.0f,
           -25.0f, -25.0f, 0.0f,  0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/ground.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);


    /*unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("asset/image/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);*/

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}

unsigned int* lightTest()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int param[] = { cubeVAO, lightCubeVAO};
    return param;
}