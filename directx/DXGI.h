#pragma once

#include<d3d12.h>
#include<dxgi1_4.h>
#include<wrl/client.h>

class DXGI final
{
public:
	DXGI() = default;
	~DXGI() = default;

	bool setDisplayAdapter() noexcept;

	IDXGIFactory4* factory() const noexcept;

	IDXGIAdapter1* displayAdapter() const noexcept;
private:
	Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory_{};
	Microsoft::WRL::ComPtr<IDXGIAdapter1> dxgiAdapter_{};
};

