#include <iostream>
#include <fstream>
#include <string>
#include<regex>
#include <sstream>
#include <algorithm>


using namespace std;

using std::regex;
using std::string;
struct length {
	bool operator() (const string& a, const string& b)
	{
		return a.size() < b.size();
	}
};

std::string space2empty(std::string text) {
	const auto target = regex{ " " };
	const auto replacement = string{ "" };
	const auto value = string{ text };
	text = regex_replace(value, target, replacement);
	
	return text;
}
vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}
void closure(string attributes, vector<string> leftkeys, vector<string> righkeys ){

	vector<string> keyArray;
	int array_index = 0;
	int max_size = 0;
	string leftcankey;
	for (int i = 0; i < leftkeys.size(); i++){
		vector<string> cKey;
		//cout << leftkeys[i] << endl;
		//cout << righkeys[i] << endl;
		cKey.push_back(leftkeys[i]);
		cKey.push_back(righkeys[i]);
		for (int r = 0; r < 1; r++){
			const auto& value = righkeys[i];
				//std::cout << value << '\n';
				string rKey;
				for (auto c : value)
				{
					rKey.push_back(c);
					for (int t = i+1; t < leftkeys.size(); t++)
					{
						if (leftkeys[t] == rKey)
						{
							cKey.push_back(righkeys[t]);
						}
					}
					rKey.pop_back();
				}
					
			
			std::stringstream ss;
			for (size_t i = 0; i < cKey.size(); ++i)
			{
				if (i != 0)
					ss << "";
				ss << cKey[i];
			}
			std::string s = ss.str();
			keyArray.push_back(s);
			cout << leftkeys[i] << "=" << s<<endl;
			if (s.size() > max_size){
				max_size = s.size();
				array_index = i;
			}
			
//			leftcankey.append(leftkeys[i]);
			
		}
		
		


		
	}
	sort(keyArray.begin(), keyArray.end(), length());
	string key = keyArray.back();
	sort(key.begin(), key.end());
	leftcankey.append(leftkeys[array_index]);

	for (int i = 0,j=0; i < attributes.size(); i++)
	{
		if (!(attributes[i]== key[j])){
			//cout << attributes[i] << endl;
			for (int y = 0; y < keyArray.size(); y++){
				const auto& value = keyArray[y];
				for (auto c : value)
				{
					if (attributes[i] == c){
						key.append(keyArray[y]);
						for (auto c : value)
						{
							for (int e = 0; e < leftkeys.size(); e++){
								string n;
								n = c;


								if (n == leftkeys[e])
								{
									leftcankey.append(n);



									y = keyArray.size();
									sort(key.begin(), key.end());
									sort(leftcankey.begin(), leftcankey.end());
									j = 0;
									i = -1;
									break;
									//}
								}



							}
						}
					}
					
					
				}

			}
		}
		else{
			j++;
		}
		
	}
	cout << "Your Ans Key is " << leftcankey <<" = "<<key << endl;

	
}
int main()
{
	string STRING;
	ifstream infile;
	string attributes;
	infile.open("first.txt");
	getline(infile, attributes);
	cout << space2empty(attributes) << endl; 
	vector<vector<string>> givenDeps;
	vector<string> leftKeys;
	vector<string> rightKeys;

	while (!(infile.eof())) // To get you all the lines.
	{
		getline(infile, STRING); // Saves the line in STRING.
		cout <<space2empty(STRING) <<endl; // Prints our STRING.
		vector<string> givenDep;
		givenDep = split(space2empty(STRING), "->");
		leftKeys.push_back(givenDep[0]);
		rightKeys.push_back(givenDep[1]);

		givenDeps.push_back(givenDep);
	}
	closure(attributes, leftKeys,rightKeys);
	infile.close();
	system("pause");
	return 0;
}
