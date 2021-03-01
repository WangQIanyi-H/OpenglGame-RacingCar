#pragma once

#include<glad\glad.h>
#include<iostream>

struct point_f {
    float x;
    float y;
    point_f() {
        x = 0.0f;
        y = 0.0f;
    }
    point_f(float a, float b) {
        x = a;
        y = b;
    }
};

//���� | p1 p2 | X | p1 p3 |
float GetCross(point_f p1, point_f p3, point_f p2) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
//�жϵ�p�Ƿ���p1p2p3p4����������
//�ж�p���Ƿ��ھ��������ڲ�
bool IS_IN_AREA(point_f click, point_f rect[4]) {
    if (GetCross(rect[0], rect[1], click) * GetCross(rect[2], rect[3], click) >= 0
        && GetCross(rect[1], rect[2], click) * GetCross(rect[3], rect[0], click) >= 0)
        return true;
    else {
        return false;
    }
}

//-------------------------------------------------------------------1.��
struct Start {
	bool Session = false;//ϵ��ȫ��
    //����ת��ƣ���D��������ɲ��
    bool Session1 = false;
    bool Session2 = false;
    bool Session3 = false;
    int Score() {
        return (int)(Session3) * 100;
    }
};
Start start;

//-------------------------------------------------------------------2.·��ֱ��
struct CrossingStraight {
    //��ɲ��,��ֱ��
    bool Session1 = false;
    bool Session2 = false;
    point_f Area1[4] = {
        point_f(-0.6f, 7.0f),
        point_f(-0.6f, 2.0f),
        point_f(1.2f, 2.0f),
        point_f(1.2f, 7.0f),
    };
    point_f Area2[4] = {
        point_f(-0.6f, 17.0f),
        point_f(-0.6f, 7.0f),
        point_f(1.2f, 7.0f),
        point_f(1.2f, 17.0f),
    };
    int Score() {
        return (int)(Session2) * 100;
    }
};
CrossingStraight crossingStraight;

//-------------------------------------------------------------------3.ֱ����ʻ
struct GoStraight {
    bool Session=false;
    point_f Area[4] = {
        point_f(-0.6f, 27.0f),
        point_f(-0.6f, 17.0f),
        point_f(1.2f, 17.0f),
        point_f(1.2f, 27.0f),
    };
    int Score() {
        return (int)(Session )* 100;
    }
};
GoStraight goStraight;

//--------------------------------------------------------------------4.�ᳵ
struct GiveWay {
    //ɲ��
    bool Session1 = false;
    point_f Area1[4] = {
        point_f(-0.6f, 48.0f),
        point_f(-0.6f, 30.0f),
        point_f(1.2f, 30.0f),
        point_f(1.2f, 48.0f),
    };
    int Score() {
        return (int)(Session1) * 100;
    }
};
GiveWay giveWay;

//--------------------------------------------------------------------5.��ת��
struct TurnLeft {
    //��ǰ������ת��ƣ�·��������ǰ��һ��ɲ������Ҫת��·���ĵ��Ǹ�������

    //������ת��ƣ�
    bool Session1 = false;
    //������ǰ��ɲ����
    bool Session2 = false;
    //ȷ��ת��·���ĵĳ�����
    bool Session3 = false;

    //������ת��ƣ�
    point_f Area1[4] = {
        point_f(-0.6f, 54.0f),
        point_f(-0.6f, 48.0f),
        point_f(1.2f, 48.0f),
        point_f(1.2f, 54.0f),
    };
    //������ǰ��ɲ����
    point_f Area2[4] = {
        point_f(-0.6f, 59.0f),
        point_f(-0.6f, 54.0f),
        point_f(1.2f, 54.0f),
        point_f(1.2f, 59.0f),
    };
    //ȷ���������ڿ���դ���ĳ�����
    point_f Area3[4] = {
        point_f(4.9f, 65.5f),
        point_f(4.9f, 64.7f),
        point_f(6.6f, 64.7f),
        point_f(6.6f, 65.5f),
    };
    int Score() {
        return (int)(Session3) * 100;
    }
};
TurnLeft turnleft;

//--------------------------------------------------------------------6.·��ѧУ
struct PassingSchool {
    //ɲ��
    bool Session1 = false;
    point_f Area1[4] = {
        point_f(6.0f, 66.9f),
        point_f(6.0f, 64.8f),
        point_f(15.0f, 64.8f),
        point_f(15.0f, 66.9f),
    };
    int Score() {
        return (int)(Session1) * 100;
    }
};
PassingSchool passingSchool;

//---------------------------------------------------------------------7.��ͷ
struct UTurn {
    //��ת���
    bool Session1 = false;
    //�ٶȽ���ʮ��ɲ���ɵ�
    bool Session2 = false;
    point_f Area1[4] = {
       point_f(19.0f, 66.9f),
       point_f(19.0f, 65.1f),
       point_f(25.0f, 65.1f),
       point_f(25.0f, 66.9f),
    };
    point_f Area2[4] = {
       point_f(30.0f, 63.6f),
       point_f(30.0f, 62.4f),
       point_f(23.0f, 62.4f),
       point_f(23.0f, 63.6f),
    };
	int Score() {
		return (int)Session2 *100;
	}


};
UTurn uTurn;
//---------------------------------------------------------------------8.����
struct Overtake {

    int changeNumber = 0;
    int lane1 = 0;
    int lane2 = 0;
    int lane3 = 0;

    //����ת���
    bool Session1 = false;
    //����������
    bool Session2 = false;
    //����ת���
    bool Session3 = false;
    //�����ҳ���
    bool Session4 = false;

    point_f Area1[4] = {
        point_f(10.0f, 64.8f),
        point_f(10.0f, 64.2f),
        point_f(20.0f, 64.2f),
        point_f(20.0f, 64.8f),
    };
    point_f Area2[4] = {
        point_f(10.0f, 64.2f),
        point_f(10.0f, 63.6f),
        point_f(20.0f, 63.6f),
        point_f(20.0f, 64.2f),
    };
    point_f Area3[4] = {
        point_f(10.0f, 63.6f),
        point_f(10.0f, 63.0f),
        point_f(20.0f, 63.0f),
        point_f(20.0f, 63.6f),
    };
    point_f Area4[4] = {
        point_f(10.0f, 63.0f),
        point_f(10.0f, 62.4f),
        point_f(20.0f, 62.4f),
        point_f(20.0f, 63.0f),
    };
    int detect(point_f p) {
        if (IS_IN_AREA(p, Area1))return 1;
        if (IS_IN_AREA(p, Area2))return 2;
        if (IS_IN_AREA(p, Area3))return 3;
        if (IS_IN_AREA(p, Area4))return 4;
    }
    int Score() {
        return (int)Session4 * 100;
    }
};
Overtake overTake;
//-------------------------------------------------------------------9.����ת
struct TurnRight {
	//������ת��ƣ�
	bool Session1 = false;
	//������ǰ��ɲ����
	bool Session2 = false;
	//ȷ��ת��·���ĵĳ�����
	bool Session3 = false;

	//������ת��ƣ�
	point_f Area1[4] = {
		point_f(14.7f, 64.5f),
		point_f(14.7f, 62.7f),
		point_f(7.0f, 62.7f),
		point_f(7.0f, 64.5f),
	};

	//������ǰ��ɲ����
	point_f Area2[4] = {
		point_f(8.6f, 64.5f),
		point_f(8.6f, 62.7f),
		point_f(6.4f, 62.7f),
		point_f(6.4f, 64.5f),
	};
	//ȷ���������ڿ���դ���ĳ�����
	point_f Area3[4] = {
		point_f(3.2f, 61.5f),
		point_f(3.2f, 56.0f),
		point_f(4.0f, 56.0f),
		point_f(4.0f, 61.5f),
	};
	int Score() {
		return (int)Session3 * 100;
	}
};
TurnRight turnright;

//--------------------------------------------------------------------10.�������
struct MoveLane {
    bool Session1 = false;
    bool Session2 = false;
    int changeNumber = 0;
    int lane1 = 0;
    point_f Area1[4] = {
        point_f(1.5f, 56.0f),
        point_f(1.5f, 46.0f),
        point_f(2.1f, 46.0f),
        point_f(2.1f, 56.0f),
    };
    point_f Area2[4] = {
        point_f(2.1f, 56.0f),
        point_f(2.1f, 46.0f),
        point_f(2.7f, 46.0f),
        point_f(2.7f, 56.0f),
    };
    point_f Area3[4] = {
        point_f(2.7f, 56.0f),
        point_f(2.7f, 46.0f),
        point_f(3.3f, 46.0f),
        point_f(3.3f, 56.0f),
    };
    point_f Area4[4] = {
        point_f(3.3f, 56.0f),
        point_f(3.3f, 46.0f),
        point_f(3.9f, 46.0f),
        point_f(3.9f, 56.0f),
    };
    int detect(point_f p) {
        if (IS_IN_AREA(p, Area1))return 1;
        if (IS_IN_AREA(p, Area2))return 2;
        if (IS_IN_AREA(p, Area3))return 3;
        if (IS_IN_AREA(p, Area4))return 4;
    }
    int Score() {
		return (int)Session2 * 100 ;
	}
};
MoveLane moveLane;


//------------------------------------------------------------------11.·��������վ
struct PassingBusStop {
    //ɲ��
    bool Session1 = false;
    point_f Area[4] = {
         point_f(1.7f,25.85f),
         point_f(1.7f,35.0f),
         point_f(3.8f,35.0f),
         point_f(3.8f,25.85f),
    };
    int Score() {
        return (int)Session1 * 100;
    }
};
PassingBusStop passingBusStop;

//--------------------------------------------------------------------12.����ͣ�� 
struct PullOver {
    bool Session1 = false;//ת���
    bool Session2 = false;//�ٶ�Ϊ��
    bool Session3 = false;//��λP
    bool Session4 = false;//��ɲ
    bool Session = false;
    point_f Area[4] = {
        point_f(2.4f, 10.0f),
        point_f(2.4f, -4.4f),
        point_f(3.6f, -4.4f),
        point_f(3.6f, 10.0f),
    };
	int Score() {
		return (int)Session4 * 100;
	}

};
PullOver pullOver;

//===============��¼�ܷ�=================
int ScoreSum()
{
	int sum = 100;//�ܷ���Ϊ100���۵ķ�������100�˾���Ϊ0������Ŀ��
	sum = 100-(start.Score() + crossingStraight.Score() + goStraight.Score() + giveWay.Score() + turnleft.Score() + passingSchool.Score() +
		uTurn.Score() + overTake.Score() + moveLane.Score() + turnright.Score() + passingBusStop.Score() + pullOver.Score());
	//if (sum < 0) return 0;
	return sum;
}


//===============��¼ÿ���������=================

bool isMoving = false;            //--------Ĭ�ϳ�û������ʻ
int automatic = 1;                //--------�Զ�����λ
bool Map = false;                 //--------��ͼĬ�ϲ���ʾ
int switchView = 0;

//===============��¼ÿ�����ڵ�������==============

//bool CrossingStraight = false;    //·��ֱ��
//bool GoStraight = false;          //ֱ����ʻ
//bool GiveWay = false;             //�ᳵ
//bool TurnLeft = false;            //��ת��
//bool PassingSchool = false;       //·��ѧУ
//bool UTurn = false;               //��ͷ
//bool Overtake = false;            //����
//bool MoveLane = false;            //�������
//bool PassingBusStop = false;      //·��������վ
//bool PullOver = false;            //����ͣ��



//ȫ�ֱ���������갴��ʱ��λ��
point_f mouse_pos;
point_f car_pos;
//�Ż�����������points[4]����ʾ10����������
point_f Area1_1[4] = {
    point_f(-0.6f, 6.2f),
    point_f(-0.6f, 1.2f),
    point_f(1.2f, 1.2f),
    point_f(1.2f, 6.2f),
};
point_f Area1_2[4] = {
    point_f(-0.6f, 22.0f),
    point_f(-0.6f, 18.0f),
    point_f(1.2f, 18.0f),
    point_f(1.2f, 22.0f),
};
point_f Area1_3[4] = {
    point_f(-0.6f, 34.0f),
    point_f(-0.6f, 30.0f),
    point_f(1.2f, 30.0f),
    point_f(1.2f, 34.0f),
};
point_f Area1_4[4] = {
    point_f(-0.6f, 56.0f),
    point_f(-0.6f, 48.0f),
    point_f(1.2f, 48.0f),
    point_f(1.2f, 56.0f),
};
point_f Area2_1[4] = {//·��ѧУ
    point_f(5.8f, 66.9f),
    point_f(5.8f, 65.1f),
    point_f(11.0f, 65.1f),
    point_f(11.0f, 66.9f),
};
point_f Area2_2[4] = {//��ͷ
    point_f(17.0f, 66.9f),
    point_f(17.0f, 65.1f),
    point_f(25.0f, 65.1f),
    point_f(25.0f, 66.9f),
};
point_f Area2_3[4] = {//����
    point_f(10.0f, 64.5f),
    point_f(10.0f, 62.7f),
    point_f(20.0f, 62.7f),
    point_f(20.0f, 64.5f),
};
point_f Area2_4[4] = {
    point_f(15.0f, 64.5f),
    point_f(15.0f, 62.7f),
    point_f(10.0f, 62.7f),
    point_f(10.0f, 64.5f),
};
point_f Area3_1[4] = {
    point_f(1.8f, 56.0f),
    point_f(1.8f, 46.0f),
    point_f(3.6f, 46.0f),
    point_f(3.6f, 56.0f),
};
point_f Area3_2[4] = {
    point_f(1.8f, 35.0f),
    point_f(1.8f, 30.0f),
    point_f(3.6f, 30.0f),
    point_f(3.6f, 35.0f),
};
point_f Area3_3[4] = {//����ͣ��
    point_f(1.8f, 10.0f),
    point_f(1.8f, 0.0f),
    point_f(3.6f, 0.0f),
    point_f(3.6f, 10.0f),
};

//�����ܾ���
point_f Area_W[4] = {
    point_f(36.0f, 67.2f),
    point_f(4.2f, 67.2f),
    point_f(4.2f, 62.4f),
    point_f(36.0f, 62.4f),
};
//�����ܾ���
point_f Area_H[4] = {
    point_f(4.2f,67.2f),
    point_f(-0.9f,67.2f),
    point_f(-0.9f,-4.4f),
    point_f(4.2f,-4.4f),
};



//ȫ�ֱ���
//���ڷֱ���
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
// ��Ⱦ��Ӱʱ�Ĵ��ڷֱ��ʣ���Ӱ����Ӱ�ľ�ݱ������
const unsigned int SHADOW_WIDTH = 1024 * 10;
const unsigned int SHADOW_HEIGHT = 1024 * 10;
// �Ƿ�Ϊ�߿�ͼģʽ
bool isPolygonMode = false;
// ��������ϵY�ᵥλ����
glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);
// timing ����ƽ�ⲻͬ������Ⱦˮƽ���������ٶȱ仯
float deltaTime = 0.0f;
float lastFrame = 0.0f;
//�����
//Camera camera(glm::vec3(4.0f, 10.0f, 1.5f));
Camera camera(glm::vec3(0.0f, 15.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//car
glm::vec3 carPos = glm::vec3(0.0f, 0.0f, 0.0f);
Car car(carPos);

//�ƹ�
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
// ��պ�
unsigned int cubemapTexture;
unsigned int skyboxVAO, skyboxVBO;
// ��պж�������
const float skyboxVertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};
// ��պе�������
//const vector<std::string> faces{
//    "asset/textures/skybox/right.tga",
//    "asset/textures/skybox/left.tga",
//    "asset/textures/skybox/top.tga",
//    "asset/textures/skybox/bottom.tga",
//    "asset/textures/skybox/front.tga",
//    "asset/textures/skybox/back.tga"
//};
//const vector<std::string> faces{
//    "asset/textures/5/rainbow_rt.png",
//    "asset/textures/5/rainbow_lf.png",
//    "asset/textures/5/rainbow_up.png",
//    "asset/textures/5/rainbow_dn.png",
//    "asset/textures/5/rainbow_ft.png",
//    "asset/textures/5/rainbow_bk.png"
//};
const vector<std::string> faces
{
    "asset/textures/13/right.tga",
    "asset/textures/13/left.tga",
    "asset/textures/13/top.tga",
    "asset/textures/13/bottom.tga",
    "asset/textures/13/front.tga",
    "asset/textures/13/back.tga"
};


// �������������Ϊһ��cubemap����
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void skyboxInit()
{
    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // �������
    cubemapTexture = loadCubemap(faces);
}

void renderSkyBox(Shader& shader)
{
    // viewMatrix ͨ�����죬�Ƴ�������ƶ�
    glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    // ͶӰ
    glm::mat4 projMatrix = camera.GetProjMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);

    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", projMatrix);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        switchView = abs(switchView - 1);
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        isPolygonMode = !isPolygonMode;
        if (isPolygonMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        string info = isPolygonMode ? "�л�Ϊ�߿�ͼ��Ⱦģʽ" : "�л�Ϊ������Ⱦģʽ";
        std::cout << "[POLYGON_MODE]" << info << std::endl;
    }
}

void handleKeyInput(GLFWwindow* window)
{
    // esc�˳�
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //���������
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)// && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)// && (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    //����
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        car.ProcessKeyboard(CAR_FORWARD, deltaTime);
    //�ɿ�����
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
        car.ProcessKeyboard(CAR_ACCELERATION, deltaTime);
    //ɲ��
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        car.ProcessKeyboard(CAR_BACKWARD, deltaTime);
    //�ɿ�ɲ��
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
        car.ProcessKeyboard(CAR_BRAKE, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )//&& (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        car.ProcessKeyboard(CAR_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )//&& (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
        car.ProcessKeyboard(CAR_RIGHT, deltaTime);
    // �ص�����������һ������ֻ�ᴥ��һ���¼���
    glfwSetKeyCallback(window, key_callback);
}


//ת�������ʱ�Ķ�ά����ϵ
void turn_to_view(double& a, double& b) {
    point_f point;

    point.x = a - SCR_WIDTH / 2;
    point.y = SCR_HEIGHT / 2 - b;
    a = point.x / (SCR_WIDTH / 2);
    b = point.y / (SCR_HEIGHT / 2);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}






// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void setDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

//���ڳ�ʼ��
GLFWwindow* windowInit() {
    //setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return NULL;

    // GL 3.0 + GLSL 330 core ����
    const char* glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ��������
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return NULL;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //��ʼ�� OpenGL loader
    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ����ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}

unsigned int* mainBackgroundLoader()
{
      //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/menu/����24.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1};
    return param;
}
unsigned int* ruleBackgroundLoader()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data =  stbi_load("asset/image/rule/rule.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}
unsigned int* pauseBackgroundLoader()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/pause/pause.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}
unsigned int* setBackgroundLoader()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/set/����.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}

//���������������
unsigned int* scoreBackgroundLoader1()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/score/������������.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}
//δͨ��
unsigned int* scoreBackgroundLoader2()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/score/δͨ��.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}
//ͨ��
unsigned int* scoreBackgroundLoader3()
{
    //������ͼ��ʹ������任
    float vertices[] = {
        //     ---- λ�� ----   -------color------   - �������� -
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
            1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 1.0f, 1.0f,
           -1.0f,  1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f,  0.0f,0.0f,0.0f, 0.0f, 0.0f,
    };

    int indices[] = {
        0,1,2,3,4,5
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("asset/image/score/ͨ��.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, EBO, texture1 };
    return param;
}





unsigned int* main_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/main/begin.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/main/rule.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/main/set.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/main/quit.png", &width, &height, &nrChannels, 0);
        break;
    }    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* rule_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/rule/back.png", &width, &height, &nrChannels, 0);
        break;
    case 2://�ɼ����ķ������˵���ť
        data = stbi_load("asset/image/main/quit.png", &width, &height, &nrChannels, 0);
        break;
    case 3://��ͣ����ķ������˵�
        data = stbi_load("asset/image/pause/back.png", &width, &height, &nrChannels, 0);
        break;
    case 4://���ý���ķ������˵�
        data = stbi_load("asset/image/set/����.png", &width, &height, &nrChannels, 0);
        break;
    }

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* game_icon_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 1:
        data = stbi_load("asset/image/game/��ȫ��.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/game/��ͼ.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/game/�ӽ�.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/game/��ͣ.png", &width, &height, &nrChannels, 0);
        break;
    case 5:
        data = stbi_load("asset/image/game/����.png", &width, &height, &nrChannels, 0);
        break;
    case 6:
        data = stbi_load("asset/image/game/ɲ��.png", &width, &height, &nrChannels, 0);
        break;
    case 7:
        data = stbi_load("asset/image/game/��ɲ.png", &width, &height, &nrChannels, 0);
        break;
    case 8:
        data = stbi_load("asset/image/game/Σ�վ�ʾ��.png", &width, &height, &nrChannels, 0);
        break;
    case 9:
        data = stbi_load("asset/image/game/������.png", &width, &height, &nrChannels, 0);
        break;
    case 10:
        data = stbi_load("asset/image/game/�ٶ���ʾ��.png", &width, &height, &nrChannels, 0);
        break;
    case 11:
        data = stbi_load("asset/image/game/�Զ���p.png", &width, &height, &nrChannels, 0);
        break;
    case 12:
        data = stbi_load("asset/image/game/�Զ���r.png", &width, &height, &nrChannels, 0);
        break;  
    case 13:
        data = stbi_load("asset/image/game/�Զ���n.png", &width, &height, &nrChannels, 0);
        break;
    case 14:
        data = stbi_load("asset/image/game/�Զ���d.png", &width, &height, &nrChannels, 0);
        break;
    case 15:
        data = stbi_load("asset/image/game/��ת���.png", &width, &height, &nrChannels, 0);
        break;
    case 16:
        data = stbi_load("asset/image/game/��ת���.png", &width, &height, &nrChannels, 0);
        break;
    case 17:
        data = stbi_load("asset/image/game/��ȫ��1.png", &width, &height, &nrChannels, 0);
        break;
    case 18:
        data = stbi_load("asset/image/game/��ɲ1.png", &width, &height, &nrChannels, 0);
        break;
    case 19:
        data = stbi_load("asset/image/game/��ͼ����.png", &width, &height, &nrChannels, 0);
        break;
   
    }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}
unsigned int* tips_Loader(int index)
{
    float vertices1[] = {
        // positions        //color               // texture coords
         0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f, 1.0f,1.0f,1.0f, 0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = 0;
    switch (index) {
    case 0:
        data = stbi_load("asset/image/tip/��.png", &width, &height, &nrChannels, 0);
        break;
    case 1:
        data = stbi_load("asset/image/tip/�������.png", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/tip/����.png", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/tip/��ͷ.png", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/tip/������վ.png", &width, &height, &nrChannels, 0);
        break;
    case 5:
        data = stbi_load("asset/image/tip/�ᳵ.png", &width, &height, &nrChannels, 0);
        break;
    case 6:
        data = stbi_load("asset/image/tip/����ͣ��.png", &width, &height, &nrChannels, 0);
        break;
    case 7:
        data = stbi_load("asset/image/tip/·��ֱ��.png", &width, &height, &nrChannels, 0);
        break;
    case 8:
        data = stbi_load("asset/image/tip/�ϳ�׼��.png", &width, &height, &nrChannels, 0);
        break;
    case 9:
        data = stbi_load("asset/image/tip/ѧУ.png", &width, &height, &nrChannels, 0);
        break;
    case 10:
        data = stbi_load("asset/image/tip/��ת��.png", &width, &height, &nrChannels, 0);
        break;
    case 11:
        data = stbi_load("asset/image/tip/ֱ����ʻ.png", &width, &height, &nrChannels, 0);
        break;
    case 12:
        data = stbi_load("asset/image/tip/��ת��.png", &width, &height, &nrChannels, 0);
        break;
    case 13:
        data = stbi_load("asset/image/tip/��.png", &width, &height, &nrChannels, 0);
        break;
    }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int param[] = { VAO, VBO, texture };
    return param;
}



unsigned int* lightTest()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int param[] = { cubeVAO, lightCubeVAO};
    return param;
}