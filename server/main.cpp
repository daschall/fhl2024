#include <iostream>

#include "queryprocessing/operators.h"
#include "expressions/expressions.h"

int main()
{
    // Create a value array to hold data.
    //
    Value rgvals[3];
    rgvals[2] = 10;
    
    // col0 < 10
    //
    Comparison<ComparisonType::LE> cmp(0, 2);

    // Generate rows from 0 to 100.
    //
    Qp::RowGenerator scanner(0, 100, 1);

    // Filter using above expression.
    //
    Qp::Filter filter(&scanner, &cmp);

    // Root of the query is the filter.
    //
    Qp::IOperator* root = &filter;


    // Now run the query until we get no more rows.
    //
    root->Open();
    while (root->GetRow(rgvals))
    {
        std::cout << "Got a row, value: " << rgvals[0] << '\n';
    }
    root->Close();
}

