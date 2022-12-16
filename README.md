# server | no project name yet

simple chatroom application i worked on for a week. 
credits:
winsock documentation
stackoverflow

monday
started with a project named "chatroom." was a headache to figure out the structure of the program, but i figured it out. started writing the server aspect, everything seemed to work well

tuesday 
added client program, had various issues. during my research, my code got messy and project lost its structure. in the end, i got the basic structure working, but it was in a very bare bones state, so i scrapped it and started over with the new concepts i had learned.

wednesday
worked on the readability of the program. figured out how to make everything seamless. added broadcasting, and now the program is very simple to use. I had a bug with strings being parsed by std::cin instead of std::getline. was stumped by the error all of wednesday.

thursday
gained some inspiration from my teacher to keep working on std::cin error. made a google search and luckily found it on the first stackoverflow answer. started working on a way to exit the chatroom, since currently leaving the chatroom will spam the other clients with empty messages.

friday
had a weird error with iostream's strcmp_s(). fixed it, and had another error with exit(0). turns out exit(0) does not work very well with multithreading. finished the exiting commands and added some debug information for the server side.
