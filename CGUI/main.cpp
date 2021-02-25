#include "imgui.h"

#include "imgui_impl_glfw.h"

#include "imgui_impl_opengl3.h"

#include <stdio.h>

#include<glad/glad.h> // Initialize with gladLoadGL()

#include <GLFW/glfw3.h>

#include<learnopengl/shader.h>
#include<learnopengl/camera.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>

#include<stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include"Car.h"
#include "functional.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

//主菜单四个按钮的长宽
int menu_icon_height = 70;
int menu_icon_width = 200;
//自动挡挡位
int automatic = 1;
//默认安全带是断开的
bool safety_belt = false;
//默认车没有在行驶
bool isMoving = false;

bool parkBrake = false;






//imgui窗口参数预设
//static bool no_titlebar = false;
//static bool no_scrollbar = false;
//static bool no_menu = false;
//static bool no_move = false;
//static bool no_resize = false;
//static bool no_collapse = false;
//static bool no_close = false;
//static bool no_nav = false;
//static bool no_background = false;
//static bool no_bring_to_front = false;
static bool no_titlebar = true;
static bool no_scrollbar = true;
static bool no_menu = true;
static bool no_move = true;
static bool no_resize = true;
static bool no_collapse = true;
static bool no_close = true;
static bool no_nav = true;
static bool no_background = true;
static bool no_bring_to_front = false;
ImGuiWindowFlags window_flags = 0;



int main(int, char**)
{
    GLFWwindow* window = windowInit();

    //初始设置
    bool show_window = true;
    bool set_windoe = false;
    bool rule_window = false;
    bool game_window = false;
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 clear_color = ImVec4(0.5f, 0.5f, 0.0f, 1.00f);

    stbi_set_flip_vertically_on_load(true);

    //深度测试
    glEnable(GL_DEPTH_TEST);

    skyboxInit();
    Shader skyboxShader("shader/skybox.vs", "shader/skybox.fs");

    //灯光
    Shader shader("shader/model_loading.vs", "shader/model_loading.fs");
    Shader shaderM("shader/lightModel.vs", "shader/lightModel.fs");

    std::cout << "读取tree模型中......" << endl;
    Model treeModel("asset/models/trees/treesnew.obj");

    std::cout << "读取street模型中......" << endl;
    Model streetModel("asset/models/street/streetnew.obj");

    std::cout << "读取buildings模型中......" << endl;
    Model houseModel("asset/models/buildings/buildingsnew.obj");

    std::cout << "读取others模型中......" << endl;
    Model othersModel("asset/models/others/othersnew.obj");
	
    std::cout << "读取car模型中......" << endl;
    Model carModel("asset/models/car1/newcar.obj");


    std::cout << "模型读取完毕" << endl;

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    camera.Pitch = 5.0f;
    camera.Yaw = 180.0f;
    camera.Position = glm::vec3(0.0f, 0.6f, -1.93f);

    //==========================主菜单页面==========================
    //--------按钮--------
    unsigned int* param_image = main_icon_Loader(1);
    unsigned int texture_image = param_image[2];

    unsigned int* param_image2 = main_icon_Loader(2);
    unsigned int texture_image2 = param_image2[2];

    unsigned int* param_image3 = main_icon_Loader(3);
    unsigned int texture_image3 = param_image3[2];

    unsigned int* param_image4 = main_icon_Loader(4);
    unsigned int texture_image4 = param_image4[2];

    //---------背景--------
    Shader shaderGround_main("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param = mainBackgroundLoader();
    unsigned int VAO = param[0];
    unsigned int texture_main_bg = param[3];

    //==========================游戏规则==========================
    //--------图标--------
    unsigned int* param_icon_rule_1 = rule_icon_Loader(1);
    unsigned int texture_rule_icon1 = param_icon_rule_1[2];
    //---------背景--------
    Shader shaderGround_rule("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_ground_rule = ruleBackgroundLoader();
    unsigned int VAO_ground_rule = param_ground_rule[0];
    unsigned int texture_rule_bg = param_ground_rule[3];

    //==========================游戏页面==========================
    //--------图标--------
    //安全带
    unsigned int* param_icon_game_1 = game_icon_Loader(1);
    unsigned int texture_game_icon1 = param_icon_game_1[2];
    //地图
    unsigned int* param_icon_game_2 = game_icon_Loader(2);
    unsigned int texture_game_icon2 = param_icon_game_2[2];
    //视角
    unsigned int* param_icon_game_3 = game_icon_Loader(3);
    unsigned int texture_game_icon3 = param_icon_game_3[2];
    //暂停
    unsigned int* param_icon_game_4 = game_icon_Loader(4);
    unsigned int texture_game_icon4 = param_icon_game_4[2];
    //油门
    unsigned int* param_icon_game_5 = game_icon_Loader(5);
    unsigned int texture_game_icon5 = param_icon_game_5[2];
    //刹车
    unsigned int* param_icon_game_6 = game_icon_Loader(6);
    unsigned int texture_game_icon6 = param_icon_game_6[2];
    //手刹
    unsigned int* param_icon_game_7 = game_icon_Loader(7);
    unsigned int texture_game_icon7 = param_icon_game_7[2];
    //危险警示灯
    unsigned int* param_icon_game_8 = game_icon_Loader(8);
    unsigned int texture_game_icon8 = param_icon_game_8[2];
    //方向盘
    unsigned int* param_icon_game_9 = game_icon_Loader(9);
    unsigned int texture_game_icon9 = param_icon_game_9[2];
    //速度显示框
    unsigned int* param_icon_game_10 = game_icon_Loader(10);
    unsigned int texture_game_icon10 = param_icon_game_10[2];
    //P档
    unsigned int* param_icon_game_11 = game_icon_Loader(11);
    unsigned int texture_game_icon11 = param_icon_game_11[2];
    //R档
    unsigned int* param_icon_game_12 = game_icon_Loader(12);
    unsigned int texture_game_icon12 = param_icon_game_12[2];
    //N档
    unsigned int* param_icon_game_13 = game_icon_Loader(13);
    unsigned int texture_game_icon13 = param_icon_game_13[2];
    //D档
    unsigned int* param_icon_game_14 = game_icon_Loader(14);
    unsigned int texture_game_icon14 = param_icon_game_14[2];
    //左转弯灯
    unsigned int* param_icon_game_15 = game_icon_Loader(15);
    unsigned int texture_game_icon15 = param_icon_game_15[2];
    //右转弯灯
    unsigned int* param_icon_game_16 = game_icon_Loader(16);
    unsigned int texture_game_icon16 = param_icon_game_16[2];
    //安全带1
    unsigned int* param_icon_game_17 = game_icon_Loader(17);
    unsigned int texture_game_icon17 = param_icon_game_17[2];
    //手刹1
    unsigned int* param_icon_game_18 = game_icon_Loader(18);
    unsigned int texture_game_icon18 = param_icon_game_18[2];

    //--------图标--------
    //变更车道
    unsigned int* tips_1 = tips_Loader(1);
    unsigned int texture_tips_1 = tips_1[2];
    //超车
    unsigned int* tips_2 = tips_Loader(2);
    unsigned int texture_tips_2 = tips_2[2];
    //掉头
    unsigned int* tips_3 = tips_Loader(3);
    unsigned int texture_tips_3 = tips_3[2];
    //公交车站
    unsigned int* tips_4 = tips_Loader(4);
    unsigned int texture_tips_4 = tips_4[2];
    //会车
    unsigned int* tips_5 = tips_Loader(5);
    unsigned int texture_tips_5 = tips_5[2];
    //靠边停车
    unsigned int* tips_6 = tips_Loader(6);
    unsigned int texture_tips_6 = tips_6[2];
    //路口直行
    unsigned int* tips_7 = tips_Loader(7);
    unsigned int texture_tips_7 = tips_7[2];
    //上车准备
    unsigned int* tips_8 = tips_Loader(8);
    unsigned int texture_tips_8 = tips_8[2];
    //学校
    unsigned int* tips_9 = tips_Loader(9);
    unsigned int texture_tips_9 = tips_9[2];
    //右转弯
    unsigned int* tips_10 = tips_Loader(10);
    unsigned int texture_tips_10 = tips_10[2];
    //直线行驶
    unsigned int* tips_11 = tips_Loader(11);
    unsigned int texture_tips_11 = tips_11[2];
    //左转弯
    unsigned int* tips_12 = tips_Loader(12);
    unsigned int texture_tips_12 = tips_12[2];


    //==========================背景音乐==========================
    ISoundEngine* SoundEngine = createIrrKlangDevice();
    //SoundEngine->play2D("asset/music/bensound-littleidea.mp3", GL_TRUE);

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Poll and handle events
        glfwPollEvents();

        // 计算一帧的时间长度以便于使帧绘制速度均匀
        setDeltaTime();

        //绘制屏幕
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

 
        //主菜单背景shader激活
        shaderGround_main.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_main_bg);
        glUniform1i(glGetUniformLocation(shaderGround_main.ID, "texture1"), 0);

        //-------------------------------------------开始界面-------------------------------------------
        if (show_window)
        {
            //背景图片
            shaderGround_main.use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

           
            if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
            if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
            if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
            if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
            if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
            if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
            if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
            if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
            if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

            ImGui::Begin("Another Window", &show_window, window_flags);

            //主菜单的四个按钮实现跳转

            if (ImGui::ImageButton((ImTextureID*)texture_image, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)){
				SoundEngine->play2D("asset/music/2.wav", GL_FALSE);
                show_window = false;
                set_windoe = false;
                rule_window = false;
                game_window = true;
            }
            ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image2, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)){
				SoundEngine->play2D("asset/music/2.wav", GL_FALSE);
				show_window = false;
                set_windoe = false;
                rule_window = true;
                game_window = false;
            }ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image3, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)) {
				SoundEngine->play2D("asset/music/2.wav", GL_FALSE);

				show_window = false;
                set_windoe = true;
                rule_window = false;
                game_window = false;
            }ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image4, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)) {
				SoundEngine->play2D("asset/music/2.wav", GL_FALSE);

            }
            
            ImGui::End();
        }

        //-----------------------------------------游戏规则界面-------------------------------------------
        if (rule_window)
        {
            //规则背景shader激活
            shaderGround_rule.use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_rule_bg);
            glUniform1i(glGetUniformLocation(shaderGround_rule.ID, "texture1"), 0);
            //背景图片
            shaderGround_rule.use();
            glBindVertexArray(VAO_ground_rule);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
            if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
            if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
            if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
            if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
            if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
            if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
            if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
            if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

            ImGui::Begin("Rule Window", &rule_window, window_flags);
            ImGui::ImageButton((ImTextureID*)texture_rule_icon1, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();

            ImGui::Begin("Rule Window_1", &rule_window, window_flags);
            if (ImGui::InvisibleButton("规则", ImVec2(menu_icon_width, menu_icon_height))) {
                std::cout << "规则";
                show_window = true;
                set_windoe = false;
                rule_window = false;
                game_window = false;
            };
            ImGui::End();
        }

        //-------------------------------------------游戏界面-------------------------------------------
        if (game_window) {
            if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
            if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
            if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
            if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
            if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
            if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
            if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
            if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
            if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

            //鼠标点击位置判断
            glfwSetMouseButtonCallback(window, mouse_button_callback);

            ImGui::Begin("game Window1", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon4, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//暂停
            ImGui::Text("\n");
            if (!safety_belt) {
                ImGui::Image((ImTextureID*)texture_game_icon1, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//安全带
            }
            else {
                ImGui::Image((ImTextureID*)texture_game_icon17, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//安全带1
            }
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon2, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//地图
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon3, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1)); //视角
            ImGui::Text("\n");
            ImGui::End();



            ImGui::Begin("game Window1_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("暂停", ImVec2(50, 50))) {
                std::cout << "暂停";
            };
            if (ImGui::InvisibleButton("安全带", ImVec2(50, 50))) {
                safety_belt = !safety_belt;
                if (safety_belt) {
                    ////////////////////////////////////////////////////////////在这里插入相应的提示音或者提示信息
                     std::cout << "安全带已经系好，可以出发啦！";
                }
                else {
                    ////////////////////////////////////////////////////////////在这里插入相应的提示音或者提示信息
                    std::cout << "请系好安全带！";

                }
            };
            ImGui::Text("\n");

            if (ImGui::InvisibleButton("地图", ImVec2(50, 50))) {
                std::cout << "地图";
            };
            ImGui::Text("\n");

            if (ImGui::InvisibleButton("视角", ImVec2(50, 50))) {
                std::cout << "视角";
            };
            ImGui::Text("\n");
            
            ImGui::Text("\n");
            ImGui::End();

            //油门
            ImGui::Begin("game Window2", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon5, ImVec2(100, 150), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window2_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("油门", ImVec2(100, 150))) {
                std::cout << "油门";
            };
            ImGui::End();
            //刹车
            ImGui::Begin("game Window3", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon6, ImVec2(120, 90), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window3_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("刹车", ImVec2(120, 90))) {
                std::cout << "刹车";
            };
            ImGui::End();
            //手刹
            ImGui::Begin("game Window4", &game_window, window_flags);
            if (parkBrake) {
                ImGui::Image((ImTextureID*)texture_game_icon7, ImVec2(190, 90), ImVec2(0, 0), ImVec2(1, 1));
            }
            else {
                ImGui::Image((ImTextureID*)texture_game_icon18, ImVec2(190, 90), ImVec2(0, 0), ImVec2(1, 1));
            }
            ImGui::End();
            ImGui::Begin("game Window4_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("手刹", ImVec2(190, 90))) {
                parkBrake = !parkBrake;
                if (parkBrake) {
                    ////////////////////////////////////////////////////////////在这里插入相应的提示音或者提示信息
                    std::cout << "手刹已刹好！";
                }
                else {
                    ////////////////////////////////////////////////////////////在这里插入相应的提示音或者提示信息
                    std::cout << "未拉上手刹！";
                }
            };
            ImGui::End();
            //危险警示灯
            ImGui::Begin("game Window5", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon8, ImVec2(70, 70), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window5_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("危险警示灯", ImVec2(70, 70))) {
                std::cout << "危险警示灯";
            };
            ImGui::End();
            //方向盘
            ImGui::Begin("game Window6", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon9, ImVec2(250, 250), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window6_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("方向盘", ImVec2(250, 250))) {
                std::cout << "方向盘";
            };
            ImGui::End();
            //速度显示框
            ImGui::Begin("game Window7", &game_window, window_flags);
            ImGui::ImageButton((ImTextureID*)texture_game_icon10, ImVec2(120, 60), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window7_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("速度显示框", ImVec2(120, 60))) {
                std::cout << "速度显示框";
            };
            ImGui::End();
            //自动挡
            ImGui::Begin("game Window9", &game_window, window_flags);
            switch (automatic) {
            case 1:
                ImGui::Image((ImTextureID*)texture_game_icon11, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                break;
            case 2:
                ImGui::Image((ImTextureID*)texture_game_icon12, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                break;
            case 3:
                ImGui::Image((ImTextureID*)texture_game_icon13, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                break;
            case 4:
                ImGui::Image((ImTextureID*)texture_game_icon14, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                break;
            }
            if (automatic > 4)automatic = 1;
            ImGui::End();
            ImGui::Begin("game Window9_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("自动挡", ImVec2(120, 180))) {
                std::cout << "自动挡";
                automatic++;
            };
            ImGui::End();
            //左转弯灯
            ImGui::Begin("game Window10", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon15, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window10_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("左转弯灯", ImVec2(60, 36))) {
                std::cout << "左转弯灯";
                automatic++;
            };
            ImGui::End();
            //右转弯灯
            ImGui::Begin("game Window11", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon16, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window11_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("右转弯灯", ImVec2(60, 36))) {
                std::cout << "右转弯灯";
                automatic++;
            };
            ImGui::End();


            camera.updateCameraVectors();

            // 监听按键
            handleKeyInput(window);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetCursorPosCallback(window, mouse_callback);

            // 观察空间
            glm::mat4 view = glm::mat4(1.0f);
            //view = camera.GetViewMatrix(glm::vec3(car.Position.x, car.Position.y + 0.5f , car.Position.z));
            view = camera.GetViewMatrix();

            //投影
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // 世界坐标
            glm::mat4 model = glm::mat4(1.0f);

            //颜色
            glm::vec3 ambient = glm::vec3(1.0f);
            glm::vec3 diffuse = glm::vec3(1.0f);
            glm::vec3 specular = glm::vec3(1.0f);

            //模型渲染
            shaderM.use();
            //shaderM
            shaderM.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			shaderM.setVec3("dirLight.ambient", 0.7f, 0.7f, 0.6f);
			shaderM.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.2f);
			shaderM.setVec3("dirLight.specular", 0.4f, 0.2f, 0.4f);
            shaderM.setVec3("spotLight.position", camera.Position);
            shaderM.setVec3("spotLight.direction", camera.Front);
            shaderM.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            shaderM.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
            shaderM.setVec3("viewPos", camera.Position);
            shaderM.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
            shaderM.setVec3("spotLight.diffuse", 0.3f, 0.3f, 0.3f);
            shaderM.setVec3("spotLight.specular", 0.2f, 0.2f, 0.2f);
            shaderM.setFloat("spotLight.constant", 1.0f);
            shaderM.setFloat("spotLight.linear", 0.09f);
            shaderM.setFloat("spotLight.quadratic", 0.032f);
            shaderM.setFloat("material.shininess", 32.0f);
            shaderM.setMat4("projection", projection);
            shaderM.setMat4("view", view);
            // tree
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
            shaderM.setMat4("model", model);
            treeModel.Draw(shaderM);

            //house
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
            shaderM.setMat4("model", model);
            houseModel.Draw(shaderM);

            //street
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
            shaderM.setMat4("model", model);
            streetModel.Draw(shaderM);

            //others
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
            shaderM.setMat4("model", model);
            othersModel.Draw(shaderM);

            //car
			model = glm::mat4(1.0f);
			model = glm::translate(model, car.Position); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
            model = glm::rotate(model, glm::radians(car.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
			shaderM.setMat4("model", model);
			carModel.Draw(shaderM);
            cout << "(" << car.Position.x << "," << car.Position.y << "," << car.Position.z << ")"<< endl;
            //摄像机跟随
            car.updateFront();
            float r = 1.93f;
            float angle = glm::radians(-car.getYaw()-90.0f);
            float s = sinf(angle);
            float c = cosf(angle);
            camera.Position.x = r * c + car.Position.x;
            camera.Position.z = r * s + car.Position.z;
            camera.updateCameraVectors();
            camera.Yaw = car.Yaw + 180.0f;
           

            //车的位置判断，相应地弹出提示

            if (isMoving) {
                
            }

            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            renderSkyBox(skyboxShader);
            // 复原深度测试
            glDepthFunc(GL_LESS);
        }
        //if (game_window) {
        //    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        //    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        //    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        //    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        //    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        //    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        //    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        //    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        //    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        //    ImGui::Begin("game Window1", &game_window, window_flags);
        //    if (ImGui::ImageButton((ImTextureID*)texture_game_icon1, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(1,1,1, 0), ImVec4(0, 0,1,0.5))) {
        //        std::cout << "icon1";
        //    }
        //    ImGui::Text("\n");
        //    ImGui::Image((ImTextureID*)texture_game_icon2, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));
        //    if (ImGui::InvisibleButton("test", ImVec2(50, 50))) {
        //        std::cout << "icon2";
        //    };
        //    ImGui::Text("\n");
        //   /* if (ImGui::ImageButton((ImTextureID*)texture_game_icon2, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //        std::cout << "icon2";
        //    }
        //    ImGui::Text("\n");*/
        //    if (ImGui::ImageButton((ImTextureID*)texture_game_icon3, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //        std::cout << "icon3";
        //    }
        //    ImGui::Text("\n");
        //    if (ImGui::ImageButton((ImTextureID*)texture_game_icon4, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //        std::cout << "icon4";
        //    }
        //    ImGui::Text("\n");
        //    ImGui::End();
        //    //油门
        //   ImGui::Begin("game Window2", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon5, ImVec2(100, 150), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon5";
        //   }
        //   ImGui::End();
        //   //刹车
        //   ImGui::Begin("game Window3", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon6, ImVec2(120, 90), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon6";
        //   }
        //   ImGui::End();
        //   //手刹
        //   ImGui::Begin("game Window4", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon7, ImVec2(190,90), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon7";
        //   }
        //   ImGui::End();
        //    //危险警示灯
        //   ImGui::Begin("game Window5", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon8, ImVec2(70, 70), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon8";
        //   }
        //   ImGui::End();
        //   //方向盘
        //   ImGui::Begin("game Window6", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon9, ImVec2(250, 250), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon9";
        //   }
        //   ImGui::End();
        //   //速度显示框
        //   ImGui::Begin("game Window7", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon10, ImVec2(120, 60), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon10";
        //   }
        //   ImGui::End();
        //   //自动挡
        //   ImGui::Begin("game Window9", &game_window, window_flags);
        //   switch (automatic) {
        //   case 1:
        //       if (ImGui::ImageButton((ImTextureID*)texture_game_icon11, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //           automatic++;
        //       std::cout << "icon11";
        //       }
        //       break;
        //   case 2:
        //       if (ImGui::ImageButton((ImTextureID*)texture_game_icon12, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //           automatic++;
        //           std::cout << "icon12";
        //       }
        //       break;
        //   case 3:
        //       if (ImGui::ImageButton((ImTextureID*)texture_game_icon13, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //           automatic++;
        //           std::cout << "icon13";
        //       }
        //       break;
        //   case 4:
        //       if (ImGui::ImageButton((ImTextureID*)texture_game_icon14, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //           automatic++;
        //           std::cout << "icon14";
        //       }
        //       break;
        //   }
        //   if (automatic > 4)automatic = 1;
        //   ImGui::End();
        //   //左转弯灯
        //   ImGui::Begin("game Window10", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon15, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon15";
        //   }
        //   ImGui::End();
        //   //右转弯灯
        //   ImGui::Begin("game Window11", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon16, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon16";
        //   }
        //   ImGui::End();
        //    //鼠标点击位置判断
        //    glfwSetMouseButtonCallback(window, mouse_button_callback);
        //    camera.updateCameraVectors();
        //    // 监听按键
        //    handleKeyInput(window);
        //    glfwSetScrollCallback(window, scroll_callback);
        //    glfwSetCursorPosCallback(window, mouse_callback);
        //    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //    // 观察空间
        //    glm::mat4 view = glm::mat4(1.0f);
        //    view = camera.GetViewMatrix();
        //    //投影
        //    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //    // 世界坐标
        //    glm::mat4 model = glm::mat4(1.0f);
        //    //颜色
        //    glm::vec3 ambient = glm::vec3(1.0f);
        //    glm::vec3 diffuse = glm::vec3(1.0f);
        //    glm::vec3 specular = glm::vec3(1.0f);
        //    /*ImGui::Begin("Window", &game_window);
        //    ImGui::SliderFloat("环境光r", &transx, 0.0f, 0.2);
        //    ImGui::SliderFloat("环境光g", &transy, 0.0f, 0.2);
        //    ImGui::SliderFloat("环境光b", &transz, 0.0f, 0.2);
        //    ImGui::SliderFloat("漫反射r", &transx1, 0.0f, 0.2);
        //    ImGui::SliderFloat("漫反射g", &transy1, 0.0f, 0.2);
        //    ImGui::SliderFloat("漫反射b", &transz1, 0.0f, 0.2);
        //    ImGui::SliderFloat("镜面r", &transx2, 0.0f, 0.2);
        //    ImGui::SliderFloat("镜面g", &transy2, 0.0f, 0.2);
        //    ImGui::SliderFloat("镜面b", &transz2, 0.0f, 0.2);
        //    ImGui::End();*/
        //    //模型渲染
        //    shaderM.use();
        //    //shaderM
        //    shaderM.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        //    shaderM.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
        //    shaderM.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
        //    shaderM.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
        //    shaderM.setVec3("spotLight.position", camera.Position);
        //    shaderM.setVec3("spotLight.direction", camera.Front);
        //    shaderM.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        //    shaderM.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        //    shaderM.setVec3("viewPos", camera.Position);
        //    shaderM.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
        //    shaderM.setVec3("spotLight.diffuse", 0.3f, 0.3f, 0.3f);
        //    shaderM.setVec3("spotLight.specular", 0.2f, 0.2f, 0.2f);
        //    shaderM.setFloat("spotLight.constant", 1.0f);
        //    shaderM.setFloat("spotLight.linear", 0.09f);
        //    shaderM.setFloat("spotLight.quadratic", 0.032f);
        //    shaderM.setFloat("material.shininess", 32.0f);
        //    shaderM.setMat4("projection", projection);
        //    shaderM.setMat4("view", view);
        //    // tree
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f)); // translate it down so it's at the center of the scene
        //    model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
        //    shaderM.setMat4("model", model);
        //    treeModel.Draw(shaderM);
        //    //house
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //    model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
        //    shaderM.setMat4("model", model);
        //    houseModel.Draw(shaderM);
        //    //street
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //    model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
        //    shaderM.setMat4("model", model);
        //    streetModel.Draw(shaderM);
        //    //others
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //    model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));	// it's a bit too big for our scene, so scale it down
        //    shaderM.setMat4("model", model);
        //    othersModel.Draw(shaderM);
        //    
        //    //car1
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, car.getPosition()); // translate it down so it's at the center of the scene
        //    model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));	// it's a bit too big for our scene, so scale it down
        //    model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //    shaderM.setMat4("model", model);
        //    carModel.Draw(shaderM);
        //    glDepthFunc(GL_LEQUAL);
        //    skyboxShader.use();
        //    renderSkyBox(skyboxShader);
        //    // 复原深度测试
        //    glDepthFunc(GL_LESS);
        //}

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
        // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}