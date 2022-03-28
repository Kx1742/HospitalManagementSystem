#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;
//store in array of structure
const int maxrow = 30;  //set the variable that can hold 30 values only
struct CONSULT_DETAIL //consultation detail
{
    string doctorNameLst;   //Doctor Name
    string diagnosisLst;    //Diagonisis
    string patientStatusLst;//Patient Status
    string dateLst;         //Consultation Date
};
typedef struct {
    string nameLst;         //Patient name 
    string IDLst;           //Patient ID
    string ageLst;          //Patient age
    string addressLst;      //Patient address
    CONSULT_DETAIL c;        //consultation detail

} PATIENT;
typedef struct {
    string DocnameLst;     //Doctor Name
    string DocIDLst;       //Doctor ID
} DOCTOR;

//function prototypes
void programInfo();
void Menu();
void Open_File(PATIENT pts[], DOCTOR d[]);
void List_Patient(PATIENT pts[]);
void Display_Patient_Detail(PATIENT pts[]);
void Patient_Detail(string search, PATIENT pts[], char action);
void List_Doctor(DOCTOR d[]);
void Add_Doctor(DOCTOR d[]);
int Validate_Doctor_ID(string input,DOCTOR d[]);
void Delete_Doctor(DOCTOR d[]);
void Add_Patient_Information(PATIENT pts[], DOCTOR d[]);
int Validate_Patient_ID(string userInput, PATIENT pts[]);
int Validate_date(string date);
void Delete_Patient(PATIENT pts[], int line);
void Delete_Patient_Information(PATIENT pts[]);
void Advanced_Edit_Patient_Information(PATIENT pts[], DOCTOR d[]);
void Edit_Patient(string search, PATIENT pts[], DOCTOR d[], char action);
void Search_Patient(PATIENT pts[]);
void Search_Patient_by_ID(PATIENT pts[], string avdSearchID);
void Search_Patient_by_Name(PATIENT pts[], string avdSearchName);
void Save_Patient(PATIENT pts[]);
void Save_Doctor(DOCTOR d[]);

/*A main function to test all of the functions .
*Input data (choice) to call out the specific fuction*/
int main()
{
    PATIENT pts[30];//set the max number of the element of array to 30
    DOCTOR  d[10]; //set the max number of the element of array to 10
    system("color 0B");
    string input;
    char choice;
    bool loop = true;
    Open_File(pts, d);  //open text file
    programInfo();  //display program info
    system("PAUSE");
    //Press any key to continue . . .
    //pause program terminated.Resuming...
    //This program waits to be terminated, and halts the exceution of the parent C++ program. Only after the pause program is terminated, will the original program continue.
    do {
        system("CLS");//cl ear s creen
        Menu(); //display menu
        cout << "                    Select option from 1 - 9 : ";
        getline(cin, input);    //allow user to select their option
        choice = (input.size() > 1) ? '\0' : input[0];   //change string input into char, if the input size is greater than 1, set the input to null, else get the first character as user input 
        switch (choice)
        {
        case '1': {
            Display_Patient_Detail(pts); // open and display patient record
            cout << " "; system("PAUSE");
            break;
        }
        case '2': {
            List_Doctor(d); // open and displpay doctor record
            cout << " "; system("PAUSE");
            break;
        }
        case '3': {
            Add_Doctor(d);  // add doctor name
            cout << " "; system("PAUSE");
            break;
        }
        case '4': {
            Delete_Doctor(d); //delete doctor name
            cout << " "; system("PAUSE");
            break;
        }
        case '5': {
            Add_Patient_Information(pts, d); // Add patient(s) information into the system. new patient(s) or existing patient(s).
            cout << " "; system("PAUSE");
            break;
        }
        case '6': {
            Delete_Patient_Information(pts);// delete all of information relating to the selected patient(s) from the system.
            cout << " "; system("PAUSE");
            break;
        }
        case '7': {
            Advanced_Edit_Patient_Information(pts, d); // update or edit patient’s information 
            cout << " "; system("PAUSE");
            break;
        }
        case '8': {
            Search_Patient(pts); //search patient information according to name or ID
            cout << " "; system("PAUSE");
            break;
        }
        case '9': {
            Save_Patient(pts); //write the updated data in the list to the patient file.
            Save_Doctor(d); //write the updated data in the list to the doctor file.
            cout << "Save successfully!";
            loop = false;
            break;
        }

        default:
        {
            cout << "                    Invalid choice entered....." << endl;
            cout << "                    ";
            system("PAUSE");
        }
        }
    } while (loop == true);
    return 0;

}


/*Task I -Read from file (building the list)
*Open file and read in the data into nested array of structure*/
void Open_File(PATIENT pts[], DOCTOR d[])
{
    //Task I - Read from file(building the list)-Patient file
    string line; //Create a text sstring , which is used to output the text file
    ifstream myfile("PatientList.txt"); //Read from the text file
    if (!myfile)//set to false if open failed
    {
        cout << " Error in opening patient file .Please insert the correct text file" << endl; //if error in opening file
        exit(EXIT_FAILURE); //terminate process
    }
    else {
        //read input from file
        int i = 0;//initialisation
        while (getline(myfile, line)) //Use while loop together with getline function to read the file line by line 
        {
            stringstream ss(line);// creates a string stream: a stream that takes line as input
            getline(ss, pts[i].nameLst, '%'); //get each elements of the line and stop when meet '/'
            getline(ss, pts[i].IDLst, '%');
            getline(ss, pts[i].ageLst, '%');
            getline(ss, pts[i].addressLst, '%');
            getline(ss, pts[i].c.doctorNameLst, '%');
            getline(ss, pts[i].c.diagnosisLst, '%');
            getline(ss, pts[i].c.patientStatusLst, '%');
            getline(ss, pts[i].c.dateLst);
            i++;
            //repeat until reach end of the file
        }
        myfile.close();
    }
    //Task I - Read from file(building the list)-Doctor file
    string row;
    ifstream Docfile("DoctorList.txt"); //Read from the text file
    if (!Docfile)//set to false if open failed
    {
        cout << " Error in opening doctor file .Please insert the correct text file" << endl; //if error in opening file
        exit(EXIT_FAILURE); //terminate process
    }
    else {
        //read input from file
        int y = 0;//initialisation
        while (getline(Docfile, row)) //Use while loop together with getline function to read the file line by line 
        {
            stringstream ss(row);// creates a string stream: a stream that takes line as input
            getline(ss, d[y].DocIDLst, '/');//get each elements of the line and stop when meet '/'
            getline(ss, d[y].DocnameLst);

            y++;
            //repeat until reach end of the file
        }
        Docfile.close();
    }
}


/*Display group information, brief explain about the program and the program limitataion*/
void programInfo()
{
    cout << "\n---------------------------------------------------------------------------------------------" << endl;
    cout << "                                [GROUP & PROGRAM INFROMATION ]" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << " Group name : A++\n" << endl;
    cout << " Group member : \n" << endl;
    cout << " [1] CHIN QIAN HUI             [4] WONG KE XIN" << endl;
    cout << " [2] CHIN ROU XING             [5] WONG YONG JIE" << endl;
    cout << " [3] GRACE LIM WEI QI\n" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << " The project purpose is to develop a simple application in C++ to aid in the management of\n" << endl;
    cout << " patients within a hospital. There are some function to VIEW, ADD, UPDATE, EDIT, DELETE,\n" << endl;
    cout << " SEARCH and SAVE patient information.\n" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << " Program Limitation:\n" << endl;
    cout << " 1) Only maximum 30 patient data can be stored.\n" << endl;
    cout << " 2) Only maximum 10 doctor data can be stored.\n" << endl;
    cout << " 3) The changes will be save into file once and only you enter option 9 to exit program.\n" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
}


/*Display the choice of all of the function */
void Menu()
{
    cout << "\n---------------------------------------------------------------------------------------------" << endl;
    cout << "                                 PATIENT MANAGEMENT SYSTEM" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "                     Press 1     View patient list  \n" << endl;
    cout << "                     Press 2     View doctor list  \n" << endl;
    cout << "                     Press 3     Add doctor record  \n" << endl;
    cout << "                     Press 4     Delete doctor record  \n" << endl;
    cout << "                     Press 5     Add patient information  \n" << endl;
    cout << "                     Press 6     Delete patient information  \n" << endl;
    cout << "                     Press 7     Advanced Update/Edit  \n" << endl;
    cout << "                     Press 8     Advanced seacrh  \n" << endl;
    cout << "                     Press 9     Save before exit  \n" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
}


/* Task V b)-Input patient name or patient ID to look into patient's detail
* Data validation for all of the data key in
* User is required to repeat key in the value input until the correct value is entered .*/
void Display_Patient_Detail(PATIENT pts[])
{
    string searchName;
    string searchID;
    string choice;
    char action;
    List_Patient(pts);
    do {
        cout << " Look into patient detail (1-patient name   2-patient ID  3-Exit the function) : ";//user choose whether search the patient data by patient name or patient id
        getline(cin, choice);
        int y = choice.length();//test the number of character in the string
        if (y == 1) //if only one character is entered 
            action = choice[0]; //take tha value and read it in char data type
        else  //if more one character is entered 
        {
            cout << " You should enter one character only " << endl; //ask user to key in the value again
            action = '0';
        }

    } while (action != '1' && action != '2' && action != '3');//repeat the function if more one character is entered or space or nothing is input

    if (action == '1') //choose to look into patient list by entering patient name
    {
        int counter = 0; //check whether the patient name exists
        do {
            cout << " Enter Patient name : ";
            getline(cin, searchName); //Read in patient name
            cout << searchName << endl;
            if (searchName.length() != 0)//if enter anything
            {
                for (int x = 0; x < maxrow; x++)
                {
                    if (pts[x].nameLst == searchName)
                    {
                        cout << " Patient name found !"; //if the name is found in the patient name list ,proceed to the next step,go into function and display patient data
                        Patient_Detail(searchName, pts, action);
                        counter++;//counter +1 if patient name is found 
                        break;
                    }
                }
            }
            if (counter == 0) // no patient name match the patient name in the array
                cout << " Patient name is not in the record. Please enter patient name again.\n" << endl;
        } while (counter == 0); //Enter again if the patient name is not found
    }
    else if (action == '2')//choose enter patient ID
    {
        int counter = 0;//check whether the patient ID exists
        do {
            cout << " Enter patient ID :";
            getline(cin, searchID);//read in patient ID
            if (searchID.length() != 0)//if enter anything
            {
                for (int x = 0; x < maxrow; x++)
                {
                    if (pts[x].IDLst == searchID) //if the ID is found in the ID list ,proceed to the next step,go into function and display patient data
                    {
                        cout << " Patient ID found.";
                        Patient_Detail(searchID, pts, action);
                        counter++;//counter +1 if patient ID is found
                        break;
                    }
                }
            }
            if (counter == 0)// no patient ID match the patient ID in the array
                cout << " Patient ID is not in the record. Please enter patient ID again.\n" << endl;

        } while (counter == 0);//Enter again if the patient ID is not found
    }
    else if (action == '3')
        cout << " Exit function" << endl;
    cout << " You had exit the patient list." << endl; // exit patient list
}


/*Task V - List patient information-general information
*Display the patient's name , ID ,status and date only
*Can look into patient's detail by inputing patient name or ID in the next function */
void List_Patient(PATIENT pts[])
{
    int counter = 0;//initialisation
    system("CLS"); //clear screen
    cout << "\n------------------------------------------------------------------------------------------------------------------------\n" << endl;
    cout << "                                 Patient Management System" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
    cout << "                                        Patient List  " << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
    cout << " No.  ||        Patient Name     ||     Patient ID     ||      Consultation  Date  " << endl;
    cout << "========================================================================================================================" << endl;

    for (int x = 0; x < maxrow; x++)
    {
        if (pts[x].nameLst != "\0")//if the element in the nameLst array is not empty
        {
            counter++;
            cout << fixed << endl; //Display the patient general detail
            cout << " " << setw(3) << counter << "      " << setw(20) << pts[x].nameLst << "       " << setw(15) << pts[x].IDLst << "       " << setw(26) << pts[x].c.dateLst << endl;
        }
    }
    if (counter == 0) //means the array of nameLst is empty.
    {
        cout << "----------------------------------!!! No Record Found !!!------------------------------------------------------------" << endl;
    }
    cout << "\n=======================================================================================================================" << endl;
}


/*Task V - List patient information-detail information
* Look into patient's detail by patient's ID and patient's name.
*Display all of the patient's information.*/
void Patient_Detail(string search, PATIENT pts[], char action)
{
    system("CLS");//clear screen
    if (action == '1') {
        for (int x = 0; x < maxrow; x++)
        {
            if (pts[x].nameLst == search) //Display the patient information if the ID of the patient match the ID in the List
            {
                cout << "\n---------------------------------------------------------------------------------------------" << endl;
                cout << "                                 Patient Management System" << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << "                                       Patient Document  " << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << " Name : " << pts[x].nameLst << "\n";
                cout << " ID : " << pts[x].IDLst << "\n";
                cout << " Age : " << pts[x].ageLst << "\n";
                cout << " Address : " << pts[x].addressLst << "\n";
                cout << "\n---------------------------------------------------------------------------------------------\n" << endl;
                cout << " Counsultation Date : " << pts[x].c.dateLst << endl;
                cout << " Status : " << pts[x].c.patientStatusLst << endl;
                cout << " Attending Doctor's Name : " << pts[x].c.doctorNameLst << "\n";
                cout << " Diagnosis : " << pts[x].c.diagnosisLst << "\n";
                cout << "\n=============================================================================================" << endl;
                break;
            }
        }
    }
    else if (action == '2') {
        for (int x = 0; x < maxrow; x++)
        {

            if (pts[x].IDLst == search) //Display the patient information if the ID of the patient match the ID in the List
            {
                cout << "\n---------------------------------------------------------------------------------------------" << endl;
                cout << "                                 Patient Management System" << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << "                                       Patient Document  " << endl;
                cout << "---------------------------------------------------------------------------------------------" << endl;
                cout << " Name : " << pts[x].nameLst << "\n";
                cout << " ID : " << pts[x].IDLst << "\n";
                cout << " Age : " << pts[x].ageLst << "\n";
                cout << " Address : " << pts[x].addressLst << "\n";
                cout << "\n---------------------------------------------------------------------------------------------\n" << endl;
                cout << " Counsultation Date : " << pts[x].c.dateLst << endl;
                cout << " Status : " << pts[x].c.patientStatusLst << endl;
                cout << " Attending Doctor's Name : " << pts[x].c.doctorNameLst << "\n";
                cout << " Diagnosis : " << pts[x].c.diagnosisLst << "\n";
                cout << "\n=============================================================================================" << endl;
                break;
            }
        }
    }
}


/*List doctors' information
 *Display the doctor's name and ID only*/
void List_Doctor(DOCTOR d[])
{
    system("CLS");
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "                                 Patient Management System" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "                                        Doctor List  " << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "  No.  ||        Doctor ID      ||              Doctor Name              ||" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    int counter = 0;//initialisation to find whether the doctor exists in the system
    for (int x = 0; x < 10; x++)
    {
        if (d[x].DocIDLst != "\0")
        {
            counter++;//counter +1 if the doctor exists in the system
            cout << "  " << setw(2) << right << x + 1 << " . " << setw(20) << right << d[x].DocIDLst << "           " << fixed << left << setw(40) << d[x].DocnameLst << "\n" << endl;
        }
    }
    if (counter == 0)// no doctor information is exist in the doctor file
    {
        cout << "----------------------------------!!! No Record Found !!!------------------------------------" << endl;
    }
    cout << "---------------------------------------------------------------------------------------------" << endl;
}


//Add Doctor Information into the system.
void Add_Doctor(DOCTOR d[])
{
    string name;  //reserve 30 characters of memory
    string DocID;
    system("CLS"); //clear screen
    cout << endl;
    cout << "-----------------------------------[ Add Doctor Information ]--------------------------------\n" << endl;

    int error;
    do
    {
        cout << " Doctor ID (e.i. A123456)   : ";
        getline(cin, DocID);  //get doctor ID from user
        error = Validate_Doctor_ID(DocID,d);  //call validate ID function
    } while (error != 0);   //break do while loop if the validation return 1

    int y, name_digit, n_sum;
    do {
        y = 0;
        name_digit = 0;
        n_sum = 0;
        cout << " Doctor Name : "; getline(cin, name);  //get doctor name from user
        y = name.length();  //assign y to length of name
        for (int i = 0; i < y; i++)
        {
            if (isdigit(name[i])) //if enter number
                name_digit++;
            if (isspace(name[i]))//if enter space
                n_sum++;
            if (isalpha(name[i]))//if enter letter
                n_sum++;
        }
        n_sum = n_sum + name_digit;
    } while (y > 30 || name_digit > 0 || n_sum != y || isspace(name[0]) != 0 || y == 0);
    // terminate if y <= 30 AND number of digit <= 0 AND n_sum == y AND no space in front of name entered AND the length of name not equal zero

    for (int x = 0; x < 10; x++)
    {
        if (d[x].DocIDLst == "\0")
        {
            d[x].DocnameLst = name;// store the name that entered
            d[x].DocIDLst = DocID;// store the ID that entered
            break;
        }
    }
    cout << " Doctor added sucessfully!";
}


/*Validate the doctor ID
Pre: input is defined and it the the new input docter ID of the user.
It must be a string with 1 alphabet  and 6 int only*/
int Validate_Doctor_ID(string input,DOCTOR d[])
{
    string alpha(input, 0, 1); // assign alpha to first letter of the input with only 1 alphabet
    int numOfAlpha = 1, //numOfAlpha for doctor ID is 1
        totalSize = 7, //totalSize of the ID is 7
        error = 0;
    if (input.size() != totalSize) // if enter more than 7 (letter & number)
        error ++;
    else 
    {
        if (alpha != "A") // if enter without start with "A"
            error++;

        for (int i = 0; i <= (numOfAlpha - 1); i++)
        {
            if (isalpha(input[i]) == 0) // if enter not letter
            {
                error++;
            }
        }
        for (int n = numOfAlpha; n <= (totalSize - 1); n++)
        {
            if (isdigit(input[n]) == 0) // if enter not number
            {
                error++;
            }
        }
        for (int x = 0; x < 10; x++)
        {
            if (d[x].DocIDLst == input)// if doctor name is exist
            {
                cout << " This doctor ID had been used....." << endl;
                error++;
            }
        }
    }
    return error;
}


/*Input doctor name for delete
* Data validation for all of the data key in*/
void Delete_Doctor(DOCTOR d[])
{
    string docName, input;
    char opt;
    int counter = 0;
    do {
        system("CLS"); // clear screen
        List_Doctor(d); //display doctor list
        cout << " Enter doctor name (enter 0 to back to the menu) : ";
        getline(cin, docName); // get the whole line for doctor name
        for (int x = 0; x < maxrow; x++)
        {
            if (d[x].DocnameLst == docName && docName.size() > 0) // if doctor name in list and not empty value entered
            {
                cout << " Doctor name found!" << endl;
                do {
                    cout << " "; system("PAUSE");
                    system("CLS"); // clear screen
                    cout << "\n---------------------------------------------------------------------------------------------" << endl;
                    cout << "                                 Patient Management System" << endl;
                    cout << "---------------------------------------------------------------------------------------------" << endl;
                    cout << "                                        Doctor Name  " << endl;
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                    cout << "  No.  ||        Doctor ID      ||              Doctor Name              ||" << endl;
                    cout << "---------------------------------------------------------------------------------------------" << endl;
                    cout << "  1 . " << setw(20) << right << d[x].DocIDLst << "           " << fixed << left << setw(40) << d[x].DocnameLst << endl; //desplay all doctor information
                    cout << "----------------------------------------------------------------------------------------------" << endl;
                    cout << " Do you want to delete this doctor record? Yes(y)/ No(n): ";
                    getline(cin, input); // get choice from user
                    opt = input.size() > 1 ? '\0' : input[0];   // if input size greater than 1, assign it to null, else take the fist letter of input
                    if (tolower(opt) == 'y')// if user enter y
                    {
                        int i = 10;
                        for (x; x < (i - 1); x++)
                        {
                            d[x].DocIDLst = d[x + 1].DocIDLst; // delete doctor ID
                            d[x].DocnameLst = d[x + 1].DocnameLst; //delete doctor name
                        }
                        if (x == i - 1)   // if the line want to delete is last line
                        {
                            d[x].DocIDLst = ""; // assign the element to empty
                            d[x].DocnameLst = "";
                        }
                        List_Doctor(d); //display doctor list
                        cout << "Delete successfully !!!" << endl;
                        counter++;
                    }
                    else if (tolower(opt) == 'n')// if option is no, quit delete
                    {
                        cout << " Quit delete..." << endl;
                        counter++;
                    }
                    else
                    {
                        cout << " Error option enter..." << endl; //prompt error message
                    }
                } while (counter == 0);
            }
        }
        if (docName == "0")
        {
            cout << " Back to menu..." << endl; // back to main menu
            counter++;
        }
        if (counter == 0) //if the doctor is not in notepad
        {
            cout << " Doctor name is not in the record. Please enter the doctor name again. " << endl;
            cout << " "; system("PAUSE");
        }
    } while (counter == 0);
}


/*Task II - Add patient Information
* Add patient(s) information into the system.
* There are TWO options when it comes to adding patient information: new patient(s) or existing patient(s).*/
void Add_Patient_Information(PATIENT pts[], DOCTOR d[])
{
    string name;
    char ID[20];
    string age;
    string address;
    string doctorName;
    string diagonisis;
    string patientStatus;
    string date;
    string choice;
    char action;
    system("CLS"); //clear screen
    cout << "=============================================================================================\n" << endl;
    cout << "                                     ADD PATIENT INFROMATION \n" << endl;
    cout << "=============================================================================================\n" << endl;
    cout << " 1--Add New Patient Information \n" << endl;
    cout << " 2--Add Exiting Patient Information \n" << endl;
    cout << "=============================================================================================\n" << endl;
    do {
        cout << " Enter your choice : ";
        getline(cin, choice);//get the choice from user
        int y = choice.length();//test the number of character in the string
        if (y == 1) //if only one character is entered 
            action = choice[0]; //take tha value and read it in char data type
        else  //if more one character is entered 
        {
            action = '0';
        }

    } while (action != '1' && action != '2');
    string keyInID;
    if (action == '1')// if the user choice 1
    {
        system("CLS"); //clear screen
        cout << "\n--------------------------------[ Add New Patient Information ]-------------------------------\n" << endl;

        int x;
        do
        {
            cout << " Please input ID (e.i. UMMY123456)   : ";
            cin.getline(ID, 20); // get ID from user
            x = Validate_Patient_ID(ID, pts); //call validate ID function

        } while (x != 1);

        int y = 0, count = 0;
        string name;
        do {
            count = 0;
            cout << " Patient Name      : ";
            getline(cin, name);//get name from user
            y = name.length(); //get length of name
            for (int i = 0; i < y; i++)//check all the character in the string
            {
                if (isalpha(name[i]))//if the name contain any thing that is not alphabet
                    count++;
                else if (isspace(name[i]))
                    count++;
            }
        } while (count != y || y == 0 || y > 30 || isspace(name[0]));//number of character of length entered should less or equal to 30 and do not contain number or is space or empty.

        bool age_condition = true;
        do {
            age_condition = true;
            cout << " Age               : "; getline(cin, age);
            int z = age.length();
            for (int i = 0; i < z; i++)//check all the character in the string
            {
                if (!isdigit(age[i])) {//if the age contains not digit character)
                    age_condition = false;
                }
            }
            if (z != 0 && !isspace(age[0]) && age_condition == true)
            {
                int age_int;
                age_int = stoi(age); //change the string to int type
                if (age_int < 0 || age_int>150) //age entered should be in 0-149
                    age_condition = false;
            }
            else
                age_condition = false;

        } while (age_condition == false);//if the condition is false or the input is empty or white space}
        do {
            cout << " Address           : ";
            getline(cin, address);// get address from user
            y = address.length();   // address length

        } while (y > 60 || y == 0);//number of character of length entered should less or qual to 30 and do not contain number.

        bool doc_assist = true;
        int z;
        do {

            doc_assist = true;
            cout << " Doctor's Name     : ";
            getline(cin, doctorName); //get doctorname from user
            z = doctorName.length();    // doctor name length
            for (int x = 0; x < 10; x++)
            {
                if (d[x].DocnameLst == doctorName)// if doctor name is exist
                {
                    doc_assist = false;
                }
            }
        } while (doc_assist == true || z == 0);// termainate when doc_assist is false and length not equal zero

        do {
            cout << " Diagnosis         : ";
            getline(cin, diagonisis);
            y = diagonisis.length();//get diagonisis from user
        } while (y > 15 || y == 0);

        do {
            cout << " Patient Status    : ";
            getline(cin, patientStatus);//get patient Status from user

        } while (patientStatus != "Outpatient" && patientStatus != "outpatient" && patientStatus != "Inpatient" && patientStatus != "inpatient");
        //terminate when patient status equal to Outpatient/outpatient and Inpatient/inpatient

        int error = 0;
        string date;
        bool flag = false;
        do {
            cout << " Consultation Date (dd/mm/yyyy): "; getline(cin, date);
            y = date.length();//get Consultation date from user
            error = Validate_date(date);
            if (error == 0) {
                flag = true;
            }
        } while (y != 10 || flag == false); // terminate if date length no equal to 10 and flag is true

        for (int x = 0; x < maxrow; x++)
        {
            if (pts[x].IDLst == "\0")
            {//send all the data that user enter back to main
                pts[x].nameLst = name;
                pts[x].IDLst = ID;
                pts[x].ageLst = age;
                pts[x].addressLst = address;
                pts[x].c.doctorNameLst = doctorName;
                pts[x].c.diagnosisLst = diagonisis;
                pts[x].c.patientStatusLst = patientStatus;
                pts[x].c.dateLst = date;
                break;
            }
        }
    }
    string searchID;
    int counter = 0;
    if (action == '2')
    {
        system("CLS");
        List_Patient(pts);  //display patient list
        cout << "\n-------------------------------[ Add Exiting Patient Information ]----------------------------\n" << endl;
        do {
            cout << " Enter patient ID that you want to add :";
            getline(cin, searchID);//read in patient ID//read in patient ID
            if (searchID.length() != 0) //if enter anything
            {
                for (int x = 0; x < maxrow; x++)
                {
                    if (pts[x].IDLst == searchID) //if the ID is found in the ID list ,proceed to the next step,go into function and display patient data
                    {
                        cout << " Patient ID found.";

                        Patient_Detail(searchID, pts, action);
                        int counters = 0; //initialisation to find whether the patient exists in the system

                        for (int x = 0; x < maxrow; x++)
                        {
                            if (pts[x].IDLst == searchID)   // if the search patient ID match in ID list
                            {
                                int error = 0;
                                int y;
                                string date;
                                bool flag = false;
                                do {
                                    cout << " Consultation Date (dd/mm/yyyy): "; getline(cin, date);
                                    y = date.length();//get Consultation date from user
                                    error = Validate_date(date);
                                    if (error == 0) {
                                        flag = true;
                                    }
                                } while (y != 10 || flag == false); // terminate if date length no equal to 10 and flag is true


                                do {
                                    cout << " Patient Status    : ";
                                    getline(cin, patientStatus);//get new patient states from user
                                } while (patientStatus != "Outpatient" && patientStatus != "outpatient" && patientStatus != "Inpatient" && patientStatus != "inpatient");
                                //terminate when patient status equal to Outpatient/outpatient and Inpatient/inpatient

                                bool doc_assist = true;
                                int z;
                                do {
                                    doc_assist = true;
                                    cout << " Doctor's Name     : ";
                                    getline(cin, doctorName);//get new doctor name from user
                                    z = doctorName.length();    // doctor name length
                                    for (int x = 0; x < 10; x++)
                                    {
                                        if (d[x].DocnameLst == doctorName)// // if doctor name is exist
                                        {
                                            doc_assist = false;
                                        }
                                    }
                                } while (doc_assist == true || z == 0); // termainate when doc_assist is false and length not equal zero

                                y=0;
                                do {
                                    cout << " New Diagnosis     : ";
                                    getline(cin, diagonisis);//get new diagonis from user
                                    y = diagonisis.length();    // diagonosis length
                                } while (y > 15 || y == 0);

                                //add record to the exiting patient 
                                pts[x].c.doctorNameLst = pts[x].c.doctorNameLst + "," + doctorName;
                                pts[x].c.diagnosisLst = pts[x].c.diagnosisLst + "," + diagonisis;
                                pts[x].c.patientStatusLst = pts[x].c.patientStatusLst + "," + patientStatus;
                                pts[x].c.dateLst = pts[x].c.dateLst + "," + date;

                                // to inform user that they have successfully updated
                                cout << "\n!!!!!!!!!! Successfully Updated !!!!!!!!!!" << endl;

                                counters++; //counter +1 if the patient exists in the system
                                break;
                            }
                        }
                        if (counters == 0)// the patient is not exist in the system
                        {
                            // to inform user that the id is not exist
                            cout << "!!!!!!!!!! No Record Found !!!!!!!!!!" << endl;
                        }
                        counter++;
                        break;
                    }
                }
            }
            if (counter == 0)
                cout << " Patient ID is not in the record. Please enter patient ID again.\n" << endl;
        } while (counter == 0);
    }
}


/*Validate the Patient ID
Pre: input is defined and it the the new input patient ID of the user.
It must be a string with 4 alphabet  and 6 int only*/
int Validate_Patient_ID(string userInput, PATIENT pts[])
{
    string alpha(userInput, 0, 4);
    int numOfAlpha = 4,
        totalSize = 10;
    if (userInput.size() != totalSize)//if totol character user enter is not 10
        return false;

    if (alpha != "UMMY") //if the ID is not start with UMMY
        return false;

    for (int i = 0; i <= (numOfAlpha - 1); i++)
    {
        if (isalpha(userInput[i]) == 0) //if the ID do not have letter
        {
            return false;
            break;
        }
    }
    for (int n = numOfAlpha; n <= (totalSize - 1); n++)
    {
        if (isdigit(userInput[n]) == 0)//if the ID do not have number
        {
            return false;
            break;
        }
    }
    int z = userInput.length();    // doctor name length
    for (int x = 0; x < 10; x++)
    {
        if (pts[x].IDLst == userInput)// if patient name is exist
        {
            cout << " This patient ID had been used....." << endl;
            return false;
            break;
        }
    }
    return 1;
}


/*Consultation date validation
* Pre: input is defined and undergo validation below.
* It must be a valid date which the day input is in range of every month. For example, 31 days for January.
* It must be valid month which within 1 to 12 months.
* It must be valid year in rnage of 2021 to 2023*/
int Validate_date(string date)
{
    int DAYS_IN_MONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int error = 0;
    int dd, mm, yy;
    int digit = 0;
    int y = date.length();//get Consultation date from user
    if (!isspace(date[0]) && y != 0 && y == 10 && date.substr(2, 1) == "/" && date.substr(5, 1) == "/") {
        for (int i = 0; i < 10; i++)
        {
            if (isdigit(date[i]))//if the date contain number, digit +1
                digit++;
        }
        if (digit == (y - 2)) //proceed when date length is 10 and position of 2 and 5 is /
        {
            dd = stoi(date.substr(0, 2)); //change day in position 0, 2 number from string to integer
            mm = stoi(date.substr(3, 2)); //change day in position 3, 2 number from string to integer
            yy = stoi(date.substr(6, 4)); //change day in position 6, 4 number from string to integer
            if (mm < 1 || mm > 12 || yy < 2021 || yy> 2023) //if the month enter is between 1 to 12
                error++;
            else
            {
                if ((mm == 2) && ((yy % 400 == 0) || (yy % 100 != 0) || (yy % 4 == 0))) //vaiidate if is leap year
                    DAYS_IN_MONTH[1] = 29;  //days in February will be 29 days
                if (dd < 1 || dd > DAYS_IN_MONTH[mm - 1])//if the day enter is not between 1 to  the last day of the month
                    error++;
            }
        }
    }
    if (isspace(date[0]) || y == 0 || y != 10 || date.substr(2, 1) != "/" || date.substr(5, 1) != "/" || digit != (y - 2))
        error++;

    return error;
}


/*Task III b)- Input patient name or patient ID to search patient's list for delete
* Data validation for all of the data key in*/
void Delete_Patient_Information(PATIENT pts[])
{
    string searchID, searchName, choice, opt;
    char action;
    int line;
    bool proceed = true;
    do {
        List_Patient(pts);
        cout << " Search delete patient detail (1-patient name   2-patient ID   3-back to menu) : ";//user choose whether search the patient data by patient name or patient id
        getline(cin, choice);
        if (choice != "1" && choice != "2" && choice != "3")    // if the choice is not 1, 2 or 3
        {
            cout << " Wrong input..." << endl;  //prompt error message
            cout << " "; system("PAUSE"); // halt program
            system("CLS"); // clear screen
            proceed = false;
        }
        else
        {
            action = choice[0];
            proceed = true; // if the choice is 1, 2 or 3, proceed
        }
    } while (!proceed); // terminate of proceed is true

    int counter = 0;
    if (action == '1') //choose to input patient name
    {
        do {
            system("CLS"); // clear screen
            List_Patient(pts);  //display patient list
            cout << " Enter Patient name : ";
            getline(cin, searchName); //Read in patient name
            for (int x = 0; x < maxrow; x++) //validation
            {
                if (pts[x].nameLst == searchName && searchName.size() > 0)  // if searchName match with the name in list and no empty value entered
                {
                    line = x;
                    cout << " Patient name found !" << endl; //if the name is found in the patient name list ,proceed to the next step,run the delete function and display patient data
                    cout << " "; system("PAUSE");// halts the program
                    do {
                        Patient_Detail(searchName, pts, action); //display patient data in detail
                        cout << " Do you want to delete the patient record shown? Yes(y)/ No(n): "; //confirm again whether want to delete or not
                        getline(cin, opt);

                        if (opt == "y" || opt == "Y") //if option is yes
                        {
                            Delete_Patient(pts, line); //delete the patient record match with name entered
                            List_Patient(pts); //display updated patient list
                            cout << "--------------------------------------- Delete successfully ----------------------------------" << endl;
                            counter++;
                        }
                        else if (opt == "n" || opt == "N") // if option is no, quit delete
                        {
                            cout << " Quit delete..." << endl;
                            counter++;
                        }
                        else
                        {
                            cout << " Error option entered..." << endl; //prompt eerror message
                            cout << " "; system("PAUSE"); //halt program
                            system("CLS"); // clear the screen
                        }

                    } while (counter == 0);
                }
            }
            if (counter == 0)
            {
                cout << " Patient name is not in the record. Please enter patient name again.\n";
                cout << " "; system("PAUSE"); //halt program
            }

        } while (counter == 0);
        cout << " You had exit the patient list." << endl; // exit patient list
    }
    else if (action == '2')//choose enter patient ID
    {
        do
        {
            system("CLS"); // cleart the screen
            List_Patient(pts);  //display patient list
            cout << " Enter patient ID :";
            getline(cin, searchID); //read in patient ID
            for (int x = 0; x < maxrow; x++)
            {
                if (pts[x].IDLst == searchID && searchID.size() > 0) //proceed if the ID is found in the ID list and no empty value entered
                {
                    line = x;
                    cout << " Patient ID found !" << endl;
                    cout << " "; system("PAUSE"); //halt the program
                    do {
                        Patient_Detail(searchID, pts, action); //display patient data in detail
                        cout << " Do you want to delete the patient record shown? Yes(y)/ No(n): "; //ask to confirm user whether want to delete or not
                        getline(cin, opt);

                        if (opt == "y" || opt == "Y") //if option is yes
                        {
                            Delete_Patient(pts, line);//delete the patient record match with ID entered
                            List_Patient(pts); //display updated patient list
                            cout << "--------------------------------------- Delete successfully ----------------------------------" << endl;
                            counter++;
                        }
                        else if (opt == "n" || opt == "N")// if option is no, quit delete
                        {
                            cout << " Quit delete..." << endl;
                            counter++;
                        }
                        else
                        {
                            cout << " Error option entered..." << endl; //prompt error message
                            cout << " "; system("PAUSE"); // halt the system
                            system("CLS"); // clear the screen
                        }
                    } while (counter == 0);
                }
            }
            if (counter == 0)
            {
                cout << " Patient ID is not in the record. Please enter patient ID again.\n" << endl; //prompt error message
                cout << " "; system("PAUSE"); //halt program
            }
        } while (counter == 0);
        cout << " You had exit the patient list." << endl; // exit patient list
    }
    else if (action == '3') {
        cout << " Back to menu..." << endl; // back to main menu
    }
}


/*Task III - Delete patient Information
*Delete ALL information relating to the selected patient(s) from the system.*/
void Delete_Patient(PATIENT pts[], int line)
{
    //Task III - Delete patient Information
    int y = maxrow;
    for (int j = line; j < (y - 1); j++)
    {
        // the array is moved up 1 step to replace the array match with seacrhName
        pts[j].nameLst = pts[j + 1].nameLst;
        pts[j].IDLst = pts[j + 1].IDLst;
        pts[j].ageLst = pts[j + 1].ageLst;
        pts[j].addressLst = pts[j + 1].addressLst;
        pts[j].c.doctorNameLst = pts[j + 1].c.doctorNameLst;
        pts[j].c.diagnosisLst = pts[j + 1].c.diagnosisLst;
        pts[j].c.patientStatusLst = pts[j + 1].c.patientStatusLst;
        pts[j].c.dateLst = pts[j + 1].c.dateLst;
    }
    if (line == (y - 1)) // if the array is in the last line, set it empty to delete it
    {
        pts[line].nameLst = "";
        pts[line].IDLst = "";
        pts[line].ageLst = "";
        pts[line].addressLst = "";
        pts[line].c.doctorNameLst = "";
        pts[line].c.diagnosisLst = "";
        pts[line].c.patientStatusLst = "";
        pts[line].c.dateLst = "";
    }
}


/* Task IV b)-Input patient name or patient ID to look into patient's detail for edit
* Data validation for all of the data key in
* User is required to repeat key in the value input until the correct value is entered .*/
void Advanced_Edit_Patient_Information(PATIENT pts[], DOCTOR d[])
{
    string searchName;
    string searchID;
    string choice;
    char action;
    List_Patient(pts);
    do {
        cout << " Look into patient detail (1-patient name   2-patient ID) : ";//user choose whether search the patient data by patient name or patient id
        getline(cin, choice);//get choice from user
        int y = choice.length();
        if (y == 1)
            action = choice[0];
        else
        {
            cout << " You should enter one character only " << endl;
            action = '0';
        }

    } while (action != '1' && action != '2'); // user entered anything other than 1 and 2 repeat again

    if (action == '1')//get choice from user
    {
        int counter = 0;
        do {
            cout << " Enter Patient name : ";
            getline(cin, searchName); //Read in patient name

            if (searchName.length() != 0)//if enter anything
            {
                cout << searchName << endl;
                for (int x = 0; x < maxrow; x++) //validation
                {
                    if (pts[x].nameLst == searchName)
                    {
                        cout << " Patient name found !"; //if the name is found in the patient name list ,proceed to the next step,go into function and display patient data
                        Patient_Detail(searchName, pts, action);//call in disply patient function
                        Edit_Patient(searchName, pts, d, action);//call in edit patient function
                        counter++;
                        break;
                    }
                }
            }
            if (counter == 0)
                cout << " Patient name is not in the record. Please enter patient name again.\n" << endl;
        } while (counter == 0);
    }
    else if (action == '2')//When user choose patient ID
    {
        int counter = 0;
        do {
            cout << " Enter patient ID :";
            getline(cin, searchID);//read in patient ID
            if (searchID.length() != 0) //if entered anything
            {
                for (int x = 0; x < maxrow; x++)
                {
                    if (pts[x].IDLst == searchID) //if the ID is found in the ID list ,proceed to the next step,go into function and display patient data
                    {
                        cout << " Patient ID found.";
                        Patient_Detail(searchID, pts, action);//call in disply patient function
                        Edit_Patient(searchID, pts, d, action);//call in edit patient function
                        counter++;
                        break;
                    }
                }
            }
            if (counter == 0)
                cout << " Patient ID is not in the record. Please enter patient ID again.\n" << endl;
        } while (counter == 0);
        cout << " You had exit the patient list." << endl; // exit patient list
    }
}


/*Task IV - Update/Edit patient information
* Input patient's ID or name to find the patient's detail that you want to edit
* Prompts for the Patient ID or Patient Name.
*This enables admin staff to update patient’s information*/
void Edit_Patient(string search, PATIENT pts[], DOCTOR d[], char action)
{
    string name;            //reserve 30 characters of memory for Patient's name
    string age;             //reserve 3 characters of memory for Patient's age
    string address;         //reserve 60 characters of memory for Patient's address
    string doctorName;      //reserve 30 characters of memory for Patient's Doctor Name
    string diagonisis;      //reserve 30 characters of memory for Diagonisis
    string patientStatus;   //reserve 15 characters of memory for Patient Status
    string date;            //reserve 12 characters of memory for Consultation Date
    int counter = 0;        //initialisation to find whether the patient exists in the system
    string target = ",";    //target to detect
    string choice;
    int count = 0;
    int found = -1;
    char actions;
    cout << " 1--Update Name" << endl;
    cout << " 2--Update Age" << endl;
    cout << " 3--Update Address" << endl;
    cout << " 4--Update Doctor's Name" << endl;
    cout << " 5--Update Diagnosis" << endl;
    cout << " 6--Update Patient Status" << endl;
    cout << " 7--Update Consultation Date" << endl;
    cout << "==============================================================================================" << endl;

    do {
        cout << " Please select a number to update : ";
        getline(cin, choice);//get the choice from user
        int y = choice.length();//test the number of character in the string
        if (y == 1) //if only one character is entered 
            actions = choice[0]; //take tha value and read it in char data type
        else  //if more one character is entered 
        {
            actions = '0';
        }
    } while (actions != '1' && actions != '2' && actions != '3' && actions != '4' && actions != '5' && actions != '6' && actions != '7'); //terminate when correct choice entered
    cout << "==============================================================================================" << endl;
    if (action == '1')//edit by using name
    {
        for (int x = 0; x < maxrow; x++)
        {
            if (pts[x].nameLst == search)   // if the seacrh ID match the list
            {
                if (actions == '1') //if choice is 1, update patient name
                {
                    // to read the new information that user update
                    int y = 0, count = 0;
                    string name;
                    do {
                        count = 0;
                        cout << "New Patient Name      : ";
                        getline(cin, name);//get name from user
                        y = name.length(); //get length of name
                        for (int i = 0; i < y; i++)//check all the character in the string
                        {
                            if (isalpha(name[i]))//if the name contain any thing that is not alphabet
                                count++;
                            else if (isspace(name[i]))
                                count++;
                        }
                    } while (count != y || y == 0 || y > 30 || isspace(name[0]));//number of character of length entered should less or equal to 30 and do not contain number or is space or empty.


                    pts[x].nameLst = name; //replace the previous record with the new updated record
                }

                else if (actions == '2') { //if choice is 2, update age
                    bool age_condition = true;
                    do {
                        age_condition = true;
                        cout << " Age               : "; getline(cin, age);
                        int z = age.length();
                        for (int i = 0; i < z; i++)//check all the character in the string
                        {
                            if (!isdigit(age[i])) {//if the age contains not digit character)
                                age_condition = false;
                            }
                        }
                        if (z != 0 && !isspace(age[0]) && age_condition == true)
                        {
                            int age_int;
                            age_int = stoi(age); //change the string to int type
                            if (age_int < 0 || age_int>150) //age entered should be in 0-149
                                age_condition = false;
                        }
                        else
                            age_condition = false;

                    } while (age_condition == false);//if the condition is false or the input is empty or white space}
                    pts[x].ageLst = age; //replace the previous record with the new updated record
                }

                else if (actions == '3')   // if choice is 3, update address
                {
                    int a;
                    do {
                        cout << " New Address           : ";
                        getline(cin, address);// get address from user
                        a = address.length();

                    } while (a > 60 || a == 0);//number of character of length entered should less or qual to 30 and do not contain number.
                    pts[x].addressLst = address;    // update the address with new address provided
                }

                else if (actions == '4')   //if choice is 4, update doctor name
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.doctorNameLst.find(target, found + 1); //to detect the target
                        if (found != -1) // if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " doctor records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        bool doc_assist = true;
                        int z;
                        do {

                            doc_assist = true;
                            cout << " New Doctor's Name for record " << i + 1 << "    : ";
                            getline(cin, doctorName); //get doctorname from user
                            z = doctorName.length();    //doctor name length
                            for (int x = 0; x < 10; x++)
                            {
                                if (d[x].DocnameLst == doctorName)// if doctor name is exist
                                {
                                    doc_assist = false;
                                }
                            }
                        } while (doc_assist == true || z == 0);

                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.doctorNameLst = doctorName;
                        else 
                            pts[x].c.doctorNameLst = pts[x].c.doctorNameLst + "," + doctorName;
                    }
                }

                else if (actions == '5')   //if choice is 5, update diagnosis
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.diagnosisLst.find(target, found + 1);//to detect the target
                        if (found != -1)// if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " diagnosis records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        int b;
                        do {
                            cout << " New Diagnosis for record " << i + 1 << "         :";
                            getline(cin, diagonisis);
                            b = diagonisis.length();//get diagonisis from user
                        } while (b > 15 || b == 0);

                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.diagnosisLst = diagonisis;
                        else 
                            pts[x].c.diagnosisLst = pts[x].c.diagnosisLst + "," + diagonisis;
                    }
                }

                else if (actions == '6')   //if choice is 6, update patient status
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.patientStatusLst.find(target, found + 1); //to detect the target
                        if (found != -1) //if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " date records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        do {
                            cout << " New Patient Status for record " << i + 1 << "     : ";
                            getline(cin, patientStatus);//get patient Status from user
                        } while (patientStatus != "Outpatient" && patientStatus != "outpatient" && patientStatus != "Inpatient" && patientStatus != "inpatient");
                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.patientStatusLst = patientStatus;
                        else 
                            pts[x].c.patientStatusLst = pts[x].c.patientStatusLst + "," + patientStatus;
                    }
                }

                else if (actions == '7')   //if choice is 7, update consultation date
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.dateLst.find(target, found + 1);//to detect the target
                        if (found != -1)// if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " date records...." << endl << endl;

                    for (int i = 0; i < count + 1; i++)
                    {
                        int error = 0;
                        int y;
                        string date;
                        bool flag = false;
                        do {
                            cout << " Consultation Date for record " << i + 1 << " (dd / mm / yyyy) : ";
                            getline(cin, date);
                            y = date.length();//get Consultation date from user
                            error = Validate_date(date);
                            if (error == 0) {
                                flag = true;
                            }
                        } while (y != 10 || flag == false); // terminate if date length no equal to 10 and flag is true


                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.dateLst = date;
                        else
                            pts[x].c.dateLst = pts[x].c.dateLst + "," + date;
                    }
                }

                // to inform user that they have successfully updated
                cout << "\n!!!!!!!!!! Successfully Updated !!!!!!!!!!" << endl;
                counter++; //counter +1 if the patient exists in the system
                break;
            }
        }
    }
    if (action == '2')// edit by using ID
    {
        for (int x = 0; x < maxrow; x++)
        {
            if (pts[x].IDLst == search)   // if the seacrh ID match the list
            {
                if (actions == '1') //if choice is 1, update patient name
                {
                    // to read the new information that user update
                    int y = 0, count = 0;
                    string name;
                    do {
                        count = 0;
                        cout << "New Patient Name      : ";
                        getline(cin, name);//get name from user
                        y = name.length(); //get length of name
                        for (int i = 0; i < y; i++)//check all the character in the string
                        {
                            if (isalpha(name[i]))//if the name contain any thing that is not alphabet
                                count++;
                            else if (isspace(name[i]))
                                count++;
                        }
                    } while (count != y || y == 0 || y > 30 || isspace(name[0]));//number of character of length entered should less or equal to 30 and do not contain number or is space or empty.
                    pts[x].nameLst = name; //replace the previous record with the new updated record
                }

                else if (actions == '2') { //if choice is 2, update age
                    bool age_condition = true;
                    do {
                        age_condition = true;
                        cout << " Age               : "; getline(cin, age);
                        int z = age.length();
                        for (int i = 0; i < z; i++)//check all the character in the string
                        {
                            if (!isdigit(age[i])) {//if the age contains not digit character)
                                age_condition = false;
                            }
                        }
                        if (z != 0 && !isspace(age[0]) && age_condition == true)
                        {
                            int age_int;
                            age_int = stoi(age); //change the string to int type
                            if (age_int < 0 || age_int>150) //age entered should be in 0-149
                                age_condition = false;
                        }
                        else
                            age_condition = false;

                    } while (age_condition == false);//if the condition is false or the input is empty or white space}
                    pts[x].ageLst = age; //replace the previous record with the new updated record
                }

                else if (actions == '3')   // if choice is 3, update address
                {
                    int a;
                    do {
                        cout << " New Address           : ";
                        getline(cin, address);// get address from user
                        a = address.length();

                    } while (a > 60 || a == 0);//number of character of length entered should less or qual to 30 and do not contain number.
                    pts[x].addressLst = address;    // update the address with new address provided
                }

                else if (actions == '4')   //if choice is 4, update doctor name
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.doctorNameLst.find(target, found + 1); //to detect the target
                        if (found != -1) // if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " doctor records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        bool doc_assist = true;
                        int z;
                        do {

                            doc_assist = true;
                            cout << " New Doctor's Name for record " << i + 1 << "    : ";
                            getline(cin, doctorName); //get doctorname from user
                            z = doctorName.length();    //doctor name length
                            for (int x = 0; x < 10; x++)
                            {
                                if (d[x].DocnameLst == doctorName)// if doctor name is exist
                                {
                                    doc_assist = false;
                                }
                            }
                        } while (doc_assist == true || z == 0);

                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.doctorNameLst = doctorName;
                        else 
                            pts[x].c.doctorNameLst = pts[x].c.doctorNameLst + "," + doctorName;
                    }
                }

                else if (actions == '5')   //if choice is 5, update diagnosis
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.diagnosisLst.find(target, found + 1);//to detect the target
                        if (found != -1)// if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " diagnosis records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        int b;
                        do {
                            cout << " New Diagnosis for record " << i + 1 << "         :";
                            getline(cin, diagonisis);
                            b = diagonisis.length();//get diagonisis from user
                        } while (b > 15 || b == 0);

                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.diagnosisLst = diagonisis;
                        else
                            pts[x].c.diagnosisLst = pts[x].c.diagnosisLst + "," + diagonisis;
                    }
                }

                else if (actions == '6')   //if choice is 6, update patient status
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.patientStatusLst.find(target, found + 1); //to detect the target
                        if (found != -1) //if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " date records...." << endl << endl;
                    for (int i = 0; i < count + 1; i++)
                    {
                        do {
                            cout << " New Patient Status for record " << i + 1 << "     : ";
                            getline(cin, patientStatus);//get patient Status from user
                        } while (patientStatus != "Outpatient" && patientStatus != "outpatient" && patientStatus != "Inpatient" && patientStatus != "inpatient");
                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.patientStatusLst = patientStatus;
                        else 
                            pts[x].c.patientStatusLst = pts[x].c.patientStatusLst + "," + patientStatus;
                    }
                }

                else if (actions == '7')   //if choice is 7, update consultation date
                {
                    count = 0;
                    found = -1;
                    do {
                        found = pts[x].c.dateLst.find(target, found + 1);//to detect the target
                        if (found != -1)// if target found add 1
                            count++;
                    } while (found != -1);
                    cout << " This patient have " << count + 1 << " date records...." << endl << endl;

                    for (int i = 0; i < count + 1; i++)
                    {
                        int error = 0;
                        int y;
                        string date;
                        bool flag = false;
                        do {
                            cout << " Consultation Date for record " << i + 1 << " (dd / mm / yyyy) : ";
                            getline(cin, date);
                            y = date.length();//get Consultation date from user
                            error = Validate_date(date);
                            if (error == 0) {
                                flag = true;
                            }
                        } while (y != 10 || flag == false); // terminate if date length no equal to 10 and flag is true


                        //replace the previous record with the new updated record
                        if (i == 0)
                            pts[x].c.dateLst = date;
                        else 
                            pts[x].c.dateLst = pts[x].c.dateLst + "," + date;
                    }

                    // to inform user that they have successfully updated
                    cout << "\n!!!!!!!!!! Successfully Updated !!!!!!!!!!" << endl;
                    counter++; //counter +1 if the patient exists in the system
                    break;
                }
            }
        }
        if (counter == 0)// the patient is not exist in the system
               // to inform user that the id is not exist
            cout << "\n!!!!!!!!!! No Record Found !!!!!!!!!!" << endl;
    }
}


/* Task VI b)-Input patient name or patient ID to search patient's list
* Data validation for all of the data key in*/
void Search_Patient(PATIENT pts[])
{
    string choice; // to identify user what to search by name or ID
    char action;
    List_Patient(pts);// call display all patient function
    do {
        cout << " Search patient detail (1-patient name   2-patient ID   3-quit search) : ";//user choose whether search the patient data by patient name or patient id
        getline(cin, choice);//get choice from user
        int y = choice.length();

        if (y == 1)//if choice enter by user is 1
            action = choice[0];
        else // when user enter more than 1 character
        {
            cout << " You should enter one character only " << endl;
            action = '0';
        }

    } while (action != '1' && action != '2' && action != '3'); //Repeat when the user enter invalide number 

    if (action == '1') //When user choose patient name
    {
        string avdSearchName;
        cout << " Enter patient Name :";
        getline(cin, avdSearchName);//get name from the user
        Search_Patient_by_Name(pts, avdSearchName); // call in search patient function 
    }
    else if (action == '2') // When user choose patient ID
    {
        string avdSearchID;
        cout << " Enter patient ID :";
        getline(cin, avdSearchID);//get ID from the user
        Search_Patient_by_ID(pts, avdSearchID);// call in search patient function 
    }
    else if (action == '3')// if the user choose to quit 
    {
        cout << "Quit advanced search";
    }
}


/*Task VI - Advanced Search-(Name)
* Search for patient(s) using the Patient Name
* Print the full details of the matching entry(s).
* It can match word(s)/number within a string/number, and also print multiple results.*/
void Search_Patient_by_Name(PATIENT pts[], string avdSearchName)
{
    int counter = 0;//find whether the  data in the avdsearchName match the element in the array
    system("CLS");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                 Patient Management System" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                        Patient List  " << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << " No.  ||        Patient Name     ||     Patient ID     ||      Consultation  Date  " << endl;
    cout << "========================================================================================================================" << endl;

    if (avdSearchName.length() != 0)//if enter anything
    {
        for (int x = 0; x < maxrow; x++)
        {
            std::size_t found = pts[x].nameLst.find(avdSearchName);
            if (found != std::string::npos)//npos:until the end of the string== -1.no matches //if not found ,then return -1
            {
                counter++;//if the words in the avdsearchName match the element in the array
                cout << fixed << endl;
                cout << " " << setw(3) << counter << "      " << setw(20) << pts[x].nameLst << "       " << setw(15) << pts[x].IDLst << "       " << setw(26) << pts[x].c.dateLst << endl;
            }
        }
    }
    if (counter == 0)//if nothing in the avdsearchName match the element in the array
    {
        cout << "--------------------------------!!! No Record Found!!!---------------------------------------" << endl;
    }
    cout << "\n===================================================================================================================" << endl;
}


/*Task VI - Advanced Search-(ID)
* Search for patient(s) using the Patient ID
* Print the full details of the matching entry(s).
* It can match word(s)/number within a string/number, and also print multiple results.*/
void Search_Patient_by_ID(PATIENT pts[], string avdSearchID)
{
    int counter = 0;//find whether the  data in the avdsearchID match the element in the array
    system("CLS");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                 Patient Management System" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                        Patient List  " << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << " No.  ||        Patient Name     ||     Patient ID     ||      Consultation  Date  " << endl;
    cout << "========================================================================================================================" << endl;

    if (avdSearchID.length() != 0)//if enter anything
    {
        for (int x = 0; x < maxrow; x++)
        {
            std::size_t found = pts[x].IDLst.find(avdSearchID);
            if (found != std::string::npos)
            {
                counter++;//if the words in the avdsearchName match the element in the array
                cout << fixed << endl;
                cout << " " << setw(3) << counter << "      " << setw(20) << pts[x].nameLst << "       " << setw(15) << pts[x].IDLst << "       " << setw(26) << pts[x].c.dateLst << endl;
            }
        }
    }
    if (counter == 0) //if nothing in the avdsearchID match the element in the array
    {
        cout << "--------------------------------!!! No Record Found!!!---------------------------------------" << endl;
    }
    cout << "\n=============================================================================================" << endl;
}


/*Task VII - Exit (Writing data to file)-(patient)
* The program will write the updated data in the list to the doctor file.*/
void Save_Patient(PATIENT pts[])
{
    ofstream orgFile//s the default mode for std::ofstream, it means that output operations can be used (i.e. you can write to the file).
    //If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.
        //ios out contains trunc but trunc does not contain out
        //means that when the file is opened, the old contents are immediately removed.
        // Again, this is only meaningful if the file is also open for output.
        //Truncate file; that is, delete file content
        // ios::trunc is used to truncate a file if it exists. It is not a file opening mode
        //open first and then delete the file content
        //Your code just uses the default ios::out mode. So it starts writing from the beginning of the file, but doesn't remove the old contents. So the new contents will overlay what's already there -- if the file is originally 10 bytes long, and you write 3 bytes, the result will be the 3 bytes you write followed by the remaining 7 bytes of the original contents.
        //More concretely, if the file originally contains:
    orgFile.open("PatientList.txt", ios::trunc); // Append mode  that when the file is opened, the old contents are immediately removed. Again, this is only meaningful if the file is also open for output.
    if (!orgFile)//set to false if open failed
    {
        cout << " Error opening input file" << endl;
    }
    else {
        for (int x = 0; x < maxrow; x++)  //marrow = 30 ,write all data into file
        {
            if (pts[x].IDLst == "\0") //if reach the end of array that is empty
            {
                break;
            }
            else
            {
                //write all the data into the file
                orgFile << pts[x].nameLst + "%" + pts[x].IDLst + "%" + pts[x].ageLst + "%" + pts[x].addressLst + "%" + pts[x].c.doctorNameLst + "%" + pts[x].c.diagnosisLst + "%" + pts[x].c.patientStatusLst + "%" + pts[x].c.dateLst << endl;
            }
        }
        orgFile.close(); // Close the file
    }
}


/*Task VII - Exit (Writing data to file)-(doctor)
* The program will write the updated data in the list to the doctor file.*/
void Save_Doctor(DOCTOR d[])
{

    ofstream fout;  // Create object of ofstream
    fout.open("DoctorList.txt", ios::trunc); // Append mode
    if (!fout)//set to false if open failed
        cout << " Error opening input file" << endl;

    else
    {
        for (int x = 0; x < 10; x++)  //marrow = 10 ,write all data into file
        {
            if (d[x].DocnameLst == "\0") //if reach the end of array that is empty
                break;
            else
                //add data into a list and write data to file
                fout << d[x].DocIDLst + "/" + d[x].DocnameLst << endl;
        }
        fout.close(); // Close the file at the end
    } 
}
