#pragma once

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan\vulkan.h>
#include <vector>

/*****************************************************************
*                -== Handles and constants ==-                   *
******************************************************************/

VkResult Result;

VkInstance Instance = VK_NULL_HANDLE;
VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
VkDevice Device = VK_NULL_HANDLE;
VkSurfaceKHR Surface = VK_NULL_HANDLE;
VkSwapchainKHR Swapchain = VK_NULL_HANDLE;
VkCommandPool CommandPool = VK_NULL_HANDLE;
VkSemaphore WaitSemaphores = VK_NULL_HANDLE;
VkSemaphore SignalSemaphores = VK_NULL_HANDLE;
VkQueue Queue = VK_NULL_HANDLE;

std::vector<VkImage> SwapchainImage;
std::vector<VkCommandBuffer> CommandBuffer;

std::vector<const char*> InstanceExtension;
std::vector<const char*> DeviceExtension;

VkClearColorValue ClearColorValue = { 0.4f, 0.6f, 0.9f, 1.0f };

uint32_t QueueFamilyIndex = UINT32_MAX;
uint32_t i = 0;
uint32_t ImageIndex = 0;

/*****************************************************************
*                 -== VK Structure Type ==-                      *
******************************************************************/

VkApplicationInfo ApplicationInfo = {};
VkInstanceCreateInfo InstanceCreateInfo = {};
VkDeviceQueueCreateInfo DeviceQueueCreateInfo = {};
VkDeviceCreateInfo DeviceCreateInfo = {};
VkWin32SurfaceCreateInfoKHR Win32SurfaceCreateInfo = {};
VkSurfaceCapabilitiesKHR SurfaceCapabilities = {};
VkSurfaceFormatKHR SurfaceFormat = {};
VkPresentModeKHR PresentMode = {};
VkSwapchainCreateInfoKHR SwapchainCreateInfo = {};
VkCommandPoolCreateInfo CommandPoolCreateInfo = {};
VkCommandBufferAllocateInfo CommandBufferAllocateInfo = {};
VkCommandBufferBeginInfo CommandBufferBeginInfo = {};
VkImageSubresourceRange ImageSubresourceRange = {};
VkImageMemoryBarrier ImageMemoryBarrierPresentToClear = {};
VkImageMemoryBarrier ImageMemoryBarrierClearToPresent = {};
VkSemaphoreCreateInfo SemaphoreCreateInfo = {};
VkSubmitInfo SubmitInfo = {};
VkPresentInfoKHR PresentInfo = {};

void ApplicationInfoStructure() {
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;
}

void InstanceCreateInfoStructure() {
	InstanceExtension.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	InstanceExtension.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	ApplicationInfoStructure();
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledExtensionCount = (uint32_t)InstanceExtension.size();
	InstanceCreateInfo.ppEnabledExtensionNames = InstanceExtension.data();
}

void DeviceQueueCreateInfoStructure() {
	std::vector<float> QueuePriorities = { 1.0f };
	DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	DeviceQueueCreateInfo.queueFamilyIndex = QueueFamilyIndex;
	DeviceQueueCreateInfo.queueCount = static_cast<uint32_t>(QueuePriorities.size());
	DeviceQueueCreateInfo.pQueuePriorities = &QueuePriorities[0];
}

void DeviceCreateInfoStructure() {
	DeviceExtension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	DeviceQueueCreateInfoStructure();
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;
	DeviceCreateInfo.enabledExtensionCount = (uint32_t)DeviceExtension.size();
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtension.data();
}

void Win32SurfaceCreateInfoStructure(_In_ HINSTANCE hInstance, _In_ HWND hWnd) {
	Win32SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	Win32SurfaceCreateInfo.hinstance = hInstance;
	Win32SurfaceCreateInfo.hwnd = hWnd;
}

void SwapchainCreateInfoStructure() {
	SwapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainCreateInfo.surface = Surface;
	SwapchainCreateInfo.minImageCount = SurfaceCapabilities.minImageCount;
	SwapchainCreateInfo.imageFormat = SurfaceFormat.format;
	SwapchainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
	SwapchainCreateInfo.imageExtent.width = SurfaceCapabilities.maxImageExtent.width;
	SwapchainCreateInfo.imageExtent.height = SurfaceCapabilities.maxImageExtent.height;
	SwapchainCreateInfo.imageArrayLayers = 1;
	SwapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	SwapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	SwapchainCreateInfo.queueFamilyIndexCount = 0;
	SwapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	SwapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	SwapchainCreateInfo.presentMode = PresentMode;
	SwapchainCreateInfo.clipped = VK_TRUE;
}

void CommandPoolCreateInfoStructure() {
	CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CommandPoolCreateInfo.queueFamilyIndex = QueueFamilyIndex;
}

void CommandBufferAllocateInfoStructure() {
	CommandBuffer.resize(SwapchainImage.size());
	CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	CommandBufferAllocateInfo.commandPool = CommandPool;
	CommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	CommandBufferAllocateInfo.commandBufferCount = (uint32_t)CommandBuffer.size();
}

void CommandBufferBeginInfoStructure() {
	CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	CommandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
}

void ImageSubresourceRangeStructure() {
	ImageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.layerCount = 1;
}

void ImageMemoryBarrierStructure() {
	ImageSubresourceRangeStructure();
	ImageMemoryBarrierPresentToClear.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	ImageMemoryBarrierPresentToClear.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	ImageMemoryBarrierPresentToClear.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	ImageMemoryBarrierPresentToClear.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	ImageMemoryBarrierPresentToClear.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	ImageMemoryBarrierPresentToClear.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ImageMemoryBarrierPresentToClear.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ImageMemoryBarrierPresentToClear.image = SwapchainImage[i];
	ImageMemoryBarrierPresentToClear.subresourceRange = ImageSubresourceRange;
	ImageMemoryBarrierClearToPresent.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	ImageMemoryBarrierClearToPresent.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	ImageMemoryBarrierClearToPresent.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	ImageMemoryBarrierClearToPresent.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	ImageMemoryBarrierClearToPresent.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	ImageMemoryBarrierClearToPresent.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ImageMemoryBarrierClearToPresent.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	ImageMemoryBarrierClearToPresent.image = SwapchainImage[i];
	ImageMemoryBarrierClearToPresent.subresourceRange = ImageSubresourceRange;
}

void SemaphoreCreateInfoStructure() {
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

void SubmitInfoStructure() {
	VkPipelineStageFlags PipelineStageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &WaitSemaphores;
	SubmitInfo.pWaitDstStageMask = &PipelineStageFlags;
	SubmitInfo.commandBufferCount = 1;
	SubmitInfo.pCommandBuffers = &CommandBuffer[ImageIndex];
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores = &SignalSemaphores;
}

void PresentInfoStructure() {
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.waitSemaphoreCount = 1;
	PresentInfo.pWaitSemaphores = &SignalSemaphores;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pSwapchains = &Swapchain;
	PresentInfo.pImageIndices = &ImageIndex;
}

/*****************************************************************
*              -== Initialization functions ==-                  *
******************************************************************/

VKAPI_ATTR VkResult VKAPI_CALL VkCreateInstance(
	const VkInstanceCreateInfo* InstanceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkInstance* Instance) {
	InstanceCreateInfoStructure();
	vkCreateInstance(InstanceCreateInfo, AllocationCallbacks, Instance);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyInstance() {
	vkDestroyInstance(Instance, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkEnumeratePhysicalDevices() {
	uint32_t PhysicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
	PhysicalDevice = PhysicalDeviceList[0];
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkGetPhysicalDeviceQueueFamilyProperties() {
	uint32_t QueueFamilyPropertiesCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertiesCount, nullptr);
	std::vector<VkQueueFamilyProperties>QueueFamilyPropertiesList(QueueFamilyPropertiesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertiesCount, QueueFamilyPropertiesList.data());
	for (uint32_t i = 0; i < QueueFamilyPropertiesCount; ++i)
		if ((QueueFamilyPropertiesList[i].queueCount > 0) && (QueueFamilyPropertiesList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
			QueueFamilyIndex = i;
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateDevice(VkPhysicalDevice PhysicalDevice,
	const VkDeviceCreateInfo* DeviceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkDevice* Device) {
	DeviceCreateInfoStructure();
	vkCreateDevice(PhysicalDevice, DeviceCreateInfo, AllocationCallbacks, Device);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyDevice() {
	vkDestroyDevice(Device, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateWin32Surface(VkInstance Instance,
	const VkWin32SurfaceCreateInfoKHR* Win32SurfaceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkSurfaceKHR* Surface) {
	vkCreateWin32SurfaceKHR(Instance, Win32SurfaceCreateInfo, AllocationCallbacks, Surface);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroySurface() {
	vkDestroySurfaceKHR(Instance, Surface, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfaceSupport(VkPhysicalDevice PhysicalDevice,
	uint32_t QueueFamilyIndex, VkSurfaceKHR Surface, VkBool32* Supported) {
	vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, QueueFamilyIndex, Surface, Supported);
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfaceCapabilities(VkPhysicalDevice PhysicalDevice,
	VkSurfaceKHR Surface, VkSurfaceCapabilitiesKHR* SurfaceCapabilities) {
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, SurfaceCapabilities);
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfaceFormats() {
	uint32_t SurfaceFormatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR>SurfaceFormatList(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, SurfaceFormatList.data());
	SurfaceFormat = SurfaceFormatList[0];
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfacePresentModes() {
	uint32_t PresentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &PresentModeCount, nullptr);
	std::vector<VkPresentModeKHR>PresentModeList(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice, Surface, &PresentModeCount, PresentModeList.data());
	PresentMode = PresentModeList[0];
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateSwapchain(VkDevice Device,
	const VkSwapchainCreateInfoKHR* SwapchainCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkSwapchainKHR* Swapchain) {
	SwapchainCreateInfoStructure();
	vkCreateSwapchainKHR(Device, SwapchainCreateInfo, AllocationCallbacks, Swapchain);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroySwapchain() {
	vkDestroySwapchainKHR(Device, Swapchain, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetSwapchainImages() {
	uint32_t SwapchainImageCount = 0;
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, nullptr);
	SwapchainImage.resize(SwapchainImageCount);
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, SwapchainImage.data());
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyImage() {
	for (auto &Image : SwapchainImage)
		vkDestroyImage(Device,Image, nullptr);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateCommandPool(VkDevice Device,
	const VkCommandPoolCreateInfo* CommandPoolCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkCommandPool* CommandPool) {
	CommandPoolCreateInfoStructure();
	vkCreateCommandPool(Device, CommandPoolCreateInfo, AllocationCallbacks, CommandPool);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyCommandPool() {
	vkDestroyCommandPool(Device, CommandPool, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkAllocateCommandBuffers() {
	CommandBufferAllocateInfoStructure();
	vkAllocateCommandBuffers(Device, &CommandBufferAllocateInfo, CommandBuffer.data());
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkBeginCommandBuffer(VkCommandBuffer CommandBuffer,
	const VkCommandBufferBeginInfo* CommandBufferBeginInfo) {
	CommandBufferBeginInfoStructure();
	vkBeginCommandBuffer(CommandBuffer, CommandBufferBeginInfo);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkCmdPipelineBarrier(VkCommandBuffer CommandBuffer,
	VkPipelineStageFlags SrcPipelineStageFlags, VkPipelineStageFlags DstPipelineStageFlags,
	VkDependencyFlags DependencyFlags, uint32_t MemoryBarrierCount,
	const VkMemoryBarrier* MemoryBarriers, uint32_t BufferMemoryBarrierCount,
	const VkBufferMemoryBarrier* BufferMemoryBarrier, uint32_t ImageMemoryBarrierCount,
	const VkImageMemoryBarrier* ImageMemoryBarrier) {
	ImageMemoryBarrierStructure();
	vkCmdPipelineBarrier(CommandBuffer, SrcPipelineStageFlags, DstPipelineStageFlags, DependencyFlags,
		MemoryBarrierCount, MemoryBarriers, BufferMemoryBarrierCount, BufferMemoryBarrier,
		ImageMemoryBarrierCount, ImageMemoryBarrier);
}

VKAPI_ATTR void VKAPI_CALL VkCmdClearColorImage(VkCommandBuffer CommandBuffer,
	VkImage Image, VkImageLayout ImageLayout,
	const VkClearColorValue* ClearColorValue, uint32_t ImageSubresourceRangeCount,
	const VkImageSubresourceRange* ImageSubresourceRange) {
	ImageSubresourceRangeStructure();
	vkCmdClearColorImage(CommandBuffer, Image, ImageLayout, ClearColorValue,
		ImageSubresourceRangeCount, ImageSubresourceRange);
}

VKAPI_ATTR VkResult VKAPI_CALL VkEndCommandBuffer(VkCommandBuffer CommandBuffer) {
	vkEndCommandBuffer(CommandBuffer);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyCommandBuffers() {
	vkFreeCommandBuffers(Device, CommandPool, (uint32_t)CommandBuffer.size(), CommandBuffer.data());
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateSemaphore(VkDevice Device,
	const VkSemaphoreCreateInfo* SemaphoreCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkSemaphore* Semaphore) {
	SemaphoreCreateInfoStructure();
	vkCreateSemaphore(Device, SemaphoreCreateInfo, AllocationCallbacks, Semaphore);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroySemaphore(VkSemaphore Semaphore) {
	vkDestroySemaphore(Device, Semaphore, VK_NULL_HANDLE);
}

VKAPI_ATTR VkResult VKAPI_CALL VkAcquireNextImage(VkDevice Device, VkSwapchainKHR Swapchain,
	uint64_t Timeout, VkSemaphore Semaphore, VkFence Fence, uint32_t* ImageIndex) {
	vkAcquireNextImageKHR(Device, Swapchain, Timeout, Semaphore, Fence, ImageIndex);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkGetDeviceQueue(VkDevice Device,
	uint32_t QueueFamilyIndex, uint32_t QueueIndex, VkQueue* Queue) {
	vkGetDeviceQueue(Device, QueueFamilyIndex, QueueIndex, Queue);
}

VKAPI_ATTR VkResult VKAPI_CALL VkQueueSubmit(VkQueue Queue, uint32_t SubmitCount,
	const VkSubmitInfo* SubmitInfo, VkFence Fence) {
	SubmitInfoStructure();
	vkQueueSubmit(Queue, SubmitCount, SubmitInfo, Fence);
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkQueuePresent(VkQueue Queue, const VkPresentInfoKHR* PresentInfo) {
	PresentInfoStructure();
	vkQueuePresentKHR(Queue, PresentInfo);
	return Result;
}
