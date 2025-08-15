#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
using namespace std;

void printArray(const vector<int>& arr, const string& title) {
    cout << title << ": ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void printResult(const string& algorithm, int target, int result, int comparisons = -1) {
    cout << "   Searching for " << target << ": ";
    if (result != -1) {
        cout << "Found at index " << result;
        if (comparisons != -1) cout << " (Comparisons: " << comparisons << ")";
    } else {
        cout << "Not found";
        if (comparisons != -1) cout << " (Comparisons: " << comparisons << ")";
    }
    cout << endl;
}

// ==========================================================================
// 1. LINEAR SEARCH - O(n) Time, O(1) Space
// Sequential search through array, works on unsorted data
// ==========================================================================

int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Not found
}

// Linear Search with comparison count
int linearSearchWithCount(vector<int>& arr, int target, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Linear Search - Find all occurrences
vector<int> linearSearchAll(vector<int>& arr, int target) {
    vector<int> indices;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            indices.push_back(i);
        }
    }
    return indices;
}

// ==========================================================================
// 2. BINARY SEARCH - O(log n) Time, O(1) Space
// Works only on sorted arrays, divides search space in half
// ==========================================================================

int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

// Binary Search with comparison count
int binarySearchWithCount(vector<int>& arr, int target, int& comparisons) {
    int left = 0, right = arr.size() - 1;
    comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Binary Search - Recursive Implementation
int binarySearchRecursive(vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }
    
    if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

int binarySearchRecursiveWrapper(vector<int>& arr, int target) {
    return binarySearchRecursive(arr, target, 0, arr.size() - 1);
}

// ==========================================================================
// 3. BINARY SEARCH VARIATIONS - First and Last Occurrence
// Find boundaries in sorted array with duplicates
// ==========================================================================

// Find first occurrence of target
int findFirst(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Continue searching left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find last occurrence of target
int findLast(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Continue searching right
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Count occurrences using first and last
int countOccurrences(vector<int>& arr, int target) {
    int first = findFirst(arr, target);
    if (first == -1) return 0;
    
    int last = findLast(arr, target);
    return last - first + 1;
}

// ==========================================================================
// 4. TERNARY SEARCH - O(log₃ n) Time, O(1) Space
// Divides search space into three parts, works on sorted arrays
// ==========================================================================

int ternarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] == target) {
            return mid1;
        }
        if (arr[mid2] == target) {
            return mid2;
        }
        
        if (target < arr[mid1]) {
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    
    return -1;
}

// Ternary Search with comparison count
int ternarySearchWithCount(vector<int>& arr, int target, int& comparisons) {
    int left = 0, right = arr.size() - 1;
    comparisons = 0;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        comparisons++;
        if (arr[mid1] == target) {
            return mid1;
        }
        
        comparisons++;
        if (arr[mid2] == target) {
            return mid2;
        }
        
        comparisons++;
        if (target < arr[mid1]) {
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    
    return -1;
}

// ==========================================================================
// 5. JUMP SEARCH - O(√n) Time, O(1) Space
// Jumps ahead by fixed steps, then linear search in block
// ==========================================================================

int jumpSearch(vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    
    // Find the block where element is present
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }
    
    // Linear search in the identified block
    while (arr[prev] < target) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }
    
    if (arr[prev] == target) {
        return prev;
    }
    
    return -1;
}

// Jump Search with comparison count
int jumpSearchWithCount(vector<int>& arr, int target, int& comparisons) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    comparisons = 0;
    
    // Find the block where element is present
    while (arr[min(step, n) - 1] < target) {
        comparisons++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }
    
    // Linear search in the identified block
    while (arr[prev] < target) {
        comparisons++;
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }
    
    comparisons++;
    if (arr[prev] == target) {
        return prev;
    }
    
    return -1;
}

// ==========================================================================
// 6. INTERPOLATION SEARCH - O(log log n) Average, O(n) Worst
// Better than binary search for uniformly distributed data
// ==========================================================================

int interpolationSearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        
        // Calculate position using interpolation formula
        int pos = low + (double)(target - arr[low]) / (arr[high] - arr[low]) * (high - low);
        
        if (arr[pos] == target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

// ==========================================================================
// 7. EXPONENTIAL SEARCH - O(log n) Time, O(1) Space
// Find range then binary search, good for infinite arrays
// ==========================================================================

int exponentialSearch(vector<int>& arr, int target) {
    int n = arr.size();
    
    // If element is at first position
    if (arr[0] == target) {
        return 0;
    }
    
    // Find range for binary search
    int i = 1;
    while (i < n && arr[i] <= target) {
        i = i * 2;
    }
    
    // Binary search in found range
    int left = i / 2;
    int right = min(i, n - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// ==========================================================================
// 8. FIBONACCI SEARCH - O(log n) Time, O(1) Space
// Uses Fibonacci numbers to divide array, no division/multiplication
// ==========================================================================

int fibonacciSearch(vector<int>& arr, int target) {
    int n = arr.size();
    
    // Initialize fibonacci numbers
    int fibM2 = 0;   // (m-2)th Fibonacci number
    int fibM1 = 1;   // (m-1)th Fibonacci number
    int fibM = fibM2 + fibM1; // mth Fibonacci number
    
    // Find smallest Fibonacci number >= n
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    
    int offset = -1;
    
    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);
        
        if (arr[i] < target) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        } else if (arr[i] > target) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        } else {
            return i;
        }
    }
    
    if (fibM1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }
    
    return -1;
}

// ==========================================================================
// 9. HASH TABLE SEARCH - O(1) Average, O(n) Worst
// Uses hash table for constant time lookup
// ==========================================================================

class HashSearch {
private:
    unordered_map<int, vector<int>> hashTable;
    
public:
    void buildHashTable(vector<int>& arr) {
        hashTable.clear();
        for (int i = 0; i < arr.size(); i++) {
            hashTable[arr[i]].push_back(i);
        }
    }
    
    int search(int target) {
        if (hashTable.find(target) != hashTable.end()) {
            return hashTable[target][0]; // Return first occurrence
        }
        return -1;
    }
    
    vector<int> searchAll(int target) {
        if (hashTable.find(target) != hashTable.end()) {
            return hashTable[target]; // Return all occurrences
        }
        return {};
    }
};

// ==========================================================================
// 10. TWO POINTERS SEARCH - O(n) Time, O(1) Space
// For sorted arrays, finding pairs/triplets
// ==========================================================================

class TwoPointerSearch {
public:
    // Two Sum - Find pair that adds to target
    static vector<int> twoSum(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            int sum = arr[left] + arr[right];
            
            if (sum == target) {
                return {left, right};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {-1, -1}; // Not found
    }
    
    // Three Sum - Find triplet that adds to target
    static vector<vector<int>> threeSum(vector<int>& arr, int target) {
        vector<vector<int>> result;
        sort(arr.begin(), arr.end());
        
        for (int i = 0; i < arr.size() - 2; i++) {
            if (i > 0 && arr[i] == arr[i - 1]) continue; // Skip duplicates
            
            int left = i + 1, right = arr.size() - 1;
            
            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];
                
                if (sum == target) {
                    result.push_back({i, left, right});
                    
                    // Skip duplicates
                    while (left < right && arr[left] == arr[left + 1]) left++;
                    while (left < right && arr[right] == arr[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

// ==========================================================================
// 11. BINARY SEARCH ON ANSWER - O(log(max-min) * f(x))
// Search for answer in a range, checking feasibility
// ==========================================================================

class BinarySearchOnAnswer {
public:
    // Example: Find square root using binary search
    static int findSquareRoot(int x) {
        if (x == 0 || x == 1) return x;
        
        int left = 1, right = x;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (mid <= x / mid) { // Avoid overflow: mid * mid <= x
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Example: Minimum pages allocation problem
    static bool canAllocate(vector<int>& books, int students, int maxPages) {
        int studentCount = 1;
        int currentPages = 0;
        
        for (int pages : books) {
            if (pages > maxPages) return false;
            
            if (currentPages + pages > maxPages) {
                studentCount++;
                currentPages = pages;
                
                if (studentCount > students) return false;
            } else {
                currentPages += pages;
            }
        }
        
        return true;
    }
    
    static int allocateBooks(vector<int>& books, int students) {
        int totalPages = 0, maxPages = 0;
        
        for (int pages : books) {
            totalPages += pages;
            maxPages = max(maxPages, pages);
        }
        
        int left = maxPages, right = totalPages;
        int result = totalPages;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canAllocate(books, students, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};

// ==========================================================================
// MAIN FUNCTION - TESTING ALL SEARCHING ALGORITHMS
// ==========================================================================

int main() {
    cout << "SEARCHING ALGORITHMS DEMONSTRATION" << endl;
    cout << "==================================" << endl;
    cout << "Total algorithms implemented: 11+ variations" << endl;
    
    // Test arrays
    vector<int> unsortedArr = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    vector<int> sortedArr = {5, 11, 12, 22, 25, 30, 34, 64, 77, 90};
    vector<int> duplicateArr = {1, 2, 2, 2, 3, 4, 5, 5, 6, 7};
    
    printArray(unsortedArr, "Unsorted Array");
    printArray(sortedArr, "Sorted Array");
    printArray(duplicateArr, "Array with Duplicates");
    
    int target = 25;
    cout << "\nSearching for target = " << target << endl;
    cout << string(60, '=') << endl;
    
    // 1. LINEAR SEARCH
    cout << "\n1. LINEAR SEARCH" << endl;
    cout << "   Time: O(n), Space: O(1), Works on: Any array" << endl;
    
    int comparisons;
    int result = linearSearchWithCount(unsortedArr, target, comparisons);
    printResult("Linear Search", target, result, comparisons);
    
    vector<int> allOccurrences = linearSearchAll(duplicateArr, 2);
    cout << "   All occurrences of 2 in duplicate array: ";
    for (int idx : allOccurrences) cout << idx << " ";
    cout << endl;
    
    // 2. BINARY SEARCH
    cout << "\n2. BINARY SEARCH (Multiple Implementations)" << endl;
    cout << "   Time: O(log n), Space: O(1), Works on: Sorted arrays only" << endl;
    
    result = binarySearchWithCount(sortedArr, target, comparisons);
    printResult("Binary Search (Iterative)", target, result, comparisons);
    
    result = binarySearchRecursiveWrapper(sortedArr, target);
    printResult("Binary Search (Recursive)", target, result);
    
    // 3. BINARY SEARCH VARIATIONS
    cout << "\n3. BINARY SEARCH VARIATIONS" << endl;
    cout << "   Find first/last occurrence, count duplicates" << endl;
    
    int first = findFirst(duplicateArr, 2);
    int last = findLast(duplicateArr, 2);
    int count = countOccurrences(duplicateArr, 2);
    
    cout << "   Target 2 in duplicate array:" << endl;
    cout << "   First occurrence: " << first << endl;
    cout << "   Last occurrence: " << last << endl;
    cout << "   Total count: " << count << endl;
    
    // 4. TERNARY SEARCH
    cout << "\n4. TERNARY SEARCH" << endl;
    cout << "   Time: O(log₃ n), Space: O(1), Works on: Sorted arrays" << endl;
    
    result = ternarySearchWithCount(sortedArr, target, comparisons);
    printResult("Ternary Search", target, result, comparisons);
    
    // 5. JUMP SEARCH
    cout << "\n5. JUMP SEARCH" << endl;
    cout << "   Time: O(√n), Space: O(1), Works on: Sorted arrays" << endl;
    
    result = jumpSearchWithCount(sortedArr, target, comparisons);
    printResult("Jump Search", target, result, comparisons);
    
    // 6. INTERPOLATION SEARCH
    cout << "\n6. INTERPOLATION SEARCH" << endl;
    cout << "   Time: O(log log n) avg, O(n) worst, Works on: Uniformly distributed" << endl;
    
    result = interpolationSearch(sortedArr, target);
    printResult("Interpolation Search", target, result);
    
    // 7. EXPONENTIAL SEARCH
    cout << "\n7. EXPONENTIAL SEARCH" << endl;
    cout << "   Time: O(log n), Space: O(1), Good for: Infinite arrays" << endl;
    
    result = exponentialSearch(sortedArr, target);
    printResult("Exponential Search", target, result);
    
    // 8. FIBONACCI SEARCH
    cout << "\n8. FIBONACCI SEARCH" << endl;
    cout << "   Time: O(log n), Space: O(1), No division/multiplication" << endl;
    
    result = fibonacciSearch(sortedArr, target);
    printResult("Fibonacci Search", target, result);
    
    // 9. HASH TABLE SEARCH
    cout << "\n9. HASH TABLE SEARCH" << endl;
    cout << "   Time: O(1) avg, O(n) worst, Space: O(n)" << endl;
    
    HashSearch hashSearch;
    hashSearch.buildHashTable(unsortedArr);
    result = hashSearch.search(target);
    printResult("Hash Table Search", target, result);
    
    // 10. TWO POINTERS SEARCH
    cout << "\n10. TWO POINTERS TECHNIQUE" << endl;
    cout << "    Time: O(n), Space: O(1), For: Sum problems" << endl;
    
    vector<int> twoSumResult = TwoPointerSearch::twoSum(sortedArr, 47); // 22 + 25 = 47
    cout << "    Two Sum (target=47): ";
    if (twoSumResult[0] != -1) {
        cout << "Found at indices " << twoSumResult[0] << " and " << twoSumResult[1];
        cout << " (" << sortedArr[twoSumResult[0]] << " + " << sortedArr[twoSumResult[1]] << " = 47)";
    } else {
        cout << "Not found";
    }
    cout << endl;
    
    // 11. BINARY SEARCH ON ANSWER
    cout << "\n11. BINARY SEARCH ON ANSWER" << endl;
    cout << "    Time: O(log(range) * validation), Advanced technique" << endl;
    
    int sqrtResult = BinarySearchOnAnswer::findSquareRoot(64);
    cout << "    Square root of 64: " << sqrtResult << endl;
    
    vector<int> books = {12, 34, 67, 90};
    int minPages = BinarySearchOnAnswer::allocateBooks(books, 2);
    cout << "    Book allocation (2 students): " << minPages << " pages" << endl;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "ALGORITHM COMPARISON SUMMARY" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nTime Complexity Comparison:" << endl;
    cout << "┌────────────────────────┬─────────────┬─────────────┬─────────────────┐" << endl;
    cout << "│ Algorithm              │ Best Case   │ Average     │ Worst Case      │" << endl;
    cout << "├────────────────────────┼─────────────┼─────────────┼─────────────────┤" << endl;
    cout << "│ Linear Search          │ O(1)        │ O(n)        │ O(n)            │" << endl;
    cout << "│ Binary Search          │ O(1)        │ O(log n)    │ O(log n)        │" << endl;
    cout << "│ Ternary Search         │ O(1)        │ O(log₃ n)   │ O(log₃ n)       │" << endl;
    cout << "│ Jump Search            │ O(1)        │ O(√n)       │ O(√n)           │" << endl;
    cout << "│ Interpolation Search   │ O(1)        │ O(log log n)│ O(n)            │" << endl;
    cout << "│ Exponential Search     │ O(1)        │ O(log n)    │ O(log n)        │" << endl;
    cout << "│ Fibonacci Search       │ O(1)        │ O(log n)    │ O(log n)        │" << endl;
    cout << "│ Hash Table Search      │ O(1)        │ O(1)        │ O(n)            │" << endl;
    cout << "│ Two Pointers           │ O(n)        │ O(n)        │ O(n)            │" << endl;
    cout << "└────────────────────────┴─────────────┴─────────────┴─────────────────┘" << endl;
    
    cout << "\nWhen to Use Each Algorithm:" << endl;
    cout << "• Linear Search: Unsorted data, small arrays, simple implementation" << endl;
    cout << "• Binary Search: Sorted data, most common interview algorithm" << endl;
    cout << "• Ternary Search: Alternative to binary, slightly more comparisons" << endl;
    cout << "• Jump Search: Good balance between linear and binary" << endl;
    cout << "• Interpolation: Uniformly distributed data, better than binary" << endl;
    cout << "• Exponential: Unbounded/infinite arrays, find range first" << endl;
    cout << "• Fibonacci: No division/multiplication operations" << endl;
    cout << "• Hash Table: When multiple searches needed, extra space ok" << endl;
    cout << "• Two Pointers: Sum problems, pair finding in sorted arrays" << endl;
    cout << "• Binary Search on Answer: Optimization problems, search for optimal value" << endl;
    
    cout << "\nData Structure Requirements:" << endl;
    cout << "• Any Array: Linear Search, Hash Table" << endl;
    cout << "• Sorted Array: Binary, Ternary, Jump, Interpolation, Exponential, Fibonacci" << endl;
    cout << "• Special Cases: Two Pointers (sum problems), Binary on Answer (optimization)" << endl;
    
    cout << "\nInterview Priority (Must Know):" << endl;
    cout << "1. Binary Search (and its variations)" << endl;
    cout << "2. Two Pointers Technique" << endl;
    cout << "3. Linear Search (basic understanding)" << endl;
    cout << "4. Hash Table Search (for optimization)" << endl;
    cout << "5. Binary Search on Answer (advanced problems)" << endl;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "Program executed successfully!" << endl;
    cout << "All searching algorithms implemented and tested." << endl;
    
    return 0;
}
