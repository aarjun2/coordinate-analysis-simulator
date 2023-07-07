#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "random.h"
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#include<thread>
#include <mutex>
#include <string>
#include <limits>

using namespace std;
std::mutex printMutex;
//
////ORIGINAL DRAFT ------------------------------------------------------------
//
//int main()
//{
//    map<double, double> passMap;
//    map<double, double> retryMap;
//    map<double, double> failMap;
//    map<double, double>::iterator itlow, itup, findIt;
//
//    passMap[13] = 0.1171;
//    passMap[15] = 0.3033;
//    passMap[16.5] = 0.4754;
//    passMap[17.7] = 0.5205;
//    passMap[19] = 0.6159;
//    passMap[21] = 0.6388;
//
//    retryMap[13] = 0.2559;
//    retryMap[15] = 0.3595;
//    retryMap[16.5] = 0.3349;
//    retryMap[17.7] = 0.2992;
//    retryMap[19] = 0.2670;
//    retryMap[21] = 0.2313;
//
//    failMap[13] = 0.6270;
//    failMap[15] = 0.3361;
//    failMap[16.5] = 0.1885;
//    failMap[17.7] = 0.1803;
//    failMap[19] = 0.1159;
//    failMap[21] = 0.1288;
//
//    int no_of_trials = 0;
//    double NF = -131;//-131
//    double SD = 5.6;//5.6
//    /*string inputString;
//    string outputString;
//    cout << "Enter data file name" << endl;
//    cin >> inputString;
//    cout << "Enter number of trials" << endl;
//    cin >> no_of_trials;
//    cout << "Enter standard deviation" << endl;
//    cin >> SD;
//    cout << "Enter noise floor" << endl;
//    cin >> NF;
//    cout << "Enter output file name" << endl;
//    cin >> outputString;*/
//
//
//    fstream outputFile("output.txt", ios::app);
//    if (!outputFile) {
//        cerr << "Error opening the file." << endl;
//        return 1;
//    }
//
//	HANDLE hFile, hFileMap;
//	double* pBuffer = nullptr;
//
//	// Open the file
//	hFile = CreateFile(TEXT("RetryAnalysis.sig"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (hFile == INVALID_HANDLE_VALUE)
//	{
//		std::cout << "Failed to open the file." << std::endl;
//		return 1;
//	}
//
//	// Get the file size
//	DWORD nFileSize = GetFileSize(hFile, NULL);
//	if (nFileSize == INVALID_FILE_SIZE)
//	{
//		CloseHandle(hFile);
//		std::cout << "Failed to get the file size." << std::endl;
//		return 1;
//	}
//
//	// Create a file mapping object
//	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
//	if (hFileMap == NULL)
//	{
//		CloseHandle(hFile);
//		std::cout << "Failed to create file mapping." << std::endl;
//		return 1;
//	}
//
//	// Map the file into memory
//	pBuffer = (double*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
//	if (pBuffer == NULL)
//	{
//		CloseHandle(hFileMap);
//		CloseHandle(hFile);
//		std::cout << "Failed to map the file into memory." << std::endl;
//		return 1;
//	}
//
//	// Now you can access the file content as a double array using pBuffer
//	int nNumRecords = nFileSize / sizeof(double);
//
//    
//    for (int i = 0; i < 1; ++i) {
//        vector<int> resultArr;
//        for (int j = 0; j < nNumRecords; ++j) {
//            double DV = pBuffer[j];
//            std::cout << "Value at index " << j << ": " << DV << std::endl;
//            CRandom myObject;
//            double AV = myObject.rand_normal(DV, SD);
//            double CN = AV - NF;
//            double pass_percentage, retry_percentage, fail_percentage;
//            findIt = passMap.find(CN);
//            if (findIt != passMap.end()) {
//                pass_percentage = findIt->second;
//                retry_percentage = retryMap[findIt->first];
//                fail_percentage = failMap[findIt->first];
//            }
//            else if (CN <= 13) {
//                pass_percentage = passMap[13];
//                retry_percentage = retryMap[13];
//                fail_percentage = failMap[13];
//            }
//            else if (CN >= 21) {
//                pass_percentage = passMap[21];
//                retry_percentage = retryMap[21];
//                fail_percentage = failMap[21];
//            }
//            else if (CN > 13 && CN < 21) {
//                itlow = passMap.lower_bound(CN);
//                itup = passMap.upper_bound(CN);
//                itlow--;
//                pass_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
//                itlow = retryMap.lower_bound(CN);
//                itup = retryMap.upper_bound(CN);
//                itlow--;
//                retry_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
//                itlow = failMap.lower_bound(CN);
//                itup = failMap.upper_bound(CN);
//                itlow--;
//                fail_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
//            }
//            if ((fail_percentage * 1000 + retry_percentage * 1000 + pass_percentage * 1000) != 1000) {
//                fail_percentage = fail_percentage * 1000;
//                retry_percentage = retry_percentage * 1000;
//                pass_percentage = pass_percentage * 1000;
//                double ret = max(fail_percentage, retry_percentage);
//                ret = max(ret, pass_percentage);
//                if (ret == fail_percentage) {
//                    fail_percentage = ceil(fail_percentage);
//                }
//                if (ret == pass_percentage) {
//                    pass_percentage = ceil(pass_percentage);
//                }
//                if (ret == retry_percentage) {
//                    retry_percentage = ceil(retry_percentage);
//                }
//                if ((fail_percentage + retry_percentage + pass_percentage) != 1000) {
//                    double valDifference = (fail_percentage +
//                        retry_percentage + pass_percentage) - 1000;
//                    valDifference = valDifference / 3;
//                    if (valDifference > 0) {
//                        fail_percentage = fail_percentage - valDifference;
//                        pass_percentage = pass_percentage - valDifference;
//                        retry_percentage = retry_percentage - valDifference;
//                    }
//                    else {
//                        fail_percentage = fail_percentage - valDifference;
//                        pass_percentage = pass_percentage - valDifference;
//                        retry_percentage = retry_percentage - valDifference;
//                    }
//                }
//            }
//            int val_arr[1000];
//            int numZeroes = static_cast<int>(pass_percentage);
//            int numOnes = static_cast<int>(retry_percentage);
//            int numTwos = static_cast<int>(fail_percentage);
//            if ((numOnes + numZeroes + numTwos) != 1000) {
//                int differVal = (numOnes + numZeroes + numTwos) - 1000;
//                int ret = max(numOnes, numZeroes);
//                ret = max(ret, numTwos);
//                if (ret == numOnes) {
//                    numOnes = numOnes - differVal;
//                }
//                if (ret == numTwos) {
//                    numTwos = numTwos - differVal;
//                }
//                if (ret == numZeroes) {
//                    numZeroes = numZeroes - differVal;
//                }
//            }
//
//            /*int z = 0;
//            for (z = 0; z < numZeroes; ++z) {
//                val_arr[z] = 0;
//            }
//            int count = numOnes + z;
//            for (;z < count; ++z) {
//                val_arr[z] = 1;
//            }
//            count = numTwos + z;
//            for (; z < count; ++z) {
//                val_arr[z] = 2;
//            }*/
//
//            for (int k = 0; k < 1000; ++k) {
//                if (numOnes > 0 && numTwos > 0 && numZeroes > 0) {
//                    std::random_device rd;
//                    std::mt19937 engine(rd());
//                    std::uniform_int_distribution<int> distribution(0, 2);
//                    int randomNumber = distribution(engine);
//                    val_arr[k] = randomNumber;
//                }
//                if (numOnes > 0 && numTwos > 0 && numZeroes <= 0) {
//                    std::random_device rd;
//                    std::mt19937 engine(rd());
//                    std::uniform_int_distribution<int> distribution(1, 2);
//                    int randomNumber = distribution(engine);
//                    val_arr[k] = randomNumber;
//                }
//                if (numOnes > 0 && numTwos <= 0 && numZeroes > 0) {
//                    std::random_device rd;
//                    std::mt19937 engine(rd());
//                    std::uniform_int_distribution<int> distribution(0, 1);
//                    int randomNumber = distribution(engine);
//                    val_arr[k] = randomNumber;
//                }
//                if (numOnes <= 0 && numTwos > 0 && numZeroes > 0) {
//                    std::random_device rd;
//                    std::mt19937 engine(rd());
//                    std::uniform_int_distribution<int> distribution(0, 1);
//                    int randomNumber = distribution(engine) * 2;
//                    val_arr[k] = randomNumber;
//                }
//                if (numOnes <= 0 && numTwos <= 0 && numZeroes > 0) {
//                    val_arr[k] = 0;
//                }
//                if (numOnes > 0 && numTwos <= 0 && numZeroes <= 0) {
//                    val_arr[k] = 1;
//                }
//                if (numOnes <= 0 && numTwos > 0 && numZeroes <= 0) {
//                    val_arr[k] = 2;
//                }
//            }
//            std::random_device rd; // Obtain a random seed from the hardware
//            std::mt19937 engine(rd()); // Use the Mersenne Twister engine with the random seed
//            // Define a uniform distribution for integers between 0 and 9 (inclusive)
//            std::uniform_int_distribution<int> distribution(0, 999);
//            int randomNumber = distribution(engine);
//            int TR = val_arr[randomNumber];
//            resultArr.push_back(TR);
//        }
//        int value_retry = count(resultArr.begin(), resultArr.end(), 1);
//        int total = resultArr.size();
//        double percentage = (double(value_retry) / double(total)) * 100;
//        cout << "trial " << i+1 << "percentage " << percentage << endl;
//        outputFile << "trial " << i+1 << "percentage " << percentage << endl;
//    }
//	// Unmap the file and close the handles
//	UnmapViewOfFile(pBuffer);
//	CloseHandle(hFileMap);
//	CloseHandle(hFile);
//    outputFile.close();
//
//	return 0;
//}
//ORIGINAL DRAFT ENDS ------------------------------------------------------


// With Multithreading and optimizations------------------------------------------
void computeTrial(const double* pBuffer, int startRecord, int endRecord, map<double, double>& passMap, map<double, double>& retryMap, map<double, double>& failMap, double NF, double SD, int thread_id, vector<int> &resultArray);

int main()
{
    map<double, double> passMap;
    map<double, double> retryMap;
    map<double, double> failMap;

    passMap[13] = 0.1171;
    passMap[15] = 0.3033;
    passMap[16.5] = 0.4754;
    passMap[17.7] = 0.5205;
    passMap[19] = 0.6159;
    passMap[21] = 0.6388;

    retryMap[13] = 0.2559;
    retryMap[15] = 0.3595;
    retryMap[16.5] = 0.3349;
    retryMap[17.7] = 0.2992;
    retryMap[19] = 0.2670;
    retryMap[21] = 0.2313;

    failMap[13] = 0.6270;
    failMap[15] = 0.3361;
    failMap[16.5] = 0.1885;
    failMap[17.7] = 0.1803;
    failMap[19] = 0.1159;
    failMap[21] = 0.1288;
    
    	HANDLE hFile, hFileMap;
    	double* pBuffer = nullptr;
        //CHANGE INPUT FILE NAME HERE
    	// Open the file
    	hFile = CreateFile(TEXT("RetryAnalysis.sig"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    	if (hFile == INVALID_HANDLE_VALUE)
    	{
    		std::cout << "Failed to open the file." << std::endl;
    		return 1;
    	}
    
    	// Get the file size
    	DWORD nFileSize = GetFileSize(hFile, NULL);
    	if (nFileSize == INVALID_FILE_SIZE)
    	{
    		CloseHandle(hFile);
    		std::cout << "Failed to get the file size." << std::endl;
    		return 1;
    	}
    
    	// Create a file mapping object
    	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    	if (hFileMap == NULL)
    	{
    		CloseHandle(hFile);
    		std::cout << "Failed to create file mapping." << std::endl;
    		return 1;
    	}
    
    	// Map the file into memory
    	pBuffer = (double*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
    	if (pBuffer == NULL)
    	{
    		CloseHandle(hFileMap);
    		CloseHandle(hFile);
    		std::cout << "Failed to map the file into memory." << std::endl;
    		return 1;
    	}
    
        int no_of_trials;
        std::cout << "Enter number of trials: " << endl;
        std::cin >> no_of_trials;
        double NF;
        double SD;
        cout << "Enter noise floor: " << endl;
        cin >> NF;
        cout << "Enter standard deviation: " << endl;
        cin >> SD;
        string filename;
        string fileArray;
        std::cout << "Enter output file name for storing trial percentage: " << endl;
        cin.ignore();
        getline(cin, filename);
        if (filename == "default") {
            filename = "output.txt";
        }
        cout << "Enter output file name for storing array: " << endl;
        std::getline(std::cin >> std::ws, fileArray);
        if (fileArray == "default") {
            fileArray = "outputArray.txt";
        }
        fstream outputFile(filename, ios::app);
        if (!outputFile) {
            cerr << "Error opening the file." << endl;
            return 1;
        }
        ofstream outputArray(fileArray, ios::app);
        if (!outputArray) {
            cerr << "Error opening the file." << endl;
            return 1;
        }

    	// Now you can access the file content as a double array using pBuffer
    	//int nNumRecords = nFileSize / sizeof(double);
        int nNumRecords = 1000;
        int GCF = 1;
        for (int i = 1; i < 100; i++) {
            if (nNumRecords % i == 0) {
                GCF = i;
            }
        }
        int numThreads = 0;
        cout << "Enter number of threads of divisble by: "<< nNumRecords << endl;
        cin >> numThreads;
        if ((nNumRecords % numThreads) != 0 || numThreads > 100) {
            numThreads = GCF;
        }
        cout << "threads going to be used: " << numThreads << endl;
 
    int totalRecords = nNumRecords;
    int recordsPerThread = totalRecords / numThreads;
    vector<thread> threads;
    vector<double> threadResults(numThreads);
    vector<int> resultArray;
    for (int j = 0; j < no_of_trials; ++j) {
        threads.clear();
        resultArray.clear();
        for (int i = 0; i < numThreads; ++i) {
            int startRecord = i * recordsPerThread;
            int endRecord = (i + 1) * recordsPerThread;

            // Start a new thread for each workload
            threads.emplace_back([&pBuffer, startRecord, endRecord, &passMap, &retryMap, &failMap, NF, SD, &threadResults, i, &resultArray]() {
                    computeTrial(pBuffer, startRecord, endRecord, passMap, retryMap, failMap, NF, SD, i, resultArray);
                });
        }

        for (auto& thread : threads) {
            thread.join();//wait for all threads to finish
        }
        
        int value_retry = count(resultArray.begin(), resultArray.end(), 1);
        int value_fail = count(resultArray.begin(), resultArray.end(), 2);
        int total = resultArray.size();
        int retry_without_fail = total - value_fail;
        double percentage = (double(value_retry) / double(total)) * 100;
        double without_fail_percentage = (double(value_retry) / double(retry_without_fail)) * 100;
        cout << "trial " << j+1 << "percentage " << percentage << endl;
        cout << "trial " << j+1 << "percentage without fail " << without_fail_percentage << endl;
        outputFile << "trial " << j + 1 << "percentage " << percentage << endl;
        outputFile << "trial " << j + 1 << "percentage without fail " << without_fail_percentage << endl;
        outputFile << endl;
        for (int i = 0; i < resultArray.size(); ++i) {
            outputArray << resultArray[i];
        }
        outputArray << endl;
    }

    UnmapViewOfFile(pBuffer);
    CloseHandle(hFileMap);
    CloseHandle(hFile);
    outputFile.close();
    outputArray.close();
    return 0;
}

/* Each thread will call the compute trial function which passes in the value to the result array*/
void computeTrial(const double* pBuffer, int startRecord, int endRecord, map<double, double>& passMap, map<double, double>& retryMap, map<double, double>& failMap, double NF, double SD, int thread_id, vector<int> &resultArray)
{
    map<double, double>::iterator itlow, itup, findIt;
    for (int j = startRecord; j < endRecord; ++j) {
        double DV = pBuffer[j];
        {//guard used here to make sure cout statements are printed by each thread at a time
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "thread id " << thread_id << "Value at index " << j << ": " << DV << std::endl;
        }
        CRandom myObject;
        double AV = myObject.rand_normal(DV, SD);
        double CN = AV - NF;
        double pass_percentage, retry_percentage, fail_percentage;
        findIt = passMap.find(CN);
        if (findIt != passMap.end()) {//if the value exists in map return it
            pass_percentage = findIt->second;
            retry_percentage = retryMap[findIt->first];
            fail_percentage = failMap[findIt->first];
        }
        else if (CN <= 13) {// if value is lower than 13 bound it to 13
            pass_percentage = passMap[13];
            retry_percentage = retryMap[13];
            fail_percentage = failMap[13];
        }
        else if (CN >= 21) {//if value is greater than 21 bound it to 21
            pass_percentage = passMap[21];
            retry_percentage = retryMap[21];
            fail_percentage = failMap[21];
        }
        else if (CN > 13 && CN < 21) {
            itlow = passMap.lower_bound(CN);
            itup = passMap.upper_bound(CN);
            itlow--;
            pass_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
            itlow = retryMap.lower_bound(CN);
            itup = retryMap.upper_bound(CN);
            itlow--;
            retry_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
            itlow = failMap.lower_bound(CN);
            itup = failMap.upper_bound(CN);
            itlow--;
            fail_percentage = itlow->second + (itup->first - CN) * (itup->second - itlow->second) / (itup->first - itlow->first);
        }//if value is in between apporximate the value
        if ((fail_percentage * 1000 + retry_percentage * 1000 + pass_percentage * 1000) != 1000) {
            fail_percentage = fail_percentage * 1000;
            retry_percentage = retry_percentage * 1000;
            pass_percentage = pass_percentage * 1000;
            double ret = max(fail_percentage, retry_percentage);
            ret = max(ret, pass_percentage);//if value doesnt precisely equal a 1000
            if (ret == fail_percentage) {//find the max value and round up
                fail_percentage = ceil(fail_percentage);
            }
            if (ret == pass_percentage) {
                pass_percentage = ceil(pass_percentage);
            }
            if (ret == retry_percentage) {
                retry_percentage = ceil(retry_percentage);
            }
            if ((fail_percentage + retry_percentage + pass_percentage) != 1000) {
                double valDifference = (fail_percentage +
                    retry_percentage + pass_percentage) - 1000;
                valDifference = valDifference / 3;
                fail_percentage = fail_percentage - valDifference;
                pass_percentage = pass_percentage - valDifference;
                retry_percentage = retry_percentage - valDifference;
            }
        }// if it still doesn equal 1000, take the difference and subract evenly from all three values
        int val_arr[1000];
        //when converting from percentage to int, value indexes may not add up
        int numZeroes = static_cast<int>(pass_percentage);//so if they dont
        int numOnes = static_cast<int>(retry_percentage);
        int numTwos = static_cast<int>(fail_percentage);
        if ((numOnes + numZeroes + numTwos) != 1000) {
            int differVal = (numOnes + numZeroes + numTwos) - 1000;
            int ret = max(numOnes, numZeroes);
            ret = max(ret, numTwos);
            if (ret == numOnes) {
                numOnes = numOnes - differVal;
            }
            if (ret == numTwos) {
                numTwos = numTwos - differVal;
            }
            if (ret == numZeroes) {
                numZeroes = numZeroes - differVal;
            }
        }//bound it to 1000 by calculating the difference

        //SEQUENTIAL ARRAY FILLING ------------------
        /*int z = 0;
        for (z = 0; z < numZeroes; ++z) {
            val_arr[z] = 0;
        }
        int count = numOnes + z;
        for (;z < count; ++z) {
            val_arr[z] = 1;
        }
        count = numTwos + z;
        for (; z < count; ++z) {
            val_arr[z] = 2;
        }*/

        //Random index filling
        for (int k = 0; k < 1000; ++k) {
            if (numOnes > 0 && numTwos > 0 && numZeroes > 0) {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> distribution(0, 2);
                int randomNumber = distribution(engine);
                val_arr[k] = randomNumber;
            }
            if (numOnes > 0 && numTwos > 0 && numZeroes <= 0) {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> distribution(1, 2);
                int randomNumber = distribution(engine);
                val_arr[k] = randomNumber;
            }
            if (numOnes > 0 && numTwos <= 0 && numZeroes > 0) {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> distribution(0, 1);
                int randomNumber = distribution(engine);
                val_arr[k] = randomNumber;
            }
            if (numOnes <= 0 && numTwos > 0 && numZeroes > 0) {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> distribution(0, 1);
                int randomNumber = distribution(engine) * 2;
                val_arr[k] = randomNumber;
            }
            if (numOnes <= 0 && numTwos <= 0 && numZeroes > 0) {
                val_arr[k] = 0;
            }
            if (numOnes > 0 && numTwos <= 0 && numZeroes <= 0) {
                val_arr[k] = 1;
            }
            if (numOnes <= 0 && numTwos > 0 && numZeroes <= 0) {
                val_arr[k] = 2;
            }
        }
        std::random_device rd; // Obtain a random seed from the hardware
        std::mt19937 engine(rd()); // Use the Mersenne Twister engine with the random seed
        // Define a uniform distribution for integers between 0 and 9 (inclusive)
        std::uniform_int_distribution<int> distribution(0, 999);
        int randomNumber = distribution(engine);
        int TR = val_arr[randomNumber];
        resultArray.push_back(TR);

    }
}