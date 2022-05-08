/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    // TODO: Implement this function.
    int length = strlen(password);
    bool flag_num = false;
    bool flag_char = false;
    bool flag_nonAlph = false;
    //Check bit by bit
    for (int i = 0; i < length; i++){
        char ch = password[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            flag_char = true;
        else if (ch >= '0' && ch <= '9')
            flag_num = true;
        else flag_nonAlph = true;
    }
    return (flag_char && flag_num && flag_nonAlph);
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
