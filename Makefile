CC=gcc
CFLAGS=-Wall -Werror -fvisibility=hidden -s -fPIC
LDFLAGS=-ldl
SO_LFLAGS=-shared
APP_OBJ=app.o ias.so

APP=app

ifeq ($(DEBUG),y)
CFLAGS+=-g
endif

all: $(APP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.so: %.o
	$(foreach obj,$^, \
		$(shell objcopy --localize-hidden --strip-unneeded $(obj)))
	$(CC) $(SO_LFLAGS) $^ -o $@

$(APP): $(APP_OBJ)
	$(CC) -o $@ $(filter %.o, $^) $(LDFLAGS)

clean:
	rm -rf *.o

cleanall: clean
	rm -rf *.so $(APP) tags

