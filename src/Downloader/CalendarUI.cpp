#include "stdafx.h"
#include "CalendarUI.h"

CalendarUI::CalendarUI()
:m_bTag(true)
{
	
}


CalendarUI::~CalendarUI()
{
}

DUI_BEGIN_MESSAGE_MAP(CalendarUI, WindowImplBase)
DUI_ON_CLICK_CTRNAME(BT_CANCEL, OnClose)
DUI_END_MESSAGE_MAP()

LPCTSTR CalendarUI::GetWindowClassName() const
{
	return _T("CalendarUI");
}

CDuiString CalendarUI::GetSkinFolder()
{
	return _T("skin");
}

CDuiString CalendarUI::GetSkinFile()
{
	return _T("xml\\CalendarUI.xml");
}

void CalendarUI::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
}

void CalendarUI::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		STDSTRING btnName = msg.pSender->GetName();
		STDSTRING strTag(_T("Button"));
		int iRet = btnName.compare(0, 6, strTag);
		if (iRet == 0){
			SaveData(btnName);
			Close();
		}
		if (btnName == _T("Add_Year")){
			m_sysTime.wYear = m_sysTime.wYear + 1;
			DrawCalendar(m_sysTime);
		}
		if (btnName == _T("Sub_Year")){
			m_sysTime.wYear = m_sysTime.wYear - 1;
			DrawCalendar(m_sysTime);
		}
	}
	if (m_bTag)
	{	
		OnPrepare();
		m_PrevMonth = m_sysTime.wMonth;
		m_bTag = false;
	}
	if (msg.sType == DUI_MSGTYPE_ITEMSELECT && msg.pSender->GetName() == _T("CB_month"))
	{
		CComboUI* Comb = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("CB_month")));
		int newmonth = Comb->GetCurSel() + 1;
		if (newmonth > m_PrevMonth){
			m_sysTime.wMonth = m_sysTime.wMonth + newmonth - m_PrevMonth;
			DrawCalendar(m_sysTime);
		}
		else if(newmonth < m_PrevMonth){
			m_sysTime.wMonth = m_sysTime.wMonth + newmonth - m_PrevMonth;
			DrawCalendar(m_sysTime);
		}
		m_PrevMonth = newmonth;		
	}
	WindowImplBase::Notify(msg);
}

void CalendarUI::OnClose(TNotifyUI& msg)
{
	Close();
}

void CalendarUI::OnPrepare()
{
	::GetLocalTime(&m_sysTime);
	DrawCalendar(m_sysTime);
}

//绘制日历
void CalendarUI::DrawCalendar(SYSTEMTIME m_sysTime)
{
	int iDay = 0;
	STDSTRING cDay, cMonth, cYear;
	STDSTRING itemName, BtnName;
	//int iStartDay = m_sysTime.wDayOfWeek;
	m_sysTime.wDay = 1;
	int iStartDay = GetDayOfWeek(m_sysTime);
	//上月天数
	int iLastMonthStartDays = 31 - iStartDay;
	if (m_sysTime.wMonth > 1)
		iLastMonthStartDays = GetMonthDays(m_sysTime.wYear, m_sysTime.wMonth - 1) - iStartDay;
	//本月天数
	int iMonthDays = GetMonthDays(m_sysTime.wYear, m_sysTime.wMonth);
	//下月天数
	int iNextMonthDays = 0;
	
	for (int i = 0; i < 42; i++)
	{
		BtnName = _T("Button") + std::to_string(i);
		CButtonUI* btn = static_cast<CButtonUI*>(m_PaintManager.FindControl(BtnName.c_str()));
		//上月
		if (i<iStartDay)
		{
			iLastMonthStartDays++;
			cDay = std::to_string(iLastMonthStartDays);
			btn->SetText(cDay.c_str());
			btn->SetBkColor(BT_BKCOLOR1);
		}
		else if (i>iStartDay - 1 && iDay < iMonthDays)
		{
			iDay++;
			cDay = std::to_string(iDay);
			btn->SetText(cDay.c_str());
			btn->SetBkColor(BT_BKCOLOR2);
		}
		else
		{
			iNextMonthDays++;
			cDay = std::to_string(iNextMonthDays);
			btn->SetText(cDay.c_str());
			btn->SetBkColor(BT_BKCOLOR3);
		}
	}

	itemName = STDSTRING(("Item")) + std::to_string(m_sysTime.wMonth);
	CListLabelElementUI* itemLabe = static_cast<CListLabelElementUI*>(m_PaintManager.FindControl(itemName.c_str()));
	itemLabe->Select(true);

	cYear = std::to_string(m_sysTime.wYear);
	CLabelUI* edit_year = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("InputYear")));
	edit_year->SetText(cYear.c_str());
}

int CalendarUI::GetMonthDays(int iY, int iM)
{
	int iTotalDay = 31;
	if (iM == 2)
	{
		if (iY % 4 == 0 && iY % 100 != 0 || iY % 400 == 0)
			iTotalDay = 29;
		else
			iTotalDay = 28;
	}
	else if (iM == 4 || iM == 6 || iM == 9 || iM == 11)
		iTotalDay = 30;
	return iTotalDay;
}

int CalendarUI::GetDayOfWeek(SYSTEMTIME m_sysTime)
{
	m_ctime.SetDate(m_sysTime.wYear, m_sysTime.wMonth, m_sysTime.wDay);
	return m_ctime.GetDayOfWeek() - 1;
}

void CalendarUI::SaveData(STDSTRING& btnName)
{
	CComboUI* CB_Month = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("CB_month")));
	CLabelUI* LB_Year = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("InputYear")));
	CButtonUI* BT_Input = static_cast<CButtonUI*>(m_PaintManager.FindControl(btnName.c_str()));
	DWORD bkcolor = BT_Input->GetBkColor();
	int month = CB_Month->GetCurSel() + 1;
	if (bkcolor == BT_BKCOLOR1)
	{
		month = month - 1;
	}
	if (bkcolor == BT_BKCOLOR3)
	{
		month = month + 1;
	}
	STDSTRING strMonth = to_string(month);
	STDSTRING strYear = LB_Year->GetText();
	STDSTRING Day = BT_Input->GetText();
	if (Day.size() == 1)
	{
		Day = STDSTRING(_T("0")) + Day;
	}
	if (strMonth.size() == 1)
	{
		strMonth = STDSTRING(_T("0")) + strMonth;
	}
	m_strData = strYear + STDSTRING(_T("-")) + strMonth + STDSTRING(_T("-")) + Day;
}


STDSTRING CalendarUI::GetData()
{
	return m_strData;
}

LRESULT CalendarUI::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_NCLBUTTONDOWN || wParam == WM_NCLBUTTONDOWN || lParam == WM_NCLBUTTONDOWN)
	{
		Close();
	}
	bHandled = FALSE;
	return 0;
}