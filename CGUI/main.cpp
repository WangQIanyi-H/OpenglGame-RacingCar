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

        //背景界面
        Shader shaderGround("shader/vertexShaderSource.vs", "shader/fragmentShaderSource.fs");
        unsigned int* param = textureLoader();
        unsigned int VAO = param[0];
        unsigned int texture1 = param[3];
        shaderGround.use();
        glUniform1i(glGetUniformLocation(shaderGround.ID, "texture1"), 0);

        //贴图
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        //开始界面
        if (show_window)
        {
            shaderGround.use();
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -7.0f, -15.0f));
            model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 0.57f, 0.0f));
            shaderGround.setMat4("projection", projection);
            shaderGround.setMat4("view", view);
            shaderGround.setMat4("model", model);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            ImGui::Begin("Another Window", &show_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Game")) {
                game_window = true;
                show_window = false;
            }
            ImGui::End();
            
        }

        //游戏界面
        if (game_window) {

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