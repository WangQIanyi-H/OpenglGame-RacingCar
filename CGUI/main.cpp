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

//���˵��ĸ���ť�ĳ���
int menu_icon_height = 70;
int menu_icon_width = 200;
//�Զ�����λ
int automatic = 1;
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
    Model treeModel("asset/models/trees/trees.obj");

    std::cout << "��ȡstreetģ����......" << endl;
    Model streetModel("asset/models/street/street.obj");

    std::cout << "��ȡbuildingsģ����......" << endl;
    Model houseModel("asset/models/buildings/buildings.obj");

    std::cout << "��ȡothersģ����......" << endl;
    Model othersModel("asset/models/others/others.obj");

    std::cout << "��ȡcarģ����......" << endl;
    Model carModel("asset/models/car1/car1.obj");


    std::cout << "ģ�Ͷ�ȡ���" << endl;

    float transx = 0.1f;
    float transy = 0.1f;
    float transz = 0.1f;
    float transx1 = 1.0f;
    float transy1 = 1.0f;
    float transz1 = 1.0f;
    float transx2 = 0.1f;
    float transy2 = 0.1f;
    float transz2 = 0.1f;

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    camera.Pitch = -18.9f;
    camera.Position = glm::vec3(5.2f, 0.7f, 0.33f);

    //==========================���˵�ҳ��==========================
    //--------��ť--------
   // Shader shaderImage("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image = main_icon_Loader(1);
    //unsigned int VAO_image = param_image[0];
    unsigned int texture_image = param_image[2];

   // Shader shaderImage2("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image2 = main_icon_Loader(2);
   // unsigned int VAO_image2 = param_image2[0];
    unsigned int texture_image2 = param_image2[2];

   // Shader shaderImage3("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image3 = main_icon_Loader(3);
    //unsigned int VAO_image3 = param_image3[0];
    unsigned int texture_image3 = param_image3[2];

    //Shader shaderImage4("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image4 = main_icon_Loader(4);
    //unsigned int VAO_image4 = param_image4[0];
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
    
    //==========================��������==========================
    ISoundEngine* SoundEngine = createIrrKlangDevice();
    //SoundEngine->play2D("asset/music/1.mp3", GL_TRUE);

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
                show_window = false;
                set_windoe = false;
                rule_window = false;
                game_window = true;
            }
            ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image2, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)){
                show_window = false;
                set_windoe = false;
                rule_window = true;
                game_window = false;
            }ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image3, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)) {
                show_window = false;
                set_windoe = true;
                rule_window = false;
                game_window = false;
            }ImGui::Text("\n\n");

            if (ImGui::ImageButton((ImTextureID*)texture_image4, ImVec2(menu_icon_width, menu_icon_height), ImVec2(0, 0), ImVec2(1, 1), 0)) {
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

<<<<<<< Updated upstream
            //�����λ���ж�
            glfwSetMouseButtonCallback(window, mouse_button_callback);


=======
            
            
            ImGui::Begin("game Window1", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon1, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon2, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon3, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1)); 
            ImGui::Text("\n");
            ImGui::Image((ImTextureID*)texture_game_icon4, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();

            ImGui::Begin("game Window1_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ȫ��", ImVec2(50, 50))) {
                std::cout << "��ȫ��";
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
            if (ImGui::InvisibleButton("��ͣ", ImVec2(50, 50))) {
                std::cout << "��ͣ";
            };
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
            };
            ImGui::End();
            //��ɲ
            ImGui::Begin("game Window4", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon7, ImVec2(190, 90), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window4_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ɲ", ImVec2(190, 90))) {
                std::cout << "��ɲ";
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
            ImGui::ImageButton((ImTextureID*)texture_game_icon10, ImVec2(120, 60), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window7_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("�ٶ���ʾ��", ImVec2(120, 60))) {
                std::cout << "�ٶ���ʾ��";
            };
            ImGui::End();
            //�Զ���
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
                automatic++;
            };
            ImGui::End();
            //��ת���
            ImGui::Begin("game Window11", &game_window, window_flags);
            ImGui::Image((ImTextureID*)texture_game_icon16, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::End();
            ImGui::Begin("game Window11_1", &game_window, window_flags);
            if (ImGui::InvisibleButton("��ת���", ImVec2(60, 36))) {
                std::cout << "��ת���";
                automatic++;
            };
            ImGui::End();


            //�����λ���ж�
            glfwSetMouseButtonCallback(window, mouse_button_callback);
>>>>>>> Stashed changes
            camera.updateCameraVectors();

            // ��������
            handleKeyInput(window);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetCursorPosCallback(window, mouse_callback);

            // �۲�ռ�
            glm::mat4 view = glm::mat4(1.0f);
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
            shaderM.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
            shaderM.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
            shaderM.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
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


            //car1
            model = glm::mat4(1.0f);
            model = glm::translate(model, car.getPosition()); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));	// it's a bit too big for our scene, so scale it down
            model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(car.getYaw() - car.getDelayYaw() / 2), WORLD_UP);
            shaderM.setMat4("model", model);
            carModel.Draw(shaderM);

            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            renderSkyBox(skyboxShader);
            // ��ԭ��Ȳ���
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
        //    //����
        //   ImGui::Begin("game Window2", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon5, ImVec2(100, 150), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon5";
        //   }
        //   ImGui::End();
        //   //ɲ��
        //   ImGui::Begin("game Window3", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon6, ImVec2(120, 90), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon6";
        //   }
        //   ImGui::End();
        //   //��ɲ
        //   ImGui::Begin("game Window4", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon7, ImVec2(190,90), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon7";
        //   }
        //   ImGui::End();
        //    //Σ�վ�ʾ��
        //   ImGui::Begin("game Window5", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon8, ImVec2(70, 70), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon8";
        //   }
        //   ImGui::End();
        //   //������
        //   ImGui::Begin("game Window6", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon9, ImVec2(250, 250), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon9";
        //   }
        //   ImGui::End();
        //   //�ٶ���ʾ��
        //   ImGui::Begin("game Window7", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon10, ImVec2(120, 60), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon10";
        //   }
        //   ImGui::End();
        //   //�Զ���
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
        //   //��ת���
        //   ImGui::Begin("game Window10", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon15, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon15";
        //   }
        //   ImGui::End();
        //   //��ת���
        //   ImGui::Begin("game Window11", &game_window, window_flags);
        //   if (ImGui::ImageButton((ImTextureID*)texture_game_icon16, ImVec2(60, 36), ImVec2(0, 0), ImVec2(1, 1), 0)) {
        //       std::cout << "icon16";
        //   }
        //   ImGui::End();
        //    //�����λ���ж�
        //    glfwSetMouseButtonCallback(window, mouse_button_callback);
        //    camera.updateCameraVectors();
        //    // ��������
        //    handleKeyInput(window);
        //    glfwSetScrollCallback(window, scroll_callback);
        //    glfwSetCursorPosCallback(window, mouse_callback);
        //    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //    // �۲�ռ�
        //    glm::mat4 view = glm::mat4(1.0f);
        //    view = camera.GetViewMatrix();
        //    //ͶӰ
        //    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //    // ��������
        //    glm::mat4 model = glm::mat4(1.0f);
        //    //��ɫ
        //    glm::vec3 ambient = glm::vec3(1.0f);
        //    glm::vec3 diffuse = glm::vec3(1.0f);
        //    glm::vec3 specular = glm::vec3(1.0f);
        //    /*ImGui::Begin("Window", &game_window);
        //    ImGui::SliderFloat("������r", &transx, 0.0f, 0.2);
        //    ImGui::SliderFloat("������g", &transy, 0.0f, 0.2);
        //    ImGui::SliderFloat("������b", &transz, 0.0f, 0.2);
        //    ImGui::SliderFloat("������r", &transx1, 0.0f, 0.2);
        //    ImGui::SliderFloat("������g", &transy1, 0.0f, 0.2);
        //    ImGui::SliderFloat("������b", &transz1, 0.0f, 0.2);
        //    ImGui::SliderFloat("����r", &transx2, 0.0f, 0.2);
        //    ImGui::SliderFloat("����g", &transy2, 0.0f, 0.2);
        //    ImGui::SliderFloat("����b", &transz2, 0.0f, 0.2);
        //    ImGui::End();*/
        //    //ģ����Ⱦ
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
        //    // ��ԭ��Ȳ���
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