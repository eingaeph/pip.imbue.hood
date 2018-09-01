//#include "../allib.h"

#define possibleLine    assert(       ((text[testy].row == NULL) &&       \
                                       (text[testy].size == 0  ))         \
                                 ||                                       \
                                      ((text[testy].row != NULL) &&       \
                                       (text[testy].size >  0  ))         \
                               ); 


#define possibleIxIy    assert( glob.iy <= glob.numbLines);            \
                        assert( glob.iy >= 0); assert( glob.ix >= 0); \
                        assert( glob.ix <= text[glob.iy].size - 1 );

