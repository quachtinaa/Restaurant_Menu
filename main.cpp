// Tina Quach
// COSC-1437-58002 - Dr.T
// Date: 04/25/2024
// menu-driven restaurant program
// Credit to Dr. T for making the outline and menu

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "input_validation.h"

using namespace std;

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;    
  public:
    MenuItem(){name = "Default Name", itemCost = 0.0, desc = "Default Description", addLetter = '\0', removeLetter = '\0', count = 0;} // default constructor

    // setters, mutators
    void setName(string n){name = n;}
    void setItemCost(double i){itemCost = i;}
    void setDesc (string d) {desc = d;}
    void setAddLetter (char a) {addLetter = a;}
    void setRemoveLetter (char r) {removeLetter = r;}
    void setCount (int c) {count = c;}

    // getters, accessors
    string getName() const {return name;}
    double getItemCost() const {return itemCost;}
    string getDesc() const {return desc;}
    char getAddLetter() const {return addLetter;}
    char getRemoveLetter() const {return removeLetter;}
    int getCount() const {return count;}

};

// prototypes
void populateMenu (vector<MenuItem> &entireMenu);
void showMenu (vector<MenuItem> &m);
void acceptOrder (vector<MenuItem> &m);
void printReceipt(vector<string> itemNames, vector<double> itemCosts, vector<MenuItem> m, double, double, double, double, double, char, double);


int main()

{       
  char orderAgain = '\0';
  // object of MenuItem class
  do
    {
      cout << "\033[2J\033[1;1H";
      vector<MenuItem> wholeMenu; 
  
      populateMenu(wholeMenu); // put some default values in the menu
      showMenu(wholeMenu); // print the current data of the menu on screen 
      acceptOrder(wholeMenu); 

       // ask user if they would like to order again
       cout << "\nWould you like to order again? (Y/N): ";
       orderAgain = validateChar(orderAgain);
     
    } while (orderAgain != 'N' && orderAgain != 'n');

  cout << "\nIt was a pleasure having business with you! Thank you for coming to 'Lettuce Eat' and please come again! 👋" << endl;
  
  return 0;
}

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Lemonade", "Fruit Tart", "Calamari", "Veggie Wrap", "Fish Fillet", "Smoked Steak"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  vector<string> defaultDescriptions = {"Refreshing beverage packed w/ antioxidants      ", "Tangy, sweet citrus drink                       ", "Flaky pastry filled w/ fresh fruit and custard  ", "Crispy, golden squid rings w/ spicy mayo sauce  ", "Fresh veggies within a soft tortilla            ", "Seasoned fish fillet w/ tangy tartar sauce      ", "Premium steak w/ a side of mashed potatoes      "};
  vector<double> defaultItemCosts = {3.25, 3.25, 5.50, 9.75, 11.75, 18.75, 20.75 };
  // add each item to the default list efficiently
  for(int i = 0; i < numItems; i++)
  {
    entireMenu[i].setName(defaultMenuNames[i]);
    entireMenu[i].setAddLetter(defaultAddLetters[i]);
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(defaultItemCosts[i]); 
    entireMenu[i].setCount(0); // initialze all counts to 0
    entireMenu[i].setDesc(defaultDescriptions[i]);
  }

}

void showMenu(vector<MenuItem> &m)
{
  string color = "\x1b[" + to_string(32) + ";"+to_string(91)+"m";
  string reset = "\x1b[0m";


  cout << fixed << setprecision(2); // set doubles to 2 decimal places
  cout << color << "Welcome to 'Lettuce Eat'! Here is our menu:\n\n" << reset << endl;
  color = "\x1b[" + to_string(32) + ";"+to_string(104)+"m";
  cout << color << "                                                                                     \n" << "                                   🥪 LETTUCE EAT 🥪                                 ";
  cout << "\n-----------------------------------------------------------------------------------  " << endl;
  cout << "ADD      NAME       COST    REMOVE COUNT                        DESC                 " << endl; 
  cout << "---     ----      ----  ------ -----                        ----                     " << endl;
  for (int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(13) << m[i].getName() << setw(3) << "$" << m[i].getItemCost();
    if (m[i].getRemoveLetter() == 'a' || m[i].getRemoveLetter() == 'b' || m[i].getRemoveLetter() == 'c' || m[i].getRemoveLetter() == 'd')
    {
      cout << setw(4) << "(" << m[i].getRemoveLetter() << ")";
    }
    else if (m[i].getRemoveLetter() == 'e' || m[i].getRemoveLetter() == 'f' || m[i].getRemoveLetter() == 'g')
    {
      cout << setw(3) << "(" << m[i].getRemoveLetter() << ")";
    }

    cout << setw(6) << m[i].getCount() << "   " << m[i].getDesc() << endl; 
  
  }
  cout << "-----------------------------------------------------------------------------------  " << reset << endl;
}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0'; // the user-selected menu item
  char tipChoice = '\0';
  double subtotal = 0.0;
  vector<string>itemNames;
  vector<double>itemCosts;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i = 0; i < m.size(); i++)
    {
      if (option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].setCount(m[i].getCount() + 1); // increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); // increment the subtotal by the cost of the item 
        showMenu(m); // show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
        itemNames.push_back(m[i].getName());
        itemCosts.push_back(m[i].getItemCost());
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) // subtract if and only if the count is > 0
        {
          m[i].setCount(m[i].getCount() - 1); // decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); // decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else // if item count >= 0 then can't remove
        {

            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X' 
            ) // test for all of my valid inputs
            {
              if (i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  } while(option != 'x' && option != 'X'); 

  string color = "\x1b[" + to_string(32) + ";"+to_string(91)+"m";
  string reset = "\x1b[0m";
  
  cout << color << "\nThank you for placing your order." << reset << endl;

  
  // ask for tips
  double tipAmount = 0.0;
  do
  {
    cout << color << "\nWould you like to tip us 20% or more? (Y/N): " << reset;
    tipChoice = validateChar(tipChoice);
    if (tipChoice == 'Y' || tipChoice == 'y')
    {
      cout << "\nEnter tip percentage in decimal: ";
      tipAmount = validateDouble(tipAmount);
    }
    else if (tipChoice == 'N' || tipChoice == 'n')
    {
      cout << "\nNo tip will be added." << endl;
    }
    else
    {
      cout << "\nInvalid option. Please try again." << endl;
    }
  }
    while (tipChoice != 'Y' && tipChoice != 'y' && tipChoice != 'N' && tipChoice != 'n');

  char payment = '\0';
  double tipping = (subtotal * tipAmount);
  double tax = (subtotal * 0.0825);
  double amount = subtotal + tipping + tax;
  double tender = 0.0;
  
  // tipping/receipt
  cout << "\nYour total amount after tipping and taxes is " << color << amount << endl;
  cout << "\nWould you like to pay with cash or credit card? (A for cash / R for credit): " << reset;
  payment = validateChar(payment);
  if (payment == 'A' || payment == 'a')
  {
    cout << "\nPlease enter your cash amount: ";
    tender = validateDouble(tender);

    if (tender >= amount)
    {
      cout << "\nYour change is $" << color << tender - amount << reset << endl;
    }
    cout << "\n\nHere is your receipt! Thank you for coming, have an amazing day!" << endl;
    printReceipt(itemNames, itemCosts, m, subtotal, amount, tipping, tax, tipAmount, payment, tender);
  }
  else if (payment == 'R' || payment == 'r')
  {
    cout << "Processing Payment..." << endl;
    cout << "Your payment has been processed." << endl;
    cout << color << "\n\nHere is your receipt! Thank you for coming, have an amazing day!" << reset << endl;
    printReceipt(itemNames, itemCosts, m, subtotal, amount, tipping, tax, tipAmount, payment, tender);
  }


  // receipt generation to receipt.txt
  string my_string = "Default";
  string my_string2 = "Default";
  string my_string3 = "Default";
  
  // open the file
  ofstream outputFile("RECEIPT.txt");
  if (outputFile.is_open()) // once opened, put the receipt into the file
  {
    outputFile << fixed << setprecision(2); // set so displays two decimal places
    
    // display money portion
    my_string = "\t\t\t\tYOUR RECEIPT\n------------------------------\n";
    outputFile << my_string;
    for (int k = 0; k < itemNames.size(); k++)
      {
        int length = 22 - itemNames[k].length();
        string space = " ";
        for (int i = 0; i < length; i++) 
        {
            space += " "; // Concatenate a space to the string for each character
        }
        my_string2 = itemNames[k];
        my_string = "\n";
        my_string3 = "$";
        outputFile << my_string2 << space << my_string3 << itemCosts[k] << my_string;
      }
    my_string = "\nTOTAL ITEMS PURCHASED = ";
    outputFile << my_string << itemNames.size();
    my_string = "\n------------------------------\nSubtotal:              $";
    outputFile << my_string << subtotal;

    my_string = "\nTipping (";
    my_string2 = "):        $";
    outputFile << my_string << tipAmount << my_string2 << tipping;

    my_string = "\nTax:                   $";
    outputFile << my_string << tax;

    my_string = "\nTOTAL:                 $";
    outputFile << my_string << amount;

    my_string2 = "\n------------------------------\n";
    outputFile << my_string2;
    
    if (payment == 'A'|| payment == 'a')
    {
      my_string3 = "CASH:                  $";
      my_string2 = "\n------------------------------\nCHANGE:                $";
      my_string = "\n------------------------------";
      outputFile << my_string3 << tender << my_string2 << tender - amount << my_string << endl;
      
    }
    else if (payment == 'R' || payment == 'r')
    {
      my_string3 = "CREDIT CARD            $";
      my_string2 = "\n************1234\n-----------------------------\nChange Due: $00.00\n-----------------------------\n";
      outputFile << my_string3 << amount << my_string2;
    }

    my_string = "  THANK YOU FOR EATING AT\n\t    LETTUCE EAT 🥦";
    outputFile << my_string;
    
  }
  else 
  {
    cerr << "Unable to open file for writing." << endl;
    return;
  }
  
} 

void printReceipt(vector<string> itemNames, vector<double> itemCosts, vector<MenuItem> m, double subtotal, double amount, double tipping, double tax, double tipAmount, char payment, double tender)
{
  string color = "\x1b[" + to_string(32) + ";"+to_string(107)+"m";
  string reset = "\x1b[0m";
  
  cout << color << "\n-----------------------------" << endl;
  cout << "         YOUR RECEIPT" << endl;

  // display items
  cout << "-----------------------------" << endl;
  for (int j = 0; j < itemNames.size(); j++)
    {
    cout << itemNames[j] << setw(23 - itemNames[j].length()) << "$"<< itemCosts[j] << endl;
    }

  // display money portion
  cout << "\nTOTAL ITEMS PURCHASED = " << itemNames.size() << endl;
  cout << "-----------------------------" << endl;
  cout << "Subtotal: " << setw(12) << "$"<< subtotal << endl;
  cout << "Sales Tax: " << setw(11) << "$" << tax << endl;
  cout << "Tipping (" << tipAmount << "): " << setw(6) << "$" << tipping << endl;
  cout << "TOTAL: " << setw(15) << "$" << amount << endl;
  cout << "-----------------------------" << endl;
  if (payment == 'A' || payment == 'a')
  {
    cout << "CASH" << setw(18) << "$" << tender << endl;
    cout << "-----------------------------" << endl;
    cout << "Change Due" << setw(13) << "$" << tender - amount << endl;
  }
  else if (payment == 'R' || payment == 'r')
  {
    cout << "CREDIT CARD " << setw(10) << "$"<< amount << endl;
    cout << "************1234" << endl;
    cout << "-----------------------------" << endl;
    cout << "Change Due" << setw(16) << "$0.00" << endl;
  }
  cout << "-----------------------------" << endl;
  cout << "   THANK YOU FOR EATING AT" << endl << "       LETTUCE EAT 🥦" << reset << endl;

  cout << "\nNow generating the receipt in RECEIPT.txt..." << endl;
}
