#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
using namespace std;

struct PyApduTool {
    uint8_t CLA;
    uint8_t INS;
    uint8_t P1;
    uint8_t P2;
    uint8_t LC;
    uint8_t LE;
    vector<uint8_t> Data;
};

enum StatusCode {
    Success = 0x9000,
    FileNotFound = 0x6A82,
    WrongParameters = 0x6A86,
    Unknown = 0x6F00
};

uint8_t hexToByte(const string &hex) {
    return static_cast<uint8_t>(stoi(hex, nullptr, 16));
}

StatusCode checkSelectCommand(const PyApduTool &MF) {
    if (MF.Data.size() == 2 && MF.Data[0] == 0x3F && MF.Data[1] == 0x00) return Success;
    if (MF.Data.size() == 2 && (MF.Data[0] & 0xF0) == 0x7F)  return Success;
    if (MF.Data.size() == 2 && (MF.Data[0] & 0xF0) == 0x4F) return Success;
    if (MF.Data.empty())  return WrongParameters;
    return FileNotFound;
}

void Response(const PyApduTool &MF) {
    cout << "Send: " << " ";
    cout << hex << setw(2) << setfill('0') << (int)MF.CLA << " ";
    cout << hex << setw(2) << setfill('0') << (int)MF.INS << " ";
    cout << hex << setw(2) << setfill('0') << (int)MF.P1 << " ";
    cout << hex << setw(2) << setfill('0') << (int)MF.P2 << " ";
    cout << hex << setw(2) << setfill('0') << (int)MF.LC << " ";

    if(MF.LE > 0)
        cout << hex << setw(2) << setfill('0') << (int)MF.LE << " ";

    for (const auto& byte : MF.Data) {
        cout << hex << setw(2) << setfill('0') << (int)byte << " ";
    }
    cout << dec << endl;
    StatusCode status = checkSelectCommand(MF);
    cout << "Recv: " << hex << status << dec << endl;
}

int main(){
    PyApduTool MF;

    string input;

    cout << "Enter Select values: \n";
    
    cout << "CLA : ";
    cin >> input;
    MF.CLA = hexToByte(input);

    cout << "INS : ";
    cin >> input;
    MF.INS = hexToByte(input);

    cout << "P1 : ";
    cin >> input;
    MF.P1 = hexToByte(input);

    cout << "P2 : ";
    cin >> input;
    MF.P2 = hexToByte(input);

    cout << "Data (space-separated hex bytes): ";
    cin.ignore();  // Similar to fflush(stdin); in c

    getline(cin, input);  
    // This reads an entire line from the user input (until you press Enter \n).
    // It stores the full line in the string input.

    // User types: 3F 00 12 AB
    // input = "3F 00 12 AB"

    istringstream iss(input);
    // It creates a "string stream" from the input string.

    string byte;
    while(iss >> byte) {
        MF.Data.push_back(hexToByte(byte));
    }

    MF.LC = static_cast<uint8_t>(MF.Data.size());
    MF.LE = 0;



    Response(MF);
    return 0;
}