# SoCoroutine
这是一个使用“switch-case”实现的轻量级的原语级别的风骚的令人惊叹的协程库<br>
我学习了大牛的方法，用自己理解的方式进行了封装。版权属于大牛。仅供学习。<br>
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
// SoCoroutineDelete(&pCo)<br>
<br>
在 main.cpp 中有完整示例。<br>
<br>
编译方法：<br>
由于使用了违背编程规范的邪恶的宏（主要是指宏的展开代码），VisualStudio的debug模式会编译失败。<br>
修改项目属性即可解决：<br>
Propertys -> C/C++ -> General -> Debug Information Format : 把默认的 Program Database for Edit & Continue (/ZI) 修改成 Program Database (/Zi)。<br>
<br>

<br>暂且把这种基于达夫设备（Duff's Device）的使用switch-case语句实现的协程称作无栈协程，其他的协程称作有栈协程。
<br>
<br>有些游戏服务器会这样做，通过共享内存实现了一种resume的机制，将状态数据存放在共享内存中，游戏进程crash后再次重启attach原共享内存，所有状态得到恢复，玩家不受影响。
<br>resume机制使游戏容灾能力得到很大程度的提升，但同时也让上文所述的普通协程失去了作用，主要有以下两点原因：
<br>（1）resume后栈基地址、堆基地址等发生了变化，寄存器上下文中保存的地址将会失效；
<br>（2）协程栈内用户使用的指针也将失效；
<br>
<br>无栈协程成功的解决了普通有栈协程在resume失效的问题，同有栈协程相比，优点：
<br>   1、切换时，不涉及内核态切换，类似于普通函数调用效率更高。
<br>   2、不用考虑有栈协程中的由于栈开辟空间太小导致的栈溢出的问题。
<br>   3、代码小巧，跨平台。
<br>缺点：
<br>   由于其不保存上下文，函数栈内的临时变量都不会保存，只能依赖传递的参数再次恢复数据。
<br>
