#include <GL/glut.h>
#include<iostream>

int windowWidth = 800, windowHeight = 600; // 假设窗口尺寸为 800x600

void setupOrthoProjection() {
    glMatrixMode(GL_PROJECTION); // 选择投影矩阵模式
    glLoadIdentity(); // 重置投影矩阵

    // 设置正交投影，确保坐标系统的原点在左下角，单位为像素
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW); // 切换回模型视图矩阵
    glLoadIdentity(); // 重置模型视图矩阵
}

void drawButton() {
    float buttonX = 100.0f, buttonY = 100.0f;  // 按钮的左上角位置
    float buttonWidth = 150.0f, buttonHeight = 50.0f; // 按钮的宽度和高度

    glColor3f(0.2f, 0.6f, 0.8f); // 设置按钮的颜色

    glBegin(GL_QUADS);  // 绘制矩形（按钮）
        glVertex2f(buttonX, buttonY);  // 左上角
        glVertex2f(buttonX + buttonWidth, buttonY);  // 右上角
        glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);  // 右下角
        glVertex2f(buttonX, buttonY + buttonHeight);  // 左下角
    glEnd();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // 检查是否是鼠标左键按下
        // 由于OpenGL坐标系统的y轴向上，而窗口的y坐标是向下的，需要进行转换
        y = windowHeight - y; // 转换y坐标为OpenGL坐标系

        // 检查点击位置是否在按钮范围内
        if (x >= 100 && x <= 250 && y >= 100 && y <= 150) {
            // 按钮被点击
            printf("Button clicked!\n");
            // 在这里可以执行按钮点击后的操作
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // 清除屏幕

    drawButton(); // 绘制按钮

    glFlush(); // 渲染并显示
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Fixed 2D Button");

    setupOrthoProjection();  // 设置正交投影

    glutDisplayFunc(display);  // 注册绘制回调函数
    glutMouseFunc(mouseCallback); // 注册鼠标回调函数

    glutMainLoop();  // 进入主循环
    return 0;
}
