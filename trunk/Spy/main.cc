#include <iostream>
#include "Process.hh"
#include "ScreenShot.hh"
#include "MsgBox.hh"
#include "Cmd.hh"
using namespace std;

int main() {
    Process proc;
    proc.show_list_process();
   

    ScreenShot sc;
    sc.save("img1.bmp", 0.5);
    sc.save("img2.bmp", 0.3);


    return 0;
}
