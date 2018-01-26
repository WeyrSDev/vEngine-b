#pragma once
#include "vInclude.h"

namespace vEngine {
	class BufferContainer {
	public:
		BufferContainer();
	private:
		BufferContainer(const BufferContainer& rhs);
		BufferContainer& operator=(const BufferContainer& rhs);
	public:
		ID3D11Buffer* Buffer();
		void SetBuffer(ID3D11Buffer* buffer);
		UINT ElementCount() const;
		void SetElementCount(UINT elementCount);
		void ReleaseBuffer();
	private:
		ID3D11Buffer* mBuffer;
		UINT mElementCount;
	};
}