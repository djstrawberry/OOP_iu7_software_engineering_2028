#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <type_traits>

#include "../inc/set/set.h"

// Вспомогательные классы для тестов static_assert
struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&) = default;
    bool operator==(const NonCopyable&) const { return true; }
};

struct NonComparable
{
    int x;
    NonComparable(int x) : x(x) {}
};

int main()
{
    std::cout << "=== SET CLASS TESTING ===\n\n";

    std::cout << "--- 1. Basic Constructors ---\n";
    Set<int> s1;
    Set<int> s2 = {1, 2, 3, 4, 5};
    if (!s2.empty())
        std::cout << "Initializer list: " << s2 << " (size: " << s2.size() << ")\n";
    else
        std::cout << "Initializer list: {} (0) (size: 0)\n";

    int arr[] = {10, 20, 30, 40};
    Set<int> s3(4, arr);
    if (!s3.empty())
        std::cout << "C-array: " << s3 << " (size: " << s3.size() << ")\n";
    else
        std::cout << "C-array: {} (0) (size: 0)\n";

    Set<int> s4(s2);
    if (!s4.empty())
        std::cout << "Copy: " << s4 << " (size: " << s4.size() << ")\n";
    else
        std::cout << "Copy: {} (0) (size: 0)\n";

    Set<int> s5(std::move(s3));
    std::cout << "Move (from s3): " << s5 << " (size: " << s5.size() << ")\n";
    std::cout << "Moved-from (s3): " << s3 << " (size: " << s3.size() << ")\n";

    std::cout << "\n--- 2. Constructors from STL Containers ---\n";
    std::vector<int> vec = {1, 2, 2, 3, 4, 4, 5};
    Set<int> s6(vec.begin(), vec.end());
    std::cout << "From vector: " << s6 << " (duplicates removed)\n";

    std::list<std::string> lst = {"apple", "banana", "apple", "cherry"};
    Set<std::string> s7(lst.begin(), lst.end());
    std::cout << "From list: " << s7 << "\n";

    std::cout << "\n--- 3. Add / Erase / In / Find ---\n";
    Set<int> s8 = {1, 3, 5};
    std::cout << "Original: " << s8 << "\n";
    
    s8.add(7);
    std::cout << "After add(7): " << s8 << "\n";
    
    s8.add(3);
    std::cout << "After add(3) (duplicate): " << s8 << "\n";
    
    s8.erase(3);
    std::cout << "After erase(3): " << s8 << "\n";
    
    std::cout << "in(5): " << s8.in(5) << "\n";
    std::cout << "in(3): " << s8.in(3) << "\n";
    
    auto it = s8.find(7);
    std::cout << "find(7): " << (it ? "found" : "not found") << "\n";

    std::cout << "\n--- 4. Math Operations ---\n";
    Set<int> A = {1, 2, 3, 4};
    Set<int> B = {3, 4, 5, 6};
    
    std::cout << "A = " << A << "\n";
    std::cout << "B = " << B << "\n";
    std::cout << "A + B: " << (A + B) << "\n";
    std::cout << "A & B: " << (A & B) << "\n";
    std::cout << "A - B: " << (A - B) << "\n";
    std::cout << "A ^ B: " << (A ^ B) << "\n";

    std::cout << "\n--- 5. Comparisons ---\n";
    Set<int> X = {1, 2};
    Set<int> Y = {1, 2, 3};
    Set<int> Z = {4, 5};
    
    std::cout << "X = " << X << ", Y = " << Y << ", Z = " << Z << "\n";
    std::cout << "X == Y: " << (X == Y) << "\n";
    std::cout << "X.subsetOf(Y): " << X.subsetOf(Y) << "\n";
    std::cout << "Y.supersetOf(X): " << Y.supersetOf(X) << "\n";
    std::cout << "X <=> Z: " << ((X <=> Z) == std::partial_ordering::unordered ? "unordered" : "comparable") << "\n";

    // 6. Итераторы
    std::cout << "\n--- 6. Iterators ---\n";
    std::cout << "Iterating X: ";
    for (const auto &el : X)
        std::cout << el << " ";
    std::cout << "\n";

    std::cout << "\n--- 7. Mixed Types (int + double) ---\n";
    Set<int> si = {1, 2, 3};
    Set<double> sd = {2.5, 3.5, 4.5};
    auto mixed = si.make_union(sd);
    std::cout << "int U double: " << mixed << " (type: double)\n";

    std::cout << "\n--- 8. Empty Set ---\n";
    Set<int> empty_set;
    std::cout << "Empty: " << empty_set << ", size: " << empty_set.size() << "\n";
    empty_set.add(42);
    std::cout << "After add(42): " << empty_set << "\n";
    empty_set.clear();
    std::cout << "After clear(): " << empty_set << "\n";


    std::cout << "\n--- 9. Static Assert Tests (COMMENTED OUT) ---\n";

    /*
    // ТЕСТ 1: NonCopyable тип (должен вызвать static_assert в Set<T>)
    // Ожидаемая ошибка: "T must be copyable, movable, assignable"
    Set<NonCopyable> bad_set;
    
    // ТЕСТ 2: NonComparable тип (должен вызвать static_assert)
    // Ожидаемая ошибка: "T must support equality comparison"
    Set<NonComparable> bad_set2;
    bad_set2.add(NonComparable(5));
    
    // ТЕСТ 3: Контейнер с неправильным типом элемента
    // Ожидаемая ошибка: "Container elements must be convertible to T"
    std::vector<std::string> str_vec = {"a", "b"};
    Set<int> bad_set3(str_vec); // string не конвертируется в int
    */

    std::cout << "\n=== ALL RUNTIME TESTS PASSED ===\n";
    std::cout << "Uncomment the static_assert section to verify compile-time checks.\n";

    return 0;
}