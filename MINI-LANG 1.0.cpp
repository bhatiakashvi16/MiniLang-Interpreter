//MINI LANGUAGE INTERPRETER VERSION 1.0.0
#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<stdexcept>
using namespace std;
//Variable Made By User
class Variable
{public:
    string datatype;
    int intValue;
    float floatValue;
    double doubleValue;
    string stringValue;
    bool boolValue;};
//Making Tokenizer that breaks command into Tokens
vector<string>tokenize(string line)
    {vector<string> tokens;
    string word = "";
    for(int i=0; i<line.length(); i++)
    {if(line[i] != ' '){word += line[i];}
     else{if(word != "")
            {tokens.push_back(word);
             word = "";}}}
    if(word != "")
    {tokens.push_back(word);}
    return tokens;}
//Checking Datatype
bool isInteger(string value)
{for(int i=0; i<value.length(); i++)
    {if(value[i]<'0' || value[i]>'9')
        {return false;}}
    return true;}
bool isFloat(string value)
{int dotCount = 0;
    for(int i=0; i<value.length(); i++)
    {if(value[i]=='.')
        {dotCount++;}
     else if(value[i]<'0' || value[i]>'9')
        {return false;}}
    return dotCount==1;}
bool isBoolean(string value)
{return value=="true" || value=="false";}
//Command Class (Abstract Class)
class Command
{public:
    virtual void execute(map<string,Variable>& variables) = 0;
    virtual ~Command(){}};
class StoreCommand : public Command
{private:
    string variable;
    string value;
public:
    StoreCommand(string v,string val)
    {variable = v;
     value = val;}
    void execute(map<string,Variable>& variables)
    {Variable obj;
     if(isInteger(value))
        {obj.datatype = "int";
         obj.intValue = stoi(value);}
     else if(isFloat(value))
        {obj.datatype = "float";
         obj.floatValue = stof(value);}
        else if(isBoolean(value))
        {obj.datatype = "bool";
         if(value=="true")
            {obj.boolValue = true;}
         else
            {obj.boolValue = false;}}
        else
        {obj.datatype = "string";
         obj.stringValue = value;}
        variables[variable] = obj;
        cout<<"[Stored] "<<variable<<endl;}};
//Displaying Command
class DisplayCommand : public Command
{
private:
    string variable;
public:
    DisplayCommand(string v)
    {variable = v;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(variable)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable obj = variables[variable];
     cout<<variable<<" = ";
     if(obj.datatype=="int")
        {cout<<obj.intValue;}
     else if(obj.datatype=="float")
        {cout<<obj.floatValue;}
     else if(obj.datatype=="bool")
    {if(obj.boolValue==true){cout<<"true";}
     else{cout<<"false";}}
     else if(obj.datatype=="string")
        {cout<<obj.stringValue;}
        cout<<endl;}
    };
//DELETE COMMAND
class DeleteCommand : public Command
{
private:
    string variable;
public:
    DeleteCommand(string v)
    {variable = v;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(variable)==variables.end())
        {throw runtime_error("Variable Not Found");}
     variables.erase(variable);
        cout<<variable<<" Deleted Successfully"<<endl;}
};
//UPDATE COMMAND
class UpdateCommand : public Command
{
private:
    string variable;
    string newValue;
public:
    UpdateCommand(string v,string val)
    {variable = v;
     newValue = val;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(variable)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable &obj = variables[variable];
     if(obj.datatype=="int")
        {obj.intValue = stoi(newValue);}
     else if(obj.datatype=="float")
        {obj.floatValue = stof(newValue);}
     else if(obj.datatype=="bool")
        {if(newValue=="true")
            {obj.boolValue = true;}
         else
            {obj.boolValue = false;}}
     else if(obj.datatype=="string")
        {obj.stringValue = newValue;}
     cout<<variable<<" Updated Successfully"<<endl;}
    };
//Increase Value of Variable
class IncreaseCommand : public Command
{private:
    string variable;
    float value;
public:
    IncreaseCommand(string v,float val)
    {variable = v;
     value = val;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(variable)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable &obj = variables[variable];
     if(obj.datatype=="int")
        {obj.intValue += value;}
     else if(obj.datatype=="float")
        {obj.floatValue += value;}
     else
        {throw runtime_error("Increase Works Only On Numbers");}
     cout<<variable<<" Increased"<<endl;}};
//Decrease Value of Variable
class DecreaseCommand : public Command
{private:
    string variable;
    float value;
public:
    DecreaseCommand(string v,float val)
    {variable = v;
     value = val;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(variable)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable &obj = variables[variable];
     if(obj.datatype=="int")
        {obj.intValue -= value;}
     else if(obj.datatype=="float")
        {obj.floatValue -= value;}
     else
        {throw runtime_error("Decrease Works Only On Numbers");}
     cout<<variable<<" Decreased"<<endl;}};
//COMPARE COMMNAND
class CompareCommand : public Command
{private:
    string a,b;
public:
    CompareCommand(string x,string y)
    {a = x;
     b = y;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(a)==variables.end() || variables.find(b)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable obj1 = variables[a];
     Variable obj2 = variables[b];
     if((obj1.datatype!="int" && obj1.datatype!="float") ||(obj2.datatype!="int" && obj2.datatype!="float"))
        {throw runtime_error("Compare Supports Only Numbers");}
     float x,y;
     if(obj1.datatype=="int")
        {x = obj1.intValue;}
     else
        {x = obj1.floatValue;}
     if(obj2.datatype=="int")
        {y = obj2.intValue;}
     else
        {y = obj2.floatValue;}
     if(x>y)
        {cout<<a<<" > "<<b<<endl;}
     else if(x<y)
        {cout<<a<<" < "<<b<<endl;}
     else
        {cout<<a<<" == "<<b<<endl;}}};
class ArithmeticCommand : public Command
{private:
    string operation;
    string var1;
    string var2;
    string result;
public:
    ArithmeticCommand(string op,string a,string b,string r)
    {operation = op;
     var1 = a;
     var2 = b;
     result = r;}
    void execute(map<string,Variable>& variables)
    {if(variables.find(var1)==variables.end() || variables.find(var2)==variables.end())
        {throw runtime_error("Variable Not Found");}
     Variable obj1 = variables[var1];
     Variable obj2 = variables[var2];
     // STRING CONCAT SUPPORT
    if(obj1.datatype=="string" && obj2.datatype=="string")
        {if(operation!="add"){throw runtime_error("Strings Support Only Add Operation");}
         Variable resultObj;
         resultObj.datatype = "string";
         resultObj.stringValue = obj1.stringValue + obj2.stringValue;
         variables[result] = resultObj;
         cout<<result<<" Stored Successfully"<<endl;
         return;}
     // NUMBER CHECK
    if((obj1.datatype!="int" && obj1.datatype!="float") || (obj2.datatype!="int" && obj2.datatype!="float"))
    {throw runtime_error("Arithmetic Supports Only Numbers");}
     Variable resultObj;
        // FLOAT CASE
        if(obj1.datatype=="float" || obj2.datatype=="float")
        {float a,b,ans;
         if(obj1.datatype=="int"){a = obj1.intValue;}
         else{a = obj1.floatValue;}
         if(obj2.datatype=="int"){b = obj2.intValue;}
         else{b = obj2.floatValue;}
        if(operation=="add"){ans = a + b;}
        else if(operation=="subtract"){ans = a - b;}
        else if(operation=="multiply"){ans = a * b;}
        else if(operation=="divide")
        {if(b==0)
            {throw runtime_error("Division By Zero");}
             ans = a / (float)b;}
         resultObj.datatype = "float";
         resultObj.floatValue = ans;}
        // INTEGER CASE
        else
        {int a = obj1.intValue;
         int b = obj2.intValue;
         int ans;
         if(operation=="add"){ans = a + b;}
         else if(operation=="subtract"){ans = a - b;}
         else if(operation=="multiply"){ans = a * b;}
         else if(operation=="divide")
        {if(b==0)
        {throw runtime_error("Division By Zero");}
         resultObj.datatype = "float";
         resultObj.floatValue = (float)a / b;
         variables[result] = resultObj;
         cout<<result<<" Stored Successfully"<<endl;
         return;}
         resultObj.datatype = "int";
         resultObj.intValue = ans;}
        variables[result] = resultObj;
        cout<<result<<" Stored Successfully"<<endl;}};
//Show Variable Command
class ShowVarsCommand : public Command
{public:
    void execute(map<string,Variable>& variables)
    {map<string,Variable>::iterator itr;
     cout << "\n===== VARIABLES =====\n";
        for(itr=variables.begin(); itr!=variables.end(); itr++)
        {cout<<itr->first<<endl;}
        cout<<"====================="<<endl;}};
//Interpreter
class Interpreter
{private:
    map<string,Variable> variables;
    queue<Command*> commandQueue;
public:
    void parse(string line)
    {vector<string> tokens = tokenize(line);
     if(tokens.size()==0)
        {return;}
        //Set or Store Values
        if((tokens[0]=="store" || tokens[0]=="set") && tokens.size()==4 && tokens[2]=="as")
        {commandQueue.push(new StoreCommand(tokens[1],tokens[3]));}
        //Display or Print Values
        else if((tokens[0]=="display" || tokens[0]=="print") && tokens.size()==4)
        {commandQueue.push(new DisplayCommand(tokens[3]));}
        //Deleting a Variable
        else if(tokens[0]=="delete" && tokens.size()==2)
        {commandQueue.push(new DeleteCommand(tokens[1]));}
        //Updating a Variable
        else if(tokens[0]=="update" && tokens.size()==4 && tokens[2]=="as")
        {commandQueue.push(new UpdateCommand(tokens[1],tokens[3]));}
        //Increase Value of Variable
        else if(tokens[0]=="increase" && tokens.size()==4 && tokens[2]=="by")
        {commandQueue.push(new IncreaseCommand(tokens[1],stof(tokens[3])));}
        //Decrease Value of Variable
        else if(tokens[0]=="decrease" && tokens.size()==4 && tokens[2]=="by")
        {commandQueue.push(new DecreaseCommand(tokens[1],stof(tokens[3])));}
        //Compare Variables
        else if(tokens[0]=="compare" && tokens.size()==4 && tokens[2]=="&")
        {commandQueue.push(new CompareCommand(tokens[1],tokens[3]));}
        //Show Variables
        else if(tokens[0]=="showvars")
        {commandQueue.push(new ShowVarsCommand());}
        //Arithmetic Operations
        else if((tokens[0]=="add" || tokens[0]=="subtract" || tokens[0]=="multiply" || tokens[0]=="divide") && tokens.size()==6
                && tokens[2]=="and" && tokens[4]=="into")
        {commandQueue.push(new ArithmeticCommand(tokens[0],tokens[1],tokens[3],tokens[5]));}
            //Help Command
        else if(tokens[0]=="help")
            {cout<<endl<<"================= AVAILABLE COMMANDS ================="<<endl;
             cout<<endl<<"VARIABLE COMMANDS"<<endl;
             cout<<"store <variable> as <value>"<<endl;
             cout<<"display variable <variable>"<<endl;
             cout<<"update <variable> as <value>"<<endl;
             cout<<"delete <variable>"<<endl;
             cout<<"showvars"<<endl;
             cout<<endl<<"ARITHMETIC COMMANDS"<<endl;
             cout<<"add <var1> and <var2> into <result>"<<endl;
             cout<<"subtract <var1> and <var2> into <result>"<<endl;
             cout<<"multiply <var1> and <var2> into <result>"<<endl;
             cout<<"divide <var1> and <var2> into <result>"<<endl;
             cout<<endl<<"OTHER COMMANDS"<<endl;
             cout<<"increase <variable> by <number>"<<endl;
             cout<<"decrease <variable> by <number>"<<endl;
             cout<<"compare <var1> & <var2>"<<endl;
             cout<<"about"<<endl;
             cout<<"help"<<endl;
             cout<<"exit"<<endl;
             cout<<"======================================================"<<endl;}
        //Invalid Command
        else
        {cout<<"Invalid Command"<<endl;}}
    //Executing Command
    void executeCommands()
    {while(!commandQueue.empty())
        {Command *command = commandQueue.front();
         commandQueue.pop();
         try
            {command->execute(variables);}
         catch(exception& e)
            {cout<<"Error : "<<e.what()<<endl;}
         delete command;}}};
//Main Function of Mini Lamguage Interpreter
int main()
    {Interpreter interpreter;
    string line;
    cout<<"  ===================================="<<endl;
    cout<<"       MINI LANGUAGE INTERPRETER"<<endl;
    cout<<"  ===================================="<<endl;
    cout <<"Write Below what Command You want to give :-"<<endl;
    while(true)
    {cout<<"--> ";
     getline(cin,line);
     if(line=="exit" || line=="exit interpreter")
        {break;}
     interpreter.parse(line);
     interpreter.executeCommands();}
    cout<<"\nInterpreter Closed Successfully\n";
    return 0;}
