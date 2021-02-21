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




int main(int, char**)
{
    GLFWwindow* window = windowInit();

    //初始设置
    bool show_window = true;
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
    Model treeModel("asset/models/trees/trees.obj");

    std::cout << "读取street模型中......" << endl;
    Model streetModel("asset/models/street/street.obj");

    std::cout << "读取buildings模型中......" << endl;
    Model houseModel("asset/models/buildings/buildings.obj");

    std::cout << "读取others模型中......" << endl;
    Model othersModel("asset/models/others/others.obj");

    std::cout << "读取car模型中......" << endl;
    Model carModel("asset/models/car1/car1.obj");


    std::cout << "模型读取完毕" << endl;

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

    //贴图
    Shader shaderImage("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image = imageLoader(1);
    unsigned int VAO_image = param_image[0];
    unsigned int texture_image = param_image[2];

    Shader shaderImage2("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param_image2 = imageLoader(2);
    unsigned int VAO_image2 = param_image2[0];
    unsigned int texture_image2 = param_image2[2];

    //背景界面
    Shader shaderGround("shader/vertexShaderSource1.vs", "shader/fragmentShaderSource1.fs");
    unsigned int* param = textureLoader();
    unsigned int VAO = param[0];
    unsigned int texture1 = param[3];

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


        shaderImage.use();
        //贴图1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_image);
        glUniform1i(glGetUniformLocation(shaderImage.ID, "texture2"), 1);

        shaderImage2.use();
        //贴图2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture_image2);
        glUniform1i(glGetUniformLocation(shaderImage2.ID, "texture2"), 2);

        shaderGround.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1); 
        glUniform1i(glGetUniformLocation(shaderGround.ID, "texture1"), 0);
        

        //图标
      
    
    /*  Shader shadeIcon1("shader/vertexShaderSource2.vs", "shader/fragmentShaderSource2.fs");
        unsigned int* param1 = iconLoader1();
        unsigned int VAO1 = param1[0];
        unsigned int VAO2 = param1[1];
        shadeIcon1.use()*/;

       


        //开始界面
        if (show_window)
        {
            glDepthFunc(GL_LEQUAL);
            //背景图片
            shaderGround.use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            static bool no_titlebar = true;
            static bool no_scrollbar = true;
            static bool no_menu = true;
            static bool no_move = true;
            static bool no_resize = true;
            static bool no_collapse = false;
            static bool no_close = true;
            static bool no_nav = false;
            static bool no_background = true;
            static bool no_bring_to_front = false;
            ImGuiWindowFlags window_flags = 0;
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
            if (ImGui::ImageButton((ImTextureID*)texture_image, ImVec2(271, 87), ImVec2(0, 0), ImVec2(1, 1), 0))
            {
                game_window = true;
                show_window = false;

            }
            ImGui::Text("\n\n");
            if (ImGui::ImageButton((ImTextureID*)texture_image2, ImVec2(271, 87), ImVec2(0, 0), ImVec2(1, 1), 0))
            {

            }
            ImGui::End();
            
            glDepthFunc(GL_LESS);
        }

        //游戏界面
        if (game_window) {

            //ICON1
            shaderImage.use();
            glBindVertexArray(VAO_image);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //ICON2
            shaderImage2.use();
            glBindVertexArray(VAO_image2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
           

            /*shadeIcon1.use();
            glBindVertexArray(VAO1); 
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);*/

            //鼠标点击位置判断
            glfwSetMouseButtonCallback(window, mouse_button_callback);


            /*camera.Pitch = -18.9f;
            camera.Position = glm::vec3(5.2f, 0.7f, 0.33f);*/
            camera.updateCameraVectors();

            // 监听按键
            handleKeyInput(window);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // 观察空间
            glm::mat4 view = glm::mat4(1.0f);
            view = camera.GetViewMatrix();

            //投影
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // 世界坐标
            glm::mat4 model = glm::mat4(1.0f);

            //颜色
            glm::vec3 ambient = glm::vec3(1.0f);
            glm::vec3 diffuse = glm::vec3(1.0f);
            glm::vec3 specular = glm::vec3(1.0f);

            /*ImGui::Begin("Window", &game_window);
            ImGui::SliderFloat("环境光r", &transx, 0.0f, 0.2);
            ImGui::SliderFloat("环境光g", &transy, 0.0f, 0.2);
            ImGui::SliderFloat("环境光b", &transz, 0.0f, 0.2);
            ImGui::SliderFloat("漫反射r", &transx1, 0.0f, 0.2);
            ImGui::SliderFloat("漫反射g", &transy1, 0.0f, 0.2);
            ImGui::SliderFloat("漫反射b", &transz1, 0.0f, 0.2);
            ImGui::SliderFloat("镜面r", &transx2, 0.0f, 0.2);
            ImGui::SliderFloat("镜面g", &transy2, 0.0f, 0.2);
            ImGui::SliderFloat("镜面b", &transz2, 0.0f, 0.2);


            ImGui::End();*/

            //模型渲染
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
            shaderM.setMat4("model", model);
            carModel.Draw(shaderM);

            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            renderSkyBox(skyboxShader);
            // 复原深度测试
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