//----------------------------------------------------------------
#include <Windows.h>
#include <cstdio>
#include "SoCoroutine.h"
//----------------------------------------------------------------
#define Time_Interval 1
#define Time_Max 20
//----------------------------------------------------------------
struct CoParam
{
	float fWaitTime;
	float fPrintNum;
};
//----------------------------------------------------------------
void testCo(SoCoroutine* pCo)
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
//----------------------------------------------------------------
void main()
{
	SoCoroutineManager::CreateCoroutineManager();
	CoParam kParamA;
	kParamA.fWaitTime = 5.5f;
	kParamA.fPrintNum = 555.0f;
	CoParam kParamB;
	kParamB.fWaitTime = 8.5f;
	kParamB.fPrintNum = 888.0f;

	//
	testCo(SoCoroutineCreate(testCo, &kParamA));
	testCo(SoCoroutineCreate(testCo, &kParamB));

	float fAccTime = 0.0f;
	bool bRunning = true;
	while (bRunning)
	{
		Sleep(Time_Interval*1000);
		fAccTime += (float)Time_Interval;
		SoCoroutineManager::Get()->UpdateCoroutineManager((float)Time_Interval);
		printf("%.2f\n", fAccTime);
		//
		if (fAccTime > Time_Max)
		{
			bRunning = false;
		}
	}

	SoCoroutineManager::ReleaseCoroutineManager();
}
//----------------------------------------------------------------
