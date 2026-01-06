#include "DescriptorHeap.h"
#include"Device.h"
#include<cassert>
#include<wrl//client.h>


class DescriptorHeap final
{
public:
	DescriptorHeap() = default;

	~DescriptorHeap() = default;

public:

	bool create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = type;
		heapDesc.NumDescriptors = numDescriptors;
		heapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		heapDesc.NodeMask = 0;

		type_ = type;

		HRESULT hr = Device::instance().get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap_));
		if (FAILED(hr))
		{
			assert(false && "ディスクリプターヒープの生成に失敗しました");
			return false;
		}

		maxDescriptorCount_ = numDescriptors;
		for (UINT i = 0; i < maxDescriptorCount_; ++i)
		{
			freeIndices_.push_back(i);
		}

		return true;
	}

	void applyPendingFree() noexcept
	{
		if (pendingFreeIndices_.empty()) {
			return;
		}

		for (auto i : pendingFreeIndices_)
		{
			freeIndices_.push_back(i);
		}
		pendingFreeIndices_.clear();
	}

	ID3D12DescriptorHeap* get()const noexcept {
		if (!heap_) {
			assert(false && "ディスクリプターヒープが未作成です");
		}
		return heap_.Get();
	}

	D3D12_DESCRIPTOR_HEAP_TYPE getType()const noexcept {
		if(!heap_) {
			assert(false && "ディスクリプターヒープが未作成です");
		}
		return type_;
	}

	std::optional<UINT> allocaterDescriptor() noexcept
	{
		if (freeIndices_.empty()) {
			return std::nullopt;
		}
		const auto index = freeIndices_.back();
		freeIndices_.pop_back();
		return index;
	}

	void releaseDescriptor(UINT descriptorIndex) noexcept
	{
		pendingFreeIndices_.push_back(descriptorIndex);
	}

private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap_{};
	D3D12_DESCRIPTOR_HEAP_TYPE type_{};
	UINT maxDescriptorCount_{};
	std::vector<UINT> freeIndices_{};
	std::vector<UINT> pendingFreeIndices_{};
};

DescriptorHeapContainer::DescriptorHeapContainer() = default;

DescriptorHeapContainer::~DescriptorHeapContainer() {
	map_.clear();
}


bool DescriptorHeapContainer::create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT nuumDescriptors, bool shaderVisible) noexcept
{
	if(map_.find(type) != map_.end()) {
		return false;
	}

	auto p = std::make_unique<DescriptorHeap>();
	if (p->create(type, nuumDescriptors, shaderVisible)) {
		map_.emplace(type, std::move(p));
	}

	return true;
}

void DescriptorHeapContainer::applyPendingFree() noexcept
{
	for (auto& [key, p] : map_)
	{
		p->applyPendingFree();
	}
}

ID3D12DescriptorHeap* DescriptorHeapContainer::get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept
{
	const auto it = map_.find(type);
	if (it == map_.end()) {
		assert(false && "ディスクリプターヒープがありません");
		return nullptr;
	}
	return it->second->get();
}

std::optional<UINT>DescriptorHeapContainer::allocaterDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept
{
	const auto it = map_.find(type);
	if (it == map_.end()) {
		assert(false && "ディスクリプターヒープがありません");
		return std::nullopt;
	}
	return it->second->allocaterDescriptor();
}

void DescriptorHeapContainer::releaseDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorIndex) noexcept
{
	const auto it = map_.find(type);
	if (it == map_.end()) {
		assert(false && "ディスクリプターヒープがありません");
	}
	return it->second->releaseDescriptor(descriptorIndex);
}