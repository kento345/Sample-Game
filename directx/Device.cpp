#include "Device.h"
#include<cassert>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

bool Device::create() noexcept {
	if(!dxgiInstance_.setDisplayAdapter()) {
		assert(false && "DXGIのアダプター設定に失敗しました");
		return false;
	}

	const auto hr = D3D12CreateDevice(dxgiInstance_.displayAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
	if(FAILED(hr)) {
		assert(false && "デバイスの作成に失敗しました");
		return false;
	}

	return true;
}

ID3D12Device* Device::get() const noexcept {
	if (!device_) {
		assert(false && "デバイスが未作成です");
	}

	return device_.Get();
}	

const DXGI& Device::dxgi() const noexcept {
	return dxgiInstance_;
}