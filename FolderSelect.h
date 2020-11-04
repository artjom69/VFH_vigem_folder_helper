#pragma once
#pragma once
//#include <vector>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <shlobj.h>  //This is needed for virtually everything in BrowseFolder. 
#include <filesystem>
#include <filesystem>
#include <vector>
#include <experimental/filesystem>


using namespace std;

class FolderSelect
{

private:


	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	

	//first data gets into temp
	
	std::string   temp_certificate;
	std::string   temp_schultes_xlsx;

	//second  temp gets into unsorted vectors
	struct struct_vehicle { std::string chassis_number; std::string vehicle; };
	struct struct_equipment { std::string chassis_number; std::string equipment; };
	struct struct_5102 { std::string chassis_number; std::string export_5102; };
	struct struct_5103 { std::string chassis_number; std::string export_5103; };
	struct struct_asep { std::string chassis_number; std::string export_asep; };

	//vectors get sorted by chassis numbers
	struct struct_sorted_output { std::string chassis_number; std::string data; };
	std::vector<struct_sorted_output>  sorted_output_vec;


	std::string output_name;




	


	

public:
	FolderSelect();
	~FolderSelect();

	std::string folder_name;	
	void create_folder(std::string folder_name);
	void move_folders(std::string target_folder);
	void list_all_subfolders();
	std::vector<std::string> subffolder_list;


};