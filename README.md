# SoCoroutine
这是一个使用“switch-case”实现的轻量级的原语级别的风骚的令人惊叹的协程库<br>
我学习了大牛的方法，用自己理解的方式进行了封装。仅供学习。<br>
/* The credit belongs to Tom Duff , Simon Tatham and zhicheng */<br>
//http://coolshell.cn/articles/10975.html<br>
//https://github.com/zhicheng/coroutine<br>
//支持跨平台。支持函数重入（Re-entrant）。<br>
//对多线程的支持情况，未知。<br>
//由于这个协程库的实现方法异常简单，所以在使用时有一些注意事项：<br>
//1，尽量在 SoCoroutineFuncPointer 函数的开始处调用 SoCoroutineBegin ，在该函数的末尾处调用 SoCoroutineEnd ，<br>
//   也即，让 SoCoroutineBegin-SoCoroutineEnd 函数对把 SoCoroutineFuncPointer 包裹住。<br>
//2，禁止在同一行代码里面调用两次或者多次 SoCoroutineYield 。<br>
//<br>
//下面的伪代码展示了使用方法：<br>
// SoCoroutine* pCo = SoCoroutineCreate()<br>
// ...<br>
//    void testCo(SoCoroutine* pCo)<br>
//    {<br>
//      //<<<<<<<<<<<<<<<<<<<<<<<<br>
//      //在 SoCoroutineBegin 函数之前的代码块，每次执行本函数都会执行一次。<br>
//      //>>>>>>>>>>>>>>>>>>>>>>><br>
//      //<<<<<<<<<<<<<<<<<<<<<<<<br>
//      //从 SoCoroutineBegin 函数开始到本函数末尾，在pCo生命期内只执行一次。<br>
//      SoCoroutineBegin(pCo);<br>
//      ...<br>
//      SoCoroutineYield(pCo);<br>
//      ...<br>
//      SoCoroutineEnd(pCo);<br>
//      //>>>>>>>>>>>>>>>>>>>>>>><br>
//    }<br>
// ...<br>
//    other code invote SoCoroutineResume(pCo)<br>
// ...<br>
// SoCoroutineDelete(pCo)<br>
<br>

