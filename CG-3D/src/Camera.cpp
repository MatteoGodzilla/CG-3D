#include "Camera.hpp"

Camera::Camera() {
    position = glm::vec3(0, 0, 0);
    yaw = 0;
    pitch = 0;
}

void Camera::keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {  
    rightMovement = 0;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rightMovement += 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rightMovement -= 1;

    forwardMovement = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        forwardMovement += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        forwardMovement -= 1;
}

void Camera::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {

}

void Camera::mousePosEvent(GLFWwindow* window, double xpos, double ypos) {
    glm::vec2 now = glm::vec2(xpos, ypos);
    glm::vec2 delta = now - lastMousePos;

    float epsilon = 0.0001;

    if (glm::length(delta) < 1000) {
        yaw += delta.x / 1000;
        pitch -= delta.y / 1000;
        pitch = std::min(std::max(-glm::half_pi<float>() + epsilon, pitch), glm::half_pi<float>() - epsilon);
    }

    lastMousePos = now;
}

void Camera::update(double deltaTime) {
    glm::vec3 forwardDir = glm::vec3(cos(yaw), 0, sin(yaw));
    glm::vec3 rightDir = glm::vec3(-sin(yaw), 0, cos(yaw));
    const float speed = 5;

    position += (float)rightMovement * (float)deltaTime * speed * rightDir;
    position += (float)forwardMovement * (float)deltaTime * speed * forwardDir;
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 lookingDir = glm::vec3(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw));
    return glm::lookAt(position, position + lookingDir, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjMatrix() {
    return glm::perspective(glm::radians(69.0f), 1.0f, 0.1f, 100.0f);
}