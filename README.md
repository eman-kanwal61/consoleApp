```
# Console-Based Social Media Application

## Overview
This is a console-based social media application written in C++. It allows users to create accounts, add friends, share posts, like posts, comment on posts, and follow pages. The application manages user and page data using text files.

## Features
- **User Authentication:** Users can sign in and sign up.
- **Friend Management:** Users can add friends and track friend count.
- **Posting System:** Users can create, share, and like posts.
- **Commenting System:** Users can comment on posts.
- **Page Management:** Users can follow pages and view liked pages.
- **Search Functionality:** Users can search for posts, users, or pages.
- **Post Interaction:** Users can like, comment on, and share posts.

## File Structure
- `Source.cpp` - Contains the main logic and implementations.
- `Header.h` - Header file defining classes and functions.
- `user.txt` - Stores user information.
- `post.txt` - Stores posts and their details.
- `comments.txt` - Stores comments made on posts.
- `page.txt` - Stores pages and their details.
- `shared_post.txt` - Stores shared posts.
- `userfollowpages.txt` - Stores pages followed by users.

## Classes and Functionalities
### 1. `socialentity`
- Stores username and password.
- Allows searching for friends and pages.
- Handles user authentication.

### 2. `user`
- Manages user details, friends, and liked pages.
- Allows users to add friends.
- Enables signing in and saving user details.
- Handles liking and sharing posts.
- Manages friend post views.

### 3. `page`
- Manages pages created by users.
- Allows adding, liking, and viewing pages.
- Stores posts on pages.

### 4. `post`
- Stores and manages posts.
- Allows liking, commenting, and displaying posts.
- Handles post creation and interaction.

## How to Run the Program
1. Compile the source code using a C++ compiler (e.g., `g++ Source.cpp -o social_app`).
2. Run the executable (`./social_app` on Linux/macOS or `social_app.exe` on Windows).
3. Follow the on-screen instructions to sign in, add friends, create posts, and interact with posts and pages.

## Future Enhancements
- Implement a graphical user interface (GUI).
- Improve file handling and use a database for better performance.
- Enhance security by hashing passwords.
- Add real-time notifications and messaging features.

## Author
Developed by [Your Name]

## License
This project is licensed under the MIT License.
```

