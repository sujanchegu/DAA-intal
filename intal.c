#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *adjptr(char *result)
{
    int f;
    int n = strlen(result);
    for (f = 0; f < n + 1 && result[f] == '0'; f++)
        ;
    if (result[f] == '\0')
    {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if (f != 0)
    {
        for (int offset = f; offset <= n; offset++)
        {
            result[offset - f] = result[offset];
        }
    }
    return result;
}

static int msb(int n)
{
    return (n / 10);
}

static int lsb(int n)
{
    return (n % 10);
}

static char chr(int n)
{
    return (char)(n + 48);
}

static int ord(char c)
{
    return (int)(c - '0');
}

char *intal_add(char *intal1, char *intal2)
{
    char *result = (char *)malloc(sizeof(char) * 1001);
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    int i = l1 - 1;
    int j = l2 - 1;
    int k = l1 > l2 ? l1 : l2;
    result[k] = '\0';
    k--;
    int sum = 0;
    int carry = 0;
    while (i >= 0 && j >= 0)
    {
        sum = ord(intal1[i--]) + ord(intal2[j--]) + carry;
        result[k--] = chr(sum % 10);
        carry = sum / 10;
    }
    if (i >= 0)
    {
        while (i >= 0)
        {
            sum = ord(intal1[i--]) + carry;
            result[k--] = chr(sum % 10);
            carry = sum / 10;
        }
    }
    else if (j >= 0)
    {
        while (j >= 0)
        {
            sum = ord(intal2[j--]) + carry;
            result[k--] = chr(sum % 10);
            carry = sum / 10;
        }
    }
    if (carry > 0)
    {
        for (i = strlen(result); i >= 0; i--)
        {
            result[i + 1] = result[i];
        }
        result[0] = chr(carry);
    }
    adjptr(result);
    return result;
}

int intal_compare(const char *intal1, const char *intal2)
{
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    if (l1 > l2)
    {
        return 1;
    }
    else if (l1 < l2)
    {
        return -1;
    }
    else
    {
        int k = strcmp(intal1, intal2);
        if (k != 0)
        {
            k /= abs(k);
        }
        return k;
    }
}

char *intal_diff(const char *intal1, const char *intal2)
{
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    int l3;
    int gret;
    if (l1 > l2)
    {
        l3 = l1 + 1;
        gret = 1;
    }
    else if (l1 < l2)
    {
        l3 = l2 + 1;
        gret = 2;
    }
    else
    {
        gret = intal_compare(intal1, intal2);
        if (gret == 0)
        {
            char *result = (char *)malloc(sizeof(char) * 2);
            result[0] = '0';
            result[1] = '\0';
            return result;
        }
        if (gret == -1)
        {
            gret = 2;
        }
        l3 = l1 + 1;
    }

    char *result = (char *)malloc(sizeof(char) * (l3 + 1));
    int i = l1 - 1, j = l2 - 1, k = l3 - 1;
    result[l3] = '\0';
    int diff, borrow = 0;
    if (gret == 1)
    {
        while (i >= 0 && j >= 0)
        {
            diff = ord(intal1[i]) - (ord(intal2[j]) + borrow);
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result[k] = chr(diff);
            k--;
            i--;
            j--;
        }
        while (i >= 0)
        {
            diff = ord(intal1[i]) - borrow;
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result[k] = chr(diff);
            k--;
            i--;
        }
        result[k] = chr(borrow);
    }
    else
    {
        while (i >= 0 && j >= 0)
        {
            diff = ord(intal2[j]) - (ord(intal1[i]) + borrow);

            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result[k] = chr(diff);
            k--;
            i--;
            j--;
        }
        while (j >= 0)
        {
            diff = ord(intal2[j]) - borrow;
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result[k] = chr(diff);
            k--;
            j--;
        }
        result[k] = chr(borrow);
    }
    return adjptr(result);
}

char *intal_multiply(const char *intal1, const char *intal2)
{
    char *result;
    if (strcmp(intal1, "0") == 0 || strcmp(intal2, "0") == 0)
    {
        result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    int l3 = l1 + l2 + 1;
    int carry;
    int product;
    result = (char *)malloc(sizeof(char) * (l3 + 1));
    result[l3] = '\0';
    for (int k = 0; k < l3; k++)
    {
        result[k] = '0';
    }
    for (int i = 0; i < l1; i++)
    {
        carry = 0;
        for (int j = 0; j < l2; j++)
        {
            product = (ord(intal1[l1 - 1 - i]) * ord(intal2[l2 - 1 - j])) + carry + ord(result[l3 - 1 - i - j]);
            carry = msb(product);
            result[l3 - 1 - i - j] = chr(lsb(product));
        }
        for (int j = l2 + i; j < l2 + l1; j++)
        {
            if (carry == 0)
            {
                break;
            }
            product = carry + ord(result[l3 - 1 - j]);
            carry = msb(product);
            result[l3 - 1 - j] = chr(lsb(product));
        }
    }
    return adjptr(result);
}

char *intal_mod(const char *intal1, const char *intal2)
{
    int c = intal_compare(intal1, intal2);
    if (c == 0)
    {
        char *result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if (c == -1)
    {
        char *result = (char *)malloc(sizeof(char) * strlen(intal1));
        strcpy(result, intal1);
        return result;
    }

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    char *result = (char *)malloc(sizeof(char) * (strlen(intal2) + 2));
    for (int i = 0; i < l2; ++i)
    {
        result[i] = intal1[i];
    }
    result[l2] = '\0';

    if (intal_compare(result, intal2) == -1 && l2 < l1)
    {
        int n = strlen(result);
        if (strcmp(result, "0") == 0)
        {
            n = 0;
        }
        result[n] = intal1[l2];
        result[n + 1] = '\0';
        l2++;
    }

    if (intal_compare(result, intal2) != -1)
    {
        char *temp = intal_diff(result, intal2);
        while (intal_compare(temp, intal2) > -1)
        {
            char *diff = temp;
            temp = intal_diff(temp, intal2);
            free(diff);
        }
        strcpy(result, temp);
        free(temp);
    }
    while (l2 < l1)
    {
        if (intal_compare(result, intal2) == -1)
        {
            int n = strlen(result);
            if (strcmp(result, "0") == 0)
            {
                n = 0;
            }
            result[n] = intal1[l2];
            result[n + 1] = '\0';
            l2++;
        }

        if (intal_compare(result, intal2) != -1)
        {
            char *temp = intal_diff(result, intal2);
            while (intal_compare(temp, intal2) > -1)
            {
                char *diff = temp;
                temp = intal_diff(temp, intal2);
                free(diff);
            }

            strcpy(result, temp);
            free(temp);
        }
    }
    return adjptr(result);
}

char *intal_pow(const char *intal1, unsigned int n)
{
    char *result;
    if (strcmp(intal1, "0") == 0)
    {
        result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    char *x = (char *)malloc(sizeof(char) * (n * strlen(intal1) + 1));
    strcpy(x, intal1);
    result = (char *)malloc(sizeof(char) * (n * strlen(intal1) + 1));
    strcpy(result, "1");
    while (n > 0)
    {
        if (n & 1 == 1)
        {
            result = intal_multiply(result, x);
        }
        n = n >> 1;
        x = intal_multiply(x, x);
    }
    free(x);
    return adjptr(result);
}

char *intal_gcd(const char *intal1, const char *intal2)
{
    if (strcmp(intal1, "0") == 0)
    {
        char *result = (char *)malloc(sizeof(char) * strlen(intal2));
        strcpy(result, intal2);
        return result;
    }
    if (strcmp(intal2, "0") == 0)
    {
        char *result = (char *)malloc(sizeof(char) * strlen(intal1));
        strcpy(result, intal1);
        return result;
    }
    char *a = (char *)malloc(sizeof(char) * strlen(intal1));
    char *b = (char *)malloc(sizeof(char) * strlen(intal2));
    strcpy(a, intal1);
    strcpy(b, intal2);
    while (strcmp(b, "0") != 0)
    {
        char *temp = intal_mod(a, b);
        free(a);
        a = b;
        b = temp;
    }
    free(b);
    return a;
}

char *intal_fibonacci(unsigned int n)
{
    char *ppn = (char *)malloc(sizeof(char) * 2);
    ppn[0] = '0';
    ppn[1] = '\0';
    if (n == 0)
    {
        return ppn;
    }
    char *pn = (char *)malloc(sizeof(char) * 2);
    pn[0] = '1';
    pn[1] = '\0';
    if (n == 1)
    {
        return pn;
    }
    char *cn;
    for (unsigned int t = 1; t < n; t++)
    {
        if (t == 999)
        {
            int k = 100;
            int j = 100;
        }
        cn = intal_add(ppn, pn);
        char *temp = ppn;
        ppn = pn;
        pn = cn;
        free(temp);
    }
    free(ppn);
    return adjptr(cn);
}

char *intal_factorial(unsigned int n)
{
    char *start = (char *)malloc(sizeof(char) * 2);
    start[0] = '1';
    start[1] = '\0';
    if (n == 0 || n == 1)
    {
        return start;
    }
    char *strn = (char *)malloc(sizeof(char) * 11);
    strn[10] = '\0';
    sprintf(strn, "%u", n);
    return intal_multiply(strn, intal_factorial(n - 1));
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
    if (n == 0 || k == 0)
    {
        char *result = malloc(sizeof(char) * 2);
        result[0] = '1';
        result[1] = '\0';
        return result;
    }
    if (k > (n / 2))
    {
        k = n - k;
    }
    char **value = malloc(sizeof(char *) * (k + 1));
    for (int i = 0; i <= k; i++)
    {
        value[i] = malloc(sizeof(char) * 1002);
        strcpy(value[i], "0");
    }
    strcpy(value[0], "1");
    char *temp;
    for (int i = 1; i <= n; i++)
    {
        for (int j = k; j > 0; j--)
        {
            temp = intal_add(value[j - 1], value[j]);
            value[j] = temp;
        }
    }
    char *result = (char *)malloc(sizeof(char) * strlen(value[k]));
    strcpy(result, value[k]);
    free(value);
    return result;
}

int intal_max(char **arr, int n)
{
    char *result = arr[0];
    int maxptr = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(result, arr[i]) == -1)
        {
            result = arr[i];
            maxptr = i;
        }
    }
    return maxptr;
}

int intal_min(char **arr, int n)
{
    char *result = arr[0];
    int minptr = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(result, arr[i]) == 1)
        {
            result = arr[i];
            minptr = i;
        }
    }
    return minptr;
}

int intal_search(char **arr, int n, const char *key)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(arr[i], key) == 0)
        {
            return i;
        }
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char *key)
{
    int start = 0, end = n - 1;
    int mid;
    int found = 0;
    while (start <= end && found == 0)
    {
        mid = (start + end) / 2;
        if (intal_compare(arr[mid], key) == 0)
        {
            found = 1;
        }
        else if (intal_compare(arr[mid], key) == 1)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    if (found != 1)
    {
        return -1;
    }
    int ptr = mid;
    while (ptr >= 0 && (intal_compare(arr[ptr], key) == 0))
    {
        ptr--;
    }
    return (ptr + 1);
}

static void Merge(char **arr, int start, int mid, int end)
{
    int l1 = mid - start + 1;
    int l2 = end - mid;
    char **left = (char **)malloc(l1 * sizeof(char *));
    char **right = (char **)malloc(l2 * sizeof(char *));
    for (int i = 0; i < l1; ++i)
    {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < l2; ++i)
    {
        right[i] = arr[mid + i + 1];
    }
    int i = 0, j = 0, ptr = start;
    while (i < l1 && j < l2)
    {
        if (intal_compare(*(left + i), *(right + j)) != 1)
        {
            arr[ptr] = left[i];
            ++i;
        }
        else if (intal_compare(*(left + i), *(right + j)) == 1)
        {
            arr[ptr] = right[j];
            ++j;
        }
        ++ptr;
    }
    while (i < l1)
    {
        arr[ptr] = left[i];
        ++i;
        ++ptr;
    }
    while (j < l2)
    {
        arr[ptr] = right[j];
        ++j;
        ++ptr;
    }
    free(left);
    free(right);
}

static void MergeSort(char **arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(arr, start, mid);
        MergeSort(arr, mid + 1, end);
        Merge(arr, start, mid, end);
    }
}

void intal_sort(char **arr, int n)
{
    int start = 0, end = n - 1;
    MergeSort(arr, start, end);
}

char *coin_row_problem(char **arr, int n)
{
    if (n == 0)
    {
        char *result = (char *)malloc(sizeof(char) * 2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    char *ppn = "0";
    char *pn = arr[0];
    char *cn;
    for (int i = 1; i < n; i++)
    {
        char *temp = intal_add(ppn, arr[i]);
        if (intal_compare(temp, pn) != 1)
        {
            cn = pn;
        }
        else
        {
            cn = temp;
        }
        ppn = pn;
        pn = cn;
    }
    return pn;
}
