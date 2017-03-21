#include "Macros.h"

InitializationVulkanAPI::InitializationVulkanAPI() {
	CreateExtension();
	CreateInstance();
	EnumeratePhysicalDevices();
	GetPhysicalDeviceQueueFamilyProperties();
	CreateDevice();
}

InitializationVulkanAPI::~InitializationVulkanAPI() {
	DestroyDevice();
	DestroyInstance();
}

void InitializationVulkanAPI::CreateExtension() {
	InstanceExtension.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	InstanceExtension.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	DeviceExtension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

void InitializationVulkanAPI::CreateInstance() {
	VkApplicationInfo ApplicationInfo{};
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo InstanceCreateInfo{};
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledExtensionCount = (uint32_t)InstanceExtension.size();
	InstanceCreateInfo.ppEnabledExtensionNames = InstanceExtension.data();

	vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance);
}

void InitializationVulkanAPI::DestroyInstance() {
	vkDestroyInstance(Instance, nullptr);
}

void InitializationVulkanAPI::EnumeratePhysicalDevices() {
	uint32_t PhysicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
	vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
	PhysicalDevice = PhysicalDeviceList[0];
}

void InitializationVulkanAPI::GetPhysicalDeviceQueueFamilyProperties() {
	uint32_t QueueFamilyPropertiesCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertiesCount, nullptr);
	std::vector<VkQueueFamilyProperties>QueueFamilyPropertiesList(QueueFamilyPropertiesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyPropertiesCount, QueueFamilyPropertiesList.data());
	for (uint32_t i = 0; i < QueueFamilyPropertiesCount; ++i)
		if ((QueueFamilyPropertiesList[i].queueCount > 0) && (QueueFamilyPropertiesList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
			QueueFamilyIndex = i;
}

void InitializationVulkanAPI::CreateDevice() {
	float QueuePriorities[]{ 1.0f };
	VkDeviceQueueCreateInfo DeviceQueueCreateInfo{};
	DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	DeviceQueueCreateInfo.queueFamilyIndex = QueueFamilyIndex;
	DeviceQueueCreateInfo.queueCount = 1;
	DeviceQueueCreateInfo.pQueuePriorities = QueuePriorities;
	
	VkDeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;
	DeviceCreateInfo.enabledExtensionCount = (uint32_t)DeviceExtension.size();
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtension.data();

	vkCreateDevice(PhysicalDevice, &DeviceCreateInfo, nullptr, &Device);
}

void InitializationVulkanAPI::DestroyDevice() {
	vkDestroyDevice(Device, nullptr);
}
