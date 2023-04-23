#include "Application.h"
#include "Constants.h"

int main() {
    Constants::init();

    Application app;
    app.run();

    return 0;
}