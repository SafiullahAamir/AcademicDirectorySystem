#include <iostream>
#include <conio.h>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <windows.h>

using namespace std;
class Admin;
class AVL
{
public:
    struct Node
    {
        int roll_no;
        int Fees, Credit_h;
        int Scholarship;
        string id, std_name, fthr_name, Program;
        string password;
        int semester_no;
        Node *left;
        Node *right;
        int height;

        Node(int rn, string ID, string pass, string f_n, string s_n, int ss, string prgrm, int fee, int cH, int sem)
        {
            std_name = s_n;
            fthr_name = f_n;
            Scholarship = ss;
            Program = prgrm;
            Fees = fee;
            Credit_h = cH;
            roll_no = rn;
            id = ID;
            password = pass;
            semester_no = sem;
            left = NULL;
            right = NULL;
            height = 0;
        }
    };

    Node *root;

    AVL()
    {
        root = NULL;
    }

    int get_height(Node *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return n->height;
    }

    int get_balance(Node *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return get_height(n->left) - get_height(n->right);
    }

    Node *rotate_left(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(get_height(x->left), get_height(x->right)) + 1;
        y->height = max(get_height(y->left), get_height(y->right)) + 1;

        return y;
    }

    Node *rotate_right(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(get_height(y->left), get_height(y->right)) + 1;
        x->height = max(get_height(x->left), get_height(x->right)) + 1;

        return x;
    }

    Node *rotate_leftRight(Node *z)
    {
        z->left = rotate_left(z->left);
        return rotate_right(z);
    }

    Node *rotate_rightLeft(Node *z)
    {
        z->right = rotate_right(z->right);
        return rotate_left(z);
    }

    void add_node(int rn, string ID, string pass, string f_n, string s_n, int ss, string prgrm, int fee, int cH, int sem, Node *&t)
    {
        if (t == NULL)
        {
            t = new Node(rn, ID, pass, f_n, s_n, ss, prgrm, fee, cH, sem);
            return;
        }

        if (rn < t->roll_no)
        {
            add_node(rn, ID, pass, f_n, s_n, ss, prgrm, fee, cH, sem, t->left);
        }
        else if (rn > t->roll_no)
        {
            add_node(rn, ID, pass, f_n, s_n, ss, prgrm, fee, cH, sem, t->right);
        }
        else
        {
            return;
        }

        t->height = max(get_height(t->left), get_height(t->right)) + 1;
        int balance = get_balance(t);

        // Left-Left Case
        if (balance > 1 && rn < t->left->roll_no)
        {
            t = rotate_right(t);
        }

        // Right-Right Case
        if (balance < -1 && rn > t->right->roll_no)
        {
            t = rotate_left(t);
        }

        // Left-Right Case
        if (balance > 1 && rn > t->left->roll_no)
        {
            t = rotate_leftRight(t);
        }

        // Right-Left Case
        if (balance < -1 && rn < t->right->roll_no)
        {
            t = rotate_rightLeft(t);
        }
    }

    int find_max()  //to assign by default id
    {
        if (root == NULL)
            return 0;

        Node *temp = root;      
        while (temp->right != NULL)
        {
            temp = temp->right;     // most right will have the greatest value
        }
        return temp->roll_no;
    }

    Node *min_val_node(Node *node)
    {
        Node *current = node;
        while (current && current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    Node *delete_node(Node *node, int rn)
    {
        if (node == NULL)
        {
            return node;
        }

        if (rn < node->roll_no)
        {
            node->left = delete_node(node->left, rn);
        }
        else if (rn > node->roll_no)
        {
            node->right = delete_node(node->right, rn);
        }
        else
        {
            if (node->left == NULL || node->right == NULL)
            {
                Node *temp;
                if (node->left != NULL)
                {
                    temp = node->left;
                }
                else
                {
                    temp = node->right;
                }
                delete node;
                return temp;
            }

            Node *temp = min_val_node(node->right);
            node->roll_no = temp->roll_no;
            node->id = temp->id;
            node->password = temp->password;
            node->std_name = temp->std_name;
            node->fthr_name = temp->fthr_name;
            node->Scholarship = temp->Scholarship;
            node->Program = temp->Program;
            node->Fees = temp->Fees;
            node->Credit_h = temp->Credit_h;
            node->semester_no=temp->semester_no;

            node->right = delete_node(node->right, temp->roll_no);
        }

        node->height = max(get_height(node->left), get_height(node->right)) + 1;

        int balance = get_balance(node);

        if (balance > 1 && get_balance(node->left) >= 0)
        {
            return rotate_right(node);
        }

        if (balance > 1 && get_balance(node->left) < 0)
        {
            return rotate_leftRight(node);
        }

        if (balance < -1 && get_balance(node->right) <= 0)
        {
            return rotate_left(node);
        }

        if (balance < -1 && get_balance(node->right) > 0)
        {
            return rotate_rightLeft(node);
        }
        
        return node;
    }

    Node *search(Node *node, int rn)
    {
        if (node == NULL || node->roll_no == rn)
        {
            return node;
        }

        if (rn < node->roll_no)
        {
            return search(node->left, rn);
        }

        return search(node->right, rn);
    }

    void promotes_sem(Node *root)       // in order traversal 
    {
        if (root != nullptr)
        {
            promotes_sem(root->left);
            if(root->semester_no <8 )
                root->semester_no+=1;       // increment semester
            promotes_sem(root->right);
        }
    }

    void inorder_traversal(Node *root)
    {
        if(root == nullptr)
        {
           return;
        }
        inorder_traversal(root->left);
        cout << "Roll No: " << root->roll_no << endl;
        cout << "Name: " << root->std_name << endl;
        cout << "Father's Name: " << root->fthr_name << endl;
        cout << "Program: " << root->Program << endl;
        cout << "ID: " << root->id << endl;
        cout << "Semester: " << root->semester_no << endl;
        cout << "Fees: " << root->Fees << endl;
        cout << "Credit Hours: " << root->Credit_h << endl;
        cout << "Scholarship: " << root->Scholarship << endl;
        cout << "Password: " << root->password << endl;
        cout << "-----------------------------" << endl;
        inorder_traversal(root->right);
    }
};

class Admin : public AVL
{
private:
    string syntax = "@ads.com";
    string name, father_name, mail, pass_word;
    int rollNo;
    int scolarship;
    string prg_n;
    int fee, crdt_hrs;
    int choice = 0;
    int sem;
    struct program  // programs details
    {
        string name_p[5] = {"BS Computer Science", "BS Software Engineering", "BS Cyber Security", "BS Artificial Intelligence", "BS Data Science"};
        int fees[5] = {1990000, 1890000, 1490000, 1001000, 1590000};
        int credit_hour[5] = {133, 133, 133, 130, 132};
    };

    struct Feedback_Node    // struct of queue of feedback using single linked list
    {
        string feedback;
        Feedback_Node* next;
        Feedback_Node(string msg)
        {
            feedback = msg;
            next = nullptr;
        }
    };

    Feedback_Node* front = nullptr;
    Feedback_Node* rear = nullptr;
    string filename = "feedbacks.txt";

    struct Announce
    { // changes here

        string title;
        string content;
        // bool publish;

        Announce(string t = "", string c = "")
        { // in case arguments are not passed
            title = t;
            content = c;
            // publish = false;
        }
    };

public:

    Admin()
    {
        load_feedbacks_from_file();
    }

    void Add_std_detail()
    {
        rollNo = find_max() + 1;
        add_mail();
        sem = 1;
        setTextColor('A');
        cout << "~~~~~~~~~~~~~~~~~~~ Student Roll No. " << setw(3) << setfill('0') << rollNo << " ~~~~~~~~~~~~~~~~~~~\n" << endl;
        setTextColor(7);
        cout << "\t" << "Student Name          : ";
        getline(cin, name);
        cout << "\t" << "Student Mail          : " << mail << endl;
        cout << "\t" << "Student Mail Password : ";
        getline(cin, pass_word);
        
        cout << "\t" << "Student Semester      : " << sem << endl;
        cout << "\t" << "Student Father's Name : ";
        getline(cin, father_name);
        cout << "\t" << "Student Scholarship   : ";
        cin >> scolarship;
        while(scolarship%5!=0)
        {
            cout << "\t" << "Student Scholarship (%5==0)  : ";
            cin >> scolarship;
        }
        add_program(prg_n, crdt_hrs, fee);
        
        add_node(rollNo, mail, pass_word, father_name, name, scolarship, prg_n, fee, crdt_hrs, sem, root);
    }

    void delete_student()
    {
        system("cls");
        int r_n;
        cout << "Enter Roll No to delete ('0' to go back): ";
        cin >> r_n;
        if(r_n==0)
        {
            return;
        }
        else
        {
            delete_node(root, r_n);
            setTextColor(2);
            cout << "Student successfully deleted" << endl;
            setTextColor(7);
            system("pause");
        }
    }

    void add_program(string &p, int &c, int &f)
    {
        program obj;
        choice = displayMenu(obj.name_p, 5) - 1;
        p = obj.name_p[choice];
        c = obj.credit_hour[choice];
        f = obj.fees[choice];
        system("cls");
        setTextColor(2);
        cout << "Student Have Been Added Successfully " << endl;
        setTextColor(7);
        system("pause");
    }
    void add_mail()
    {
        ostringstream os;
        os.width(3);
        os.fill('0');
        os << rollNo;
        mail = "st" + os.str();
        mail += syntax;
    }

    void setTextColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void hide_cursor()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(hConsole, &info);
        info.bVisible = false;
        SetConsoleCursorInfo(hConsole, &info);
    }

    void drawMenu(int highlight, string options[], int size)
    {
        system("cls");
        cout << "         Academic Directory System       \n";
        cout << "========================================\n";

        for (int i = 0; i < size; i++)
        {
            if (i + 1 == highlight)
            {
                setTextColor(4);
                cout << " [" << i + 1 << "] " << options[i] << "\n";
                setTextColor(7);
            }
            else
            {
                cout << " [" << i + 1 << "] " << options[i] << "\n";
            }
        }
        cout << "========================================\n";
    }

    int displayMenu(string options[], int size) // need
    {
        int highlight = 1;
        while (true)
        {
            hide_cursor();
            drawMenu(highlight, options, size);
            int key = getch();

            if (key == 72 && highlight > 1) // up
            {
                highlight--;
            }
            else if (key == 80 && highlight < size) // down
            {
                highlight++;
            }

            if (key == 13) // Enter
            {
                system("cls");
                return highlight;
            }
        }
    }
    void view_all() // view all
    {
        system("cls");
        inorder_traversal(root);
        system("pause");
    }
    void update()
    {
        int rn;
        cout << "Enter Roll. No: ";
        cin >> rn;
        Node *temp = search(root, rn);
        system("cls");
        if (temp == NULL)
        {
            cout << "Id Doesn\'t Exist " << endl;
            system("pause");
            return;
        }
        else
        {
            string options[2] = {"Update All", "Update Specific"};
            choice = displayMenu(options, 2);
            if (choice == 1)
            {
                cin.ignore(100, '\n');
                setTextColor('A');
                cout << "~~~~~~~~~~~~~~~~~~~ Updating Roll No. " << setw(3) << setfill('0') << temp->roll_no << " ~~~~~~~~~~~~~~~~~~~ " << endl;
                setTextColor(7);
                cout << setw(23) << setfill(' ') << "Student Name          : ";
                getline(cin, temp->std_name);
                cout << setw(23) << setfill(' ') << "Student Mail Password : ";
                getline(cin, temp->password);
                cout << setw(23) << setfill(' ') << "Student Father's Name : ";
                getline(cin, temp->fthr_name);
                cout << setw(23) << setfill(' ') << "Student Scholarship   : ";
                cin >> temp->Scholarship;
                while(scolarship%5!=0)
                {
                    cout << "\t" << "Student Scholarship (%5==0)  : ";
                    cin >> temp->Scholarship;
                }
                add_program(temp->Program, temp->Credit_h, temp->Fees);
                cin.ignore(100, '\n');
            }
            else if (choice == 2)
            {
                cin.ignore(100, '\n');
                int c;
                string upd_opt[6] = {"Update Name", "Update Father Name", "Update Password", "Update Scholarship", "Update Program", "Update Semester"};
                c = displayMenu(upd_opt, 6);

                setTextColor('A');
                cout << "~~~~~~~~~~~~~~~~~~~ Updating Roll No. " << setw(3) << setfill('0') << temp->roll_no << " ~~~~~~~~~~~~~~~~~~~ " << endl;
                setTextColor(7);

                if (c == 1)
                {
                    cout << setw(23) << setfill(' ') << "Student Name: ";
                    getline(cin, temp->std_name);
                }
                else if (c == 2)
                {
                    cout << setw(23) << setfill(' ') << "Student Father's Name: ";
                    getline(cin, temp->fthr_name);
                }
                else if (c == 3)
                {
                    cout << setw(23) << setfill(' ') << "Student Mail " << temp->id << " Password: ";
                    getline(cin, temp->password);
                }
                else if (c == 4)
                {
                    cout << setw(23) << setfill(' ') << "Student Scholarship: ";
                    cin >> temp->Scholarship;
                    while(scolarship%5!=0)
                    {
                        cout << "\t" << "Student Scholarship (%5==0)  : ";
                        cin >> temp->Scholarship;
                    }
                }
                else if (c == 5)
                {
                    system("cls");
                    add_program(temp->Program, temp->Credit_h, temp->Fees);
                }
                else
                {
                    cout << setw(23) << setfill(' ') << "Student Semester: ";
                    cin >> temp->semester_no;
                }
            }
        }
    }

    void load_feedbacks_from_file() 
    {
        ifstream file(filename);
        string feedback;
        while (getline(file, feedback)) 
        {
            enqueue_from_file(feedback);
        }
        file.close();
    }

    void save_feedback_to_file(string &feedback) 
    {
        ofstream file(filename, ios::app);
        file << feedback << endl;
        file.close();
    }

    void clear_file() 
    {
        ofstream file(filename, ios::trunc); //will delete whole data of file
        file.close();
    }

    void enqueue_from_file(string feedback) 
    {
        Feedback_Node* newNode = new Feedback_Node(feedback);
        if (rear == nullptr) 
        {
            front = rear = newNode;
        } 
        else 
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void enqueue(string feedback) 
    {
        Feedback_Node* newNode = new Feedback_Node(feedback);
        if (rear == nullptr) 
        {
            front = rear = newNode;
        } 
        else 
        {
            rear->next = newNode;
            rear = newNode;
        }
        save_feedback_to_file(feedback);
        setTextColor(2);
        cout << "Feedback added successfully!\n";
        setTextColor(7);
    }

    void view_feedback() 
    {
        int count = 0;
        system("cls");
        if (front == nullptr) 
        {
            setTextColor(4);
            cout << "No feedback available.\n";
            setTextColor(7);
            system("pause");
            return;
        }
        Feedback_Node* temp = front;
        cout << "Feedbacks:\n";
        while (temp != nullptr) 
        {
            count++;
            cout << count << "- " << temp->feedback << endl;
            temp = temp->next;
        }
        cout << endl;
        system("pause");
        string choices[2]={"Clear Feedbacks", "Back to Admin Menu"};
        int c = displayMenu(choices,2);
        switch(c)
        {
            case 1: 
                clear_feedback(); 
                break;
            case 2: 
                return;
        }
    }

    void clear_feedback() 
    {
        while (front != nullptr) 
        {
            Feedback_Node *temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        clear_file();
        cout << "All feedbacks have been cleared.\n";
    }

    const int s = 5;
    Announce A[5];
    int top = 0;
    int counter = 0;
    bool loaded = false;
    //string finame = "announcements.txt";

    bool isFull()
    {
        return counter == s;
    }

    bool isEmpty()
    {
        return counter == 0;
    }

    void save_to_file() 
    {
        ofstream file("announcements.txt", ios::trunc);
        for (int i = 0; i < counter; i++) 
        {
            int index = (top + i) % s;  // Circular indexing
            file << A[index].title << "\n" << A[index].content << "\n";
        }
        file.close();
    }

    void load_from_file() 
    {
        if (loaded) return;
        ifstream file("announcements.txt");
        string title, content;
        while (getline(file, title) && getline(file, content)) 
        {
            push(title, content);
        }
        file.close();
        loaded = true;
    }

    void push(string t, string c)
    {
        if (isFull())
        {
            top = (top + 1) % s;  //circular stack
        }
        else
        {
            counter++;
        }

        A[(top + counter - 1) % s] = Announce(t, c);
        save_to_file();
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "No announcements are left to remove." << endl;
            return;
        }
        top = (top + 1) % s;
        counter--;
        save_to_file();
    }

    void view_all_announcements()
    {
        load_from_file();
        if (isEmpty())
        {
            cout << "No Announcements Yet" << endl;
        }
        else
        {
            for (int i = counter - 1; i >= 0; i--)
            {
                int index = (top + i) % s;
                cout << "TITLE: " << A[i].title << endl;
                cout << "CONTENT: " << A[i].content << endl;
                cout << "-------------------------" << endl << endl;
            }
        }
        system("pause");
    }

    void Announcements()
    {
        load_from_file();

        label:
        string options[] = {"Add Announement", "Delete Announement", "Current Announcements", "Exit"};
        int c = displayMenu(options, 4);
        switch (c)
        {
        case 1:
        {
            string title;
            string content;
            cout << "Enter the title of the announcement: " << endl;
            getline(cin, title);
            cout << "Enter the content of the announcement: " << endl;
            getline(cin, content);
            push(title, content);
            //cin.ignore(100, '\n');
            break;
            goto label;
        }
        case 2:
            pop();
            cout << "Succesfully Deleted" << endl;
            system("pause");
           goto label;
        case 3:
            if (isEmpty())
            {
                cout << "No announcements available." << endl;
            }
            else
            {
                view_all_announcements();
            }
            goto label;
        case 4:
            return;
        }
    }
};
// student class
class Student : public Admin
{
    string sem_start4[4][6] = {{"ICT LAB", "PF LAB", "ICT THEORY", "PF THEORY", "English", "Calculus and Analytical Geomtery"}, {"OOP Lab", "DLD Lab", "OOP theory", "DLD theory", "Linear Algebra", "Discrete Structure"}, {"DSA LAB", "COAL LAB", "DSA THEORY", "COAL THEORY", "Probability", "Software Engineering"}, {"Computer Networks LAB", "Database System Lab", "Database Theory", "Computer Network Theory", "Technical Elective 1", "Computer Architecture"}};
    string sem_end4[5][4][6] = {{{"Operating Systems Lab", "Operating System Theory", "Theory of Automata", "Information Security", "Analysis of Algorithms", "Techniqal Elective 2"}, // CS
                                 {"AI", "Human Computer Interaction", "Compiler Construction", "Technical Elective 3", "Technical Elective 4", "21st Century Skills"},
                                 {"Final Year Project I", "Advance Database Management System Lab", "Advance Database Management System", "Parallel & Distributed Computing", "Technical Elective 5", "Technical Elective 6"},
                                 {"Final Year Project II", "University Elective", "Technical Elective 7", "COOP", " ", " "}},
                                {{"Software Design & Architecture Lab", "Operating System Lab", "Softwar Design & Architecture", "Operating System", "Computer Network", "Computer Network Lab"}, // SE
                                 {"Software Construction & Development Lab", "Software Construction & Development", "Web Engineering", "Human Computer Interaction", "Information Security", "Technical Elective"},
                                 {"Final Year Project I", "Software Project Management", "Software Quality Engineering", "Software Re-Engineeering", "Technical Elective II", "Technical Elective III"},
                                 {"Final Year Project II", "Professional Practice", "Technical Elective IV", "Technical Elective V", "", ""}},
                                {{"Cyber Security Lab", "Cyber Security Lab", "Operating System Lab", "Operating System", "Artificial Intelligence", "Techniqal Elective II"}, // Cyber
                                 {"Secure Software Construction & Development Lab", "Secure Software Construction & Development", "Network Security", "Analysis of Algorithm", "Technical Elective III", "Technical Elective IV"},
                                 {"Final Year Project I", "Digital Forensic", "Parallel Distributed", "Technical Elective V", "21 Century Skill", "University Elective"},
                                 {"Final Year Project II", "University Elective II", "Technical Elective VI", "Technical Elective VII"}},
                                {{"Artificial Intelligence Lab", "Artificail Intelligence", "Operating System Lab", "Operating System", "Deep Learning and Neural Networks", "Information Security"}, // AI
                                 {"Programming for Artificail Intelligence Lab", "Programming for Artificail Intelligence", "Parallel Distributed Computing Lab", "Parallel Distributed Computing", "Computer Vision Lab", "Computer Vision"},
                                 {"Final Year Project I", "Neutral Language Processing", "AI Elective I", "AI Elective II", "English", "Research Paper Writing and Presentation"},
                                 {"Final Year Project II", "AI Elective III", "Professional Practices", "21 Century Skill", "", ""}},
                                {{"Operating Systems Lab", "Operating Systems", "Data Mining", "Advance Statistics", "DS Elective I", "DS Elective II"}, // data science
                                 {"Professional Practices", "Artficial Intelligence", "Artficial Intelligence Lab", "Data Warehousing & Business Intelligence", "DS Elective III", "DS Elective IV"},
                                 {"Final Year Project I", "Data Visualization", "University Elective", "Big Data Analytics", "Analysis of Algorithms", "English Immersion"},
                                 {"Final Year Project II", "21 Century Skill", "Information Security", "Parallel & Distributed Computing", "", ""}}};                                 ;


public:
    int extract_id(string userID)
    {
        return stoi(userID.substr(2, 3));
    }
    void view(Node *node)
    {
        system("cls");
        setTextColor('A');
        cout << "~~~~~~~~~~~~~~~~~~~ Student Roll No. " << setw(3) << setfill('0') << node->roll_no << " ~~~~~~~~~~~~~~~~~~~\n" << endl;
        setTextColor(7);
        cout << "\t" << setw(24) << left << setfill(' ') << "Student Name         : " << node->std_name << endl;
        cout << "\t" << setw(24) << left << setfill(' ') << "Student Father Name  : " << node->fthr_name << endl;
        cout << "\t" << setw(24) << left << setfill(' ') << "Student Program      : " << node->Program << endl;
        cout << "\t" << setw(24) << left << setfill(' ') << "Student Semester     : " << node->semester_no << endl;
        cout << "\t" << setw(24) << left << setfill(' ') << "Credit Hour per Sem  : " << node->Credit_h / 8 << endl;
        cout << "\t" << setw(24) << left << setfill(' ') << "Student ScholarShip  : " << node->Scholarship << "%\n" << endl;

        setTextColor(6);
        system("pause");
        setTextColor(7);
    }
    void time_table(Node *n)
    {
        int c = 6;
        string time_[6][2] = {{"Mon/Wed", "9.30-10.45"}, {"Mon/Wed", "11.15-12.30"}, {"Tues/Fri", "9.30-10.45"}, {"Tues/Fri", "11.15-12.30"}, {"Thurs/Sat", "9.30-10.45"}, {"Thurs/Sat", "11.15-12.30"}};
        int t = find_courseNo(n->Program)-1;
        cout << setw(30) << setfill(' ') << "Time Table Of " << n->semester_no << " Semester :" << endl;
        if (n->semester_no <= 4)
        {
            for (int w = 0; w < 6; w++)
            {
                cout << left << setw(45) << sem_start4[n->semester_no - 1][w] + ":" << setw(15) << time_[w][0] << time_[w][1] << endl;
            }
        }
        else
        {
            if (n->semester_no == 8)
            {
                c = 4;
            }
            for (int w = 0; w < c; w++)
            {
                cout << left << setw(45) << sem_end4[t][n->semester_no - 5][w] + ":" << setw(15) << time_[w][0] << time_[w][1] << endl;
            }
        }
        cout << right;
        system("pause");
    }
    void start_4(int z)
    {
        cout << "Semester No. " << z << " Courses: " << endl;
        for (int i = 0; i < 6; i = i + 2)
        {
            cout << left << setw(60) << to_string(i + 1) + ". " + sem_start4[z - 1][i] << setw(15) << to_string(i + 2) + ". " + sem_start4[z - 1][i + 1] << endl;
        }
    }
    void end_4(int z, int c_n, int c)
    {
        cout << "Semester No. " << z << " Courses: " << endl;
        for (int i = 0; i < c; i = i + 2)
        {
            cout << left << setw(60) << to_string(i + 1) + ". " + sem_end4[c_n - 1][z - 5][i] << to_string(i + 2) + ". " + sem_end4[c_n - 1][z - 5][i + 1] << endl;
        }
    }
    int find_courseNo(string c_n)
    {
        // string name_p[5] = {"BS Computer Science", "BS Software Engineering", "BS Cyber Security", "BS Artificial Intelligence", "BS Data Science"};
        if (c_n == "BS Computer Science")
            return 1;
        else if (c_n == "BS Software Engineering")
            return 2;
        else if (c_n == "BS Cyber Security")
            return 3;
        else if (c_n == "BS Artificial Intelligence")
            return 4;
        else
            return 5;
    }
    void courses(Node *n)
    {
        cout << "Viewing My Courses..." << endl;
        string m[3] = {"Semester Courses", "All", "Exit"};
        int c_n = find_courseNo(n->Program);
        int c;
        while (true)
        {
            c = displayMenu(m, 3);
            if (c == 1)
            {
                if (n->semester_no <= 4)
                {
                    start_4(n->semester_no);
                }
                else
                {
                    if (n->semester_no == 8)
                    {
                        end_4(n->semester_no, c_n, 4);
                    }
                    else
                    {
                        end_4(n->semester_no, c_n, 6);
                    }
                }
                system("pause");
                system("cls");
            }
            else if (c == 2)
            {
                for (int z = 1; z <= 4; z++)
                {
                    start_4(z);
                }

                for (int z = 5; z <= 8; z++)
                {
                    if (z == 8)
                    {
                        end_4(z, c_n, 4);
                    }
                    else
                    {
                        end_4(z, c_n, 6);
                    }
                }
                system("pause");
                system("cls");
            }
            else
            {
                cout << right;
                return;
            }
        }
        system("pause");
    }

    void payment(Node *discount)
    {
        cout << "Viewing Payment..." << endl;
        system("cls");
        float discountA;
        int finalFee;

        discountA = (float(discount->Scholarship) / 100) * discount->Fees;
        finalFee = discount->Fees - discountA;
        cout << setw(80) << "=========================================" << endl;
        cout << setw(80) << "|           FEE PAYMENT RECEIPT         |" << endl;
        cout << setw(80) << "=========================================" << endl;
        cout << setw(41) << "| " << "Original Fee:" << discount->Fees << " Rs " << setw(18) << "|" << endl;
        cout << setw(41) << "| " << "Discount n (" + to_string(discount->Scholarship) + "%):" << static_cast<int>(discountA) << " Rs " << setw(9) << "|" << endl;
        cout << setw(41) << "| " << "Payable Fee After Discount:" << finalFee/8 << " Rs" << setw(4) << "|" << endl;
        cout << setw(80) << "=========================================" << endl;
        //cout << "-----------------------------" << endl;
        system("pause");
    }

    void give_feedback() 
    {
        string msg;
        cout << "Enter your feedback: ";
        getline(cin, msg);
        enqueue(msg);
        cout << "Feedback submitted successfully!" << endl << endl;
        system("pause");
    }
};
class Menu : public Student
{
public:
    void adminMenu()
    {
        string options[] = {"Add Student", "Delete Student", "Update Student","Promote Student", "View All", "View Feedback", "Add Announcement", "Exit"};
        while (true)
        {
            int choice = displayMenu(options, 8);
            system("cls");
            switch (choice)
            {
            case 1:
                Add_std_detail();
                cin.ignore(100, '\n');
                break;
            case 2:
                delete_student();
                cin.ignore(100, '\n');
                break;
            case 3:
                update();
                break;
            case 4:
                promotes_sem(root);
                cout << " All Students Promoted..." << endl;
                system("pause");
                break;
            case 5:
                view_all();
                break;
            case 6:
                view_feedback();
                break;
            case 7:
                Announcements();
                break;
            case 8:
                return;
            }
        }
    }

    void studentMenu(string userID)
    {
        int rn = extract_id(userID);
        Node *node = search(root, rn);
        string options[] = {"View Profile", "My Courses", "Timetable", "Payment", "Announcements", "Feedback", "Exit"};
        while (true)
        {
            int choice = displayMenu(options, 7);
            switch (choice)
            {
            case 1:
                view(node);
                break;
            case 2:
                courses(node);
                break;
            case 3:
                time_table(node);
                break;
            case 4:
                payment(node);
                break;
            case 5:
                view_all_announcements();
                break;
            case 6:
                give_feedback();
                break;
            case 7:
                return;
            }
        }
    }
};
class UserManager : public Menu
{
protected:
    string admin_id = "admin@ads.com";
    string admin_pas = "12345";
    Admin admin;

public:
    void main_function()
    {
        bool isLoggedIn = false;
        string userID;
        int attempts = 0;

        while (!isLoggedIn) // on false it will continue
        {
            userID = check_id();
            if (!userID.empty()) // on not epmty it will enter this if
            {
                isLoggedIn = true;
            }
            else
            {
                system("cls");
                attempts++;
                cout << "Incorrect ID/Password" << setw(120) << setfill(' ') << "Attempt " << attempts << " of 3.\n";

                if (attempts >= 3)
                {
                    cout << "Too many incorrect attempts. Please wait for 30 seconds.\n";
                    for (int i = 30; i > 0; i--)
                    {
                        cout << "\rTime remaining: " << setw(2) << setfill('0') << i << " seconds";
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                    system("cls");
                    attempts = 0;
                }
                cout << setw(1) << setfill(' ');
            }
        }

        if (isAdmin(userID))
        {
            adminMenu();
        }
        else
        {
            studentMenu(userID);
        }
    }

    bool isAdmin(string id)
    {
        if (id == admin_id)
            return true;

        else
            return false;
    }

    void loadDataFromCSV()
    {
        ifstream file("data.csv");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string ID, pass, f_n, s_n, prgrm;
            int rn, cH, fee, sem;
            int scholarship;

            // Read values separated by commas
            getline(ss, line, ',');
            rn = stoi(line);

            getline(ss, ID, ',');
            getline(ss, pass, ',');
            getline(ss, f_n, ',');
            getline(ss, s_n, ',');
            getline(ss, line, ',');
            scholarship = stof(line);

            getline(ss, prgrm, ',');
            getline(ss, line, ',');
            cH = stoi(line);

            getline(ss, line, ',');
            sem = stoi(line);

            getline(ss, line, ',');
            fee = stoi(line);

            // Add student to the data structure
            add_node(rn, ID, pass, f_n, s_n, scholarship, prgrm, fee, cH, sem, root);
        }

        file.close();
    }

    void saveDataToCSV()
    {
        ofstream file("data.csv");
        saveDataToCSVHelper(root, file);
        file.close();
    }

    void saveDataToCSVHelper(Node *node, ofstream &file)
    {
        if (node == NULL)
            return;
        file << node->roll_no << "," << node->id << "," << node->password << "," << node->fthr_name << "," << node->std_name << "," << node->Scholarship << "," << node->Program << "," << node->Credit_h << "," << node->semester_no << "," << node->Fees << endl;
        saveDataToCSVHelper(node->left, file);
        saveDataToCSVHelper(node->right, file);
    }

    string check_password()
    {
        string password;
        char c;
        int p_len = 0;
        cout << "\t\t\t\t\tEnter your Password: ";
        while (true)
        {
            c = getch();
            if (c == '\r')
            {
                break;
            }
            if (c == '\b' && p_len > 0)
            {
                p_len--;
                password = password.substr(0, p_len);
                cout << "\b \b";
                continue;
            }
            password += c;
            p_len++;
            cout << '*';
        }

        cout << endl;
        return password;
    }
    string check_id()
    {
        string id;
        setTextColor((5 << 4) | 15);        
        cout << "\n\n.                                   WELCOME TO ACADEMIC DIRECTORY SYSTEM                                  ." << endl;
        setTextColor(7);
        cout << "\n\n\t\t\t\t\tEnter your ID: ";
        cin >> id;
        cin.ignore();
        if (id == admin_id)
        {
            if (check_password() == admin_pas)
                return id;
        }
        else
        {
            Node *temp = root;
            while (temp != NULL)
            {
                if (temp->id == id)
                {
                    if (check_password() == temp->password)
                    {
                        cout << "Login successful!" << endl;
                        return id;
                    }
                    cout << "Incorrect password" << endl;
                    return "";
                }
                temp = (id < temp->id) ? temp->left : temp->right;
            }
        }
        cout << "In-Correct ID" << endl;
        return "";
    }
};
int main()
{
    UserManager userManager;
    userManager.loadDataFromCSV();
    userManager.main_function();
    userManager.saveDataToCSV();
    return 0;
}
