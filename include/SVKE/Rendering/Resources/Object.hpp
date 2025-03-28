#pragma once

#include "SVKE/Rendering/Resources/Model.hpp"
#include "SVKE/Core/Graphics/Color.hpp"

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#ifndef GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#endif
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace vk
{
class Object
{
  public:
    struct TransformComponent
    {
        glm::vec3 translation{};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        // Corresponds to: translate * Ry * Rx * Rz * scale transformation
        // Rotation convention uses Tail-Bryan angles with axis order Y(1), X(2), Z(3)
        // More: https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
        glm::mat4 mat4();
        glm::mat3 normalMatrix();
    };

    Object(const Color &color = COLOR_WHITE);
    Object(std::shared_ptr<Model> &model, const Color &color = COLOR_WHITE);
    Object &operator=(const Object &) = delete;
    Object(Object &&) = default;
    Object &operator=(Object &&) = default;

    void bind(VkCommandBuffer &command_buffer);

    void draw(VkCommandBuffer &command_buffer);

    glm::mat4 transform();

    glm::mat3 normalMatrix();

    const Color &getColor() const;

    const std::shared_ptr<Model> &getModel() const;

    const TransformComponent &getTransformComponent() const;

    const glm::vec3 &getTranslation() const;

    const glm::vec3 &getScale() const;

    const glm::vec3 &getRotation() const;

    void setModel(std::shared_ptr<Model> &model);

    void setColor(const Color &color);

    void setTranslation(const glm::vec3 &translation);

    void setScale(const glm::vec3 &scale);

    void setRotation(const glm::vec3 &rotation);

  protected:
    std::shared_ptr<Model> model;
    Color color;
    TransformComponent transformComponent;
};
} // namespace vk
