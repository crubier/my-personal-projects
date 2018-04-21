#include <cantor/DeclDBL.h>
#include <cantor/Field.h>
#include <cstdlib>

// $Id: prgm_Field3.cpp,v 1.1 2003/07/29 06:56:42 cantor Exp $

int main(int argc, char** argv) {

  VecDBL v1 (0, -1, 0);
  Field c1 (Cone (v1, 2.4434609527920614077));
  VecDBL v2 (0, 1, 0);
  Field c2 (Cone (v2, 2.4434609527920614077));
  c1 *= c2;

  if (c1.isEmpty()) {
    cout << "wrong" << endl;
  } else {
    cout << "good" << endl;
  }

  return 0;


}
