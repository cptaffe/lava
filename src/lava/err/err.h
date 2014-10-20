// Errors

#ifndef LAVA_LAVA_ERR_ERR_H_
#define LAVA_LAVA_ERR_ERR_H_

#include <iostream>

namespace lava {
  class Err {
    std::ostream *out;
  public:
    Err();
    template<class T>
    friend Err &operator<<(Err &, const T &);
  };

  // templatiness, must stay in header
  // prints anything to err stream.
  template<class T>
  Err &operator<<( Err &err, const T& output ) {
      *err.out << output;
      return err;
  }

  extern Err err;
}

#endif // LAVA_LAVA_ERR_ERR_H_
