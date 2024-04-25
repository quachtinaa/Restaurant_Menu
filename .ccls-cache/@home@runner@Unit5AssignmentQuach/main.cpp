// Tina Quach
// COSC-1437-58002 - Dr.T
// Date: 04/25/2024
// menu-driven restaurant program

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>

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
void showMenu (vector<MenuItem> &entireMenu);
void acceptOrder (vector<MenuItem> &entireMenu);

int main()

{
  // object of MenuItem class
  vector<MenuItem> wholeMenu; 
  
  populateMenu(wholeMenu); // put some default values in the menu
  showMenu(wholeMenu); // print the current data of the menu on screen 
  acceptOrder(wholeMenu); 
  
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

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Ramen", "Burger", "Coke-Cola", "Nachos", "Lemonade"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  // add each item to the default list efficiently
  for(int i = 0; i < numItems; i++)
  {
    entireMenu[i].setName(defaultMenuNames[i]);
    entireMenu[i].setAddLetter(defaultAddLetters[i]);
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); // set a random starter cost for each item
    entireMenu[i].setCount(0); // initialze all counts to 0
    entireMenu[i].setDesc("delicious"); // set all default desc to "delicous"
  }

}

void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2); // set doubles to 2 decimal places
  cout << "Dr. T's Effcient Menu" << endl; 
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC"<<endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << m[i].getAddLetter() << ")" << setw(10) << m[i].getName() << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << m[i].getRemoveLetter() << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() << endl; 
  
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0; 

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
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 
  // handle the tip process here
  // handle reciept generation here
}