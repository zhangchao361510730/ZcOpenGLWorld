#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // 包含 glm::translate
#include <glm/gtc/type_ptr.hpp> // 可选，用于转换矩阵为指针

// 打印 glm::mat4 矩阵的函数
void printMatrix(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        std::cout << matrix[i][0] << " "
                  << matrix[i][1] << " "
                  << matrix[i][2] << " "
                  << matrix[i][3] << std::endl;
    }
}


int main() {
    glm::mat4 matrixT1(1.0f); // 创建一个单位矩阵
    glm::mat4 matrixT2(1.0f); // 创建一个单位矩阵

    glm::mat4 matrix2 = {
        {1.0f, 0.0f, 0.0f, 0.0f}, // 第一行
        {0.0f, 1.0f, 0.0f, 0.0f}, // 第二行
        {0.0f, 0.0f, 1.0f, 0.0f}, // 第三行
        {0.0f, 0.0f, 0.0f, 1.0f}  // 第四行
    };

    glm::mat4 matrix3 = {
        {1.0f, 0.0f, 0.0f, 1.0f}, // 第一行
        {0.0f, 1.0f, 0.0f, 2.0f}, // 第二行
        {0.0f, 0.0f, 1.0f, 3.0f}, // 第三行
        {0.0f, 0.0f, 0.0f, 1.0f}  // 第四行
    };

    matrixT1 = glm::translate(matrix2, glm::vec3(1.0f, 2.0f, 3.0f)); // 示例变换
    matrixT2 = matrix2*matrix3; // 示例变换

    std::cout << "Matrix1:" << std::endl;
    printMatrix(matrixT1); // 打印矩阵

    std::cout << "Matrix2:" << std::endl;
    printMatrix(matrixT2); // 打印矩阵

    return 0;
}
