#include "smart_pointer.h"

class smart_pointer {
private:
    int* y;

public:
    smart_pointer(int x) {
       y = allocate(x);
    }
    
    ~smart_pointer() {
        release(y);
    }
};

int main() {
    // Nothing
    return 0;
}
