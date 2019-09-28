#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <string>
#include "Stack.h"
#include "Exception.h"
#include "ArrayStack.cpp"
#include "DoublingArrayStack.cpp"
#include "LinkedListStack.cpp"

using namespace std;

int main()
{
	// Request: reduce CPU use (vagrant?)
	// Output: demonstrate basic functionality
	// Extra Credit: alternate structures and analysis
	try
	{
    int testMax = 10000;
		string trialID = "1";

		// File-handling:
		ofstream arraystack_ofs;
		string arraystack_filename = "./logs/arraystack_log" + trialID + ".csv";
		// arraystack_ofs.open(arraystack_filename);

		ofstream doublingarraystack_ofs;
		string doublingarraystack_filename = "./logs/doublingarraystack_log" + trialID + ".csv";
		// doublingarraystack_ofs.open(doublingarraystack_filename);

		ofstream linkedliststack_ofs;
		string linkedliststack_filename = "./logs/linkedliststack_log" + trialID + ".csv";
		// linkedliststack_ofs.open(linkedliststack_filename);

    for (int testCount = 0; testCount <= testMax; testCount += 1000)
        {
            ArrayStack<int> arrStack(1000, 100);
            auto startAS = chrono::high_resolution_clock::now();
            for (int i = 1; i <= testCount; i++)
            {
                arrStack.push(i);
            }
            auto finishAS = chrono::high_resolution_clock::now();

            DoublingArrayStack<double> doubStack(100);
            auto startDAS = chrono::high_resolution_clock::now();
            for (int i = 1; i <= testCount; i++)
            {
                doubStack.push(i);
            }
            auto finishDAS = chrono::high_resolution_clock::now();

            LinkedListStack<int> llStack;
            auto startLLS = chrono::high_resolution_clock::now();
            for (int i = 1; i <= testCount; i++)
            {
                llStack.push(i);
            }
            auto finishLLS = chrono::high_resolution_clock::now();

            // convert nanoseconds (1e-9) to seconds
            double millisecondsDenominator = 1000000; 
            auto elapsedAS = (finishAS - startAS)/millisecondsDenominator;
            auto elapsedDAS = (finishDAS - startDAS)/millisecondsDenominator;
            auto elapsedLLS = (finishLLS - startLLS)/millisecondsDenominator;

            // Console log:
            // cout << "\nArrayStack:         " << elapsedAS.count() << endl;
            // cout << "\nDoublingArrayStack: " << elapsedDAS.count() << endl;
            // cout << "\nLinkedListStack:    " << elapsedLLS.count() << endl;
            // cout << endl;

            // CSV log:
            arraystack_ofs.open(arraystack_filename, ios::app);
            arraystack_ofs << testCount << "," << elapsedAS.count() << "\n";
			arraystack_ofs.close();

            doublingarraystack_ofs.open(doublingarraystack_filename, ios::app);
            doublingarraystack_ofs << testCount << "," << elapsedDAS.count() << "\n";
			doublingarraystack_ofs.close();

            linkedliststack_ofs.open(linkedliststack_filename, ios::app);
            linkedliststack_ofs << testCount << "," << elapsedLLS.count() << "\n";
			linkedliststack_ofs.close();


        }
        cout << "Success.\n";
	}
	catch (const exception& e)
	{
		cerr << e.what() << '\n';
	}
}