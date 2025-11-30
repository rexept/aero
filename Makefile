# aero - Minimalism. Simplified.

include config.mk

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = aero

all: $(TARGET)

.c.o:
	${CC} -c ${CFLAGS} $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f aero ${OBJS} aero-${VERSION}.tar.gz

# update for aero (icon)
dist: clean
	mkdir -p aero-${VERSION}
	# cp -R LICENSE Makefile README config.def.h config.mk\
	# 	aero.1 drw.h util.h ${SRC} transient.c aero-${VERSION}
	cp -R Makefile README config.mk\
		aero.1 ${SRCS} aero-${VERSION}
	tar -cf aero-${VERSION}.tar aero-${VERSION}
	gzip aero-${VERSION}.tar
	rm -rf aero-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f aero ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/aero
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < aero.1 > ${DESTDIR}${MANPREFIX}/man1/aero.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/aero.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/aero\
		${DESTDIR}${MANPREFIX}/man1/aero.1

.PHONY: all clean dist install uninstall
