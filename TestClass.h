//------------------------------------------------------------
#ifndef _TestCoClass_h_
#define _TestCoClass_h_
//------------------------------------------------------------
class SoCoroutine;
//------------------------------------------------------------
struct CoParam
{
	float fWaitTime;
	float fPrintNum;
};
//------------------------------------------------------------
class TestClass
{
public:
	typedef void (TestClass::*CoFuncPointer)(SoCoroutine* pCo);

	void ProcessCo(SoCoroutine* pCo);

};
//------------------------------------------------------------
#endif //_TestCoClass_h_
//------------------------------------------------------------
