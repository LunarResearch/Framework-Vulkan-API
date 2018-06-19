#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan\vulkan.h>

VkResult Result;

VkInstance Instance = nullptr;
VkPhysicalDevice PhysicalDevice = nullptr;
VkDevice Device = nullptr;
VkSurfaceKHR Surface = nullptr;
VkSwapchainKHR Swapchain = nullptr;
VkImage SwapchainImage = nullptr;
VkCommandPool CommandPool = nullptr;
VkCommandBuffer CommandBuffer = nullptr;
VkSemaphore Semaphore = nullptr;
VkQueue Queue = nullptr;
VkRenderPass RenderPass = nullptr;
VkImageView SwapchainImageView = nullptr;
VkFramebuffer FrameBuffer = nullptr;
VkShaderModule ShaderModule = nullptr;
VkPipelineLayout PipelineLayout = nullptr;
VkPipeline Pipeline = nullptr;

std::vector<VkImage> VectorSwapchainImage;
std::vector<VkCommandBuffer> VectorCommandBuffer;
std::vector<VkImageView> VectorSwapchainImageView;
std::vector<VkFramebuffer> VectorFrameBuffer;

std::vector<const char *> InstanceExtension;
std::vector<const char *> DeviceExtension;

uint32_t QueueFamilyIndex = UINT32_MAX;
uint32_t ImageIndex = NULL;

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
VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo = {};
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
VkVertexInputBindingDescription VertexInputBindingDescription = {};
VkVertexInputAttributeDescription VertexInputAttributeDescription = {};
VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo = {};
VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo = {};
VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo = {};
VkViewport Viewport = {};
VkRect2D Rect2D = {};
VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo = {};
VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo = {};
VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo = {};
VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo = {};
VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState = {};
VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo = {};
VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo = {};
VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo = {};

void ApplicationInfoStructure() {
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.pNext = nullptr;
	ApplicationInfo.pApplicationName = "vkLiteSDKApplication";
	ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 27);
	ApplicationInfo.pEngineName = "vkLiteSDKEngine";
	ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 7);
	ApplicationInfo.apiVersion = VK_API_VERSION_1_1;
}

void InstanceCreateInfoStructure() {
	InstanceExtension.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	InstanceExtension.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	ApplicationInfoStructure();
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pNext = nullptr;
	InstanceCreateInfo.flags = NULL;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledLayerCount = 0;
	InstanceCreateInfo.ppEnabledLayerNames = nullptr;
	InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(InstanceExtension.size());
	InstanceCreateInfo.ppEnabledExtensionNames = &InstanceExtension[0];
}

void DeviceQueueCreateInfoStructure() {
	std::vector<float> QueuePriorities = { 1.0f };
	DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	DeviceQueueCreateInfo.pNext = nullptr;
	DeviceQueueCreateInfo.flags = NULL;
	DeviceQueueCreateInfo.queueFamilyIndex = QueueFamilyIndex;
	DeviceQueueCreateInfo.queueCount = static_cast<uint32_t>(QueuePriorities.size());
	DeviceQueueCreateInfo.pQueuePriorities = &QueuePriorities[0];
}

void DeviceCreateInfoStructure() {
	DeviceExtension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	DeviceQueueCreateInfoStructure();
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.pNext = nullptr;
	DeviceCreateInfo.flags = NULL;
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;
	DeviceCreateInfo.enabledLayerCount = 0;
	DeviceCreateInfo.ppEnabledLayerNames = nullptr;
	DeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtension.size());
	DeviceCreateInfo.ppEnabledExtensionNames = &DeviceExtension[0];
	DeviceCreateInfo.pEnabledFeatures = nullptr;
}

void Win32SurfaceCreateInfoStructure(HINSTANCE hInstance, HWND hWnd) {
	Win32SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	Win32SurfaceCreateInfo.pNext = nullptr;
	Win32SurfaceCreateInfo.flags = NULL;
	Win32SurfaceCreateInfo.hinstance = hInstance;
	Win32SurfaceCreateInfo.hwnd = hWnd;
}

void SwapchainCreateInfoStructure() {
	SwapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainCreateInfo.pNext = nullptr;
	SwapchainCreateInfo.flags = NULL;
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
	SwapchainCreateInfo.pQueueFamilyIndices = &QueueFamilyIndex;
	SwapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	SwapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	SwapchainCreateInfo.presentMode = PresentMode;
	SwapchainCreateInfo.clipped = VK_TRUE;
	SwapchainCreateInfo.oldSwapchain = nullptr;
}

void AttachmentDescriptionStructure() {
	AttachmentDescription.flags = NULL;
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
	AttachmentReference.attachment = 0;
	AttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

void SubpassDescriptionStructure() {
	AttachmentReferenceStructure();
	SubpassDescription.flags = NULL;
	SubpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	SubpassDescription.inputAttachmentCount = 0;
	SubpassDescription.pInputAttachments = nullptr;
	SubpassDescription.colorAttachmentCount = 1;
	SubpassDescription.pColorAttachments = &AttachmentReference;
	SubpassDescription.pResolveAttachments = nullptr;
	SubpassDescription.preserveAttachmentCount = 0;
	SubpassDescription.pPreserveAttachments = nullptr;
}

void RenderPassCreateInfoStructure() {
	AttachmentDescriptionStructure();
	SubpassDescriptionStructure();
	RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RenderPassCreateInfo.pNext = nullptr;
	RenderPassCreateInfo.flags = NULL;
	RenderPassCreateInfo.attachmentCount = 1;
	RenderPassCreateInfo.pAttachments = &AttachmentDescription;
	RenderPassCreateInfo.subpassCount = 1;
	RenderPassCreateInfo.pSubpasses = &SubpassDescription;
	RenderPassCreateInfo.dependencyCount = 0;
	RenderPassCreateInfo.pDependencies = nullptr;
}

void ImageSubresourceRangeStructure() {
	ImageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.layerCount = 1;
}

void ImageViewCreateInfoStructure() {
	ImageSubresourceRangeStructure();
	VectorSwapchainImageView.resize(VectorSwapchainImage.size());
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = NULL;
	ImageViewCreateInfo.image = SwapchainImage;
	ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	ImageViewCreateInfo.format = SurfaceFormat.format;
	ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	ImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
	ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
	ImageViewCreateInfo.subresourceRange = ImageSubresourceRange;
}

void FramebufferCreateInfoStructure() {
	VectorFrameBuffer.resize(VectorSwapchainImageView.size());
	FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCreateInfo.pNext = nullptr;
	FramebufferCreateInfo.flags = NULL;
	FramebufferCreateInfo.renderPass = RenderPass;
	FramebufferCreateInfo.attachmentCount = 1;
	FramebufferCreateInfo.pAttachments = &SwapchainImageView;
	FramebufferCreateInfo.width = CW_USEDEFAULT;
	FramebufferCreateInfo.height = CW_USEDEFAULT;
	FramebufferCreateInfo.layers = 1;
}

void CommandPoolCreateInfoStructure() {
	CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CommandPoolCreateInfo.pNext = nullptr;
	CommandPoolCreateInfo.flags = NULL;
	CommandPoolCreateInfo.queueFamilyIndex = QueueFamilyIndex;
}

void CommandBufferAllocateInfoStructure() {
	VectorCommandBuffer.resize(VectorSwapchainImage.size());
	CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	CommandBufferAllocateInfo.pNext = nullptr;
	CommandBufferAllocateInfo.commandPool = CommandPool;
	CommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	CommandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(VectorCommandBuffer.size());
}

void CommandBufferInheritanceInfoStructure() {
	CommandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	CommandBufferInheritanceInfo.pNext = nullptr;
	CommandBufferInheritanceInfo.renderPass = RenderPass;
	CommandBufferInheritanceInfo.subpass = 0;
	CommandBufferInheritanceInfo.framebuffer = FrameBuffer;
	CommandBufferInheritanceInfo.occlusionQueryEnable = VK_TRUE;
	CommandBufferInheritanceInfo.queryFlags = VK_QUERY_CONTROL_PRECISE_BIT;
	CommandBufferInheritanceInfo.pipelineStatistics = VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT;
}

void CommandBufferBeginInfoStructure() {
	CommandBufferInheritanceInfoStructure();
	CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	CommandBufferBeginInfo.pNext = nullptr;
	CommandBufferBeginInfo.pInheritanceInfo = &CommandBufferInheritanceInfo;
	CommandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
}

void SemaphoreCreateInfoStructure() {
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = nullptr;
	SemaphoreCreateInfo.flags = NULL;
}

void SubmitInfoStructure() {
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.pNext = nullptr;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &Semaphore;
	SubmitInfo.pWaitDstStageMask = reinterpret_cast<VkPipelineStageFlags *>(VK_PIPELINE_STAGE_VERTEX_SHADER_BIT);
	SubmitInfo.commandBufferCount = 1;
	SubmitInfo.pCommandBuffers = &VectorCommandBuffer[ImageIndex];
	SubmitInfo.signalSemaphoreCount = 0;
	SubmitInfo.pSignalSemaphores = nullptr;
}

void PresentInfoStructure() {
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.pNext = nullptr;
	PresentInfo.waitSemaphoreCount = 1;
	PresentInfo.pWaitSemaphores = &Semaphore;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pSwapchains = &Swapchain;
	PresentInfo.pImageIndices = &ImageIndex;
	PresentInfo.pResults = &Result;
}

std::vector<char> GetBinaryFileContents(std::string const &FileName) {
	std::ifstream file(FileName, std::ios::binary);
	return std::vector<char>();
}

void ShaderModuleCreateInfoStructure(const char* FileName) {
	ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderModuleCreateInfo.pNext = nullptr;
	ShaderModuleCreateInfo.flags = NULL;
	const std::vector<char> Code = GetBinaryFileContents(FileName);
	ShaderModuleCreateInfo.codeSize = Code.size();
	ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t *>(&Code[0]);
}

void PipelineLayoutCreateInfoStructure() {
	PipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutCreateInfo.pNext = nullptr;
	PipelineLayoutCreateInfo.flags = NULL;
	PipelineLayoutCreateInfo.setLayoutCount = 0;
	PipelineLayoutCreateInfo.pSetLayouts = nullptr;
	PipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	PipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
}

// std::vector<VkPipelineShaderStageCreateInfo> PipelineShaderStageCreateInfoStructure()

void VertexInputBindingDescriptionStructure() {
	VertexInputBindingDescription.binding = 0;
	VertexInputBindingDescription.stride = 0;
	VertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}

void VertexInputAttributeDescriptionStructure() {
	VertexInputAttributeDescription.location = 0;
	VertexInputAttributeDescription.binding = 0;
	VertexInputAttributeDescription.format = SurfaceFormat.format;
	VertexInputAttributeDescription.offset = 0;
}

void PipelineVertexInputStateCreateInfoStructure() {
	PipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	PipelineVertexInputStateCreateInfo.pNext = nullptr;
	PipelineVertexInputStateCreateInfo.flags = NULL;
	PipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
	PipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &VertexInputBindingDescription;
	PipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 1;
	PipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = &VertexInputAttributeDescription;
}

void PipelineInputAssemblyStateCreateInfoStructure() {
	PipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	PipelineInputAssemblyStateCreateInfo.pNext = nullptr;
	PipelineInputAssemblyStateCreateInfo.flags = NULL;
	PipelineInputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	PipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;
}

void PipelineTessellationStateCreateInfoStructure() {
	PipelineTessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	PipelineTessellationStateCreateInfo.pNext = nullptr;
	PipelineTessellationStateCreateInfo.flags = NULL;
	PipelineTessellationStateCreateInfo.patchControlPoints = 0;
}

void ViewportStructure() {
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = CW_USEDEFAULT;
	Viewport.height = CW_USEDEFAULT;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;
}

void Rect2DStructure() {
	Rect2D.offset.x = 0;
	Rect2D.offset.y = 0;
	Rect2D.extent.width = CW_USEDEFAULT;
	Rect2D.extent.height = CW_USEDEFAULT;
}

void PipelineViewportStateCreateInfoStructure() {
	PipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	PipelineViewportStateCreateInfo.pNext = nullptr;
	PipelineViewportStateCreateInfo.flags = NULL;
	PipelineViewportStateCreateInfo.viewportCount = 1;
	PipelineViewportStateCreateInfo.pViewports = &Viewport;
	PipelineViewportStateCreateInfo.scissorCount = 1;
	PipelineViewportStateCreateInfo.pScissors = &Rect2D;
}

void PipelineRasterizationStateCreateInfoStructure() {
	PipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	PipelineRasterizationStateCreateInfo.pNext = nullptr;
	PipelineRasterizationStateCreateInfo.flags = NULL;
	PipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	PipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_FRONT_AND_BACK;
	PipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	PipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
	PipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
	PipelineRasterizationStateCreateInfo.depthBiasClamp = 0.0f;
	PipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;
	PipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
}

void PipelineMultisampleStateCreateInfoStructure() {
	PipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	PipelineMultisampleStateCreateInfo.pNext = nullptr;
	PipelineMultisampleStateCreateInfo.flags = NULL;
	PipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_32_BIT;
	PipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
	PipelineMultisampleStateCreateInfo.minSampleShading = 0.0f;
	PipelineMultisampleStateCreateInfo.pSampleMask = 0;
	PipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
	PipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;
}

void PipelineDepthStencilStateCreateInfoStructure() {
	PipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	PipelineDepthStencilStateCreateInfo.pNext = nullptr;
	PipelineDepthStencilStateCreateInfo.flags = NULL;
	/*PipelineDepthStencilStateCreateInfo.depthTestEnable = ;
	PipelineDepthStencilStateCreateInfo.depthWriteEnable = ;
	PipelineDepthStencilStateCreateInfo.depthCompareOp = ;
	PipelineDepthStencilStateCreateInfo.depthBoundsTestEnable = ;
	PipelineDepthStencilStateCreateInfo.stencilTestEnable = ;
	PipelineDepthStencilStateCreateInfo.front = ;
	PipelineDepthStencilStateCreateInfo.back = ;
	PipelineDepthStencilStateCreateInfo.minDepthBounds = ;
	PipelineDepthStencilStateCreateInfo.maxDepthBounds = ;*/
}

void PipelineColorBlendAttachmentStateStructure() {
	/*PipelineColorBlendAttachmentState.blendEnable = ;
	PipelineColorBlendAttachmentState.srcColorBlendFactor = ;
	PipelineColorBlendAttachmentState.dstColorBlendFactor = ;
	PipelineColorBlendAttachmentState.colorBlendOp = ;
	PipelineColorBlendAttachmentState.srcAlphaBlendFactor = ;
	PipelineColorBlendAttachmentState.dstAlphaBlendFactor = ;
	PipelineColorBlendAttachmentState.alphaBlendOp = ;
	PipelineColorBlendAttachmentState.colorWriteMask = ;*/
}

void PipelineColorBlendStateCreateInfoStructure() {
	PipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	PipelineColorBlendStateCreateInfo.pNext = nullptr;
	PipelineColorBlendStateCreateInfo.flags = NULL;
	//PipelineColorBlendStateCreateInfo.logicOpEnable = ;
	//PipelineColorBlendStateCreateInfo.logicOp = ;
	PipelineColorBlendStateCreateInfo.attachmentCount = 1;
	PipelineColorBlendStateCreateInfo.pAttachments = &PipelineColorBlendAttachmentState;
	//PipelineColorBlendStateCreateInfo.blendConstants = ;
}

void PipelineDynamicStateCreateInfoStructure() {
	PipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	PipelineDynamicStateCreateInfo.pNext = nullptr;
	PipelineDynamicStateCreateInfo.flags = NULL;
	PipelineDynamicStateCreateInfo.dynamicStateCount = 1;
	PipelineDynamicStateCreateInfo.pDynamicStates = reinterpret_cast<VkDynamicState *>(VK_DYNAMIC_STATE_VIEWPORT);
}

void GraphicsPipelineCreateInfoStructure() {
	GraphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	GraphicsPipelineCreateInfo.pNext = nullptr;
	GraphicsPipelineCreateInfo.flags = NULL;
	//GraphicsPipelineCreateInfo.stageCount = 1;
	//GraphicsPipelineCreateInfo.pStages = ;
	GraphicsPipelineCreateInfo.pVertexInputState = &PipelineVertexInputStateCreateInfo;
	GraphicsPipelineCreateInfo.pInputAssemblyState = &PipelineInputAssemblyStateCreateInfo;
	GraphicsPipelineCreateInfo.pTessellationState = &PipelineTessellationStateCreateInfo;
	GraphicsPipelineCreateInfo.pViewportState = &PipelineViewportStateCreateInfo;
	GraphicsPipelineCreateInfo.pRasterizationState = &PipelineRasterizationStateCreateInfo;
	GraphicsPipelineCreateInfo.pMultisampleState = &PipelineMultisampleStateCreateInfo;
	GraphicsPipelineCreateInfo.pDepthStencilState = &PipelineDepthStencilStateCreateInfo;
	GraphicsPipelineCreateInfo.pColorBlendState = &PipelineColorBlendStateCreateInfo;
	GraphicsPipelineCreateInfo.pDynamicState = &PipelineDynamicStateCreateInfo;
	GraphicsPipelineCreateInfo.layout = PipelineLayout;
	GraphicsPipelineCreateInfo.renderPass = RenderPass;
	GraphicsPipelineCreateInfo.subpass = 0;
	GraphicsPipelineCreateInfo.basePipelineHandle = nullptr;
	GraphicsPipelineCreateInfo.basePipelineIndex = 0;
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
	VkInstance Instance, uint32_t PhysicalDeviceCount, VkPhysicalDevice* PhysicalDevices) {
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
	PhysicalDevice = PhysicalDeviceList[0];
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice PhysicalDevice,
	uint32_t QueueFamilyPropertyCount, VkQueueFamilyProperties* QueueFamilyProperties) {
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

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfaceFormats(VkPhysicalDevice PhysicalDevice,
	VkSurfaceKHR Surface, uint32_t SurfaceFormatCount, VkSurfaceFormatKHR* SurfaceFormats) {
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR>SurfaceFormatList(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &SurfaceFormatCount, SurfaceFormatList.data());
	SurfaceFormat = SurfaceFormatList[0];
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkGetPhysicalDeviceSurfacePresentModes(VkPhysicalDevice PhysicalDevice,
	VkSurfaceKHR Surface, uint32_t PresentModeCount, VkPresentModeKHR* PresentModes) {
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
	VkSwapchainKHR Swapchain, uint32_t SwapchainImageCount, VkImage* SwapchainImages) {
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, nullptr);
	VectorSwapchainImage.resize(SwapchainImageCount);
	vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImageCount, VectorSwapchainImage.data());
	SwapchainImage = VectorSwapchainImage[0];
	return Result;
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
	const VkCommandBufferAllocateInfo* CommandBufferAllocateInfo, VkCommandBuffer* CommandBuffers) {
	CommandBufferAllocateInfoStructure();
	vkAllocateCommandBuffers(Device, CommandBufferAllocateInfo, VectorCommandBuffer.data());
	CommandBuffer = VectorCommandBuffer[0];
	return Result;
}

VKAPI_ATTR VkResult VKAPI_CALL VkBeginCommandBuffer(VkCommandBuffer CommandBuffer,
	const VkCommandBufferBeginInfo* CommandBufferBeginInfo) {
	CommandBufferBeginInfoStructure();
	vkBeginCommandBuffer(CommandBuffer, CommandBufferBeginInfo);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkCmdClearColorImage(
	VkCommandBuffer CommandBuffer, VkImage SwapchainImage, VkImageLayout ImageLayout,
	const VkClearColorValue* ClearColorValue, uint32_t ImageSubresourceRangeCount,
	const VkImageSubresourceRange* ImageSubresourceRange) {
	ImageSubresourceRangeStructure();
	vkCmdClearColorImage(CommandBuffer, SwapchainImage, ImageLayout, ClearColorValue,
		ImageSubresourceRangeCount, ImageSubresourceRange);
}

VKAPI_ATTR VkResult VKAPI_CALL VkEndCommandBuffer(VkCommandBuffer CommandBuffer) {
	vkEndCommandBuffer(CommandBuffer);
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyCommandBuffers(VkDevice Device, VkCommandPool CommandPool) {
	vkFreeCommandBuffers(Device, CommandPool, static_cast<uint32_t>(VectorCommandBuffer.size()), VectorCommandBuffer.data());
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
	const VkAllocationCallbacks* AllocationCallbacks, VkImageView* SwapchainImageViews) {
	ImageViewCreateInfoStructure();
	vkCreateImageView(Device, ImageViewCreateInfo, AllocationCallbacks, VectorSwapchainImageView.data());
	SwapchainImageView = VectorSwapchainImageView[0];
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyImageView(VkDevice Device, VkImageView SwapchainImageView,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyImageView(Device, SwapchainImageView, AllocationCallbacks);
}

VKAPI_ATTR VkResult VKAPI_CALL VkCreateFramebuffer(VkDevice Device,
	const VkFramebufferCreateInfo* FramebufferCreateInfo,
	const VkAllocationCallbacks* AllocationCallbacks, VkFramebuffer* FrameBuffers) {
	FramebufferCreateInfoStructure();
	vkCreateFramebuffer(Device, FramebufferCreateInfo, AllocationCallbacks, VectorFrameBuffer.data());
	FrameBuffer = VectorFrameBuffer[0];
	return Result;
}

VKAPI_ATTR void VKAPI_CALL VkDestroyFramebuffer(VkDevice Device, VkFramebuffer FrameBuffer,
	const VkAllocationCallbacks* AllocationCallbacks) {
	vkDestroyFramebuffer(Device, FrameBuffer, AllocationCallbacks);
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

VKAPI_ATTR VkResult VKAPI_CALL VkCreateGraphicsPipelines(VkDevice Device,
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
