# SparseMatrix

SparseMatrix — это библиотека для работы с разреженными матрицами в формате CSR.

## Установка и подключение

### **1. Добавление в CMake-проект**
Добавьте SparseMatrix в свой проект через `add_subdirectory`:

```cmake
add_subdirectory(SparseMatrix)
target_link_libraries(YourProject PRIVATE SparseMatrix)
```

### **2. Примеры использования**
Пример создания и использования кватерниона:

```cpp
#include <SparseMatrix/MatrixCSR3.h>
#include <SparseMatrix/MatrixReader.h>
#include <iostream>

int main() {
    SparseMatrix::MatrixCSR3 matrix = SparseMatrix::MatrixReader::read("matrix.txt");
    matrix.print(); // Выведет значения полей values_, columns_ и row_indices_
    return 0;
}

```

### **3. Сборка**

```sh
mkdir build
cd build
cmake ..
make
```

### **4. Запуск тестов**
```sh
cd tests
ctest
```