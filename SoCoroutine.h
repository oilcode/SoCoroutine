//------------------------------------------------------------
#ifndef _SoCoroutine_h_
#define _SoCoroutine_h_
//------------------------------------------------------------
#define SoCoroutineCreate(pFunc, pUserData) SoCoroutineManager::Get()->CreateCoroutine(pFunc, pUserData)
#define SoCoroutineDelete(ppCo)             SoCoroutineManager::Get()->DeleteCoroutine(ppCo);
#define SoCoroutineBegin(pCo)               pCo->m_nStatus = SoCoroutineStatus_Running; switch (pCo->m_nLineNum) { case 0:
#define SoCoroutineEnd(pCo)                 }; pCo->m_nStatus = SoCoroutineStatus_End;
#define SoCoroutineYield(pCo)               do { pCo->m_nStatus = SoCoroutineStatus_Suspend; pCo->m_nLineNum = __LINE__; return; case __LINE__:; } while (0);
#define SoCoroutineResume(pCo)              pCo->m_nStatus = SoCoroutineStatus_Running; pCo->m_pFunc(pCo);
#define SoCoroutineWait(pCo, fWaitTime)     pCo->m_fRemainWaitTime = fWaitTime; SoCoroutineYield(pCo);
//------------------------------------------------------------
#include "SoArray.h"
//------------------------------------------------------------
enum SoCoroutineStatus
{
	SoCoroutineStatus_Begin,
	SoCoroutineStatus_Running,
	SoCoroutineStatus_Suspend,
	SoCoroutineStatus_End,
	SoCoroutineStatus_Dead,
};
//------------------------------------------------------------
class SoCoroutine;
typedef void (*SoCoroutineFuncPointer)(SoCoroutine* pCo);
//------------------------------------------------------------
class SoCoroutine
{
public:
	int m_nStatus;
	int m_nLineNum;
	float m_fRemainWaitTime;
	SoCoroutineFuncPointer m_pFunc;
	void* m_pUserData;
	//
	SoCoroutine()
	{
		Clear();
	}
	void Clear()
	{
		m_nStatus = SoCoroutineStatus_Dead;
		m_nLineNum = 0;
		m_fRemainWaitTime = -1.0f;
		m_pFunc = 0;
		m_pUserData = 0;
	}
};
//------------------------------------------------------------
class SoCoroutineManager
{
public:
	static bool CreateCoroutineManager();
	static void ReleaseCoroutineManager();
	static SoCoroutineManager* Get();

	void UpdateCoroutineManager(float fDeltaTime);
	SoCoroutine* CreateCoroutine(SoCoroutineFuncPointer pFunc, void* pUserData);
	void DeleteCoroutine(SoCoroutine** ppCo);

private:
	SoCoroutineManager();
	~SoCoroutineManager();
	bool InitCoroutineManager();
	void ClearCoroutineManager();
	SoCoroutine* FindEmptyElement();

private:
	static SoCoroutineManager* ms_pInstance;
	SoArray m_kArray;
	int m_nCountOfUndeadCoroutine;
};
//------------------------------------------------------------
inline SoCoroutineManager* SoCoroutineManager::Get()
{
	return ms_pInstance;
}
//------------------------------------------------------------
#endif //_SoCoroutine_h_
//------------------------------------------------------------
