#include <iostream>
#include <sstream>
#include <string>
#include "QS.h"
using namespace std;



void QS::sort(int left, int right) {
	if ((right - left) < 1) { // everything on the left is smaller than the thing on the right
			return;               // pivot is next to left or right
	}												

	int pivot = medianOfThree(left, right);
	pivot = partition(left, right, pivot);			
	sort(left , pivot - 1); // sort from pivot to left
	sort(pivot + 1, right); // sort from puvot to right

	return;
}
	/*
	* sortAll()
	*
	* Sorts elements of the array.  After this function is called, every
	* element in the array is less than or equal its successor.
	*
	* Does nothing if the array is empty.
	*/
	void QS::sortAll() {
		if (valueSize == 0) {
			return;
		}
		sort(0, valueSize - 1);

		return;
	}

	/*
	* medianOfThree()
	*
	* The median of three pivot selection has two parts:
	*
	* 1) Calculates the middle index by averaging the given left and right indices:
	*
	* middle = (left + right)/2
	*
	* 2) Then bubble-sorts the values at the left, middle, and right indices.
	*
	* After this method is called, data[left] <= data[middle] <= data[right].
	* The middle index will be returned.
	*
	* Returns -1 if the array is empty, if either of the given integers
	* is out of bounds, or if the left index is not less than the right
	* index.
	*
	* @param left
	* 		the left boundary for the subarray from which to find a pivot
	* @param right
	* 		the right boundary for the subarray from which to find a pivot
	* @return
	*		the index of the pivot (middle index); -1 if provided with invalid input
	*/
	int QS::medianOfThree(int left, int right) {
		if (left >= right || valueSize == 0 || left < 0 || right < 0 || (right >= valueSize)) {
			return -1;
		}

		int middle;
		middle = (left + right)/2;

		if (myArray[left] > myArray[middle]) {
			int temp;
			temp = myArray[left];
			myArray[left] = myArray[middle];
			myArray[middle] = temp;
			// cout << left << middle << " next ";
		}
		if (myArray[right] < myArray[middle]) {
			int temp1;
			temp1 = myArray[right];
			myArray[right] = myArray[middle];
			myArray[middle] = temp1;
			// cout << myArray[right] << myArray[middle] << " next ";
		}
		if (myArray[middle] < myArray[left]) {
			int temp2;
			temp2 = myArray[left];
			myArray[left] = myArray[middle];
			myArray[middle] = temp2;
			// cout << left << middle << " next ";
		}

		return middle;
	}

	/*
	* Partitions a subarray around a pivot value selected according to
	* median-of-three pivot selection.  Because there are multiple ways to partition a list,
	* we will follow the algorithm on page 611 of the course text when testing this function.
	*
	* The values which are smaller than the pivot should be placed to the left
	* of the pivot; the values which are larger than the pivot should be placed
	* to the right of the pivot.
	*
	* Returns -1 if the array is null, if either of the given integers is out of
	* bounds, or if the first integer is not less than the second integer, or if the
	* pivot is not within the sub-array designated by left and right.
	*
	* @param left
	* 		the left boundary for the subarray to partition
	* @param right
	* 		the right boundary for the subarray to partition
	* @param pivotIndex
	* 		the index of the pivot in the subarray
	* @return
	*		the pivot's ending index after the partition completes; -1 if
	* 		provided with bad input
	*/
	int QS::partition(int left, int right, int pivotIndex) {
		if (left >= right || valueSize == 0 || left < 0 || right < 0 
		|| (right >= valueSize) || (pivotIndex > right)) {
			return -1;
		}

		int temp = myArray[pivotIndex];
		myArray[pivotIndex] = myArray[left];
		myArray[left] = temp;
		int up = left + 1;
		int down = right;

		do {
			/* All items in myArray[first] through myArray[up - 1] <= myArray[first] 
				 All items in myArray[down + 1] through myArray[last - 1] > myArray[first]
			*/
			while ((myArray[up] <= myArray[left]) && (up < right)) {
				up++; // Assert: up equals last - 1 or myArray[up] > myArray[left]
			}
			while ((myArray[down] > myArray[left]) && (down > left)) {
				down--; // Assert: down equals first or myArray[down] <= myArray[left]
			}
			if (up < down) { // if up is to the left of down (myArray[up] > myArray[down])(always by the while loop)
				int temp1;
				temp1 = myArray[up];
				myArray[up] = myArray[down];
				myArray[down] = temp1; 
			}
		}while (up < down);

		// Exchange myArray[left] and myArray[down] thus putting the (myArray[down] < myArray[left])
		// pivot value where it belongs. 
		// Return position of pivot
		int temp2 = myArray[left];
		myArray[left] = myArray[down];
		myArray[down] = temp2; 

		return down;
	}

	/*
	* Produces a comma delimited string representation of the array. For example: if my array
	* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
	* with no trailing comma.  The number of cells included equals the number of values added.
	* Do not include the entire array if the array has yet to be filled.
	*
	* Returns an empty string, if the array is NULL or empty.
	*
	* @return
	*		the string representation of the current array
	*/
	string QS::getArray() const {
		string temp = "";

		if (myArray == NULL) {
			return temp;
		}

		stringstream ss;

		for (int i = 0; i < valueSize; ++i) {
			if(i == (valueSize - 1)) {
				ss << myArray[i];
				// temp.append(arrayValue);
				break;
			}
			ss << myArray[i] << ",";
			}
		
		temp = ss.str();
		// cout << temp;
		
		return temp;
	}

	/*
	* Returns the number of elements which have been added to the array.
	*/
	int QS::getSize() const {
		return valueSize;
	}

	/*
	* Adds the given value to the end of the array starting at index 0.
	* For example, the first time addToArray is called,
	* the give value should be found at index 0.
	* 2nd time, value should be found at index 1.
	* 3rd, index 2, etc up to its max capacity.
	*
	* If the array is filled, do nothing.
	* returns true if a value was added, false otherwise.
	*/
	bool QS::addToArray(int value) {
		if (valueSize == myArrayLength) {
			return false;
		}
		if (myArray != NULL) {
				myArray[valueSize] = value;
				// cout << "haha" << myArray[valueSize] << endl;
				valueSize++; // Count how many number added to the array
		}

				return true;
	}

	/*
	* Dynamically allocates an array with the given capacity.
	* If a previous array had been allocated, delete the previous array.
	* Returns false if the given capacity is non-positive, true otherwise.
	*
	* @param
	*		size of array
	* @return
	*		true if the array was created, false otherwise
	*/
	bool QS::createArray(int capacity) {
		if (capacity <= 0) {
			return false;
		}

		myArrayLength = capacity;
		// cout << "array length" << myArrayLength << endl;

		delete [] myArray;
		myArray = new int[capacity];
		valueSize = 0; // reset what has been add to the array

		for (int i = 0; i < myArrayLength; ++i) {
			myArray[i] = -9999;
		}

	return true;
	}

	/*
	* Resets the array to an empty or NULL state.
	*/
	void QS::clear() {
		if (myArray == NULL) {
			return;
		}
		
		delete [] myArray;
		myArray = 0;

		valueSize = 0;

		return;
	}