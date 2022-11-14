// Based on https://web.stanford.edu/~laurik/fsmbook/examples/Einstein'sPuzzle.html

#ifdef KLEE
#include <klee/klee.h>
#endif
#include <assert.h>

typedef enum {
  NAT = 0,
  COL = 1,
  PET = 2,
  DRI = 3,
  SMO = 4
} cols_type;

#define N 5
char e[N*N];

int get_house(cols_type a, char a_value)
{
  int i;
  for (i = 0; i < N; i++) {
    if (a_value == e[i * N + a]) {
      return i;
    }
  }
  return -1;
}

int connect_2(cols_type a, char a_value, cols_type b, char b_value)
{
  int house = get_house(a, a_value);
  if (-1 == house) {
    return 0;
  }
  return get_house(b, b_value) == house;
}

int get_houses(cols_type a, char a_value, int *a_house, cols_type b, char b_value, int *b_house)
{  
  int a_h = get_house(a, a_value);
  int b_h = get_house(b, b_value);
  if (-1 == a_h || -1 == b_h) {
    return 0;
  }
  *a_house = a_h;
  *b_house = b_h;
  return 1;
}

int near(int a_house, int b_house) {
  return (1 == (a_house - b_house)) ||
         (-1 == (a_house - b_house));
}

#define NEAR(ATTRIB_A, VALUE_A, ATTRIB_B, VALUE_B)\
int VALUE_A ## _near_ ## VALUE_B() {\
  int a_house, b_house;\
  int houses = get_houses(ATTRIB_A, #VALUE_A[0], &a_house, ATTRIB_B, #VALUE_B[0], &b_house);\
  if (!houses) {\
    return 0;\
  }\
  return near(a_house, b_house);\
}

int norwegian_first_house()
{
  return 'n' == e[0]; 
}

int brit_house_red()
{
  return connect_2(NAT, 'b', COL, 'r');
}

int swede_pet_dog()
{
  return connect_2(NAT, 's', PET, 'd');
}

int dane_drink_tea()
{
  return connect_2(NAT, 'd', DRI, 't');
}

NEAR(COL, g, COL, w)

int green_drink_coffee()
{
  return connect_2(COL, 'g', DRI, 'c');
}

NEAR(SMO, n, PET, c)

int pall_pet_birds()
{
  return connect_2(SMO, 'p', PET, 'b');
}

int yellow_smoke_dunhill()
{
  return connect_2(COL, 'y', SMO, 'd');
}

int center_drink_milk()
{
  return 2 == get_house(DRI, 'm');
}

int german_smoke_prince()
{
  return connect_2(NAT, 'g', SMO, 'r');
}

NEAR(SMO, n, DRI, w)
NEAR(NAT, n, COL, b)
NEAR(PET, h, SMO, d)

int masters_drink_beer()
{
  return connect_2(SMO, 'm', DRI, 'b');
}

int someone_pet_fish()
{
  return get_house(PET, 'f') >= 0;
}

int main(int argc, char *argv[])
{
#ifdef KLEE
  klee_make_symbolic(e, sizeof(e), "e");
  klee_assert(!(
  		  /* The Norwegian lives in the first house. */
                  norwegian_first_house() &&
                  /* The Brit lives in the red house. */
                  brit_house_red() &&
                  /* The Swede keeps dogs as pets. */
                  swede_pet_dog() &&
                  /* The Dane drinks tea. */
                  dane_drink_tea() &&
                  /* The green house is just on the left of the white house. */
                  g_near_w() &&
                  /* The green house owner drinks coffee. */ 
                  green_drink_coffee() &&
                  /* The man who smokes Blend lives next to the one who keeps cats. */
                  n_near_c() &&
                  /* The person who smokes Pall Mall rears birds. */
                  pall_pet_birds() &&
                  /* The owner of the yellow house smokes Dunhill. */
                  yellow_smoke_dunhill() &&
                  /* The man living in the house right in the center drinks milk. */
                  center_drink_milk() &&
                  /* The German smokes Prince. */
                  german_smoke_prince() &&
                  /* The man who smokes Blend has a neighbor who drinks water. */
                  n_near_w() &&
                  /* The Norwegian lives next to the blue house. */
                  n_near_b() &&
                  /* The man who keeps horses lives next to the man who smokes Dunhill. */
                  h_near_d() &&
                  /* The owner who smokes Blue Master drinks beer. */
                  masters_drink_beer() &&
                  /* Someone has a fish */
                  someone_pet_fish()
 	       ));
#endif
  return 0;
}
