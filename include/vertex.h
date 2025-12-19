#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <numeric>

const glm::vec3 x_axis = {1.0f, 0.0f, 0.0f}; // x axis in right-handed system
const glm::vec3 y_axis = {0.0f, 1.0f, 0.0f}; // y axis in right-handed system
const glm::vec3 z_axis = {0.0f, 0.0f, 1.0f}; // z axis in right-handed system

class Vector3D // Line with direction
{
public:
    Vector3D(glm::vec3 begin, glm::vec3 end)
    {
        vec = glm::normalize(end - begin);

        dot_set.push_back(begin);
        dot_set.push_back(end);
    }

    ~Vector3D();

    float a;
    float b;
    float c;

    glm::vec3 vec;

private:
    glm::vec3 begin;
    glm::vec3 end;

    std::vector<glm::vec3> dot_set;
};

class Plane
{
public:
    Plane(){};
    Plane(glm::vec3 normal_vec, glm::vec3 dot) : normal_vec(normal_vec), dot(dot)
    {
        projection_x_axis = {1.0f, 0.0f};
        projection_y_axis = {0.0f, 1.0f};

        dot_set.push_back(dot);
        
    }

    float getDistanceFromObserverToOrigin(glm::vec3 observer_coord)
    {
        return glm::abs(glm::dot(observer_coord - dot, normal_vec)) / glm::length(normal_vec);
    }

    float getProjectionDistanceFromDotToOrigin(glm::vec3 observer_coord)
    {
        float a = glm::abs(glm::dot(dot - observer_coord, dot)) / glm::length(normal_vec);
        float c = glm::distance(observer_coord, dot);
        return std::sqrt(c * c - a * a);
    }

private:
    glm::vec3 normal_vec; // normal vector

    glm::vec2 projection_x_axis;
    glm::vec2 projection_y_axis;

    glm::vec3 dot;

    std::vector<glm::vec3> dot_set;
};

#endif // VERTEX_H
