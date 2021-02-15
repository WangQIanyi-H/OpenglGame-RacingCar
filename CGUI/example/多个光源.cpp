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

    stbi_set_flip_vertically_on_load(true);
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
    Shader lightingShader("shader/light.vs", "shader/light.fs");
    Shader lightCubeShader("shader/lightCube.vs", "shader/lightCube.fs");
    unsigned int* param1 = lightTest();
    unsigned int cubeVAO = param1[0];
    unsigned int lightCubeVAO = param1[1];

    //Shader ourShader("shader/1.model_loading.vs", "shader/1.model_loading.fs");

    
    //载入模型
    //Model carModel("asset/models/obj/car/car.obj");

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

            lightingShader.setVec3("material.ambient", 0.24725f, 0.1995f, 0.0745f);
            lightingShader.setVec3("material.diffuse", 0.75164f, 0.60648f, 0.22648f);
            lightingShader.setVec3("material.specular", 0.628281f, 0.555802f, 0.366065f);
            lightingShader.setFloat("material.shininess", 0.4f);

            // directional light
            lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

            glm::vec3 pointLightPositions[] = {
                glm::vec3(0.7f,  0.2f,  2.0f),
                glm::vec3(2.3f, -3.3f, -4.0f),
                glm::vec3(-4.0f,  2.0f, -12.0f),
                glm::vec3(0.0f,  0.0f, -3.0f)
            };
            // point light 1
            lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
            lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("pointLights[0].constant", 1.0f);
            lightingShader.setFloat("pointLights[0].linear", 0.09);
            lightingShader.setFloat("pointLights[0].quadratic", 0.032);
            // point light 2
            lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
            lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("pointLights[1].constant", 1.0f);
            lightingShader.setFloat("pointLights[1].linear", 0.09);
            lightingShader.setFloat("pointLights[1].quadratic", 0.032);
            // point light 3
            lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
            lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("pointLights[2].constant", 1.0f);
            lightingShader.setFloat("pointLights[2].linear", 0.09);
            lightingShader.setFloat("pointLights[2].quadratic", 0.032);
            // point light 4
            lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
            lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("pointLights[3].constant", 1.0f);
            lightingShader.setFloat("pointLights[3].linear", 0.09);
            lightingShader.setFloat("pointLights[3].quadratic", 0.032);
            // spotLight
            lightingShader.setVec3("spotLight.position", camera.Position);
            lightingShader.setVec3("spotLight.direction", camera.Front);
            lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            lightingShader.setFloat("spotLight.constant", 1.0f);
            lightingShader.setFloat("spotLight.linear", 0.09);
            lightingShader.setFloat("spotLight.quadratic", 0.032);
            lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            lightingShader.setVec3("viewPos", camera.Position);
            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            glBindVertexArray(cubeVAO);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            glm::vec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f), 
                glm::vec3( 2.0f,  5.0f, -15.0f), 
                glm::vec3(-1.5f, -2.2f, -2.5f),  
                glm::vec3(-3.8f, -2.0f, -12.3f),  
                glm::vec3( 2.4f, -0.4f, -3.5f),  
                glm::vec3(-1.7f,  3.0f, -7.5f),  
                glm::vec3( 1.3f, -2.0f, -2.5f),  
                glm::vec3( 1.5f,  2.0f, -2.5f), 
                glm::vec3( 1.5f,  0.2f, -1.5f), 
                glm::vec3(-1.3f,  1.0f, -1.5f)  
};
            for (unsigned int i = 0; i < 10; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                lightingShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            lightCubeShader.use();
            lightCubeShader.setMat4("projection", projection);
            lightCubeShader.setMat4("view", view);
            //model = glm::mat4(1.0f);
            //model = glm::translate(model, lightPos);
            //model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            //lightCubeShader.setMat4("model", model);
            glBindVertexArray(lightCubeVAO);
            //glDrawArrays(GL_TRIANGLES, 0, 36);

            for (unsigned int i = 0; i < 4; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                lightCubeShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }


            //render car
            /*ourShader.use();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);
            ourShader.setMat4("model", model);
            carModel.Draw(ourShader);*/


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