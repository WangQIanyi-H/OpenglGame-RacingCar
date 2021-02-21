#pragma once

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

// 用于按钮特效的变换矩阵
glm::mat4 trans_button = glm::mat4(1.0f);//单位矩阵




//开始
point_f ICON_BEGIN[4] = {
    point_f(-0.2f, 0.63f),// top left 
    point_f(0.2f, 0.63f),// top right
    point_f(0.2f, 0.4f),// bottom right
    point_f(-0.2f, 0.4f),// bottom left
};
//游戏规则
point_f ICON_RULE[4] = {
    point_f(-0.2f, 0.27f),
    point_f(0.2f, 0.27f),
    point_f(0.2f, 0.04f),
    point_f(-0.2f, 0.04f),
};
//设置
point_f ICON_SET[4] = {
    point_f(-0.2f, -0.09f),
    point_f(0.2f, -0.09f),
    point_f(0.2f,  -0.32f),
    point_f(-0.2f, -0.32f),
};
//退出
point_f ICON_EXIT[4] = {
    point_f(0.6f, -0.45f),
    point_f(0.6f, -0.45f),
    point_f(0.3f, -0.68f),
    point_f(0.3f, -0.68f),
};

unsigned int* menu_Loader(int index)
{
    float verticesBegin[] = {
        // positions                           // texture coords
        ICON_BEGIN[1].x, ICON_BEGIN[1].y, 0.0f,1.0f, 1.0f, // top right
        ICON_BEGIN[2].x, ICON_BEGIN[2].y, 0.0f,1.0f, 0.0f, // bottom right
        ICON_BEGIN[3].x, ICON_BEGIN[3].y, 0.0f,0.0f, 0.0f, // bottom left
        ICON_BEGIN[0].x, ICON_BEGIN[0].y, 0.0f,0.0f, 1.0f  // top left 
    };
    float verticesRule[] = {
        // positions                   // texture coords
        ICON_RULE[1].x, ICON_RULE[1].y, 0.0f,1.0f, 1.0f, // top right
        ICON_RULE[2].x, ICON_RULE[2].y, 0.0f,1.0f, 0.0f, // bottom right
        ICON_RULE[3].x, ICON_RULE[3].y, 0.0f,0.0f, 0.0f, // bottom left
        ICON_RULE[0].x, ICON_RULE[0].y, 0.0f,0.0f, 1.0f  // top left 
    };

    float verticesSet[] = {
        // positions                   // texture coords
        ICON_SET[1].x, ICON_SET[1].y, 0.0f,1.0f, 1.0f, // top right
        ICON_SET[2].x, ICON_SET[2].y, 0.0f,1.0f, 0.0f, // bottom right
        ICON_SET[3].x, ICON_SET[3].y, 0.0f,0.0f, 0.0f, // bottom left
        ICON_SET[0].x, ICON_SET[0].y, 0.0f,0.0f, 1.0f  // top left 
    };
    float verticesExit[] = {
        // positions                   // texture coords
        ICON_EXIT[1].x, ICON_EXIT[1].y, 0.0f,1.0f, 1.0f, // top right
        ICON_EXIT[2].x, ICON_EXIT[2].y, 0.0f,1.0f, 0.0f, // bottom right
        ICON_EXIT[3].x, ICON_EXIT[3].y, 0.0f,0.0f, 0.0f, // bottom left
        ICON_EXIT[0].x, ICON_EXIT[0].y, 0.0f,0.0f, 1.0f  // top left 
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

    if (index == 1) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBegin), verticesBegin, GL_STATIC_DRAW);
    }
    if (index == 2) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRule), verticesRule, GL_STATIC_DRAW);
    }
    if (index == 3) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSet), verticesSet, GL_STATIC_DRAW);
    }
    if (index == 4) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesExit), verticesExit, GL_STATIC_DRAW);
    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


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
        data = stbi_load("asset/image/menu/begin.jpg", &width, &height, &nrChannels, 0);
        break;
    case 2:
        data = stbi_load("asset/image/menu/rule.jpg", &width, &height, &nrChannels, 0);
        break;
    case 3:
        data = stbi_load("asset/image/menu/set.jpg", &width, &height, &nrChannels, 0);
        break;
    case 4:
        data = stbi_load("asset/image/menu/exit.jpg", &width, &height, &nrChannels, 0);
        break;
    }

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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