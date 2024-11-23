#include <iostream>  // 표준 입출력 스트림을 사용하기 위한 헤더 파일 포함
#include <string>    // 문자열을 사용하기 위한 헤더 파일 포함

#define MAX_ACCOUNTS 100  // 최대 계좌 수를 100으로 정의

using namespace std;  // std 이름 공간을 사용

// 계좌 정보를 저장할 구조체 정의
struct Account {
    int accountNumber;     // 계좌 번호
    string customerName;   // 고객 이름
    int balance;           // 잔액
};

// 계좌 관리 배열과 계좌 수를 저장할 변수
Account accounts[MAX_ACCOUNTS];  // MAX_ACCOUNTS 크기의 Account 배열
int accountCount = 0;  // 현재 개설된 계좌 수 초기화

// 함수 선언
void ShowMenu();         // 메뉴를 표시하는 함수
void OpenAccount();      // 계좌를 개설하는 함수
void Deposit();          // 입금하는 함수
void Withdraw();         // 출금하는 함수
void ShowAllAccounts();  // 모든 계좌 정보를 표시하는 함수

// main 함수 시작점
int main() {
    int choice;  // 사용자의 메뉴 선택을 저장할 변수
    
    while (true) {  // 무한 루프
        ShowMenu();  // 메뉴 표시 함수 호출
        cout << "선택: ";  // 사용자에게 입력을 요청
        cin >> choice;  // 사용자의 선택을 입력받음
        
        switch (choice) {
            case 1:
                OpenAccount();  // 계좌 개설 함수 호출
                break;
            case 2:
                Deposit();  // 입금 함수 호출
                break;
            case 3:
                Withdraw();  // 출금 함수 호출
                break;
            case 4:
                ShowAllAccounts();  // 모든 계좌 정보 표시 함수 호출
                break;
            case 5:
                cout << "프로그램을 종료합니다." << endl;  // 종료 메시지 출력
                return 0;  // 프로그램 종료
            default:
                cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;  // 잘못된 선택 메시지
        }
    }
    
    return 0;  // 프로그램 종료 (while문에서 빠져나올 수 없음)
}

// 메뉴를 표시하는 함수 정의
void ShowMenu() {
    cout << "-------------------Menu--------------------" << endl;
    cout << "1. 계좌 개설" << endl;
    cout << "2. 입금" << endl;
    cout << "3. 출금" << endl;
    cout << "4. 계좌 정보" << endl;
    cout << "5. 프로그램 종료" << endl;
}

// 계좌를 개설하는 함수 정의
void OpenAccount() {
    if (accountCount >= MAX_ACCOUNTS) {  // 계좌 수가 최대치를 넘으면
        cout << "더 이상 계좌를 개설할 수 없습니다." << endl;  // 경고 메시지 출력
        return;  // 함수 종료
    }
    
    int accountNumber;  // 새로운 계좌 번호를 저장할 변수
    string customerName;  // 새로운 고객 이름을 저장할 변수
    int initialDeposit;  // 초기 입금액을 저장할 변수
    
    cout << "계좌 번호: ";  // 사용자에게 계좌 번호 입력 요청
    cin >> accountNumber;  // 계좌 번호 입력받음
    cout << "고객 이름: ";  // 사용자에게 고객 이름 입력 요청
    cin >> customerName;  // 고객 이름 입력받음
    cout << "초기 입금액: ";  // 사용자에게 초기 입금액 입력 요청
    cin >> initialDeposit;  // 초기 입금액 입력받음
    
    // 새 계좌 정보 저장
    accounts[accountCount].accountNumber = accountNumber;
    accounts[accountCount].customerName = customerName;
    accounts[accountCount].balance = initialDeposit;
    accountCount++;  // 계좌 수 증가
    
    cout << "계좌 개설 완료!" << endl;  // 성공 메시지 출력
}

// 입금하는 함수 정의
void Deposit() {
    int accountNumber;  // 입금할 계좌 번호를 저장할 변수
    int amount;  // 입금액을 저장할 변수
    
    cout << "계좌 번호: ";  // 사용자에게 계좌 번호 입력 요청
    cin >> accountNumber;  // 계좌 번호 입력받음
    cout << "입금액: ";  // 사용자에게 입금액 입력 요청
    cin >> amount;  // 입금액 입력받음
    
    for (int i = 0; i < accountCount; i++) {  // 모든 계좌를 순회
        if (accounts[i].accountNumber == accountNumber) {  // 계좌 번호가 일치하면
            accounts[i].balance += amount;  // 잔액에 입금액 더함
            cout << "입금 완료!" << endl;  // 성공 메시지 출력
            return;  // 함수 종료
        }
    }
    
    cout << "존재하지 않는 계좌 번호입니다." << endl;  // 계좌 번호가 없으면 경고 메시지
}

// 출금하는 함수 정의
void Withdraw() {
    int accountNumber;  // 출금할 계좌 번호를 저장할 변수
    int amount;  // 출금액을 저장할 변수
    
    cout << "계좌 번호: ";  // 사용자에게 계좌 번호 입력 요청
    cin >> accountNumber;  // 계좌 번호 입력받음
    cout << "출금액: ";  // 사용자에게 출금액 입력 요청
    cin >> amount;  // 출금액 입력받음
    
    for (int i = 0; i < accountCount; i++) {  // 모든 계좌를 순회
        if (accounts[i].accountNumber == accountNumber) {  // 계좌 번호가 일치하면
            if (accounts[i].balance >= amount) {  // 잔액이 출금액 이상이면
                accounts[i].balance -= amount;  // 잔액에서 출금액 빼기
                cout << "출금 완료!" << endl;  // 성공 메시지 출력
            } else {
                cout << "잔액이 부족합니다." << endl;  // 잔액이 부족하면 경고 메시지
            }
            return;  // 함수 종료
        }
    }
    
    cout << "존재하지 않는 계좌 번호입니다." << endl;  // 계좌 번호가 없으면 경고 메시지
}

// 모든 계좌 정보를 표시하는 함수 정의
void ShowAllAccounts() {
    for (int i = 0; i < accountCount; i++) {  // 모든 계좌를 순회
        cout << "계좌 번호: " << accounts[i].accountNumber << ", 고객 이름: " << accounts[i].customerName << ", 잔액: " << accounts[i].balance << endl;
    }
}
