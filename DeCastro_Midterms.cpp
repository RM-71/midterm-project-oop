#include <iostream>
#include <iomanip>
using namespace std;

bool categoryValid(string& category){ // Categories Validation
	return category == "clothing"  || category == "electronics" || category == "entertainment";
}
bool isNumeric(const string& str, string typevar) { //Numerics Validation
	bool decimal = false;
    for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.' && typevar == "float") {
            if (decimal)
                return false;  
             decimal = true;	
        } 
		else if (!isdigit(str[i])) 
            return false; 
    }
    return true;
}
float validInput(const string typevar) { //Input Validations Float and Integer
	string input;
        while (!(cin >> input)|| !isNumeric(input, typevar) || stof(input) < 1) {
            cin.clear(); 
            cin.ignore(); 
            cout << "Error: The Input ["<<input<<"] Is Invalid. Please Try Again: ";
        } 
        if (typevar == "float")
        	return stof(input);
        else if (typevar == "integer")
        	return stoi(input);
}
string toLower(string& str){ // Validation for Case Insensitive
	for(char& c: str){
		c = tolower(c);
	}
	return str;
}

class Item{ // Base Class
	private:
		string itemID, itemname;
		int qtyitem;
		float priceitem;
		string categorytype;
		
	protected:
		Item(string ID, string name,string type ,int qty, float price) : itemID(ID), itemname(name),categorytype(type) ,qtyitem(qty), priceitem(price){}
		
	public:
		virtual void displayItem() = 0;
		virtual void addProduct(Item* product[], int &itemCount, string& id, string& name, int qty, float price) = 0;
		
		string getItemid(){
			return itemID;
		}
		string getItemname(){
			return itemname;
		}
		string getCategory(){
			return categorytype;
		}
		int getQuantity(){
			return qtyitem;
		}
		float getPrice(){
			return priceitem;
		}
		float updateQuantity(int updqty){
			qtyitem = updqty; 
			return qtyitem;
		}
		int updatePrice(float updateprice){
			priceitem = updateprice;
			return priceitem;
		}
};

class Clothings : public Item { // Category Class: Clothing Inheritance
public:
    Clothings(string ID, string name, int qty, float price) : Item(ID, name, "clothing", qty, price) {}

    void displayItem() override { // Display Clothing
        cout << left << setw(15) << setfill(' ') << getItemid() 
			 << left << setw(15) << setfill(' ') << getItemname() 
			 << left << setw(15) << setfill(' ') << getQuantity() 
			 << left << setw(15) << setfill(' ') << getPrice() 
			 << left << setw(15) << setfill(' ') << getCategory() << endl;
    }
    void addProduct(Item* product[], int &itemCount, string& id, string& name, int qty, float price) override {
            product[itemCount] = new Clothings(id, name, qty, price);
            itemCount++;
    }
};

class Electronics : public Item { // Category Class: Electronics Inheritance
public:
    Electronics(string ID, string name, int qty, float price) : Item(ID, name, "electronics", qty, price) {}

    void displayItem() override { // Display Electronics
        cout << left << setw(15) << setfill(' ') << getItemid() 
			 << left << setw(15) << setfill(' ') << getItemname() 
			 << left << setw(15) << setfill(' ') << getQuantity() 
			 << left << setw(15) << setfill(' ') << getPrice() 
			 << left << setw(15) << setfill(' ') << getCategory() << endl;
    }

    void addProduct(Item* product[], int &itemCount, string& id, string& name, int qty, float price) override {
            product[itemCount] = new Electronics(id, name, qty, price);
            itemCount++;
    }
};

class Entertainment : public Item { // Category Class: Entertainment Inheritance
public:
    Entertainment(string ID, string name, int qty, float price) : Item(ID, name, "entertainment", qty, price) {}

    void displayItem() override { // Display Entertainment
        cout << left << setw(15) << setfill(' ') << getItemid() 
			 << left << setw(15) << setfill(' ') << getItemname() 
			 << left << setw(15) << setfill(' ') << getQuantity() 
			 << left << setw(15) << setfill(' ') << getPrice() 
			 << left << setw(15) << setfill(' ') << getCategory() << endl;
    }

    void addProduct(Item* product[], int &itemCount, string& id, string& name,  int qty, float price) override { 
            product[itemCount] = new Entertainment(id, name, qty, price);
            itemCount++;
    }
};

class ItemInventory{
	private:
		Item* product[100]; // Main Data Array Holde
		Item* tempArr[100]; // Temporary Data Array Holder
		int itemCount;
		
	public:
		ItemInventory() : itemCount(0) {}
		
		void tempHolder(){ // Passing Product Array to Temporary Array Value
			for (int i = 0; i < itemCount; i++){
				tempArr[i] = product[i];
			}
		}

		bool isDuplicate(string& id){ // Validation For Duplicate ID
			for(int i = 0; i < itemCount; i++){
				    if (product[i]->getItemid() == id){
					cout << "Item Already Exist: Please Try Again" << endl;
					return true;
				}
			}
			return false;
		}
		
		void addProduct(string& id, string& name, string &category, int quantity, float price) {// Item Add::Store Data to class
			if (category == "clothing") {// For Clothing
          		Clothings cloth(id, name, quantity, price);
            	cloth.addProduct(product, itemCount, id, name,  quantity, price);
        	} 
			else if (category == "electronics") { // For Electronics
          		Electronics electro(id, name, quantity, price);
          		electro.addProduct(product, itemCount, id, name, quantity, price);
        	} 
			else if (category == "entertainment") { // For Entertainment
            	Entertainment ent(id, name, quantity, price);
            	ent.addProduct(product, itemCount, id, name,  quantity, price);
        	}
    	}
    	
		void updateProduct(int choice, int qty, float price, string itemID){ // Updating Product: Quantity and Price
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			cout << "	Update Item" << endl;
			cout << "-------------------------" << endl;
			cout << "Input Item ID: ";
			getline (cin >> ws, itemID);
			toLower(itemID); 
			tempHolder();
			for (int i = 0; i < itemCount; i++) {
				string idHolder=tempArr[i]->getItemid();
				bool validitem = false;
				if (toLower(idHolder) == itemID){
					while(!validitem){
						cout << "Displaying Requested Item: " << endl;
							cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
						product[i]->displayItem();
						cout << "Is This Correct Item [1-Yes/2-No]: ";
						choice = validInput("integer");
						if(choice == 1){
							cout << "Item Found: Proceeding..." << endl << endl;
							validitem = true;
						}
						else if (choice == 2){
							cout << "Proceeding to Next item: ";
							validitem = true;
						}
						else
							cout << "Error: Must be 1 or 2 " << endl;
					}
				}
				if (toLower(idHolder) == itemID && choice == 1){
					cout << "[1] - Update Quantity \n" << "[2] - Update Price" << endl << "Enter Choice[1/2]: ";
					choice = validInput("integer");
				
					if (choice == 1){
						cout<<"Enter New Quantity: ";
						qty = validInput("integer");
						if (product[i]->getQuantity() != qty){
							cout << "Quantity of Item " << product[i]->getItemname() << " Updated From " << product[i]->getQuantity() << " To " << qty << endl;
							product[i]->updateQuantity(qty);
						}
						else
							cout << "Quantity Value Is Already " << qty << endl;
					}
					else if (choice == 2){
						cout << "Enter New Price: ";
						price = validInput("float");
						if (product[i]->getQuantity() != price){
							cout << "Price of Item " << product[i]->getItemname() << " Updated From " << product[i]->getPrice() << " To " << price <<endl;
							product[i]->updatePrice(price);
						}
						else
							cout << "Price Value Is Already " << price << endl;
					}
					return;
				}
			}
			cout << "Item Not Found" << endl;
		}
		
		void removeProduct(string itemID, int choice){
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			cout << "	Remove Product" << endl;
			cout << "-------------------------" << endl;
			cout << "Input Item ID: ";
			getline (cin >> ws, itemID);
			toLower(itemID); 
			tempHolder();
			for (int i = 0; i < itemCount; i++) {
				string idHolder=tempArr[i]->getItemid();
				bool validitem = false;
				if (toLower(idHolder) == itemID){
					while(!validitem){
						cout << "Displaying Requested Item: " << endl;
						cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
						product[i]->displayItem();
						cout << "Is This Correct Item [1-Yes/2-No]: ";
						choice = validInput("integer");
						if(choice == 1){
							cout << "Item Found: Proceeding..." << endl << endl;
							validitem = true;
						}
						else if (choice == 2){
							cout << "Proceeding to Next item: ";
							validitem = true;
						}
						else
							cout << "Error: Must be 1 or 2 " << endl;
					}
				}
				if (toLower(idHolder) == itemID && choice == 1){
					cout << "Item " << product[i]->getItemname() << "  Has Been Removed" << endl;
					delete product[i];
					for (int j=i; j<itemCount -1; j++){
						product[j] = product[j+1];
					}
					itemCount--;
					return;
				}
			}
			cout << "Item Not Found" << endl;
		}
		
		void displayProduct(){
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			cout << "		Display All Product" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
			cout << "----------------------------------------------------------------------" << endl;
			for (int i = 0; i < itemCount; i++){
				cout << left << setw(15) << setfill(' ') << product[i]->getItemid() 
					 << left << setw(15) << setfill(' ') << product[i]->getItemname() 
					 << left << setw(15) << setfill(' ') <<  product[i]->getQuantity() 
					 << left << setw(15) << setfill(' ') << product[i]->getPrice() 
					 << left << setw(15) << setfill(' ') << product[i]->getCategory() << endl;
			}
		}
		
		void displayBycategory(string& category, bool founditem) {
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			cout << "	Display By Category" << endl;
			cout << "---------------------------------" << endl;
			cout << "Categories:\n[Clothing || Electronics || Entertainment]" << endl << endl;
			cout << "Enter the category to display item: ";
			getline (cin >> ws, category);
			toLower(category);
			if (!(categoryValid(category))){
				cout << "Error: Category " << category << " Is An Invalid Input" << endl;
				return;
			}
			cout << endl << category << " Items: " << endl;
			cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
			cout << "----------------------------------------------------------------------" << endl;
        		for (int i = 0; i < itemCount; i++) {
            			if (product[i]->getCategory() == category) { 
            				product[i]->displayItem();
            			founditem = true;
        			}
        		}
        		if (!founditem)
        		cout << "No item found in the category: "<< category << endl;
    	}
    	
    	void searchItem(bool founditem, string itemID, int choice){
    		if(itemCount == 0){
			cout << "Inventory Does Not Have Any Available Items" << endl;		
			return;
		}
		cout << "	Search Item" << endl;
		cout << "-------------------------"  << endl;
    		cout << "Enter Item ID: ";
    		getline (cin >> ws, itemID);
    		toLower(itemID);
    		tempHolder();
    			for (int i = 0; i < itemCount; i++) {
				string idHolder=tempArr[i]->getItemid();
				bool validitem = false;
				if (toLower(idHolder) == itemID){
					while(!validitem){
						cout << "Displaying Requested Item: " << endl;
						cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
						product[i]->displayItem();
						cout << "Is This Correct Item [1-Yes/2-No]: ";
						choice = validInput("integer");
						if(choice == 1){
							cout << "Item Found: Proceeding..." << endl << endl;
							validitem = true;
						}
						else if (choice == 2){
							cout << "Proceeding to Next item: ";
							validitem = true;
						}
						else
							cout << "Error: Must be 1 or 2 " << endl;
					}
				}
    			if(toLower(idHolder) == itemID && choice == 1){
    				cout << "ID: " << product[i]->getItemid() 
					<< "\nName: " << product[i]->getItemname() 
					<< "\nQuantity: "<< product[i]->getQuantity()
    					<< "\nPrice: " << product[i]->getPrice() 
					<< "\nCategory: " << product[i]->getCategory() << endl;  
    				founditem = true;
				}
			}
			if (!founditem){
				cout << "Item Is Not Found" << endl;
			}
		}
		
		void sortItem(int choice, bool condition){
			int orderchoice;
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			
			cout << "	Sort Item" << endl;
			cout << "----------------------" << endl; 
			cout << "Sort By: \n[1] - Quantity \n[2] - Price" << endl;
			cout << "Enter Choice [1 or 2]: ";
			choice = validInput("integer");
			cout << endl;
			cout << "Sort Order: \n[1] - Ascending \n[2] - Descending " << endl;
			cout << "Enter Choice [1 or 2]: ";
			orderchoice = validInput("integer"); 
			tempHolder();
			for (int i = 0; i < itemCount - 1; i++) {
        		for (int j = 0; j < itemCount - i - 1; j++) {
					if (choice == 1) {
                		if (orderchoice == 1) 
                    		condition = tempArr[j]->getQuantity() > tempArr[j + 1]->getQuantity();
						else 
                    		condition = tempArr[j]->getQuantity() < tempArr[j + 1]->getQuantity();
            		}
            		else if (choice == 2) {
                		if (orderchoice == 1) 
                    		condition = tempArr[j]->getPrice() > tempArr[j + 1]->getPrice();
               			else 
                		condition = tempArr[j]->getPrice() < tempArr[j + 1]->getPrice();
            		}
            		if (condition) {
                	Item* temp = tempArr[j];
               		tempArr[j] = tempArr[j + 1];
                	tempArr[j + 1] = temp;
            		}
            	}
            }
            cout << "\nSorted Item" << endl;
            cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
            cout << "----------------------------------------------------------------------" << endl;
            for (int i = 0; i < itemCount; i++) {
            	tempArr[i]->displayItem();
            }
		}	
		
		void displayLowitem(bool founditem){
			if(itemCount == 0){
				cout << "Inventory Does Not Have Any Available Items" << endl;		
				return;
			}
			cout << "		Display Low Stock Items" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << left <<setw(15)<<setfill(' ') << "ID"<<setw(15)<<setfill(' ')<<"Name"<< left <<setw(15)<<setfill(' ')<<"Quantity"<< left <<setw(15)<<setfill(' ')<<"Price"<< left <<setw(15)<<setfill(' ')<<"Category"<< endl;
			cout << "----------------------------------------------------------------------" << endl;
			for (int i = 0; i < itemCount; i++){
				if (product[i]->getQuantity() <= 5){
					cout <<left<< setw(15) << setfill(' ') << product[i]->getItemid() 
						 << left << setw(15) << setfill(' ') << product[i]->getItemname() 
						 << left << setw(15) <<setfill(' ')  <<  product[i]->getQuantity() 
						 << left << setw(15) <<setfill(' ') << product[i]->getPrice() 
						 << left << setw(15) << setfill(' ') << product[i]->getCategory() << endl;
					founditem = true;
				}
			}
			if (!founditem)
				cout << "No Low Stock Items Available" << endl;
		}
	
	~ItemInventory() { // Destructor to deallocate memory
    	for (int i = 0; i < itemCount; ++i) {
        	delete product[i];
    	}
	}
};

int main(){
	ItemInventory item;
	string itemID, itemname, category;
	int itemqty, choice;
	float priceitem;            
	bool exit = false;

	while (!(exit)){
		cout << "\t	Menu" << endl;
		cout << "---------------------------------------------" << endl;
		cout << "\t[1] - Add Item \n\t[2] - Update Item \n\t[3] - Remove Item \n\t[4] - Display Item By Category \n\t[5] - Display All Item \n\t[6] - Search Item \n\t[7] - Sort Item \n\t[8] - Display Low Stock Item \n\t[9] - Exit" << endl;
		cout << "	Enter Choice[1-9]: "; 
		choice = validInput("integer");
		cin.ignore();
		
		if(choice < 9)
		system ("cls");
		switch (choice){
			case 1:
				do {
					cout << "-------------------------" << endl;
					cout << "	Add Item	" << endl;
					cout << "-------------------------" << endl;
					cout <<"Category:" << endl << "Clothing \nElectronics \nEntertainment\n" << endl;
					cout << "Enter The Item Category: ";
					getline (cin >> ws, category);
					toLower(category);
					if (categoryValid(category)){
						do{	
							cout << "Input Item ID: ";
							getline (cin >> ws, itemID);
						}while (item.isDuplicate(itemID));
						cout << "Input Item Name: "; 
						getline (cin >> ws, itemname);
						cout << "Input Quantity of Item: ";
            					itemqty = validInput("integer");
            					cout << "Input Price For Item: ";
            					priceitem = validInput("float");
            					item.addProduct(itemID, itemname, category, itemqty, priceitem);
					}
					else
						cout << "Category " << category << " is an invalid input please try again\n" << endl;
				}while(!(categoryValid(category)));
				system ("pause");	system ("cls");
			break;
			case 2:
				item.updateProduct(choice, itemqty, priceitem, itemID);
				system ("pause");	system ("cls");
			break;
			case 3:
				item.removeProduct(itemID, choice);
				system ("pause");	system ("cls");
			break;
			case 4:
                		item.displayBycategory(category, false);
                		system ("pause");	system ("cls");
			break;
			case 5:
				item.displayProduct();
				system ("pause");	system ("cls");
			break;
			case 6:
				item.searchItem(false, itemID, choice);
				system ("pause");	system ("cls");
			break;
			case 7:
				item.sortItem(choice, false);
				system ("pause");	system ("cls");
			break;
			case 8:
				item.displayLowitem(false);
				system ("pause");	system ("cls");
			break;
			case 9:
				system ("cls"); cout << "Exit...";
				exit = true;
			break;
			default:
				cout << "	Error: Invalid Input Please Try Again" << endl;
				system ("pause");	system ("cls");
		}
	}
	return 0;
}
