//------------------------------------------------------------
#include "TestClass.h"
#include "SoCoroutine.h"
#include <cstdio>
//------------------------------------------------------------
void TestClass::ProcessCo(SoCoroutine* pCo)
{
	CoParam* pParam = (CoParam*)pCo->m_pUserData;
	SoCoroutineBegin(pCo);
	SoCoroutineWait(pCo, pParam->fWaitTime);
	printf("my num %.2f\n", pParam->fPrintNum);
	SoCoroutineWait(pCo, pParam->fWaitTime);
	printf("my num %.2f\n", pParam->fPrintNum);
	SoCoroutineEnd(pCo);
	SoCoroutineDelete(&pCo);
}
//------------------------------------------------------------
