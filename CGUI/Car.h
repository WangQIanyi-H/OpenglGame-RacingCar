#ifndef CAR_H
#define CAR_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<iostream>
#include <queue>
using namespace std;

// ���������ƶ��ļ������ܵ�ѡ��
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

    //�Ƿ�ͣ
    bool speeddelta = false;

    // �洢��Yaw��Ϣ��ʵ��Ư��
    queue<float> HistoryYaw;
    int DelayFrameNum = 20;
    float DelayYaw;

    // ʵ�����������뻺ͣ
    // TODO ����һ��speed���ԣ����հ��������deltatime�������ӻ��Сspeed����ֵ��ʵ�ֻ������Ӻ��ʣ�������ʹ�����ڵ���ֵķ������������Yawƫ��Ҳ��ͬ��
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

    // ������ͼ����
    glm::mat4 GetViewMatrix(glm::vec3 cameraPosition)
    {
        return glm::lookAt(cameraPosition, Position, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // ���ܼ�������
    void ProcessKeyboard(Direction direction, float deltaTime)
    {
        if (direction == CAR_FORWARD) {
            if (movementSpeed <= 30)//�������С���壬�����
            {
                movementSpeed += 0.1;
                Position += Front * movementSpeed * deltaTime;
            }
            else if (movementSpeed > 30.0)//������ٴ���30��������
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

    // ����DalayYaw
    void UpdateDelayYaw()
    {
        HistoryYaw.push(Yaw);
        while (HistoryYaw.size() > DelayFrameNum) {
            HistoryYaw.pop();
        }
        DelayYaw = HistoryYaw.front();
    }

    // ����DalayYaw
    void UpdateDelayPosition()
    {
        HistoryPosition.push(Position);
        while (HistoryPosition.size() > DelayFrameNum) {
            HistoryPosition.pop();
        }
        DelayPosition = HistoryPosition.front();
    }

private:
    // �����µ� Front ����
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