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
	VkQueueSubmit(Queue, 1, &SubmitInfo, nullptr);
	VkQueuePresent(Queue, &PresentInfo);
}

void DrawPrimitive() {
	VkCreateRenderPass(Device, &RenderPassCreateInfo, nullptr, &RenderPass);
	VkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &SwapchainImageView);
	VkCreateFramebuffer(Device, &FramebufferCreateInfo, nullptr, &FrameBuffer);
	//VkCreateShaderModule(Device, &ShaderModuleCreateInfo, nullptr, &ShaderModule);
	VkCreatePipelineLayout(Device, &PipelineLayoutCreateInfo, nullptr, &PipelineLayout);
	VkCreateGraphicsPipelines(Device, nullptr, 1, &GraphicsPipelineCreateInfo, nullptr, &Pipeline);
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
	//VkDestroyImage(Device, SwapchainImage, nullptr);
	VkDestroySwapchain(Device, Swapchain, nullptr);
	VkDestroySurface(Instance, Surface, nullptr);
}

void DestroyVulkan() {
	VkDestroyDevice(Device, nullptr);
	VkDestroyInstance(Instance, nullptr);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	case WM_CREATE:
		CreateVulkan();
		Win32SurfaceCreateInfoStructure(reinterpret_cast<CREATESTRUCT *>(lParam)->hInstance, hWnd);
		break;

	case WM_PAINT:
		DrawBackGround();
		DrawPrimitive();
		break;

	case WM_CLOSE:
		DestroyPrimitive();
		DestroyBackGround();
		DestroyVulkan();
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	BOOL bRet;
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!hPrevInstance) {
		WNDCLASS MainWndClass = {
			0,
			(WNDPROC)WindowProc,
			0,
			0,
			hInstance,
			LoadIcon((HINSTANCE)NULL, IDI_APPLICATION),
			LoadCursor((HINSTANCE)NULL, IDC_ARROW),
			(HBRUSH)NULL,
			"MainMenu",
			"MainWndClass"
		};
		if (!RegisterClass(&MainWndClass)) return FALSE;
	}

	HWND hWnd = CreateWindow("MainWndClass", "vkLiteSDK v0.1b",
		WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXSCREEN) - 1024) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 576) / 2,
		1024, 576, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) exit(-1);
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);
}
