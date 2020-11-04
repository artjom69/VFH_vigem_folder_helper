#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "File.h"
#include <fstream>
#include <windows.h>
#include <sstream>

//This is needed for virtually everything in BrowseFolder.
#include <shlobj.h>   

class File
{
public:
	File();
	~File();
	int number_timestamps_count, age_youngest_timestamp_count;
	void write_timestamp_in_list();
	void write_scenario_in_list(std::string scenario_name);

	void do_list_content_of_folder(std::string folder_name);
	bool check_if_debug_present();	
	void count_timestamps_in_debug_folder();
	bool check_if_timestamp_file_present();
	std::string timestamp_file_name;
	int already_driven;
	std::string youngest_timestamp;
	std::string debug_folder_name;
	std::vector<std::string> content_list;
	std::string  select_folder();  //sauce: https://www.codeproject.com/Articles/2604/Browse-Folder-dialog-search-folder-and-all-sub-fol
private:
	

	int add_up_numbers(std::string input);
	std::string trim_string(std::string input_str, std::string criteria);

	void count_age_of_youngest_timestamp();//needs imperative count_timestamps_in_debug_folder() first
	std::string debug_reference_name = "ADCAMM_DEBUG";
	std::string timestamp_reference_name = "timestamp";
	std::string last_known_timestamp;
	bool check_if_present(std::string input);
	
	std::vector<std::string> debug_content_list;
	bool has_digit(const std::string& s);
	void create_file();
};

