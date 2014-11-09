CC=gcc
CFLAGS=-Wall -Werror -fPIC
LDFLAGS=-ldl
SO_LFLAGS=-shared -fvisibility=hidden -fvisibility-inlines-hidden -s
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
	$(CC) -o $@ $(filter %.o, $^) $(LDFLAGS)

clean:
	rm -rf *.o

cleanall: clean
	rm -rf *.so $(APP) tags

