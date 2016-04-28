//----------------------------------------------------------------
#ifndef _SoArray_h_
#define _SoArray_h_
//----------------------------------------------------------------
class SoArray
{
public:
	SoArray();
	~SoArray();
	//初始化函数。也可以作为清零重置函数，把一个旧数组重置成新数组。
	//--nElementSize 元素大小，即对元素执行sizeof运算得到的返回值。
	//--nInitCount 初始时的最大元素个数，也即预分配的内存能够容纳多少个元素。
	//--nAddCount 当数组元素已满，预分配更大内存时，新增加的内存能够容纳多少个元素。
	bool InitArray(int nElementSize, int nInitCount, int nAddCount);
	//返回值为新元素的位置序号。
	int PushBack(const void* pElement);
	bool InsertAt(int nIndex, const void* pElement);
	bool SwapElement(int nIndexA, int nIndexB);
	void* GetElement(int nIndex) const;
	//删除所有的元素。m_pBuff不会重新分配。
	void Clear();
	int GetCount() const;

private:
	bool Resize(int nMaxCount);

private:
	char* m_pBuff;
	int m_nMaxCount;
	int m_nCurrentCount;
	int m_nElementSize;
	int m_nAddCount;
};
//----------------------------------------------------------------
inline void* SoArray::GetElement(int nIndex) const
{
	if (m_pBuff && nIndex >= 0 && nIndex < m_nMaxCount)
	{
		return (m_pBuff + nIndex * m_nElementSize);
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------
inline void SoArray::Clear()
{
	m_nCurrentCount = 0;
}
//----------------------------------------------------------------
inline int SoArray::GetCount() const
{
	return m_nCurrentCount;
}
//----------------------------------------------------------------
#endif //_SoArray_h_
//----------------------------------------------------------------
