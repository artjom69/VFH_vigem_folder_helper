#include "File.h"



File::File(){
	this->number_timestamps_count = 0;
	this->age_youngest_timestamp_count = 0;
	this->debug_folder_name = "";
	this->youngest_timestamp = "";
	this->timestamp_file_name = "--";
	this->already_driven = 0;
}


File::~File(){
}


void File::write_timestamp_in_list() {

	std::ofstream ofile(this->timestamp_file_name, std::ios::out | std::ios::app);

	if (ofile.is_open()){
		ofile << this->youngest_timestamp << std::endl; // this->trim_string(this->youngest_timestamp, "\"");
		//ofile << this->youngest_timestamp << std::endl;
		std::cout << "operation successfully performed\n";
		ofile.close();
		this->already_driven += 1;
	}
	else{
		std::cout << "Error opening file";
	}

	
	
}

void File::write_scenario_in_list(std::string scenario_name){
	std::ofstream ofile(this->timestamp_file_name, std::ios::out | std::ios::app);

	if (ofile.is_open()) {
		ofile <<std::endl << scenario_name << std::endl;
		ofile.close();
		std::cout << "operation successfully performed\n";
	}
	else {
		std::cout << "Error opening file";
	}

}

void File::create_file() {
	
}

void File::count_timestamps_in_debug_folder() {
	this->number_timestamps_count = 0;
	this->do_list_content_of_folder(this->debug_folder_name);
	
	
	for (int i = 0; i < this->content_list.size(); i++) {
		bool is_included = false;

		std::size_t found = content_list[i].find("MF4");
		if (this->has_digit(this->content_list[i])  && found != std::string::npos ) {
			
			for (int j = 0; j < this->debug_content_list.size(); j++) {
				if (this->content_list[i] == this->debug_content_list[j]) {
					is_included = true;
					this->number_timestamps_count += 1;
				}
			}
			if (!is_included) {
				this->debug_content_list.push_back(this->content_list[i]);
				this->number_timestamps_count = 0;
				this->youngest_timestamp.clear();
				this->youngest_timestamp = this->trim_string(this->content_list[i], "\"");
			}
		}
	}
	
	this->count_age_of_youngest_timestamp();
}

bool File::check_if_timestamp_file_present(){
	if (this->check_if_present(this->timestamp_reference_name)) {

		for (int i = 0; i < this->content_list.size(); i++) {
			//std::cout << "list content: " << this->content_list[i] << "\n";
			std::size_t found = this->content_list[i].find(this->timestamp_reference_name);
			if (found != std::string::npos) {
				this->timestamp_file_name = content_list[i];
			}
		}
		return true;
	}

	else
		return false;
}

bool File::check_if_present(std::string input) {
	
	this->do_list_content_of_folder("./");
	for (int i = 0; i < this -> content_list.size(); i++) {
		std::size_t found = content_list[i].find(input);
		if (found != std::string::npos)
			return true;
	}
	return false;
}

bool File::has_digit(const std::string & s) {
	return (s.find_first_of("0123456789") != std::string::npos);
}

void File::do_list_content_of_folder(std::string folder_name) {
	while(this->content_list.size()>0)
		this->content_list.clear();
	
	for (const auto & entry : std::experimental::filesystem::directory_iterator(folder_name)) 
		this->content_list.push_back(entry.path().string());
	
}

bool File::check_if_debug_present(){
	
	if (this->check_if_present(this->debug_reference_name)) {
		
		for (int i = 0; i < this->content_list.size(); i++) {
			std::size_t found = content_list[i].find(this->debug_reference_name);
			if (found != std::string::npos) {
				this->debug_folder_name = content_list[i];
			}
		}
		return true;
	}
	
	else
		return false;
}

std::string File::select_folder(){
	
	TCHAR path[MAX_PATH];
	BROWSEINFO bi = { 0 };
	//bi.lpszTitle = ("All Folders Automatically Recursed.");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		// get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//Set the current directory to path
		SetCurrentDirectory(path);

		//Begin the search
		std::string some_path;
		some_path = path;  //konfigurationseigenschaften, allgemein, Multibyte-Zeichensatz verwenden
		std::wstring tmp(some_path.begin(), some_path.end());
		
	
		
		// free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		//setup converter, sauce : https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
			using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
		return  converter.to_bytes(tmp);
	
	}
}



int File::add_up_numbers(std::string input){
	int counter = 0;
	for (int i = 0; i < input.size(); i++) {
		std::string s(1, input[i]);
		if(this->has_digit(s))
			counter += input[i];
	}
	return counter;
}

std::string File::trim_string(std::string input_str, std::string critetria){
	/*int pos_of_last_criteria = 0;
	for (int i = 0; i < input_str.size(); i++) {
		std::size_t found = input_str.find(critetria);
		if (found != std::string::npos)
			pos_of_last_criteria = i;
	}
	return input_str.substr(pos_of_last_criteria, input_str.size());*/
	return  input_str.substr(46);//brutal
}

void File::count_age_of_youngest_timestamp(){
	
	if (this->last_known_timestamp == this->youngest_timestamp && this->number_timestamps_count>0)
		this->age_youngest_timestamp_count += 1;
	else
		this->age_youngest_timestamp_count = 0;

	this->last_known_timestamp = this->youngest_timestamp;
	
}

