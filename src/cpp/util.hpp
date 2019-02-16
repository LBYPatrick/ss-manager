//
// Created by LBYPatrick on 2/6/2018.
//

#pragma once
#include "includes.hpp"

namespace util {
    void RemoveLetter(string & original_string, char letter);
    void ReportError(string message);
    void RemoveFile(string filename);
	void AppendStringVector(vector<string> & left, vector<string> & right);
	void PrintLines(vector<string> arr);
	void Print(string str);
    void ShowHelp(vector<TableElement> option_list);
	void PercentageBar(int current, int total);
	void SetVisualizing(bool is_enable);
	bool IsFileExist(string path);
    bool IsProcessAlive(string pid);
	bool IsTheSame(string str, string key, bool is_precise, bool is_case_sensitive);
	bool IsLineVaild(string & line, FileFilter filter);
	string GetEncodedBase64(string ascii);

	vector<string> Make2DTable(vector<TableElement> table);
    vector<string> SysExecute(string cmd);
    vector<string> SysExecute(string cmd,bool output);
	vector<string> ReadFile(string path);
	vector<string> ReadFile(string path, FileFilter filter);
    vector<string> GetFileList(string directory);
    vector<string> GetFolderList(string directory);

	YAML DecodeYamlLine(string line);
	
	string SubString(string str, size_t left, size_t stop);
	string GetMachineIP();

    int MatchWithWords(string str, vector <string> match_list, bool precise);
	
	//Overloaded Methods
	vector<string> GetFileList();
	bool WriteFile(string filename, vector<string> content);
	vector <size_t> SearchString(string str, char key);
    vector <size_t> SearchString(string str, char key, size_t left, size_t stop);
	vector<string> GetFolderList();
	int MatchWithWords(string str, vector <string> match_list);

	class QuickSort {
	public:

		static void Sort(vector<SortItem> &arr, size_t low, size_t high);
		static vector<size_t> Sort(vector<long long> & arr, size_t low, size_t high);
		static vector<size_t> Sort(vector<long long> & arr);

	private:
		static size_t Partition(vector<SortItem> &arr, size_t low, size_t high);
	};

};