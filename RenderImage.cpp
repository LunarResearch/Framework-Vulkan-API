#include "Macros.h"

InitializationVulkanAPI InitVkAPI;
BuildWindow bWin;

RenderImage::RenderImage() {
	CreateSurface();
	CreateSwapchain();
	GetSwapchainImages();
	CreateCommandPool();
	CreateCommandBuffers();
	CreateVkSemaphore();
	PresentSwapchains();
	RenderWindow();
}

RenderImage::~RenderImage() {
	DestroyVkSemaphore();
	DestroyCommandBuffers();
	DestroyCommandPool();
	DestroySwapchainImage();
	DestroySwapchain();
	DestroySurface();
}

void RenderImage::CreateSurface() {
	VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo{};
	SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	SurfaceCreateInfo.hinstance = bWin.hInstance;
	SurfaceCreateInfo.hwnd = bWin.hWnd;

	vkCreateWin32SurfaceKHR(InitVkAPI.Instance, &SurfaceCreateInfo, nullptr, &Surface);

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(InitVkAPI.PhysicalDevice, Surface, &SurfaceCapabilities);

	uint32_t SurfaceFormatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(InitVkAPI.PhysicalDevice, Surface, &SurfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR>SurfaceFormatList(SurfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(InitVkAPI.PhysicalDevice, Surface, &SurfaceFormatCount, SurfaceFormatList.data());
	SurfaceFormat = SurfaceFormatList[0];

	uint32_t PresentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(InitVkAPI.PhysicalDevice, Surface, &PresentModeCount, nullptr);
	std::vector<VkPresentModeKHR>PresentModeList(PresentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(InitVkAPI.PhysicalDevice, Surface, &PresentModeCount, PresentModeList.data());
	PresentMode = PresentModeList[0];
}

void RenderImage::DestroySurface() {
	vkDestroySurfaceKHR(InitVkAPI.Instance, Surface, nullptr);
}

void RenderImage::CreateSwapchain() {
	VkSwapchainCreateInfoKHR SwapchainCreateInfo{};
	SwapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	SwapchainCreateInfo.surface = Surface;
	SwapchainCreateInfo.minImageCount = SurfaceCapabilities.minImageCount;
	SwapchainCreateInfo.imageFormat = SurfaceFormat.format;
	SwapchainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
	SwapchainCreateInfo.imageExtent.width = 1038;
	SwapchainCreateInfo.imageExtent.height = 583;
	SwapchainCreateInfo.imageArrayLayers = 1;
	SwapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	SwapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	SwapchainCreateInfo.queueFamilyIndexCount = 0;
	SwapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	SwapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	SwapchainCreateInfo.presentMode = PresentMode;
	SwapchainCreateInfo.clipped = VK_TRUE;

	vkCreateSwapchainKHR(InitVkAPI.Device, &SwapchainCreateInfo, nullptr, &Swapchain);
}

void RenderImage::DestroySwapchain() {
	vkDestroySwapchainKHR(InitVkAPI.Device, Swapchain, nullptr);
}

void RenderImage::GetSwapchainImages() {
	vkGetSwapchainImagesKHR(InitVkAPI.Device, Swapchain, &SwapchainImageCount, nullptr);
	SwapchainImages.resize(SwapchainImageCount);
	vkGetSwapchainImagesKHR(InitVkAPI.Device, Swapchain, &SwapchainImageCount, SwapchainImages.data());
}

void RenderImage::DestroySwapchainImage() {
	for (auto &SwapchainImage : SwapchainImages)
		vkDestroyImage(InitVkAPI.Device, SwapchainImage, nullptr);
}

void RenderImage::CreateCommandPool() {
	VkCommandPoolCreateInfo CommandPoolCreateInfo{};
	CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CommandPoolCreateInfo.queueFamilyIndex = InitVkAPI.QueueFamilyIndex;

	vkCreateCommandPool(InitVkAPI.Device, &CommandPoolCreateInfo, nullptr, &CommandPool);
}

void RenderImage::DestroyCommandPool() {
	vkDestroyCommandPool(InitVkAPI.Device, CommandPool, nullptr);
}

void RenderImage::CreateCommandBuffers() {
	CommandBuffer.resize(SwapchainImages.size());

	VkCommandBufferAllocateInfo CommandBufferAllocateInfo{};
	CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	CommandBufferAllocateInfo.commandPool = CommandPool;
	CommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	CommandBufferAllocateInfo.commandBufferCount = (uint32_t)CommandBuffer.size();

	vkAllocateCommandBuffers(InitVkAPI.Device, &CommandBufferAllocateInfo, CommandBuffer.data());

	VkCommandBufferBeginInfo CommandBufferBeginInfo{};
	CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	CommandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VkClearColorValue ClearColorValue = { 0.4f, 0.6f, 0.9f, 1.0f };

	VkImageSubresourceRange ImageSubresourceRange{};
	ImageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.layerCount = 1;

	for (uint32_t i = 0; i < SwapchainImages.size(); ++i) {
		VkImageMemoryBarrier ImageMemoryBarrierPresentToClear{};
		ImageMemoryBarrierPresentToClear.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		ImageMemoryBarrierPresentToClear.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		ImageMemoryBarrierPresentToClear.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		ImageMemoryBarrierPresentToClear.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		ImageMemoryBarrierPresentToClear.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		ImageMemoryBarrierPresentToClear.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		ImageMemoryBarrierPresentToClear.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		ImageMemoryBarrierPresentToClear.image = SwapchainImages[i];
		ImageMemoryBarrierPresentToClear.subresourceRange = ImageSubresourceRange;
		VkImageMemoryBarrier ImageMemoryBarrierClearToPresent{};
		ImageMemoryBarrierClearToPresent.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		ImageMemoryBarrierClearToPresent.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		ImageMemoryBarrierClearToPresent.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		ImageMemoryBarrierClearToPresent.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		ImageMemoryBarrierClearToPresent.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		ImageMemoryBarrierClearToPresent.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		ImageMemoryBarrierClearToPresent.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		ImageMemoryBarrierClearToPresent.image = SwapchainImages[i];
		ImageMemoryBarrierClearToPresent.subresourceRange = ImageSubresourceRange;

		vkBeginCommandBuffer(CommandBuffer[i], &CommandBufferBeginInfo);

		vkCmdPipelineBarrier(CommandBuffer[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrierPresentToClear);
		vkCmdClearColorImage(CommandBuffer[i], SwapchainImages[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &ClearColorValue, 1, &ImageSubresourceRange);
		vkCmdPipelineBarrier(CommandBuffer[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrierClearToPresent);

		vkEndCommandBuffer(CommandBuffer[i]);
	}
}

void RenderImage::DestroyCommandBuffers() {
	vkFreeCommandBuffers(InitVkAPI.Device, CommandPool, (uint32_t)CommandBuffer.size(), CommandBuffer.data());
}

void RenderImage::CreateVkSemaphore() {
	VkSemaphoreCreateInfo SemaphoreCreateInfo{};
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(InitVkAPI.Device, &SemaphoreCreateInfo, nullptr, &WaitSemaphores);

	vkCreateSemaphore(InitVkAPI.Device, &SemaphoreCreateInfo, nullptr, &SignalSemaphores);
}

void RenderImage::DestroyVkSemaphore() {
	vkDestroySemaphore(InitVkAPI.Device, SignalSemaphores, nullptr);
	vkDestroySemaphore(InitVkAPI.Device, WaitSemaphores, nullptr);
}

void RenderImage::PresentSwapchains() {
	uint32_t ImageIndex = 0;
	vkAcquireNextImageKHR(InitVkAPI.Device, Swapchain, UINT64_MAX, WaitSemaphores, VK_NULL_HANDLE, &ImageIndex);

	VkPipelineStageFlags PipelineStageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;

	VkSubmitInfo SubmitInfo{};
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.waitSemaphoreCount = 1;
	SubmitInfo.pWaitSemaphores = &WaitSemaphores;
	SubmitInfo.pWaitDstStageMask = &PipelineStageFlags;
	SubmitInfo.commandBufferCount = 1;
	SubmitInfo.pCommandBuffers = &CommandBuffer[ImageIndex];
	SubmitInfo.signalSemaphoreCount = 1;
	SubmitInfo.pSignalSemaphores = &SignalSemaphores;

	vkGetDeviceQueue(InitVkAPI.Device, InitVkAPI.QueueFamilyIndex, 0, &Queue);

	vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE);

	VkPresentInfoKHR PresentInfo{};
	PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	PresentInfo.waitSemaphoreCount = 1;
	PresentInfo.pWaitSemaphores = &SignalSemaphores;
	PresentInfo.swapchainCount = 1;
	PresentInfo.pSwapchains = &Swapchain;
	PresentInfo.pImageIndices = &ImageIndex;

	vkQueuePresentKHR(Queue, &PresentInfo);
}

bool RenderImage::RenderWindow() {
	ShowWindow(bWin.hWnd, SW_SHOW);
	MSG msg{};
	while (msg.message != WM_QUIT)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return static_cast<char>(msg.wParam);
}
