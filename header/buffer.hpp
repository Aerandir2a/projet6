#pragma once

#include "../gc_3d_defs.hpp"

class Buffer
{
	unsigned int m_buffer;
	int attribut;

public:
	void CreateBuffer(const void* iData, size_t iSize);
	template<typename T>
	void CreateBuffer(std::vector<T> const& iData)
	{
		return CreateBuffer(iData.data(), sizeof(T)*iData.size());
	}
	void BindBuffer(int attribut, int iSize);

};