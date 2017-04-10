#pragma once

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan\vulkan.h>
#include <vector>
#include <fstream>
#include <iostream>

VkResult Result;

VkInstance Instance = VK_NULL_HANDLE;
VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
VkDevice Device = VK_NULL_HANDLE;
VkSurfaceKHR Surface = VK_NULL_HANDLE;
VkSwapchainKHR Swapchain = VK_NULL_HANDLE;
VkCommandPool CommandPool = VK_NULL_HANDLE;
VkSemaphore Semaphore = VK_NULL_HANDLE;
VkQueue Queue = VK_NULL_HANDLE;
VkRenderPass RenderPass = VK_NULL_HANDLE;
VkShaderModule ShaderModule = VK_NULL_HANDLE;
VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
VkPipeline Pipeline = VK_NULL_HANDLE;

std::vector<VkImage> SwapchainImage;
std::vector<VkCommandBuffer> CommandBuffer;
std::vector<VkImageView> SwapchainImageView;
std::vector<VkFramebuffer> FrameBuffer;

std::vector<const char*> InstanceExtension;
std::vector<const char*> DeviceExtension;

uint32_t QueueFamilyIndex = UINT32_MAX;
uint32_t ImageIndex = 0;

VkClearColorValue ClearColorValue = {};

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
VkSemaphoreCreateInfo SemaphoreCreateInfo = {};
VkSubmitInfo SubmitInfo = {};
VkPresentInfoKHR PresentInfo = {};
VkAttachmentDescription AttachmentDescription = {};
VkAttachmentReference AttachmentReference = {};
VkSubpassDescription SubpassDescription = {};
VkRenderPassCreateInfo RenderPassCreateInfo = {};
VkImageViewCreateInfo ImageViewCreateInfo = {};
VkFramebufferCreateInfo FramebufferCreateInfo = {};
VkShaderModuleCreateInfo ShaderModuleCreateInfo = {};
VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo = {};

// std::vector<VkPipelineShaderStageCreateInfo> PipelineShaderStageCreateInfo;
// VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo = {};
// VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo = {};
// VkViewport viewport
// VkRect2D
// VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo = {};
// VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo = {};
// VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo = {};
// VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState = {};
// VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo = {};

VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo = {};

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
	InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(InstanceExtension.size());
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
	DeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtension.size());
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
	CommandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(CommandBuffer.size());
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

void SemaphoreCreateInfoStructure() {
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

void SubmitInfoStructure() {
	VkPipelineStageFlags PipelineStageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &Semaphore;
	SubmitInfo.pWaitDstStageMask = &PipelineStageFlags;
	SubmitInfo.commandBufferCount = 1;
	SubmitInfo.pCommandBuffers = &CommandBuffer[ImageIndex];
}

void PresentInfoStructure() {
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.waitSemaphoreCount = 1;
	PresentInfo.pWaitSemaphores = &Semaphore;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pSwapchains = &Swapchain;
	PresentInfo.pImageIndices = &ImageIndex;
}

void AttachmentDescriptionStructure() {
	AttachmentDescription.format = SurfaceFormat.format;
	AttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	AttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	AttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
}

void AttachmentReferenceStructure() {
	AttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

void SubpassDescriptionStructure() {
	AttachmentReferenceStructure();
	SubpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	SubpassDescription.colorAttachmentCount = 1;
	SubpassDescription.pColorAttachments = &AttachmentReference;
}

void RenderPassCreateInfoStructure() {
	AttachmentDescriptionStructure();
	SubpassDescriptionStructure();
	RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RenderPassCreateInfo.attachmentCount = 1;
	RenderPassCreateInfo.pAttachments = &AttachmentDescription;
	RenderPassCreateInfo.subpassCount = 1;
	RenderPassCreateInfo.pSubpasses = &SubpassDescription;
}

void ImageViewCreateInfoStructure() {
	ImageSubresourceRangeStructure();
	SwapchainImageView.resize(SwapchainImage.size());
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.format = SurfaceFormat.format;
	ImageViewCreateInfo.image = SwapchainImage[0];
	ImageViewCreateInfo.subresourceRange = ImageSubresourceRange;
	ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	ImageViewCreateInfo.components.g= VK_COMPONENT_SWIZZLE_G;
	ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
}

void FramebufferCreateInfoStructure() {
	FrameBuffer.resize(SwapchainImageView.size());
	FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCreateInfo.renderPass = RenderPass;
	FramebufferCreateInfo.attachmentCount = 1;
	FramebufferCreateInfo.pAttachments = &SwapchainImageView[0];
	FramebufferCreateInfo.width = 300;
	FramebufferCreateInfo.height = 300;
	FramebufferCreateInfo.layers = 1;
 }

std::vector<char> GetBinaryFileContents(std::string const &FileName) {
	std::ifstream file(FileName, std::ios::binary);
	return std::vector<char>();
}

void ShaderModuleCreateInfoStructure(const char* FileName) {
	const std::vector<char> Code = GetBinaryFileContents(FileName);
	ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderModuleCreateInfo.codeSize = Code.size();
	ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(&Code[0]);
}

void PipelineLayoutCreateInfoStructure() {
	PipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

// std::vector<VkPipelineShaderStageCreateInfo> PipelineShaderStageCreateInfoStructure()
// PipelineVertexInputStateCreateInfoStructure()
// PipelineInputAssemblyStateCreateInfoStructure()
// VkViewport viewport
// VkRect2D
// PipelineViewportStateCreateInfoStructure()
// PipelineRasterizationStateCreateInfoStructure()
// PipelineMultisampleStateCreateInfoStructure()
// PipelineColorBlendAttachmentStateStructure()
// PipelineColorBlendStateCreateInfoStructure()

void GraphicsPipelineCreateInfoStructure() {
	GraphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

 }

VKAPI_ATTR VkResult VKAPI_CALL VkCreateInstance(
	const VkInstanceCreateInfo* InstanceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkInstance* Instance) {
	InstanceCreateInfoStructure();
	vkCreateInstance(InstanceCreateInfo, AllocationCallbacks, Instance);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyInstance(VkInstance Instance,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyInstance(Instance, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkEnumeratePhysicalDevices(
	VkInstance Instance, uint32_t PhysicalDeviceCount) {
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
	PhysicalDevice = PhysicalDeviceList[0];
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkGetPhysicalDeviceQueueFamilyProperties(
	VkPhysicalDevice PhysicalDevice, uint32_t QueueFamilyPropertyCount) {
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertyCount, nullptr);
	std::vector<VkQueueFamilyProperties>QueueFamilyPropertiesList(QueueFamilyPropertyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertyCount, QueueFamilyPropertiesList.data());
	for (uint32_t i = 0; i < QueueFamilyPropertyCount; ++i)
		if ((QueueFamilyPropertiesList[i].queueCount > 0) &&
		    (QueueFamilyPropertiesList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
			QueueFamilyIndex = i;
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateDevice(VkPhysicalDevice PhysicalDevice,
	const VkDeviceCreateInfo* DeviceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkDevice* Device) {
	DeviceCreateInfoStructure();
	vkCreateDevice(PhysicalDevice, DeviceCreateInfo, AllocationCallbacks, Device);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyDevice(VkDevice Device,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyDevice(Device, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateWin32Surface(VkInstance Instance,
	const VkWin32SurfaceCreateInfoKHR* Win32SurfaceCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkSurfaceKHR* Surface) {
	vkCreateWin32SurfaceKHR(Instance, Win32SurfaceCreateInfo, AllocationCallbacks, Surface);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroySurface(VkInstance Instance, VkSurfaceKHR Surface,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroySurfaceKHR(Instance, Surface, AllocationCallbacks);
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

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfaceFormats(
	VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, uint32_t SurfaceFormatCount) {
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR>SurfaceFormatList(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, SurfaceFormatList.data());
	SurfaceFormat = SurfaceFormatList[0];
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfacePresentModes(
	VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, uint32_t PresentModeCount) {
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

VKAPI_ATTR void VKAPI_CALL VkDestroySwapchain(VkDevice Device, VkSwapchainKHR Swapchain,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroySwapchainKHR(Device, Swapchain, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetSwapchainImages(VkDevice Device,
	VkSwapchainKHR Swapchain, uint32_t SwapchainImageCount) {
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, nullptr);
	SwapchainImage.resize(SwapchainImageCount);
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, SwapchainImage.data());
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyImage(VkDevice Device,
	const VkAllocationCallbacks* AllocationCallbacks) {
	for (auto &SwapchainImages : SwapchainImage)
		vkDestroyImage(Device, SwapchainImages, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateCommandPool(VkDevice Device,
	const VkCommandPoolCreateInfo* CommandPoolCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkCommandPool* CommandPool) {
	CommandPoolCreateInfoStructure();
	vkCreateCommandPool(Device, CommandPoolCreateInfo, AllocationCallbacks, CommandPool);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyCommandPool(VkDevice Device, VkCommandPool CommandPool,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyCommandPool(Device, CommandPool, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkAllocateCommandBuffers(VkDevice Device,
	const VkCommandBufferAllocateInfo* CommandBufferAllocateInfo) {
	CommandBufferAllocateInfoStructure();
	vkAllocateCommandBuffers(Device, CommandBufferAllocateInfo, CommandBuffer.data());
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkBeginCommandBuffer(VkCommandBuffer CommandBuffer,
	const VkCommandBufferBeginInfo* CommandBufferBeginInfo) {
	CommandBufferBeginInfoStructure();
	vkBeginCommandBuffer(CommandBuffer, CommandBufferBeginInfo);
	return Result;
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

VKAPI_ATTR void VKAPI_CALL VkDestroyCommandBuffers(VkDevice Device, VkCommandPool CommandPool) {
	vkFreeCommandBuffers(Device, CommandPool, static_cast<uint32_t>(CommandBuffer.size()), CommandBuffer.data());
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateSemaphore(VkDevice Device,
	const VkSemaphoreCreateInfo* SemaphoreCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkSemaphore* Semaphore) {
	SemaphoreCreateInfoStructure();
	vkCreateSemaphore(Device, SemaphoreCreateInfo, AllocationCallbacks, Semaphore);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroySemaphore(VkDevice Device, VkSemaphore Semaphore,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroySemaphore(Device, Semaphore, AllocationCallbacks);
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

VKAPI_ATTR VkResult VKAPI_CALL VkCreateRenderPass(VkDevice Device,
	const VkRenderPassCreateInfo* RenderPassCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkRenderPass* RenderPass) {
	RenderPassCreateInfoStructure();
	vkCreateRenderPass(Device, RenderPassCreateInfo, AllocationCallbacks, RenderPass);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyRenderPass(VkDevice Device, VkRenderPass RenderPass,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyRenderPass(Device, RenderPass, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateImageView(VkDevice Device,
	const VkImageViewCreateInfo* ImageViewCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks) {
	ImageViewCreateInfoStructure();
	vkCreateImageView(Device, ImageViewCreateInfo, AllocationCallbacks, SwapchainImageView.data());
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyImageView(VkDevice Device,
	const VkAllocationCallbacks* AllocationCallbacks) {
	for (auto &SwapchainImageViews : SwapchainImageView)
		vkDestroyImageView(Device, SwapchainImageViews, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateFramebuffer(VkDevice Device,
	const VkFramebufferCreateInfo* FramebufferCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks) {
	FramebufferCreateInfoStructure();
	vkCreateFramebuffer(Device, FramebufferCreateInfo, AllocationCallbacks, FrameBuffer.data());
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyFramebuffer(VkDevice Device,
	const VkAllocationCallbacks* AllocationCallbacks) {
	for (auto &FrameBuffers : FrameBuffer)
		vkDestroyFramebuffer(Device, FrameBuffers, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateShaderModule(VkDevice Device,
	const VkShaderModuleCreateInfo* ShaderModuleCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkShaderModule* ShaderModule) {
	ShaderModuleCreateInfoStructure("vert.spv"); // frag.spv
	vkCreateShaderModule(Device, ShaderModuleCreateInfo, AllocationCallbacks, ShaderModule);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyShaderModule(VkDevice Device, VkShaderModule ShaderModule,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyShaderModule(Device, ShaderModule, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreatePipelineLayout(VkDevice Device,
	const VkPipelineLayoutCreateInfo* PipelineLayoutCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkPipelineLayout* PipelineLayout) {
	PipelineLayoutCreateInfoStructure();
	vkCreatePipelineLayout(Device, PipelineLayoutCreateInfo, AllocationCallbacks, PipelineLayout);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyPipelineLayout(VkDevice Device, VkPipelineLayout PipelineLayout,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyPipelineLayout(Device, PipelineLayout, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateGraphicsPipelines( VkDevice Device,
	VkPipelineCache PipelineCache, uint32_t CreateInfoCount,
	const VkGraphicsPipelineCreateInfo* GraphicsPipelineCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkPipeline* Pipeline) {
	GraphicsPipelineCreateInfoStructure();
	vkCreateGraphicsPipelines(Device, PipelineCache, CreateInfoCount,
				  GraphicsPipelineCreateInfo, AllocationCallbacks, Pipeline);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyPipeline( VkDevice Device, VkPipeline Pipeline,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyPipeline(Device, Pipeline, AllocationCallbacks);
}
