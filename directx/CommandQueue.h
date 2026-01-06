#pragma once

#include"Device.h"

class CommandQueue
{
public:
	CommandQueue() = default;
	~CommandQueue() = default;

	bool create() noexcept;

	ID3D12CommandQueue* get() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>commandQueue_{};
};

