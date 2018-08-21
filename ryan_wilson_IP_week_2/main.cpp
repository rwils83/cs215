/* Created By Ryan J. Wilson
for CTU CS215
Referenced code from Sample Code Week 2
Date of last Modification: 7/14/18*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib> //used for random number generator
#include <ctime> //used for time function to seed RNG
using namespace std;

ofstream outfile;
ifstream infile;

class Question
{
private:
	string question, answer;
	int value;
public:

	string getQuestion()
	{return question;}

	int getValue()
	{return value;}

	virtual void setQuestion(string answer, int value)
	{}

	virtual void printOptions()
	{}

	virtual string getAnswer()
	{return answer;}
};

class QuestionTF: public Question
{
private:
	string question;
	string answer;
	int points;
	string options;
public:
	void setQuestion(string theQuestion, int pointValue)
	{
        string theAnswer;
		question = theQuestion;
		points = pointValue;
		options = "true/false";
		getline(infile,theAnswer);
		answer = theAnswer;
	}
	void printOptions()
	{
		cout<<question<<endl;
		cout<<answer<<endl;}
	string getAnswer()
	{
		return answer;
	}
};

class QuestionMC: public Question
{
private:
	int value, numberOfOptions;
	string question, answer;
	string options[6];
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string line;
		getline(infile,line);//
		numberOfOptions = stoi(line);
		question = theQuestion;
		value = pointValue;
		for (int count = 0; count<numberOfOptions;count++){
			getline(infile,line);
			options[count] = line;
		}
		getline(infile, line);
		answer = line;
	}
	void printOptions()
	{
		char first = 'A';
		cout<<question<<endl;
		for(int count = 0; count<numberOfOptions;count++){
			cout<<first++ <<".  "<<options[count]<<endl;
		}
		cout<<"Answer:  "<< answer << endl;
	}
	string getAnswer()
	{
		return answer;
	}
};



int main() {
    int numquestions = 0;
    for (int c = 0; c<2; c++)
    {string numberofquestions;
	cout <<" How many questions?"<<endl;
	getline(cin, numberofquestions);
    stringstream geek(numberofquestions);

    geek >> numquestions;
    string correctAmountOfQuestions;
    cout << "You chose to enter " << numquestions << " . Is this correct?"<<endl;
    getline(cin, correctAmountOfQuestions);
    if (correctAmountOfQuestions!= "y" && correctAmountOfQuestions!= "Y"&& correctAmountOfQuestions!="Yes" && correctAmountOfQuestions!= "yes"){
        c--;}
        else c++;
        }


	Question *myQuestions[numquestions];
	string questiontype, questiontxt, typeOfQuestion, questionAnswer;
	string answertxt, optiontxt;
	int questionvalue;
	int i = 0;



outfile.open("testbank.txt");
if (outfile.is_open())

{

	outfile << to_string(numquestions) + "\n";
	for (int i = 0; i<numquestions; i++){
        string mcOptionsString, correctornot, mcValueString, tfValueString, mcQuestion, mcAnswer, tfQuestion, tfAnswer;
        int mcOptionsInt;
        cout << "What type of question would you like to add?"<<endl;
        getline(cin, typeOfQuestion);
        if (typeOfQuestion=="MC" || typeOfQuestion=="TF"){
            cout << "You chose to add a "<< typeOfQuestion << " question. Is this correct?"<<endl;
            getline(cin, correctornot);
            if (correctornot!="Y" && correctornot!="y" && correctornot!= "Yes" && correctornot!= "yes"){
                typeOfQuestion = " ";
                i--;}}
        //cout << typeOfQuestion<< endl;
        if (typeOfQuestion != "MC" && typeOfQuestion != "TF"){
            cout << "Please Enter MC for Multiple Choice or TF for True/False."<<endl;
            i--;}
        if (typeOfQuestion == "MC"){
            cout << "How many Points is this question worth?" << endl;
            getline(cin, mcValueString);
            outfile << typeOfQuestion + " " + mcValueString + "\n";
            cout << "What is the question?" << endl;
            getline(cin, mcQuestion);
            outfile <<  mcQuestion + "\n";
            cout << "How many choices would you like to have?" << endl;
            getline(cin, mcOptionsString);
            outfile << mcOptionsString + "\n";
            stringstream geek(mcOptionsString);
            geek >> mcOptionsInt;
                for (int h = 0; h<mcOptionsInt; h++){
                    string choice;
                    cout << "Enter Answer Choice"<<endl;
                    getline(cin, choice);
                    outfile << choice + "\n";}
            cout << "What is the correct Answer?"<<endl;
            getline(cin, mcAnswer);
            outfile << mcAnswer + "\n";}
        if (typeOfQuestion == "TF"){
            cout << "What is your question?" << endl;
            getline(cin, tfQuestion);
            cout << "How many Points is your question worth?"<< endl;
            getline(cin, tfValueString);
            outfile << typeOfQuestion  + " " + tfValueString + "\n";
            outfile << "T/F\n";
            cout << "Is the answer True or False?" << endl;
            getline(cin, tfAnswer);
            outfile << tfAnswer;}

	}

	outfile.close();
}
else cout << "Unable to open file";

infile.open("testbank.txt");

string line, theQuestion, theAnswer;

if (infile.is_open())
{
    // uncomment the next two lines to run without RNG
	getline(infile,line);
	numquestions = stoi(line);
	//comment out next line to run without RNG
	//numquestions = (rand()%10)+1;//randomize number of test questions. Modulus 10 to range 0-9 +1 to range from 1-10.
	for(int count = 0; count<numquestions;count++){
		getline(infile,line);
		int npos = line.size();
		int prev_pos = 0;
		int pos = 0;
		while( line[pos]!=' ')
			pos++;
		questiontype = line.substr(prev_pos, pos-prev_pos);
		prev_pos = ++pos;
        questionvalue = stoi(line.substr(prev_pos, npos-prev_pos));
	   if (questiontype == "TF")
		{
			myQuestions[count] = new QuestionTF;
			getline(infile,theQuestion);
			myQuestions[count]->setQuestion(theQuestion,questionvalue);
		}
		if (questiontype =="MC")
		{
			myQuestions[count] =new QuestionMC;
			getline(infile,theQuestion);
			myQuestions[count]->setQuestion(theQuestion,questionvalue);
		}

	}
}
	for(int count = 0; count<numquestions;count++)
	{
		myQuestions[count]->printOptions();
		cout<<endl;
	}

	getchar();
	return 0;
}
