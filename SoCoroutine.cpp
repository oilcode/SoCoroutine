//------------------------------------------------------------
/* The credit belongs to Tom Duff , Simon Tatham and zhicheng */
//http://coolshell.cn/articles/10975.html
//https://github.com/zhicheng/coroutine
//这是一个使用“switch-case”实现的轻量级的原语级别的风骚的令人惊叹的协程库。
//支持跨平台。支持函数重入（Re-entrant）。
//对多线程的支持情况，未知。
//由于这个协程库的实现方法异常简单，所以在使用时有一些注意事项：
//1，尽量在 SoCoroutineFuncPointer 函数的开始处调用 SoCoroutineBegin ，在该函数的末尾处调用 SoCoroutineEnd ，
//   也即，让 SoCoroutineBegin-SoCoroutineEnd 函数对把 SoCoroutineFuncPointer 包裹住。
//2，禁止在同一行代码里面调用两次或者多次 SoCoroutineYield 。
//
//下面的伪代码展示了使用方法：
// SoCoroutine* pCo = SoCoroutineCreate()
// ...
//    void testCo(SoCoroutine* pCo)
//    {
//      //<<<<<<<<<<<<<<<<<<<<<<<
//      //在 SoCoroutineBegin 函数之前的代码块，每次执行本函数都会执行一次。
//      //>>>>>>>>>>>>>>>>>>>>>>>
//      //<<<<<<<<<<<<<<<<<<<<<<<
//      //从 SoCoroutineBegin 函数开始到本函数末尾，在pCo生命期内只执行一次。
//      SoCoroutineBegin(pCo);
//      ...
//      SoCoroutineYield(pCo);
//      ...
//      SoCoroutineEnd(pCo);
//      //>>>>>>>>>>>>>>>>>>>>>>>
//    }
// ...
//    other code invote SoCoroutineResume(pCo)
// ...
// SoCoroutineDelete(pCo)
//------------------------------------------------------------
#include "SoCoroutine.h"
//------------------------------------------------------------
SoCoroutineManager* SoCoroutineManager::ms_pInstance = 0;
//------------------------------------------------------------
bool SoCoroutineManager::CreateCoroutineManager()
{
	bool br = true;
	if (ms_pInstance == 0)
	{
		ms_pInstance = new SoCoroutineManager;
		if (ms_pInstance && ms_pInstance->InitCoroutineManager())
		{
			br = true;
		}
		else
		{
			ReleaseCoroutineManager();
			br = false;
		}
	}
	return br;
}
//------------------------------------------------------------
void SoCoroutineManager::ReleaseCoroutineManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//----------------------------------------------------------------
SoCoroutineManager::SoCoroutineManager()
{

}
//----------------------------------------------------------------
SoCoroutineManager::~SoCoroutineManager()
{
	ClearCoroutineManager();
}
//----------------------------------------------------------------
bool SoCoroutineManager::InitCoroutineManager()
{
	if (m_kArray.InitArray(sizeof(SoCoroutine), 10, 10) == false)
	{
		return false;
	}
	return true;
}
//------------------------------------------------------------
void SoCoroutineManager::ClearCoroutineManager()
{
	m_kArray.Clear();
}
//------------------------------------------------------------
void SoCoroutineManager::UpdateCoroutineManager(float fDeltaTime)
{
	const int nCount = m_kArray.GetCount();
	if (nCount > 0)
	{
		SoCoroutine* pCo = 0;
		for (int i = 0; i < nCount; ++i)
		{
			pCo = (SoCoroutine*)m_kArray.GetElement(i);
			if (pCo)
			{
				if (pCo->m_nStatus == SoCoroutineStatus_Suspend)
				{
					if (pCo->m_fRemainWaitTime > 0.0f)
					{
						pCo->m_fRemainWaitTime -= fDeltaTime;
						if (pCo->m_fRemainWaitTime <= 0.0f)
						{
							pCo->m_fRemainWaitTime = -1.0f;
							SoCoroutineResume(pCo);
						}
					}
				}
			}
		}
	}
}
//------------------------------------------------------------
SoCoroutine* SoCoroutineManager::CreateCoroutine(SoCoroutineFuncPointer pFunc, void* pUserData)
{
	SoCoroutine* pCo = FindEmptyElement();
	if (pCo == 0)
	{
		SoCoroutine kCo;
		const int nIndex = m_kArray.PushBack(&kCo);
		pCo = (SoCoroutine*)m_kArray.GetElement(nIndex);
	}
	if (pCo)
	{
		pCo->m_nStatus = SoCoroutineStatus_Ready;
		pCo->m_pFunc = pFunc;
		pCo->m_pUserData = pUserData;
	}
	return pCo;
}
//------------------------------------------------------------
void SoCoroutineManager::DeleteCoroutine(SoCoroutine* pCo)
{
	if (pCo)
	{
		pCo->Clear();
	}
}
//------------------------------------------------------------
SoCoroutine* SoCoroutineManager::FindEmptyElement()
{
	SoCoroutine* pCo = 0;
	SoCoroutine* pTemp = 0;
	const int nCount = m_kArray.GetCount();
	for (int i = 0; i < nCount; ++i)
	{
		pTemp = (SoCoroutine*)m_kArray.GetElement(i);
		if (pTemp->m_nStatus == SoCoroutineStatus_Dead)
		{
			pCo = pTemp;
			break;
		}
	}
	return pCo;
}
//------------------------------------------------------------
