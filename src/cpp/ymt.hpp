#pragma once

#include "includes.hpp"
#include "parser.hpp"

class ymt {
public:
	static void RunConfig();
    static void StopConfig();
    static void SetExtraParam(string extra_param);
	static void SetAttribute(YMTAttributes attribute, string value);
	static vector<SSLog> GetFormattedData();
	static vector<string> GetFormattedStringData();
	static vector<string> GetFormattedStringData(bool is_readable);
	static bool PrintFormattedData(bool is_readable);
	static bool PrintFormattedData(bool is_readable, string output_filename);
	static vector<string> GetStatistics();
	static vector<string> GetUserInfo();
    static bool GetPortLog(YFile & buffer);
	static void SetFileName(string filename);
	static string GetSSShareLink(Parser & user);
private:
    static string RunUser(Parser &p);
	static bool PrintFormattedData(bool is_readable, bool is_write);
    static void CleanSyslog();
    static void UpdateUsers();
	static bool UpdateLog();
    static vector<PIDInfo> GetPIDTable();
    static void UpdatePIDTable();
};