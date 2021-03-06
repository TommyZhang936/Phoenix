#pragma once

// System
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <tchar.h>
#include <map>
#include <assert.h> 
#include <ctime>
#include "io.h"
#include "direct.h"

// Self
#include "AbstractVendor.h"
#include "QMSqlite.h"
#include "QMFileSqlite.h"
#include "TestWindows.h"

// Json
#include "document.h"
#include "prettywriter.h"
#include "stringbuffer.h"
#include "ostreamwrapper.h"
#include "istreamwrapper.h"

// Exception
#include "LoginException.h"
#include "SearchFileException.h"


#define Test_Bug
#define Test_Filename

#define Vendor_DH	"大华"
#define Vendor_JXJ	"佳信捷"
#define Vendor_DZP	"迪智浦"
#define Vendor_HK	"海康"

#define Vendor_DH_Abbr		"DH"
#define Vendor_JXJ_Abbr		"JXJ"
#define Vendor_DZP_Abbr		"DZP"
#define Vendor_HK_Abbr		"HK"

#define MAX_SEARCH_COUNT 1000
#define ONE_DAY		 (24 * 60 * 60)
#define ONE_HOUR	 (60 * 60)
#define ONE_MINUTE	 (60)

typedef struct __ComTime
{
	uint8_t year;					//从1900开始, J_SDK_DEF_BASE_YEAR
	uint8_t month;
	uint8_t date;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t weekday;				//详情见JWeekDay
}ComTime;


class CCommonUtrl
{
public:
	CCommonUtrl();
	~CCommonUtrl();

	///     The object of instance class
	///     @param		None
	///     @return		Instances of the class object
	///     @see		
	///		@note		None
	static CCommonUtrl& getInstance();

	///     Create the file name
	///     @param		int channel -- Channel
	///     @param		const std::string& startTime -- The start of time
	///     @param		const std::string& endTime --  The end of time
	///     @param		const std::string& extensions --   The filename extension
	///     @return		File name
	///     @see		
	///		@note		The file name is composed of channels, start time and end time
	std::string MakeFileName(int channel, const std::string& startTime, const std::string& endTime, const std::string& extensions);

	///     Create folder path
	///     @param		const std::string basePath -- The root directory path
	///     @param		const std::string& startTimeZero -- The start time
	///     @param		const std::string& endTimeZero -- The end time
	///     @param		const std::string& venderName -- Vender name
	///     @param		int channel -- Channel
	///     @return		folder path
	///     @see		
	///		@note		None
	std::string MakeDownloadFileFolder(const std::string basePath, const std::string& startTimeZero, const std::string& endTimeZero, const std::string& venderName, int channel);

	///     The creation of a complete file path
	///     @param		std::string fileName -- File name
	///     @return		folder path
	///     @see		
	///		@note		None
	void MakeFolder(std::string fileName);

	///     Will get time divided into unit of data for a day
	///     @param		std::string fileName -- File name
	///     @return		Vector object
	///     @see		
	///		@note		None
	std::vector<time_range> MakeTimeRangeList(const time_range& range);

	///     Time_t data can be converted to string type of data to display
	///     @param		time_t time -- Time
	///     @return		Time measuring string
	///     @see		
	///		@note		None
	std::string MakeStrTimeByTimestamp(time_t time);
	
	// Json File Handle

	///     The download file of information save to a JSon file
	///     @param		const std::vector<RecordFile>& files -- Download the file information of object
	///     @param		const std::string& VenderName -- Vendor name
	///     @return		None
	///     @see		
	///		@note		None
	void SaveSearchFileListToFile(const std::vector<RecordFile>& files, const std::string& VenderName);

	///     The JSon file of information save to memory
	///     @param		None
	///     @return		std::vector<RecordFile> -- The object of a RecordFile 
	///     @see		
	///		@note		None
	std::vector<RecordFile> LoadSearchFileListFromFile();

	// DB Operation

	///     The download file of information save to database
	///     @param		const std::vector<RecordFile>& files -- Download the file information of object
	///     @return		None
	///     @see		
	///		@note		None
	void WriteFileListToDB(RECORD_FILE_LIST& recordFiles);

	// Search File to RecordFile
	RecordFile MakeDBFileToRecordFile(const readSearchVideo& rsv);


	///     Get the current time
	///     @param		None
	///     @return		The current time of a string
	///     @see		
	///		@note		None
	std::string GetCurTime();
};

