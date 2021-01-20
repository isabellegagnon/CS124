//Isabelle Gagnon
using namespace std;
#include <iostream>
#include <vector>
#include "Coronavirus.h"

//Open the file and read to vector
void readToVector(vector<Coronavirus> &covidVector) {
    string dataFileName = "../CovidDataset.csv";
    ifstream inFile(dataFileName);

    //Initialize variables
    if (inFile) {
        string continent;
        double total_cases;
        double total_deaths;
        double total_tests_per_thousand;
        double population;
        char comma;

        //Create Coronavirus object to put in vector
        Coronavirus covid(continent, total_cases, total_deaths, total_tests_per_thousand, population);
        covidVector.push_back(covid);

        //Only read first 1000 lines
        for (int i = 0; i < 1000; ++i) {
            inFile >> total_cases >> comma;
            getline(inFile, continent, comma);
            inFile >> total_deaths >> comma;
            inFile >> total_tests_per_thousand >> comma;
            inFile >> population >> comma;
            if (!inFile) {
                inFile.clear();
            }
        }
        inFile.close();
    } else {
        cout << "Can't Open "<< dataFileName << endl;
    }
}

//
void addFromVector(vector<Coronavirus> &covidVectorResized, int num, const vector<Coronavirus> &covidVector) {
    covidVectorResized.clear();
    for (int i = 0; i < num; ++i) {
        covidVectorResized.push_back(covidVector[i]);
    }
}

void mergeSort ( vector<Coronavirus> & a, int &mergeSort, int &mergeSortWrites);
void mergeSort( vector<Coronavirus> & a, vector<Coronavirus> & temporaryArray, int left, int right, int &mergeSortReads, int &mergeSortWrites );
void merge( vector<Coronavirus> & a, vector<Coronavirus> & temporaryArray, int leftPosition, int rightPosition, int rightEnd, int &mergeSortReads, int &mergeSortWrites );
void percDown( vector<Coronavirus> & a, int, int n, int &heapSortReads, int &heapSortWrites );


//Bubble Sort

void bubbleSort(vector<Coronavirus> &vec, int &bubbleSortReads, int &bubbleSortWrites) {
    bool swapped = true;
    int lastIndex = vec.size();
    while (swapped) {
        swapped = false;
        for (int i = 0; i + 1 < lastIndex; ++i) {
            bubbleSortReads += 2;
            if (vec[i] > vec[i + 1]) {
                ++bubbleSortReads;
                Coronavirus temp = vec[i];
                ++bubbleSortWrites;
                ++bubbleSortReads;
                vec[i] = vec[i + 1];
                ++bubbleSortWrites;
                ++bubbleSortReads;
                vec[i + 1] = temp;
                swapped = true;
            }
        }
        --lastIndex;
    }
}

//Insertion Sort

void insertionSort(vector<Coronavirus> &vec, int &insertionSortReads, int &insertionSortWrites) {
    for (int currentIndex = 1; currentIndex < vec.size(); ++currentIndex) {
        ++insertionSortReads;
        Coronavirus toBeInserted = vec[currentIndex];
        int sortedIndex = currentIndex - 1;
        while (sortedIndex >= 0 && toBeInserted < vec[sortedIndex]) {
            ++insertionSortReads;
            ++insertionSortWrites;
            ++insertionSortReads;
            vec[sortedIndex + 1] = vec[sortedIndex];
            --sortedIndex;
        }
        ++insertionSortWrites;
        vec[sortedIndex + 1] = toBeInserted;
    }
}

//Mergesort

void mergeSort( vector<Coronavirus> & a, int &mergeSortReads, int &mergeSortWrites ) {
    vector<Coronavirus> tmpArray( a.size( ) );
    mergeSort(a, tmpArray, 0, (a.size( ) - 1), mergeSortReads, mergeSortWrites);
}

void mergeSort( vector<Coronavirus> & a, vector<Coronavirus> & temporaryArray, int left, int right, int &mergeSortReads, int &mergeSortWrites ) {
    if( left < right ) {
        int center = ( left + right ) / 2;
        mergeSort( a, temporaryArray, left, center, mergeSortReads, mergeSortWrites );
        mergeSort( a, temporaryArray, center + 1, right, mergeSortReads, mergeSortWrites );
        merge( a, temporaryArray, left, center + 1, right, mergeSortReads, mergeSortWrites );
    }
}

void merge( vector<Coronavirus> & a, vector<Coronavirus> & temporaryArray, int leftPosition, int rightPosition, int rightEnd, int &mergeSortReads, int &mergeSortWrites ) {
    int leftEnd = rightPosition - 1;
    int temporaryPosition = leftPosition;
    int numElements = rightEnd - leftPosition + 1;

    while( leftPosition <= leftEnd && rightPosition <= rightEnd ) {
        mergeSortReads += 2;
        if (leftPosition <= rightPosition) {
            ++mergeSortReads;
            temporaryArray[temporaryPosition++] = move(a[leftPosition++]);
        } else {
            ++mergeSortReads;
            temporaryArray[temporaryPosition++] = move(a[rightPosition++]);
        }
    }

    while( leftPosition <= leftEnd ) {
        ++mergeSortReads;
        temporaryArray[temporaryPosition++] = move(a[leftPosition++]);
    }

    while( rightPosition <= rightEnd ) {
        ++mergeSortReads;
        temporaryArray[temporaryPosition++] = move(a[rightPosition++]);
    }

    for( int i = 0; i < numElements; ++i, --rightEnd ) {
        ++mergeSortWrites;
        a[rightEnd] = move(temporaryArray[rightEnd]);
    }
}


//HeapSort
void heapSort( vector<Coronavirus> & a, int &heapSortReads, int &heapSortWrites )
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ), heapSortReads, heapSortWrites );
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        heapSortReads += 2;
        heapSortWrites += 2;
        swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j, heapSortReads, heapSortWrites );
    }
}

inline int leftChild( int i )
{
    return 2 * i + 1;
}

void percDown( vector<Coronavirus> & a, int i, int n, int &heapSortReads, int &heapSortWrites )
{
    int child;
    Coronavirus temporary;

    for( temporary = move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        ++heapSortReads;
        child = leftChild( i );
        heapSortReads += 2;
        if( child != n - 1 && a[ child ] < a[ child + 1 ] ) {
            ++child;
        }
        ++heapSortReads;
        if( temporary < a[ child ] ) {
            ++heapSortReads;
            ++heapSortWrites;
            a[i] = move(a[child]);
        }
        else
            break;
    }
    ++heapSortWrites;
    a[ i ] = move( temporary );
}


//TwoSort

void bubbleSortByName(vector<Coronavirus> &vec, int &twoSortReads, int &twoSortWrites) {
    bool swapped = true;
    int lastIndex = vec.size();
    while (swapped) {
        swapped = false;
        for (int i = 0; i + 1 < lastIndex; ++i) {
            twoSortReads += 2;
            if (vec[i].getContinent() > vec[i + 1].getContinent()) {
                ++twoSortReads;
                Coronavirus temporary = vec[i];
                ++twoSortWrites;
                ++twoSortReads;
                vec[i] = vec[i + 1];
                ++twoSortWrites;
                ++twoSortReads;
                vec[i + 1] = temporary;
                swapped = true;
            }
        }
        --lastIndex;
    }
}


int main() {
    //Read 1000 objects to vector.
    vector<Coronavirus> covidVector;
    readToVector(covidVector);

    vector<Coronavirus> covidVectorResized;

    //Initialize all variables
    int insertionSortReads;
    int insertionSortWrites;

    int mergeSortReads;
    int mergeSortWrites;

    int bubbleSortReads;
    int bubbleSortWrites;

    int heapSortReads;
    int heapSortWrites;

    int twoSortReads;
    int twoSortWrites;

    for (int i = 100; i <= 1000; i += 100) {

        cout << "\n================================{SORTING VECTOR OF " << i << " COVID OBJECTS}======================================\n" << endl;

        //Bubble Sort
        addFromVector(covidVectorResized, i, covidVector);

        bubbleSortReads = 0;
        bubbleSortWrites = 0;

        bubbleSort(covidVectorResized, bubbleSortReads, bubbleSortWrites);

        cout << "Bubble Sort Reads: " << bubbleSortReads << endl;
        cout << "Bubble Sort Writes: " << bubbleSortWrites << endl << endl;

        //Insertion Sort
        addFromVector(covidVectorResized, i, covidVector);

        insertionSortReads = 0;
        insertionSortWrites = 0;

        insertionSort(covidVectorResized, insertionSortReads, insertionSortWrites);

        cout << "Insertion Sort Reads: " << insertionSortReads << endl;
        cout << "Insertion Sort Writes: " << insertionSortWrites << endl << endl;

        //Merge Sort
        addFromVector(covidVectorResized, i, covidVector);

        mergeSortReads = 0;
        mergeSortWrites = 0;

        mergeSort(covidVectorResized, mergeSortReads, mergeSortWrites);

        cout << "Merge Sort Reads: " << mergeSortReads << endl;
        cout << "Merge Sort Writes: " << mergeSortWrites << endl << endl;

        //Heap Sort
        addFromVector(covidVectorResized, i, covidVector);

        heapSortReads = 0;
        heapSortWrites = 0;

        heapSort(covidVectorResized, heapSortReads, heapSortWrites);

        cout << "Heap Sort Reads: " << heapSortReads << endl;
        cout << "Heap Sort Writes: " << heapSortWrites << endl << endl;

        //Two-Sort
        addFromVector(covidVectorResized, i, covidVector);

        twoSortReads = 0;
        twoSortWrites = 0;

        insertionSort(covidVectorResized, twoSortReads, twoSortWrites);
        bubbleSortByName(covidVectorResized, twoSortReads, twoSortWrites);

        cout << "Two Sort Reads: " << twoSortReads << endl;
        cout << "Two Sort Writes: " << twoSortWrites << endl;

    }
    return 0;
}
