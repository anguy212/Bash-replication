#include "commandClass.h"
//#include "parsing.h"
//#include "createContainers.h"
#include <vector>

using namespace std;

//takes in an empty vector of containers and trees to *****return one complete tree*****
void makeTrees(vector<CommandComponent*> &vectorOfCommands, CommandComponent* &tree)
{
    CommandComponent *previous_container = 0;
    
    for(int i = 0; i < vectorOfCommands.size(); i++)
    {
        if(vectorOfCommands.size() == 1)
        {
            previous_container = vectorOfCommands.at(0);
        }
        else if(vectorOfCommands.at(i)->ifEmptyTree() == true)
        {
            if(previous_container == 0)
            {
                vectorOfCommands.at(i)->addLeftComponent(vectorOfCommands.at(i - 1));
            }
            else
            {
                vectorOfCommands.at(i)->addLeftComponent(previous_container);
            }
            vectorOfCommands.at(i)->addRightComponent(vectorOfCommands.at(i + 1));
            previous_container = vectorOfCommands.at(i);
        }
    }
    tree = previous_container;

}
//takes in a vector of string commands sperated by spaces and return vector of empty containers and trees
void makeStringArrayToCommandArray(vector<string> &vectorString, vector<CommandComponent*> &vectorOfCommands)
{
    Command commandHolder;
    int counter = 0;
    for(int i = 0; i < (vectorString.size() - 1); i++)
    {
        if(vectorString.at(i) == "&&")
        {
            vectorOfCommands.push_back(new andConnector());
        }
        else if(vectorString.at(i) == "||")
        {
            vectorOfCommands.push_back(new orConnector());
        }
        else if(vectorString.at(i) == "|")
        {
            vectorOfCommands.push_back(new pipeConnector());
        }
        else if(vectorString.at(i) == "<")
        {
            vectorOfCommands.push_back(new Input_ReDirect());
        }
        else if(vectorString.at(i) == ">")
        {
            vectorOfCommands.push_back(new Output_ReDirect());
        }
        else if(vectorString.at(i) == ">>")
        {
            vectorOfCommands.push_back(new Append_ReDirect());
        }
        else if(vectorString.at(i) == "test")
        {
            bool hasSemi = false;
            if(vectorString.at(i+2).back() == ';')
            {
                vectorString.at(i+2).back() = 0;
                hasSemi = true;
            }
            vectorOfCommands.push_back(new filePath(vectorString.at(i+2)));
            if(hasSemi == true)
            {
                vectorOfCommands.push_back(new SemiColon());
            }
            i+= 2;
        }
        else if(vectorString.at(i) == "[")
        {
            bool hasSemi = false;
            if(vectorString.at(i+3).back() == ';')
            {
                hasSemi = true;
            }
            vectorOfCommands.push_back(new filePath(vectorString.at(i+2)));
            if(hasSemi == true)
            {
                vectorOfCommands.push_back(new SemiColon());
            }
            i+= 3;
        }
        else
        {

            if(vectorString.at(i).at(vectorString.at(i).length() -1) == ';')
            {
                vectorString.at(i).at(vectorString.at(i).length() -1) = ' ';
                commandHolder.appendString(vectorString.at(i));
                vectorOfCommands.push_back(new Command(commandHolder.getString()));
                commandHolder.clearString();
                vectorOfCommands.push_back(new SemiColon());
                }

            else
            {
               commandHolder.appendString(vectorString.at(i));
                if(vectorString.at(i+1) == "&&" || vectorString.at(i+1) == "||" || vectorString.at(i+1) == " " || vectorString.at(i+1) == "|" || vectorString.at(i+1) == ">" || vectorString.at(i+1) == ">>" || vectorString.at(i+1) == "<")
                {
                    vectorOfCommands.push_back(new Command(commandHolder.getString()));
                    commandHolder.clearString();
                   }
                }
            }
        }
}
//parsed by spaces is vector parsed when there are no parenthesis
void ParseWithoutParenthesis(string bash_input, vector<string> &parsedbySpaces)
{
    char *inputHolder = new char[bash_input.length() +1];
    strcpy(inputHolder, bash_input.c_str());
    
    char *inputsWithoutSpaces = strtok(inputHolder, " ");
    
    while(inputsWithoutSpaces != 0)
    {
        string str(inputsWithoutSpaces);
        parsedbySpaces.push_back(str);
        inputsWithoutSpaces = strtok(NULL, " ");
    }

    parsedbySpaces.push_back(" ");
}
CommandComponent* ParseTheseParenthesis(string ParseHasParen)
{
    //BLOCK OF CODE CHECKS IF PARAMATER STRING HAS PARANTHESIS;
    bool ParenFound = false;
    int rightPCount = 0;
    int leftPCount = 0;
    for(int i = 0; i <ParseHasParen.size(); i++)
    {
        if(ParseHasParen.at(i) == '(')
        {
            ParenFound = true;
            rightPCount++;
        }
        if(ParseHasParen.at(i) == ')')
        {
            leftPCount++;
        }
    }
    if(rightPCount != leftPCount)
    {
        cout << "Parenthesis don't make sense." << endl;
        return nullptr;
    }
    //////////////////////////////////////////////////////////////
    
    vector<string> SpacedStringCommands;
    vector<CommandComponent*> emptyCommands;
    CommandComponent* tree;
    
    //BLOCK OF CODE WILL RUN BASE CASE: NO PARENTHESIS: RETURN TREE ROOT OF COMMAND
    if(ParenFound == false)
    {
        //debugging
        //cout << "hi" << endl;
        //
        ParseWithoutParenthesis(ParseHasParen, SpacedStringCommands);
        makeStringArrayToCommandArray(SpacedStringCommands, emptyCommands);
        makeTrees(emptyCommands, tree);
        
//        for(int i = 0; i < emptyCommands.size(); i++)
//        {
//            free emptyCommands.at(i);
//        }
        return tree;
    }
    //////////////////////////////////////////////////////////////////
    
    //BLOCK OF CODE WILL RECURSIVELY CALL WHAT IS IN PARENTHESIS AND MAKE EMPTY COMMAND VECTOR WITH WHATS NOT IN PARENTHESIS
    else
    {
        ParseWithoutParenthesis(ParseHasParen, SpacedStringCommands);
        
        int counter = 0;
        
//        //debug
//        for(int i = 0; i < SpacedStringCommands.size(); i ++)
//        {
//            cout << SpacedStringCommands.at(i) << endl;
//        }
//        ////
       
        Command commandHolder;

        while(counter < SpacedStringCommands.size() - 1)
        {
            if(SpacedStringCommands.at(counter).front() == '(')
            {
                //debugging
                //cout << "hi" << endl;
                //
                SpacedStringCommands.at(counter).erase(SpacedStringCommands.at(counter).begin());
                bool foundEnding = false;
                bool endedWithSemi = false;
                int parenTracker = 0;
                string newParam;
                
                while(foundEnding == false)
                {
                    if(SpacedStringCommands.at(counter) == " ")
                    {
                        cout << "Parenthensis don't make sense." << endl;
                        return nullptr;
                    }
                    for(int i = 0; i < SpacedStringCommands.at(counter).length(); i++)
                    {
                        if(SpacedStringCommands.at(counter).at(i) == '(')
                        {
                            parenTracker++;
                        }
                        else if(SpacedStringCommands.at(counter).at(i) == ')' && parenTracker > 0)
                        {
                            parenTracker--;
                        }
                        else if(SpacedStringCommands.at(counter).at(i) == ')' && parenTracker == 0)
                        {
                            foundEnding = true;
                            if(i < SpacedStringCommands.at(counter).length() - 1)
                            {
                                if(SpacedStringCommands.at(counter).at(i+1) == ';')
                                {
                                    endedWithSemi = true;
                                }
                            }
                            SpacedStringCommands.at(counter).erase(SpacedStringCommands.at(counter).begin() + i, SpacedStringCommands.at(counter).end());
                        }
                    }
                    newParam.append(SpacedStringCommands.at(counter));
                    newParam.append(" ");
                    counter++;
//                    //debugging
//                    cout << newParam << endl;
//                    cout << counter << endl;
//                    //
                }
                emptyCommands.push_back(ParseTheseParenthesis(newParam));
                if(endedWithSemi)
                {
                    emptyCommands.push_back(new SemiColon());
                }
            }
            else
            {
                if(SpacedStringCommands.at(counter) == "&&")
                {
                    emptyCommands.push_back(new andConnector());
                }
                else if(SpacedStringCommands.at(counter) == "||")
                {
                    emptyCommands.push_back(new orConnector());
                }
                else if(SpacedStringCommands.at(counter) == "<")
                {
                    emptyCommands.push_back(new Input_ReDirect());
                }
                else if(SpacedStringCommands.at(counter) == "|")
                {
                    emptyCommands.push_back(new pipeConnector());
                }
                else if(SpacedStringCommands.at(counter) == ">>")
                {
                    emptyCommands.push_back(new Append_ReDirect());
                }
                else if(SpacedStringCommands.at(counter) == ">")
                {
                    emptyCommands.push_back(new Output_ReDirect());
                }
                else if(SpacedStringCommands.at(counter) == "test")
                {
                    bool hasSemi = false;
                    if(SpacedStringCommands.at(counter+2).back() == ';')
                    {
                        SpacedStringCommands.at(counter+2).back() = 0;
                        hasSemi = true;
                    }
                    emptyCommands.push_back(new filePath(SpacedStringCommands.at(counter+2)));
                    if(hasSemi == true)
                    {
                        emptyCommands.push_back(new SemiColon());
                    }
                    counter+= 2;
                }
                else if(SpacedStringCommands.at(counter) == "[")
                {
                    bool hasSemi = false;
                    if(SpacedStringCommands.at(counter+3).back() == ';')
                    {
                        hasSemi = true;
                    }
                    emptyCommands.push_back(new filePath(SpacedStringCommands.at(counter+2)));
                    if(hasSemi == true)
                    {
                        emptyCommands.push_back(new SemiColon());
                    }
                    counter+= 3;
                }

                else
                {
                    if(SpacedStringCommands.at(counter).at(SpacedStringCommands.at(counter).length() -1) == ';')
                    {
                        SpacedStringCommands.at(counter).at(SpacedStringCommands.at(counter).length() -1)= 0;
                        commandHolder.appendString(SpacedStringCommands.at(counter));
                        emptyCommands.push_back(new Command(commandHolder.getString()));
                        commandHolder.clearString();
                        emptyCommands.push_back(new SemiColon());
                    }
                    else
                    {
                        commandHolder.appendString(SpacedStringCommands.at(counter));
                        if(SpacedStringCommands.at(counter+1) == "&&" || SpacedStringCommands.at(counter+1) == "||" || SpacedStringCommands.at(counter+1) == " " || SpacedStringCommands.at(counter+1) == "|" || SpacedStringCommands.at(counter+1) == ">" || SpacedStringCommands.at(counter+1) == ">>" || SpacedStringCommands.at(counter+1) == "<")
                        {
                            emptyCommands.push_back(new Command(commandHolder.getString()));
                            commandHolder.clearString();
                        }
                    }
//                    //debugging
//                    cout << "appending string to command" << commandHolder.getString() << endl;
                }
                counter++;
            }
        }
        //debug
        //cout << "test" << endl;
//        emptyCommands.at(0)->execute();
//        cout << emptyCommands.size() << endl;
        
        
        makeTrees(emptyCommands, tree);

        return tree;
    }
    //////////////////////////////////////////////////////////////////////////////////////////
}
void executeUserInput(string bash_input)
{
    /* vector names:
     *  semi_positions: positions of semi colons
     *  substrings : contains all substrings before semi colons and whatever is left over
     *  p
     *  osition_values: contains all positions of connectors including semi colons
     */
    
    //check input for #
    bool hasComments = false;
    int commentAt = 0;
    for(int k = 0; k < bash_input.length(); k++)
    {
        if(bash_input[k] == '#')
        {
            hasComments = true;
            commentAt = k;
        }
    }
    if(hasComments)
    {
        bash_input.erase(bash_input.begin() + commentAt, bash_input.end());
    }
    
    
    CommandComponent* treePrint = ParseTheseParenthesis(bash_input);

    if(treePrint != nullptr)
    {
        treePrint->execute();
    }
}

int main()
{
    cout <<  "Type commands with one of the following ‘||’, ‘&&’, or ‘;’ between each command. ‘||’ will execute the next command if the previous command fails. ‘&&’ will execute the next command only if previous command succeeds. ‘;’ will execute the next command at all times. \n make sure there is a space between command and the ‘&&’ and ‘||’ connectors, while ‘;’ should be connected the preceding command and spaced with the next command." << endl;
    string userInput;
    while(userInput != "abort")
    {
        cout << "When done with commands type ‘abort’ to quit." << endl;
        getline(cin, userInput);
        if(userInput != "abort")
        {
        executeUserInput(userInput);
        }
    }

//    Command *c1 = new Command("ls -a");
//    Command *c2 = new Command("new_file.txt");
//
//    Output_ReDirect *op1 = new Output_ReDirect();
//    op1->addLeftComponent(c1);
//    op1->addRightComponent(c2);
//    op1->execute();
//
//    Command *c3 = new Command("echo this3");
//    Command *c4 = new Command("new_file.txt");
//
//    Append_ReDirect *ap1 = new Append_ReDirect();
//    ap1->addLeftComponent(c3);
//    ap1->addRightComponent(c4);
//    ap1->execute();
//
//    Command *c5 = new Command("cat");
//    Command *c6 = new Command("ex");
//
//    Input_ReDirect *ip1 = new Input_ReDirect();
//    ip1->addLeftComponent(c5);
//    ip1->addRightComponent(c6);
//    ip1->execute();



}



