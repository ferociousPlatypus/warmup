SRC_FILE=p05.c
BIN_FILE=p05
SUBMIT_DIR=cjs288-p05
.PHONY: pack
.PHONY: clean

all:
	gcc ${SRC_FILE} -o ${BIN_FILE}

pack: all
	mkdir -p ${SUBMIT_DIR}
	cp ${SRC_FILE} ${SUBMIT_DIR}/${SRC_FILE}
	cp ./Makefile ${SUBMIT_DIR}/Makefile
	tar -cvzf ${SUBMIT_DIR}.tar.gz ${SUBMIT_DIR}

clean:
	rm -f ${BIN_FILE}
	rm -f ${SUBMIT_DIR}/*
	rm -rf ${SUBMIT_DIR}
	rm -f ${SUBMIT_DIR}.tar.gz
