> sudo dnf install gtk3-devel

> git clone https://github.com/imnadev/PlayTogether.git

> cd main

> gcc -export-dynamic -Wall main.c ../data/data.c ../window/admin/admin_socket.c ../window/admin/admin_window.c ../window/client/client_window.c ../window/client/client_socket.c ../window/onboarding/onboarding_window.c  -o CovidTracker -pthread \`pkg-config --cflags --libs gtk+-3.0\` && ./CovidTracker