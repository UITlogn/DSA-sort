#include <bits/stdc++.h>                                                                                                                                                                                      //Logm
using namespace std;
// #define int long long

const int N = 1e6+5;
int n;
int base[N];
int a[N];

namespace QuickSort {
    void quickSort(int a[], int l, int r) {
        int p = a[l + r >> 1]; // lấy phần tử ở giữa làm pivot
        int i = l, j = r;
        while (i < j) {
            while (a[i] < p) ++i;
            while (a[j] > p) --j;

            if (i <= j) {
                swap(a[i], a[j]);
                ++i;
                --j;
            }
        }
        if (i < r) quickSort(a, i, r);
        if (l < j) quickSort(a, l, j);
    }
    void solve(int a[], int l, int r) {
        quickSort(a, l, r);
    }
}

namespace HeapSort {
    void heapify(int a[], int n, int i) {
        int largest = i;
        int left = 2 * i;
        int right = 2 * i + 1;
    
        if (left <= n && a[left] > a[largest])
            largest = left;
    
        if (right <= n && a[right] > a[largest])
            largest = right;
    
        if (largest != i) {
            swap(a[i], a[largest]);
            heapify(a, n, largest);
        }
    }
    
    void buildHeap(int a[], int n) {
        for (int i = n / 2; i >= 1; i--) {
            heapify(a, n, i);
        }
    }
    
    void heapSort(int a[], int n) {
        buildHeap(a, n);
        for (int i = n; i > 1; i--) {
            swap(a[1], a[i]);
            heapify(a, i - 1, 1);
        }
    }
    void solve(int a[], int n) {
        heapSort(a, n);
    }
}

namespace MergeSort {
    int arr[N];
    int temp[N];

    void mergeParts(int arr[], int l, int mid, int r) {
        int i = l, j = mid + 1;
        int k = 0;
        // 2 con trỏ hợp nhất 2 phần đã sắp xếp
        while (i <= mid && j <= r) {
            int nextValue;
            if (arr[i] < arr[j]) nextValue = arr[i++];
            else nextValue = arr[j++];
            temp[k++] = nextValue;
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= r) temp[k++] = arr[j++];
    
        for (int i = 0; i < k; ++i) arr[l + i] = temp[i];    
    }

    void mergeSort(int arr[], int l, int r) {
        if (l >= r) return;
        // chia để trị
        int mid = (l + r) / 2;
        // gọi đệ quy sort 2 nửa
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        // hợp nhất lại bằng thuật 2 con trỏ
        mergeParts(arr, l, mid, r);
    }

    void solve(int a[], int l, int r) {
        mergeSort(a, l, r);
    }
}

bool checker(int a[], int l, int r) { // -> 1 khi mảng a không được sắp xếp tăng dần
    for (int i = l + 1; i <= r; ++i)
        if (a[i - 1] > a[i])
            return 1;
    return 0;
}

void calc() {
    int t = clock();
    QuickSort::solve(a, 1, n);
    int tn = clock();
    if (checker(a, 1, n)) cout << "Quick sort wrong!\n";
    cout << "Quick sort time: " << tn - t << "ms\n";
    cerr << tn - t << '\t';

    for (int i = 1; i <= n; ++i) a[i] = base[i];
    t = clock();
    HeapSort::solve(a, n);
    tn = clock();
    if (checker(a, 1, n)) cout << "Heap sort wrong!\n";
    cout << "Heap sort time: " << tn - t << "ms\n";
    cerr << tn - t << '\t';

    for (int i = 1; i <= n; ++i) a[i] = base[i];
    t = clock();
    MergeSort::solve(a, 1, n);
    tn = clock();
    if (checker(a, 1, n)) cout << "Merge sort wrong!\n";
    cout << "Merge sort time: " << tn - t << "ms\n";
    cerr << tn - t << '\t';

    for (int i = 1; i <= n; ++i) a[i] = base[i];
    t = clock();
    sort(a + 1, a + n + 1);
    tn = clock();
    if (checker(a, 1, n)) cout << "C++ sort wrong!\n";
    cout << "C++ sort time: " << tn - t << "ms\n";
    cerr << tn - t << '\n';
}
signed main() {
    freopen("DSA.out", "w", stdout);
    string NAMETASK = "DSA";

    for (int i = 1; i <= 10; ++i) {
        string num = (i<10?"0":"") + to_string(i);
        string finp = NAMETASK + "/TEST" + num + "/" + NAMETASK + ".inp";
        ifstream inp(finp);

        inp >> n;
        for (int i = 1; i <= n; ++i) inp >> base[i];

        // cerr << "Test " << i << "...\n";
        cout << "Test " << i << "\n";
        calc();
        cout << "\n";
    }
    return 0;
}