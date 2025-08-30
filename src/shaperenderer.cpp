#include <glad/glad.h>
#include "shaperenderer.h"


namespace Shaperenderer {
    GLuint VAO, VBO;

    void initShape(float* arrayname, int vertexCount)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // minden vertex: 3 koordináta + 3 szín = 6 float
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), arrayname, GL_STATIC_DRAW);

        // pozíció attribútum (location=0 a shaderben)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // szín attribútum (location=1 a shaderben)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void drawShape(int vertexCount)
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }
}