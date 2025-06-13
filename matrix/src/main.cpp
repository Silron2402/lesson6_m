#include <src/matrix.h>
#include <iostream>

int main()
{
    //зададим первую матрицу
    math::Matrix m(3, 3);
    m(0,0) = 2.;
    m(1,1) = 1.;

    //зададим вторую матрицу
    math::Matrix m1(3, 3);
    m1(0,0) = 5.;
    m1(1,1) = 5.;

    //выведем первую матрицу m с помощью метода print
    std::cout << "Matrix m is: " << std::endl;
    m.print();

    //выведем матрицу m1 с помощью метода print
    std::cout << std::endl
              << "Matrix m1 is: " << std::endl;
    m1.print();

    //протестируем перегруженный оператор +
    std::cout << std::endl
              << "Summ m1 + m is: " << std::endl;
    math::Matrix m2 = m + m1;          
    m2.print();

    //протестируем перегруженный оператор -
    std::cout << std::endl
              << "Substract m1 - m is: " << std::endl;
    math::Matrix m3 = m1 - m;          
    m3.print();

    //протестируем перегруженный оператор *
    std::cout << std::endl
              << "Multiplication m1 * m is: " << std::endl;
    math::Matrix m4 = m1 * m;          
    m4.print();    

    //протестируем перегруженный оператор +=
    std::cout << std::endl
              << "Result of m += m1 is: " << std::endl;
    math::Matrix (m += m1); 

    m.print(); 

    //протестируем перегруженный оператор -=
    std::cout << std::endl
              << "Result of m1 -= m is: " << std::endl;
    math::Matrix (m1 -= m); 
    m1.print(); 

    //Проверим перегруженный оператор вывода
    std::cout << "result of overloading << opreator is"<<std::endl;
    std::cout << m1 << std::endl;

    //Протестируем перегруженный оператор *=
    std::cout << std::endl
              << "Multiplication m *= m1 is: " << std::endl;
    math::Matrix (m *= m1);          
    m.print();   
    
    // проверим работу оператора ввода и создадим новую матрицу m10
    math::Matrix m10;
    
    // протестируем перегруженный оператор ввода
    std::cin >> m10;
    
    //Проверим перегруженный оператор вывода
    std::cout << "result of overloading << opreator is"<<std::endl;
    std::cout << m10 << std::endl;

    return 0;
}