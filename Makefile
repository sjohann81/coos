CC = gcc
CFLAGS = -Wall -O2
BASE_DIR = .

all: version_a_elf version_b_elf version_c_elf version_d_elf version_e_elf version_f_elf version_g_elf

version_a_elf: version_a_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_a/main main.o
version_a_o: $(BASE_DIR)/version_a/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_a/main.c

version_b_elf: version_b_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_b/main main.o
version_b_o: $(BASE_DIR)/version_b/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_b/main.c
	
version_c_elf: version_c_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_c/main main.o
version_c_o: $(BASE_DIR)/version_c/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_c/main.c

version_d_elf: version_d_o version_d_coos_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_d/main main.o coos.o
version_d_coos_o: $(BASE_DIR)/version_d/coos.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_d/coos.c
version_d_o: $(BASE_DIR)/version_d/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_d/main.c

version_e_elf: version_e_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_e/main main.o
version_e_o: $(BASE_DIR)/version_e/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_e/main.c
	
version_f_elf: version_f_o version_f_coos_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_f/main main.o coos.o
version_f_coos_o: $(BASE_DIR)/version_f/coos.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_f/coos.c
version_f_o: $(BASE_DIR)/version_f/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_f/main.c

version_g_elf: version_g_o version_g_coos_o
	$(CC) $(CFLAGS) -o $(BASE_DIR)/version_g/main main.o coos.o
version_g_coos_o: $(BASE_DIR)/version_g/coos.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_g/coos.c
version_g_o: $(BASE_DIR)/version_g/main.c
	$(CC) $(CFLAGS) -c $(BASE_DIR)/version_g/main.c
	
clean:
	rm *.o
	rm	version_a/main \
		version_b/main \
		version_c/main \
		version_d/main \
		version_e/main \
		version_f/main \
		version_g/main
