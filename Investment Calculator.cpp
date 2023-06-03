#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

struct YearlyInvestment {
    int year;
    double principal;
    double interest;
    double futureValue;
    double inflationAdjustedFutureValue;
    double afterTaxFutureValue;
};

double calculateFutureValue(double principal, double interestRate, int timePeriod) {
    double rate = 1 + (interestRate / 100);
    return principal * pow(rate, timePeriod);
}

double calculateInflationAdjustedFutureValue(double futureValue, double inflationRate, int timePeriod) {
    double rate = 1 - (inflationRate / 100);
    return futureValue * pow(rate, timePeriod);
}

double calculateAfterTaxFutureValue(double futureValue, double taxRate) {
    double rate = 1 - (taxRate / 100);
    return futureValue * rate;
}

bool validateInput(double value) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void displayInvestmentTable(const vector<YearlyInvestment>& investments) {
    cout << endl;
    cout << "Investment Table" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(10) << left << "Year" << setw(15) << "Principal" << setw(15) << "Interest" << setw(20) << "Future Value"
        << setw(30) << "Inflation-Adjusted Future Value" << setw(20) << "After-Tax Future Value" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

    for (const auto& investment : investments) {
        cout << setw(10) << left << investment.year << setw(15) << fixed << setprecision(2) << investment.principal
            << setw(15) << investment.interest << setw(20) << investment.futureValue
            << setw(30) << investment.inflationAdjustedFutureValue << setw(20) << investment.afterTaxFutureValue << endl;
    }

    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}

vector<YearlyInvestment> calculateYearlyInvestments(double principal, double interestRate, int timePeriod, double inflationRate, double taxRate) {
    vector<YearlyInvestment> investments;
    double currentPrincipal = principal;

    for (int year = 1; year <= timePeriod; ++year) {
        double interest = currentPrincipal * (interestRate / 100);
        double futureValue = currentPrincipal + interest;
        double inflationAdjustedFutureValue = calculateInflationAdjustedFutureValue(futureValue, inflationRate, year);
        double afterTaxFutureValue = calculateAfterTaxFutureValue(futureValue, taxRate);

        YearlyInvestment investment;
        investment.year = year;
        investment.principal = currentPrincipal;
        investment.interest = interest;
        investment.futureValue = futureValue;
        investment.inflationAdjustedFutureValue = inflationAdjustedFutureValue;
        investment.afterTaxFutureValue = afterTaxFutureValue;

        investments.push_back(investment);

        currentPrincipal = futureValue;
    }

    return investments;
}

void displayInvestmentSummary(const vector<YearlyInvestment>& investments, double principal, int timePeriod) {
    double totalPrincipal = 0.0;
    double totalInterest = 0.0;
    double totalInflationAdjustedFutureValue = 0.0;
    double totalAfterTaxFutureValue = 0.0;

    for (const auto& investment : investments) {
        totalPrincipal += investment.principal;
        totalInterest += investment.interest;
        totalInflationAdjustedFutureValue += investment.inflationAdjustedFutureValue;
        totalAfterTaxFutureValue += investment.afterTaxFutureValue;
    }

    double averageAnnualReturn = totalInterest / timePeriod;
    double averageAnnualReturnRate = (averageAnnualReturn / totalPrincipal) * 100;

    cout << endl;
    cout << "Investment Summary" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Principal Invested: $" << principal << endl;
    cout << "Total Interest Earned: $" << totalInterest << endl;
    cout << "Average Annual Return: $" << averageAnnualReturn << endl;
    cout << "Average Annual Return Rate: " << fixed << setprecision(2) << averageAnnualReturnRate << "%" << endl;
    cout << "Total Inflation-Adjusted Future Value: $" << totalInflationAdjustedFutureValue << endl;
    cout << "Total After-Tax Future Value: $" << totalAfterTaxFutureValue << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
}

int main() {
    while (true) {
        double principal, interestRate, inflationRate, taxRate;
        int timePeriod;

        cout << "Welcome to the Future Value Calculator!" << endl;

        while (true) {
            cout << "Enter the principal amount: $";
            cin >> principal;
            if (validateInput(principal))
                break;
            cout << "Invalid input. Please enter a numeric value." << endl;
        }

        while (true) {
            cout << "Enter the annual interest rate (%): ";
            cin >> interestRate;
            if (validateInput(interestRate))
                break;
            cout << "Invalid input. Please enter a numeric value." << endl;
        }

        while (true) {
            cout << "Enter the inflation rate (%): ";
            cin >> inflationRate;
            if (validateInput(inflationRate))
                break;
            cout << "Invalid input. Please enter a numeric value." << endl;
        }

        while (true) {
            cout << "Enter the tax rate (%): ";
            cin >> taxRate;
            if (validateInput(taxRate))
                break;
            cout << "Invalid input. Please enter a numeric value." << endl;
        }

        while (true) {
            cout << "Enter the time period (in years): ";
            cin >> timePeriod;
            if (validateInput(timePeriod) && timePeriod >= 0)
                break;
            cout << "Invalid input. Please enter a non-negative integer value." << endl;
        }

        double futureValue = calculateFutureValue(principal, interestRate, timePeriod);

        cout << "The future value of your investment after " << timePeriod << " years will be: $" << fixed << setprecision(2) << futureValue << endl;

        vector<YearlyInvestment> investments = calculateYearlyInvestments(principal, interestRate, timePeriod, inflationRate, taxRate);
        displayInvestmentTable(investments);
        displayInvestmentSummary(investments, principal, timePeriod);

        char choice;
        cout << "Do you want to calculate another investment? (Y/N): ";
        cin >> choice;

        if (tolower(choice) != 'y')
            break;

        cout << endl;
    }

    return 0;
}
