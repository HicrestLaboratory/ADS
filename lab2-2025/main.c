#include <limits.h>
#include <stdlib.h>

int max_in_array(int *array, int start, int end);
int fibonacci(int n);
int is_palindrome(char *str, int start, int end);
int count_occurrences(int *array, int target, int start, int end, int n);
void merge_sort(int *array, int start, int end);
int majority_elem(int *array, int start, int end);
int max_subarray_sum(int *array, int start, int end);

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }

int max2(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int max_in_array(int *array, int start, int end) {
  if (start == end)
    return array[start];
  if (start > end)
    return INT_MIN;

  int half = (start + end) / 2;
  int quarter = (start + half) / 2;
  int threeQuarters = (half + end) / 2;

  return max2(max2(max_in_array(array, start, quarter - 1),
                   max_in_array(array, quarter, half - 1)),
              max2(max_in_array(array, half, threeQuarters - 1),
                   max_in_array(array, threeQuarters, end)));
}

int fibonacci(int n) {
  if (n <= 1)
    return max2(n, 0);
  return fibonacci(n - 2) + fibonacci(n - 1);
}

int is_palindrome(char *str, int start, int end) {
  if (end - start <= 1)
    return 1;
  return str[start] == str[end] && is_palindrome(str, start + 1, end - 1);
}

int count_occurrences(int *array, int target, int start, int end, int n) {
  if (start == end)
    return array[start] == target ? 1 : 0;
  if (start > end)
    return 0;

  int diff = end - start;
  int step = diff / n;

  int count = 0;
  for (int i = 0; i < n; i++) {
    int new_start = start + i * step;
    int new_end = start + (i + 1) * step;
    if (i < diff % n)
      new_end++;

    count += count_occurrences(array, target, new_start, new_end, n);
  }
  return count;
}

void merge_sort(int *array, int start, int end) {
  if (start >= end)
    return;

  int mid = (start + end) / 2;
  merge_sort(array, start, mid);
  merge_sort(array, mid + 1, end);

  int diff = end - start;
  int *temp = (int *)malloc(sizeof(int) * diff);

  int i = 0;
  int left = start;
  int right = mid + 1;

  while (left <= mid && right <= end) {
    if (array[left] < array[right]) {
      temp[i] = array[left];
      left++;
    } else {
      temp[i] = array[right];
      right++;
    }
    i++;
  }

  while (left <= mid) {
    temp[i] = array[left];
    left++;
  }
  while (right <= end) {
    temp[i] = array[right];
    right++;
  }

  for (i = 0; i < diff; i++) {
    array[i + start] = temp[i];
  }

  free(temp);
}

int majority_elem(int *array, int start, int end) {
  if (start == end) {
    return array[start];
  }

  int mid = (start + end) / 2;

  int left_maj = majority_elem(array, start, mid - 1);
  int right_maj = majority_elem(array, mid, end);

  if (count_occurrences(array, left_maj, start, end, 2) >
      count_occurrences(array, right_maj, start, end, 2)) {
    return left_maj;
  } else {
    return right_maj;
  }
}

int max_subarray_middle(int *array, int start, int end) {
  int mid = (start + end) / 2;

  int right_sum = 0;
  int right_acc = 0;
  for (int i = mid; i <= end; i++) {
    right_acc += array[i];
    right_sum = max2(right_sum, right_acc);
  }

  int left_sum = 0;
  int left_acc = 0;
  for (int i = mid; i <= end; i++) {
    left_acc += array[i];
    left_sum = max2(left_sum, left_acc);
  }

  return right_sum + left_sum;
}

int max_subarray_sum(int *array, int start, int end) {
  if (start > end) return 0;

  int mid = (start + end) / 2;

  int left_sum = max_subarray_sum(array, start, mid - 1);
  int right_sum = max_subarray_sum(array, mid, end);
  int middle_sum = max_subarray_middle(array, start, end);

  return max2(max2(left_sum, right_sum), middle_sum);
}
