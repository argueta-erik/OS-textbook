define say
$(info [MQ Demo] $1)
endef

$(call say,Begin)


CC := g++
CFLAGS := -std=c++23 -Wall -pedantic -g -c
LINKFLAGS := -std=c++23 -Wall -pedantic -g
LINKER := g++


BIN_SENDER_NAME := sender
BIN_SENDER := ./$(BIN_SENDER_NAME)
$(call say,Sender executable: $(BIN_SENDER))


BIN_RECEIVER_NAME := receiver
BIN_RECEIVER := ./$(BIN_RECEIVER_NAME)
$(call say,Receiver executable: $(BIN_RECEIVER))


default: help
.phony: default


help:
	@echo
	@echo "*** Makefile Menu ***"
	@echo
	@echo "make run-sender     ==> Run the sender"
	@echo "make run-receiver   ==> Run the receiver"
	@echo
	@echo "make build          ==> Build everything"
	@echo "make build-sender   ==> Build the sender"
	@echo "make build-receiver ==> Build the receiver"
	@echo
	@echo "make clean          ==> Clean temporary build files"
	@echo
.phony: help



run-sender:	build-sender
	$(call say,Running)
	$(BIN_SENDER)


run-receiver:	build-receiver
	$(call say,Running)
	$(BIN_RECEIVER)


build:	build-sender build-receiver
	$(call say,Done building)


build-sender:	$(BIN_SENDER)
	$(call say,Done building)


build-receiver:	$(BIN_RECEIVER)
	$(call say,Done building)


$(BIN_SENDER):	sender.o
	$(call say,Building $@)
	$(LINKER) $(LINKFLAGS) $^ -o $@ 


$(BIN_RECEIVER):	receiver.o
	$(call say,Building $@)
	$(LINKER) $(LINKFLAGS) $^ -o $@


sender.o:	message_queue_sender.cpp MyMessage.hpp
	$(call say,Compiling $@)
	$(CC) $(CFLAGS) $< -o $@


receiver.o:	message_queue_receiver.cpp MyMessage.hpp
	$(call say,Compiling $@)
	$(CC) $(CFLAGS) $< -o $@



clean:
	-rm $(BIN_SENDER)
	-rm $(BIN_RECEIVER)
	-rm *.o












