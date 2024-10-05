#ifndef SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>

namespace suisho::backend {

class VulkanDevice {
public:
    bool initialize();
    void terminate();

    template <class F>
    void subscribeWindowResize(F&& f) {
        onWindowResize.push_back(std::forward<F>(f));
    }

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    VkShaderModule createShaderModule(const std::vector<char>& code);

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
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    VkCommandPool commandPool;

    VkDescriptorPool descriptorPool;

    std::vector<VkSemaphore> presentationSync;
    std::vector<VkSemaphore> renderingSync;
    std::vector<VkFence> CmdExecutionSync;

    uint32_t currentFrame = 0;
    uint32_t currentImageIndex = 0;

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
