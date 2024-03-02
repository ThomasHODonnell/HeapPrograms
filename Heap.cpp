#include <iostream> 
#include <vector>

using namespace std; 

int ARY = 3; 

class Heap {
    public:
        int size, max;
        vector<int> A;  
        Heap (int value) {
            size = 0; 
            A.push_back(value); 
            max = value; 
        }
        int min (int i, int j) {
            int minIndex = i; 
            for (int k = i + 1; k <= j; k++) 
                if (A[k] < A[minIndex]) minIndex = k;
            return minIndex; 
        }
        void swap (int i, int j) {
            int temp = A[i]; 
            A[i] = A[j]; 
            A[j] = temp; 
        }
        int extractMin() {
            if (size == 0) return -1; 
            int min = A[0]; 
            A[0] = A[size - 1]; 
            A.pop_back();
            size--; 
            heapify(0);
            return min; 
        }
        void heapify (int top) {

            int firstChild = top*ARY+1; 
            int lastChild = min(firstChild+2, size-1);           
            int minChild = firstChild;
            for (int i = firstChild + 1; i <= lastChild; i++) {
                if (A[i] < A[minChild])
                    minChild = i;
            }
            if (minChild <= size - 1 && A[top] > A[minChild]) {
                swap(top, minChild);
                heapify(minChild);
            }
            return; 
        }

        
        void insert (int newKey) {
            if (newKey > max) max = newKey;
            if (size == max) throw runtime_error("Warning: Heap is Full");
            A.push_back(newKey);
            size++;
            percolate(size - 1);
        }

        void percolate (int position) {
            int parent = (position-1)/ARY;
            if (position <= 0) return;
            if (A[parent] < A[position]) return; 
            else {
                swap(parent,position);
                percolate(parent);
                return;
            }
        }
        void decreaseKey (int position, int newKey) {
            if (size == 0) return;
            else if (A[position] > newKey) return;
            else {
                A[position] = newKey;
                percolate(position); 
            }
            return; 
        }
};

int main () {

    Heap* H = new Heap (100); 
    for (int i = 10; i > 0; i--) 
        H->insert((i*3497+379)%1000);
    H->decreaseKey(9,100);
    for (int i = 0; i < 10; i++)
        cout << H->extractMin() << endl;  
    return 0; 
}