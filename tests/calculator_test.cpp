#include <gtest/gtest.h>

#include "InMemoryHistory.h"
#include "SimpleCalculator.h"
#include "mocks.h"

using namespace calc;
using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

// Проверка: операция сложения записывает результат в историю (один вызов AddEntry)
TEST(SimpleCalculatorTest, AddRecordsHistory) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry(_)).Times(Exactly(1));
    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Add(2, 3), 5);
}

// Проверка: результат вычитания записывается в историю корректно
TEST(SimpleCalculatorTest, SubtractRecordsHistory) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("10 - 4 = 6")).Times(1);

    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Subtract(10, 4), 6);
}

// Проверка: результат умножения сохраняется в историю
TEST(SimpleCalculatorTest, MultiplyRecordsHistory) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("6 * 7 = 42")).Times(1);

    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Multiply(6, 7), 42);
}

// Проверка: результат деления корректно сохраняется в историю
TEST(SimpleCalculatorTest, DivideRecordsHistory) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("20 / 5 = 4")).Times(1);

    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Divide(20, 5), 4);
}


TEST(SimpleCalculatorTest, Divide_NormalCase)
{
    InMemoryHistory hist;
    SimpleCalculator calc(&hist);

    EXPECT_EQ(calc.Divide(10, 2), 5);
    const auto ops = hist.GetLastOperations(1);
    ASSERT_EQ(ops.size(), 1);
    EXPECT_EQ(ops[0], "10 / 2 = 5");
}

TEST(SimpleCalculatorTest, Divide_ByZeroThrows)
{
    InMemoryHistory hist;
    SimpleCalculator calc(&hist);

    EXPECT_THROW(calc.Divide(10, 0), std::invalid_argument);
}

// Проверка: можно подменить хранилище истории на лету и оно будет использоваться
TEST(SimpleCalculatorTest, CanSwapHistoryAtRuntime) {
    InMemoryHistory realHist;
    SimpleCalculator calc(&realHist);

    // Сначала используем реальное хранилище
    calc.Add(1, 1);
    EXPECT_EQ(realHist.GetLastOperations(1).back(), "1 + 1 = 2");

    // Затем подменяем хранилище на мок — проверим, что оно используется
    MockHistory hist2;
    EXPECT_CALL(hist2, AddEntry("2 + 2 = 4")).Times(1);
    calc.SetHistory(&hist2);
    EXPECT_EQ(calc.Add(2, 2), 4);
}

// Граничный случай: вычитание даёт отрицательный результат
TEST(SimpleCalculatorEdgeTest, SubtractNegativeResult) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("3 - 5 = -2")).Times(1);
    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Subtract(3, 5), -2);
}

// Граничный случай: умножение на ноль
TEST(SimpleCalculatorEdgeTest, MultiplyByZero) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("7 * 0 = 0")).Times(1);
    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Multiply(7, 0), 0);
}

// Проверка: целочисленное деление округляется вниз
TEST(SimpleCalculatorEdgeTest, DivisionRoundingDown) {
    MockHistory hist;
    EXPECT_CALL(hist, AddEntry("3 / 2 = 1")).Times(1);
    SimpleCalculator calc(&hist);
    EXPECT_EQ(calc.Divide(3, 2), 1);
}
