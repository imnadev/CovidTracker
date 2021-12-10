#include <gtk/gtk.h>
#include "../window/onboarding/onboarding_window.h"

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    onboarding_window_show();

    return 0;
}
