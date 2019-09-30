#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <string>
#include "Stack.h"
#include "Exception.h"
#include "ArrayStack.h"
#include "DoublingArrayStack.h"
#include "LinkedListStack.h"

using namespace std;

void log_csv(string filename, ofstream& ofs, chrono::duration<double, nano> elapsed, int currPushCount)
{
    double millisecondsDenominator = 1000000; 
    auto elapsed_seconds = elapsed/millisecondsDenominator;
    ofs.open(filename, ios::app);
    ofs << currPushCount << "," << elapsed_seconds.count() << "\n";
    ofs.close();
}

int main()
{
	// Request: reduce CPU use (vagrant?)
	// Output: demonstrate basic functionality
	// Extra Credit: alternate structures and analysis
	try
	{
        int pushes = 1000000;
        int logInterval = 10000;
        string trialID = "3";

    	// File-handling:
        // The open() and close() clear the previous log each time.
    	ofstream arraystack_ofs;
    	string arraystack_filename = "./logs/arraystack_log" + trialID + ".csv";
    	arraystack_ofs.open(arraystack_filename);
    	arraystack_ofs.close();

    	ofstream doublingarraystack_ofs;
    	string doublingarraystack_filename = "./logs/doublingarraystack_log" + trialID + ".csv";
    	doublingarraystack_ofs.open(doublingarraystack_filename);
    	doublingarraystack_ofs.close();

    	ofstream linkedliststack_ofs;
    	string linkedliststack_filename = "./logs/linkedliststack_log" + trialID + ".csv";
    	linkedliststack_ofs.open(linkedliststack_filename);
    	linkedliststack_ofs.close();

        ArrayStack<int> *arrStack = new ArrayStack<int>(1000, 100);
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i <= pushes; i++)
        {
            arrStack->push(i);
            if (i % logInterval == 0) 
            { 
                auto curr = chrono::high_resolution_clock::now();
                auto elapsed = curr - start;
                log_csv(arraystack_filename, arraystack_ofs, elapsed, i); 
            }
        }
        delete arrStack;

        DoublingArrayStack<double> *doubStack = new DoublingArrayStack<double>(100);
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i <= pushes; i++)
        {
            doubStack->push(i);
            if (i % logInterval == 0) 
            { 
                auto curr = chrono::high_resolution_clock::now();
                auto elapsed = curr - start;
                log_csv(doublingarraystack_filename, doublingarraystack_ofs, elapsed, i); 
            }
        }
        delete doubStack;

        LinkedListStack<int> *llStack = new LinkedListStack<int>();
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i <= pushes; i++)
        {
            llStack->push(i);
            if (i % logInterval == 0) 
            { 
                auto curr = chrono::high_resolution_clock::now();
                auto elapsed = curr - start;
                log_csv(linkedliststack_filename, linkedliststack_ofs, elapsed, i); 
            }
        }
        delete llStack;

        // Console log:
        // cout << "\nArrayStack:         " << elapsedAS.count() << endl;
        // cout << "\nDoublingArrayStack: " << elapsedDAS.count() << endl;
        // cout << "\nLinkedListStack:    " << elapsedLLS.count() << endl;
        // cout << endl;

        cout << "Success.\n";
	}
	catch (const exception& e)
	{
		cerr << e.what() << '\n';
	}
}