#include "imgui.h"

#include "imgui_impl_glfw.h"

#include "imgui_impl_opengl3.h"

#include <stdio.h>

#include<glad/glad.h> // Initialize with gladLoadGL()

#include <GLFW/glfw3.h>

#include<learnopengl/shader.h>
#include<learnopengl/camera.h>
#include <learnopengl/model.h>

#include<stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "functional.h"


int main(int, char**)
{
    GLFWwindow* window = windowInit();

    // Our state
    bool show_window = true;
    bool game_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    //深度测试
    glEnable(GL_DEPTH_TEST);


    //// 地面
    //Shader shaderGround("shader/vertexShaderSource.vs", "shader/fragmentShaderSource.fs");
    //unsigned int*param = textureLoader();
    //unsigned int VAO = param[0];
    //unsigned int VBO = param[1];
    //unsigned int EBO = param[2];
    //unsigned int texture1 = param[3];
    //unsigned int texture2 = param[4];

    //灯光
    Shader lightingShader("shader/1.colors.vs", "shader/1.colors.fs");
    Shader lightCubeShader("shader/1.light_cube.vs", "shader/1.light_cube.fs");
    unsigned int* param1 = lightTest();
    unsigned int cubeVAO = param1[0];
    unsigned int lightCubeVAO = param1[1];


    /*shaderGround.use();
    glUniform1i(glGetUniformLocation(shaderGround.ID, "texture1"), 1);
    glUniform1i(glGetUniformLocation(shaderGround.ID, "texture2"), 2);*/

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Poll and handle events (inputs, window resize, etc.)
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

        //开始界面
        if (show_window)
        {
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
            // 监听按键
            handleKeyInput(window);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            lightPos.x = 1.0f + sin(glfwGetTime()) * 3.0f;
            lightPos.y = sin(glfwGetTime() / 2.0f) * 3.0f;

            // view/projection transformations
            glm::mat4 view = glm::mat4(1.0f);
            //glm::mat4 projection = glm::mat4(1.0f);
            //projection = camera.GetProjMatrix((float)1280 / (float)720);
            view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // world transformation
            glm::mat4 model = glm::mat4(1.0f);

            ////地面贴图
            //glActiveTexture(GL_TEXTURE1);
            //glBindTexture(GL_TEXTURE_2D, texture1);
            //glActiveTexture(GL_TEXTURE2);
            //glBindTexture(GL_TEXTURE_2D, texture2);
            //shaderGround.use();
            //shaderGround.setMat4("projection", projection);
            //shaderGround.setMat4("view", view);
            //shaderGround.setMat4("model", model);
            ////render地面
            //glBindVertexArray(VAO);
            //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //render light and cube
            lightingShader.use();
            lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
            lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            lightingShader.setVec3("lightPos", lightPos);
            lightingShader.setVec3("viewPos", camera.Position);
            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            lightingShader.setMat4("model", model);
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            lightCubeShader.use();
            lightCubeShader.setMat4("projection", projection);
            lightCubeShader.setMat4("view", view);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            lightCubeShader.setMat4("model", model);

            glBindVertexArray(lightCubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);*/
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}