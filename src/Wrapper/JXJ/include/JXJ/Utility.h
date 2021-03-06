#pragma once
#include "JXJLite.h"

#include <Poco/DateTime.h>
#include <string>
#include "DVR/DVRSession.h"
#include <Poco/Net/SocketAddress.h>
#include <map>




namespace DVR {
namespace JXJLite {

class JXJLite_API Utility
{
public:
	~Utility();

	typedef long HANDLE;
	typedef long DOWNLOAD_HANDLE;

	typedef struct FILEINFO
	{
		int ch;						//channel
		int size;					//file size
		char sFileName[108];		//file name
		__time64_t stBeginTime;		//file start time
		__time64_t stEndTime;		//file end time	
		HWND hwnd;
	} FILEINFO;

	typedef struct TIMEINFO
	{
		int ch;						//channel
		int size;					//file size
		char sFileName[108];		//file name
		__time64_t stBeginTime;		//file start time
		__time64_t stEndTime;		//file end time
		HWND hwnd;
	} TIMEINFO;

	struct DownloadInfo
	{
		DownloadInfo(){
			mDownloadHandle = -1;
			mDownloadSize = 0;
			mDownloadBeginTime = -1;
		}
		long mDownloadHandle;
		__int64 mDownloadSize;
		__int64 mDownloadBeginTime;
		//RecordFile mDownloadFile;
	};

	typedef struct DVRINFO
	{
		long nTotalChannel;
		std::map<__int32, std::string> channels;
	} DVRINFO;
	typedef struct CONDITION{} CONDITION;

	static const int success = 1;
	static Utility::HANDLE dvrHandle(const DVRSession& session);
	static std::string lastError(int error);
	static std::string lastError(const DVRSession& session);
	static void throwException(Utility::HANDLE handle);
	static void throwException(int rc, const std::string& addErrMsg = std::string());

	static Utility::HANDLE login(const Poco::Net::SocketAddress& _addr, 
								 const std::string& user, 
								 const std::string& password,
								 DVRINFO& info);

	static int logout(Utility::HANDLE handle);
	static int setTimeOut(std::size_t timeout, std::size_t times);

	static int Init();
	static int CleanUp();

	static int GetFile(Utility::HANDLE handle, const Utility::FILEINFO& fileinfo, const std::string& path);
	static int GetFile(Utility::HANDLE handle, const Utility::TIMEINFO& timeinfo, const std::string& path, bool merge);
	
	static int Playback(Utility::HANDLE handle, const Utility::FILEINFO& fileinfo);
	static int Playback(Utility::HANDLE handle, const Utility::TIMEINFO& timeinfo, int& Channel);

	static int FindFile(Utility::HANDLE handle, const Utility::TIMEINFO timeinfo, std::size_t timeout);


	static int stopPlayback(long lPlayHandle, int Channel);
	static int setPlaybackPos(__int64 playbackHandle, int Channel, __int32 pos);
	static int getPlaybackPos(__int64 playbackHandle, __int32 *pos);
	static int pausePlayback(long lPlayHandle, BOOL bPause);
	static int getDownloadPos(__int64 downloaJXJandle);
	static int stopDownload(long lPlayHandle, int Channel);

	typedef void(*EventCallbackType)(void* pVal);

	template <typename T, typename CBT>
	static bool registerUpdateHandler(Utility::HANDLE Handle, CBT callbackFn, T* pParam)
		/// Registers the callback for (1)(insert, delete, update), (2)(commit) or 
		/// or (3)(rollback) events. Only one function per group can be registered
		/// at a time. Registration is not thread-safe. Storage pointed to by pParam
		/// must remain valid as long as registration is active. Registering with
		/// callbackFn set to zero disables notifications.
		/// 
		/// See http://www.sqlite.org/c3ref/update_hook.html and 
		/// http://www.sqlite.org/c3ref/commit_hook.html for details.
	{
		typedef std::pair<CBT, T*> CBPair;
		typedef std::multimap<Utility::HANDLE, CBPair> CBMap;
		typedef typename CBMap::iterator CBMapIt;
		typedef std::pair<CBMapIt, CBMapIt> CBMapItPair;

		static CBMap retMap;

		if (retMap.find(Handle) == retMap.end())//insert callbackFn when key is noexist.
		{
			retMap.insert(std::make_pair(Handle, CBPair(callbackFn, pParam)));
			return true;
		}
		else //update callbackFn when key is exist.
		{
			CBMapItPair retMapRange = retMap.equal_range(Handle);
			for (CBMapIt it = retMapRange.first; it != retMapRange.second; ++it)
			{
				poco_assert(it->second.first != 0);
				if ((callbackFn == 0) && (*pParam == *it->second.second))
				{
					retMap.erase(it);
					return true;
				}

				if ((callbackFn == it->second.first) && (*pParam == *it->second.second))
				{
					it->second.second = pParam;
					return true;
				}
			}
		}

		return false;
	}

	template <typename T, typename CBT>
	static bool registerUpdateHandler(const DVRSession& session, CBT callbackFn, T* pParam)
		/// Registers the callback by calling registerUpdateHandler(sqlite3*, CBT, T*).
	{
		//return registerUpdateHandler(dvrHandle(session), callbackFn, pParam);
		return NULL;
	}


protected:	
	static int __stdcall JRecDownload(long lHandle, LPBYTE pBuff, DWORD dwRevLen, void* pUserParam);
	static int __stdcall JRecStream(long lHandle, LPBYTE pBuff, DWORD dwRevLen, void* pUserParam);

	//static void* eventHookRegister(void* Handle, EventCallbackType callbackFn, void* pParam);
private:
	Utility();
	Utility(const Utility&);
	Utility& operator = (const Utility&);
private:
	
};

}}
