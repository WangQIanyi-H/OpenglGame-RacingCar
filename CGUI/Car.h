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
    CAR_RIGHT,
    CAR_BRAKE,
    CAR_ACCELERATION
};

class Car {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    float Yaw;

    // 存储旧Yaw信息，实现漂移
    queue<float> HistoryYaw;
    int DelayFrameNum = 20;
    float DelayYaw;

    // 实现汽车缓动与缓停
    // TODO 设置一个speed属性，接收按键后根据deltatime不断增加或减小speed至阈值以实现缓动更加合适（而不是使用现在的奇怪的方法）（相机的Yaw偏移也相同）
    queue<glm::vec3> HistoryPosition;
    glm::vec3 DelayPosition;

    //挡位
    bool D = false;//drive
    bool P = true;
    bool R = false;//reverse
    bool N = false;

    //加油log
    bool acceleration = false;
    
    //刹车x²
    bool brake = false;
    bool safety_belt = false;         //--------安全带
    bool parkBrake = true;            //--------手刹
    bool leftLight = false;           //--------左转向灯
    bool rightLight = false;          //--------右转向灯

    float MovementSpeed;
    float DSpeed = 0.7f;
    float TurningSpeed;


    Car(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
        : MovementSpeed(0.0f)
        , TurningSpeed(60.0f)
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

    void switchTo(string gear)
    {
        if (gear=="P")
        {
            P = true;
            R = false;
            N = false;
            D = false;
        }
        else if (gear == "R")
        {
            P = false;
            R = true;
            N = false;
            D = false;
        }
        else if (gear == "N")
        {
            P = false;
            R = false;
            N = true;
            D = false;
        }
        else if (gear == "D")
        {
            P = false;
            R = false;
            N = false;
            D = true;
        }
    }

    void run(float deltaTime)
    {
        if (D == true && parkBrake == false)
        {
            if (MovementSpeed <= DSpeed && !brake)
            {
                MovementSpeed += 0.09f;
            }
            Position -= Front * MovementSpeed * deltaTime;
        }
    }

    // 接受键盘输入
    void ProcessKeyboard(Direction direction, float deltaTime)
    {
        if (D == true && parkBrake == false)
        {
            if (direction == CAR_FORWARD)
            {
                acceleration = true;
                MovementSpeed += 0.11f;
            }
            if (direction == CAR_BACKWARD)
            {
                brake = true;
                if (MovementSpeed <= 0)
                {
                    MovementSpeed = 0;
                }
                else if(MovementSpeed >= 0.42f)
                {
                    MovementSpeed -= 0.42f;
                }
                else if (MovementSpeed <= 0.42f)
                {
                    MovementSpeed -= MovementSpeed;
                }
            }
            if(direction == CAR_BRAKE)
                brake = false;
            if (direction == CAR_ACCELERATION)
                acceleration = false;
        }
        if (direction == CAR_LEFT && (MovementSpeed < -0.05f || MovementSpeed > 0.05f))
        {
            Yaw += TurningSpeed * deltaTime;
        }
        if (direction == CAR_RIGHT && (MovementSpeed < -0.05f || MovementSpeed > 0.05f))
        {
            Yaw -= TurningSpeed * deltaTime;
        }
        updateFront();
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

    // 计算新的 Front 向量
    void updateFront()
    {
        glm::vec3 front;
        front.x = -sin(glm::radians(getYaw()));
        front.y = 0.0f;
        front.z = -cos(glm::radians(getYaw()));
        Front = glm::normalize(front);
    }
};

#endif