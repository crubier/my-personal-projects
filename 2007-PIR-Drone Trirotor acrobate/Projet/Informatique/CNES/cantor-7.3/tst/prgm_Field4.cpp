#include <cantor/DeclDBL.h>
#include <cantor/Field.h>
#include <cantor/Util.h>
#include <cstdlib>

// $Id: prgm_Field4.cpp,v 1.1 2005/03/04 07:40:54 chope Exp $

int main(int argc, char** argv) {

  VecDBL a1 (radians (180.0), radians (45.0));
  Field  c1 (Cone (a1, radians (75.0)));
  VecDBL a2 (radians (0.0), radians (-45.0));
  Field  c2 (Cone (a2, radians (75.0)));
  c1 += c2;
  c1.applyMargin (radians (10.0));

  if (c1.isEmpty()) {
    cout << "wrong" << endl;
  } else {
    cout << "good" << endl;
  }

  return 0;


}
