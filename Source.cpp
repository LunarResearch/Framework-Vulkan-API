#include "VkFramework.h"

void CREATE() {
	VkCreateInstance(&InstanceCreateInfo, VK_NULL_HANDLE, &Instance);
	VkEnumeratePhysicalDevices();
	VkGetPhysicalDeviceQueueFamilyProperties();
	VkCreateDevice(PhysicalDevice, &DeviceCreateInfo, VK_NULL_HANDLE, &Device);
	VkGetDeviceQueue(Device, QueueFamilyIndex, 0, &Queue);
}

void RENDER() {
	VkCreateWin32Surface(Instance, &Win32SurfaceCreateInfo, VK_NULL_HANDLE, &Surface);
	VkGetPhysicalDeviceSurfaceCapabilities(PhysicalDevice, Surface, &SurfaceCapabilities);
	VkGetPhysicalDeviceSurfaceFormats();
	VkGetPhysicalDeviceSurfacePresentModes();
	VkCreateSwapchain(Device, &SwapchainCreateInfo, VK_NULL_HANDLE, &Swapchain);
	VkGetSwapchainImages();
	VkCreateCommandPool(Device, &CommandPoolCreateInfo, VK_NULL_HANDLE, &CommandPool);
	VkAllocateCommandBuffers();
	VkImageSubresourceRange ImageSubresourceRange{};
	ImageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	ImageSubresourceRange.baseMipLevel = 0;
	ImageSubresourceRange.levelCount = 1;
	ImageSubresourceRange.baseArrayLayer = 0;
	ImageSubresourceRange.layerCount = 1;
	for (i = 0; i < SwapchainImages.size(); ++i) {
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
		VkBeginCommandBuffer(CommandBuffer[i], &CommandBufferBeginInfo);
		VkCmdPipelineBarrier(CommandBuffer[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
			0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &ImageMemoryBarrierPresentToClear);
		VkCmdClearColorImage(CommandBuffer[i], SwapchainImages[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			&ClearColorValue, 1, &ImageSubresourceRange);
		VkCmdPipelineBarrier(CommandBuffer[i], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &ImageMemoryBarrierClearToPresent);
		VkEndCommandBuffer(CommandBuffer[i]);
	}	
	VkCreateSemaphore(Device, &SemaphoreCreateInfo, VK_NULL_HANDLE, &WaitSemaphores);
	VkCreateSemaphore(Device, &SemaphoreCreateInfo, VK_NULL_HANDLE, &SignalSemaphores);
	VkAcquireNextImage(Device, Swapchain, UINT64_MAX, WaitSemaphores, VK_NULL_HANDLE, &ImageIndex);
	VkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE);
	VkQueuePresent(Queue, &PresentInfo);
}

void DESTROY() {
	VkDestroySemaphore(SignalSemaphores);
	VkDestroySemaphore(WaitSemaphores);
	VkDestroyCommandBuffers();
	VkDestroyCommandPool();
	VkDestroyImage();
	//VkDestroySwapchain();
	VkDestroySurface();
	VkDestroyDevice();
	VkDestroyInstance();
}

void KeyDown(uint8_t key) {
	if (GetAsyncKeyState(VK_ESCAPE))
		exit(0);
}

LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (uMsg) {

	case WM_CREATE:
		CREATE();
		break;

	case WM_PAINT:
		RENDER();
		break;

	case WM_KEYDOWN:
		KeyDown(static_cast<uint8_t>(wParam));
		break;

	case WM_DESTROY:
		DESTROY();
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName, "Test",
		WS_SYSMENU | WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - 1024) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 576) / 2,
		1024, 576, NULL, NULL, hInstance, 0);
	Win32SurfaceCreateInfoStructure(hInstance, hWnd);
	ShowWindow(hWnd, nCmdShow);
	MSG msg = {};
	while (msg.message != WM_QUIT)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return static_cast<char>(msg.wParam);
}
