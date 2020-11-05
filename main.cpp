/*
Konsolenanwendung zur Sortierung von Vigem recording Daten.
2020.10.14  created by Artjom Muehlbeier
*/


#include <string>
#include <iostream>
#include <windows.h>
#include "FolderSelect.h"
#include "File.h"



FolderSelect folder;
File file;
int one_min_countdown;

void print_like_80ies(int i) {
	if (i == 0) {
		printf("   xxxxxx   \n");
		printf("   x    x   \n");
		printf("   x    x   \n");
		printf("   x    x   \n");
		printf("   xxxxxx   \n");
	}
	if (i == 1) {
		printf("     x      \n");
		printf("     x      \n");
		printf("     x      \n");
		printf("     x      \n");
		printf("     x      \n");
	}
	if (i == 2) {
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("    xxxxx      \n");
		printf("    x          \n");
		printf("    xxxxx      \n");
	}
	if (i == 3) {
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("    xxxxx      \n");
	}
	if (i == 4) {
		printf("    x   x      \n");
		printf("    x   x      \n");
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("        x      \n");
	}
	if (i == 5) {
		printf("    xxxxx      \n");
		printf("    x          \n");
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("    xxxxx      \n");
	}
	if (i == 6) {
		printf("    xxxxx      \n");
		printf("    x          \n");
		printf("    xxxxx      \n");
		printf("    x   x      \n");
		printf("    xxxxx      \n");
	}
	if (i == 7) {
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("      xx       \n");
		printf("       x       \n");
		printf("       x       \n");
	}
	if (i == 8) {
		printf("    xxxxx      \n");
		printf("    x   x      \n");
		printf("    xxxxx      \n");
		printf("    x   x      \n");
		printf("    xxxxx      \n");
	}
	if (i == 9) {
		printf("    xxxxx      \n");
		printf("    x   x      \n");
		printf("    xxxxx      \n");
		printf("        x      \n");
		printf("    xxxxx      \n");
	}
	if (i == 10) {
		printf("   x     xxxxxx   \n");
		printf("   x     x    x   \n");
		printf("   x     x    x   \n");
		printf("   x     x    x   \n");
		printf("   x     xxxxxx   \n");
	}
}
void counter_printer() {
	if(one_min_countdown >=55)
		std::cout << "\n* * * * * * \n";
	
	if (one_min_countdown >= 45)
		std::cout << "\n* * * * *  \n";
	
	if (one_min_countdown >= 35)
		std::cout << "\n* * * *   \n";
	
	if (one_min_countdown >= 25)
		std::cout << "\n* * *   \n";
	
	if (one_min_countdown >= 15)
		std::cout << "\n* *  \n";
	
	if (one_min_countdown >= 5)
		std::cout << "\n*   \n";

	one_min_countdown -= 1;
	
}

void screen_output() {
	system("cls");
	std::cout << "[UP] = new scenario, [DOWN] = save timestamp,  [RIGHT] = beta select scenario \n";

	std::cout << "\n******************************************************************* \n";

	std::cout << "actual   scenario: " << folder.folder_name << " \n";
	std::cout << "debug folder name: " << file.debug_folder_name << " \n";
	std::cout << "timestamp file name: " << file.timestamp_file_name << " \n";
	std::cout << "youngest timestamp name: " << file.youngest_timestamp << " \n";
	std::cout << "\n******************************************************************* \n";


	std::cout << "number  timestamps: " << file.number_timestamps_count << " \n";
	std::cout << "last timestamp age: " << file.age_youngest_timestamp_count << " \n";
	std::cout << "already driven:  \n\n\n";
	print_like_80ies(file.already_driven);
	std::cout << "\n 1_min countddown:\n";
}


//strictly procedural, program needs to do only 1 thing at the time
int main() {
	one_min_countdown = 0;
	file.check_if_timestamp_file_present();

	while (true) {

		screen_output();
		counter_printer();

		if (GetAsyncKeyState(VK_UP)) {
			std::cout << "enter new scenario name: \n";
			string folder_name_input;
			cin >> folder_name_input;
			folder.create_folder(folder_name_input);
			file.write_scenario_in_list(folder.folder_name);
			file.already_driven = 0;
		}
		


		if (GetAsyncKeyState(VK_DOWN)) {
			if (file.check_if_debug_present() && file.check_if_timestamp_file_present()) {
				file.write_timestamp_in_list();
				one_min_countdown = 60;
			}
			else
				std::cout << "Error: No VIGEM-timestamp found.\n";	
		}


		
		if (GetAsyncKeyState(VK_RIGHT)) {
			file.do_list_content_of_folder("./");
			std::cout << "choose your scenario folder, [0] = cancel\n\n";
			try {
				if (file.content_list.size() > 3) {
					for (int i = 0; i < file.content_list.size(); i++)
						std::cout << i + 1 << ": " << file.content_list[i + 1] << "\n";
				}
			}
			catch(...){}

			int command = 0;
			std::cin >> command;
			
			if (command != 0) {
				folder.folder_name = file.content_list[command].substr(2)  ;
				std::cout << "folder name: " << folder.folder_name << "\n";
				file.write_scenario_in_list(folder.folder_name);
			}
		}


		file.check_if_debug_present();
		file.count_timestamps_in_debug_folder();	
		Sleep(1000); //else cpu goes up to 40%
	}

	return 0;
}



