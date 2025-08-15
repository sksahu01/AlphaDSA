#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

void printArray(const vector<int>& arr, const string& title) {
    cout << title << ": ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// ==========================================================================
// 1. BUBBLE SORT - O(n²) Time, O(1) Space
// Simple comparison-based algorithm, good for educational purposes
// ==========================================================================

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        // Last i elements are already sorted
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no swapping occurred, array is sorted
        if (!swapped) break;
    }
}

// ==========================================================================
// 2. SELECTION SORT - O(n²) Time, O(1) Space
// Finds minimum element and places it at the beginning
// ==========================================================================

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        // Find the minimum element in remaining array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap the found minimum element with first element
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ==========================================================================
// 3. INSERTION SORT - O(n²) Time, O(1) Space
// Builds sorted array one element at a time, good for small arrays
// ==========================================================================

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// ==========================================================================
// 4. MERGE SORT - O(n log n) Time, O(n) Space
// Divide and conquer algorithm, stable sorting
// ==========================================================================

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    vector<int> leftArr(n1), rightArr(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// ==========================================================================
// 5. QUICK SORT - O(n log n) Average, O(n²) Worst, O(log n) Space
// Divide and conquer, in-place sorting, not stable
// Multiple implementations with different pivot strategies
// ==========================================================================

// 5A. STANDARD QUICK SORT (Last element as pivot)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1; // Index of smaller element
    
    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// 5B. QUICK SORT WITH RANDOM PIVOT (Better average performance)
int partitionRandom(vector<int>& arr, int low, int high) {
    // Generate random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); // Move random element to end
    
    return partition(arr, low, high); // Use standard partition
}

void quickSortRandomHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandom(arr, low, high);
        
        quickSortRandomHelper(arr, low, pi - 1);
        quickSortRandomHelper(arr, pi + 1, high);
    }
}

void quickSortRandom(vector<int>& arr) {
    srand(time(nullptr)); // Initialize random seed
    quickSortRandomHelper(arr, 0, arr.size() - 1);
}

// 5C. QUICK SORT WITH MEDIAN-OF-THREE PIVOT (Improved worst-case)
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[mid] < arr[low])
        swap(arr[mid], arr[low]);
    if (arr[high] < arr[low])
        swap(arr[high], arr[low]);
    if (arr[high] < arr[mid])
        swap(arr[high], arr[mid]);
    
    return mid;
}

int partitionMedian(vector<int>& arr, int low, int high) {
    int medianIndex = medianOfThree(arr, low, high);
    swap(arr[medianIndex], arr[high]); // Move median to end
    
    return partition(arr, low, high);
}

void quickSortMedianHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionMedian(arr, low, high);
        
        quickSortMedianHelper(arr, low, pi - 1);
        quickSortMedianHelper(arr, pi + 1, high);
    }
}

void quickSortMedian(vector<int>& arr) {
    quickSortMedianHelper(arr, 0, arr.size() - 1);
}

// 5D. ITERATIVE QUICK SORT (No recursion - uses stack)
void quickSortIterative(vector<int>& arr) {
    if (arr.size() <= 1) return;
    
    // Create auxiliary stack
    stack<pair<int, int>> st;
    st.push({0, (int)arr.size() - 1});
    
    while (!st.empty()) {
        int high = st.top().second;
        int low = st.top().first;
        st.pop();
        
        if (low < high) {
            int pi = partition(arr, low, high);
            
            // Push left and right subarrays
            st.push({low, pi - 1});
            st.push({pi + 1, high});
        }
    }
}

// 5E. THREE-WAY QUICK SORT (Handles duplicates efficiently)
void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int pivot = arr[low];
    int i = low + 1;
    lt = low;
    gt = high;
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
}

void quickSort3WayHelper(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    
    int lt, gt;
    threeWayPartition(arr, low, high, lt, gt);
    
    quickSort3WayHelper(arr, low, lt - 1);
    quickSort3WayHelper(arr, gt + 1, high);
}

void quickSort3Way(vector<int>& arr) {
    quickSort3WayHelper(arr, 0, arr.size() - 1);
}

// ==========================================================================
// 6. HEAP SORT - O(n log n) Time, O(1) Space
// Uses binary heap data structure, not stable
// ==========================================================================

void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Move current root to end
        heapify(arr, i, 0); // Call heapify on reduced heap
    }
}

// ==========================================================================
// 7. COUNTING SORT - O(n + k) Time, O(k) Space
// Non-comparison based, works when range of elements is known
// ==========================================================================

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find the maximum element to determine range
    int maxElement = *max_element(arr.begin(), arr.end());
    int minElement = *min_element(arr.begin(), arr.end());
    int range = maxElement - minElement + 1;
    
    // Create count array
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    // Store count of each element
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - minElement]++;
    
    // Change count[i] to actual position
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];
    
    // Build output array
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minElement] - 1] = arr[i];
        count[arr[i] - minElement]--;
    }
    
    // Copy output array to original array
    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}

// ==========================================================================
// 8. RADIX SORT - O(d * (n + k)) Time, O(n + k) Space
// Non-comparison based, sorts by individual digits
// ==========================================================================

int getMax(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    
    // Store count of occurrences
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    // Change count[i] to actual position
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copy output array to arr
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int maxNum = getMax(arr);
    
    // Do counting sort for every digit
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}

// ==========================================================================
// 9. BUCKET SORT - O(n + k) Average, O(n²) Worst, O(n + k) Space
// Distributes elements into buckets and sorts individually
// ==========================================================================

void bucketSort(vector<float>& arr) {
    if (arr.empty()) return;
    
    int n = arr.size();
    
    // Create n empty buckets
    vector<vector<float>> buckets(n);
    
    // Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Assuming arr[i] is between 0 and 1
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (float value : buckets[i]) {
            arr[index++] = value;
        }
    }
}

// ==========================================================================
// 10. SHELL SORT - O(n log n) to O(n²) Time, O(1) Space
// Improved insertion sort with gap sequence
// ==========================================================================

void shellSort(vector<int>& arr) {
    int n = arr.size();
    
    // Start with big gap, then reduce gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do gapped insertion sort
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            // Shift earlier gap-sorted elements up
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            arr[j] = temp;
        }
    }
}

// ==========================================================================
// 11. COCKTAIL SHAKER SORT - O(n²) Time, O(1) Space
// Bidirectional bubble sort
// ==========================================================================

void cocktailShakerSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    
    while (swapped) {
        swapped = false;
        
        // Forward pass
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
        
        end--;
        swapped = false;
        
        // Backward pass
        for (int i = end; i > start; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        
        start++;
    }
}

// ==========================================================================
// 12. COMB SORT - O(n log n) Average, O(n²) Worst, O(1) Space
// Improved bubble sort with shrinking gap
// ==========================================================================

void combSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n;
    bool swapped = true;
    
    while (gap != 1 || swapped) {
        // Find next gap
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        swapped = false;
        
        // Compare all elements with current gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// ==========================================================================
// MAIN FUNCTION - TESTING ALL SORTING ALGORITHMS
// ==========================================================================

int main() {
    // Test data
    vector<int> originalArr = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    
    cout << "SORTING ALGORITHMS DEMONSTRATION" << endl;
    cout << "================================" << endl;
    cout << "Total algorithms implemented: 11" << endl;
    cout << "Array size: " << originalArr.size() << " elements" << endl;
    
    printArray(originalArr, "Original Array");
    cout << "\n" << string(60, '-') << endl;
    
    // Test each sorting algorithm
    vector<int> arr;
    
    // 1. Bubble Sort
    cout << "\n1. BUBBLE SORT" << endl;
    cout << "   Time: O(n²), Space: O(1), Stable: Yes" << endl;
    arr = originalArr;
    bubbleSort(arr);
    printArray(arr, "   Result");
    
    // 2. Selection Sort
    cout << "\n2. SELECTION SORT" << endl;
    cout << "   Time: O(n²), Space: O(1), Stable: No" << endl;
    arr = originalArr;
    selectionSort(arr);
    printArray(arr, "   Result");
    
    // 3. Insertion Sort
    cout << "\n3. INSERTION SORT" << endl;
    cout << "   Time: O(n²), Space: O(1), Stable: Yes" << endl;
    arr = originalArr;
    insertionSort(arr);
    printArray(arr, "   Result");
    
    // 4. Merge Sort
    cout << "\n4. MERGE SORT" << endl;
    cout << "   Time: O(n log n), Space: O(n), Stable: Yes" << endl;
    arr = originalArr;
    mergeSort(arr);
    printArray(arr, "   Result");
    
    // 5. Quick Sort (Multiple Variations)
    cout << "\n5. QUICK SORT VARIATIONS" << endl;
    cout << "    Time: O(n log n) avg, O(n²) worst, Space: O(log n), Stable: No" << endl;
    cout << "    Most important algorithm for coding interviews!" << endl;
    
    // Standard Quick Sort
    arr = originalArr;
    quickSort(arr);
    printArray(arr, "   5A. Standard Quick Sort (last pivot)");
    
    // Random Pivot Quick Sort
    arr = originalArr;
    quickSortRandom(arr);
    printArray(arr, "   5B. Random Pivot Quick Sort");
    
    // Median-of-Three Quick Sort
    arr = originalArr;
    quickSortMedian(arr);
    printArray(arr, "   5C. Median-of-Three Quick Sort");
    
    // Iterative Quick Sort
    arr = originalArr;
    quickSortIterative(arr);
    printArray(arr, "   5D. Iterative Quick Sort (no recursion)");
    
    // Three-way Quick Sort (good for duplicates)
    vector<int> duplicateArr = {5, 2, 8, 2, 9, 1, 5, 5, 2};
    cout << "   Testing 3-Way Quick Sort with duplicates: ";
    for (int x : duplicateArr) cout << x << " ";
    cout << endl;
    quickSort3Way(duplicateArr);
    printArray(duplicateArr, "   5E. Three-Way Quick Sort");
    
    // 6. Heap Sort
    cout << "\n6. HEAP SORT" << endl;
    cout << "   Time: O(n log n), Space: O(1), Stable: No" << endl;
    arr = originalArr;
    heapSort(arr);
    printArray(arr, "   Result");
    
    // 7. Counting Sort (only for non-negative integers)
    cout << "\n7. COUNTING SORT" << endl;
    cout << "   Time: O(n + k), Space: O(k), Stable: Yes" << endl;
    cout << "   Note: Works best with small range of integers" << endl;
    vector<int> positiveArr = {4, 2, 2, 8, 3, 3, 1};
    cout << "   Input : ";
    for (int x : positiveArr) cout << x << " ";
    cout << endl;
    countingSort(positiveArr);
    printArray(positiveArr, "   Result");
    
    // 8. Radix Sort (only for non-negative integers)
    cout << "\n8. RADIX SORT" << endl;
    cout << "   Time: O(d * (n + k)), Space: O(n + k), Stable: Yes" << endl;
    cout << "   Note: d = number of digits, k = range of digits (0-9)" << endl;
    vector<int> radixArr = {170, 45, 75, 90, 2, 802, 24, 66};
    cout << "   Input : ";
    for (int x : radixArr) cout << x << " ";
    cout << endl;
    radixSort(radixArr);
    printArray(radixArr, "   Result");
    
    // 9. Shell Sort
    cout << "\n9. SHELL SORT" << endl;
    cout << "   Time: O(n log n) to O(n²), Space: O(1), Stable: No" << endl;
    arr = originalArr;
    shellSort(arr);
    printArray(arr, "   Result");
    
    // 10. Cocktail Shaker Sort
    cout << "\n10. COCKTAIL SHAKER SORT" << endl;
    cout << "    Time: O(n²), Space: O(1), Stable: Yes" << endl;
    arr = originalArr;
    cocktailShakerSort(arr);
    printArray(arr, "    Result");
    
    // 11. Comb Sort
    cout << "\n11. COMB SORT" << endl;
    cout << "    Time: O(n log n) avg, O(n²) worst, Space: O(1), Stable: No" << endl;
    arr = originalArr;
    combSort(arr);
    printArray(arr, "    Result");
    
    cout << "\n" << string(60, '=') << endl;
    cout << "ALGORITHM COMPARISON SUMMARY" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nBest for interviews:" << endl;
    cout << "• Quick Sort - Most commonly asked" << endl;
    cout << "• Merge Sort - Guaranteed O(n log n)" << endl;
    cout << "• Heap Sort - In-place O(n log n)" << endl;
    
    cout << "\nBest for specific cases:" << endl;
    cout << "• Insertion Sort - Small arrays or nearly sorted" << endl;
    cout << "• Counting Sort - Small range of integers" << endl;
    cout << "• Radix Sort - Large integers with fixed digits" << endl;
    
    cout << "\nTime Complexity Comparison:" << endl;
    cout << "┌─────────────────────┬─────────────┬─────────────┬─────────────┐" << endl;
    cout << "│ Algorithm           │ Best Case   │ Average     │ Worst Case  │" << endl;
    cout << "├─────────────────────┼─────────────┼─────────────┼─────────────┤" << endl;
    cout << "│ Bubble Sort         │ O(n)        │ O(n²)       │ O(n²)       │" << endl;
    cout << "│ Selection Sort      │ O(n²)       │ O(n²)       │ O(n²)       │" << endl;
    cout << "│ Insertion Sort      │ O(n)        │ O(n²)       │ O(n²)       │" << endl;
    cout << "│ Merge Sort          │ O(n log n)  │ O(n log n)  │ O(n log n)  │" << endl;
    cout << "│ Quick Sort          │ O(n log n)  │ O(n log n)  │ O(n²)       │" << endl;
    cout << "│ Heap Sort           │ O(n log n)  │ O(n log n)  │ O(n log n)  │" << endl;
    cout << "│ Counting Sort       │ O(n + k)    │ O(n + k)    │ O(n + k)    │" << endl;
    cout << "│ Radix Sort          │ O(nk)       │ O(nk)       │ O(nk)       │" << endl;
    cout << "│ Shell Sort          │ O(n log n)  │ O(n^1.25)   │ O(n²)       │" << endl;
    cout << "│ Cocktail Sort       │ O(n)        │ O(n²)       │ O(n²)       │" << endl;
    cout << "│ Comb Sort           │ O(n log n)  │ O(n²/2^p)   │ O(n²)       │" << endl;
    cout << "└─────────────────────┴─────────────┴─────────────┴─────────────┘" << endl;
    
    cout << "\nSpace Complexity:" << endl;
    cout << "• O(1): Bubble, Selection, Insertion, Heap, Shell, Cocktail, Comb" << endl;
    cout << "• O(log n): Quick Sort (recursion stack)" << endl;
    cout << "• O(n): Merge Sort" << endl;
    cout << "• O(k): Counting Sort (k = range of input)" << endl;
    cout << "• O(n + k): Radix Sort" << endl;
    
    cout << "\nStability (maintains relative order of equal elements):" << endl;
    cout << "• Stable: Bubble, Insertion, Merge, Counting, Radix, Cocktail" << endl;
    cout << "• Not Stable: Selection, Quick, Heap, Shell, Comb" << endl;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "Program executed successfully!" << endl;
    cout << "All " << 11 << " sorting algorithms implemented and tested." << endl;
    
    return 0;
}
