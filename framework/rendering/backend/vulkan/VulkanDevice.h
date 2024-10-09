#ifndef SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <variant>
#include "rendering/backend/vulkan/VulkanImage.h"
#include "rendering/backend/vulkan/VulkanBuffer.h"

namespace suisho::backend {

class VulkanCommandBuffer;
struct VulkanImage;

class VulkanDevice {
public:
    bool initialize();
    void terminate();
    bool isWindowClosed() const;
    bool isWindowMinimized() const;

    template <class F>
    void subscribeWindowResize(F&& f) {
        onWindowResize.push_back(std::forward<F>(f));
    }

    const std::vector<VulkanImage>& getSwapchainImages() const { return swapChainImages; }

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

    VulkanImage createImage(
        uint32_t width, uint32_t height, const void* data,
        VkFormat format, VkImageTiling tiling,
        VkImageUsageFlags usage, VkMemoryPropertyFlags mem_props,
        VkImageAspectFlags view_aspect
    );
    void destroyImage(VulkanImage& image);

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VulkanBuffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void destroyBuffer(VulkanBuffer& buffer);

    VkShaderModule createShaderModule(const std::vector<char>& code);
    void destroyShaderModule(VkShaderModule mod);

    // FIXME: Fixed function
    // 0: presented image, 1: depth. Subpass is 0 only
    VkRenderPass createRenderPass();
    void destroyRenderPass(VkRenderPass pass);

    VkPipeline createGraphicsPipeline(
        VkShaderModule vert, VkShaderModule frag,
        const std::vector<VkDescriptorSetLayout>& binding_layouts,
        VkRenderPass pass,
        VkPipelineLayout& out_layout
    );
    void destroyPipeline(VkPipeline pipeline, VkPipelineLayout layout);

    VkDescriptorSetLayout createBindingLayout(const std::unordered_map<uint32_t, VkDescriptorType>& bindings);
    void destroyBindingLayout(VkDescriptorSetLayout layout);

    VkDescriptorSet createBindingSet(VkDescriptorSetLayout layout, const std::unordered_map<uint32_t, std::variant<VulkanBuffer>>& binded);

    // CONCERN: Assert attachment size is equal to framebuffer size
    VkFramebuffer createFramebuffer(const std::vector<VulkanImage>& attachments, VkRenderPass pass);
    void destroyFramebuffer(VkFramebuffer fb);

    VulkanCommandBuffer createCommandBuffer();
    void destroyCommandBuffer(VulkanCommandBuffer& buf);

    bool submit(const VulkanCommandBuffer& cmds, VkFence sync);
    bool present(uint32_t image_index);

    uint32_t acquireNextImage();
    void waitIdle();

    VkFence createFence(bool signaled = false);
    /// @brief フェンスがシグナル状態になるまで待機する
    /// @param fence 待機するフェンス
    /// @param timeout_nano 待機の最大時間[ナノ秒]。最大値で永久に待機する
    /// @return 正常終了なら0, タイムアウトなら負の値、それ以外なら正の値
    /// @note 待機時間は、指定された値よりも僅かに長くなる可能性がある
    int waitForFence(VkFence fence, uint64_t timeout_nano);
    void resetFence(VkFence fence);
    void destroyFence(VkFence fence);

private:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
    };

    bool isDebugged = true;
    std::vector<const char*> enabledLayers;
    std::vector<const char*> enabledDeviceExtensions;

    GLFWwindow* window;
    std::vector<std::function<void(uint32_t, uint32_t)>> onWindowResize;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VulkanImage> swapChainImages;

    VkCommandPool commandPool;

    VkDescriptorPool descriptorPool;

    VkSemaphore presentationSync;
    VkSemaphore renderingSync;

    bool framebufferResized = false;
    static void onGlfwWindowResized(GLFWwindow* window, int width, int height);

    void initWindow();
    void initVulkan();
    void recreateSwapChain();
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void cleanupSwapChain();
    void createCommandPool();
    void createDescriptorPool(); // FIXME: Fixed descriptor counts
    void createSyncObjects();
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device); // NOTE: Assert queue is completed
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
