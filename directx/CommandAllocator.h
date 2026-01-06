#pragma once

#include"Device.h"

class CommandAllocator final
{
public:
	CommandAllocator() = default;
	~CommandAllocator() = default;

	bool create(const D3D12_COMMAND_LIST_TYPE type) noexcept;

	void reset() noexcept;

	ID3D12CommandAllocator* get() const noexcept;

	D3D12_COMMAND_LIST_TYPE getType() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator_{};
	D3D12_COMMAND_LIST_TYPE type_{};
};

