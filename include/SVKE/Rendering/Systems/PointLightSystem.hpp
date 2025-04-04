#pragma once

#include "SVKE/Core/Graphics/Pipeline.hpp"
#include "SVKE/Core/Math/Matrix.hpp"
#include "SVKE/Core/Math/Vector.hpp"
#include "SVKE/Core/System/Device.hpp"
#include "SVKE/Core/System/Memory/Alignment.hpp"
#include "SVKE/Rendering/Camera.hpp"
#include "SVKE/Rendering/FrameInfo.hpp"
#include "SVKE/Rendering/Resources/Object.hpp"
#include "SVKE/Rendering/Systems/Renderer.hpp"
#include "SVKE/Rendering/Descriptors/DescriptorSetLayout.hpp"

namespace vk
{
class PointLightSystem
{
  public:
    struct PointLightPushConstant
    {
        ALIGNAS_VEC3 Vec3f position{};
        ALIGNAS_VEC4 Vec4f color; // w = intensity
        ALIGNAS_SCLR(float) float radius;
    };

    PointLightSystem(Device &device, Renderer &renderer, DescriptorSetLayout &global_set_layout);
    PointLightSystem(const PointLightSystem &) = delete;
    PointLightSystem &operator=(const PointLightSystem &) = delete;

    ~PointLightSystem();

    void update(const FrameInfo &frame_info, GlobalUBO &ubo);
    void render(const FrameInfo &frame_info);

  private:
    Device &device;

    VkPipelineLayout pipelineLayout;
    std::unique_ptr<Pipeline> pipeline;

    std::unique_ptr<Shader> vertShader;
    std::unique_ptr<Shader> fragShader;

    void loadShaders();

    void createPipelineLayout(DescriptorSetLayout &global_set_layout);

    void createPipeline(VkRenderPass render_pass);
};
} // namespace vk
