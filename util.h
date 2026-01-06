#pragma once

#include<basetsd.h>

namespace id {
	template<class T>
	UINT64 get()noexcept {
		static char valu{};
		return reinterpret_cast<UINT64>(&valu);
	}
}


