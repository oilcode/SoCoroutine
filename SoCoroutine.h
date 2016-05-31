//------------------------------------------------------------
#ifndef _SoCoroutine_h_
#define _SoCoroutine_h_
//------------------------------------------------------------
enum SoCoroutineObjType
{
	SoCoroutineObjType_None, //SoCoroutine::m_pObjFunc的值为SoCoroutineFuncPointer。
	//<<<<<<<<<<<<<<<<<<<<<<<<<< user define <<<<<<<<<<<<<
	SoCoroutineObjType_Test, //SoCoroutine::m_pObjFunc的值为TestClass类对象的指针。
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//------------------------------------------------------------
#define SoCoroutineCreate(pParam)           SoCoroutineManager::Get()->CreateCoroutine(pParam)
#define SoCoroutineDelete(ppCo)             SoCoroutineManager::Get()->DeleteCoroutine(ppCo);
#define SoCoroutineBegin(pCo)               pCo->m_nStatus = SoCoroutineStatus_Running; switch (pCo->m_nLineNum) { case 0:
#define SoCoroutineEnd(pCo)                 }; pCo->m_nStatus = SoCoroutineStatus_End;
#define SoCoroutineYield(pCo)               do { pCo->m_nStatus = SoCoroutineStatus_Suspend; pCo->m_nLineNum = __LINE__; return; case __LINE__:; } while (0);
#define SoCoroutineResume(pCo)              pCo->m_nStatus = SoCoroutineStatus_Running; pCo->CallFunc();
#define SoCoroutineWait(pCo, fWaitTime)     pCo->m_fRemainWaitTime = fWaitTime; SoCoroutineYield(pCo);
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
class SoCoroutine
{
public:
	//如果m_nObjType值为SoCoroutineObjType_None，则m_pObjFunc值为SoCoroutineFuncPointer；
	//否则，m_nObjType值为类对象的指针。
	void* m_pObjFunc;
	void* m_pUserData;
	int m_nStatus;
	int m_nLineNum;
	int m_nObjType;
	float m_fRemainWaitTime;
	//
	SoCoroutine();
	void Clear();
	void CallFunc();
};
//------------------------------------------------------------
typedef void (*SoCoroutineFuncPointer)(SoCoroutine* pCo);
//------------------------------------------------------------
//------------------------------------------------------------
#include "SoArrayUID.h"
//------------------------------------------------------------
struct SoCoroutineParam
{
	void* pObjFunc;
	void* pUserData;
	int nObjType;
};
//------------------------------------------------------------
class SoCoroutineManager
{
public:
	static bool CreateCoroutineManager();
	static void ReleaseCoroutineManager();
	static SoCoroutineManager* Get();

	void UpdateCoroutineManager(float fDeltaTime);
	SoCoroutine* CreateCoroutine(const SoCoroutineParam* pParam);
	void DeleteCoroutine(SoCoroutine** ppCo);

private:
	SoCoroutineManager();
	~SoCoroutineManager();
	bool InitCoroutineManager();
	void ClearCoroutineManager();
	SoCoroutine* FindEmptyElement();

private:
	static SoCoroutineManager* ms_pInstance;
	SoArrayUID m_kArray;
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
