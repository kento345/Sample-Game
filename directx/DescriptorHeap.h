#pragma once

#include<d3d12.h>
#include<unordered_map>
#include<optional>
#include<memory>

class DescriptorHeap;

class DescriptorHeapContainer final
{
public:

	static DescriptorHeapContainer& instance() noexcept
	{
		static DescriptorHeapContainer instance;
		return instance;
	}


	bool create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT nuumDescriptors, bool shaderVisible = false) noexcept;


	void applyPendingFree() noexcept;

	ID3D12DescriptorHeap* get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept;


	std::optional<UINT>allocaterDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	void releaseDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorIndex) noexcept;


private:
	DescriptorHeapContainer();
	~DescriptorHeapContainer();

	DescriptorHeapContainer(const DescriptorHeapContainer& r) = delete;
	DescriptorHeapContainer& operator=(const DescriptorHeapContainer& r) = delete;
	DescriptorHeapContainer(DescriptorHeapContainer&& r) = delete;
	DescriptorHeapContainer& operator=(DescriptorHeapContainer&& r) = delete;

private:
	std::unordered_map<UINT, std::unique_ptr<DescriptorHeap>> map_{};
};

