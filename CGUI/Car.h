#ifndef CAR_H
#define CAR_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<iostream>
#include <queue>
using namespace std;

// 定义汽车移动的几个可能的选项
enum Direction {
    CAR_FORWARD,
    CAR_BACKWARD,
    CAR_LEFT,
    CAR_RIGHT
};

class Car {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    float Yaw;

    //是否缓停
    bool speeddelta = false;

    // 存储旧Yaw信息，实现漂移
    queue<float> HistoryYaw;
    int DelayFrameNum = 20;
    float DelayYaw;

    // 实现汽车缓动与缓停
    // TODO 设置一个speed属性，接收按键后根据deltatime不断增加或减小speed至阈值以实现缓动更加合适（而不是使用现在的奇怪的方法）（相机的Yaw偏移也相同）
    queue<glm::vec3> HistoryPosition;
    glm::vec3 DelayPosition;

    float movementSpeed;
    float TurningSpeed;

    Car(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
        : movementSpeed(0.0f)
        , TurningSpeed(90.0f)
        , Yaw(0.0f)
        , DelayYaw(0.0f)
    {
        Position = position;
        updateFront();
    }

    glm::vec3 getPosition()
    {
        return Position;
    }

    float getYaw()
    {
        return Yaw;
    }

    float getDelayYaw()
    {
        return DelayYaw;
    }

    float getYawDif()
    {
        return Yaw - DelayYaw;
    }

    float getMidValYaw()
    {
        return (DelayYaw + Yaw) / 2;
    }

    glm::vec3 getMidValPosition()
    {
        return (DelayPosition + Position) / 2.0f;
    }

    // 计算视图矩阵
    glm::mat4 GetViewMatrix(glm::vec3 cameraPosition)
    {
        return glm::lookAt(cameraPosition, Position, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // 接受键盘输入
    void ProcessKeyboard(Direction direction, float deltaTime)
    {
        if (direction == CAR_FORWARD) {
            if (movementSpeed <= 30)//如果车速小于五，则加速
            {
                movementSpeed += 0.1;
                Position += Front * movementSpeed * deltaTime;
            }
            else if (movementSpeed > 30.0)//如果车速大于30，则匀速
            {
                Position += Front * movementSpeed * deltaTime;
            }
        }
        if (direction == CAR_BACKWARD)
            Position -= Front * movementSpeed * deltaTime;
        if (direction == CAR_LEFT)
            Yaw += TurningSpeed * deltaTime;
        if (direction == CAR_RIGHT)
            Yaw -= TurningSpeed * deltaTime;
        updateFront();
    }

    void updateSpeed(float deltaTime) {
        if (speeddelta) {
            if (movementSpeed > 0.1) {
                movementSpeed -= 0.1;
                Position += Front * movementSpeed * deltaTime;
            }
            if (movementSpeed <= 0.1) {
                movementSpeed = 0;
                speeddelta = false;
            }
        }
    }

    // 更新DalayYaw
    void UpdateDelayYaw()
    {
        HistoryYaw.push(Yaw);
        while (HistoryYaw.size() > DelayFrameNum) {
            HistoryYaw.pop();
        }
        DelayYaw = HistoryYaw.front();
    }

    // 更新DalayYaw
    void UpdateDelayPosition()
    {
        HistoryPosition.push(Position);
        while (HistoryPosition.size() > DelayFrameNum) {
            HistoryPosition.pop();
        }
        DelayPosition = HistoryPosition.front();
    }

private:
    // 计算新的 Front 向量
    void updateFront()
    {
        glm::vec3 front;
        front.x = -sin(glm::radians(getMidValYaw()));
        front.y = 0.0f;
        front.z = -cos(glm::radians(getMidValYaw()));
        Front = glm::normalize(front);
    }
};

#endif