#pragma once

#include"Device.h"

class DepthBuffer
{
public:
	DepthBuffer() = default;
	~DepthBuffer();

	bool create()noexcept;

	ID3D12Resource* depthBuffer()const noexcept;

	D3D12_CPU_DESCRIPTOR_HANDLE getCpuDescriptorHandle()const noexcept;

private:
		Microsoft::WRL::ComPtr<ID3D12Resource>depthBuffer_{};
		D3D12_CPU_DESCRIPTOR_HANDLE handle_{};
};

