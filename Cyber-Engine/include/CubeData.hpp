#pragma once

const float cubePos[] = { 
    //top +y
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    //bottom -y
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    //left -X
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    //right +X
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    //front -Z
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    //back +Z
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};

const float cubeTexCoord[] = { 
    //top +y
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    //bottom -y
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    //left -X
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    //right +X
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    //front -Z
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    //back +Z 
    0.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
};

const float cubeNormal[] = {   
    //top +y
    0.f, 1.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 1.f, 0.f,
    //bottom -y
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
    //left -X
    -1.f, 0.f, 0.f,
    -1.f, 0.f, 0.f,
    -1.f, 0.f, 0.f,
    -1.f, 0.f, 0.f,
    //right +X
    1.f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    //front -Z
    0.f, 0.f, -1.f,
    0.f, 0.f, -1.f,
    0.f, 0.f, -1.f,
    0.f, 0.f, -1.f,
    //back +Z 
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f
};

const unsigned int cubeIndex[] = { 
    //top +y
    0, 1, 2,
    0, 2, 3,
    //bottom -y
    4, 5, 6,
    4, 6, 7,
    //left -X
    8, 9, 10,
    8, 10, 11,
    //right +X
    12, 13, 14,
    12, 14, 15,
    //front -Z
    16, 17, 18,
    16, 18, 19,
    //back +Z
    20, 21, 22,
    20, 22, 23
};

const unsigned int cubeVerticesSize = 24;
const unsigned int cubeIndexSize = 36;
