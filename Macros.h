#pragma once

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan\vulkan.h>
#include <Windows.h>
#include <vector>

class InitializationVulkanAPI {
public:
	InitializationVulkanAPI();
	~InitializationVulkanAPI();
	
	void CreateExtension();

	void CreateInstance();
	void DestroyInstance();

	void EnumeratePhysicalDevices();
	void GetPhysicalDeviceQueueFamilyProperties();

	void CreateDevice();
	void DestroyDevice();

	VkInstance Instance = VK_NULL_HANDLE;
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	VkDevice Device = VK_NULL_HANDLE;

	std::vector<const char*> InstanceExtension;
	std::vector<const char*> DeviceExtension;

	uint32_t QueueFamilyIndex = 0;
};

class BuildWindow {
public:
	BuildWindow();
	~BuildWindow();
	
	void MakeWindow();
	void KillWindow();

	HINSTANCE hInstance = NULL;
	HWND hWnd = NULL;
};

class RenderImage {
public:
	RenderImage();
	~RenderImage();

	void CreateSurface();
	void DestroySurface();

	void CreateSwapchain();
	void DestroySwapchain();

	void GetSwapchainImages();
	void DestroySwapchainImage();

	void CreateCommandPool();
	void DestroyCommandPool();

	void CreateCommandBuffers();
	void DestroyCommandBuffers();

	void CreateVkSemaphore();
	void DestroyVkSemaphore();

	void PresentSwapchains();
	bool RenderWindow();

	VkSurfaceKHR Surface = VK_NULL_HANDLE;
	VkSwapchainKHR Swapchain = VK_NULL_HANDLE;
	VkCommandPool CommandPool = VK_NULL_HANDLE;
	VkSemaphore WaitSemaphores = VK_NULL_HANDLE;
	VkSemaphore SignalSemaphores = VK_NULL_HANDLE;
	VkQueue Queue = VK_NULL_HANDLE;

	std::vector<VkImage> SwapchainImages;
	std::vector<VkCommandBuffer> CommandBuffer;

	VkSurfaceCapabilitiesKHR SurfaceCapabilities = {};
	VkSurfaceFormatKHR SurfaceFormat = {};
	VkPresentModeKHR PresentMode = {};

	uint32_t SwapchainImageCount = 0;
};
