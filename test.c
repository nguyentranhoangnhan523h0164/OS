#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
// Hàm kiểm tra xem một số có phải là số nguyên tố hay không
int isPrime(int n) {
    if (n <= 1) return 0; // Số nguyên dương nhỏ hơn hoặc bằng 1 không phải là số nguyên tố
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Số n chia hết cho i => không phải số nguyên tố
    }
    return 1; // Nếu không thỏa mãn điều kiện nào ở trên, số đó là số nguyên tố
}

// Hàm kiểm tra xem một số có phải là số Armstrong hay không
int isArmstrong(int n) {
    int originalNumber, remainder, result = 0, nDigits = 0;
    originalNumber = n;

    // Đếm số chữ số trong số n
    while (originalNumber != 0) {
        originalNumber /= 10;
        ++nDigits;
    }

    originalNumber = n;

    // Tính tổng lũy thừa các chữ số của số n
    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        result += pow(remainder, nDigits);
        originalNumber /= 10;
    }

    // Kiểm tra xem số n có bằng tổng lũy thừa của các chữ số của n không
    if (result == n)
        return 1; // Nếu có, số n là số Armstrong
    else
        return 0; // Ngược lại, số n không phải là số Armstrong
}

int main() {
    int number;
    printf("Nhập một số nguyên dương: ");
    scanf("%d", &number);

    clock_t start, end;
    double cpu_time_used;

    // Thời gian bắt đầu
    start = clock();

    // Thực hiện kiểm tra số nguyên tố không sử dụng tiến trình
    printf("Kiểm tra số nguyên tố không sử dụng tiến trình:\n");
    if (isPrime(number)) {
        printf("%d là số nguyên tố.\n", number);
    } else {
        printf("%d không là số nguyên tố.\n", number);
    }

    // Thời gian kết thúc
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi không sử dụng tiến trình: %f giây\n", cpu_time_used);

    // Thời gian bắt đầu
    start = clock();

    // Thực hiện kiểm tra số Armstrong không sử dụng tiến trình
    printf("\nKiểm tra số Armstrong không sử dụng tiến trình:\n");
    if (isArmstrong(number)) {
        printf("%d là số Armstrong.\n", number);
    } else {
        printf("%d không là số Armstrong.\n", number);
    }

    // Thời gian kết thúc
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi kiểm tra số Armstrong không sử dụng tiến trình: %f giây\n", cpu_time_used);

    // Thời gian bắt đầu
    start = clock();

    // Thực hiện kiểm tra số nguyên tố sử dụng tiến trình
    printf("\nKiểm tra số nguyên tố sử dụng tiến trình:\n");
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        // Fork thất bại
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        if (isPrime(number)) {
            printf("%d là số nguyên tố.\n", number);
        } else {
            printf("%d không là số nguyên tố.\n", number);
        }
        exit(0);
    } else {
        // Tiến trình cha
        //wait(NULL);
    }

    // Thời gian kết thúc
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi kiểm tra số nguyên tố sử dụng tiến trình: %f giây\n", cpu_time_used);

    // Thời gian bắt đầu
    start = clock();

    // Thực hiện kiểm tra số Armstrong sử dụng tiến trình
    printf("\nKiểm tra số Armstrong sử dụng tiến trình:\n");
    pid = fork();

    if (pid < 0) {
        // Fork thất bại
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        if (isArmstrong(number)) {
            printf("%d là số Armstrong.\n", number);
        } else {
            printf("%d không là số Armstrong.\n", number);
        }
        exit(0);
    } else {
        // Tiến trình cha
        //wait(NULL);
    }

    // Thời gian kết thúc
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi kiểm tra số Armstrong sử dụng tiến trình: %f giây\n", cpu_time_used);

    return 0;
}

