#include <iostream>
#include <stdexcept>

template<class T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialSize = 0, int growFactor = 1)
        : size(initialSize), capacity(initialSize), grow(growFactor) {
        data = (size > 0) ? new T[size] : nullptr;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int growFactor = 1) {
        if (newSize > capacity) {
            capacity = newSize + growFactor - newSize % growFactor;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        size = newSize;
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        size = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void Add(const T& value) {
        if (size == capacity) {
            SetSize(size + grow);
        }
        data[size++] = value;
    }

    void Append(const Array<T>& other) {
        int newSize = size + other.size;
        SetSize(newSize);
        for (int i = 0; i < other.size; ++i) {
            data[size++] = other.data[i];
        }
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this == &other) return *this;

        delete[] data;
        size = other.size;
        capacity = other.capacity;
        grow = other.grow;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    T* GetData() {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) throw std::out_of_range("Index out of range");

        if (size == capacity) {
            SetSize(size + grow);
        }

        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }
};

int main() {
    try {
        Array<int> arr(5, 5);

        for (int i = 0; i < 5; ++i) {
            arr[i] = i * 2;
        }

        arr.Add(10);
        arr.InsertAt(2, 15);
        arr.RemoveAt(1);

        arr.SetAt(3, 100);
        arr.FreeExtra();

        std::cout << "Array contents: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";

        std::cout << "Upper Bound: " << arr.GetUpperBound() << std::endl;
        std::cout << "Is Empty: " << (arr.IsEmpty() ? "Yes" : "No") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
