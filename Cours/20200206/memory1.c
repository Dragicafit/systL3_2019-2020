int g(int n){
  return 3*n;
}

int f(int n){
  int m = g(n);
  return m-1;
}

int main(void){
  int n;
  n = f(11);
  return 0;
}
