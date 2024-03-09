#include <iostream>

namespace mpcs51044 { 
    struct ForceInit {
        ForceInit() {
            if(count == 0) {
                count = 1;
                std::ios_base::Init();
            }
        }
        private:
            static int count;
    };
    int ForceInit::count = 0;
    static ForceInit forceInit;
}