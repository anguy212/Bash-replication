#ifndef CS100_ASSIGNMENT_2_ALICE_AND_JESUS_COMMANDCLASS_H
#define CS100_ASSIGNMENT_2_ALICE_AND_JESUS_COMMANDCLASS_H

#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

class CommandComponent
{
public:
    CommandComponent() {}
    virtual bool execute() = 0;
    virtual ~CommandComponent(){}
    virtual bool ifEmptyTree() {return false;}
    virtual void addLeftComponent(CommandComponent *command) = 0;
    virtual void addRightComponent(CommandComponent *command) = 0;
    virtual string getString() = 0;
};

class Command: public CommandComponent {
private:
    string dudeExecuteThis;
public:
    Command() { dudeExecuteThis = ""; }
    
    Command(string commandtoExecute) { dudeExecuteThis = commandtoExecute; }
    
    ~Command(){};
    
    bool execute() {
        bool returnValue = true;
        char *cstr = new char[dudeExecuteThis.length() + 1];
        strcpy(cstr, dudeExecuteThis.c_str());
        char *p = strtok(cstr, " ");
        char *arg[30];
        int holder = 0;
        while (p != 0) {
            arg[holder] = p;
            p = strtok(NULL, " ");
            holder++;
        }
        char *lastElement = 0;
        arg[holder] = lastElement;
        pid_t pID = fork();
        if (pID == 0) {
            if(execvp(arg[0], arg) == -1)
            {
                perror("exec");
            }
            exit(errno);
        } else {
            int status;
            waitpid(-1, &status, 0);
            delete[] cstr;
//            cout << "parent pid: " << pID << endl;
            if (status != 0) {
                returnValue = false;
            }
            return returnValue;
        }
    }
//        bool returnValue = true;
//        pid_t pID = fork();
//        if (pID == 0) {
//            char *cstr = new char[dudeExecuteThis.length() + 1];
//            strcpy(cstr, dudeExecuteThis.c_str());
//            char *p = strtok(cstr, " ");
//            char *arg[30];
//            int holder = 0;
//            while (p != 0) {
//                arg[holder] = p;
//                p = strtok(NULL, " ");
//                holder++;
//                }
//            char *lastElement = 0;
//            arg[holder] = lastElement;
//            delete[] cstr;
//            if(execvp(arg[0], arg) == -1)
//            {
//                perror("exec");
//    
//                returnValue = false;
//                cout << "return value: " << returnValue << endl;
//                exit(1);
//                return returnValue;
//            }
//            exit(1);
//        }
//        else{
//            wait(0);
//            cout << "return value: " << returnValue << endl;
//            cout << "parent" << endl;
//        }
//        cout << "return value: " << returnValue << endl;
//                return returnValue;
//    }
    bool check()
    {
        return true;
    }
    
    bool ifEmptyTree() {return false;}
    
    void addLeftComponent(CommandComponent *command){}
    void addRightComponent(CommandComponent *command){}
    void addComponent(CommandComponent *command){}
    
    void clearString() {
        dudeExecuteThis = "";
    }
    void appendString(string str)
    {
        dudeExecuteThis.append(" ");
        dudeExecuteThis.append(str);
    }
    string getString()
    {
        return dudeExecuteThis;
    }
    
};

class SemiColon: public CommandComponent
{
private:
    CommandComponent* alwaysExecuteThis1;
    CommandComponent* alwaysExecuteThis2;
public:
    SemiColon() {alwaysExecuteThis1 = 0; alwaysExecuteThis2 = 0;}
    SemiColon(CommandComponent* executeThis, CommandComponent *executeThis2) {alwaysExecuteThis1 = executeThis; alwaysExecuteThis2 = executeThis2;}
    ~SemiColon() {delete alwaysExecuteThis1; delete alwaysExecuteThis2;}
    bool execute()
    {
        bool holder;
        holder = alwaysExecuteThis1->execute();
        return alwaysExecuteThis2->execute();
    }
    bool ifEmptyTree()
    {
        if(alwaysExecuteThis2 == 0 && alwaysExecuteThis1 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command){alwaysExecuteThis1 = command;}
    void addRightComponent(CommandComponent *command){alwaysExecuteThis2 = command;}

};

class andConnector: public CommandComponent
{
private:
    CommandComponent* leftBranch;
    CommandComponent* rightBranch;
public:
    andConnector() {leftBranch = 0; rightBranch = 0;}
    andConnector(CommandComponent* left, CommandComponent* right)
    {
        leftBranch = left;
        rightBranch = right;
    }
    ~andConnector() {delete leftBranch; delete rightBranch;}
    bool execute()
    {
        //check logic behind this
        if(leftBranch->execute() == true)
        {
            return rightBranch->execute();
        }
        else
        {
            return false;
        }
    }
    
    bool ifEmptyTree()
    {
        if(leftBranch == 0 && rightBranch == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command) { leftBranch = command; }
    void addRightComponent(CommandComponent *command) { rightBranch = command; }
    
};

class orConnector: public CommandComponent
{
private:
    CommandComponent* leftBranch;
    CommandComponent* rightBranch;
public:
    orConnector(){leftBranch = 0; rightBranch = 0;}
    orConnector(CommandComponent* left, CommandComponent* right)
    {
        leftBranch = left;
        rightBranch = right;
    }
    ~orConnector()
    {
        delete leftBranch;
        delete rightBranch;
    }
    bool execute()
    {
        //check logic behind this
        if(leftBranch->execute() == false)
        {
            return rightBranch->execute();
        }
        else
        {
            //return rightBranch->checker();
            return true;
        }
    }
    
    bool ifEmptyTree()
    {
        if(leftBranch == 0 && rightBranch == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    string getString(){return "";}
    void addLeftComponent(CommandComponent *command) {leftBranch = command; }
    void addRightComponent(CommandComponent *command) { rightBranch = command;}
};

class filePath: public CommandComponent
{
private:
    const char *pathInput;
public:
    filePath()
    {
        pathInput = 0;
    }
    filePath(string path)
    {
        pathInput = path.c_str();
    }

    bool execute()
    {
        struct stat sb;

        if(stat(pathInput, &sb) == 0)
        {
            if(sb.st_mode & S_IFREG)
                cout << "This is a valid file!" << endl;
            else
            cout << "This is a valid directory!" << endl;
            return true;
        }
        else
            cout << "The following path is not valid!" << endl;
            return false;
    }

    bool ifEmptyTree()
    {
        return false;
    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command){}
    void addRightComponent(CommandComponent *command){}


};

class Input_ReDirect: public CommandComponent
{

private:
    CommandComponent *left_side, *right_side;
public:

    Input_ReDirect(){left_side = 0; right_side = 0;}

    bool execute()
    {
        int fid = dup(0);

        int file = open(right_side->getString().c_str(), O_RDONLY);

        if(file == -1)
        {
            perror("Error opening the file!");
            return false;
        }


        close(0);
        dup2(file, 0);

        bool result = left_side->execute();

        close(0);
        dup2(fid, 0);

        return result;

    }

    ~Input_ReDirect(){}
    bool ifEmptyTree()
    {
        if(left_side == 0 && right_side == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command){left_side = command;}
    void addRightComponent(CommandComponent *command){right_side = command;}
   
};

class Output_ReDirect: public CommandComponent
{
private:
    CommandComponent *left_side, *right_side;
//    char *redirect_input;
public:


    Output_ReDirect(){ left_side = 0; right_side = 0;}

    bool execute()
    {
        int fid  = dup(1);
        int file = open(right_side->getString().c_str() , O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

        if(file == -1)
        {
            perror("Could not open file!");
            return false;
        }

        close(1);
        dup2(file, 1);

        bool result = left_side->execute();


        close(1);
        dup2(fid, 1);


        return result;

    }
    ~Output_ReDirect(){}
    bool ifEmptyTree()
    {
        if(left_side == 0 && right_side == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command) { left_side = command; }
    void addRightComponent(CommandComponent *command) { right_side = command; }
};


class Append_ReDirect: public CommandComponent
{

private:
    CommandComponent *left_side, *right_side;

public:


    Append_ReDirect(){left_side = 0; right_side = 0;}
    bool execute()
    {

        int fid  = dup(1);
        int file = open(right_side->getString().c_str() ,O_CREAT|O_APPEND|O_RDWR, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

        if(file == -1)
        {
            perror("Could not open file!");
            return false;
        }

        close(1);
        dup2(file, 1);

        bool result = left_side->execute();


        close(1);
        dup2(fid, 1);


        return result;

    }
    ~Append_ReDirect(){}
    bool ifEmptyTree()
    {
        if(left_side == 0 && right_side == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command){left_side = command;}
    void addRightComponent(CommandComponent *command){right_side = command;}

};

class pipeConnector: public CommandComponent
{
private:
    CommandComponent* leftBranch;
    CommandComponent* rightBranch;
public:
    pipeConnector()
    {
        leftBranch = 0;
        rightBranch = 0;
    }
    
    bool execute()
    {
        //        cout << "executing pipe " << endl;
        pid_t pid;
        int fd[2];
        bool returnValue = true;
        
        pipe(fd);
        pid = fork();
        
        if(pid==0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            returnValue = leftBranch->execute();
            exit(0);
        }
        else
        {
            pid=fork();
            
            if(pid==0)
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[1]);
                close(fd[0]);
                returnValue = rightBranch->execute();
                exit(0);
            }
            else
            {
                int status;
                close(fd[1]);
                close(fd[0]);
                waitpid(pid, &status, 0);
                //debug
//                cout << "this is pid of parent: " << pid << endl;
                return returnValue;
            }
        }
    }
    bool ifEmptyTree()
    {
        if(leftBranch == 0 && rightBranch == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    string getString(){return "";}
    void addLeftComponent(CommandComponent *command){leftBranch = command;}
    void addRightComponent(CommandComponent *command){rightBranch = command;}
};


#endif //CS100_ASSIGNMENT_2_ALICE_AND_JESUS_COMMANDCLASS_H
