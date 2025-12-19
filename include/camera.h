#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include <vector>

#include "vertex.h"

const float speed = 1;
const float d = 5000;
class Camera
{
public:
    Camera(glm::vec3 camera_coord, glm::vec3 camera_vec)
        : camera_coord(camera_coord), camera_vec(camera_vec)
    {
        camera_perspective = {camera_coord, camera_vec};
        x_axis = {1.0, 0.0};
        y_axis = {0.0, 1.0};
        this->camera_speed = speed;

        near_plane_origin = camera_coord + glm::normalize(camera_vec) * d;
    }

    void update(glm::vec3 camera_coord, glm::vec3 camera_vec)
    {
        this->camera_coord = camera_coord;
        this->camera_vec = camera_vec;
    }

    // Projects world-space point P onto the camera's near plane (using
    // `near_plane_origin`) and appends the resulting UV to `dot_set`.
    // Returns true on success, false if the ray is parallel or behind.
    bool projectPointToNearPlane(const glm::vec3 &up, const glm::vec3 &P)
    {
        glm::vec3 f = glm::normalize(camera_vec);

        glm::vec3 rayDir = P - camera_coord;
        float denom = glm::dot(f, rayDir);
        if (std::abs(denom) < 1e-6f)
            return false; // 平行

        float t = glm::dot(f, near_plane_origin - camera_coord) / denom;
        if (t < 0)
            return false; // 在相机后方

        glm::vec3 outWorldPos = camera_coord + t * rayDir;

        glm::vec3 right = glm::normalize(glm::cross(f, up));
        glm::vec3 upPlane = glm::cross(right, f);

        glm::vec3 delta = outWorldPos - near_plane_origin;
        glm::vec2 outPlaneUV;
        outPlaneUV.x = glm::dot(delta, right);
        outPlaneUV.y = glm::dot(delta, upPlane);

        dot_set.push_back(outPlaneUV);
        return true;
    }

private:
    glm::vec3 camera_coord;
    glm::vec3 camera_vec;

    glm::vec2 x_axis; // camera axis system
    glm::vec2 y_axis; // camera axis system

    float camera_speed;

    Plane camera_perspective;

    float d; // near plane distance
    glm::vec3 near_plane_origin;
    std::vector<glm::vec2> dot_set;
};

#endif