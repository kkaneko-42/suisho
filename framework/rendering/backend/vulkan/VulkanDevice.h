#ifndef SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <variant>
#include "rendering/backend/vulkan/VulkanImage.h"
#include "rendering/backend/vulkan/VulkanTexture.h"
#include "rendering/backend/vulkan/VulkanBuffer.h"
#include "rendering/backend/vulkan/VulkanBindingLayout.h"

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

    VkPhysicalDeviceProperties getProperties() const;
    const std::vector<VulkanImage>& getSwapchainImages() const { return swapChainImages; }

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    VulkanImage createImage(
        uint32_t width, uint32_t height, const void* data,
        VkFormat format, VkImageLayout layout,
        VkImageUsageFlags usage, VkMemoryPropertyFlags mem_props,
        VkImageAspectFlags view_aspect
    );
    void destroyImage(VulkanImage& image);

    VulkanTexture createTexture(uint32_t width, uint32_t height, const void* data, VkFormat format);
    void destroyTexture(VulkanTexture& tex);

    void transitionImageLayout(VulkanImage& target, VkImageLayout to);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VulkanBuffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void flushBuffer(VulkanBuffer& buffer, VkDeviceSize offset, VkDeviceSize size);
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

    VulkanBindingLayout createBindingLayout(const std::unordered_map<uint32_t, VkDescriptorType>& bindings);
    void destroyBindingLayout(VulkanBindingLayout& layout);

    VkDescriptorSet createBindingSet(
        const VulkanBindingLayout& layout,
        const std::unordered_map<uint32_t, std::variant<VulkanBuffer, VulkanTexture>>& binded
    );
    void destroyBindingSet(VkDescriptorSet set);

    // CONCERN: Assert attachment size is equal to framebuffer size
    VkFramebuffer createFramebuffer(const std::vector<VulkanImage>& attachments, VkRenderPass pass);
    void destroyFramebuffer(VkFramebuffer fb);

    VulkanCommandBuffer createCommandBuffer();
    void destroyCommandBuffer(VulkanCommandBuffer& buf);

    bool submit(const VulkanCommandBuffer& cmds, VkFence sync);
    bool present();

    uint32_t swapBackBuffer();
    uint32_t getNextImageIndex() const { return nextImageIndex; }
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
        bool isComplete() const {
            return graphicsFamily != UINT32_MAX && presentFamily != UINT32_MAX;
        }
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
    uint32_t nextImageIndex = 0;
    std::vector<VulkanImage> swapChainImages;
    std::vector<VkSemaphore> presentationSyncs;
    std::vector<VkSemaphore> renderingSyncs;

    VkCommandPool commandPool;
    VkDescriptorPool descriptorPool;

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
