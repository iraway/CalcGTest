#include <gtest/gtest.h>
#include "InMemoryHistory.h"

using namespace calc;

// Проверяем базовый сценарий: добавление нескольких операций и получение последних N
TEST(InMemoryHistoryTest, StoreAndRetrieveEntries) {
    InMemoryHistory h;
    h.AddEntry("op1");
    h.AddEntry("op2");
    h.AddEntry("op3");

    // Получаем последние 2 операции (должны быть "op2", "op3")
    auto last2 = h.GetLastOperations(2);
    ASSERT_EQ(last2.size(), 2u);
    EXPECT_EQ(last2[0], "op2");
    EXPECT_EQ(last2[1], "op3");
}

// Проверяем случай, когда запрашивается больше операций, чем содержится в истории
TEST(InMemoryHistoryTest, RequestMoreThanExists) {
    InMemoryHistory h;
    h.AddEntry("only");

    // Запросим 10 операций, а в истории только одна
    auto all = h.GetLastOperations(10);
    ASSERT_EQ(all.size(), 1u);
    EXPECT_EQ(all[0], "only");
}

// Проверяем поведение при запросе истории, когда история пуста
TEST(InMemoryHistoryTest, EmptyHistory) {
    InMemoryHistory h;
    auto none = h.GetLastOperations(5);

    // Ожидаем пустой результат
    EXPECT_TRUE(none.empty());
}

// Проверяем корректность возврата при запросе количества, равного размеру истории
TEST(InMemoryHistoryTest, RequestExactSize) {
    InMemoryHistory h;
    h.AddEntry("a");
    h.AddEntry("b");

    // Запрашиваем ровно 2 операции — ожидаем "a" и "b"
    auto last2 = h.GetLastOperations(2);
    ASSERT_EQ(last2.size(), 2u);
    EXPECT_EQ(last2[0], "a");
    EXPECT_EQ(last2[1], "b");
}

// Проверка поведения при запросе 0 последних операций
TEST(InMemoryHistoryTest, RequestZeroOperations) {
    InMemoryHistory h;
    auto none = h.GetLastOperations(0);

    // Ожидаем пустой вектор
    EXPECT_TRUE(none.empty());
}

// FIXME: этот тест демонстрирует отсутствие ограничения на размер истории
TEST(InMemoryHistoryTest, DefaultCapacityExceededFails) {
    InMemoryHistory h;

    // Добавим 200 записей
    for (int i = 0; i < 200; ++i) {
        h.AddEntry("op" + std::to_string(i));
    }

    // Предположим, что в истории должно храниться не более 100 операций
    // Этот тест упадёт, т.к. ограничение не реализовано
    EXPECT_LE(h.GetLastOperations(200).size(), 100u);
}
