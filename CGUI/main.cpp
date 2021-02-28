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
#include<string>

#include"Car.h"
#include "functional.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

//���˵��ĸ���ť�ĳ���
int menu_icon_height = 70;
int menu_icon_width = 200;
//��ʾ�Ĵ�С
float tip_height = 220.0;
float tip_width = 390.0;
//����ʵʱ�ٶ�
float CAR_SPEED;


//imgui���ڲ���Ԥ��
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

    //��ʼ����
    bool show_window = true;
    bool set_windoe = false;
    bool rule_window = false;
    bool game_window = false;
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 clear_color = ImVec4(0.5f, 0.5f, 0.0f, 1.00f);

    stbi_set_flip_vertically_on_load(true);

    //��Ȳ���
    glEnable(GL_DEPTH_TEST);

    skyboxInit();
    Shader skyboxShader("shader/skybox.vs", "shader/skybox.fs");

    //�ƹ�
    Shader shader("shader/model_loading.vs", "shader/model_loading.fs");
    Shader shaderM("shader/lightModel.vs", "shader/lightModel.fs");

    std::cout << "��ȡtreeģ����......" << endl;
    Model treeModel("asset/models/trees/treesnew.obj");

    std::cout << "��ȡstreetģ����......" << endl;
    Model streetModel("asset/models/street/streetnew.obj");

    std::cout << "��ȡbuildingsģ����......" << endl;
    Model houseModel("asset/models/buildings/buildingsnew.obj");

    std::cout << "��ȡothersģ����......" << endl;
    Model othersModel("asset/models/others/othersnew.obj");
	
    std::cout << "��ȡcarģ����......" << endl;
    Model carModel("asset/models/car1/newcar.obj");


    std::cout << "ģ�Ͷ�ȡ���" << endl;

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    camera.Pitch = 5.0f;
    camera.Yaw = 180.0f;
    camera.Position = glm::vec3(0.0f, 0.6f, -1.93f);

    //==========================���˵�ҳ��==========================
    //--------��ť--------
    unsigned int* param_image = main_icon_Loader(1);
    unsigned int texture_image = param_image[2];

    unsigned int* param_image2 = main_icon_Loader(2);
    unsigned int texture_image2 = param_image2[2];

    unsigned int* param_image3 = main_icon_Loader(3);
    unsigned int texture_image3 = param_image3[2];

    unsigned int* param_image4 = main_icon_Loader(4);
    unsigned int texture_image4 = param_image4[2];

    //---------����--------
    Shader shaderGround_main("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param = mainBackgroundLoader();
    unsigned int VAO = param[0];
    unsigned int texture_main_bg = param[3];

    //==========================��Ϸ����==========================
    //--------ͼ��--------
    unsigned int* param_icon_rule_1 = rule_icon_Loader(1);
    unsigned int texture_rule_icon1 = param_icon_rule_1[2];
    //---------����--------
    Shader shaderGround_rule("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_ground_rule = ruleBackgroundLoader();
    unsigned int VAO_ground_rule = param_ground_rule[0];
    unsigned int texture_rule_bg = param_ground_rule[3];

    //==========================��Ϸҳ��==========================
    //--------ͼ��--------
    //��ȫ��
    unsigned int* param_icon_game_1 = game_icon_Loader(1);
    unsigned int texture_game_icon1 = param_icon_game_1[2];
    //��ͼ
    unsigned int* param_icon_game_2 = game_icon_Loader(2);
    unsigned int texture_game_icon2 = param_icon_game_2[2];
    //�ӽ�
    unsigned int* param_icon_game_3 = game_icon_Loader(3);
    unsigned int texture_game_icon3 = param_icon_game_3[2];
    //��ͣ
    unsigned int* param_icon_game_4 = game_icon_Loader(4);
    unsigned int texture_game_icon4 = param_icon_game_4[2];
    //����
    unsigned int* param_icon_game_5 = game_icon_Loader(5);
    unsigned int texture_game_icon5 = param_icon_game_5[2];
    //ɲ��
    unsigned int* param_icon_game_6 = game_icon_Loader(6);
    unsigned int texture_game_icon6 = param_icon_game_6[2];
    //��ɲ
    unsigned int* param_icon_game_7 = game_icon_Loader(7);
    unsigned int texture_game_icon7 = param_icon_game_7[2];
    //Σ�վ�ʾ��
    unsigned int* param_icon_game_8 = game_icon_Loader(8);
    unsigned int texture_game_icon8 = param_icon_game_8[2];
    //������
    unsigned int* param_icon_game_9 = game_icon_Loader(9);
    unsigned int texture_game_icon9 = param_icon_game_9[2];
    //�ٶ���ʾ��
    unsigned int* param_icon_game_10 = game_icon_Loader(10);
    unsigned int texture_game_icon10 = param_icon_game_10[2];
    //P��
    unsigned int* param_icon_game_11 = game_icon_Loader(11);
    unsigned int texture_game_icon11 = param_icon_game_11[2];
    //R��
    unsigned int* param_icon_game_12 = game_icon_Loader(12);
    unsigned int texture_game_icon12 = param_icon_game_12[2];
    //N��
    unsigned int* param_icon_game_13 = game_icon_Loader(13);
    unsigned int texture_game_icon13 = param_icon_game_13[2];
    //D��
    unsigned int* param_icon_game_14 = game_icon_Loader(14);
    unsigned int texture_game_icon14 = param_icon_game_14[2];
    //��ת���
    unsigned int* param_icon_game_15 = game_icon_Loader(15);
    unsigned int texture_game_icon15 = param_icon_game_15[2];
    //��ת���
    unsigned int* param_icon_game_16 = game_icon_Loader(16);
    unsigned int texture_game_icon16 = param_icon_game_16[2];
    //��ȫ��1
    unsigned int* param_icon_game_17 = game_icon_Loader(17);
    unsigned int texture_game_icon17 = param_icon_game_17[2];
    //��ɲ1
    unsigned int* param_icon_game_18 = game_icon_Loader(18);
    unsigned int texture_game_icon18 = param_icon_game_18[2];

    //--------��ʿ--------
    //�������
    unsigned int* tips_1 = tips_Loader(1);
    unsigned int texture_tips_1 = tips_1[2];
    //����
    unsigned int* tips_2 = tips_Loader(2);
    unsigned int texture_tips_2 = tips_2[2];
    //��ͷ
    unsigned int* tips_3 = tips_Loader(3);
    unsigned int texture_tips_3 = tips_3[2];
    //������վ
    unsigned int* tips_4 = tips_Loader(4);
    unsigned int texture_tips_4 = tips_4[2];
    //�ᳵ
    unsigned int* tips_5 = tips_Loader(5);
    unsigned int texture_tips_5 = tips_5[2];
    //����ͣ��
    unsigned int* tips_6 = tips_Loader(6);
    unsigned int texture_tips_6 = tips_6[2];
    //·��ֱ��
    unsigned int* tips_7 = tips_Loader(7);
    unsigned int texture_tips_7 = tips_7[2];
    //�ϳ�׼��
    unsigned int* tips_8 = tips_Loader(8);
    unsigned int texture_tips_8 = tips_8[2];
    //ѧУ
    unsigned int* tips_9 = tips_Loader(9);
    unsigned int texture_tips_9 = tips_9[2];
    //��ת��
    unsigned int* tips_10 = tips_Loader(10);
    unsigned int texture_tips_10 = tips_10[2];
    //ֱ����ʻ
    unsigned int* tips_11 = tips_Loader(11);
    unsigned int texture_tips_11 = tips_11[2];
    //��ת��
    unsigned int* tips_12 = tips_Loader(12);
    unsigned int texture_tips_12 = tips_12[2];


    //==========================��������==========================
    ISoundEngine* SoundEngine = createIrrKlangDevice();
    //SoundEngine->play2D("asset/music/bensound-littleidea.mp3", GL_TRUE);

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Poll and handle events
        glfwPollEvents();

        // ����һ֡��ʱ�䳤���Ա���ʹ֡�����ٶȾ���
        setDeltaTime();

        //������Ļ
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

 
        //���˵�����shader����
        shaderGround_main.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_main_bg);
        glUniform1i(glGetUniformLocation(shaderGround_main.ID, "texture1"), 0);

        //-------------------------------------------��ʼ����-------------------------------------------
        if (show_window)
        {
            //����ͼƬ
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

            //���˵����ĸ���ťʵ����ת

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

        //-----------------------------------------��Ϸ�������-------------------------------------------
        if (rule_window)
        {
            //���򱳾�shader����
            shaderGround_rule.use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_rule_bg);
            glUniform1i(glGetUniformLocation(shaderGround_rule.ID, "texture1"), 0);
            //����ͼƬ
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
            if (ImGui::InvisibleButton("����", ImVec2(menu_icon_width, menu_icon_height))) {
                std::cout << "����";
                show_window = true;
                set_windoe = false;
                rule_window = false;
                game_window = false;
            };
            ImGui::End();
        }

        //-------------------------------------------��Ϸ����-------------------------------------------
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

            //�����λ���ж�
            //glfwSetMouseButtonCallback(window, mouse_button_callback);

            ImGui::Begin("game Window1", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon4, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//��ͣ
            ImGui::Text("\n");
            if (!car.safety_belt) {
                ImGui::Image((ImTextureID*)texture_game_icon1, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//��ȫ��
            }
            else {
                ImGui::Image((ImTextureID*)texture_game_icon17, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//��ȫ��1
            }
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon2, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));//��ͼ
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon3, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1)); //�ӽ�
            ImGui::Text("\n");
            ImGui::End();



            ImGui::Begin("game Window1_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ͣ", ImVec2(50, 50))) {
                std::cout << "��ͣ";
            };
            if (ImGui::InvisibleButton("��ȫ��", ImVec2(50, 50))) {
                car.safety_belt = car.safety_belt;
                if (car.safety_belt) {
                    ////////////////////////////////////////////////////////////�����������Ӧ����ʾ��������ʾ��Ϣ
                     std::cout << "��ȫ���Ѿ�ϵ�ã����Գ�������";
                }
                else {
                    ////////////////////////////////////////////////////////////�����������Ӧ����ʾ��������ʾ��Ϣ
                    std::cout << "��ϵ�ð�ȫ����";

                }
            };
            ImGui::Text("\n");

            if (ImGui::InvisibleButton("��ͼ", ImVec2(50, 50))) {
                std::cout << "��ͼ";
            };
            ImGui::Text("\n");

            if (ImGui::InvisibleButton("�ӽ�", ImVec2(50, 50))) {
                std::cout << "�ӽ�";
            };
            ImGui::Text("\n");
            
            ImGui::Text("\n");
            ImGui::End();

            //����
            ImGui::Begin("game Window2", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon5, ImVec2(100, 150), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window2_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("����", ImVec2(100, 150))) {
                std::cout << "����";
            };
            ImGui::End();
            //ɲ��
            ImGui::Begin("game Window3", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon6, ImVec2(120, 90), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window3_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("ɲ��", ImVec2(120, 90))) {
                std::cout << "ɲ��";
                //brake = !brake;
            };
            ImGui::End();
            //��ɲ
            ImGui::Begin("game Window4", &game_window, window_flags);
            if (car.parkBrake) {
                ImGui::Image((ImTextureID*)texture_game_icon7, ImVec2(190, 90), ImVec2(0, 0), ImVec2(1, 1));
            }
            else {
                ImGui::Image((ImTextureID*)texture_game_icon18, ImVec2(190, 90), ImVec2(0, 0), ImVec2(1, 1));
            }
            ImGui::End();
            ImGui::Begin("game Window4_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ɲ", ImVec2(190, 90))) {
                car.parkBrake = !car.parkBrake;
                if (car.parkBrake) {
                    ////////////////////////////////////////////////////////////�����������Ӧ����ʾ��������ʾ��Ϣ
                    std::cout << "��ɲ��ɲ�ã�";
                }
                else {
                    ////////////////////////////////////////////////////////////�����������Ӧ����ʾ��������ʾ��Ϣ
                    std::cout << "δ������ɲ��";
                }
            };
            ImGui::End();
            //Σ�վ�ʾ��
            ImGui::Begin("game Window5", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon8, ImVec2(70, 70), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window5_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("Σ�վ�ʾ��", ImVec2(70, 70))) {
                std::cout << "Σ�վ�ʾ��";
            };
            ImGui::End();
            //������
            ImGui::Begin("game Window6", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon9, ImVec2(250, 250), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window6_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("������", ImVec2(250, 250))) {
                std::cout << "������";
            };
            ImGui::End();
            //�ٶ���ʾ��
            ImGui::Begin("game Window7", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon10, ImVec2(120, 60), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window7_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("�ٶ���ʾ��", ImVec2(120, 60))) {
                std::cout << "�ٶ���ʾ��";
            };
            ImGui::End();
            //��ʾ�����ٶ�
            ImGui::Begin("speed", &game_window, window_flags);
            ImGui::Text("%.1f", car.MovementSpeed * 10);
            ImGui::End();
            //�Զ���
            ImGui::Begin("game Window9", &game_window, window_flags);
            switch (automatic) {
            case 1:
                ImGui::Image((ImTextureID*)texture_game_icon11, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                car.switchTo("P");
                break;
            case 2:
                ImGui::Image((ImTextureID*)texture_game_icon12, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                car.switchTo("R");
                break;
            case 3:
                ImGui::Image((ImTextureID*)texture_game_icon13, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                car.switchTo("N");
                break;
            case 4:
                ImGui::Image((ImTextureID*)texture_game_icon14, ImVec2(120, 180), ImVec2(0, 0), ImVec2(1, 1));
                car.switchTo("D");
                break;
            }
            if (automatic > 4)automatic = 1;
            ImGui::End();
            ImGui::Begin("game Window9_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("�Զ���", ImVec2(120, 180))) {
                std::cout << "�Զ���";
                automatic++;
            };
            ImGui::End();
            //��ת���
            ImGui::Begin("game Window10", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon15, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window10_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ת���", ImVec2(60, 36))) {
                std::cout << "��ת���";
                car.leftLight = !car.leftLight;
            };
            ImGui::End();
            //��ת���
            ImGui::Begin("game Window11", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon16, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window11_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ת���", ImVec2(60, 36))) {
                std::cout << "��ת���";
                car.rightLight = !car.rightLight;
            };
            ImGui::End();


            camera.updateCameraVectors();

            // ��������
            handleKeyInput(window);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetCursorPosCallback(window, mouse_callback);

            // �۲�ռ�
            glm::mat4 view = glm::mat4(1.0f);
            //view = camera.GetViewMatrix(glm::vec3(car.Position.x, car.Position.y + 0.5f , car.Position.z));
            view = camera.GetViewMatrix();

            //ͶӰ
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // ��������
            glm::mat4 model = glm::mat4(1.0f);

            //��ɫ
            glm::vec3 ambient = glm::vec3(1.0f);
            glm::vec3 diffuse = glm::vec3(1.0f);
            glm::vec3 specular = glm::vec3(1.0f);

            //ģ����Ⱦ
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
            //cout << "(" << car.Position.x << "," << car.Position.y << "," << car.Position.z << ")"<< endl;
            //���������
            car.updateFront();
            float r = 1.93f;
            float angle = glm::radians(-car.getYaw()-90.0f);
            float s = sinf(angle);
            float c = cosf(angle);
            camera.Position.x = r * c + car.Position.x;
            camera.Position.z = r * s + car.Position.z;
            camera.updateCameraVectors();
            camera.Yaw = car.Yaw + 180.0f;

            //���ļӼ���
            car.run(deltaTime);

            ImGuiIO& io = ImGui::GetIO();
            ImFontAtlas* atlas = io.Fonts;
            ImFont* font= atlas->Fonts[0];
            //ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");
            font->Scale = 2;


            //����λ���жϣ���Ӧ�ص�����ʾ
            car_pos.x = car.Position.x;
            car_pos.y = car.Position.z;
            ImGui::Begin("TIPS1", &game_window, window_flags);
            if (IS_IN_AREA(car_pos, Area1_1)) {
                //////////////////////////////////////////////////·��ֱ����ʾ 
                ImGui::Image((ImTextureID*)texture_tips_7, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area1_2)) {
                //////////////////////////////////////////////////ֱ����ʻ��ʾ 
                ImGui::Image((ImTextureID*)texture_tips_11, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area1_3)) {
                //////////////////////////////////////////////////�ᳵ 
                ImGui::Image((ImTextureID*)texture_tips_5, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area1_4)) {
                //////////////////////////////////////////////////��ת�� 
                ImGui::Image((ImTextureID*)texture_tips_12, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area2_1)) {
                //////////////////////////////////////////////////·��ѧУ
                ImGui::Image((ImTextureID*)texture_tips_9, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area2_2)) {
                //////////////////////////////////////////////////��ͷ
                ImGui::Image((ImTextureID*)texture_tips_3, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area2_3)) {
                //////////////////////////////////////////////////����
                ImGui::Image((ImTextureID*)texture_tips_2, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area2_4)) {
                //////////////////////////////////////////////////��ת��
                ImGui::Image((ImTextureID*)texture_tips_10, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area3_1)) {
                //////////////////////////////////////////////////�������
                ImGui::Image((ImTextureID*)texture_tips_1, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area3_2)) {
                //////////////////////////////////////////////////������վ
                ImGui::Image((ImTextureID*)texture_tips_4, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            if (IS_IN_AREA(car_pos, Area3_3)) {
                //////////////////////////////////////////////////����ͣ��
                ImGui::Image((ImTextureID*)texture_tips_6, ImVec2(tip_width, tip_height), ImVec2(0, 0), ImVec2(1, 1));
            }
            ImGui::End();
            //��
            if ((car_pos.x==0&&car_pos.y==0)) {
                if (car.leftLight == true) {
                    start.Session1 = true;
                    std::cout << "��-------��ת���" << endl;
                }
                if ((start.Session1 == true) && (automatic == 4)) {
                    start.Session2 = true;
                    std::cout << "��-------D��" << endl;
                }
                if ((start.Session2 == true) && (car.parkBrake == false)) {
                    start.Session3 = true;
                    std::cout << "��-------��ɲ" << endl;
                }
            }
            //·��ֱ��
            if (crossingStraight.Session1 == false) {
                if (IS_IN_AREA(car_pos, crossingStraight.Area1)&& car.brake == true) {
                    crossingStraight.Session1 = true;
                    std::cout << "·��ֱ��-------ɲ��" << endl;
                }
            }
            if (IS_IN_AREA(car_pos, crossingStraight.Area2) && car_pos.x == 0) {
                crossingStraight.Session2 = true;
                std::cout << "·��ֱ��-------ֱ��" << endl;
            }else crossingStraight.Session2 = false;
            //ֱ����ʻ
            if (IS_IN_AREA(car_pos, goStraight.Area) && car_pos.x == 0) {
                goStraight.Session = true;
                std::cout << "ֱ����ʻ" << endl;
            }
            else goStraight.Session = false;
            //�ᳵ
            if (giveWay.Session1 == false){
                if (IS_IN_AREA(car_pos, giveWay.Area1) && car.brake == true){
                    giveWay.Session1 = true;
                    cout << "�ᳵ" << endl;

                }
            }
            //��ת��
            if (turnleft.Session1 == false && turnleft.Session2 == false && turnleft.Session3 == false){
                if (IS_IN_AREA(car_pos, turnleft.Area1) && car.leftLight == true){
                    turnleft.Session1 = true;
                    car.leftLight = false;
                }
                if ((turnleft.Session1 == true) && IS_IN_AREA(car_pos, turnleft.Area2) && (car.brake == true)){
                    turnleft.Session2 = true;
                    car.brake = false;
                }
                if ((turnleft.Session2 == true) && IS_IN_AREA(car_pos, turnleft.Area3)){
                    turnleft.Session3 = true;
                    cout << "��ת�价�ڵ÷֣�" << turnleft.Score() << "\n\n\n" << endl;
                }
            }
            //·��ѧУ
            if (passingSchool.Session1 == false){
                if (IS_IN_AREA(car_pos, passingSchool.Area1) && car.brake == true){
                    passingSchool.Session1 = true;
                    car.brake = false;
                    cout << "·��ѧУ���ڵ÷֣�" << passingSchool.Score() << "\n\n\n" << endl;
                }
            }
            //��ͷ
            if ((uTurn.Session1 == false) && (uTurn.Session2 == false)) {
                if ((IS_IN_AREA(car_pos, uTurn.Area1) && car.leftLight == true)) {
                    uTurn.Session1 = true;
                    cout << "��ͷ����һ�÷�" << endl;
                }
                if ((IS_IN_AREA(car_pos, uTurn.Area2) &&car.MovementSpeed<10)) {
                    uTurn.Session2 = true;
                    cout << "��ͷ���ڶ��÷�" << endl;
                }
            }
            //����
            if (IS_IN_AREA(car_pos, Area2_3)) {
                if ((overTake.Session1 == false) && (overTake.Session2 == false) && (overTake.Session3 == false) && (overTake.Session4 == false)) {
                    if (moveLane.changeNumber == 0) {
                        moveLane.lane1 = moveLane.detect(car_pos);
                        //�Ƿ��ڱ��ǰ����ת���
                        if (car.leftLight) {
                            overTake.Session1 = true;
                            std::cout << "����--------����ת���" << endl;
                        }
                    }
                    if ((moveLane.changeNumber == 0) && (moveLane.lane1 != moveLane.detect(car_pos))) {
                        moveLane.changeNumber = 1;
                        moveLane.lane2 = moveLane.detect(car_pos);
                        //�Ƿ�������
                        if (moveLane.lane2 < moveLane.lane1) {
                            overTake.Session2 = true;
                            std::cout << "����--------������" << endl;
                        }
                        //�Ƿ��ڱ��ǰ����ת���
                        if (car.rightLight) {
                            overTake.Session3 = true;
                            std::cout << "����--------����ת���" << endl;
                        }
                    }
                    if ((moveLane.changeNumber == 1) && (moveLane.lane2 != moveLane.detect(car_pos))) {
                        moveLane.changeNumber = 2;
                        moveLane.lane3 = moveLane.detect(car_pos);
                        if (moveLane.lane3 > moveLane.lane2) {
                            //�Ƿ����ұ��
                            overTake.Session4 = true;
                            std::cout << "����--------���ұ��" << endl;
                        }
                    }
                }
            }
            

            //��ת��
            if (turnright.Session1 == false && turnright.Session2 == false && turnright.Session3 == false){
                if (IS_IN_AREA(car_pos, turnright.Area1) && car.rightLight == true){
                    turnright.Session1 = true;
                    car.rightLight = false;
                }
                if ((turnright.Session1 == true) && IS_IN_AREA(car_pos, turnright.Area2) && (car.brake == true)){
                    turnright.Session2 = true;
                    car.brake = false;
                }
                if ((turnright.Session2 == true) && IS_IN_AREA(car_pos, turnright.Area3)){
                    turnright.Session3 = true;
                    cout << "��ת�价�ڵ÷֣�" << turnright.Score() << "\n\n\n" << endl;
                }
            }
            //�������
            if (IS_IN_AREA(car_pos, Area3_1)) {
                //��û�б��
                if (moveLane.changeNumber == 0) {
                    moveLane.lane1 = moveLane.detect(car_pos);             
                }
                if (moveLane.lane1 != moveLane.detect(car_pos)) {
                    moveLane.changeNumber = 1;
                    moveLane.lane2 = moveLane.detect(car_pos);
                }
                if (moveLane.lane2 != moveLane.detect(car_pos)) {
                    moveLane.changeNumber = 2;
                    moveLane.lane3 = moveLane.detect(car_pos);
                    if (moveLane.lane3 == moveLane.lane1) {
                       std::cout<< moveLane.Score();
                    }
                }
               
            }


            //·��������վ
            if (passingBusStop.Session1 == false){
                if (IS_IN_AREA(car_pos, passingBusStop.Area) && car.brake == true){
                    passingBusStop.Session1 = true;
                    car.brake = false;
                    cout << "·��������վ���ڵ÷֣�" << passingBusStop.Score() << "\n\n\n" << endl;
                }
            }
            //����ͣ��



            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            renderSkyBox(skyboxShader);
            // ��ԭ��Ȳ���
            glDepthFunc(GL_LESS);
        }

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