#include "mat.h"

Matrix3x3::Matrix3x3()
{

}
Matrix3x3::Matrix3x3(float** mat)
{
    for (int i = 0; i < 3; i++) {
        for (int o = 0; o < 3; o++) {
            this->mat[i][o] = mat[i][o];
        }
    }
}
Matrix3x3::Matrix3x3(vec3* vecs) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            mat[x][y] = vecs[x].getPoints()[y];
        }
    }
}
Matrix3x3::Matrix3x3(vec3 vec1, vec3 vec2, vec3 vec3p) 
{
     for (int y = 0; y < 3; y++) {
            mat[0][y] = vec1.getPoints()[y];
            mat[1][y] = vec2.getPoints()[y];
            mat[2][y] = vec3p.getPoints()[y];

    }
}
Matrix3x3::Matrix3x3(float mat[3][3]) 
{
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            this->mat[x][y] = mat[x][y];
        }
    }
}

Matrix3x3 Matrix3x3::operator*(Matrix3x3& other)
{
    float array3x3[3][3];
    float **array2d = other.GetMatrix();

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            array3x3[x][y] = mat[0][x] * array2d[y][0] + mat[1][x] * array2d[y][1] + mat[2][x] * array2d[y][2];
        }
    }
    

    return Matrix3x3(array2d);
}

float* Matrix3x3::operator*(vec3& other)
{
    float *array3x3 = new float[3];

    for (int x = 0; x < 3; x++) {
         array3x3[x] = mat[0][x] * other.getPoints()[x] + mat[1][x] * other.getPoints()[x] + mat[2][x] * other.getPoints()[x];
    }
    return array3x3;
}

float** Matrix3x3::GetMatrix()
{
    float** array2d = new float*[3];
    for (int x = 0; x < 3; x++) {
        array2d[x] = new float[3];
        for (int y = 0; y < 3; y++) {
            array2d[x][y] = mat[x][y];
        }
    }
    return array2d;
}

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(vec4* vecs)
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            mat[x][y] = vecs[x].getPoints()[y];
        }
    }
}

Matrix4x4::Matrix4x4(vec4 vec1, vec4 vec2, vec4 vec3, vec4 vec5)
{
    for (int y = 0; y < 4; y++) {
        mat[0][y] = vec1.getPoints()[y];
        mat[1][y] = vec2.getPoints()[y];
        mat[2][y] = vec3.getPoints()[y];
        mat[3][y] = vec5.getPoints()[y];

    }
}

Matrix4x4::Matrix4x4(float mat[4][4])
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            this->mat[x][y] = mat[x][y];
        }
    }
}

Matrix4x4::Matrix4x4(float** mat)
{
    for (int i = 0; i < 4; i++) {
        for (int o = 0; o < 4; o++) {
            this->mat[i][o] = mat[i][o];
        }
    }
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4& other)
{
    float array4x4[4][4];
    float** array2d = other.GetMatrix();

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            array4x4[x][y] = mat[0][x] * array2d[y][0] + mat[1][x] * array2d[y][1] + mat[2][x] * array2d[y][2] + mat[3][x] * array2d[y][3];
        }
    }
    for (int i = 0; i < 4; i++) {
        delete[] array2d[i];
    }
    delete[] array2d;
    return Matrix4x4(array4x4);

}

Matrix4x4 Matrix4x4::operator*(float mat[4][4])
{
    float array4x4[4][4];

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            array4x4[x][y] = this->mat[0][x] * mat[y][0] + this->mat[1][x] * mat[y][1] + this->mat[2][x] * mat[y][2] + this->mat[3][x] * mat[y][3];
        }
    }
    return Matrix4x4(array4x4);

}

void Matrix4x4::operator=(Matrix4x4 *other)
{
    float** arr2d = other->GetMatrix();
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            mat[x][y] = arr2d[x][y];
        }
    }
    for (int i = 0; i < 4; i++) {
        delete[] arr2d[i];
    }
    delete[] arr2d;
}

float* Matrix4x4::operator*(vec4& other)
{
    float *array4x4 = new float[4];

    for (int x = 0; x < 3; x++) {
         array4x4[x] = mat[0][x] * other.getPoints()[x] + mat[1][x] * other.getPoints()[x] + mat[2][x] * other.getPoints()[x];
    }
    return array4x4;
}

float** Matrix4x4::GetMatrix()
{
    float** array2d = new float* [4];
    for (int x = 0; x < 4; x++) {
        array2d[x] = new float[4];
        for (int y = 0; y < 4; y++) {
            array2d[x][y] = mat[x][y];
        }
    }
    return array2d;
}
