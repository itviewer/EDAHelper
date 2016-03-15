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
_T("2.1.13˵����\r\n")
_T("    ������Ƕ���EDA����������ǿ���ߣ���ɫ���ļ���֧��Win9x/NT/2000/XP/WIN7������WIN7��Ҫ�Թ���Աģʽ���У�")
_T("���⣬Win9x��Ҫ����ɷ�UNICODE�汾������Ҫ���û��ɷ��ʼ�������ȡ��֧��protel99se��DXP(AD)��PADS��OrCAD��capture��")
_T("Cam350��Saber��PC Schematic��Allegro��CircuitCAM,���Ҷ�ÿ������Ĺ��ܶ������ã��û��ɸ���ʹ��ϰ�ߴ򿪻��߹رչ��ܡ�\r\n")
_T("    �������ʱ��������ÿ��24Сʱ�����£����ϵͳ���������и���ʱ��������������Ϣ��\r\n")
_T("\r\n���protel99se, DXP,Altium Designer��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��PageUp(���ܸĵ����ԭ���Ŀ�ݼ�������Ͳ�����)\r\n")
_T("    2. ���¹������� --> ��С���൱��PageDown(���ܸĵ����ԭ���Ŀ�ݼ�������Ͳ�����)\r\n")
_T("    3. ���¹���     --> �л���Чͼ�㲢ˢ�£��൱��С����'*'�Ĺ���\r\n")
_T("    4. �������Ŀ�� --> �ٰ��Ҽ�����ת���൱�ڿո���Ĺ��ܣ��ڲ���ʱ�ǳ����ã�������\r\n")
_T("    5. ���Ҽ��϶���Ļ\r\n")
_T("    6. ԭ��ͼ�ﵥ���м��������ò˵����൱�ڰ���P����1�Σ����������൱��ֱ�ӷ���Ԫ��\r\n")
_T("    7. ���м������ƶ������������൱��ALT+Backspace\r\n")
_T("    8. ���м������ƶ������������൱��CTRL+Backspace\r\n")
_T("    9. ���м������ƶ�������ʱɾ����һ�β������൱�ڰ�Backspace\r\n")
_T("    10.���м������ƶ�����ɾ����ǰ�����ѡ�����ݣ��൱�ڰ�DELETE��CTRL+DELETE\r\n")
_T("\r\n���PADS(֧�ָ��ְ汾logic, pcb)��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��PageUp\r\n")
_T("    2. ���¹������� --> ��С���൱��PageDown\r\n")
_T("    3. ��ס����Ҽ��ƶ������ƶ�������\r\n")
_T("    4. ����м���� --> �л�ͼ�㣬�൱��F4��ԭ�м�������ܷ���\r\n")
_T("    5. �������Ŀ�� --> �ٰ��Ҽ�����ת���൱��TAB���Ĺ��ܣ��ڲ���ʱ�ǳ����ã�������\r\n")
_T("\r\n���OrCAD��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱����ĸ\"I\"��\r\n")
_T("    2. ���¹������� --> ��С�൱����ĸ\"O\"��\r\n")
_T("    3. ��ס����Ҽ��ƶ������ƶ�������\r\n")
_T("    4. ���м��������ô��ڵĹ��ܣ��൱�ڰ���P����1��\r\n")
_T("    5. ���м������ƶ������������൱�ڰ�CTRL+Z\r\n")
_T("    6. ���м������ƶ������������൱�ڰ�CTRL+Y\r\n")
_T("    7. ���м������ƶ������뻭�߲������൱�ڰ�W��\r\n")
_T("    8. ���м������ƶ���ɾ��ѡ�����ݣ��൱�ڰ�DELETE��\r\n")
_T("\r\n���Cam350��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��\"PageUp\"��\r\n")
_T("    2. ���¹������� --> ��С���൱��\"PageDown\"��\r\n")
_T("    3. ��ס����Ҽ��ƶ������ƶ�������\r\n")
_T("    4. �޸�ԭ�м����ܣ����м��ſ���������������ʾ��ͼȫ���������൱�ڰ���HOME�������м������Ч��\r\n")
_T("    5�����м������ƶ������������൱�ڰ�CTRL+Z\r\n")
_T("    6�����м������ƶ������������൱�ڰ�CTRL+U\r\n")
_T("    7�����м������ƶ�������Aperture Table���൱�ڰ�A��\r\n")
_T("    8�����м������ƶ���ɾ��ѡ�����ݣ��൱�ڰ�Edit�˵����DELETE��\r\n")
_T("\r\n���Saber��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��\"PageUp\"��\r\n")
_T("    2. ���¹������� --> ��С���൱��\"PageDown\"��\r\n")
_T("\r\n���PC Schematic(V11�в���)��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��\"PageUp\"��, ԭ�п�ݼ�Ҫ��\r\n")
_T("    2. ���¹������� --> ��С���൱��\"PageDown\"����ԭ�п�ݼ�Ҫ��\r\n")
_T("\r\n���Allegro(15.7�в��ԣ��Ѿ����м����ŵ��°汾���ֹ�ù���)��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��\"F10\"��\r\n")
_T("    2. ���¹������� --> ��С���൱��\"F11\"��\r\n")
_T("    3. �м��϶���ת(�ʺ�ϰ��AutoCAD���м��϶����û�)\r\n")
_T("\r\n���CircuitCAM��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��\"PageUp\"��\r\n")
_T("    2. ���¹������� --> ��С���൱��\"PageDown\"��\r\n")
_T("    3. ��ס����Ҽ��ƶ������ƶ�������\r\n")
_T("\r\n")
_T("�����ȡ������\"svn checkout https://dbghelper.googlecode.com/svn/EDAHelper\"\r\n")

_T("\r\n������ʷ��\r\n")
_T("2.1.14��\r\n")
_T("    1���޸�protel99se��3Dģʽʱ���ŵ�ʧЧ������\r\n")
_T("    2���޸�DXP��legacy 3Dģʽʱ���ŵ�ʧЧ������\r\n")
_T("2.1.13��\r\n")
_T("    1���޸�PADS�Ҽ��϶�֮��ͳģʽ��BUG\r\n")
_T("    2������������Ч�ʣ���������û���QQ�����ƶ����ʱ��ǳ��������\r\n")
_T("    3���޸���allegro�й������ʱ�����������ʱ�����F10,F11������BUG(����)\r\n")
_T("    4���޸�CAM350�Ҽ��϶����ܣ�ʹ��ƽ���ƶ�\r\n")
_T("2.1.12��\r\n")
_T("    1���޸ĳ�������24Сʱ���ټ����³��������\r\n")
_T("    2���ٴ��޸��Զ�������ʱ��ʧ�ܵ�����\r\n")
_T("    3���޸ķǻ����ʱ����ʧЧ�����⣬�ر��ǲ鿴�Զ����ص�QQ���ں����׳���\r\n")
_T("    4���Ż�PADS Router�ﻭ��ʱ���м����������ʹ֮�����ƶ���Ļ��ͬʱ�����unroute�Ŀ�ݼ�����ΪF4����Ϊ������ѡ�����ߵ�ʱ�򣬰��м��Ϳ���ɾ��\r\n")
_T("    5���޸�pads�Ҽ�ƽ���ƶ�(�����ûش�ͳģʽ)\r\n")
_T("    6�����������\r\n")
_T("    7��ͨ��360��֤(��2.1.10��ǰ�İ汾������������ܳ�������)\r\n")
_T("2.1.11��\r\n")
_T("    1���޸��Զ�������ʱ��ʧ�ܵ�����\r\n")
_T("2.1.10��\r\n")
_T("    1������UNICODE����ģʽ��ʹ��֧�ֶ�����NT��������ϵͳ��win9xϵͳ��Ҫ����ɷ�UNICODEģʽ\r\n")
_T("    2������Allegro���м��϶���ת(�ʺ�ϰ��AutoCAD���û�)\r\n")
_T("    3���޸ĵ�explorer�رպ�������ͼ����ʧ��BUG\r\n")
_T("    4�������ظ����г���ʱ����������\r\n")
_T("    5�����Ӷ�CircuitCAM��֧��\r\n")
_T("    6���޸�Orcad���������֮���Ҽ��϶���Ч������\r\n")
_T("    7���޸ļ����·�ʽ��ʹ�����Ի�\r\n")
_T("2.1.09��\r\n")
_T("    1���޸�protel���Ҽ��رմ��ڵ�BUG\r\n")
_T("2.1.08��\r\n")
_T("    1���޸�allegro��ʧЧ��BUG\r\n")
_T("2.1.07��\r\n")
_T("    1������CAM350���м������ƶ������������൱�ڰ�CTRL+Z\r\n")
_T("    2������CAM350���м������ƶ������������൱�ڰ�CTRL+U\r\n")
_T("    3������CAM350���м������ƶ�������Aperture Table���൱�ڰ�A��\r\n")
_T("    4������CAM350���м������ƶ���ɾ��ѡ�����ݣ��൱�ڰ�Edit�˵����DELETE��\r\n")
_T("    5���޸�(2.1.06)Դ����һ���ַ��������BUG\r\n")
_T("2.1.06��\r\n")
_T("    1������Orcad�ﰴ�м��������ô��ڵĹ��ܣ��൱�ڰ���P����1��\r\n")
_T("    2������Orcad���м������ƶ������������൱�ڰ�CTRL+Z\r\n")
_T("    3������Orcad���м������ƶ������������൱�ڰ�CTRL+Y\r\n")
_T("    4������Orcad���м������ƶ������뻭�߲������൱�ڰ�W��\r\n")
_T("    5������Orcad���м������ƶ���ɾ��ѡ�����ݣ��൱�ڰ�DELETE��\r\n")
_T("    6�����Ӱ汾�Ŵ�2.1.06��ʼ�ı��������¼\r\n")
_T("2.1.05��\r\n")
_T("    1���޸�CAM350�м����ܣ����м��ſ�����ʾ��ͼȫ�����൱�ڰ���HOME����\r\n")
_T("2.1.04��\r\n")
_T("    1������protelϵ��ԭ��ͼ�ﰴ�м��������ò˵��Ĺ��ܣ��൱�ڰ���P����1��\r\n")
_T("    2������protelϵ�а��м������ƶ������������൱��ALT+Backspace\r\n")
_T("    3������protelϵ�а��м������ƶ������������൱��CTRL+Backspace\r\n")
_T("    4������protelϵ�а��м������ƶ�������ʱɾ����һ�β������൱�ڰ�Backspace\r\n")
_T("    5������protelϵ�а��м������ƶ�����ɾ����ǰ�����ѡ�����ݣ��൱�ڰ�DELETE��CTRL+DELETE\r\n")
_T("2.1.03��\r\n")
_T("    1���޸��Ҽ��϶��Ƴ��߽�ſ����϶����ܻ��ڼ�����BUG\r\n")
_T("2.1.02��\r\n")
_T("    1������pads�ﰴס�����Ŀ�꣬�ٰ��Ҽ���ת�Ĺ���\r\n")
_T("2.1.01��\r\n")
_T("    1���޸���protel��PCB���Ҽ�ʧЧ��BUG\r\n")
_T("2.1.00��\r\n")
_T("    1����д��ģ�飬�����֧�ֶ�����������������֧�ָ�����\r\n")
_T("    2�������֧�ֿ����ã����õ�������Խ�ֹ���ӿ���������ٶ�\r\n")
_T("2.0.13��\r\n")
_T("    1����˵�ܶ��˶�����cadence 16.0���µİ汾�����Ǽ���allegro��֧�ְɣ�ǰ����ԭ�е����Ź��ܿ�ݼ�û��(F10��F11)��16.2(F11��F12)���ϵİ汾�Ͳ�Ҫ���ˣ����г�ͻ�����߰ѿ�ݼ���ΪF11��F12\r\n")
_T("2.0.12��\r\n")
_T("    1������PCSchematic���м����ż��Ҽ��϶���ǰ����ԭ�е����Ź��ܿ�ݼ�Ҫ��(ctrl+home -> pageup, ctrl+end -> pagedown)\r\n")
_T("    2���޸���������ʱ�Զ���������Ĵ���\r\n")
_T("    3�������޸���Ӧ������һλ���Ƕ���Ҫ���޸ĵģ�������512��Ҳ�������һ���봨�����\r\n")
_T("2.0.11��\r\n")
_T("    1�������Զ�������\r\n")
_T("    2���޸�orcad���Ҽ��ƶ�������ʹ������\r\n")
_T("    3���޸�˵����һֱ������һ������֣��Ǻ�\r\n")
_T("    4������saber sketch�м����Ź���\r\n")
_T("    5���޸�Ϊ���ļ���ȥ��ԭ����DLL\r\n")
_T("2.0.10��\r\n")
_T("    1���޸���PADS�а�סCONTROL��SHIFT��ALT��ʱ���м�ԭ����ʧЧ��BUG\r\n")
_T("    2���޸���PADS�зǻ�ͼ���ڣ���깦��ʧЧ��BUG\r\n")
_T("    3�����ӷ���棨��WORD2003ת��������֮����ָ��\r\n")
_T("    4���ϴ���googlecode������Ȥ�����ѿ���ͨ��svn checkout https://dbghelper.googlecode.com/svn/EDAHelper��ô���\r\n")
_T("2.0.09��\r\n")
_T("    1���޸�ͨ��˫����powerlogic�ļ�ʱ����ҹ���ʧЧ����\r\n")
_T("    2���޸��м�����ʱ��Ļƫ�Ƶ�����\r\n")
_T("2.0.08��\r\n")
_T("    1������Protel99se��DXP��ӡԤ���м����ŵ�֧��\r\n")
_T("2.0.07��\r\n")
_T("    1������OrCAD�Ҽ��϶���֧��\r\n")
_T("2.0.06��\r\n")
_T("    1������CAM350�Ҽ�ԭ����ʧЧ������\r\n")
_T("2.0.05��\r\n")
_T("    1��2.0.04�汾�����ٶȱ��������ڴ󲿷�����²������ˢ�²����������Է����ð汾�����ĸ���\r\n")
_T("    2�����PROTEL99SEԭ��ͼ�������Ҽ��ƶ��󣬰�ס����ٰ��Ҽ�ʱ����������ת������(ֱ������")
_T("�����˷��������⣬˵���˹��ܺ������õ�����ʵ���Ǻܺ��õĹ��ܣ���Ҳ������ԣ�PCB��Ҳ����)\r\n")
_T("2.0.04��\r\n")
_T("    1����������Կ����Ҽ��϶�ʱˢ�²�����������\r\n")
_T("2.0.03��\r\n")
_T("    1������CAM350��֧�֣��������ַŴ���С���Ҽ��϶�\r\n")
_T("2.0.02��\r\n")
_T("    1���޸���BlazeRouter���Ҽ��϶��󻹻���ֲ˵���BUG\r\n")
_T("2.0.01��\r\n")
_T("    1���������ƶ�����Ч��\r\n")
_T("    2�����PROTEL���������BUG\r\n")
_T("    3������PROTEL99SEԭ��ͼ�Ҽ��ƶ�����\r\n")
_T("    4��֧��powerlogic\r\n")
_T("    5��֧��BlazeRouter\r\n")
_T("\r\n�ڶ���(2.0)˵����\r\n")
_T("    ������ǲ���EDA����������ǿ���ߣ���EDAHelper.exe��Hook.dllͬʱ�ŵ�����Ŀ¼������EDAHelper.exe")
_T("���У������Ѳ����Զ�����EDA�����֧��protel99se��DXP��POWERPCB��OrCAD��capture��\r\n")
_T("\r\n���protel99se,DXP(���ܺʹ�ǰһ��)��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��PageUp(���ܸĵ����ԭ���Ŀ�ݼ�������Ͳ�����)\r\n")
_T("    2. ���¹������� --> ��С���൱��PageDown(���ܸĵ����ԭ���Ŀ�ݼ�������Ͳ�����)\r\n")
_T("    3. ���¹���     --> �л���Чͼ�㲢ˢ�£��൱��С����'*'�Ĺ���\r\n")
_T("    4. �������Ŀ�� --> �ٰ��Ҽ�����ת���൱�ڿո���Ĺ��ܣ��ڲ���ʱ�ǳ����ã�������\r\n")
_T("    5. ���Ҽ��϶���Ļ\r\n")
_T("\r\n���powerpcb(֧��PADS2005SP2��PADS2007����İ汾û�в����Ӧ��Ҳ֧��)��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱��PageUp\r\n")
_T("    2. ���¹������� --> ��С���൱��PageDown\r\n" )
_T("    3. ��ס����Ҽ��ƶ������ƶ����������൱��SHIFT+���ֻ���ALT+���֣���ƽ��\r\n")
_T("    4. ����м���� --> �л�ͼ�㣬�൱��F4��ԭ�м�������ܷ���\r\n" )
_T("\r\n���OrCAD��\r\n")
_T("    1. ���Ϲ������� --> �Ŵ��൱����ĸ\"I\"��\r\n")
_T("    2. ���¹������� --> ��С�൱����ĸ\"O\"��\r\n" )
_T("\r\n    Ŀǰ�������⣺���ϵͳͼ��رջ�����С������ʱ����Լ��ֹͣ��Ӧ3 ���ӣ�������Hookû�з���")
_T("װ���ҷ���ͬ�����Ҳ�����������⣬���ǲ�֪����ô�������λ֪����ô����������鷳��֪����ʱ�����")
_T("�����ǵ�������±ߵĹرհ�ť����������˵���Բ��ö�̬���ӿ⣬��Ҳ��֪����ôŪ��ϣ�����ĸ�֪��")
_T("\r\n    �����������ԭ��protel99se�����ǿ����(protel_increase)��2007��03��25���������Ϲ���վ(www.laogu.com)")
_T("�Ϸ����������������꣬��ʱֻ���������Լ��ã�˳�����������ҷ���������Ѿ��ܾò������ˣ���û�뵽����")
_T("������1600������أ���������ת�ص������վ��С��һЩ�˷ܣ�˵���ҵĹ�����������ġ�ǰ����һ������xtomfuk ")
_T("����������Ҫ������PADS��֧�֣���Ȼ���ܣ����Ǿ���������汾�����������˶��EDA�����֧�֣�ԭ��������")
_T("���ˣ����Ҿͽ�EDAHelper�ɡ�Ϊ�˼�����һ���汾����һ��Ҳѡ����3��25��������֮�ʷ�����\r\n")
_T("    ���������䣺�����ԭ�������ģ�ⰴ������Ĺ�����ʱ�����ˡ���Ȼ��������Ȩ���κ��˶������޸ģ����벻Ҫ��")
_T("��Ӫ��Ŀ�ģ�������Ҳ��Ҫ���ҡ���Ȼ��������Ӧ�����Ӹ�����ù��ܣ��������ϵ�ң�QQ:126186��Email:spacexplorer@163.com��")
_T("\r\n    ����лxtomfuk�Ľ���Ͳ��ԣ��Լ��θ�(paul)������ͼ�ꡣ")
_T("\r\n\r\n��һ��(1.0)˵����\r\n")
_T("    ���������ǿProtel99se����м����ܵĹ��ߡ�\r\n")
_T("    1. ���¹������֣���Ļ�����൱��PageUp,PageDown�Ĺ���\r\n")
_T("    2. ���¹��֣��л���Чͼ�㲢ˢ���൱��С����'*'�Ĺ���\r\n")
_T("    3. ��ס����϶������ٰ��Ҽ�����ת���൱��\"TAB\"�Ĺ���\r\n")
_T("    4. �������(��Hook.dll)�ŵ�Protel99se��װĿ¼,����ʱ���Զ�����Protel99se\r\n")
_T("    5. ���ա�Protel99se�����ǿ�����(www.zsmcu.com)���,��������������Source Insight")
_T("����϶�ʱ�о����Ա����Ҳ��ֲ����������ҵ�ϰ�߶���д��\r\n")
_T("    6. ���������������, һ��HOOK(.\\src\\test3)ʵ����깳�Ӻ�ģ�ⰴ����")
_T("����������(.\\src\\protel_increase), ��װ���Ӻ���ʾ������Ϣ,���ִ���Դ��")
_T("www.vckbase.com,�ް�Ȩ,�κ��˿��Ը����Լ�����Ҫ�������������������:Orcad, ")
_T("PowerPCB��������,Ҳ������������Ӧ�������Ĳ���,�Լ����Ӱ�, �����Ը��,��EMAILһ����.");

static TCHAR	*AD = 
_T("�и�����һ���������ҷ���\r\n")
_T("    �������ÿ���˹�ݵ�һ����ѩ���ӵ�ҹ��һλ���п���˹����������Ϊ��������ê�������ڽ��⡣")
_T("��������ֽ�����ʱ����һλ������������ɾ�����������龰����λ���Ӷ���û˵�������������˹")
_T("������������С���ϡ� �º󣬵��м������Ŀ���˹�ó����Ƶ�����������ʾ��лʱ����λ����˵�����ⲻ��")
_T("Ҫ�ر�������Ҫ�����һ����ŵ�������������ѵ�ʱ����ҲҪ�����������ˡ������ǣ��ں������������")
_T("��˹������������������ˣ�����ÿ�ζ�û������ת���Ǿ�ͬ���Ļ������б����������ˡ� �������һ�죬")
_T("����˹��ͻȻ�����ĺ�ˮ������һ���µ��ϣ�һλ�¸ҵ�����ð�ű���ˮ���ɵ�Σ�վ�������������л�����ʱ��")
_T("���꾹ȻҲ˵�����Ǿ����˹��˵�������εĻ������ⲻ��Ҫ�ر�������Ҫ�����һ����ŵ����������˹������")
_T("��ʱӿ����һ��ůů�ļ�������ԭ�����Ҵ����������ڰ�����������ת���������ˣ���󾭹����껹�����ң���")
_T("һ��������Щ���£�ȫ����Ϊ���Լ����ģ����������ҿ�������Ϣʱ����ת�����Լ����������ˡ��������и����")
_T("����Ҫ���ǵİ���������ᴫȾ��а��Ҳ����ˣ�Ϊ���ڵı���������Ҳ��Ϊ�˽������Լ���\r\n");

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
        ::RegisterWindowMessage(_T( "TaskbarCreated"));//��TaskbarCreated
	
	// Add "About..." menu item to system menu.

	GetDlgItem(IDC_EDIT_DESC)->SetWindowText(AppDesc);
	_stprintf(szSoftwareInfo, _T("EDAHelper(V%s %s), QQȺ:74306669, Email:126186@qq.com"), _T(CURRENT_VERSION), _T(__DATE__));
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
    m_tnid.cbSize=sizeof(NOTIFYICONDATA);        //����ṹ�ĳ�Ա����
    m_tnid.hWnd=this->m_hWnd;
    m_tnid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
    m_tnid.uCallbackMessage=MYWM_NOTIFYICON;     //�û�����Ļص���Ϣ
	_tcscat(szVerTip, _T(CURRENT_VERSION));
    _tcscpy(m_tnid.szTip, szVerTip);
	m_tnid.uID=IDR_MAINFRAME;
	m_tnid.hIcon=m_hIcon;
	if(m_hIcon)::DestroyIcon(m_hIcon);

	Shell_NotifyIcon(NIM_ADD,&m_tnid);

	if(CheckFirstRun())
	{
		SetWindowText(_T("EDAHelper(�����״����У�Ϊ��ַ���������ܣ�����ϸ�Ķ�ʹ��˵���͸��¼�¼)"));
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
	   MessageBox(_T("��ע�����ʧ��"));
	   RegCloseKey(hKey);
	   return;
	}

	if(((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->GetCheck())
	{
		TCHAR	strPath[MAX_PATH];
		GetModuleFileName(AfxGetApp()->m_hInstance, strPath, MAX_PATH); 

		if (ERROR_SUCCESS != RegSetValueEx(hKey, _T("EDAHelper"), 0, REG_SZ, (LPBYTE)strPath, (_tcslen(strPath))*sizeof(TCHAR)))
		{
		   MessageBox(_T("дע���ʧ��"));
		   RegCloseKey(hKey);
		   return;
		}
	}
	else
	{
		if (ERROR_SUCCESS != RegDeleteValue(hKey, _T("EDAHelper")))
		{
		   MessageBox(_T("дע���ʧ��"));
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
	   MessageBox(_T("��ע�����ʧ��"));
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
    if((message==WM_SYSCOMMAND)&&(wParam==SC_MINIMIZE))         //�����ϵͳ��Ϣ
	{
		this->ShowWindow(SW_MINIMIZE);
		this->ShowWindow(SW_HIDE);
		IsShowWnd = FALSE;
		return true;
	}
	else if((message==MYWM_NOTIFYICON)&&((lParam==WM_LBUTTONDOWN)||(lParam==WM_RBUTTONUP)))  //������û��������Ϣ
	{
		if(!IsShowWnd)
		{
			this->ShowWindow(SW_SHOW);
			this->ShowWindow(SW_NORMAL);
			this->SetActiveWindow();   //˫�����ҳ�����������
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
		m_tnid.cbSize=sizeof(NOTIFYICONDATA);        //����ṹ�ĳ�Ա����
		m_tnid.hWnd=this->m_hWnd;
		m_tnid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
		m_tnid.uCallbackMessage=MYWM_NOTIFYICON;     //�û�����Ļص���Ϣ
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
//		GetDlgItem(IDC_BUTTON_HELP)->SetWindowText(_T("���"));
		GetDlgItem(IDC_EDIT_DESC)->SetWindowText(AppDesc);
	}
	else
	{
//		GetDlgItem(IDC_BUTTON_HELP)->SetWindowText(_T("����"));
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
		if(memcmp(ss,_T("�鿴����"),8) == 0)
		{
			pDC->SetTextColor(RGB(0,0,254));
		}
		if(memcmp(ss,_T("��̳����"),8) == 0)
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
