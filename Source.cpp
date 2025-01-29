#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<sstream>
#include"Header.h"
#include<ctime>
#include<chrono>
using namespace std;

socialentity::socialentity(string u, string p) : username(u), password(p) {}

string socialentity::getid() const {
    return id;
}

void socialentity::setid(string id){
    this->id = id;
}

string socialentity::getusername()const {
    return username;
}

void socialentity::setusername(string user) {
    username = user;
}

string socialentity::getpassword() {
    return password;
}

void socialentity::setpassword(string pass) {
    password = pass;
}

string trim(const string& str) {
    int first = str.find_first_not_of(' ');
    if (first == -1)
        return "";
    int last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool socialentity::searchforfriend(string userid) {
    ifstream fin("user.txt");
    if (!fin) {
        cout << "Unable to open the file." << endl;
        return false;
    }
    string line;
    while (getline(fin, line)) {
        if (line.find("Username: ") != -1) {
            string username = line.substr(10);  // Length of "Username: "
            if (username == userid) {
                fin.close();
                return true;
            }
        }
    }

    fin.close();
    return false;
}

user::user() : friends(nullptr), maxfriends(0), maxpagesliked(0), pagesliked(nullptr) {}

user::user(int max, int n, string* friendList, string* pagesliked) : maxfriends(max), maxpagesliked(n) {
    friends = new string[max];
    for (int i = 0; i < max; ++i) {
        friends[i] = friendList[i];
    }
    this->pagesliked = new string[n];
    for (int i = 0; i < n; ++i) {
        this->pagesliked[i] = pagesliked[i];
    }
    this->friendcount = 0;
}

user::~user() {
    delete[] friends;
    delete[] pagesliked;
}


int user::getmaxfriends() {
    return maxfriends;
}

void user::setmaxpages(int max) {
    maxpagesliked = max;
}

int user::getmaxpages() {
    return maxpagesliked;
}

void user::input() {
    string username, password;
    cout << "Enter your username\n";
    getline(cin, username);
    cout << "Enter your password\n";
    getline(cin, password);
    this->setusername(username);
    this->setpassword(password);
}

void user::savetofile() {
    ofstream fout("user.txt", ios::app);
    if (fout) {
        fout << "Username: " << getusername() << endl;
        fout << "Password: " << getpassword() << endl;
        fout << "--------------------------------" << endl;
        cout << "User data saved to file\n";
        fout.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

bool user::signin() {
    ifstream fin("user.txt");
    string username, password;
    cout << "Enter username: ";
    getline(cin.ignore(), username);
    this->setusername(username);
    cout << "Enter password: ";
    getline(cin, password);
    // cout<<"wef"<<getusername();
    string line;
    int pos;
    bool isuername = false, ispassword = false;
    if (fin.is_open()) {
        while (getline(fin, line)) {
            pos = line.find(":");//deltmeter
            if (pos != -1) {
                string key = line.substr(0, pos);
                string temp = line.substr(pos + 1);
                int start = 0;
                while (start < key.length() && (key[start] == ' ' || key[start] == '\t' || key[start] == '\n')) {
                    ++start;
                }
                key = key.substr(start);
                int end = key.length() - 1;
                while (end >= 0 && (key[end] == ' ' || key[end] == '\t' || key[end] == '\n')) {
                    --end;
                }
                key = key.substr(0, end + 1);
                start = 0;
                while (start < temp.length() && (temp[start] == ' ' || temp[start] == '\t' || temp[start] == '\n')) {
                    ++start;
                }
                temp = temp.substr(start);
                end = temp.length() - 1;
                while (end >= 0 && (temp[end] == ' ' || temp[end] == '\t' || temp[end] == '\n')) {
                    --end;
                }
                temp = temp.substr(0, end + 1);
                if (key == "Username" && temp == username) {
                    isuername = true;
                }
                else if (key == "Password" && temp == password) {
                    ispassword = true;
                }
            }
        }
        fin.close();
        if (isuername && ispassword) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        cout << "Can not open file." << endl;
    }
    return false;
}

int user::likedpages = 0;
int user::friendcount = 0;

void user::incrementfriendcount() {
    ++friendcount;
}
void user::setfreindcount(int count) {
    friendcount = getfreindcount();
    this->friendcount = count;
}
int user::getfreindcount() {
    ifstream fin("user.txt");
    int count = 1;
    string line;
    if (fin) {
        while (getline(fin, line)) 
        {
            if (line.find("Freind Count ") != -1) 
            {
                count++;
            }
        }
    }
    fin.close();
    return count;
}

int user::getfreindcountfromfile()
{
    ifstream fin("user.txt");
    string line;
    int c = 0;
    if (fin) 
    {
        while (getline(fin, line))
        {
            if (line.find("Freind Count ") != -1)
            {
                line.substr(12);
                // line=line.substr(0, 14);
                c++;
                //cout << line << endl;
            }
        }
        return c;
        //cout << "total friend count from file " << c << endl;
    }
    else 
    {
        cout << "can not open file\n";
    }
}

void user::addfriend(string username, string friendusername)
{
    if (searchforfriend(friendusername))
    {
        ofstream fout("user.txt", ios::app);
        ifstream fin("user.txt");  // Open the file for reading
        if (fout && fin) {
            if (getfreindcountfromfile() < 10)
            {
                fout << "Freind Count " << getfreindcount() << endl;
                fout << "Friend of " << getusername() << ": " << friendusername << endl;
                fout << "--------------------------------" << endl;

                // Add the reverse friendship
                string line;
                while (getline(fin, line)) {
                    if (line.find("Username: " + friendusername) != -1)
                    {
                        fout << "Friend of " << friendusername << ": " << getusername() << endl;
                        fout << "--------------------------------" << endl;
                    }
                }

                cout << "Friend added successfully." << endl;
                fout.close();
                fin.close();
            }
            else {
                cout << "Cannot add friend. The maximum limit is 10 friends.\n";
            }
        }
        else {
            cout << "Unable to open the file." << endl;
        }
    }
    else {
        cout << "User not found." << endl;
    }
}
void user::userlikedpages(string title) {
    socialentity s;
    ifstream fin("userlikedpages.txt");
    int likedpages = 1;
    string line;
    while (getline(fin, line)) {
        if (line.find("Post ") != -1) {
            ++likedpages;
        }
    }
    fin.close();
    string n;
    if (s.searchforpage(title)) {
        cout << "page found ";
        cout << "Press 1 for following this page and any other number for not following\n";
        getline(cin, n);
        if (n == "1") {
            ofstream fout;
            fout.open("userfollowpages.txt", ios::app);
            if (fout.is_open()) {
                fout << "Post " << likedpages << endl;
                /* fout << "Text of Pages"*/
                fout << "Total liked pages " << likedpages << endl;
                fout << "Title of page " << title << endl;
                fout << "-------------------------\n";
            }
            else {
                cout << "File not found\n";
            }
        }
        else {
            return;
        }

    }
    else {
        cout << "not found";
    }
}

void user::sharepost() {
    page p;
    user u;
    cout << "Post from last 24 hours\n";
    p.displaypost();
    cout << "Enter the post number you want to share (0 to cancel): ";
    int postNumber;
    cin >> postNumber;
    if (postNumber > 0) {
        ifstream fin("post.txt");
        if (!fin.is_open()) {
            cout << "Can not open file." << endl;
            return;
        }
        int currentPost = 0;
        bool postFound = false;
        string line;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                currentPost++;
                if (currentPost == postNumber) {
                    string postText = "";
                    // Extract the post text and implement the sharing logic
                    // For simplicity, let's print the post text and save it to a file
                    while (getline(fin, line) && !line.empty()) {
                        if (line.find("Text") != -1) {
                            postText = line.substr(line.find(' ') + 1);
                            postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                            break; // Assuming Text is the last detail in the post
                        }
                    }
                    if (!postText.empty()) {
                        cout << "Post shared successfully:\n" << postText << endl;

                        // Save the shared post to the file
                        ofstream fout("shared_post.txt", ios::app);
                        if (fout.is_open()) {
                            fout << "Shared by: " << u.getusername() << endl;
                            fout << "Text: " << postText << endl;
                            fout << "--------------------------------" << endl;
                            fout.close();
                            //cout << "Post saved to shared_post.txt." << endl;
                            return;
                        }
                        else {
                            cout << "Error saving to shared_post.txt." << endl;
                        }
                    }
                    else {
                        cout << "Unable to extract post details." << endl;
                    }

                    postFound = true;
                    break;
                }
            }
        }

        if (!postFound) {
            cout << "Invalid post number." << endl;
        }

        fin.close();
    }
    else {
        cout << "Operation canceled by the user." << endl;
    }
}


void user::likepost() {
    page p;
    p.displaypost();

    // Prompt the user to select a post to like
    cout << "Enter the post number you want to like (0 to cancel): ";
    int postNumber;
    cin >> postNumber;

    if (postNumber > 0) {
        // Find the selected post and like it
        ifstream fin("post.txt");
        if (fin.is_open()) {
            int currentPost = 0;
            bool postFound = false;
            string line;
            string likedText;  // To store liked post text
            while (getline(fin, line)) {
                if (line.find("Post") != -1) {
                    currentPost++;
                    if (currentPost == postNumber) {
                        // Assuming the post class has a likePost function
                        post postToLike;
                        likedText = postToLike.likePost(getusername());
                        postFound = true;
                        break;
                    }
                }
            }

            fin.close();

            if (!postFound) {
                cout << "Invalid post number." << endl;
            }
            else {
                // Save the liked post details to shared_post.txt
                ofstream fout("shared_post.txt", ios::trunc);  // Use ios::trunc to truncate the file
                if (fout.is_open()) {
                    fout << "Shared by: " << getusername() << endl;
                    fout << "Text: " << likedText << endl;
                    fout << "Liked By:" << getusername() << endl;  // Assuming you want to show who liked the post
                    fout << "--------------------------------" << endl;
                    cout << "Post liked and saved to shared_post.txt." << endl;
                    fout.close();
                }
                else {
                    cout << "Error saving to shared_post.txt." << endl;
                }
            }
        }
        else {
            cout << "Can not open file." << endl;
        }
    }
    else {
        cout << "Operation canceled by the user." << endl;
    }
}


void user::addPost(const std::string& post) {
    posts.push_back(post);
}


void user::viewfreindspost()const {
    ifstream fin("user.txt");
    if (!fin) {
        cout << "Unable to open the file." << endl;
        return;
    }
    string line;
    bool isFriend = false;
    while (getline(fin, line)) {
        if (line.find("Username: ") != -1) {
            string username = line.substr(10);
            if (username == this->getusername()) {
                isFriend = true;
            }
            else {
                isFriend = false;
            }
        }
        else if (isFriend && line.find("Friend of ") != -1) {
            string friendUsername = line.substr(line.find(": ") + 2);
            cout << "Posts by " << friendUsername << ":" << endl;
            for (const string& post : posts) {
                // Assuming the post format is "<timestamp>: <content>"
                string timestamp = post.substr(0, post.find(":"));
                string content = post.substr(post.find(":") + 2);
                time_t postTime = stoi(timestamp);//stoi string into integer

                // Get the current time
                time_t currentTime = time(nullptr);

                // Calculate the time difference in seconds
                double diffSeconds = difftime(currentTime, postTime);

                // Check if the post was made within the last 24 hours (86400 seconds)
                if (diffSeconds <= 86400) {
                    cout << "- " << content << endl;
                }
            }
            cout << endl;
        }
    }

    fin.close();
}

string post::likePost(const string& user) {

    if (likes < MAX_LIKES) {
        // Check if the user has already liked the post
        if (find(likedby, likedby + likes, user) == likedby + likes) {
            likedby[likes++] = user;
            cout << "Post liked successfully." << endl;
        }
        else {
            cout << "You have already liked this post." << endl;
        }
    }
    else {
        cout << "Like limit reached for this post." << endl;
    }
    ifstream fin("post.txt");
    string line;
    string postText = "";
    if (fin) {
        // Extract the post text and implement the sharing logic
        // For simplicity, let's print the post text and save it to a file
        while (getline(fin, line) && !line.empty()) {
            if (line.find("Text") != -1) {
                postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                break; // Assuming Text is the last detail in the post
            }
        }
    }
    // Replace this return statement with the actual post text or data
    return postText;
}

bool socialentity::searchforpage(string t) {
    ifstream fin("page.txt");
    string line, title;
    bool found = false;
    if (fin) {
        while (getline(fin, line)) {
            if (line.compare(0, 7, "Title: ") == 0) {
                title = line.substr(7);
                int start = title.find_first_not_of(" \t\n");
                if (start != -1) {
                    title = title.substr(start);
                    int end = title.find_last_not_of(" \t\n");
                    if (end != -1) {
                        title = title.substr(0, end + 1);
                        if (title == t) {
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Error opening the file." << endl;
    }
    return found;
}

page::page() : id(0) {
    id = getPageCount();
}
page::page(int i, string t) : id(i), title(t) {}

void page::settitle(string t) {
    this->title = t;
}

string page::gettitle() {
    return title;
}

void page::setid(int t) {
    this->id = t;
}

int page::pagecount = 0;
int page::getid() {
    return id;
}

int page::getPostCount() {
    ifstream fin("post.txt");
    int count = 1;
    string line;
    if (fin) {
        while (getline(fin, line)) {
            if (line.find("Post ") != -1) {
                count++;
            }
        }
    }
    fin.close();
    return count;
}

int page::getPageCount() {
    ifstream fin("page.txt", ios::app);
    int count = 1;
    string line;
    if (fin) {
        while (getline(fin, line)) {
            if (line.find("Id ") != -1) {
                count++;
            }
        }
    }
    fin.close();
    fin.open("post.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            if (line.find("Post ") != -1) {
                count++;
            }
        }
    }
    return count;
}

void page::savetopagefile() {
    ofstream fout("page.txt");
    if (fout) {
        fout << "ID " << this->getid() << endl;
        fout << "Page title " << this->gettitle() << endl;
        fout << "------------------\n";
    }
    else {
        cout << "Can not open file\n";
    }
}

void page::incrementPageCount() {
    ++pagecount;
}

void page::addpost() {
    string title, text;
    cout << "Enter title for your page\n";
    getline(cin.ignore(), title);
    this->settitle(title);
    id = getPageCount();
    incrementPageCount();
    this->setid(id);
}

void page::savetopostfile(const user& u) {
    socialentity s;
    //  user u;
    //cout << "e" << u.getusername();
    ofstream fout("post.txt", ios::app);
    if (fout.is_open()) {
        string input, feeling, text;
        cout << "You can select from this table\n";
        cout << "Type\t\t\tValue\n";
        cout << "1\tfeeling\t\tHappy/Sad/Excited etc\n";
        cout << "2\tthinking about\tlife/future/meaning of life etc.\n";
        cout << "3\tMaking\t\tMoney/art/memories etc.\n";
        cout << "4\tcelebrating \tA birthday/Halloween/success etc.\n";
        cout << "Now enter your choice\n";
        cin >> input;

        if (input == "1" || input == "2" || input == "3" || input == "4") {
            cout << "What are you feeling?\n";
            cin.ignore(); // Ignore the newline character left in the buffer
            getline(cin, feeling);

            auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
            tm localTime;
            localtime_s(&localTime, &currentTime);
            int year = localTime.tm_year + 1900;
            int month = localTime.tm_mon + 1;
            int day = localTime.tm_mday;
            string currentDate = to_string(year) + "-" + to_string(month) + "-" + to_string(day);

            cout << "Enter your text\n";
            getline(cin, text);

            fout << "Post " << this->getid() << endl;
            fout << "Date " << currentDate << endl;
            fout << "Text " << text << endl;
            fout << "Feeling " << feeling << endl;
            fout << "Shared by " << u.getusername() << endl;
            fout << "Liked by " << u.getusername() << endl;
            fout << "------------------------------\n";
            fout.close();
        }
        else {
            cout << "Invalid choice\n";
        }
    }
    else {
        cout << "Unable to open file.\n";
    }
}


void page::likedpages() {
    ifstream fin("page.txt");
    string line;
    int i = 0;
    if (fin) {
        while (getline(fin, line)) {
            if (line.find("Title ") != -1) {
                string title = line.substr(6);
                cout << "Pages available " << ++i << " " << title << endl;
            }
        }
    }
    /* ofstream fout("likedpages.txt");
     if (fout) {

     }*/
}

void page::displaypost() {
    ifstream fin("post.txt");
    if (fin) {
        time_t now = time(0);
        tm current_time;
        localtime_s(&current_time, &now);
        int current_day = current_time.tm_mday;
        int current_month = current_time.tm_mon + 1;
        int current_year = current_time.tm_year + 1900;
        int current_hour = current_time.tm_hour;
        string line;
        string postDate;
        bool within24Hours = false;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                within24Hours = false;
                postDate = "";
            }
            else if (line.find("Date") != -1) {
                postDate = line.substr(line.find(' ') + 1);
                postDate.erase(postDate.find_last_not_of(" \n\r\t") + 1);
            }
            else if (line.find("Text") != -1) {
                string postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                if (!postDate.empty()) {
                    stringstream ss(postDate);
                    int post_day, post_month, post_year;

                    ss >> post_year;
                    ss.ignore();
                    ss >> post_month;
                    ss.ignore();
                    ss >> post_day;

                    if (current_year == post_year && current_month == post_month && current_day == post_day) {
                        within24Hours = true;
                    }
                    else if (current_year == post_year && current_month == post_month && current_day - 1 == post_day && current_hour <= 24) {
                        within24Hours = true;
                    }
                }

                if (within24Hours) {
                    cout << "Post: " << postText << endl;
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

void page::showlikedusers(int id) {
    ifstream fin("post.txt");
    if (!fin.is_open()) {
        cout << "Unable to open file." << endl;
        return;

    }
    string line;
    bool foundPost = false;
    while (getline(fin, line)) {
        if (line.find("Post " + to_string(id)) != -1) {//to_string integer id to string 
            foundPost = true;
            getline(fin, line); // Skip Date line
            getline(fin, line); // Skip Text line
            getline(fin, line); // Skip Feeling line
            getline(fin, line); // Skip Shared by line
            getline(fin, line); // Get Liked by line

            // Extract and display the list of users who liked the post
            string likedByUsers = line.substr(line.find(' ') + 1);

            // Replace commas with newline characters
            for (char& c : likedByUsers) {
                if (c == ',') {
                    c = '\n';
                }
            }

            cout << likedByUsers;

            break; // No need to search further
        }
    }

    fin.close();

    if (!foundPost) {
        cout << "Post with ID " << id << " not found." << endl;
    }
}


int post::countcomments(const string& postID) {
    ifstream commentFile("comments.txt");
    if (!commentFile.is_open()) {
        cout << "Unable to open comment file.\n";
        return 0;
    }
    int commentCount = 0;
    string line;
    while (getline(commentFile, line)) {
        stringstream ss(line);//pick the whole line
        string count, post, username, comment;

        ss >> count >> post >> username;
        getline(ss, comment);

        if (trim(post) == trim("post" + postID)) {//trim function cut the line till post + id
            commentCount++;
        }
    }
    commentFile.close();
    return commentCount;
}
void page::addComment(string postID, const string& commenter, const string& commentText) {
    post p;
    int numComments = p.countcomments(postID);
    if (numComments < MAX_COMMENTS) {
        comments[numComments++] = comment(commentText, commenter);
        // Save the updated comments to the comments file
        ofstream fout("comments.txt", ios::app);
        if (fout.is_open()) {
            fout << "count:" << numComments << "\t post" << postID << "\t" << "userame: " << commenter << "\t" << "comment: " << commentText << endl;
            fout.close();
        }
        else {
            cout << "Unable to open comments file." << endl;
        }
    }
    else {
        cout << "Maximum number of comments reached." << endl;
    }
}


void page::viewpost(const string& postID) {
    // Display the post details
    string line;
    ifstream postFile("post.txt");
    if (!postFile.is_open()) {
        cout << "Unable to open post file.\n";
        return;
    }

    bool postFound = false;

    while (getline(postFile, line)) {
        if (line.find("Post " + postID) != -1) {
            // Found the post, display the details
            cout << "Post ID: " << postID << endl;

            // Read the Date line
            getline(postFile, line);
            cout << "Date: " << line.substr(5) << endl;

            // Read the Text line
            getline(postFile, line);
            cout << "Text: " << line.substr(5) << endl;

            // Read the Feeling line
            getline(postFile, line);
            cout << "Feeling: " << line.substr(8) << endl;

            // Read the Shared by line
            getline(postFile, line);
           // cout << "Shared by: " << line.substr(11) << endl;

            // Read the Liked by line
            getline(postFile, line);
            cout << "Liked by: " << line.substr(9) << endl;

            postFound = true;
            break; // No need to continue searching
        }
    }
    postFile.close();

    if (!postFound) {
        cout << "Post not found.\n";
        return;
    }
    ifstream commentFile("comments.txt");
    if (!commentFile.is_open()) {
        cout << "Unable to open comment file.\n";
        return;
    }
    int commentCount = 0;
    while (getline(commentFile, line)) {
        stringstream ss(line);
        string count, post, username, comment;

        ss >> count >> post >> username;
        getline(ss, comment);

        if (trim(post) == trim("post" + postID)) {
            commentCount++;
            cout << "Comment " << commentCount << " by : " << comment << endl;
        }
    }
    commentFile.close();
    if (commentCount == 0) {
        cout << "No comments found for Post " << postID << endl;
    }
}

void socialentity::menuforeverything() {
    user u;
    page p;
    comment obj;
    string choice, comment, post;
    int opt;
    bool login = true;

    system("color 5f");

    while (true) {
        cout << "\t\t\t(-------Welcome to console-based social application-------)\n";
        cout << "1. Press 1 If you are a User:" << endl;
        cout << "2. Press 2 If you are a page owner: " << endl;
        cout << "3. Press 3 if you want to search anything: " << endl;
        cout << "4. Press 4 for exiting\n";
        cin >> opt;

        switch (opt) {
        case 1: {
            while (true) {
                cout << "Press 1 for sign in\nPress 2 for adding friends\nPress 3 for viewing a post\nPress 0 to exit\n";
                cin >> opt;

                if (opt == 1) {
                    if (u.signin()) {
                        do {
                            cout << "Welcome\n";
                            p.displaypost();
                            u.sharepost();
                            u.viewfreindspost();
                            u.likepost();
                            cout << "Enter on which post to add comment\n";
                            cin >> choice;
                            cout << "Enter what to comment\n";
                            getline(cin >> ws, comment);
                            p.addComment(choice, getusername(), comment);
                            cout << "Do you want to logout? Press 1 for yes and any other number for not logging out\n";
                            cin >> opt;

                            if (opt == 1) {
                                login = false;
                            }
                        } while (login);
                    }
                    else {
                        cout << "ID not found, please sign up\n";
                        u.input();
                        u.savetofile();
                    }
                }
                else if (opt == 2) {
                    if (!u.signin()) {
                        cout << "Please sign in first.\n";
                        continue;  // Go back to the menu
                    }

                    string username;
                    cout << "Enter the username of the friend to be added: ";
                    getline(cin >> ws, username);
                    u.addfriend(getusername(), username);
                }
                else if (opt == 3) {
                    if (u.signin()) {
                        cout << "Enter post id to view page\n";
                        cin >> post;
                        p.viewpost(post);
                    }
                    else {
                        cout << "Invalid credentials\n";
                        cout << "Sign in first to view page\n";
                    }
                }
                else if (opt == 0) {
                    cout << "Thank you for using our console-based social application\n";
                    break;
                }
                else {
                    cout << "Invalid choice\n";
                }
            }
            break;
        }

        case 2: {
            while (true) {
                cout << "Press 1 for Adding a post\n2 for showing users who like the post\n0 for EXIT\n";
                cin >> opt;

                if (opt == 1) {
                    p.addpost();
                    p.savetopagefile();
                    p.savetopostfile(u);
                }
                else if (opt == 2) {
                    int id;
                    cout << "Enter ID of post to show who likes the post\n";
                    cin >> id;
                    p.showlikedusers(id);
                }
                else if (opt == 0) {
                    cout << "Exiting";
                    break;
                }
                else {
                    cout << "Invalid choice";
                }
            }
            break;
        }

        case 3: {
            p.search();
            break;
        }

        case 4: {
            cout << "Exiting\n";
            return;
        }

        default: {
            cout << "Invalid choice\n";
            break;
        }
        }
    }
}

string page::search() {
    cout << "Enter keyword to be found:\n";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    ifstream finUser("user.txt");
    ifstream finPost("post.txt");
    ifstream finPage("page.txt");

    string fileContent;
    string line;

    // Search in the user file
    while (getline(finUser, line)) {
        if (line.find(keyword) != string::npos) {
            fileContent += "User File: " + line + "\n";
        }
    }

    // Search in the post file
    while (getline(finPost, line)) {
        if (line.find(keyword) != string::npos) {
            fileContent += "Post File: " + line + "\n";
        }
    }

    // Search in the page file
    while (getline(finPage, line)) {
        if (line.find(keyword) != string::npos) {
            fileContent += "Page File: " + line + "\n";
        }
    }

    finUser.close();
    finPost.close();
    finPage.close();

    // Output the content if found
    if (!fileContent.empty()) {
        cout << "Found in the following files:\n";
        cout << fileContent;
    }
    else {
        cout << "Keyword not found in any file.\n";
    }

    return fileContent;
}

void post::display() {
    ifstream fin("post.txt");
    if (fin) {
        time_t now = time(0);
        tm current_time;
        localtime_s(&current_time, &now);
        int current_day = current_time.tm_mday;
        int current_month = current_time.tm_mon + 1;
        int current_year = current_time.tm_year + 1900;
        int current_hour = current_time.tm_hour;
        string line;
        string postDate;
        bool within24Hours = false;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                within24Hours = false;
                postDate = "";
            }
            else if (line.find("Date") != -1) {
                postDate = line.substr(line.find(' ') + 1);
                postDate.erase(postDate.find_last_not_of(" \n\r\t") + 1);
            }
            else if (line.find("Text") != -1) {
                string postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                if (!postDate.empty()) {
                    stringstream ss(postDate);
                    int post_day, post_month, post_year;

                    ss >> post_year;
                    ss.ignore();
                    ss >> post_month;
                    ss.ignore();
                    ss >> post_day;

                    if (current_year == post_year && current_month == post_month && current_day == post_day) {
                        within24Hours = true;
                    }
                    else if (current_year == post_year && current_month == post_month && current_day - 1 == post_day && current_hour <= 24) {
                        within24Hours = true;
                    }
                }

                if (within24Hours) {
                    cout << "Post: " << postText << endl;
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

string post::getType() {
    return "Generic Post";
}

void post::addComment(string postid, const string& commenter, const string& commentText) {
    post p;
    int numComments = p.countcomments(postid);
    if (numComments < MAX_COMMENTS) {
        comments[numComments++] = comment(commentText, commenter);
        // Save the updated comments to the comments file
        ofstream fout("comments.txt", ios::app);
        if (fout.is_open()) {
            fout << "count:" << numComments << "\t post" << postid << "\t" << "userame: " << commenter << "\t" << "comment: " << commentText << endl;
            fout.close();
        }
        else {
            cout << "Unable to open comments file." << endl;
        }
    }
    else {
        cout << "Maximum number of comments reached." << endl;
    }
}

void FeelingPost::display() {
    ifstream fin("post.txt");
    if (fin) {
        time_t now = time(0);
        tm current_time;
        localtime_s(&current_time, &now);
        int current_day = current_time.tm_mday;
        int current_month = current_time.tm_mon + 1;
        int current_year = current_time.tm_year + 1900;
        int current_hour = current_time.tm_hour;
        string line;
        string postDate;
        bool within24Hours = false;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                within24Hours = false;
                postDate = "";
            }
            else if (line.find("Date") != -1) {
                postDate = line.substr(line.find(' ') + 1);
                postDate.erase(postDate.find_last_not_of(" \n\r\t") + 1);
            }
            else if (line.find("Text") != -1) {
                string postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                if (!postDate.empty()) {
                    stringstream ss(postDate);
                    int post_day, post_month, post_year;

                    ss >> post_year;
                    ss.ignore();
                    ss >> post_month;
                    ss.ignore();
                    ss >> post_day;

                    if (current_year == post_year && current_month == post_month && current_day == post_day) {
                        within24Hours = true;
                    }
                    else if (current_year == post_year && current_month == post_month && current_day - 1 == post_day && current_hour <= 24) {
                        within24Hours = true;
                    }
                }

                if (within24Hours) {
                    cout << "Post: " << postText << endl;
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

string FeelingPost::getType() {
    return "feeling happy";
}

void FeelingPost::addComment(string postid,const string& commenter, const string& commentText) {
    post p;
    int numComments = p.countcomments(postid);
    if (numComments < MAX_COMMENTS) {
        comments[numComments++] = comment(commentText, commenter);
        // Save the updated comments to the comments file
        ofstream fout("comments.txt", ios::app);
        if (fout.is_open()) {
            fout << "count:" << numComments << "\t post" << postid << "\t" << "userame: " << commenter << "\t" << "comment: " << commentText << endl;
            fout.close();
        }
        else {
            cout << "Unable to open comments file." << endl;
        }
    }
    else {
        cout << "Maximum number of comments reached." << endl;
    }
}

void Makingpost::display() {
    ifstream fin("post.txt");
    if (fin) {
        time_t now = time(0);
        tm current_time;
        localtime_s(&current_time, &now);
        int current_day = current_time.tm_mday;
        int current_month = current_time.tm_mon + 1;
        int current_year = current_time.tm_year + 1900;
        int current_hour = current_time.tm_hour;
        string line;
        string postDate;
        bool within24Hours = false;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                within24Hours = false;
                postDate = "";
            }
            else if (line.find("Date") != -1) {
                postDate = line.substr(line.find(' ') + 1);
                postDate.erase(postDate.find_last_not_of(" \n\r\t") + 1);
            }
            else if (line.find("Text") != -1) {
                string postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                if (!postDate.empty()) {
                    stringstream ss(postDate);
                    int post_day, post_month, post_year;

                    ss >> post_year;
                    ss.ignore();
                    ss >> post_month;
                    ss.ignore();
                    ss >> post_day;

                    if (current_year == post_year && current_month == post_month && current_day == post_day) {
                        within24Hours = true;
                    }
                    else if (current_year == post_year && current_month == post_month && current_day - 1 == post_day && current_hour <= 24) {
                        within24Hours = true;
                    }
                }

                if (within24Hours) {
                    cout << "Post: " << postText << endl;
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

string Makingpost::getType() {
    return "making post";
 }

void Makingpost:: addComment(string postid, const string& commenter, const string& commentText) {
    post p;
    int numComments = p.countcomments(postid);
    if (numComments < MAX_COMMENTS) {
        comments[numComments++] = comment(commentText, commenter);
        // Save the updated comments to the comments file
        ofstream fout("comments.txt", ios::app);
        if (fout.is_open()) {
            fout << "count:" << numComments << "\t post" << postid << "\t" << "userame: " << commenter << "\t" << "comment: " << commentText << endl;
            fout.close();
        }
        else {
            cout << "Unable to open comments file." << endl;
        }
    }
    else {
        cout << "Maximum number of comments reached." << endl;
    }
}


void Celebrating::display() {
    ifstream fin("post.txt");
    if (fin) {
        time_t now = time(0);
        tm current_time;
        localtime_s(&current_time, &now);
        int current_day = current_time.tm_mday;
        int current_month = current_time.tm_mon + 1;
        int current_year = current_time.tm_year + 1900;
        int current_hour = current_time.tm_hour;
        string line;
        string postDate;
        bool within24Hours = false;
        while (getline(fin, line)) {
            if (line.find("Post") != -1) {
                within24Hours = false;
                postDate = "";
            }
            else if (line.find("Date") != -1) {
                postDate = line.substr(line.find(' ') + 1);
                postDate.erase(postDate.find_last_not_of(" \n\r\t") + 1);
            }
            else if (line.find("Text") != -1) {
                string postText = line.substr(line.find(' ') + 1);
                postText.erase(postText.find_last_not_of(" \n\r\t") + 1);
                if (!postDate.empty()) {
                    stringstream ss(postDate);
                    int post_day, post_month, post_year;

                    ss >> post_year;
                    ss.ignore();
                    ss >> post_month;
                    ss.ignore();
                    ss >> post_day;

                    if (current_year == post_year && current_month == post_month && current_day == post_day) {
                        within24Hours = true;
                    }
                    else if (current_year == post_year && current_month == post_month && current_day - 1 == post_day && current_hour <= 24) {
                        within24Hours = true;
                    }
                }

                if (within24Hours) {
                    cout << "Post: " << postText << endl;
                }
            }
        }
        fin.close();
    }
    else {
        cout << "Can not open file\n";
    }
}

string Celebrating::getType() {
    return "celebrating";
}

void Celebrating::addComment(string postid, const string& commenter, const string& commentText) {
    post p;
    int numComments = p.countcomments(postid);
    if (numComments < MAX_COMMENTS) {
        comments[numComments++] = comment(commentText, commenter);
        // Save the updated comments to the comments file
        ofstream fout("comments.txt", ios::app);
        if (fout.is_open()) {
            fout << "count:" << numComments << "\t post" << postid << "\t" << "userame: " << commenter << "\t" << "comment: " << commentText << endl;
            fout.close();
        }
        else {
            cout << "Unable to open comments file." << endl;
        }
    }
    else {
        cout << "Maximum number of comments reached." << endl;

    }
}
