int volatile volatile_gv;
int gv;

// with -O3 reads volatile_gv twice
int get_volatile_gv(void) {
  int x = volatile_gv;
  return x == volatile_gv;
}

// with -O3 optimizes not read gv at all and just returns 1 i.e. true
int gfgv(void) {
  int x = gv;
  return x == gv;
}
