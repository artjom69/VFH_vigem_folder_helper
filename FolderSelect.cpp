
#include "FolderSelect.h" 


FolderSelect::FolderSelect() {
	
}

FolderSelect::~FolderSelect() {}


void FolderSelect::create_folder(std::string folder_name) {  //sauce:https://stackoverflow.com/questions/9235679/create-a-directory-if-it-doesnt-exist
	this->folder_name = folder_name;
	std::experimental::filesystem::create_directory(folder_name);
}



void FolderSelect::move_folders(std::string target_folder) {
	//check / for folder names contains

}

void FolderSelect::list_all_subfolders() {
	//for (auto& current_directory : std::experimental::filesystem::recursive_directory_iterator("./"))
		//if (current_directory.is_directory())
//this->subffolder_list.push_back(current_directory.path().string());
}

