#pragma once
class CDownLoadList
	:public CNotifyPump
{
public:
	CDownLoadList();
	~CDownLoadList();

	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	void AddDownloadTask();
	void AddDataToSubList(CListContainerElementUI* TaskList, const unsigned long download_ID, const int id);
	CDuiString TimeChange(__time64_t inputTime);

	void Show_Off_SubList(CDuiString& strSendName);
	int GetSubListCurSel(CListContainerElementUI* SubList, CListUI* pList);

	CListContainerElementUI* Add_FileInfoList();
	void RemoveSubList(CDuiString& strSendName);

	void RenewList();
private:
	CPaintManagerUI* _ppm;
	int				_taskCount;
};

