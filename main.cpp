/* 
 * File:   main.cpp
 * Author: Beau
 *
 * Created on December 6, 2018, 8:40 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string findId(string input){
    string tmp;
    int x = 0;
    while (input[x] != '#'){
        x++;
    }
    x += 1;
    while (input[x] != ' '){
        tmp += input[x];
        x++;
    }
    
    return tmp;
}

struct position {
    int x = 0;
    int y = 0;
};

position findPosition(string input){
    position tmpPos;
    string tmp;
    
    int x = 0;
    while (input[x] != '@'){
        x++;
    }
    x += 1;
    while (input[x] != ','){
        tmp += input[x];
        x++;
    }
    
    tmpPos.x = atoi(tmp.c_str());
    if (!tmp.empty())
        tmp.clear();
    
    x++;
    while (input[x] != ':'){
        tmp += input[x];
        x++;
    }
    
    tmpPos.y = atoi(tmp.c_str());
    
    return tmpPos;
}

struct size {
    int x = 0;
    int y = 0;
};

size findSize(string input){
    size tmpSize;
    string tmp;
    
    int x = 0;
    while (input[x] != ':'){
        x++;
    }
    x++;
    while (input[x] != 'x'){
        tmp += input[x];
        x++;
    }
    
    tmpSize.x = atoi(tmp.c_str());
    if (!tmp.empty())
        tmp.clear();
    x++;
    
    while (input[x] != '\0'){
        tmp += input[x];
        x++;
    }
    
    tmpSize.y = atoi(tmp.c_str());
    
    return tmpSize;
}

int main() {
    string output;
    ifstream input;
    
    input.open("input.txt");
    
    //Original input at index
    vector<string> lines;
    
    //Parallel vectors
    vector<string> id;
    vector<position> position;
    vector<size> size;
    
    //Map that stores the number of claims in a spot
    vector<vector<int>> map;
    
    if (input.is_open()){
        while (!input.eof()){
            getline(input, output);
            lines.push_back(output);
            id.push_back(findId(output));
            position.push_back(findPosition(output));
            size.push_back(findSize(output));
        }
    }
    
    //Initialize map
    //Dynamic size based on positions
    int mapHeight = 0;
    int mapWidth = 0;
    
    //Find map dimensions
    for (int x = 0; x < lines.size(); x++){
        //Get max x
        if (mapWidth < (position[x].x + size[x].x))
            mapWidth = (position[x].x + size[x].x);
        
        //Get max y
        if (mapHeight < (position[x].y + size[x].y))
            mapHeight = (position[x].y + size[x].y);
    }
    
    //Create map
    for (int x = 0; x < mapWidth; x++){
        vector<int> mapLine;
        for (int y = 0; y < mapHeight; y++){
            mapLine.push_back(0);
        }
        map.push_back(mapLine);
    }
    
    //Fill in map data
    for (int x = 0; x < lines.size(); x++){
        int startX = position[x].x;
        int endX = position[x].x + size[x].x - 1;
        int startY = position[x].y;
        int endY = position[x].y + size[x].y - 1;
        
        for (int posX = startX; posX <= endX; posX++){
            for (int posY = startY; posY <= endY; posY++){
                map[posX][posY] += 1;
            }
        }
    }
    
    int overlapping = 0;
    
    //Find the overlapping
    for (int x = 0; x < mapWidth; x++){
        for (int y = 0; y < mapHeight; y++){
            if (map[x][y] > 1){
                overlapping++;
            }
        }
    }

    //Find the input that doesn't overlap
    for (int x = 0; x < lines.size(); x++){
        int startX = position[x].x;
        int endX = position[x].x + size[x].x - 1;
        int startY = position[x].y;
        int endY = position[x].y + size[x].y - 1;
        
        bool valid = true;
        for (int posX = startX; posX <= endX; posX++){
            for (int posY = startY; posY <= endY; posY++){
                if (map[posX][posY] > 1)
                    valid = false;
            }
        }
        if (valid)
            cout << "ID " << id[x] << " is valid." << endl;
    }
    
    /*cout << "---This is the map---" << endl;
    for (int y = 0; y < mapHeight; y++){
        for (int x = 0; x < map.size(); x++){
            cout << "[" << map[x][y] << "]";
        }
        cout << endl;
    }
    cout << endl;*/
    
    cout << "There are " << overlapping << " square(s) overlapping." << endl;
    
    return 0;
}

