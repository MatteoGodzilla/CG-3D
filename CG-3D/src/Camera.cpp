#include "Camera.hpp"

Camera::Camera() 
    :worldPosition(glm::vec3(0,0,10)), collision(CollisionSphere(worldPosition, collisionRadius))
{
    yaw = -glm::half_pi<float>();
    pitch = 0;
    mode = FPS;
    trackBallin = false;
    aspect = 1;
}

void Camera::keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {  
    //toggle between modes
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        if (mode == FPS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mode = TRACKBALL;
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mode = FPS;
        }
    }

    //move if it's in fps mode
    if (mode == FPS) {
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

        upwardMovement = 0;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            upwardMovement += 1;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            upwardMovement -= 1;
    }
}

void Camera::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            dragStart = glm::vec2(xpos, ypos);
            trackBallin = true;
            startingAngles = glm::vec2(yaw, pitch);
        }
        else {
            trackBallin = false;
        }
    }
}

void Camera::mousePosEvent(GLFWwindow* window, double xpos, double ypos) {
    glm::vec2 now = glm::vec2(xpos, ypos);
    float epsilon = 0.0001;
    if (mode == FPS) {
        glm::vec2 delta = now - lastMousePos;

        if (glm::length(delta) < 1000) {
            yaw += delta.x / 1000;
            pitch -= delta.y / 1000;
        }
    }
    else if(trackBallin) {
        int windowWidth; int windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        
        glm::vec2 normLastMouse = 2.0f * glm::vec2(lastMousePos.x / windowWidth, lastMousePos.y / windowHeight) - 1.0f;
        glm::vec2 normNowMouse = 2.0f * glm::vec2(now.x / windowWidth, now.y / windowHeight) - 1.0f;

        float zLastMouse = 0;
        if (glm::dot(normLastMouse, normLastMouse) < 1)
            zLastMouse = sqrt(1 - glm::dot(normLastMouse, normLastMouse));
        float zNowMouse = 0;
        if (glm::dot(normNowMouse, normNowMouse) < 1)
            zNowMouse = sqrt(1 - glm::dot(normNowMouse, normNowMouse));

        glm::vec3 a = glm::normalize(glm::vec3(normLastMouse.x, normLastMouse.y, zLastMouse));
        glm::vec3 b = glm::normalize(glm::vec3(normNowMouse.x, normNowMouse.y, zNowMouse));
        glm::vec3 rotationAxis = glm::normalize(glm::cross(a, b));
        float theta = acos(glm::dot(a, b));

        glm::vec3 angles = glm::eulerAngles(glm::rotate(glm::quat(1, 0, 0, 0), theta, rotationAxis));
        yaw -= angles.y;
        pitch -= angles.x;
    }
    pitch = glm::clamp(pitch, -glm::half_pi<float>() + epsilon, glm::half_pi<float>() - epsilon);
    lastMousePos = now;
}

void Camera::update(double deltaTime, float aspect) {
    glm::vec3 forwardDir = glm::vec3(cos(yaw), 0, sin(yaw));
    glm::vec3 rightDir = glm::vec3(-sin(yaw), 0, cos(yaw));
    const float speed = 5;

    worldPosition += (float)rightMovement * (float)deltaTime * speed * rightDir;
    worldPosition += (float)forwardMovement * (float)deltaTime * speed * forwardDir;
    worldPosition += (float)upwardMovement * (float)deltaTime * speed * glm::vec3(0.0, 1.0, 0.0);

    collision.updateCollisionSphere(worldPosition, collisionRadius);
    this->aspect = aspect;
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 lookingDir = glm::vec3(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw));
    return glm::lookAt(worldPosition, worldPosition + lookingDir, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjMatrix() {
    return glm::perspective(glm::radians(69.0f), aspect, 0.1f, 100.0f);
}

CollisionSphere Camera::getCollision() {
    return collision;
}