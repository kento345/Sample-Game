#pragma once

#include"Device.h"
#include"CommandAllocator.h"

class CommandList final
{
public:
	CommandList() = default;
	~CommandList() = default;

	bool create(const CommandAllocator& commandAllocator)noexcept;

	void reset(const CommandAllocator& commandAllocator)noexcept;

	ID3D12GraphicsCommandList* get()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList_{};
};

