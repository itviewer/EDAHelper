// EDAHelperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EDAHelper.h"
#include "EDAHelperDlg.h"
#include "Hook.h"
#include "Update.h"
#include "MyPropertySheet.h"
#include "MyPropertyPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  MYWM_NOTIFYICON  WM_USER+1


/////////////////////////////////////////////////////////////////////////////
// CEDAHelperDlg dialog

static TCHAR	*AppDesc = 
_T("2.1.13说明：\r\n")
_T("    本软件是多种EDA软件的鼠标增强工具，绿色单文件，支持Win9x/NT/2000/XP/WIN7，其中WIN7需要以管理员模式运行，")
_T("另外，Win9x需要编译成非UNICODE版本，有需要的用户可发邮件给我索取，支持protel99se，DXP(AD)，PADS，OrCAD的capture、")
_T("Cam350、Saber、PC Schematic、Allegro、CircuitCAM,并且对每个软件的功能都可设置，用户可根据使用习惯打开或者关闭功能。\r\n")
_T("    软件启动时和启动后每隔24小时检查更新，如果系统能上网，有更新时会有增量更新信息。\r\n")
_T("\r\n针对protel99se, DXP,Altium Designer：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于PageUp(不能改掉软件原来的快捷键，否则就不灵了)\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于PageDown(不能改掉软件原来的快捷键，否则就不灵了)\r\n")
_T("    3. 按下滚轮     --> 切换有效图层并刷新，相当于小键盘'*'的功能\r\n")
_T("    4. 按左键拖目标 --> 再按右键可旋转，相当于空格键的功能，在布局时非常好用，请留意\r\n")
_T("    5. 按右键拖动屏幕\r\n")
_T("    6. 原理图里单击中键呼出放置菜单，相当于按“P”键1次，连按两次相当于直接放置元件\r\n")
_T("    7. 按中键向左移动撤消操作，相当于ALT+Backspace\r\n")
_T("    8. 按中键向右移动重做操作，相当于CTRL+Backspace\r\n")
_T("    9. 按中键向上移动，画线时删除上一次操作，相当于按Backspace\r\n")
_T("    10.按中键向下移动，可删除当前焦点或选中内容，相当于按DELETE和CTRL+DELETE\r\n")
_T("\r\n针对PADS(支持各种版本logic, pcb)：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于PageUp\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于PageDown\r\n")
_T("    3. 按住鼠标右键移动，可移动工作区\r\n")
_T("    4. 鼠标中键点击 --> 切换图层，相当于F4，原中键点击功能废弃\r\n")
_T("    5. 按左键拖目标 --> 再按右键可旋转，相当于TAB键的功能，在布局时非常好用，请留意\r\n")
_T("\r\n针对OrCAD：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于字母\"I\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小相当于字母\"O\"键\r\n")
_T("    3. 按住鼠标右键移动，可移动工作区\r\n")
_T("    4. 按中键呼出放置窗口的功能，相当于按“P”键1次\r\n")
_T("    5. 按中键向左移动撤消操作，相当于按CTRL+Z\r\n")
_T("    6. 按中键向右移动重做操作，相当于按CTRL+Y\r\n")
_T("    7. 按中键向上移动，进入画线操作，相当于按W键\r\n")
_T("    8. 按中键向下移动，删除选中内容，相当于按DELETE键\r\n")
_T("\r\n针对Cam350：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于\"PageUp\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于\"PageDown\"键\r\n")
_T("    3. 按住鼠标右键移动，可移动工作区\r\n")
_T("    4. 修改原中键功能，按中键放开，连续按两次显示视图全部，单次相当于按“HOME”键再中键点击的效果\r\n")
_T("    5、按中键向左移动撤消操作，相当于按CTRL+Z\r\n")
_T("    6、按中键向右移动重做操作，相当于按CTRL+U\r\n")
_T("    7、按中键向上移动，呼出Aperture Table，相当于按A键\r\n")
_T("    8、按中键向下移动，删除选中内容，相当于按Edit菜单里的DELETE项\r\n")
_T("\r\n针对Saber：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于\"PageUp\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于\"PageDown\"键\r\n")
_T("\r\n针对PC Schematic(V11有测试)：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于\"PageUp\"键, 原有快捷键要改\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于\"PageDown\"键，原有快捷键要改\r\n")
_T("\r\n针对Allegro(15.7有测试，已经有中键缩放的新版本请禁止该功能)：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于\"F10\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于\"F11\"键\r\n")
_T("    3. 中键拖动反转(适合习惯AutoCAD等中键拖动的用户)\r\n")
_T("\r\n针对CircuitCAM：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于\"PageUp\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于\"PageDown\"键\r\n")
_T("    3. 按住鼠标右键移动，可移动工作区\r\n")
_T("\r\n")
_T("代码获取方法：\"svn checkout https://dbghelper.googlecode.com/svn/EDAHelper\"\r\n")

_T("\r\n更新历史：\r\n")
_T("2.1.14：\r\n")
_T("    1、修改protel99se里3D模式时缩放等失效的问题\r\n")
_T("    2、修改DXP里legacy 3D模式时缩放等失效的问题\r\n")
_T("2.1.13：\r\n")
_T("    1、修改PADS右键拖动之传统模式的BUG\r\n")
_T("    2、大大提高运行效率，解决部分用户在QQ窗口移动鼠标时会非常慢的情况\r\n")
_T("    3、修改在allegro中滚动鼠标时下面命令窗口有时会出现F10,F11字样的BUG(可能)\r\n")
_T("    4、修改CAM350右键拖动功能，使可平滑移动\r\n")
_T("2.1.12：\r\n")
_T("    1、修改程序启动24小时后再检测更新出错的问题\r\n")
_T("    2、再次修改自动运行有时候失败的问题\r\n")
_T("    3、修改非活动窗口时操作失效的问题，特别是查看自动隐藏的QQ窗口后容易出现\r\n")
_T("    4、优化PADS Router里画线时的中键换层操作，使之不再移动屏幕，同时建议把unroute的快捷键定义为F4，因为这样在选中走线的时候，按中键就可以删除\r\n")
_T("    5、修改pads右键平滑移动(可设置回传统模式)\r\n")
_T("    6、五周年纪念\r\n")
_T("    7、通过360认证(请2.1.10以前的版本升级，否则可能出现死锁)\r\n")
_T("2.1.11：\r\n")
_T("    1、修改自动运行有时候失败的问题\r\n")
_T("2.1.10：\r\n")
_T("    1、启用UNICODE编译模式，使可支持多语言NT环境操作系统，win9x系统需要编译成非UNICODE模式\r\n")
_T("    2、增加Allegro里中键拖动反转(适合习惯AutoCAD的用户)\r\n")
_T("    3、修改当explorer关闭后任务栏图标消失的BUG\r\n")
_T("    4、增加重复运行程序时弹出主窗口\r\n")
_T("    5、增加对CircuitCAM的支持\r\n")
_T("    6、修改Orcad里编译器件之后右键拖动无效的问题\r\n")
_T("    7、修改检查更新方式，使更人性化\r\n")
_T("2.1.09：\r\n")
_T("    1、修改protel里右键关闭窗口的BUG\r\n")
_T("2.1.08：\r\n")
_T("    1、修改allegro里失效的BUG\r\n")
_T("2.1.07：\r\n")
_T("    1、增加CAM350按中键向左移动撤消操作，相当于按CTRL+Z\r\n")
_T("    2、增加CAM350按中键向右移动重做操作，相当于按CTRL+U\r\n")
_T("    3、增加CAM350按中键向上移动，呼出Aperture Table，相当于按A键\r\n")
_T("    4、增加CAM350按中键向下移动，删除选中内容，相当于按Edit菜单里的DELETE项\r\n")
_T("    5、修复(2.1.06)源码里一处字符串溢出的BUG\r\n")
_T("2.1.06：\r\n")
_T("    1、增加Orcad里按中键呼出放置窗口的功能，相当于按“P”键1次\r\n")
_T("    2、增加Orcad按中键向左移动撤消操作，相当于按CTRL+Z\r\n")
_T("    3、增加Orcad按中键向右移动重做操作，相当于按CTRL+Y\r\n")
_T("    4、增加Orcad按中键向上移动，进入画线操作，相当于按W键\r\n")
_T("    5、增加Orcad按中键向下移动，删除选中内容，相当于按DELETE键\r\n")
_T("    6、增加版本号从2.1.06开始的编译次数记录\r\n")
_T("2.1.05：\r\n")
_T("    1、修改CAM350中键功能，按中键放开，显示视图全部，相当于按“HOME”键\r\n")
_T("2.1.04：\r\n")
_T("    1、增加protel系列原理图里按中键呼出放置菜单的功能，相当于按“P”键1次\r\n")
_T("    2、增加protel系列按中键向左移动撤消操作，相当于ALT+Backspace\r\n")
_T("    3、增加protel系列按中键向右移动重做操作，相当于CTRL+Backspace\r\n")
_T("    4、增加protel系列按中键向上移动，画线时删除上一次操作，相当于按Backspace\r\n")
_T("    5、增加protel系列按中键向下移动，可删除当前焦点或选中内容，相当于按DELETE和CTRL+DELETE\r\n")
_T("2.1.03：\r\n")
_T("    1、修复右键拖动移出边界放开后，拖动功能还在继续的BUG\r\n")
_T("2.1.02：\r\n")
_T("    1、增加pads里按住左键拖目标，再按右键旋转的功能\r\n")
_T("2.1.01：\r\n")
_T("    1、修改在protel的PCB里右键失效的BUG\r\n")
_T("2.1.00：\r\n")
_T("    1、重写各模块，各软件支持独立化，今后新增软件支持更容易\r\n")
_T("    2、各软件支持可设置，不用的软件可以禁止，加快软件运行速度\r\n")
_T("2.0.13：\r\n")
_T("    1、据说很多人都在用cadence 16.0以下的版本，还是加上allegro的支持吧，前提是原有的缩放功能快捷键没改(F10、F11)，16.2(F11、F12)以上的版本就不要用了，会有冲突，或者把快捷键改为F11、F12\r\n")
_T("2.0.12：\r\n")
_T("    1、增加PCSchematic的中键缩放及右键拖动，前提是原有的缩放功能快捷键要改(ctrl+home -> pageup, ctrl+end -> pagedown)\r\n")
_T("    2、修改因不能上网时自动更新引起的错误\r\n")
_T("    3、本次修改是应绵阳的一位哥们儿的要求修改的，正好是512，也是算纪念一下汶川大地震\r\n")
_T("2.0.11：\r\n")
_T("    1、增加自动检测更新\r\n")
_T("    2、修改orcad的右键移动步进，使更灵敏\r\n")
_T("    3、修改说明中一直以来的一个错别字，呵呵\r\n")
_T("    4、增加saber sketch中键缩放功能\r\n")
_T("    5、修改为单文件，去掉原来的DLL\r\n")
_T("2.0.10：\r\n")
_T("    1、修复在PADS中按住CONTROL，SHIFT，ALT键时，中键原功能失效的BUG\r\n")
_T("    2、修改在PADS中非画图窗口，鼠标功能失效的BUG\r\n")
_T("    3、增加繁体版（用WORD2003转换，不对之处请指正\r\n")
_T("    4、上传自googlecode，感兴趣的朋友可以通过svn checkout https://dbghelper.googlecode.com/svn/EDAHelper获得代码\r\n")
_T("2.0.09：\r\n")
_T("    1、修复通过双击打开powerlogic文件时，外挂功能失效问题\r\n")
_T("    2、修改中键缩放时屏幕偏移的问题\r\n")
_T("2.0.08：\r\n")
_T("    1、增加Protel99se、DXP打印预览中键缩放的支持\r\n")
_T("2.0.07：\r\n")
_T("    1、增加OrCAD右键拖动的支持\r\n")
_T("2.0.06：\r\n")
_T("    1、修正CAM350右键原功能失效的问题\r\n")
_T("2.0.05：\r\n")
_T("    1、2.0.04版本导致速度变慢，由于大部分情况下不会出现刷新不正常，所以放弃该版本带来的更新\r\n")
_T("    2、解决PROTEL99SE原理图里增加右键移动后，按住左键再按右键时器件不能旋转的问题(直到今天")
_T("才有人反馈该问题，说明此功能很少人用到，其实这是很好用的功能，大家不妨试试，PCB里也可用)\r\n")
_T("2.0.04：\r\n")
_T("    1、解决部分显卡不右键拖动时刷新不正常的问题\r\n")
_T("2.0.03：\r\n")
_T("    1、增加CAM350的支持，包括滚轮放大缩小和右键拖动\r\n")
_T("2.0.02：\r\n")
_T("    1、修复在BlazeRouter里右键拖动后还会出现菜单的BUG\r\n")
_T("2.0.01：\r\n")
_T("    1、提高鼠标移动运行效率\r\n")
_T("    2、解决PROTEL侧边栏滚轮BUG\r\n")
_T("    3、增加PROTEL99SE原理图右键移动功能\r\n")
_T("    4、支持powerlogic\r\n")
_T("    5、支持BlazeRouter\r\n")
_T("\r\n第二版(2.0)说明：\r\n")
_T("    本软件是部分EDA软件的鼠标增强工具，将EDAHelper.exe和Hook.dll同时放到任意目录，运行EDAHelper.exe")
_T("就行，现在已不再自动运行EDA软件，支持protel99se，DXP，POWERPCB，OrCAD的capture。\r\n")
_T("\r\n针对protel99se,DXP(功能和从前一样)：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于PageUp(不能改掉软件原来的快捷键，否则就不灵了)\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于PageDown(不能改掉软件原来的快捷键，否则就不灵了)\r\n")
_T("    3. 按下滚轮     --> 切换有效图层并刷新，相当于小键盘'*'的功能\r\n")
_T("    4. 按左键拖目标 --> 再按右键可旋转，相当于空格键的功能，在布局时非常好用，请留意\r\n")
_T("    5. 按右键拖动屏幕\r\n")
_T("\r\n针对powerpcb(支持PADS2005SP2、PADS2007，别的版本没有测过，应该也支持)：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于PageUp\r\n")
_T("    2. 向下滚动滚轮 --> 缩小，相当于PageDown\r\n" )
_T("    3. 按住鼠标右键移动，可移动工作区，相当于SHIFT+滚轮或者ALT+滚轮，不平滑\r\n")
_T("    4. 鼠标中键点击 --> 切换图层，相当于F4，原中键点击功能废弃\r\n" )
_T("\r\n针对OrCAD：\r\n")
_T("    1. 向上滚动滚轮 --> 放大，相当于字母\"I\"键\r\n")
_T("    2. 向下滚动滚轮 --> 缩小相当于字母\"O\"键\r\n" )
_T("\r\n    目前存在问题：点击系统图标关闭或者最小化窗口时，大约会停止响应3 秒钟，可能是Hook没有反安")
_T("装，我发现同类软件也有这样的问题，但是不知道怎么解决，哪位知道怎么解决的朋友麻烦告知，临时解决办")
_T("法就是点击窗口下边的关闭按钮。还有朋友说可以不用动态链接库，我也不知道怎么弄，希望懂的告知。")
_T("\r\n    其它：本软件原名protel99se鼠标增强工具(protel_increase)，2007年03月25日首先在老古网站(www.laogu.com)")
_T("上发布，至今已有两年，当时只是想做了自己用，顺便放上来给大家分享。如今，我已经很久不画板了，但没想到两年")
_T("来，有1600多次下载，还有朋友转载到别的网站，小有一些兴奋，说明我的工作是有意义的。前两天一个名叫xtomfuk ")
_T("的朋友来信要求增加PADS的支持，欣然接受，于是就有了这个版本。由于增加了多个EDA软件的支持，原名不能再")
_T("用了，姑且就叫EDAHelper吧。为了纪念上一个版本，这一版也选择在3月25日两周年之际发布。\r\n")
_T("    再罗嗦两句：本软件原理仅限于模拟按键，别的功能暂时做不了。依然不保留版权，任何人都可以修改，但请不要用")
_T("于营利目的，出问题也不要找我。当然如果你觉得应该增加更多更好功能，别介意联系我，QQ:126186，Email:spacexplorer@163.com。")
_T("\r\n    最后感谢xtomfuk的建议和测试，以及涛哥(paul)制作的图标。")
_T("\r\n\r\n第一版(1.0)说明：\r\n")
_T("    本软件是增强Protel99se鼠标中键功能的工具。\r\n")
_T("    1. 上下滚动滚轮，屏幕缩放相当于PageUp,PageDown的功能\r\n")
_T("    2. 按下滚轮，切换有效图层并刷新相当于小键盘'*'的功能\r\n")
_T("    3. 按住左键拖动器件再按右键可旋转，相当于\"TAB\"的功能\r\n")
_T("    4. 将本软件(含Hook.dll)放到Protel99se安装目录,运行时会自动启动Protel99se\r\n")
_T("    5. 仿照“Protel99se鼠标增强软件”(www.zsmcu.com)设计,因我运行她后用Source Insight")
_T("鼠标拖动时感觉明显变慢且部分操作不符合我的习惯而改写的\r\n")
_T("    6. 本软件包括两部分, 一是HOOK(.\\src\\test3)实现鼠标钩子和模拟按键，")
_T("二是主窗口(.\\src\\protel_increase), 安装钩子和显示帮助信息,部分代码源自")
_T("www.vckbase.com,无版权,任何人可以根据自己的需要把他改了在其它软件如:Orcad, ")
_T("PowerPCB等里运行,也可以让其自适应多个软件的操作,自己发挥吧, 如果你愿意,请EMAIL一份我.");

static TCHAR	*AD = 
_T("有个这样一个故事与大家分享：\r\n")
_T("    在美国得克萨斯州的一个风雪交加的夜晚，一位名叫克雷斯的年轻人因为汽车“抛锚”被困在郊外。")
_T("正当他万分焦急的时候，有一位骑马的男子正巧经过这里。见此情景，这位男子二话没说便用马帮助克雷斯")
_T("把汽车拉到了小镇上。 事后，当感激不尽的克雷斯拿出不菲的美钞对他表示酬谢时，这位男子说：“这不需")
_T("要回报，但我要你给我一个承诺，当别人有困难的时候，你也要尽力帮助他人。”于是，在后来的日子里，克")
_T("雷斯主动帮助了许许多多的人，并且每次都没有忘记转述那句同样的话给所有被他帮助的人。 许多年后的一天，")
_T("克雷斯被突然暴发的洪水困在了一个孤岛上，一位勇敢的少年冒着被洪水吞噬的危险救了他。当他感谢少年的时候，")
_T("少年竟然也说出了那句克雷斯曾说过无数次的话：“这不需要回报，但我要你给我一个承诺……”克雷斯的胸中")
_T("顿时涌起了一股暖暖的激流：“原来，我穿起的这根关于爱的链条，周转了无数的人，最后经过少年还给了我，我")
_T("一生做的这些好事，全都是为我自己做的！”当您有幸看到此消息时，请转发给自己的朋友亲人。我相信有更多的")
_T("人需要我们的帮助，正义会传染，邪恶也是如此，为现在的别人做善事也是为了将来的自己。\r\n");

CEDAHelperDlg::CEDAHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEDAHelperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEDAHelperDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bUpdateRunning = 0;
	_tcscpy(szVerTip, _T("EDAHelper V"));
}

void CEDAHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDAHelperDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEDAHelperDlg, CDialog)
	//{{AFX_MSG_MAP(CEDAHelperDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_AUTORUN, OnCheckAutorun)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, OnButtonMinimize)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PROPERTY, OnProperties)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperDlg message handlers

UINT   WM_TASKBARCREATED;

BOOL CEDAHelperDlg::OnInitDialog()
{
	TCHAR	szSoftwareInfo[256];
	CDialog::OnInitDialog();

	WM_TASKBARCREATED   =   
        ::RegisterWindowMessage(_T( "TaskbarCreated"));//将TaskbarCreated
	
	// Add "About..." menu item to system menu.

	GetDlgItem(IDC_EDIT_DESC)->SetWindowText(AppDesc);
	_stprintf(szSoftwareInfo, _T("EDAHelper(V%s %s), QQ群:74306669, Email:126186@qq.com"), _T(CURRENT_VERSION), _T(__DATE__));
	GetDlgItem(IDC_SW_INFO)->SetWindowText(szSoftwareInfo);
	if(CheckAutorunStats())
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->SetCheck(1);
	}
//	hUpdateThread = ::CreateThread( NULL, 0, UpdateTask, (LPVOID)&bUpdateRunning, 0, &dwUpdateThreadId );
	AfxBeginThread((AFX_THREADPROC)UpdateTask, (LPVOID)&bUpdateRunning);
	SetTimer(100, UPDATE_CHECK_PERIOD, NULL);

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	ServiceInit();
	HookInit();
	HookInstall();

	// Set url font
	CFont	*pFont = new CFont;
	pFont->CreateFont(16, // nHeight 
		6, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		TRUE, // bItalic 
		TRUE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("Arial"));
	GetDlgItem(IDC_STATIC_HOME)->SetFont(pFont);
	GetDlgItem(IDC_STATIC_FEEDBACK)->SetFont(pFont);
	// TODO: Add extra initialization here
    m_tnid.cbSize=sizeof(NOTIFYICONDATA);        //定义结构的成员变量
    m_tnid.hWnd=this->m_hWnd;
    m_tnid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
    m_tnid.uCallbackMessage=MYWM_NOTIFYICON;     //用户定义的回调消息
	_tcscat(szVerTip, _T(CURRENT_VERSION));
    _tcscpy(m_tnid.szTip, szVerTip);
	m_tnid.uID=IDR_MAINFRAME;
	m_tnid.hIcon=m_hIcon;
	if(m_hIcon)::DestroyIcon(m_hIcon);

	Shell_NotifyIcon(NIM_ADD,&m_tnid);

	if(CheckFirstRun())
	{
		SetWindowText(_T("EDAHelper(本版首次运行，为充分发挥软件性能，请仔细阅读使用说明和更新记录)"));
	}
	else
	{
		PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEDAHelperDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEDAHelperDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEDAHelperDlg::OnCheckAutorun() 
{
	HKEY hKey;
	CWinApp *pApp = AfxGetApp();

	CString str = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if (ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, str, &hKey))
	{
	   MessageBox(_T("打开注册表项失败"));
	   RegCloseKey(hKey);
	   return;
	}

	if(((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->GetCheck())
	{
		TCHAR	strPath[MAX_PATH];
		GetModuleFileName(AfxGetApp()->m_hInstance, strPath, MAX_PATH); 

		if (ERROR_SUCCESS != RegSetValueEx(hKey, _T("EDAHelper"), 0, REG_SZ, (LPBYTE)strPath, (_tcslen(strPath))*sizeof(TCHAR)))
		{
		   MessageBox(_T("写注册表失败"));
		   RegCloseKey(hKey);
		   return;
		}
	}
	else
	{
		if (ERROR_SUCCESS != RegDeleteValue(hKey, _T("EDAHelper")))
		{
		   MessageBox(_T("写注册表失败"));
		   RegCloseKey(hKey);
		   return;
		}

	}

	RegCloseKey(hKey);
}

void CEDAHelperDlg::OnButtonMinimize() 
{
	PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
}

BOOL CEDAHelperDlg::CheckAutorunStats()
{
	HKEY			hKey;
	TCHAR			szAppPathSaved[MAX_PATH];
	unsigned long	dwSize = MAX_PATH;
	TCHAR			szAppPath[MAX_PATH];
	GetModuleFileName(AfxGetApp()->m_hInstance, szAppPath, MAX_PATH); 


	CString str = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");

	if (ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, str, &hKey))
	{
	   MessageBox(_T("打开注册表项失败"));
	   RegCloseKey(hKey);
	   return FALSE;
	}
	int ErrCode = RegQueryValueEx(hKey, _T("EDAHelper"), NULL, NULL, (LPBYTE)szAppPathSaved, &dwSize);
	if(ERROR_SUCCESS == ErrCode)
	{
		if(!_tcsncmp(szAppPathSaved, szAppPath, dwSize/sizeof(TCHAR)))
		{
			return TRUE;
		}
	}
	else
	{
	}

	return FALSE;
}

BOOL CEDAHelperDlg::CheckUpdateStats()
{
	CWinApp*	pApp = AfxGetApp();

	if(pApp->GetProfileInt(CONFIG_ENTRY, _T("CheckUpdate"), 1))
	{
		return TRUE;
	}
	
	return FALSE;
	
}

void CEDAHelperDlg::OnClose() 
{
	CDialog::OnClose();
}

LRESULT CEDAHelperDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	static bool	IsShowWnd = TRUE;
    if((message==WM_SYSCOMMAND)&&(wParam==SC_MINIMIZE))         //如果是系统消息
	{
		this->ShowWindow(SW_MINIMIZE);
		this->ShowWindow(SW_HIDE);
		IsShowWnd = FALSE;
		return true;
	}
	else if((message==MYWM_NOTIFYICON)&&((lParam==WM_LBUTTONDOWN)||(lParam==WM_RBUTTONUP)))  //如果是用户定义的消息
	{
		if(!IsShowWnd)
		{
			this->ShowWindow(SW_SHOW);
			this->ShowWindow(SW_NORMAL);
			this->SetActiveWindow();   //双击并且出现在最上面
		}
		else
		{
			this->ShowWindow(SW_MINIMIZE);
			this->ShowWindow(SW_HIDE);
		}
		IsShowWnd = !IsShowWnd;
		return true;
	}
	else if(message == WM_TASKBARCREATED)
	{
		// TODO: Add extra initialization here
		m_tnid.cbSize=sizeof(NOTIFYICONDATA);        //定义结构的成员变量
		m_tnid.hWnd=this->m_hWnd;
		m_tnid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
		m_tnid.uCallbackMessage=MYWM_NOTIFYICON;     //用户定义的回调消息
		_tcscat(szVerTip, _T(CURRENT_VERSION));
		_tcscpy(m_tnid.szTip, szVerTip);
		m_tnid.uID=IDR_MAINFRAME;
		m_tnid.hIcon=m_hIcon;
		if(m_hIcon)::DestroyIcon(m_hIcon);
		
		Shell_NotifyIcon(NIM_ADD,&m_tnid);
		TRACE0("WM_TASKBARCREATED\n");
	}
#if 1	// this place for resolving temporary hang up, when the close this application.
	else if(message == WM_NCLBUTTONDOWN)
	{
		TRACE0("NCLBUTTONDOWN\n");
	//	HookUninstall();
	}
#endif
		
	return CDialog::WindowProc(message, wParam, lParam);
}

void CEDAHelperDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	Shell_NotifyIcon(NIM_DELETE, &m_tnid);
}

void CEDAHelperDlg::OnButtonHelp() 
{
	static BOOL HelpNotAd = FALSE;
	if(HelpNotAd)
	{
//		GetDlgItem(IDC_BUTTON_HELP)->SetWindowText(_T("广告"));
		GetDlgItem(IDC_EDIT_DESC)->SetWindowText(AppDesc);
	}
	else
	{
//		GetDlgItem(IDC_BUTTON_HELP)->SetWindowText(_T("帮助"));
		GetDlgItem(IDC_EDIT_DESC)->SetWindowText(AD);
	}

	HelpNotAd = !HelpNotAd;
	
}


void CEDAHelperDlg::OnTimer(UINT nIDEvent) 
{
	if ((nIDEvent == 100) && (!bUpdateRunning))
	{
//		hUpdateThread = ::CreateThread( NULL, 0, UpdateTask, (LPVOID)&bUpdateRunning, 0, &dwUpdateThreadId );
		AfxBeginThread((AFX_THREADPROC)UpdateTask, (LPVOID)&bUpdateRunning);
	}
	CDialog::OnTimer(nIDEvent);
}

void CEDAHelperDlg::OnProperties()
{
	// TODO: The property sheet attached to your project
	// via this function is not hooked up to any message
	// handler.  In order to actually use the property sheet,
	// you will need to associate this function with a control
	// in your project such as a menu item or tool bar button.
	int	rc = propSheet.DoModal();

	if(rc == IDOK)
	{
//		AfxMessageBox("OK");
	}
	else if(rc = IDCANCEL)
	{
//		AfxMessageBox("cancel");
	}
	else
	{
//		AfxMessageBox("no");
	}
	// This is where you would retrieve information from the property
	// sheet if propSheet.DoModal() returned IDOK.  We aren't doing
	// anything for simplicity.
}



HBRUSH CEDAHelperDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		CString ss;
		pWnd->GetWindowText(ss);
		if(memcmp(ss,_T("查看更新"),8) == 0)
		{
			pDC->SetTextColor(RGB(0,0,254));
		}
		if(memcmp(ss,_T("论坛反馈"),8) == 0)
		{
			pDC->SetTextColor(RGB(0,0,254));
		}
	}	
	return hbr;
}

BOOL CEDAHelperDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CRect rcStatic; 
	CPoint ptCursor; 
	
	CWnd *pStatic=GetDlgItem(IDC_STATIC_HOME);
	pStatic->GetWindowRect(rcStatic);
	GetCursorPos(&ptCursor);
	
	if(rcStatic.PtInRect(ptCursor))
	{
		//change cursor to hand
		HCURSOR hHandCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_HAND);
		if(hHandCursor)
			SetCursor(hHandCursor); 
		
		return TRUE; 
	}
	
	pStatic=GetDlgItem(IDC_STATIC_FEEDBACK);
	pStatic->GetWindowRect(rcStatic);
	if(rcStatic.PtInRect(ptCursor))
	{
		//change cursor to hand
		HCURSOR hHandCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_HAND);
		if(hHandCursor)
			SetCursor(hHandCursor); 
		
		return TRUE; 
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CEDAHelperDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rcStatic; 
	CPoint ptCursor;
	CString str = _T("www.jyxtec.com/edahelper");
	
	CWnd *pStatic=GetDlgItem(IDC_STATIC_HOME);
	pStatic->GetWindowRect(rcStatic);
	GetCursorPos(&ptCursor);
	
	if(rcStatic.PtInRect(ptCursor))
	{
		ShellExecute(m_hWnd, NULL, str, NULL,NULL, SW_SHOWMAXIMIZED);
	}

	pStatic=GetDlgItem(IDC_STATIC_FEEDBACK);
	pStatic->GetWindowRect(rcStatic);
	GetCursorPos(&ptCursor);
	
	str = _T("http://www.jyxtec.com/forum/forum.php?mod=forumdisplay&fid=37");
	if(rcStatic.PtInRect(ptCursor))
	{
		ShellExecute(m_hWnd, NULL, str, NULL,NULL, SW_SHOWMAXIMIZED);
	}

	CDialog::OnLButtonUp(nFlags, point);
}


BOOL CEDAHelperDlg::CheckFirstRun()
{
	CWinApp *pApp = AfxGetApp();

	CString szFirstRun = pApp->GetProfileString(CONFIG_ENTRY, _T("FirstRun"));
	if(szFirstRun.Compare(_T(CURRENT_VERSION)))
	{
		pApp->WriteProfileString(CONFIG_ENTRY, _T("FirstRun"), _T(CURRENT_VERSION));
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
