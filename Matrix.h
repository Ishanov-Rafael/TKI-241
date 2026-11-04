#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс матрицы
     * @tparam T Тип элементов матрицы
     */
    template <typename T>
    class Matrix
    {
    private:
        /**
        * @brief двумерный вектор в котором хранятся элементы матрицы
        */
        std::vector<std::vector<T>> data;
        /**
        * @brief количество строк матрицы
        */
        size_t rows;
        /**
        * @brief количество столбцов матрицы
        */
        size_t cols;
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        Matrix() : rows(0), cols(0) {}

        /**
         * @brief Конструктор с параметрами
         * @param r Количество строк
         * @param c Количество столбцов
         */
        Matrix(const size_t r, const size_t c)
            : rows(r), cols(c), data(r, std::vector<T>(c)) {}

        /**
         * @brief Деструктор по умолчанию
         */
        ~Matrix() = default;

        /**
         * @brief Конструктор копирования
         */
        Matrix(const Matrix&) = default;

        /**
         * @brief Конструктор перемещения
         */
        Matrix(Matrix&&) noexcept = default;

        /**
         * @brief Оператор присваивания копированием
         * @return ссылка на текущую матрицу
         */
        Matrix& operator=(const Matrix&) = default;

        /**
         * @brief Оператор присваивания перемещением
         * @return ссылка на текущую матрицу
         */
        Matrix& operator=(Matrix&&) noexcept = default;

        /**
         * @brief Оператор индексации строки (неконстантный)
         * @param r Индекс строки
         * @return Ссылка на вектор строки
         */
        std::vector<T>& operator[](const size_t r)
        {
            if (r >= data.size()) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }

        /**
         * @brief Оператор индексации строки (константный)
         * @param r Индекс строки
         * @return Константная ссылка на вектор строки
         */
        const std::vector<T>& operator[](const size_t r) const
        {
            if (r >= data.size()) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }

        /**
         * @brief Получить количество строк матрицы
         * @return Количество строк
         */
        size_t getRows() const { return rows; }

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        size_t getCols() const { return cols; }

        /**
         * @brief Заполнение матрицы с использованием генератора
         * @param generator Ссылка на генератор
         */
        void fill(const Generator& generator)
        {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Метод вывода содержимого матрицы в строку
         * @return Строковое представление матрицы
         */
        std::string toString() const
        {
            std::ostringstream oss;
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    oss << data[i][j] << "\t";
                }
                oss << "\n";
            }
            return oss.str();
        }

        /**
         * @brief Вставка новой строки в матрицу по указанному индексу
         * @param index Индекс, по которому будет вставлена строка
         * @param row Вектор элементов строки
         */
        void insertRow(const size_t index, const std::vector<T>& row)
        {
            if (index > rows) {
                throw std::out_of_range("Индекс вставки строки выходит за границы матрицы");
            }
            data.insert(data.begin() + index, row);
            rows++;
        }

        /**
         * @brief Вставка нового столбца в матрицу по указанному индексу
         * @param index Индекс столбца, перед/после которого выполняется вставка
         * @param col Вектор элементов столбца
         */
        void insertCol(const size_t index, const std::vector<T>& col)
        {
            if (index > cols) {
                throw std::out_of_range("Индекс вставки столбца выходит за границы матрицы");
            }
            for (size_t i = 0; i < rows; ++i) {
                data[i].insert(data[i].begin() + index, col[i]);
            }
            cols++;
        }

        /**
         * @brief Получить копию указанной строки матрицы
         * @param index Индекс строки
         * @return Вектор элементов строки
         */
        std::vector<T> getRow(const size_t index) const
        {
            if (index >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы");
            }
            return data[index];
        }

        /**
         * @brief Переопределение оператора сдвига влево (вывод в поток)
         * @param os выходной поток
         * @param matrix матрица которую нужно вывести
         * @return ссылка на выходной поток
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
        {
            os << matrix.toString();
            return os;
        }

        /**
         * @brief Переопределение оператора сдвига вправо (ввод из потока)
         * @param is входной поток
         * @param matrix матрица в которую считываются элементы
         * @return ссылка на входной поток
         */
        friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
        {
            for (size_t i = 0; i < matrix.rows; ++i) {
                for (size_t j = 0; j < matrix.cols; ++j) {
                    is >> matrix.data[i][j];
                }
            }
            return is;
        }
    };
}
