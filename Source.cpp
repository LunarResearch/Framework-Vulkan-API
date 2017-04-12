#include "VkFramework.h"

void CreateVulkan() {
	VkCreateInstance(&InstanceCreateInfo, nullptr, &Instance);
	VkEnumeratePhysicalDevices(Instance, 0, &PhysicalDevice);
	VkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, 0, nullptr);
	VkCreateDevice(PhysicalDevice, &DeviceCreateInfo, nullptr, &Device);
	VkGetDeviceQueue(Device, QueueFamilyIndex, 0, &Queue);
}

void DrawBackGround() {
	VkCreateWin32Surface(Instance, &Win32SurfaceCreateInfo, nullptr, &Surface);
	VkGetPhysicalDeviceSurfaceCapabilities(PhysicalDevice, Surface, &SurfaceCapabilities);
	VkGetPhysicalDeviceSurfaceFormats(PhysicalDevice, Surface, 0, &SurfaceFormat);
	VkGetPhysicalDeviceSurfacePresentModes(PhysicalDevice, Surface, 0, &PresentMode);
	VkCreateSwapchain(Device, &SwapchainCreateInfo, nullptr, &Swapchain);
	VkGetSwapchainImages(Device, Swapchain, 0, &SwapchainImage);
	VkCreateCommandPool(Device, &CommandPoolCreateInfo, nullptr, &CommandPool);
	VkAllocateCommandBuffers(Device, &CommandBufferAllocateInfo, &CommandBuffer);
	VkBeginCommandBuffer(CommandBuffer, &CommandBufferBeginInfo);
	ClearColorValue = { 0.4f, 0.6f, 0.9f, 1.0f }; // Cornflower Blue
	VkCmdClearColorImage(CommandBuffer, SwapchainImage, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			     &ClearColorValue, 1, &ImageSubresourceRange);
	VkEndCommandBuffer(CommandBuffer);
	VkCreateSemaphore(Device, &SemaphoreCreateInfo, nullptr, &Semaphore);
	VkAcquireNextImage(Device, Swapchain, UINT64_MAX, Semaphore, nullptr, &ImageIndex);
	VkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE);
	VkQueuePresent(Queue, &PresentInfo);
}

void DrawPrimitive() {
	VkCreateRenderPass(Device, &RenderPassCreateInfo, nullptr, &RenderPass);
	VkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &SwapchainImageView);
	VkCreateFramebuffer(Device, &FramebufferCreateInfo, nullptr, &FrameBuffer);
	//VkCreateShaderModule(Device, &ShaderModuleCreateInfo, nullptr, &ShaderModule);
	VkCreatePipelineLayout(Device, &PipelineLayoutCreateInfo, nullptr, &PipelineLayout);
	VkCreateGraphicsPipelines(Device, VK_NULL_HANDLE, 1, &GraphicsPipelineCreateInfo, nullptr, &Pipeline);
}

void DestroyPrimitive() {
	VkDestroyPipeline(Device, Pipeline, nullptr);
	VkDestroyPipelineLayout(Device, PipelineLayout, nullptr);
	//VkDestroyShaderModule(Device, ShaderModule, nullptr);
	VkDestroyFramebuffer(Device, FrameBuffer, nullptr);
	VkDestroyImageView(Device, SwapchainImageView, nullptr);
	VkDestroyRenderPass(Device, RenderPass, nullptr);
}

void DestroyBackGround(){
	VkDestroySemaphore(Device, Semaphore, nullptr);
	VkDestroyCommandBuffers(Device, CommandPool);
	VkDestroyCommandPool(Device, CommandPool, nullptr);
	VkDestroyImage(Device, SwapchainImage, nullptr);
	//VkDestroySwapchain(Device, Swapchain, nullptr);
	VkDestroySurface(Instance, Surface, nullptr);
}

void DestroyVulkan() {
	VkDestroyDevice(Device, nullptr);
	VkDestroyInstance(Instance, nullptr);
}

LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (uMsg) {

	case WM_CREATE:
		CreateVulkan();
		break;

	case WM_PAINT:
		DrawBackGround();
		DrawPrimitive();
		break;

	case WM_DESTROY:
		DestroyPrimitive();
		DestroyBackGround();
		DestroyVulkan();
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
