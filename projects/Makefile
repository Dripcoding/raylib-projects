CC := gcc
CFLAGS := -I/usr/local/include
LDFLAGS := -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

purple_rain: purple_rain.c
	$(CC) -o purple_rain purple_rain.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f purple_rain