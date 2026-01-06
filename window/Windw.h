#pragma once

#include<Windows.h>
#include<string>

class Windw final
{
public:
	static Windw& instance() noexcept
	{
		static Windw instance_;
		return instance_;
	}

	HRESULT create(HINSTANCE instance, int height, std::string_view name) noexcept;


	bool messageLoop() const noexcept;

	HWND handle() const noexcept;


	std::pair<int, int> size() const noexcept;

private:

	Windw() = default;
	~Windw() = default;

	Windw(const Windw& r) = delete;
	Windw& operator=(const Windw& r) = delete;
	Windw(Windw&& r) = delete;
	Windw& operator=(Windw&& r) = delete;

private:
	HWND handle_{};
	int width_{};
	int height_{};
};