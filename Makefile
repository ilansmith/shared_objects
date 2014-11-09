CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-ldl
SO_LFLAGS=-shared -fvisibility=hidden -fvisibility-inlines-hidden -Wl -s
APP_OBJ=app.o ias.so

APP=app

ifeq ($(DEBUG),y)
CFLAGS+=-g
endif

all: $(APP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.so: %.o
	$(CC) $(SO_LFLAGS) $^ -o $@

$(APP): $(APP_OBJ)
	$(CC) $(LDFLAGS) $(filter %.o, $^) -o $@

clean:
	rm -rf *.o

cleanall: clean
	rm -rf *.so $(APP) tags

