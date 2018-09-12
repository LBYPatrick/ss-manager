//
// Created by LBYPatrick on 2/6/2018.
//

#include "util.hpp"

void util::RemoveLetter(string & original_string, char letter) {
    string temp_buffer;
    bool   is_in_quote = false;
    for (char i : original_string) {
        if(i == '\"') {
            is_in_quote = !is_in_quote;
            continue;
        }
        else if(i != letter || is_in_quote) temp_buffer += i;
    }
    original_string = temp_buffer;
}

void util::ReportError(string message) {
    printf("[ERROR] %s\n", message.c_str());
}

void util::RemoveFile(string filename) {
    remove(filename.c_str());
}

void util::ShowHelp(vector<Help> option_list) {
    int max_option_length = 0;

    string print_buffer;

    //Get max option length for better formatting
    for(Help current_help : option_list) {
        max_option_length = current_help.option.length() > max_option_length ?
                            current_help.option.length() : max_option_length;
    }

    for(Help current_help : option_list) {
        print_buffer += current_help.option;

        for(int i = current_help.option.length(); i < max_option_length; ++i) {
            print_buffer += ' ';
        }

        print_buffer += " : ";
        print_buffer += current_help.description + "\n";
    }

    printf("%s",print_buffer.c_str());

}

bool util::IsFileExist(string filename) {

    vector<string> file_list = GetFileList();

    for(string & file : file_list) {
        if(filename == file) return 1;
    }
    return 0;

}

vector<string> util::SysExecute(string cmd) {

    ifstream reader;
    vector<string> return_buffer;
    string read_buffer;

#if DEBUG 
	printf("%s\n", cmd.c_str());
#endif
    system((cmd + "> output.data").c_str());



    reader.open("output.data");

    while(getline(reader,read_buffer)) {
        return_buffer.push_back(read_buffer);
    }

    reader.close();
	
	RemoveFile("output.data");

#if DEBUG
	for (string & line : return_buffer) {
		printf(line.c_str());
	}
#endif

    return return_buffer;

}

vector<string> util::ReadFile(string path) {
	return util::ReadFile(path, true);
}

vector<string> util::ReadFile(string path, bool is_parsed) {
#if DEBUE == true
	printf("READ\n");
#endif
	ifstream r(path.c_str());
	stringstream read_buffer;
	vector<string> file_buffer;

	if (!r.is_open()) {
		return vector<string>();
	}
	read_buffer << r.rdbuf();
	r.close();

	if (!is_parsed) return { read_buffer.str() };
	else {
		string temp = read_buffer.str();
		vector<int> results = util::SearchString(temp, '\n');
		bool is_newline_head = false;

		//Quit if it's a file without "\n"
		if (results.size() == 0) {
			return { temp };
		}

		if (results[0] == 0) {
			file_buffer.push_back("");
			file_buffer.push_back(SubString(temp, 1, results[1]));
			is_newline_head = true;
		}
		else {
			file_buffer.push_back(SubString(temp, 0, results[0]));
		}

		for (int i = is_newline_head; i < results.size(); ++i) {
			if (i + 1 <= results.size() - 1) {
				file_buffer.push_back(SubString(temp, results[i] + 1, results[i + 1]));
			}
			else {
				file_buffer.push_back(SubString(temp, results[i] + 1, results.size()));
			}
		}
	}
	return file_buffer;
}


int util::Search(string str, vector<string> match_list, bool precise) {
    for(int i = 0; i < match_list.size(); ++i) {

        if(precise && match_list[i] == str) {
            return i;
        }
        else if(!precise && str.find(match_list[i]) != string::npos) {
            return i;
        }
    }

    return -1;
}

int util::Search(string str, vector<string> match_list) {
    return Search(str,match_list,false);
}

YAML util::GetYaml(string line)
{
	YAML out;

	if (line.find(":") == -1) {
		return YAML();
	}

	out.level = line.find_first_not_of(" ");
	out.left = SubString(line,out.level, line.find(":"));
	out.right = SubString(line,line.find(":") + 1, line.find_last_not_of(" ") + 1);

	//Remove Trailing & starting spaces
	out.left = SubString(out.left,0,out.left.find_last_not_of(" ") + 1);
	out.right = SubString(out.right,out.right.find_first_not_of(" "), out.right.size());


	if (out.left.find(R"(")") != -1) {
		out.left = SubString(out.left,1,out.left.size() - 1);
	}

	if (out.right.find(R"(")") != -1) {
		out.right = SubString(out.right,1,out.right.size() - 1);
	}

	return out;
}

string
util::SubString(string str, int left, int stop) {
	int length = stop - left;
	
	//Out-of-bound fix
	if (left < 0) left = 0;
	if (stop > str.size()) stop = str.size();

	return str.substr(left,length);
}



bool util::IsProcessAlive(string pid) {

    vector<string> cmd_buffer = SysExecute("ps -p " + pid);

    return cmd_buffer.size() > 1;
}

bool util::IsTheSame(string str, string key, bool is_precise, bool is_case_sensitive)
{
	if (!is_case_sensitive) {
		for (int i = 0; i < str.size(); ++i) {
			str[i] = toupper(str[i]);
		}
		for (int i = 0; i < key.size(); ++i) {
			key[i] = toupper(key[i]);
		}
	}
	
	if (is_precise) {
		return str == key;
	}
	else {
		return (str.find(key) != -1) || (key.find(str) != -1);
	}
}

vector<string> 
util::GetFileList(string directory) {

    vector<string> console_buffer = SysExecute("ls -p " + directory + " -1");

    vector<string> output_buffer;

    for (string & line : console_buffer) {

        if(line.find_last_of("/") == -1 && line.find("output.data") == -1) {
            output_buffer.push_back(line);
        }
    }

    return output_buffer;
}

vector<string> util::GetFolderList(string directory) {

    vector<string> console_buffer = SysExecute("ls -p " + directory + " -1");
    vector<string> output_buffer;

    for (string & line : console_buffer) {

        if(line.find_last_of("/") != -1) {
            output_buffer.push_back(SubString(line,0, line.size() -1));
        }

    }

    return output_buffer;
}

vector<string> util::GetFolderList() {
    return GetFolderList("./");
}

vector<string> util::GetFileList() {
    return GetFileList("./");
}

bool util::WriteFile(string filename, vector<string> content)
{
	ofstream o;
	string buf;

	o.open(filename);

	if (!o.is_open()) return 0;

	for (int i = 0; i < content.size(); ++i) {
		buf += content[i] + "\n";
	}

	o.write(buf.c_str(), buf.size());

	o.close();

	return 1;
}

vector<int> util::SearchString(string str, char key) {
	vector<int> r;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == key) {
			r.push_back(i);
		}
	}

	return r;
}