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
	VkBeginCommandBuffer(CommandBuffer[0], &CommandBufferBeginInfo);
	VkCmdClearColorImage(CommandBuffer[0], SwapchainImage[0], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&ClearColorValue, 1, &ImageSubresourceRange);
	VkEndCommandBuffer(CommandBuffer[0]);
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
