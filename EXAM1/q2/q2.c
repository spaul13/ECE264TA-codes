typedef struct {
    int p[10];
    int q[10];
} A;

typedef struct {
    int r[10];
    int s[10];
} B;

typedef struct {
  int x;
  A * y;
  B * z;
} C;