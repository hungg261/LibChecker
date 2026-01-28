#include "testlib.h"
#include <string>

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while (!ans.seekEof()) {
        std::string jans = ans.readToken(); // Đáp án từ Jury
        std::string pans = ouf.readToken(); // Đáp án từ Thí sinh

        if (jans != pans) {
            quitf(_wa, "Expected %s, but found %s", jans.c_str(), pans.c_str());
        }
    }

    quitf(_ok, "Correct answer!");
}
