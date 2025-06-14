

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;



void Logein();
void ShowATMMainMnueScreen();


struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
enum enATM
{
    eQuickWithdraw = 1,
    eNormalWithraw = 2,
    eDeposit = 3,
    eCheadBalance = 4,
    eLogout = 5
};


string ClientsFileName = "Clients.txt";
sClient Client;

/* 
    while (getline(MyFile, Line))
    {
     string TO stClientData
     stClientData TO vClients
    }

*/

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /*erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    //////////////////////////////////////////

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}


string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}



bool FindClientByAccountNumber(string AccountNumber, string PIN, sClient& Client)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PIN)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool DespoitBalanceToClient( double Amount)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "Do you want do this transactions?  y/n   ";
    char cha = 'y';
    cin >> cha;
    if (cha == 'Y' || cha == 'y')
    {
        for (sClient& C : vClients)
        {
            if (Client.AccountNumber == C.AccountNumber)
            {
                C.AccountBalance = C.AccountBalance + Amount;
                SaveCleintsDataToFile(ClientsFileName,vClients);
                cout << "Done successfully. Your Balance new is :";
                cout << C.AccountBalance << endl;
                break;
            }
        }
        return false;
    }
}



string ReadAccountName()
{
    cout << "Please enter the account name.    ";
    string Name = "";
    getline(cin >> ws, Name);
    return Name;
}
string ReadPIN()
{
    cout << "Please enter the PIN.    ";
    string PIN = "";
    getline(cin >> ws, PIN);
    return PIN;
}
enATM ReadClientChoose()
{
    cout << "Choose what do you want from [1] to [5].    ";
    short Choose;
    cin >> Choose;
    return (enATM)Choose;
}
int ReadPositiveNumber(string message)
{
    int num = 0;
    cout << message << "    ";
    cin >> num;
    while (num < 0)
    {
        cout << "That's not a positive number! please enter a positive number.\n";
        cout << message << "    ";
        cin >> num;
    }
    return num;
}


void GoBackManiMunue()
{
    cout << "Please press any key to go back to Main Menue...";
    system("pause>0");
    ShowATMMainMnueScreen();
}



//1
short MenueWithdraw()
{
    cout << "===================================\n";
    cout << "          Quick Withdraw      \n";
    cout << "===================================\n";
    cout << "      [1] 20        [2] 50\n";
    cout << "      [3] 100       [4] 200\n";
    cout << "      [5] 400       [6] 600\n";
    cout << "      [7] 800       [8] 1000\n";
    cout << "      [9] Exit      \n";
    cout << "===================================\n\n";
    
    cout << "Your balance is " << Client.AccountBalance << endl << endl;
    cout << "Choose what to withdraw from [1] to [9] ?   ";
    short Choose = 0;
    cin >> Choose;
    return Choose;
}
short GetAmountToWithdraw(short Choose)
{
    switch (Choose)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 500;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    case 9:ShowATMMainMnueScreen();
    default: 
        break;
    }
}
void ShowQuickWithdrawScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    short Choose = MenueWithdraw();
    short AmountToWithdraw = GetAmountToWithdraw(Choose);

    if (AmountToWithdraw > Client.AccountBalance)
    {
        cout << "You cant't withdarw this amount.";
        GoBackManiMunue();
    }
    DespoitBalanceToClient(-1 * AmountToWithdraw);
    Client.AccountBalance -= AmountToWithdraw;
}




//2
int ReadAmountNormalWithdraw()
{
    cout << "Please enter a mount 5'times.  ";
    int Amount = 0;
    cin >> Amount;
    while (Amount % 5 != 0)
    {
        cout << "This amount not avalibal. \n";
        cout << "Please enter a mount 5'times.  ";
        cin >> Amount;
    }
    return Amount;
}
void ShowNormalWithdraw()
{
    cout << "==============================\n";
    cout << "      Whithdraw Screen     \n";
    cout << "==============================\n";


    double Amount = ReadAmountNormalWithdraw();
    if (Amount > Client.AccountBalance)
    {
        cout << "You can't withdarw this amount, can't efort it.";
        GoBackManiMunue();
    }

    DespoitBalanceToClient(-1* Amount);
    Client.AccountBalance -= Amount;
    
}

// 3
void ShowDepositScreen()
{
    vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    cout << "==============================\n";
    cout << "        Desposit Screen     \n";
    cout << "==============================\n";

    int Amount = ReadPositiveNumber("Please enter the amount.");
    DespoitBalanceToClient(Amount);
    Client.AccountBalance += Amount;
}





void ShowCheakBalanceScreen()
{
    cout << "Your Balance is ";
    cout << Client.AccountBalance << endl << endl;
}




void PerFormMainMenue(enATM PerForm)
{
    switch (PerForm)
    {
    case eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackManiMunue();
        break;
    case eNormalWithraw:
        system("cls");
        ShowNormalWithdraw();
        GoBackManiMunue();
        break;
    case eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackManiMunue();
        break;
    case eCheadBalance:
        system("cls");
        ShowCheakBalanceScreen();
        GoBackManiMunue();
        break;
    case eLogout:
        Logein();
        break;
    default:
        break;
    }
}
void ShowATMMainMnueScreen()
{
    system("cls");
    cout << "====================================================\n";
    cout << "                ATM Main Menue Screen               \n";
    cout << "====================================================\n";
    cout << "            [1] Quick Withdraw.\n";
    cout << "            [2] Normal Withdraw.\n";
    cout << "            [3] Deposit.\n";
    cout << "            [4] Check Balance.\n";
    cout << "            [5] Logout.\n";
    cout << "====================================================\n";

    PerFormMainMenue(ReadClientChoose());
}



bool LoadClientInfo(string Name, string PIN, sClient & Client)
{
    if (FindClientByAccountNumber(Name, PIN, Client))
        return true;
    else
        return false;
}
void Logein()
{
    string Name = "", PIN = "";
    bool LogeinFaild = false;

    do
    {
        system("cls");
        cout << "------------------------\n";
        cout << "        logein          \n";
        cout << "------------------------\n";

        if (LogeinFaild)
            cout << "Not avalibl.\n\n";
        Name = ReadAccountName();
        PIN = ReadPIN();
        LogeinFaild = !LoadClientInfo(Name, PIN, Client);
    } while (LogeinFaild);
    ShowATMMainMnueScreen();
}


int main()
{
    Logein();
    return 0;
}