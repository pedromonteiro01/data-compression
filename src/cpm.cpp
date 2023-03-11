#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::reverse;
using std::string;

// read content of file and store it in a string
string read_file(string filename)
{
    string content;
    ifstream input(filename);
    if (input)
    {
        input.seekg(0, ios::end);
        content.resize(input.tellg());
        input.seekg(0, ios::beg);
        input.read(&content[0], content.size());
        input.close();
    }
    return content;
}

// string best_char(std::vector<std::string> vector, std::vector<int> pos)
// {
//     std::map<std::string, std::vector<int>> map;
//     int c,a,t,g = 0;
//     if (pos.size() > 1){
//         for (int j = 0; j < pos.size(); j++){
//             if (pos[j] + 1 < vector.size()){
//                 char c = vector[pos[j]+1].back();
//             }
//         }
//     }
// }

int main()
{
    // cout << "Hello, World!\n";
    int k = 5; // k is the sliding window
    int hits = 0; // hits
    int fails = 0; // fails
    string content = read_file("test.txt"); // get file content
    std::map<std::string, std::vector<int>> hash_map; // create hashmap to store K strings and its positions
    std::vector<std::string> my_vector; // create vector to store the chunks 
    for (int i = 0; i < content.size() - k + 1; ++i)
    {
        std::string substring = content.substr(i, k);
        my_vector.push_back(substring);
        if (hash_map.find(substring) != hash_map.end())
        {

            int position = hash_map[substring].back();   // get the previous position of the chunk
            hash_map[substring].push_back(i);   // add the chunk current position to the hashmap
            if (i + k < content.size())
            {
                if (position + 1 < my_vector.size())
                {
                    char next_char = my_vector[position + 1].back();
                    cout << substring << " (previous positions: ";
                    for (int pos : hash_map[substring]) {
                        if (pos != i) {
                            cout << pos << ", ";
                        }
                    }
                    cout << i << ") " << "Pred char: " << next_char << " - Correct char: " << content[i+k] << endl;
                    if (next_char == content[i+k])
                        hits++;
                    else
                        fails++;
                }
            }
        }
        else
        {
            cout << substring << endl;
            hash_map[substring] = std::vector<int>{i}; // add K-string to hashmap
        }
    }
    cout << "Hits: " << hits << endl;
    cout << "Fails: " << fails << endl;
    return 0;
}
